/*
*
*       Copyright (C) 1995 by the Regents of the University of California
*       Copyright (C) 1995 by George Mills
*
*      This program is free software; you can redistribute it and/or modify
*      it under the terms of the GNU General Public License as published by
*      the Free Software Foundation; either version 2 of the License, or
*      (at your option) any later version.
*
*      This program is distributed in the hope that it will be useful,
*      but WITHOUT ANY WARRANTY; without even the implied warranty of
*      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*      GNU General Public License for more details.
*
*      You should have received a copy of the GNU General Public License
*      along with this program; if not, write to the Free Software
*      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
*/
#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include "cursor.h"
   #include "init.h"
   #include "logocore.h"
   #include "debugheap.h"
#endif

#ifndef WX_PURE
HCURSOR hCursorWait;               // handle for hourglass cursor
HCURSOR hCursorArrow;              // handle for normal cursor

static HICON hCursorSave = 0; // handle for saved cursor
#endif

NODE *lsetcursorwait(NODE *)
{
#ifndef WX_PURE
    hCursorSave = ::SetCursor(hCursorWait);
#endif
    return Unbound;
}

NODE *lsetcursorarrow(NODE *)
{
#ifndef WX_PURE
    if (hCursorSave)
    {
        ::SetCursor(hCursorSave);
        hCursorSave = 0;
    }
    else
    {
        ::SetCursor(hCursorArrow);
    }
#endif

    return Unbound;
}

void init_cursors()
{
#ifndef WX_PURE
    // get an hourglass cursor
    hCursorWait  = LoadCursor(NULL, IDC_WAIT);
    hCursorArrow = LoadCursor(NULL, IDC_ARROW);
#endif
}
