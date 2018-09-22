#pragma once


//#include "music_midi_alsa_player_window.h"
//#include "music_midi_alsa_player_callback.h"
//#include "music_midi_alsa_player_interface.h"


namespace music
{


   namespace midi
   {


      namespace alsa
      {


      class sequence_thread;


      namespace player
      {

         class player;




         class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_ALSA player :
            virtual public ::music::midi::player::callback,
            virtual public ::music::midi::player::player
         {
         public:


            player(::aura::application *  papp);
            virtual ~player();


            void install_message_routing(::message::sender * pinterface) override;


            bool PlayRate(double dRate = 0.0, uint32_t dwEllapse = 584) override;
            bool Play(imedia_position tkStart, uint32_t dwEllapse = 584) override;

            virtual bool init_thread() override;
            virtual void term_thread() override;

            virtual void pre_translate_message(::message::message * pobj) override;

            void OnMmsgDone(::music::midi::sequence *pSeq);
            DECL_GEN_SIGNAL(OnUserMessage);
               void SaveFile(const char * lpszPathName);
            void SetPosition(double dRate);
            virtual void pause() override;
            virtual void close_file() override;
            void SendReset();
            bool ExecuteCommand(::music::midi::player::e_command ecommand, uint32_t dwEllapse);
            virtual void OnMidiOutDeviceChange();

            uint32_t GetMidiOutDevice();
            void PostNotifyEvent(::music::midi::player::e_notify_event eevent);

            imedia_position RateToTicks(double dRate);

            bool SetTempoShift(int32_t iTempoShift);

            bool SetMidiOutDevice(uint32_t uiDevice);

            ::multimedia::e_result SetInterface(player * pinterface);

            ::multimedia::e_result Initialize(::thread * pthread);

            bool IsPlaying();

            void PostGMReset();
            void PostTempoChange();
            void SendTempoChange(); // verificar


            DECL_GEN_SIGNAL(OnNotifyEvent);
            DECL_GEN_SIGNAL(OnMultimediaMidiOutputMessageDone);
            DECL_GEN_SIGNAL(OnMultimediaMidiOutputMessagePositionCB);

            // midi central listener
            DECL_GEN_SIGNAL(on_attribute_change);



            virtual bool OnOpenMidiPlayer();


            virtual bool Initialize(sp(::music::midi::midi) pcentral);
            virtual bool Finalize();


            virtual bool OpenMidiPlayer();


            virtual void OnMmsgDone(::music::midi::sequence *pSeq, ::music::midi::LPMIDIDONEDATA lpmdd);
            virtual void OnMidiPlayerNotifyEvent(::music::midi::player::notify_event * pdata);
            virtual void OnMidiLyricEvent(array<::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1&> * pevents);

         };


      } // namespace player


      } // namespace alsa


   } // namespace midi


} // namespace music






