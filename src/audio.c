#include "audio.h"
#define MINIAUDIO_IMPLEMENTATION
 
// Fix cygwin gcc compiler
#ifdef __CYGWIN__
#define _WIN32
#define __STRICT_ANSI__
#define __LONG_MAX__ 0x7fffffff
#endif

#include <miniaudio.h>