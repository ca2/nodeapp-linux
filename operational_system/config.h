#pragma once


//#define _REENTRANT
#define _THREAD_SAFE


#ifndef LINUX
#define LINUX
#endif


#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL

#define VARIADIC_TEMPLATE_FORMAT2


#ifdef _DEBUG
#define DEBUG
#endif


#define __WINESRC__


#define CLASS_DECL_EXPORT
#define CLASS_DECL_IMPORT
#define CLASS_DECL_THREAD __thread


#define __PLATFORM   "linux"



#ifndef OSBIT
#include "nodeapp/operational_system/bit.h"
#endif


#ifdef cplus
#define inline static
#endif

#define static_inline static inline



#ifdef __cplusplus

#define LOG_THIS_TAG (demangle(typeid(*this).name()))
#define LOG_MEMBER_PREFIX __FUNCTION__

#endif



#define AXIS_FREEIMAGE


#define FONT_SANS "FreeSans"
#define FONT_SERIF "FreeSerif"
#define FONT_MONO "Ubuntu Mono"
#define FONT_SANS_EX "Liberation Sans"
#define FONT_SERIF_EX "Liberation Serif"
#define FONT_SANS_FX "Ubuntu"
#define FONT_SERIF_FX "Bitstream Charter"




#define _strdup strdup


#define STR_NEWLINE "\n"

