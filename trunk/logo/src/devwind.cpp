/*
*   devwind.cpp     program execution control module      dvb
*
*   Copyright (C) 1995 by the Regents of the University of California
*   Copyright (C) 1995 by George Mills
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software
*   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
*/
#include <windows.h>
#include <algorithm>

#include "devwind.h"
#include "argumentutils.h"
#include "logocore.h"
#include "graphics.h"
#include "graphwin.h"
#include "main.h"
#include "init.h"
#include "logodata.h"
#include "localizedstrings.h"
#include "lists.h"
#include "eval.h"
#include "mem.h"
#include "error.h"
#include "screenwindow.h"
#include "assembly.h"
#include "debugheap.h"

// global variables
KEYBOARDCAPTURE KeyboardCapture = KEYBOARDCAPTURE_Off; // Flag to signal Keyboard is enabled

int keyboard_value = 0;                // Value of Keyboard key
bool MouseCaptureIsEnabled = false;    // Flag to signal Mouse is enabled
int mouse_posx = 0;                    // Value of Mouse position x
int mouse_posy = 0;                    // Value of Mouse position y

char *mouse_lbuttondown = NULL;        // Mouse Left button down cb
char *mouse_lbuttonup = NULL;          // Mouse Right button up cb
char *mouse_rbuttondown = NULL;        // Mouse Left button down cb
char *mouse_rbuttonup = NULL;          // Mouse Right button up cb
char *mouse_mousemove = NULL;          // Mouse Move cb
char *keyboard_keydown = NULL;         // KeyBoard key down
char *keyboard_keyup = NULL;           // KeyBoard key up

static HANDLE ComId;
static bool   ComIsOpen = false;

// function definitions

NODE *lmouseon(NODE *args)
{
    // get args
    char lbuttondown[MAX_BUFFER_SIZE];
    cnv_strnode_string(lbuttondown, args);

    char lbuttonup[MAX_BUFFER_SIZE];
    cnv_strnode_string(lbuttonup, args = cdr(args));

    char rbuttondown[MAX_BUFFER_SIZE];
    cnv_strnode_string(rbuttondown, args = cdr(args));

    char rbuttonup[MAX_BUFFER_SIZE];
    cnv_strnode_string(rbuttonup, args = cdr(args));

    char mousemove[MAX_BUFFER_SIZE];
    cnv_strnode_string(mousemove, args = cdr(args));

    // most of mouse code is in DEFWNDPROC when this flag is on
    MouseCaptureIsEnabled = true;

    if (mouse_lbuttondown == NULL)
    {
        mouse_lbuttondown = (char *) malloc(MAX_BUFFER_SIZE);
        mouse_lbuttonup = (char *) malloc(MAX_BUFFER_SIZE);
        mouse_rbuttondown = (char *) malloc(MAX_BUFFER_SIZE);
        mouse_rbuttonup = (char *) malloc(MAX_BUFFER_SIZE);
        mouse_mousemove = (char *) malloc(MAX_BUFFER_SIZE);
    }

    // these really should be NODEs but not yet

    strcpy(mouse_lbuttondown, lbuttondown);
    strcpy(mouse_lbuttonup, lbuttonup);
    strcpy(mouse_rbuttondown, rbuttondown);
    strcpy(mouse_rbuttonup, rbuttonup);
    strcpy(mouse_mousemove, mousemove);

    return Unbound;
}

NODE *lmouseoff(NODE *)
{
    // tell handler not to do anything with messages for mouse
    MouseCaptureIsEnabled = false;

    return Unbound;
}

void mouse_uninit()
{
    free(mouse_lbuttondown);
    mouse_lbuttondown = NULL;
   
    free(mouse_lbuttonup);
    mouse_lbuttonup = NULL;
   
    free(mouse_rbuttondown);
    mouse_rbuttondown = NULL;
   
    free(mouse_rbuttonup);
    mouse_rbuttonup = NULL;
   
    free(mouse_mousemove);
    mouse_mousemove = NULL;
}

NODE *lkeyboardon(NODE *args)
{
    if (keyboard_keyup == NULL)
    {
        keyboard_keyup = (char *) malloc(MAX_BUFFER_SIZE);
        keyboard_keydown = (char *) malloc(MAX_BUFFER_SIZE);
    }

    // get args
    if (cdr(args) == NIL)
    {
        char keyboardup[MAX_BUFFER_SIZE];
        cnv_strnode_string(keyboardup, args);

        // most keyboard processing is done in DEFWNDPROC
        KeyboardCapture = KEYBOARDCAPTURE_KeyDown;

        strcpy(keyboard_keyup, keyboardup);
    }
    else
    {
        char keyboarddown[MAX_BUFFER_SIZE];
        cnv_strnode_string(keyboarddown, args);

        char keyboardup[MAX_BUFFER_SIZE];
        cnv_strnode_string(keyboardup, cdr(args));

        // most keyboard processing is done in DEFWNDPROC
        KeyboardCapture = KEYBOARDCAPTURE_KeyDownKeyUp;

        strcpy(keyboard_keydown, keyboarddown);
        strcpy(keyboard_keyup, keyboardup);
    }

    return Unbound;
}

