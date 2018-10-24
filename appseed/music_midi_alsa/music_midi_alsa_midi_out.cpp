#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace alsa
      {


         midi_out::midi_out(::aura::application * papp, string driver) :
            ::object(papp),
            ::music::midi::message_out(papp),
            m_file(papp)
         {

            m_iWrite = 0;

            m_prawmidi = NULL;
// sudo modprobe snd-virmidi snd_index=1
//            aconnect -i
//             Or?
//            aconnect -o

//On my system this gives the following, so I want 72:0. The other ports would also work.
//
//client 0: 'System' [type=kernel]
//    0 'Timer           '
//    1 'Announce        '
//client 62: 'Midi Through' [type=kernel]
//    0 'Midi Through Port-0'
//client 64: 'MPU-401 MIDI 0-0' [type=kernel]
//    0 'MPU-401 MIDI 0-0'
//client 72: 'Virtual Raw MIDI 1-0' [type=kernel]
//    0 'VirMIDI 1-0     '
//client 73: 'Virtual Raw MIDI 1-1' [type=kernel]
//    0 'VirMIDI 1-1     '
//client 74: 'Virtual Raw MIDI 1-2' [type=kernel]
//    0 'VirMIDI 1-2     '
//client 75: 'Virtual Raw MIDI 1-3' [type=kernel]
//    0 'VirMIDI 1-3     '
//Connect the Virtual Raw MIDI port to the Timidity port
//
//aconnect 72:0 128:0
//
//Find the device name of the Virtual Raw MIDI port. Since I went with the first Raw MIDI port, the device name I want is hw:1,0.
//
//amidi -l
//
//Device    Name
//hw:0,0    MPU-401 MIDI 0-0
//hw:1,0    Virtual Raw MIDI (16 subdevices)
//hw:1,1    Virtual Raw MIDI (16 subdevices)
//hw:1,2    Virtual Raw MIDI (16 subdevices)
//hw:1,3    Virtual Raw MIDI (16 subdevices)

            int err = snd_rawmidi_open(NULL, &m_prawmidi, driver, SND_RAWMIDI_SYNC);

            if(err)
            {

               fprintf(stderr,"snd_rawmidi_open %s failed: %d\n", driver, err);

            }
            else
            {

               snd_rawmidi_params_t * params = NULL;

               err = snd_rawmidi_params_malloc(&params);

               err = snd_rawmidi_params_current(m_prawmidi,	params);

               err = snd_rawmidi_params_set_avail_min(m_prawmidi, params, 768);

               err = snd_rawmidi_params_set_buffer_size(m_prawmidi, params, 1024);

               err = snd_rawmidi_params(m_prawmidi, params);

               snd_rawmidi_params_free(params);

            }


         }


         void midi_out::reset_all_controllers()
         {

            ::music::midi::message_out::reset_all_controllers();

         }


         midi_out::~midi_out()
         {

            if(m_prawmidi != NULL)
            {

               snd_rawmidi_close(m_prawmidi);

            }

         }


         void midi_out::note_on(int channel, unsigned char note, unsigned char volume)
         {

            byte message[3];

            message[0] = 0x90 | channel;

            message[1] = note;

            message[2] = volume;

            add_short_message(message, 3);

         }


         void midi_out::note_off(int channel, unsigned char note, unsigned char velocity)
         {

            byte message[3];

            message[0] = 0x80 | channel;

            message[1] = note;

            message[2] = velocity;

            add_short_message(message, 3);

         }


         void midi_out::program_change(int channel, unsigned char instrument)
         {

            byte message[2];

            message[0] = 0xC0 | channel;

            message[1] = instrument;

            add_short_message(message, 2);

         }


         void midi_out::step()
         {

            if(m_iWrite > 0)
            {

               snd_rawmidi_write(m_prawmidi, m_file.get_data(), m_file.get_size());

               //snd_rawmidi_drain(m_prawmidi);

               m_file.Truncate(0);

            }

            m_iWrite = 0;

         }


         void midi_out::start()
         {

         }


         void midi_out::add_short_message(byte * pmessage, int iSize)
         {

            m_file.write(pmessage, iSize);

            m_iWrite += iSize;

            //step();

         }


         void midi_out::control_change(int channel, unsigned char controller, unsigned char value)
         {

            byte message[3];

            message[0] = 0xB0 | channel;

            message[1] = controller;

            message[2] = value;

            add_short_message(message, 3);

         }


         void midi_out::pitch_bend(int channel, unsigned short value)
         {

            int c1 = (value & 0x7F);

            int c2 = ((value >> 7) & 0x7F);

            byte message[3];

            message[0] = 0xE0 | channel;

            message[1] = c1;

            message[2] = c2;

            add_short_message(message, 3);

         }


         bool midi_out::is_ok()
         {

            return m_prawmidi != NULL;

         }


      } // namespace alsa


   } // namespace midi


} // namespace music



