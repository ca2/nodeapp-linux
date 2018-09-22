#include "app/appseed/axis/axis/axis/axis.h"
#include "aura/aura/node/linux/linux.h"


const char * g_psz_br_init_symbol_app = "";


int32_t __lnx_main(int32_t argc, char * argv[]);


int32_t main(int32_t argc, char * argv[])
{

   if(!defer_axis_init())
      return -1;

#ifdef MCHECK

   mtrace();

#endif


   int iSizeOfObject = sizeof(object);

   //void * p = aligned_memory_alloc(1024 * 1024 * 16);

   //memory_free(p);

   br_init_set_symbol(g_psz_br_init_symbol_app);

   int iRet = __lnx_main(argc, argv);


#ifdef MCHECK

   muntrace();

#endif


   defer_axis_term();

   return iRet;

}


int32_t __lnx_main(int32_t argc, char * argv[])
{

  // if(!defer_core_init())
    //  return -1;

   ::axis::system * psystem = new ::axis::system(NULL);

    psystem->::exception::translator::attach();

   int32_t nReturnCode = 0;

   ::command::command * pinitmaindata  = new ::command::command;

   pinitmaindata->m_hInstance             = NULL;

   pinitmaindata->m_hPrevInstance         = NULL;

   if(argc > 0)
   {

      pinitmaindata->m_vssCommandLine     = argv[0];

   }

   //pinitmaindata->m_vssCommandLine     = " : app=app-core/hellomultiver build_number=basis locale=_std schema=_std";

   bool bColon = false;

   for(int32_t i = 1; i < argc; i++)
   {

      if(bColon || (bColon = (strcmp(argv[i], ":") == 0)))
      {

         pinitmaindata->m_vssCommandLine     += " ";

         pinitmaindata->m_vssCommandLine     += argv[i];

      }
      else
      {

         pinitmaindata->m_vssCommandLine     += " \"";

         pinitmaindata->m_vssCommandLine     += argv[i];

         pinitmaindata->m_vssCommandLine     += "\"";

      }

   }

   pinitmaindata->m_nCmdShow              = SW_SHOW;

   psystem->init_main_data(pinitmaindata);

   bool bOk = true;

   try
   {

      if(psystem->pre_run())
      {

         bOk = true;

      }

   }
   catch(...)
   {

   }

   try
   {

      if(!bOk)
      {

         if(psystem->m_iReturnCode == 0)
         {

            return -1;

         }

         return psystem->m_iReturnCode;

      }


   }
   catch(...)
   {

      return -1;

   }

   nReturnCode = psystem->main();

   try
   {

      psystem->m_signala.remove_all();

   }
   catch(...)
   {

   }


   try
   {

      psystem->m_signala.remove_all();

   }
   catch(...)
   {

   }


   try
   {

      delete psystem;

   }
   catch(...)
   {

   }

   psystem = NULL;


   //defer_core_term();

   return nReturnCode;

}



int32_t ca2_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, const char * lpCmdLine, int32_t nCmdShow)
{

   try
   {

//      _set_purecall_handler(_ca2_purecall);

      ::axis::system * psystem = new ::axis::system(NULL);


      //Sleep(30 * 1000);


      ASSERT(hPrevInstance == NULL);

      int32_t nReturnCode = 0;

      ::command::command * pinitmaindata  = new ::command::command;

      pinitmaindata->m_hInstance             = hInstance;
      pinitmaindata->m_hPrevInstance         = hPrevInstance;
      pinitmaindata->m_vssCommandLine        = lpCmdLine;
      pinitmaindata->m_nCmdShow              = nCmdShow;


      psystem->init_main_data(pinitmaindata);


      nReturnCode = psystem->main();


      try
      {
         delete psystem;
      }
      catch(...)
      {
      }

      psystem = NULL;

      defer_axis_term();

      return nReturnCode;
   }
   catch(...)
   {
   }
   return -1;
}
