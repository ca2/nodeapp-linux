#pragma once


namespace multimedia
{


   namespace audio_alsa
   {


      //void translate(WAVEFORMATEX & formatex, ::multimedia::audio::wave_format * pwaveformat);
      //void translate(WAVEHDR & wavehdr, ::multimedia::audio::wave_buffer * pwavebuffer, int iIndex);
      //LPWAVEHDR create_new_WAVEHDR(::multimedia::audio::wave_buffer * pwavebuffer, int iIndex);
      //LPWAVEHDR get_os_data(::multimedia::audio::wave_buffer * pwavebuffer, int iIndex);

      CLASS_DECL_AUDIO_MMSYSTEM ::multimedia::e_result translate_alsa(int err);


   } // namespace audio_alsa


} // namespace multimedia





