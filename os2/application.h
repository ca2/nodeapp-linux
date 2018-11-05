#pragma once


namespace win2
{


   class CLASS_DECL_lnx2 application :
      virtual public ::cubebase::application
   {
   public:


      application(::ca::application * papp);
      virtual ~application();

      virtual ::user::printer * get_printer(const char * pszDeviceName);

   };


} // namespace win2


