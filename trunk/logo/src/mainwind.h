// -*- c++ -*-
// Copyright (C) 1995 by George Mills
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef __MAINWIND_H_
#define __MAINWIND_H_

#include <stdio.h>

#include "logocore.h"

class qlink
{
    friend class qlist;

    qlink *next;
    qlink *prev;
    void * e;

    qlink(void * a, qlink * n, qlink * p)
    {
        e = a;
        next = n;
        prev = p;
    }
};


class qlist
{
    qlink *last;
public:
    void insert(void * a);
    void * get();
    void zap();
    void clear();
    void remove(void * a);
    qlink * find(void * a);

    qlist()
    {
        last = NULL;
    }

    qlist(void * a)
    {
        last = new qlink(a, NULL, NULL);
        last->next = last;
        last->prev = last;
    }

    ~qlist()
    {
        clear();
    }
};

enum EVENTTYPE
{
    EVENTTYPE_Unknown,
    EVENTTYPE_Mouse,
    EVENTTYPE_Keyboard,
    EVENTTYPE_YieldFunction,
    EVENTTYPE_NoYieldFunction,
    EVENTTYPE_NetworkReceiveReady,
};

class callthing
{
private:
    // Hide the ctor. 
    // All events should be created with CreateEvent*().
    callthing() {};

public:
    // structured ways to create events
    static callthing * CreateKeyboardEvent(char * function, int key);
    static callthing * CreateMouseEvent(char * function, int x, int y);
    static callthing * CreateFunctionEvent(char * function);
    static callthing * CreateNoYieldFunctionEvent(char * function);
    static callthing * CreateNetworkReceiveReadyEvent(class CNetworkConnection * NetworkConnection, const char * packet);

    ~callthing();

    // CONSIDER: a union would make this struct smaller
    EVENTTYPE            kind;
    CNetworkConnection * networkconnection;
    char *               func;
    char *               networkpacket;
    int                  arg1;
    int                  arg2;
};

struct calllist : public qlist
{
    void insert(callthing *a)
    {
        qlist::insert(a);
    }
    callthing *get()
    {
        return (callthing *) qlist::get();
    }
};


// function declarations
extern NODE *leventcheck(NODE *args);
extern void emptyqueue(void);
extern void checkqueue(void);

extern void checkwindow(
    int *x,
    int *y,
    int *w,
    int *h
    );

ERR_TYPES
DumpBitmapFile(
    PCSTR Filename,
    int   MaxBitCount
    );

ERR_TYPES
WriteDIB(
    FILE* File,
    int   MaxBitCount
    );

ERR_TYPES
LoadBitmapFile(
    PCSTR,
    DWORD &,
    DWORD &
    );

bool
OpenDIB(
    FILE* File,
    DWORD &,
    DWORD &
    );

void
PaintToScreenWindow(
    HDC          PaintDC,
    const RECT & PaintRect
    );

// global variables
extern calllist calllists;

#endif // __MAINWIND_H_
