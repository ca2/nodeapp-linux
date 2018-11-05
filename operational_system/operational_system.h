#pragma once



#include <typeinfo>


typedef std::type_info std_type_info;





#define stricmp strcasecmp

#define WINAPI


#ifndef __INLINE
	#define __INLINE inline /*__forceinline*/
#endif


// SIZE_T_MAX is used by the collection classes
#ifndef SIZE_T_MAX
	#define SIZE_T_MAX  UINT_MAX
#endif

// PASCAL is used for static member functions
#ifndef PASCAL
	#define PASCAL
#endif

// FASTcaLL is used for static member functions with little or no params
#ifndef FASTcaLL
	#define FASTcaLL
#endif

// CDECL and EXPORT are defined in case WINDOWS.H doesn't
#ifndef CDECL
	#define CDECL
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

// _API is used on global public functions
#ifndef _API
	#define _API
#endif

// __CDECL is used for rare functions taking variable arguments
#ifndef __CDECL
	#define __CDECL
#endif

// __EXPORT is used for functions which need to be exported
#ifndef __EXPORT
	#define __EXPORT
#endif

#ifndef __STATIC
	#define __STATIC extern
	#define __STATIC_DATA extern __declspec(selectany)
#endif

// for data
#ifndef __DATA_EXPORT
	#define __DATA_EXPORT
#endif
#ifndef __DATA_IMPORT
	#define __DATA_IMPORT
#endif

// for classes
#ifndef __CLASS_EXPORT
	#define __CLASS_EXPORT
#endif
#ifndef __CLASS_IMPORT
	#define __CLASS_IMPORT
#endif

// for global APIs
#ifndef __API_EXPORT
	#define __API_EXPORT
#endif
#ifndef __API_IMPORT
	#define __API_IMPORT
#endif

// This macro is used to reduce size requirements of some classes
#ifndef __ALWAYS_VTABLE
#define __NOVTABLE
#endif

// for global data that should be in COMDATs (packaged data)
#ifndef __COMDAT
//#define __COMDAT __declspec(selectany)
#define __COMDAT
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







#ifdef _AFX_DEVBUILD
	#define __IMPL_DATA __DATA_EXPORT
#else
	#define __IMPL_DATA CLASS_DECL_LINUX
#endif


#define _AFX_FULLTYPEINFO
#define VC_EXTRALEAN
#define NO_ANSIUNI_ONLY
#define _MFC_OVERRIDES_NEW


#define WINBOOL int



