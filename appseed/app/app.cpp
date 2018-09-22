#define LINUX_COMMAND_LINE
#include "aura/aura/app/aura.inl"


//#include "app/appseed/core/core/core/core.h"
//#include "aura/aura/node/linux/linux.h"
//
//
//const char * g_psz_br_init_symbol_app = "";
//
//int32_t __lnx_main(int32_t argc, char * argv[]);
//
//namespace core
//{
//
//   namespace static_start
//   {
//
//      CLASS_DECL_CORE void gtk_init(int * c, char *** s);
//
//   } // namespace static_start
//
//} //namespace core
//
//int32_t main(int32_t argc, char * argv[])
//{
//
//   //::core::static_start::gtk_init(&argc, &argv);
//
//   if(!defer_core_init())
//      return -1;
//
//#ifdef MCHECK
//
//   mtrace();
//
//#endif
//
//
//   int iSizeOfObject = sizeof(object);
//
//   //void * p = aligned_memory_alloc(1024 * 1024 * 16);
//
//   //memory_free(p);
//
//   br_init_set_symbol(g_psz_br_init_symbol_app);
//
//   int iRet = __lnx_main(argc, argv);
//
//
//#ifdef MCHECK
//
//   muntrace();
//
//#endif
//
//
//   defer_core_term();
//
//   return iRet;
//
//}
//
////int xlib_error_handler(Display * d, XErrorEvent * e);
//
//
//int32_t __lnx_main(int32_t argc, char * argv[])
//{
//
//   ::core::system * psystem = new ::core::system();
//
//   c_xstart();
//
//   //XSetErrorHandler(xlib_error_handler);
//
//   psystem->::exception::translator::attach();
//
//   int32_t nReturnCode = 0;
//
//   ::command::command * pcommand  = new ::command::command;
//
//   if(argc > 0)
//   {
//
//      pcommand->m_strCommandLine     = argv[0];
//
//   }
//
//   bool bColon = false;
//
//   for(int32_t i = 1; i < argc; i++)
//   {
//
//      if(bColon || (bColon = (strcmp(argv[i], ":") == 0)))
//      {
//
//         pcommand->m_strCommandLine     += " ";
//
//         pcommand->m_strCommandLine     += argv[i];
//
//      }
//      else
//      {
//
//         pcommand->m_strCommandLine     += " \"";
//
//         pcommand->m_strCommandLine     += argv[i];
//
//         pcommand->m_strCommandLine     += "\"";
//
//      }
//
//   }
//
////   pcommand->m_nCmdShow              = SW_SHOW;
//
//   psystem->startup_command(pcommand);
//
//   bool bOk = true;
//
//   try
//   {
//
//      if(psystem->pre_run())
//      {
//
//         bOk = true;
//
//      }
//
//   }
//   catch(...)
//   {
//
//   }
//
//   try
//   {
//
//      if(!bOk)
//      {
//
//         if(psystem->m_error.get_exit_code() == 0)
//         {
//
//            return -1;
//
//         }
//
//         return psystem->m_error.get_exit_code();
//
//      }
//
//
//   }
//   catch(...)
//   {
//
//      return -1;
//
//   }
//
//   psystem->main();
//
//   try
//   {
//
//      psystem->remove_all_routes();
//
//   }
//   catch(...)
//   {
//
//   }
//
//
//   try
//   {
//
//      delete psystem;
//
//   }
//   catch(...)
//   {
//
//   }
//
//   psystem = NULL;
//
//   return nReturnCode;
//
//}
//
//
//
//int32_t ca2_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, const char * lpCmdLine, int32_t nCmdShow)
//{
//
//   try
//   {
//
////      _set_purecall_handler(_ca2_purecall);
//
//      ::core::system * psystem = new ::core::system();
//
//
//      //Sleep(30 * 1000);
//
//
//      ASSERT(hPrevInstance == NULL);
//
//      int32_t nReturnCode = 0;
//
//      ::command::command * pcommand  = new ::command::command;
//
//      //pcommand->m_hInstance             = hInstance;
//      //pcommand->m_hPrevInstance         = hPrevInstance;
//      pcommand->m_strCommandLine        = lpCmdLine;
//      //pcommand->m_nCmdShow              = nCmdShow;
//
//
//      psystem->startup_command(pcommand);
//
//
//      psystem->main();
//
//
//      try
//      {
//
//         delete psystem;
//
//      }
//      catch(...)
//      {
//
//      }
//
//      psystem = NULL;
//
//      defer_aura_term();
//
//      return nReturnCode;
//
//   }
//   catch(...)
//   {
//
//   }
//
//   return -1;
//
//}
