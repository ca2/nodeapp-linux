#pragma once


namespace multimedia
{


   namespace audio_alsa
   {


      class CLASS_DECL_AUDIO_MMSYSTEM snd_pcm :
         virtual public ::multimedia::audio::wave_base
      {
      public:



         snd_pcm_t *                      m_ppcm;
         snd_pcm_hw_params_t *            m_phwparams;
         snd_pcm_sw_params_t *            m_pswparams;
         snd_async_handler_t *            m_phandler;
         int                              m_iCurrentBuffer;
         unsigned int                     m_dwBufferTime;
         unsigned int                     m_dwPeriodTime;
         snd_pcm_uframes_t                m_framesBufferSize;
         snd_pcm_uframes_t                m_framesPeriodSize;
         int                              m_iBufferCount;



         snd_pcm(::aura::application * papp);
         virtual ~snd_pcm();


         ::multimedia::e_result snd_pcm_open(snd_pcm_stream_t stream_type);
         ::multimedia::e_result snd_pcm_close();


      };


   } // namespace audio_alsa


} // namespace multimedia




