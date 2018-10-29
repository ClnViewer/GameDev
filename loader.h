#ifndef __LOADER_DLL_H__
#define __LOADER_DLL_H__

#include <windows.h>

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

#define __NELE(a) (sizeof(a) / sizeof(a[0]))

#endif
