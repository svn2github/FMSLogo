// This file contains stubs that should be implemented by the logo engine
// but were too annoying to include with #ifdef WX_PURE directives, so I've
// just provided blank implementations in a separate file.
//
// Each one of these is a bug that must by removed in order for the WX_PURE
// version to work.

#include "mainwind.h"

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
}

void ibmturt(bool draw)
{
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

void MyBeep(unsigned int frequency, unsigned int duration)
{
}

unsigned char Myinportb(short portid)
{
    return 0;
}

void Myoutportb(short portid, unsigned char value)
{
}

void Myoutport(short portid, short value)
{
}

short Myinport(short portid)
{
    return 0;
}

int Myingameport(short portid, short mask)
{
    return 0;
}

void uninitialize_windows()
{
}
