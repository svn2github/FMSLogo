// Copyright (C) 1995 by the Regents of the University of California
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

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include "activearea.h"
   #include "fmslogo.h"
   #include "logocore.h"
   #include "graphics.h"
   #include "eval.h"
   #include "error.h"
   #include "utils.h"
   #include "logodata.h"
   #include "init.h"
   #include "debugheap.h"
#endif

// Active area dimensions
int g_PrinterAreaXLow;
int g_PrinterAreaXHigh;
int g_PrinterAreaYLow;
int g_PrinterAreaYHigh;
int g_PrinterAreaPixels;

bool IsActiveAreaOneToOneWithScreen()
{
    bool isOneToOne;

    if ((g_PrinterAreaXLow  == -BitMapWidth  / 2) &&
        (g_PrinterAreaXHigh == +BitMapWidth  / 2) &&
        (g_PrinterAreaYLow  == -BitMapHeight / 2) &&
        (g_PrinterAreaYHigh == +BitMapHeight / 2))
    {
        isOneToOne = true;
    }
    else
    {
        isOneToOne = false;
    }

    return isOneToOne;
}

NODE *lsetactivearea(NODE *arg)
{
    NODE * args = int_vector_4_arg(arg);
    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    // All arguments are integers.
    const NODE * xLowNode  = car(args);
    const NODE * yLowNode  = car(cdr(args));
    const NODE * xHighNode = car(cdr(cdr(args)));
    const NODE * yHighNode = car(cdr(cdr(cdr(args))));

    const int xLow  = getint(xLowNode);
    const int yLow  = getint(yLowNode);
    const int xHigh = getint(xHighNode); 
    const int yHigh = getint(yHighNode); 

    if (xHigh <= xLow || yHigh <= yLow)
    {
        // TODO: make this a recoverable error
        err_logo(BAD_DATA_UNREC, args);
        return Unbound;
    }

    // Now that we have validated the input, we can commit to it
    g_PrinterAreaXLow  = xLow;
    g_PrinterAreaYLow  = yLow;
    g_PrinterAreaXHigh = xHigh; 
    g_PrinterAreaYHigh = yHigh; 

    SetConfigurationInt("Printer.XLow",   g_PrinterAreaXLow);
    SetConfigurationInt("Printer.XHigh",  g_PrinterAreaXHigh);
    SetConfigurationInt("Printer.YLow",   g_PrinterAreaYLow);
    SetConfigurationInt("Printer.YHigh",  g_PrinterAreaYHigh);

    return Unbound;
}

NODE *lactivearea(NODE *)
{
    return cons_list(
        make_intnode((FIXNUM) g_PrinterAreaXLow),
        make_intnode((FIXNUM) g_PrinterAreaYLow),
        make_intnode((FIXNUM) g_PrinterAreaXHigh),
        make_intnode((FIXNUM) g_PrinterAreaYHigh));
}
