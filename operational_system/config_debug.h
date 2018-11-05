#pragma once



#define MEMDLEAK 0
#define STORE_LAST_BLOCK 0



//#define MCHECK



#ifdef MCHECK
#include <mcheck.h>
#define memory_alloc malloc
#define memory_realloc realloc
#define memory_free free
#endif






