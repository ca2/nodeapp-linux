#include "framework.h"


namespace multimedia
{


   namespace audio_alsa
   {


      snd_pcm::snd_pcm(::aura::application * papp) :
         object(papp),
         thread(papp),
         wave_base(papp)
      {

         m_ppcm            = NULL;
         m_phwparams       = NULL;
         m_pswparams       = NULL;
         m_phandler        = NULL;
         m_iCurrentBuffer  = 0;
         m_dwBufferTime    = 100 * 1000; /* ring buffer length in us */
      }

      snd_pcm::~snd_pcm()
      {

         if(m_ppcm != NULL)
         {

            snd_pcm_close();

         }

      }

      ::multimedia::e_result snd_pcm::snd_pcm_open(snd_pcm_stream_t stream_type)
      {

         ::multimedia::e_result mmr;
         ASSERT(m_ppcm == NULL);


         sp(::multimedia::audio::wave_format) pformat = m_pwaveformat;


         int err;
         short buf[128];


         int cardNum = -1;
         int devNum = -1;
         int subDevNum = -1;
         int subDevCount = 0;
         string strFormat;
         stringa straName;
         stringa straDevice;


         // Start with first card
         cardNum = -1;
         bool bFound = false;

         for (;;)
         {
            snd_ctl_t * cardHandle;

            // Get next sound card's card number. When "cardNum" == -1, then ALSA
            // fetches the first card
            if ((err = snd_card_next(&cardNum)) < 0)
            {
               TRACE("Can't get the next card number: %s\n", snd_strerror(err));
               break;
            }

            // No more cards? ALSA sets "cardNum" to -1 if so
            if (cardNum < 0)
               break;

            // Open this card's control interface. We specify only the card number -- not
            // any device nor sub-device too
            {

               string strFormat;

               strFormat.Format("hw:%i", cardNum);
               if ((err = snd_ctl_open(&cardHandle, strFormat, 0)) < 0)
               {
                  TRACE("Can't open card %i: %s\n", cardNum, snd_strerror(err));
                  continue;
               }

            }


            {

               // Start with the first wave device on this card
               devNum = -1;

               for (;;)
               {

                  snd_pcm_info_t  *pcmInfo;


                  // Get the number of the next wave device on this card
                  if ((err = snd_ctl_pcm_next_device(cardHandle, &devNum)) < 0)
                  {
                     TRACE("Can't get next wave device number: %s\n", snd_strerror(err));
                     break;
                  }

                  // No more wave devices on this card? ALSA sets "devNum" to -1 if so.
                  // NOTE: It's possible that this sound card may have no wave devices on it
                  // at all, for example if it's only a MIDI card
                  if (devNum < 0)
                     break;

                  // To get some info about the subdevices of this wave device (on the card), we need a
                  // snd_pcm_info_t, so let's allocate one on the stack
                  snd_pcm_info_alloca(&pcmInfo);
                  memset(pcmInfo, 0, snd_pcm_info_sizeof());

                  // Tell ALSA which device (number) we want info about
                  snd_pcm_info_set_device(pcmInfo, devNum);

                  // Get info on the wave outs of this device
                  snd_pcm_info_set_stream(pcmInfo, stream_type);

                  subDevCount = 1;
                  subDevNum = -1;

                  // More subdevices?
                  while (++subDevNum < subDevCount)
                  {

                     // Tell ALSA to fill in our snd_pcm_info_t with info on this subdevice

                     snd_pcm_info_set_subdevice(pcmInfo, subDevNum);

                     if ((err = snd_ctl_pcm_info(cardHandle, pcmInfo)) < 0)
                     {

                        TRACE("No wave output subdevice hw:%i,%i : %s\n", cardNum, devNum, snd_strerror(err));

                        continue;

                     }

                     // Print out how many subdevices (once only)
                     if (!subDevNum)
                     {

                        subDevCount = snd_pcm_info_get_subdevices_count(pcmInfo);

                        TRACE("\nFound %i wave output subdevices on card %i, %i : %s \n", subDevCount, cardNum, devNum, snd_strerror(err));

                     }

                     // NOTE: If there's only one subdevice, then the subdevice number is immaterial,
                     // and can be omitted when you specify the hardware name
                     //TRACE((subDevCount > 1 ? "    hw:%i,%i,%i\n" : "    hw:%i,%i\n"), cardNum, devNum, subDevNum);

                     if(subDevCount > 1)
                     {

                        strFormat.Format("hw:%d,%d,%d", cardNum, devNum, subDevNum);

                     }
                     else
                     {

                        strFormat.Format("hw:%d,%d", cardNum, devNum);

                     }

                     straName.add(snd_pcm_info_get_name(pcmInfo));

                     straDevice.add(strFormat);

                  }

               }
            }

            // Close the card's control interface after we're done with it
            snd_ctl_close(cardHandle);

         }

         snd_config_update_free_global();

         if(straDevice.get_count() < 0)
            return result_error;

         for(int i = 0; i < straDevice.get_count(); i++)
         {

            TRACE("%s", straName[i] + " : " + straDevice[i]);

         }

         //string strHw = "hw:0,0";
         string strHw = "default";


         if ((err = ::snd_pcm_open (&m_ppcm, strHw, stream_type, SND_PCM_NONBLOCK)) < 0)
         {

            TRACE ("cannot open audio device %s (%s)\n", strHw, snd_strerror (err));

            return result_error;

         }

         snd_pcm_hw_params_malloc (&m_phwparams);

         if ((err = snd_pcm_hw_params_any (m_ppcm, m_phwparams)) < 0)
         {

            TRACE ("cannot initialize hardware parameter structure (%s)\n", snd_strerror (err));

            return result_error;

         }


         if ((err = snd_pcm_hw_params_set_access (m_ppcm, m_phwparams, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
         {

            TRACE ("cannot set access type (%s)\n", snd_strerror (err));

            return result_error;

         }

         snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;

         if(pformat->wBitsPerSample == 16)
         {

            format = SND_PCM_FORMAT_S16_LE;

         }
         else if(pformat->wBitsPerSample == 8)
         {

            format = SND_PCM_FORMAT_U8;

         }

         if ((err = snd_pcm_hw_params_set_format (m_ppcm, m_phwparams, format)) < 0)
         {

            string strError = snd_strerror (err);

            TRACE ("cannot set sample format (%s)\n", strError);

            return result_error;

         }

         unsigned int uiFreq = pformat->nSamplesPerSec;

         int dir = 0;

         if ((err = snd_pcm_hw_params_set_rate_near (m_ppcm, m_phwparams, &uiFreq, &dir)) < 0)
         {

            TRACE ("cannot set sample rate (%s)\n", snd_strerror (err));

            return result_error;

         }


         pformat->nSamplesPerSec = uiFreq;

         if ((err = snd_pcm_hw_params_set_channels (m_ppcm, m_phwparams, pformat->nChannels)) < 0)
         {

            TRACE ("cannot set channel count (%s)\n", snd_strerror (err));

            return result_error;

         }

         dir = 1;

         if((err = snd_pcm_hw_params_set_period_time_near(m_ppcm, m_phwparams, &m_dwPeriodTime, &dir)) < 0)
         {

            TRACE("Unable to set period time %i for playback: %s\n", m_dwPeriodTime, snd_strerror(err));

            return result_error;

         }

         m_dwBufferTime = m_iBufferCount * 1000 * 1000 / uiFreq;

         dir = 1;

         if((err = snd_pcm_hw_params_set_buffer_time_near(m_ppcm, m_phwparams, &m_dwBufferTime, &dir)) < 0)
         {

            TRACE("Unable to set buffer time %i for playback: %s\n", m_dwBufferTime, snd_strerror(err));

            return result_error;

         }

         snd_pcm_uframes_t size;

         dir = 1;

         if((err = snd_pcm_hw_params_get_period_size(m_phwparams, &size, &dir)) < 0)
         {

            TRACE("Unable to get period size for playback: %s\n", snd_strerror(err));

            return result_error;

         }

         m_framesPeriodSize = size;

         if((err = snd_pcm_hw_params_get_buffer_size(m_phwparams, &size)) < 0)
         {

            TRACE("Unable to get buffer size for playback: %s\n", snd_strerror(err));

            return result_error;

         }

         m_framesBufferSize = size;

         m_iBufferCount = (m_framesBufferSize / m_framesPeriodSize);

         if ((err = snd_pcm_hw_params (m_ppcm, m_phwparams)) < 0)
         {

            TRACE("cannot set parameters (%s)\n", snd_strerror (err));

            return result_error;

         }

         snd_pcm_sw_params_malloc(&m_pswparams);

         err = snd_pcm_sw_params_current(m_ppcm, m_pswparams);

         if (err < 0)
         {

            printf("Unable to determine current m_pswparams: %s\n", snd_strerror(err));

            return result_error;

         }

         err = snd_pcm_sw_params_set_tstamp_mode(m_ppcm, m_pswparams, SND_PCM_TSTAMP_ENABLE);
         if (err < 0)
         {

            printf("Unable to set tstamp mode : %s\n", snd_strerror(err));

            return result_error;

         }

         err = snd_pcm_sw_params_set_tstamp_type(m_ppcm, m_pswparams, SND_PCM_TSTAMP_TYPE_MONOTONIC_RAW);

         if (err < 0)
         {

            printf("Unable to set tstamp type : %s\n", snd_strerror(err));

            return result_error;

         }

         err = snd_pcm_sw_params(m_ppcm, m_pswparams);

         if (err < 0)
         {

            printf("Unable to set swparams_p : %s\n", snd_strerror(err));

            return result_error;

         }

         return result_success;

      }


      ::multimedia::e_result snd_pcm::snd_pcm_close()
      {

         if(m_ppcm == NULL)
         {

            return result_success;

         }


         int err;

         if ((err = ::snd_pcm_close(m_ppcm)) < 0)
         {

            TRACE ("failed to close successfully sound interface (%s)\n",snd_strerror (err));

            return result_error;

         }

         return result_success;

      }


   } // namespace audio_alsa


} // namespace multimedia







