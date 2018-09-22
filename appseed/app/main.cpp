#include "aura/aura/app/aura.inl"





//#include "app/appseed/core/core/core/core.h"
//#include "aura/aura/node/linux/linux.h"
//
//const char * g_psz_br_init_symbol_app = "";
//extern char _binary_data_txt_start;
//extern char _binary_data_txt_end;
//
//int32_t __lnx_main2(int32_t argc, char * argv[], const char * pszAppApp);
//
//int32_t main(int32_t argc, char * argv[])
//{
//
//   if(!defer_core_init())
//      return -1;
//
//   char*  p1 = &_binary_data_txt_start;
//
//   char * p2 = &_binary_data_txt_end;
//
//   const char * pszAppApp = strndup(p1, p2 - p1);
//
//   br_init_set_symbol(g_psz_br_init_symbol_app);
//
//   int iRet = __lnx_main2(argc, argv, pszAppApp);
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
//
//}
//
//
//int xlib_error_handler(Display * d, XErrorEvent * e);
//
//
//
//
//int32_t __lnx_main2(int32_t argc, char * argv[], const char * pszAppApp)
//{
//
//   ::core::system * psystem = new ::core::system();
//
//   if(!XInitThreads())
//      return -1;
//
//   c_xstart();
//
//   XSetErrorHandler(xlib_error_handler);
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
//   bool bAppApp = false;
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
//         if(!bAppApp)
//         {
//
//            bAppApp = true;
//
//            if(pszAppApp != NULL)
//            {
//
//               pcommand->m_strCommandLine     += " app=";
//
//               pcommand->m_strCommandLine     += pszAppApp;
//
//            }
//
//         }
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
//   if(!bAppApp)
//   {
//
//      ASSERT(!bColon);
//
//      bAppApp = true;
//
//      if(pszAppApp != NULL)
//      {
//
//         pcommand->m_strCommandLine     += " : app=";
//
//         pcommand->m_strCommandLine     += pszAppApp;
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
//         if(psystem->m_iReturnCode == 0)
//         {
//
//            return -1;
//
//         }
//
//         return psystem->m_iReturnCode;
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
//   nReturnCode = psystem->main();
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
