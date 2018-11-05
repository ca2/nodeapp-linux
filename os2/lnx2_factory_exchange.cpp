#include "framework.h"


namespace win2
{


   factory_exchange::factory_exchange(::ca::application * papp) :
      ca(papp)
   {

      System.factory().creatable < ::win2::application         >  (System.type_info < ::cubebase::application > (), 1);

   }


   factory_exchange::~factory_exchange()
   {
   }

} // namespace win2


extern "C"
void ca2_factory_exchange(sp(::ca::application) papp)
{

   win2::factory_exchange factoryexchange(papp);

}

