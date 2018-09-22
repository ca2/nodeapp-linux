#include "framework.h"


long long timestamp2ns(snd_htimestamp_t t)
{

   long long nsec;

   nsec = t.tv_sec * 1000000000;
   nsec += t.tv_nsec;

   return nsec;

}


long long timediff(snd_htimestamp_t t1, snd_htimestamp_t t2)
{

   long long nsec1, nsec2;

   nsec1 = timestamp2ns(t1);
   nsec2 = timestamp2ns(t2);

   return nsec1 - nsec2;

}


namespace multimedia
{


   namespace audio_alsa
   {


      wave_out::wave_out(::aura::application * papp) :
         object(papp),
         ::thread(papp),
        wave_base(papp),
         snd_pcm(papp),
         ::multimedia::audio::wave_out(papp) // ,
         //m_evReady(papp)
      {

         m_estate             = state_initial;
         m_pthreadCallback    = NULL;
         m_mmr                = result_success;
         m_peffect            = NULL;
         m_bWrite             = false;
         m_bStarted           = false;

         m_pstatus            = NULL;
         snd_pcm_status_malloc (&m_pstatus);

         //m_pthreadWriter      = NULL;

      }


      wave_out::~wave_out()
      {

         snd_pcm_status_free (m_pstatus);

      }


      void wave_out::install_message_routing(::message::sender * psender)
      {

         ::multimedia::audio::wave_out::install_message_routing(psender);

      }


      bool wave_out::init_thread()
      {

         if(!::multimedia::audio::wave_out::init_thread())
            return false;

         return true;

      }


      void wave_out::term_thread()
      {

         ::multimedia::audio::wave_out::term_thread();

         thread::term_thread();

      }


//      ::multimedia::e_result wave_out::wave_out_open(thread * pthreadCallback, ::count iBufferCount, ::count iBufferSampleCount)
//      {
//
//         single_lock sLock(m_pmutex, TRUE);
//
//         if(m_ppcm != NULL && m_estate != state_initial)
//         {
//
//            return result_success;
//
//         }
//
//         m_pthreadCallback = pthreadCallback;
//         ::multimedia::e_result mmr;
//         ASSERT(m_ppcm == NULL);
//         ASSERT(m_estate == state_initial);
//
//         //m_pwaveformat->wFormatTag = WAVE_FORMAT_PCM;
//         m_pwaveformat->wFormatTag = 0;
//         m_pwaveformat->nChannels = 2;
//         m_pwaveformat->nSamplesPerSec = 44100;
//         m_pwaveformat->wBitsPerSample = sizeof(multimedia::audio::WAVEBUFFERDATA) * 8;
//         m_pwaveformat->nBlockAlign = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
//         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
//         m_pwaveformat->cbSize = 0;
//
//         if((m_mmr = this->snd_pcm_open(SND_PCM_STREAM_PLAYBACK)) != result_success)
//         {
//
//            return result_error;
//
//         }
//
//
//
//         uint32_t uiBufferSizeLog2;
//         uint32_t uiBufferSize;
//         uint32_t uiAnalysisSize;
//         uint32_t uiAllocationSize;
//         uint32_t uiInterestSize;
//         uint32_t uiSkippedSamplesCount;
//         uint32_t uiBufferCount = iBufferCount;
//
//         if(m_pwaveformat->nSamplesPerSec == 44100)
//         {
//            uiBufferSizeLog2 = 16;
//            uiBufferSize = m_pwaveformat->nChannels * 2 * iBufferSampleCount; // 512 kbytes
//            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
//            if(iBufferCount > 0)
//            {
//               uiAllocationSize = iBufferCount * uiAnalysisSize;
//            }
//            else
//            {
//               uiAllocationSize = 8 * uiAnalysisSize;
//            }
//            uiInterestSize = 200;
//            uiSkippedSamplesCount = 2;
//         }
//         else if(m_pwaveformat->nSamplesPerSec == 22050)
//         {
//            uiBufferSizeLog2 = 10;
//            uiBufferSize = 4 * 1 << uiBufferSizeLog2;
//            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
//            uiAllocationSize = 4 * uiAnalysisSize;
//            uiInterestSize = 200;
//            uiSkippedSamplesCount = 1;
//         }
//         else if(m_pwaveformat->nSamplesPerSec == 11025)
//         {
//            uiBufferSizeLog2 = 10;
//            uiBufferSize = 2 * 1 << uiBufferSizeLog2;
//            uiAnalysisSize = 2 * 1 << uiBufferSizeLog2;
//            uiAllocationSize = 4 * uiAnalysisSize;
//            uiInterestSize = 200;
//            uiSkippedSamplesCount = 1;
//         }
//
//         //uiBufferCount = 1;
//
//         wave_out_get_buffer()->PCMOutOpen(this, uiBufferSize, uiBufferCount, 128, m_pwaveformat, m_pwaveformat);
//
//         m_pprebuffer->open(this, m_pwaveformat->nChannels, uiBufferCount, iBufferSampleCount); // group sample count
//
//         int iFrameSize = (m_pwaveformat->nChannels * m_pwaveformat->wBitsPerSample) / 8;
//
//         int err;
//
//         snd_pcm_sw_params_alloca(&m_pswparams);
//
//         /* get the current m_pswparams */
//         err = snd_pcm_sw_params_current(m_ppcm, m_pswparams);
//
//         if (err < 0)
//         {
//
//            TRACE("Unable to determine current m_pswparams for playback: %s\n", snd_strerror(err));
//
//            return result_error;
//
//         }
//
//
//         /* start the transfer when the buffer is almost full: */
//         /* (buffer_size / avail_min) * avail_min */
//         err = snd_pcm_sw_params_set_start_threshold(m_ppcm, m_pswparams, (m_framesBufferSize / m_framesPeriodSize) * m_framesPeriodSize);
//         if (err < 0)
//         {
//
//            TRACE("Unable to set start threshold mode for playback: %s\n", snd_strerror(err));
//
//            return result_error;
//
//         }
//
//         /* allow the transfer when at least period_size samples can be processed */
//         err = snd_pcm_sw_params_set_avail_min(m_ppcm, m_pswparams, m_framesPeriodSize);
//         if (err < 0)
//         {
//
//            TRACE("Unable to set avail min for playback: %s\n", snd_strerror(err));
//
//            return result_error;
//
//         }
//
//         /* write the parameters to the playback device */
//         err = snd_pcm_sw_params(m_ppcm, m_pswparams);
//         if (err < 0)
//         {
//
//            TRACE("Unable to set sw params for playback: %s\n", snd_strerror(err));
//
//            return result_error;
//
//         }
//
//         m_estate = state_opened;
//
//         return result_success;
//
//      }


