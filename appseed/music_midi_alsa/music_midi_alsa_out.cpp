#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace alsa
      {


      out::out(::aura::application * papp) :
         ::object(papp),
         ::music::midi::object(papp),
         ::music::midi::out(papp)
      {

         m_poseq = NULL;
//         m_numPorts = 0;

      }


      out::~out()
      {

         close();

      }


      ::multimedia::e_result out::open()
      {

         // Set up the ALSA sequencer client.
         if ( m_poseq != NULL )
         {

            return ::multimedia::result_success;

         }

         string clientName = "";

         int result = snd_seq_open(&m_poseq, "default", SND_SEQ_OPEN_DUPLEX, SND_SEQ_NONBLOCK);

         if ( result < 0 )
         {

            m_poseq = NULL;

            return ::multimedia::result_error;

         }
         else
         {

            // Set client name, use current name if given string is empty.
            if ( clientName != "" )
            {

               m_strClientName = clientName;

            }

            snd_seq_set_client_name( m_poseq, m_strClientName.c_str() );

         }

         // Increment port count.
         //m_numPorts++;

         return ::multimedia::result_success;

      }

      ::multimedia::e_result out::close()
      {

         if(m_poseq != NULL)
         {

            snd_seq_close(m_poseq);

            m_poseq = NULL;

         }

         return ::multimedia::result_success;

      }

      ::multimedia::e_result out::send_short_message(::music::midi::e_type etype, int iChannel, int iData1, int iData2)
      {

         //return midiOutShortMsg(m_hmidiout, MIDIMSG(((int) etype) >> 4, iChannel, iData1, iData2));
         return ::multimedia::result_success;

      }

      } // namespace alsa


   } // namespace midi


} // namespace music




