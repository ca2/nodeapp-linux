#pragma once


namespace multimedia
{


   namespace audio_alsa
   {


      class  CLASS_DECL_AUDIO_MMSYSTEM wave_out :
         virtual public snd_pcm,
         virtual public ::multimedia::audio::wave_out
      {
      public:


         bool                    m_bWrite;
         int                     m_iBuffer;
         bool                    m_bStarted;
         uint64_t                m_uiStart;
         snd_pcm_status_t *      m_pstatus;

         //::thread *              m_pthreadWriter;
         //int_array               m_iaReady;
         //manual_reset_event      m_evReady;

         int                     m_iBufferCountEffective;


         wave_out(::aura::application * papp);
         virtual ~wave_out();


         void install_message_routing(::message::sender * pinterface) override;

         virtual imedia_time wave_out_get_position_millis();
         imedia_position wave_out_get_position();

         //virtual ::multimedia::e_result wave_out_open(::thread * pthreadCallback, ::count iBufferCount, ::count iBufferSampleCount) override;
         virtual ::multimedia::e_result wave_out_open_ex(::thread * pthreadCallback, uint32_t uiSamplesPerSec, uint32_t uiChannelCount, uint32_t uiBitsPerSample, ::multimedia::audio::e_purpose epurpose) override;
         virtual ::multimedia::e_result wave_out_stop() override;
         virtual ::multimedia::e_result wave_out_close() override;
         virtual ::multimedia::e_result wave_out_pause() override;
         virtual ::multimedia::e_result wave_out_restart() override;
         virtual void * get_os_data();
         snd_pcm_t * wave_out_get_safe_PCM();

         //virtual void alsa_write_thread();

         virtual void wave_out_on_playback_end() override;
         virtual void wave_out_filled(index iBuffer) override;
         virtual bool alsa_should_play();

         virtual bool init_thread() override;
         virtual void term_thread() override;

         virtual ::multimedia::e_result wave_out_start(const imedia_position & position);

         virtual bool on_run_step();

         virtual int defer_underrun_recovery(int err);

         imedia_time wave_out_get_position_millis_for_synch();


      };


   } // namespace audio_alsa


} // namespace multimedia



