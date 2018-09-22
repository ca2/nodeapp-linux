#pragma once


#define MIDIMSG(status,channel,data1,data2) ( (uint32_t)((status<<4) | channel | (data1<<8) | (data2<<16)) )


namespace music
{


   namespace midi
   {


      namespace alsa
      {

      //::multimedia::e_result ::music::translate(::music::e_result smfrc);


      }

   } // namespace midi_alsa


} // namespace music
