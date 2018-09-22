#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace alsa
      {


         factory_exchange::factory_exchange(::aura::application * papp) :
            object(papp)
         {

            System.factory().cloneable_large < sequence               >  (System.type_info < ::music::midi::sequence                  > ());
            System.factory().cloneable_large < file              >  (System.type_info < ::music::midi::file::buffer                 > ());
            System.factory().cloneable_large < sequence_thread              >  (System.type_info < ::music::midi::sequence_thread                 > ());
            System.factory().cloneable_large < player::player              >  (System.type_info < ::music::midi::player::player                 > ());
   //         System.factory().cloneable_large < ::music::midi_alsa::player:: player_interface              >  (System.type_info < ::music::midi::player::player_interface                 > ());
            System.factory().cloneable_large < midi              >  (System.type_info < ::music::midi::midi                 > ());

         }


         factory_exchange::~factory_exchange()
         {
         }


      } // namespace alsa


   } // namespace midi


} // namespace music


extern "C"
void ca2_factory_exchange(::aura::application * papp)
{

   ::music::midi::alsa::factory_exchange factoryexchange(papp);

}









