#pragma once

/////////////////////////////////////////////////////////////////////////////
// Master version numbers

#define _AFX     1      // Microsoft Application Framework Classes
#ifndef _MFC_VER
#define _MFC_VER 0x0800 // Microsoft Foundation Classes version 8.00
#endif

/////////////////////////////////////////////////////////////////////////////
// turn off reference tracking for certain often used symbols

#ifndef _AFX_PORTABLE
#pragma component(browser, off, references, "ASSERT")
#pragma component(browser, off, references, "AfxAssertFailedLine")
#pragma component(browser, off, references, "__debug_break")
#pragma component(browser, off, references, "WINBOOL")
#pragma component(browser, off, references, "BYTE")
#pragma component(browser, off, references, "DECLSPEC_IMPORT")
#pragma component(browser, off, references, "DWORD")
#pragma component(browser, off, references, "FALSE")
#pragma component(browser, off, references, "FAR")
#pragma component(browser, off, references, "LPSTR")
#pragma component(browser, off, references, "LPTSTR")
#pragma component(browser, off, references, "LPCSTR")
#pragma component(browser, off, references, "LPCTSTR")
#pragma component(browser, off, references, "NULL")
#pragma component(browser, off, references, "PASCAL")
#pragma component(browser, off, references, "THIS_FILE")
#pragma component(browser, off, references, "TRUE")
#pragma component(browser, off, references, "UINT")
#pragma component(browser, off, references, "WINAPI")
#pragma component(browser, off, references, "WORD")
#endif  //!_AFX_PORTABLE

/////////////////////////////////////////////////////////////////////////////
// For target version (one of)
//   _CUSTOM   : for custom configurations (causes afxv_cfg.h to be included)
//
// Additional build options:
//  DEBUG              debug versions (full diagnostics)
//  _USRDLL             create regular DLL
//

#ifndef DEBUG
#ifndef _AFX_DISABLE_INLINES
//	#define _AFX_ENABLE_INLINES
#endif
#endif

#define _AFX_NO_NESTED_DERIVATION

/////////////////////////////////////////////////////////////////////////////
// special include files

#ifndef __INLINE
	#define __INLINE inline /*__forceinline*/
#endif

#include "v_w32.h"

// Include any non-Intel platform specific items
#ifndef _X86_
	#include "v_cpu.h"
#endif

#ifdef _X86_
	#define _AFX_MINREBUILD
#endif

#ifdef _CUSTOM
// Put any custom configuration items in afxv_cfg.h
	#include <afxv_cfg.h>
#endif

// setup default packing value
#ifndef _AFX_PACKING
	#define _AFX_PACKING    4   // default packs structs at 4 bytes
#endif


// Define this virtual key for use by status bar
#ifndef VK_KANA
#define VK_KANA             0x15
#endif

/////////////////////////////////////////////////////////////////////////////
// Special __debug_break: used to break into debugger at critical times

#ifndef __debug_break
#ifdef _AFX_NO_DEBUG_CRT
// by default, debug break is asm int32_t 3, or a call to DebugBreak, or nothing
#if defined(_M_IX86) && !defined(_AFX_PORTABLE)
#define __debug_break() _asm { int32_t 3 }
#else
#define __debug_break() DebugBreak()
#endif
#else
#define __debug_break() _CrtDbgBreak()
#endif
#endif

/*#ifndef DEBUG
#ifdef __debug_break
#undef __debug_break
#endif
#define __debug_break()
#endif  // DEBUG*/

/////////////////////////////////////////////////////////////////////////////
// Standard preprocessor symbols if not already defined
/////////////////////////////////////////////////////////////////////////////

// SIZE_T_MAX is used by the collection classes
#ifndef SIZE_T_MAX
	#define SIZE_T_MAX  UINT_MAX
#endif

// PASCAL is used for static member functions
#ifndef PASCAL
	#define PASCAL  __stdcall
#endif

// FASTcaLL is used for static member functions with little or no params
#ifndef FASTcaLL
	#define FASTcaLL __fastcall
#endif

// CDECL and EXPORT are defined in case WINDOWS.H doesn't
#ifndef CDECL
	#define CDECL __cdecl
#endif

#ifndef EXPORT
	#define EXPORT
#endif

// UNALIGNED is used for unaligned data access (in carchive mostly)
#if !defined(UNALIGNED)
#if defined(_M_IA64) || defined(_M_AMD64)
#define UNALIGNED __unaligned
#else
#define UNALIGNED
#endif
#endif

// __DEPREcaTED is used for functions that should no longer be used
#ifndef __DEPREcaTED
#ifdef _AFX_DISABLE_DEPREcaTED
	#define __DEPREcaTED(_Message)
