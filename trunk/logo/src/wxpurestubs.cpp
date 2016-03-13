// This file contains stubs that should be implemented by the logo engine
// but were too annoying to include with #ifdef WX_PURE directives, so I've
// just provided blank implementations in a separate file.
//
// Each one of these is a bug that must by removed in order for the WX_PURE
// version to work.

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
    #include "mainwind.h"
#endif

void init_timers()
{
}

void uninitialize_timers()
{
}

void halt_all_timers()
{
}

void checkwindow(int *x, int *y, int *w, int *h)
{
    // -1 tells wxWidgets to use default size and position.
    *x = *y = *w = *h = -1;
}

ERR_TYPES DumpBitmapFile(const char * Filename, int MaxBitCount)
{
    return FILE_ERROR;
}

ERR_TYPES LoadBitmapFile( const char *, unsigned int &, unsigned int &)
{
    return FILE_ERROR;
}

bool CheckOnScreenControls()
{
    return true;
}

void uninitialize_windows()
{
}
