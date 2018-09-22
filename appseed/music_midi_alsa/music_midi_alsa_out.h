#pragma once


namespace music
{


   namespace midi
   {


      namespace alsa
      {


      class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_ALSA out :
         virtual public ::music::midi::out
      {
      public:


         snd_seq_t *       m_poseq;
         string            m_strClientName;
         //int               m_numPorts;


         out(::aura::application * papp);
         virtual ~out();


         virtual ::multimedia::e_result open();
         virtual ::multimedia::e_result close();

         ::multimedia::e_result send_short_message(::music::midi::e_type etype, int iChannel, int iData1, int iData2);

      };


      } // namespace alsa


   } // namespace midi


} // namespace music