#else
	#define __DEPREcaTED(_Message) __declspec(deprecated(_Message))
#endif
#endif

// _AFX_INSECURE_DEPREcaTE is used for deprecated, insecure functions.
#ifndef _AFX_INSECURE_DEPREcaTE
#ifdef _AFX_SECURE_NO_DEPREcaTE
#define _AFX_INSECURE_DEPREcaTE(_Message)
#else
#define _AFX_INSECURE_DEPREcaTE(_Message) __declspec(deprecated(_Message))
#endif // _AFX_SECURE_NO_DEPREcaTE
#endif // _AFX_INSECURE_DEPREcaTE

// _API is used on global public functions
#ifndef _API
	#define _API __stdcall
#endif

// _OLEAPI is used for some special OLE functions
#ifndef _OLEAPI
	#define _OLEAPI __stdcall
#endif

// __CDECL is used for rare functions taking variable arguments
#ifndef __CDECL
	#define __CDECL __cdecl
#endif

// __EXPORT is used for functions which need to be exported
#ifndef __EXPORT
	#define __EXPORT EXPORT
#endif

#ifndef __STATIC
	#define __STATIC extern
	#define __STATIC_DATA extern __declspec(selectany)
#endif

// The following macros are used to enable export/import

// for data
#ifndef __DATA_EXPORT
	#define __DATA_EXPORT __declspec(dllexport)
#endif
#ifndef __DATA_IMPORT
	#define __DATA_IMPORT __declspec(dllimport)
#endif

// for classes
#ifndef __CLASS_EXPORT
	#define __CLASS_EXPORT __declspec(dllexport)
#endif
#ifndef __CLASS_IMPORT
	#define __CLASS_IMPORT __declspec(dllimport)
#endif

// for global APIs
#ifndef __API_EXPORT
	#define __API_EXPORT __declspec(dllexport)
#endif
#ifndef __API_IMPORT
	#define __API_IMPORT __declspec(dllimport)
#endif

// This macro is used to reduce size requirements of some classes
#ifndef __ALWAYS_VTABLE
#ifndef __NOVTABLE
#if _MSC_VER >= 1100 && !defined(DEBUG)
#define __NOVTABLE __declspec(novtable)
#else
#define __NOVTABLE
#endif
#endif
#endif

// for global data that should be in COMDATs (packaged data)
#ifndef __COMDAT
#define __COMDAT __declspec(selectany)
#endif

// The following macros are used on data declarations/definitions
//  (they are redefined for extension DLLs and the shared MFC DLL)
#define __DATADEF
#define __API CLASS_DECL_LINUX

// used when building the "core" MFC80.DLL
#ifndef __CORE_DATA
	#define __CORE_DATA CLASS_DECL_LINUX
	#define __CORE_DATADEF
#endif

// used when building the MFC/OLE support MFCO80.DLL
#ifndef __OLE_DATA
	#define __OLE_DATA
	#define __OLE_DATADEF
#endif

// used when building the MFC/DB support MFCD80.DLL
#ifndef __DB_DATA
	#define __DB_DATA
	#define __DB_DATADEF
#endif

// used when building the MFC/NET support MFCN80.DLL
#ifndef __NET_DATA
	#define __NET_DATA
	#define __NET_DATADEF
#endif

// used when building extension DLLs
#ifndef __EXT_DATA
	#define __EXT_DATA
	#define __EXT_DATADEF
	#define __EXT_CLASS
	#define __EXT_API
#endif

// BASED_XXXX macros are provided for backward compatibility
#ifndef BASED_CODE
	#define BASED_CODE
#endif

#ifndef BASED_DEBUG
	#define BASED_DEBUG
#endif

#ifndef BASED_STACK
	#define BASED_STACK
#endif
/////////////////////////////////////////////////////////////////////////////


#include "v_cpu.h"











// ca2 API inline constructors (including compiler generated) can get deep
#pragma inline_depth(16)

#ifdef _AFX_DEVBUILD
	#define __IMPL_DATA __DATA_EXPORT
#else
	#define __IMPL_DATA CLASS_DECL_LINUX
#endif


// #define _AFX_NOFORCE_LIBS
#define _AFX_FULLTYPEINFO
#define VC_EXTRALEAN
#define NO_ANSIUNI_ONLY
#define _MFC_OVERRIDES_NEW

#define __COMDAT __declspec(selectany)

#include <winreg.h>
#include <winnls.h>
#include <new.h>
#include <eh.h>

#undef AfxWndProc


#define MAX_DWORD_PTR (0xffffffff)