NODE *lkeyboardoff(NODE *)
{
    // tell handler not to do anything with messages for keyboard
    KeyboardCapture = KEYBOARDCAPTURE_Off;

    return Unbound;
}

void keyboard_uninit()
{
    free(keyboard_keyup);
    keyboard_keyup = NULL;
   
    free(keyboard_keydown);
    keyboard_keydown = NULL;
}

NODE *lmousepos(NODE *)
{
    // return current mouse position
    return cons_list(
        make_intnode(  (mouse_posx + GetScreenHorizontalScrollPosition()) / the_zoom - xoffset),
        make_intnode(-((mouse_posy + GetScreenVerticalScrollPosition())   / the_zoom - yoffset)));
}

NODE *lkeyboardvalue(NODE *)
{
    // return current keyboard value
    return make_intnode(keyboard_value);
}

NODE *lportclose(NODE *)
{
    // if port closed output error else close it
    if (!ComIsOpen)
    {
        ShowErrorMessageAndStop(LOCALIZED_ERROR_CANTCLOSEPORT);
    }
    else
    {
        ComIsOpen = false;
        CloseHandle(ComId);
    }

    return Unbound;
}

NODE *lportopen(NODE *args)
{
    char comport[MAX_BUFFER_SIZE];
    cnv_strnode_string(comport, args);

    // if port open output error else open it
    if (ComIsOpen)
    {
        ShowErrorMessageAndStop(LOCALIZED_ERROR_PORTALREADYOPEN);
    }
    else
    {
        ComId = CreateFile(comport, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

        SetupComm(ComId, 4096, 4096);

        SetCommMask(ComId, 0);

        PurgeComm(ComId, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

        COMMTIMEOUTS CommTimeOuts;
        CommTimeOuts.ReadIntervalTimeout = MAXDWORD;
        CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
        CommTimeOuts.ReadTotalTimeoutConstant = 0;
        CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
        CommTimeOuts.WriteTotalTimeoutConstant = 0;
        SetCommTimeouts(ComId, &CommTimeOuts);

        DCB dcb;
        GetCommState(ComId, &dcb); // If we don't do this it won't work in Win95 !!!
        SetCommState(ComId, &dcb);

        if (ComId < 0)
        {
            ShowErrorMessageAndStop(LOCALIZED_ERROR_CANTOPENPORT);
        }
        else
        {
            ComIsOpen = true;
        }
    }

    return Unbound;
}

NODE *lportflush(NODE * /* args */)
{
    if (!ComIsOpen)
    {
        ShowErrorMessageAndStop(LOCALIZED_ERROR_PORTNOTOPEN);
    }
    else
    {
        int err = FlushFileBuffers(ComId);
        if (err == 0)
        {
            ShowErrorMessageAndStop(LOCALIZED_ERROR_CANTFLUSHPORT);
        }
    }

    return Unbound;
}

NODE *lportmode(NODE *args)
{
    char commode[MAX_BUFFER_SIZE];
    cnv_strnode_string(commode, args);

    // if closed output error else set mode
    if (!ComIsOpen)
    {
        ShowErrorMessageAndStop(LOCALIZED_ERROR_PORTNOTOPEN);
    }
    else
    {
        // build dcb, if no error continue
        DCB dcb;
        memset(&dcb, 0, sizeof(DCB));
        dcb.DCBlength = sizeof(DCB);
        int err = BuildCommDCB(commode, &dcb);

        if (err == 0)
        {
            ShowErrorMessageAndStop(LOCALIZED_ERROR_CANTDCBONPORT);
        }
        else
        {
            // now set Id in dcb and set the state
            DCB dcbold;

            GetCommState(ComId, &dcbold);

            dcbold.BaudRate = dcb.BaudRate;
            dcbold.ByteSize = dcb.ByteSize;
            dcbold.Parity   = dcb.Parity;
            dcbold.StopBits = dcb.StopBits;

            err = SetCommState(ComId, &dcbold);
            if (err == 0)
            {
                ShowErrorMessageAndStop(LOCALIZED_ERROR_CANTSETPORT);
            }
        }
    }

    return Unbound;
}

static
int min3(int a, int b, int c)
{
    return std::min(std::min(a, b), c);
}

NODE *lportwritearray(NODE *args)
{
    NODE * val = nonnegative_int_arg(args);
    NODE * obj = cadr(args);

    while ((obj == NIL || obj == Null_Word) && NOT_THROWING)
    {
        setcar(cdr(args), err_logo(BAD_DATA, obj));
        obj = cadr(args);
    }

    if (NOT_THROWING)
    {
        if (nodetype(obj) == ARRAY)
        {

            // if closed the error, else continue
            if (!ComIsOpen)
            {
                ShowErrorMessageAndStop(LOCALIZED_ERROR_PORTNOTOPEN);
            }
            else
            {
                // get min of max array and the array
                char txbuffer[MAX_BUFFER_SIZE];
                DWORD count = min3(getint(val), getarrdim(obj), sizeof(txbuffer));

                // fill buffer with elements of the array
                for (int i = 0; i < count; i++)
                {
                    NODE * item = litem(cons_list(make_intnode(i + getarrorg(obj)), obj));
                    txbuffer[i] = getint(cnv_node_to_numnode(item));
                }

                // now write buffer
                DWORD errorCode;
                ClearCommError(ComId, &errorCode, NULL);

                DWORD actual;
                int status = WriteFile(ComId, txbuffer, count, &actual, NULL);

                // if problem GetComError will Put up Message box
                if (status == 0)
                {
                    ClearCommError(ComId, &errorCode, NULL);
                }

                // return byte count sent
                return make_intnode(status);
            }
        }
        else
        {
            ShowMessageAndStop(
                LOCALIZED_ERROR, 
                LOCALIZED_ERROR_FIRSTINPUTNOTANARRY);
        }
    }

    return Unbound;
}

NODE *lportreadarray(NODE *args)
{
    NODE * val = nonnegative_int_arg(args);
    NODE * obj = cadr(args);

    while ((obj == NIL || obj == Null_Word) && NOT_THROWING)
    {
        setcar(cdr(args), err_logo(BAD_DATA, obj));
        obj = cadr(args);
    }

    if (NOT_THROWING)
    {
        if (nodetype(obj) == ARRAY)
        {

            // if closed the error, else continue

            if (!ComIsOpen)
            {
                ShowErrorMessageAndStop(LOCALIZED_ERROR_PORTNOTOPEN);
            }
            else
            {
                // don't overflow buffer
                char rxbuffer[MAX_BUFFER_SIZE];
                int count = min3(getarrdim(obj), getint(val), sizeof(rxbuffer));

                // Clear any errors
                DWORD errorCode;
                COMSTAT Stat;
                ClearCommError(ComId, &errorCode, &Stat);

                // do the read (let it fail if nothing is there, it should not hang)
                DWORD actual;
                ReadFile(ComId, rxbuffer, count, &actual, NULL);

                // if nothing there then return 0 count
                if (actual == 0) 
                {
                    return make_intnode(0);
                }

                count = actual;

                // now fill in the array
                for (int i = 0; i < count; i++)
                {
                    lsetitem(
                        cons_list(
                            make_intnode(i + getarrorg(obj)),
                            obj,
                            make_intnode(rxbuffer[i])));
                }

                // return actual transfered
                return make_intnode(count);
            }
        }
    }

    return make_intnode(0);
}

NODE *lportwritechar(NODE *args)
{
    // get arg
    char txchar[1];
    txchar[0] = getint(nonnegative_int_arg(args));

    // if not open output error, else continue

    if (!ComIsOpen)
    {
        ShowErrorMessageAndStop(LOCALIZED_ERROR_PORTNOTOPEN);
    }
    else
    {
        // write the 1 byte
        DWORD status;
        if (!WriteFile(ComId, txchar, 1, &status, NULL))
        {
            status = -1;
        }

        // if problem GetComError will Put up Message box
        if (status != 1)
        {
            DWORD errorCode;
            ClearCommError(ComId, &errorCode, NULL);
        }

        // return byte count sent
        return make_intnode(status);
    }

    return Unbound;
}

NODE *lportreadchar(NODE *)
{
    // if closed output error, else continue
    if (!ComIsOpen)
    {
        ShowErrorMessageAndStop(LOCALIZED_ERROR_PORTNOTOPEN);
    }
    else
    {
        // Clear Comm Error in case last operation failed otherwise we won't get anything
        DWORD errorCode;
        ClearCommError(ComId, &errorCode, NULL);

        // ReadFile will return immediately even if there is nothing to read
        char rxchar[64];
        DWORD actual;
        ReadFile(ComId, rxchar, 1, &actual, NULL);

        // if something was read then return it else return -1
        if (actual == 1)
        {
            return make_intnode(rxchar[0]);
        }
        else
        {
            return make_intnode(-1);
        }
    }

    return Unbound;
}

NODE *loutportb(NODE *args)
{
    // get args
    int portid = getint(nonnegative_int_arg(args));
    int value = getint(nonnegative_int_arg(cdr(args)));

    Myoutportb(portid, value);

    return Unbound;
}

NODE *linportb(NODE *args)
{
    int portid = getint(nonnegative_int_arg(args));
    int value = Myinportb(portid);

    return make_intnode(value);
}

NODE *loutport(NODE *args)
{
    // get args
    int portid = getint(nonnegative_int_arg(args));
    int value = getint(nonnegative_int_arg(cdr(args)));

    Myoutport(portid, value);

    return Unbound;
}

NODE *linport(NODE *args)
{
    int portid = getint(nonnegative_int_arg(args));
    int value = Myinport(portid);

    return make_intnode(value);
}

NODE *lingameport(NODE *args)
{
    int portid;

    int mask = getint(nonnegative_int_arg(args));

    if (cdr(args) == NIL)
    {
        portid = 0x201;
    }
    else
    {
        portid = getint(nonnegative_int_arg(cdr(args)));
    }

    int value = Myingameport(portid, mask);

    return make_intnode(value);
}
