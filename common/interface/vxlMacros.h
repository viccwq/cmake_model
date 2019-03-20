#ifndef _VXLMACROS_H_
#define _VXLMACROS_H_

#ifdef _WIN32
#include <Windows.h>
#elif defined __linux__
#define IN
#define OUT
typedef unsigned char BYTE;
#endif

#endif