      ::multimedia::e_result wave_out::wave_out_open_ex(thread * pthreadCallback, uint32_t uiSamplesPerSec, uint32_t uiChannelCount, uint32_t uiBitsPerSample, ::multimedia::audio::e_purpose epurpose)
      {

         single_lock sLock(m_pmutex, TRUE);

         TRACE("multimedia::audio_alsa::wave_out_open_ex");

         if(m_ppcm != NULL && m_estate != state_initial)
         {

            return result_success;

         }


         m_dwPeriodTime =  20 * 1000; /* period time in us */

         m_iBufferCountEffective = 4;

         if(epurpose == ::multimedia::audio::purpose_playback)
         {

            m_dwPeriodTime =  50 * 1000; /* period time in us */

            m_iBufferCountEffective = 8;

         }

         m_iBufferCount = m_iBufferCountEffective;

         m_pthreadCallback = pthreadCallback;

         ASSERT(m_ppcm == NULL);

         ASSERT(m_estate == state_initial);

         m_pwaveformat->wFormatTag        = 0;
         m_pwaveformat->nChannels         = (WORD) uiChannelCount;
         m_pwaveformat->nSamplesPerSec    = uiSamplesPerSec;
         m_pwaveformat->wBitsPerSample    = (WORD) uiBitsPerSample;
         m_pwaveformat->nBlockAlign       = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         m_pwaveformat->nAvgBytesPerSec   = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         m_pwaveformat->cbSize            = 0;

         if((m_mmr = this->snd_pcm_open(SND_PCM_STREAM_PLAYBACK)) != result_success)
         {

            return m_mmr;

         }

         if(m_iBufferCount < m_iBufferCountEffective)
         {

            m_iBufferCountEffective = m_iBufferCount;

         }

         UINT uiBufferSize = snd_pcm_frames_to_bytes(m_ppcm, m_framesPeriodSize);

         wave_out_get_buffer()->PCMOutOpen(this, uiBufferSize, m_iBufferCountEffective, 128, m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open(m_pwaveformat->nChannels, m_iBufferCountEffective, m_framesPeriodSize);

//         m_pprebuffer->SetMinL1BufferCount(wave_out_get_buffer()->GetBufferCount());

         int err;

         if((err = snd_pcm_sw_params_current(m_ppcm, m_pswparams)) < 0)
         {

            TRACE("unable to determine current m_pswparams for playback: %s\n", snd_strerror(err));

            return result_error;

         }

         int iBufferThreshold = MIN((m_framesBufferSize / m_framesPeriodSize), m_iBufferCountEffective);

         snd_pcm_sframes_t framesThreshold = (iBufferThreshold - 1) * m_framesPeriodSize;

         // start the transfer when the buffer is almost full:
         if((err = snd_pcm_sw_params_set_start_threshold(m_ppcm, m_pswparams, framesThreshold)) < 0)
         {

            TRACE("unable to set start threshold mode for playback: %s\n", snd_strerror(err));

            return result_error;

         }

         // allow the transfer when at least m_framesPeriodSize samples can be processed
         if((err = snd_pcm_sw_params_set_avail_min(m_ppcm, m_pswparams, m_framesPeriodSize)) < 0)
         {

            TRACE("unable to set avail min for playback: %s\n", snd_strerror(err));

            return result_error;

         }

         // write the parameters to the playback device
         if((err = snd_pcm_sw_params(m_ppcm, m_pswparams)) < 0)
         {

            TRACE("unable to set sw params for playback: %s\n", snd_strerror(err));

            return result_error;

         }

         m_estate = state_opened;

         m_epurpose = epurpose;

         return result_success;

      }


      ::multimedia::e_result wave_out::wave_out_close()
      {

         single_lock sLock(m_pmutex, TRUE);

         TRACE("multimedia::audio_alsa::wave_out_close");

         if(m_estate == state_playing)
         {

            wave_out_stop();

         }

         if(m_estate != state_opened)
         {

            return result_success;

         }

         ::multimedia::e_result mmr;

         mmr = this->snd_pcm_close();

         m_ppcm = NULL;

         ::multimedia::audio::wave_out::wave_out_close();

         m_estate = state_initial;

         return result_success;

      }


      ::multimedia::e_result wave_out::wave_out_stop()
      {

         synch_lock sLock(m_pmutex);

         TRACE("multimedia::audio_alsa::wave_out_stop");

         if(m_estate != state_playing && m_estate != state_paused)
         {

            return result_error;

         }

         m_pprebuffer->stop();

         m_estate = state_stopping;

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_alsa output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_mmr = translate_alsa(snd_pcm_drain(m_ppcm));

         if(m_mmr == result_success)
         {

            m_estate = state_opened;

         }

         return m_mmr;

      }


      ::multimedia::e_result wave_out::wave_out_pause()
      {

         single_lock sLock(m_pmutex, TRUE);

         ASSERT(m_estate == state_playing);

         TRACE("multimedia::audio_alsa::wave_out_pause");

         if(m_estate != state_playing)
         {

            return result_error;

         }

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_alsa output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_mmr = translate_alsa(snd_pcm_pause(m_ppcm, 1));

         ASSERT(m_mmr == result_success);

         if(m_mmr == result_success)
         {

            m_estate = state_paused;

         }

         return m_mmr;

      }


      ::multimedia::e_result wave_out::wave_out_restart()
      {

         synch_lock sLock(m_pmutex);

         ASSERT(m_estate == state_paused);

         TRACE("multimedia::audio_alsa::wave_out_restart");

         if(m_estate != state_paused)
            return result_error;

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_alsa output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_mmr = translate_alsa(snd_pcm_pause(m_ppcm, 0));

         ASSERT(m_mmr == result_success);

         if(m_mmr == result_success)
         {
            m_estate = state_playing;
         }

         return m_mmr;

      }


      imedia_time wave_out::wave_out_get_position_millis()
      {

         synch_lock sl(m_pmutex);

         imedia_time time = 0;

         if(m_ppcm != NULL)
         {

            if(snd_pcm_status(m_ppcm, m_pstatus) == 0)
            {

               snd_htimestamp_t t;

               snd_pcm_status_get_htstamp (m_pstatus, &t);

               time = t.tv_sec * 1000 + t.tv_nsec / (1000 * 1000);

            }

         }

         if(time > 0)
         {

            output_debug_string("test");

         }

         return time;

      }


      imedia_position wave_out::wave_out_get_position()
      {

         return wave_out_get_position_millis();

      }


      void wave_out::wave_out_on_playback_end()
      {

         TRACE("multimedia::audio_alsa::wave_out_on_playback_end");

         ::multimedia::audio::wave_out::wave_out_on_playback_end();

      }


      snd_pcm_t * wave_out::wave_out_get_safe_PCM()
      {

         if(this == NULL)
         {

            return NULL;

         }

         return m_ppcm;

      }


      void * wave_out::get_os_data()
      {

         return m_ppcm;

      }


      bool wave_out::alsa_should_play()
      {

         if(!::get_thread_run())
         {

            return false;

         }

         if(m_ppcm == NULL)
         {

            TRACE("alsa_out_buffer_ready m_ppcm == NULL");

            return false;

         }

         if(m_estate != audio::wave_out::state_playing && m_estate != audio::wave_out::state_stopping)
         {

            TRACE("alsa_out_buffer_ready failure: !playing && !stopping");

            return false;

         }

         return true;

      }


//      void wave_out::alsa_write_thread()
//      {
//
//         ::multithreading::set_priority(::multithreading::priority_time_critical);
//
//         int_array iaReady;
//
//         int iReady;
//
//         while(alsa_should_play())
//         {
//
//            {
//
//               synch_lock sl(m_pmutex);
//
//               if(m_iaReady.has_elements())
//               {
//
//                  iReady = m_iaReady[0];
//
//                  m_iaReady.remove_at(0);
//
//               }
//               else
//               {
//
//                  m_evReady.ResetEvent();
//
//                  sl.unlock();
//
//                  m_evReady.wait(micros(m_dwPeriodTime));
//
//                  continue;
//
//               }
//
//            }
//
//            if(!alsa_out_buffer_ready(iReady))
//            {
//
//               TRACE("ALSA wave_out: an error has occurred.\n");
//
//               break;
//
//            }
//
//         }
//
//         end:;
//
//         m_pthreadWriter = NULL;
//
//         if(m_estate == state_opened)
//         {
//
//            TRACE("ALSA wave_out: now the state is: opened.\n");
//
//         }
//
//      }


      void wave_out::wave_out_filled(index iBuffer)
      {

         synch_lock sLock(m_pmutex);

         if(m_ppcm == NULL)
         {

            return;

         }

         int result = 0;

         snd_pcm_sframes_t framesRemain = m_framesPeriodSize;

         int cptr = snd_pcm_frames_to_bytes(m_ppcm, framesRemain);

         ::multimedia::e_result mmr = result_success;

         snd_pcm_sframes_t avail;

         while(::get_thread_run())
         {

            avail = snd_pcm_avail_update(m_ppcm);

            if(avail == -EAGAIN)
            {

               continue;

            }
            else if(avail < 0)
            {

               const char * pszError = snd_strerror(avail);

               TRACE("ALSA wave_out snd_pcm_avail error: %s (%d)\n", pszError, avail);

               avail = defer_underrun_recovery(avail);

               if(avail >= 0)
               {

                  TRACE("ALSA wave_out snd_pcm_avail underrun recovery success (snd_pcm_avail)");

                  break;

               }

               TRACE("ALSA wave_out snd_pcm_avail minimum byte count %d\n", cptr);

               m_estate = state_opened;

               m_mmr = result_error;

               TRACE("ALSA wave_out snd_pcm_avail error: %s\n", snd_strerror(avail));

               return;

            }
            else if(avail >= m_framesPeriodSize)
            {

               break;

            }

            Sleep(m_dwPeriodTime / (4 * 1000));

         }


         signed short * ptr;

         memory m;

         if(iBuffer >= 0)
         {

            ptr = (signed short *) wave_out_get_buffer_data(iBuffer);

         }
         else
         {

            m.allocate(cptr);

            m.zero();

            ptr = (short int *) m.get_data();

         }

         int iZero = 0;

         while (cptr > 0)
         {

            result = snd_pcm_writei(m_ppcm, ptr, framesRemain);

            m_bStarted = true;

            if(result == -EINTR)
            {

               continue;

            }
            else if(result == -EAGAIN)
            {

               continue;

            }
            else if(result < 0)
            {

               TRACE("ALSA wave_out snd_pcm_writei error: %s (%d)\n", snd_strerror(result), result);

               result = defer_underrun_recovery(result);

               if(result >= 0)
               {

                  TRACE("ALSA wave_out snd_pcm_writei underrun recovery success (snd_pcm_writei)");

                  continue;

               }

               m_estate = state_opened;

               m_mmr = result_error;

               TRACE("ALSA wave_out snd_pcm_writei couldn't recover from error: %s\n", snd_strerror(result));

               return;

            }

            int iBytes = snd_pcm_frames_to_bytes(m_ppcm, result);

            framesRemain -= result;

            if(iBuffer >= 0)
            {

               m_pprebuffer->m_position += result;

            }

            ptr = (short *) (((byte *) ptr) + iBytes);

            cptr -= iBytes;

         }

         m_iBufferedCount++;

         sLock.unlock();

         if(iBuffer >= 0)
         {

            m_psynththread->post_message(message_free, iBuffer);

         }

      }


      imedia_time wave_out::wave_out_get_position_millis_for_synch()
      {

         if (m_pprebuffer == NULL)
            return 0;

         int64_t dwPosition = m_pprebuffer->m_position;

         dwPosition *= 1000;

         if (m_pwaveformat->nSamplesPerSec <= 0)
            return 0;

         dwPosition /= m_pwaveformat->nSamplesPerSec;

         return dwPosition;

      }

      ::multimedia::e_result wave_out::wave_out_start(const imedia_position & position)
      {

         single_lock sLock(m_pmutex, TRUE);

         if(m_estate == state_playing)
         {

            return result_success;

         }

         if(m_estate != state_opened && m_estate != state_stopped)
         {

            return result_error;

         }

         int err = 0;

         if ((err = snd_pcm_prepare (m_ppcm)) < 0)
         {

            TRACE ("wave_out_start: Cannot prepare audio interface for use (%s)\n",snd_strerror (err));

            return result_error;

         }

         TRACE("wave_out_start: snd_pcm_prepare OK");

         m_bStarted = false;

         m_mmr = ::multimedia::audio::wave_out::wave_out_start(position);

         if(failed(m_mmr))
         {

            TRACE("wave_out_start: ::multimedia::audio::wave_out::wave_out_start FAILED");

            return m_mmr;

         }

//         m_pthreadWriter = fork([&]()
//         {
//
//            alsa_write_thread();
//
//         });

         TRACE("wave_out_start: ::multimedia::audio::wave_out::wave_out_start OK");

         return result_success;

      }


      bool wave_out::on_run_step()
      {

         return false;

      }


      int wave_out::defer_underrun_recovery(int err)
      {

         if (err == -EPIPE)
         {

            TRACE("underrun_recovery, going to snd_pcm_prepare: %s\n", snd_strerror(err));

            err = snd_pcm_prepare(m_ppcm);

            if (err < 0)
            {

               TRACE("Can't recover from underrun, snd_pcm_prepare failed: %s\n", snd_strerror(err));

            }

         }
         else if (err == -ESTRPIPE)
         {

            TRACE("underrun_recovery, snd_pcm_prepare returned -ESTRPIPE: %s\n", snd_strerror(err));

            while ((err = snd_pcm_resume(m_ppcm)) == -EAGAIN)
            {

               TRACE("underrun_recovery, snd_pcm_resume returned -EAGAIN: %s\n", snd_strerror(err));

               sleep(1); /* wait until the suspend flag is released */

            }

            if (err < 0)
            {

               err = snd_pcm_prepare(m_ppcm);

               if (err < 0)
               {

                  TRACE("Can't recovery from suspend, snd_pcm_prepare failed: %s\n", snd_strerror(err));

               }

            }

         }

         return err;

      }


//      void wave_out::alsa_out_free(index iBuffer)
//      {
//
//         ::multimedia::audio::wave_out::wave_out_free(iBuffer);
//
//      }
//

   } // namespace audio_alsa


} // namespace multimedia






