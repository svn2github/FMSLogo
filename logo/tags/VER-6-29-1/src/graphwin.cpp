/*
 *  Copyright (C) 1995 by the Regents of the University of California
 *  Copyright (C) 1995 by George Mills
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <math.h>
#include <windows.h>
#include <htmlhelp.h>

#include "activearea.h"
#include "graphwin.h"
#include "mainwind.h"

#include "devwind.h"
#include "cursor.h"
#include "status.h"

#include "utils.h"
#include "stringprintednode.h"
#include "appendablelist.h"
#include "mem.h"
#include "logomath.h"
#include "dib.h"
#include "logodata.h"
#include "vector.h"
#include "parse.h"
#include "error.h"
#include "main.h"
#include "wrksp.h"
#include "lists.h"
#include "eval.h"
#include "init.h"
#include "coms.h"
#include "unix.h"
#include "const.h"
#include "screenwindow.h"
#include "startup.h"
#include "debugheap.h"

#include "localizedstrings.h"

struct CUTMAP
{
    HBITMAP MemoryBitMap;  // Used to store the bitmap
    int     Height;        // current cut height
    int     Width;         // current cut width
    bool    IsValid;       // flag to signal something in cut buffer
};


#define X_ROTATED(X, Y, COSINE, SINE) ((X)*(COSINE) + (Y)*(SINE))
#define Y_ROTATED(X, Y, COSINE, SINE) ((Y)*(COSINE) - (X)*(SINE))

extern bool bIndexMode;

extern int gbmBmpToGif(const char *BmpName, const char *GifName);
extern int gbmGifToBmp(const char *GifName, const char *BmpName);

// global variables
int iDelay;
int bAppendMode;
int iLoop;
int iTrans;

RECT FullRect;                         // rectangle of the full bitmap

LOGFONT FontRec;                       // record for label font

LOGPEN g_LogicalNormalPen;             // Handle to "Normal" logical Pen
HPEN   g_NormalPen;                    // Handle to "Normal" Pen

LOGPEN g_LogicalErasePen;              // Handle to "Erase" logical Pen
HPEN   g_ErasePen;                     // Handle to "Erase" Pen

LOGBRUSH FloodBrush;                   // Handle to the "floodfill" brush
LOGBRUSH ScreenBrush;                  // Handle to the "screen" background brush

bool EnablePalette;                    // Flag to signal 256 color mode with palette
HPALETTE OldPalette;                   // place holder for windows resources
HPALETTE ThePalette;                   // Handle for the single color palette

int xoffset = 0;                       // Used to go from logo to windows coords x
int yoffset = 0;                       // Used to go from logo to windows coords y

int BaseUnitsx = 0;                    // X Units Windows uses to for units in dialog
int BaseUnitsy = 0;                    // Y Units Windows uses to for units in dialog

bool IsTimeToExit = false;             // Flag to signal it's time to exit
bool IsTimeToPause = false;            // UCBLOGO? pause flag
bool IsTimeToHalt = false;             // UCBLOGO? halt flag
bool zoom_flag = false;                // flag to signal in zoomed state
FLONUM the_zoom = 1.0;                 // current zoom factor

HBITMAP MemoryBitMap;                  // Backing store bitmap

PLOGPALETTE MyLogPalette;              // Handle for the single logical color palette

// Flag to signal that focus should go to the commander's editbox.  This is
// initially set to true in TMyCommandWindow::DoButtonExecute(), but can
// be overridden and set to false by some commands, such as EDIT and SETFOCUS.
// If the flag is still true after the instruction has finished executing, then
// focus is given to the commander's editbox.
bool GiveFocusToEditbox = false;

typedef HWND ( __stdcall *HTMLHELPFUNC)(HWND, PCSTR, UINT, DWORD);
static HTMLHELPFUNC g_HtmlHelpFunc;
static HMODULE      g_HtmlHelpLib;

static CUTMAP * g_SelectedBitmap;
static CUTMAP * g_Bitmaps;
static int      g_BitmapsLimit;

static PENSTATE g_PenState;              // The state of the current pen (color, mode, etc.)
static long     MaxColors = 0;           // The maximum # of colors available

struct font_find_t
{
    const char *fontname;
    bool        found;
};

struct LINE3D
{
    VECTOR from;
    VECTOR to;
};

static const LINE3D turtle_vertices[4] =
{
    {{-16.0, 0.0, 0.0}, { 16.0,  0.0, 0.0}},
    {{ 16.0, 0.0, 0.0}, {  0.0, 16.0, 0.0}},
    {{  0.0,16.0, 0.0}, {-16.0,  0.0, 0.0}},
    {{  8.0, 0.0, 0.0}, {  8.0,  8.0, 0.0}},
};

static DWORD g_BitMode = SRCCOPY;

#ifdef NDEBUG
#  define ASSERT_TURTLE_INVARIANT
#else
#  define ASSERT_TURTLE_INVARIANT CTurtlesInvariant invariant

class CTurtlesInvariant
{
public:

    CTurtlesInvariant()
    {
        AssertInvariant();
    }

    ~CTurtlesInvariant()
    {
        AssertInvariant();
    }

    void
    AssertInvariant(
        void
        )
    {
        // make sure g_MaxTurtle is within range
        assert(0 <= g_MaxTurtle);
        assert(g_MaxTurtle < g_TurtlesLimit);

        // we can never have less than one turtle
        assert(0 < g_TurtlesLimit);

        // g_SelectedTurtle is in either g_Turtles or g_SpecialTurtles
        assert(
            (g_Turtles <= g_SelectedTurtle && g_SelectedTurtle <= &g_Turtles[g_MaxTurtle]) || 
            (g_SpecialTurtles <= g_SelectedTurtle && g_SelectedTurtle < &g_SpecialTurtles[TOTAL_SPECIAL_TURTLES]));

        for (volatile int i = 0; i <= g_MaxTurtle; i++)
        {
            // test that all values are valid (none are uninitialized)
            assert(
                g_Turtles[i].IsShown == true ||
                g_Turtles[i].IsShown == false);

            assert(
                g_Turtles[i].IsPenUp == true ||
                g_Turtles[i].IsPenUp == false);

            assert(
                g_Turtles[i].IsSpecial == true ||
                g_Turtles[i].IsSpecial == false);

            assert(
                g_Turtles[i].BitmapRasterMode == 0           ||
                g_Turtles[i].BitmapRasterMode == SRCCOPY     ||
                g_Turtles[i].BitmapRasterMode == SRCPAINT    ||
                g_Turtles[i].BitmapRasterMode == SRCAND      ||
                g_Turtles[i].BitmapRasterMode == SRCINVERT   ||
                g_Turtles[i].BitmapRasterMode == SRCERASE    ||
                g_Turtles[i].BitmapRasterMode == NOTSRCCOPY  ||
                g_Turtles[i].BitmapRasterMode == NOTSRCERASE ||
                g_Turtles[i].BitmapRasterMode == MERGEPAINT  ||
                g_Turtles[i].BitmapRasterMode == DSTINVERT);

            if (g_Turtles[i].BitmapRasterMode != 0)
            {
                // make sure that the bitmap exists.
                assert(i < g_BitmapsLimit);
            }
        }

        // g_SelectedBitmap is within the g_Bitmaps array
        assert(g_Bitmaps <= g_SelectedBitmap);
        assert(g_SelectedBitmap < g_Bitmaps + g_BitmapsLimit);

        assert(0 < g_BitmapsLimit);

        assert(
            g_BitMode == SRCCOPY     ||
            g_BitMode == SRCPAINT    ||
            g_BitMode == SRCAND      ||
            g_BitMode == SRCINVERT   ||
            g_BitMode == SRCERASE    ||
            g_BitMode == NOTSRCCOPY  ||
            g_BitMode == NOTSRCERASE ||
            g_BitMode == MERGEPAINT  ||
            g_BitMode == DSTINVERT);
    }
};

#endif

static
bool
ClipboardIsSelectedBitmap()
{
    return g_SelectedBitmap == &g_Bitmaps[0];
}

static
void
GrowBitmapsArray(int NewSize)
{
    // assert that the array needs to grow
    assert(NewSize > g_BitmapsLimit);

    if (NewSize > (size_t)-1 / sizeof(*g_Bitmaps))
    {
        // this allocation would result in an integer overflow
        err_logo(OUT_OF_MEM, NIL);
        return;
    }

    CUTMAP * newBitmaps = (CUTMAP*) realloc(g_Bitmaps, NewSize * sizeof(*g_Bitmaps));
    if (newBitmaps == NULL)
    {
        // could not grow the turtles array to hold turtleId
        err_logo(OUT_OF_MEM, NIL);
        return;
    }

    // initialize the newly allocated bitmap structures
    for (int i = g_BitmapsLimit; i < NewSize; i++)
    {
        newBitmaps[i].MemoryBitMap = NULL;
        newBitmaps[i].Width        = 0;
        newBitmaps[i].Height       = 0;
        newBitmaps[i].IsValid      = false;
    }

    g_Bitmaps      = newBitmaps;
    g_BitmapsLimit = NewSize;
}

static
void
UpdatePen(
    LOGPEN   & LogicalPen,
    HPEN     & Pen,
    int        Width,
    COLORREF   Color
    )
{
    LogicalPen.lopnStyle   = PS_INSIDEFRAME;
    LogicalPen.lopnWidth.x = Width;
    LogicalPen.lopnColor   = Color;

    if (Pen)
    {
        DeleteObject(Pen);
    }
    Pen = CreatePenIndirect(&LogicalPen);
}

void
UpdateErasePen(
    int      Width,
    COLORREF Color
    )
{
    UpdatePen(g_LogicalErasePen, g_ErasePen, Width, Color);
}

void
UpdateNormalPen(
    int      Width,
    COLORREF Color
    )
{
    UpdatePen(g_LogicalNormalPen, g_NormalPen, Width, Color);
}

ERR_TYPES
gifsave_helper(
    const char *GifFileName,
    int         iDelay_,
    int         bAppendMode_,
    int         iLoop_,
    int         iTrans_,
    int         iMaxColorDepth
    )
{
    iDelay      = iDelay_;
    bAppendMode = bAppendMode_;
    iLoop       = iLoop_;
    iTrans      = iTrans_;

    ERR_TYPES status = DumpBitmapFile(TempBmpName, iMaxColorDepth);
    if (status != SUCCESS)
    {
        // an error occured.
        return status;
    }

    lsetcursorwait(NIL);
    if (gbmBmpToGif(TempBmpName, GifFileName) != 0)
    {
        status = IMAGE_GIF_SAVE_FAILED;
    }
    lsetcursorarrow(NIL);
    remove(TempBmpName);

    return status;
}

PENSTATE & GetPenStateForSelectedTurtle()
{
    if (g_SelectedTurtle->HasOwnPenState)
    {
        return g_SelectedTurtle->PenState;
    }

    // the current turtle uses the global pen state
    return g_PenState;
}


/* adds color to palette */
COLORREF LoadColor(int dpenr, int dpeng, int dpenb)
{
    /* convert to color and find nearest match */
    COLORREF color = PALETTERGB(dpenr, dpeng, dpenb);
    int Index = GetNearestPaletteIndex(ThePalette, color);

    /* if not exact and room for more then allocate it */
    if ((PALETTERGB(
             MyLogPalette->palPalEntry[Index].peRed,
             MyLogPalette->palPalEntry[Index].peGreen,
             MyLogPalette->palPalEntry[Index].peBlue) != color) && 
        (MyLogPalette->palNumEntries < (MaxColors - 1)))
    {

        /* Why do check again? */
        if (MyLogPalette->palNumEntries < 255)
        {

            // kill old palette
            DeleteObject(ThePalette);

            MyLogPalette->palPalEntry[MyLogPalette->palNumEntries].peRed = dpenr;
            MyLogPalette->palPalEntry[MyLogPalette->palNumEntries].peGreen = dpeng;
            MyLogPalette->palPalEntry[MyLogPalette->palNumEntries].peBlue = dpenb;
            MyLogPalette->palPalEntry[MyLogPalette->palNumEntries].peFlags = 0;
            MyLogPalette->palNumEntries++;

            // if status window then update palette usage
            update_status_paletteuse();

            // make new palette with added color
            ThePalette = CreatePalette(MyLogPalette);
        }
    }

    /* return color new, matched or close */
    return color;
}

// returns the dimensions of the working area, that is
// the size of the desktop without the task bar.
void GetWorkingAreaDimensions(int & Width, int & Height)
{
    RECT workingArea;

    SystemParametersInfo(SPI_GETWORKAREA, 0, &workingArea, 0);
    Width  = workingArea.right  - workingArea.left;
    Height = workingArea.bottom - workingArea.top;
}

NODE *lgifsave(NODE *args)
{
    // same as BITMAP-SAVE but gets file name from logo command
    CStringPrintedNode gifFileName(car(args));

    // setup default values for the optional inputs
    int  iDelay = -1;
    bool bAppendMode = false;
    int  iLoop = -1;
    int  iMaxColorDepth = 8;
    int  iTrans = -1;

    if (cdr(args) != NIL)
    {
        NODE *val1 = integer_arg(cdr(args));
        if (NOT_THROWING)
        {
            iDelay = getint(val1);
            if (cdr(cdr(args)) != NIL)
            {
                bAppendMode = boolean_arg(cdr(cdr(args)));
                if (NOT_THROWING)
                {
                    if (cdr(cdr(cdr(args))) != NIL)
                    {
                        NODE *val3 = integer_arg(cdr(cdr(cdr(args))));
                        if (NOT_THROWING)
                        {
                            iLoop = getint(val3);
                            if (cdr(cdr(cdr(cdr(args)))) != NIL)
                            {
                                NODE *val4 = integer_arg(cdr(cdr(cdr(cdr(args)))));
                                if (NOT_THROWING)
                                {
                                    iMaxColorDepth = getint(val4);
                                    if ((iMaxColorDepth != 4) && (iMaxColorDepth != 1))
                                    {
                                        iMaxColorDepth = 8;
                                    }

                                    if (cdr(cdr(cdr(cdr(cdr(args))))) != NIL)
                                    {
                                        iTrans = GetColorArgument(cdr(cdr(cdr(cdr(cdr(args))))));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (NOT_THROWING)
    {
        ERR_TYPES status = gifsave_helper(
            gifFileName,
            iDelay,
            bAppendMode,
            iLoop,
            iTrans,
            iMaxColorDepth);
        if (status != SUCCESS)
        {
            err_logo(status, NIL);
        }
    }

    return Unbound;
}

NODE *lbitsave(NODE *args)
{
    // same as BITMAP-SAVE but gets file name from logo instruction
    CStringPrintedNode bmpFileName(car(args));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    int iMaxBitCount = 32;
    if (cdr(args) != NIL)
    {
        NODE *val1 = integer_arg(cdr(args));
        if (stopping_flag == THROWING)
        {
            return Unbound;
        }
        iMaxBitCount = getint(val1);
    }

    ERR_TYPES status = DumpBitmapFile(bmpFileName, iMaxBitCount);
    if (status != SUCCESS)
    {
        err_logo(status, NIL);
        return Unbound;
    }

    return Unbound;
}

ERR_TYPES
gifload_helper(
    const char   * GifFileName,
    unsigned int & dwPixelWidth,
    unsigned int & dwPixelHeight
    )
{
    // convert the GIF to a DIB
    lsetcursorwait(NIL);
    int rval = gbmGifToBmp(GifFileName, TempBmpName);
    lsetcursorarrow(NIL);

    if (rval != 0)
    {
        return IMAGE_GIF_LOAD_FAILED;
    }

    // load the bitmap
    ERR_TYPES status = LoadBitmapFile(
        TempBmpName,
        dwPixelWidth,
        dwPixelHeight);

    // cleanup
    remove(TempBmpName);
    return status;
}

NODE *lgifload(NODE *arg)
{
    CStringPrintedNode gifFileName(car(arg));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    unsigned int pixelWidth = 1;
    unsigned int pixelHeight = 1;
    ERR_TYPES status = gifload_helper(gifFileName, pixelWidth, pixelHeight);
    if (status != SUCCESS)
    {
        err_logo(status, NIL);
        return Unbound;
    }

    return Unbound;
}

NODE *lgifsize(NODE *args)
{
    CStringPrintedNode gifFileName(car(args));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    unsigned int pixelWidth = 0;
    unsigned int pixelHeight = 0;
    ERR_TYPES status = gifload_helper(gifFileName, pixelWidth, pixelHeight);
    if (status != SUCCESS)
    {
        err_logo(status, NIL);
        return Unbound;
    }

    return cons_list(
        make_intnode((FIXNUM) pixelWidth),
        make_intnode((FIXNUM) pixelHeight));
}

NODE *lbitload(NODE *arg)
{
    // same as BITMAP-LOAD except callable from logo command
    CStringPrintedNode bitmapFileName(car(arg));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }


    unsigned int pixelWidth = 1;
    unsigned int pixelHeight = 1;
    ERR_TYPES status = LoadBitmapFile(
        bitmapFileName,
        pixelWidth,
        pixelHeight);
    if (status != SUCCESS)
    {
        err_logo(status, NIL);
        return Unbound;
    }

    return Unbound;
}

NODE *lbitloadsize(NODE *arg)
{
    // same as BITMAP-LOAD except callable from logo command
    CStringPrintedNode bitmapFileName(car(arg));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    unsigned int pixelWidth = 0;
    unsigned int pixelHeight = 0;
    ERR_TYPES status = LoadBitmapFile(bitmapFileName, pixelWidth, pixelHeight);
    if (status != SUCCESS)
    {
        err_logo(status, NIL);
        return Unbound;
    }

    return cons_list(
        make_intnode((FIXNUM) pixelWidth),
        make_intnode((FIXNUM) pixelHeight));
}

NODE *lbitsize(NODE *)
{
    BITMAP temp;
    temp.bmWidth  = 0;
    temp.bmHeight = 0;

    if (ClipboardIsSelectedBitmap())
    {
        // The selected bitmap is whatever is on the clipboard
        ::OpenClipboard(GetMainWindow());

        // Try a DIB first
        HANDLE hDIB = (HBITMAP) ::GetClipboardData(CF_DIB);

        // If it exists get the size
        if (hDIB)
        {
            LPBITMAPINFOHEADER lpDIBHdr = (LPBITMAPINFOHEADER) GlobalLock(hDIB);

            if (lpDIBHdr)
            {
                temp.bmWidth  = lpDIBHdr->biWidth;
                temp.bmHeight = lpDIBHdr->biHeight;
                GlobalUnlock(hDIB);
            }
        }
        else
        {
            // else try for a bitmap
            HBITMAP hMemoryBitMap = (HBITMAP) ::GetClipboardData(CF_BITMAP);

            // If it exists get the size
            if (hMemoryBitMap)
            {
                ::GetObject(hMemoryBitMap, sizeof(BITMAP), (LPSTR) &temp);
            }
        }

        // we have everything we need
        ::CloseClipboard();
    }
    else
    {
        // if we have something fetch its size
        if (g_SelectedBitmap->IsValid)
        {
            ::GetObject(
                g_SelectedBitmap->MemoryBitMap,
                sizeof(BITMAP),
                (LPSTR)&temp);
        }
    }

    return cons_list(
        make_intnode((FIXNUM) temp.bmWidth),
        make_intnode((FIXNUM) temp.bmHeight));
}

// Fills TurtlePoint with the location of the current
// turtle on the 2D screen (before zooming and scrolling)
//
// returns true on success.
// returns false on error.
static
bool
WorldCoordinateToScreenCoordinate(
    const VECTOR &  TurtleWorldPosition,
    POINT &         TurtleScreenPosition
    )
{
    if (current_mode == perspectivemode)
    {
        VECTOR from3d;

        from3d.x = TurtleWorldPosition.x / WorldWidth;
        from3d.y = TurtleWorldPosition.y / WorldHeight;
        from3d.z = TurtleWorldPosition.z / WorldDepth;

        if (!ThreeD.TransformPoint(from3d, TurtleScreenPosition))
        {
            return false;
        }
    }
    else
    {
        TurtleScreenPosition.x = g_round(TurtleWorldPosition.x);
        TurtleScreenPosition.y = g_round(TurtleWorldPosition.y);
    }

    return true;
}


// Invalidates a rectangle on the screen.
// It adjusts for the zoom factor and scroll position.
static void InvalidateRectangleOnScreen(const RECT & ScreenRectangle)
{
    RECT adjustedRectangle;

    // Expand the bounding box a little to make sure that it covers everything
    adjustedRectangle.left   = ScreenRectangle.left   - 2;
    adjustedRectangle.top    = ScreenRectangle.top    - 2;
    adjustedRectangle.right  = ScreenRectangle.right  + 2;
    adjustedRectangle.bottom = ScreenRectangle.bottom + 2;

    // Expand/contract the bounding box based on the zoom
    if (zoom_flag)
    {
        adjustedRectangle.left   *= the_zoom;
        adjustedRectangle.top    *= the_zoom;
        adjustedRectangle.right  *= the_zoom;
        adjustedRectangle.bottom *= the_zoom;
    }

    const UINT scrollerX = GetScreenHorizontalScrollPosition();
    const UINT scrollerY = GetScreenVerticalScrollPosition();

    // Move the bounding box based on scroll position.
    adjustedRectangle.left   -= scrollerX;
    adjustedRectangle.right  -= scrollerX;
    adjustedRectangle.top    -= scrollerY;
    adjustedRectangle.bottom -= scrollerY;

    ::InvalidateRect(GetScreenWindow(), &adjustedRectangle, FALSE);
}

// ibmturt() calculates what needs to be done to either draw or erase
// the turte, but it does not actually do either of these operations.
// If draw==true, then the points of the turtle's vertices are computed.
// If draw==false, then the points of the turtle's vertices are simply used
// to invalidate the turtle's bounding box (so it will get erased).
void ibmturt(bool draw)
{
    // special turtles must not be drawn
    assert(!g_SelectedTurtle->IsSpecial);
    
    if (draw)
    {
        // We are supposed to draw the turtle in a new position, we
        // we need to re-calculate its points.

        if (current_mode == perspectivemode)
        {
            // in 3D mode
            for (int j = 0; j < 4; j++)
            {
                VECTOR rp = MVxyMultiply(g_SelectedTurtle->Matrix, turtle_vertices[j].from);

                VECTOR from3d;
                from3d.x = (g_SelectedTurtle->Position.x + rp.x) / BitMapWidth;
                from3d.y = (g_SelectedTurtle->Position.y + rp.y) / BitMapWidth;
                from3d.z = (g_SelectedTurtle->Position.z + rp.z) / BitMapWidth;

                rp = MVxyMultiply(g_SelectedTurtle->Matrix, turtle_vertices[j].to);

                VECTOR to3d;
                to3d.x = (g_SelectedTurtle->Position.x + rp.x) / BitMapWidth;
                to3d.y = (g_SelectedTurtle->Position.y + rp.y) / BitMapWidth;
                to3d.z = (g_SelectedTurtle->Position.z + rp.z) / BitMapWidth;

                POINT from2d;
                POINT to2d;
                if (ThreeD.TransformSegment(from3d, to3d, from2d, to2d))
                {
                    long iFromx =  from2d.x + xoffset;
                    long iFromy = -from2d.y + yoffset;
                    long iTox   =  to2d.x   + xoffset;
                    long iToy   = -to2d.y   + yoffset;
               
                    g_SelectedTurtle->Points[j].from.x = iFromx;
                    g_SelectedTurtle->Points[j].from.y = iFromy;
                    g_SelectedTurtle->Points[j].to.x   = iTox;
                    g_SelectedTurtle->Points[j].to.y   = iToy;
                    g_SelectedTurtle->Points[j].bValid = true;
                }
                else
                {
                    g_SelectedTurtle->Points[j].bValid = false;
                }
            }
        }
        else
        {
            // 2D mode
            for (int j = 0; j < 3; j++)
            {
                FLONUM cosine = cos(g_SelectedTurtle->Heading * rads_per_degree);
                FLONUM sine   = sin(g_SelectedTurtle->Heading * rads_per_degree);

                FLONUM rx = X_ROTATED(turtle_vertices[j].from.x, turtle_vertices[j].from.y, cosine, sine);
                FLONUM ry = Y_ROTATED(turtle_vertices[j].from.x, turtle_vertices[j].from.y, cosine, sine);

                FLONUM oldx = g_SelectedTurtle->Position.x + rx;
                FLONUM oldy = g_SelectedTurtle->Position.y + ry;

                rx = X_ROTATED(turtle_vertices[j].to.x, turtle_vertices[j].to.y, cosine, sine);
                ry = Y_ROTATED(turtle_vertices[j].to.x, turtle_vertices[j].to.y, cosine, sine);

                FLONUM newx = g_SelectedTurtle->Position.x + rx;
                FLONUM newy = g_SelectedTurtle->Position.y + ry;

                long iOldx = g_round(oldx);
                long iOldy = g_round(oldy);
                long iNewx = g_round(newx);
                long iNewy = g_round(newy);

                long iFromx =  iOldx + xoffset;
                long iFromy = -iOldy + yoffset;
                long iTox   =  iNewx + xoffset;
                long iToy   = -iNewy + yoffset;

                g_SelectedTurtle->Points[j].from.x = iFromx;
                g_SelectedTurtle->Points[j].from.y = iFromy;
                g_SelectedTurtle->Points[j].to.x   = iTox;
                g_SelectedTurtle->Points[j].to.y   = iToy;

                g_SelectedTurtle->Points[j].bValid = true;
            }

            // The line that distingiushes left from right is not needed
            // in 2D modes.
            g_SelectedTurtle->Points[3].bValid = false;
        }
    }

    bool  needsInvalidation = false;
    RECT  invalidationBoundingBox;

    if (g_SelectedTurtle->BitmapRasterMode != 0)
    {
        // The turtle is bitmapped, we need to invalidate the bounding box of the bitmap.
        POINT dest;
        needsInvalidation = WorldCoordinateToScreenCoordinate(
            g_SelectedTurtle->Position,
            dest);

        // If the turtle is on the screen, then calculate the bounding box.
        if (needsInvalidation)
        {
            // figure out the index into the bitmaps array.
            const CUTMAP & turtleBitmap = g_Bitmaps[g_SelectedTurtle - g_Turtles];

            FLONUM leftOffset;
            FLONUM rightOffset;
            FLONUM topOffset;
            FLONUM bottomOffset;

            if (g_SelectedTurtle->IsSprite)
            {
                FLONUM cosine = cos(g_SelectedTurtle->Heading * rads_per_degree);
                FLONUM sine   = sin(g_SelectedTurtle->Heading * rads_per_degree);

                // Compute points of the image rotated about its center.
                FLONUM x0 = X_ROTATED(-turtleBitmap.Width/2, -turtleBitmap.Height/2, cosine, sine);
                FLONUM y0 = Y_ROTATED(-turtleBitmap.Width/2, -turtleBitmap.Height/2, cosine, sine);

                FLONUM x1 = X_ROTATED(-turtleBitmap.Width/2, turtleBitmap.Height/2, cosine, sine);
                FLONUM y1 = Y_ROTATED(-turtleBitmap.Width/2, turtleBitmap.Height/2, cosine, sine);

                FLONUM x2 = X_ROTATED(turtleBitmap.Width/2, turtleBitmap.Height/2, cosine, sine);
                FLONUM y2 = Y_ROTATED(turtleBitmap.Width/2, turtleBitmap.Height/2, cosine, sine);

                FLONUM x3 = X_ROTATED(turtleBitmap.Width/2, -turtleBitmap.Height/2, cosine, sine);
                FLONUM y3 = Y_ROTATED(turtleBitmap.Width/2, -turtleBitmap.Height/2, cosine, sine);

                // Compute the bounding box.  We grow the box by one to account for rounding errors.
                leftOffset   = min(x0,min(x1, min(x2,x3))) - 1;
                topOffset    = min(y0,min(y1, min(y2,y3))) - 1;
                rightOffset  = max(x0,max(x1, max(x2,x3))) + 1;
                bottomOffset = max(y0,max(y1, max(y2,y3))) + 1;
            }
            else
            {
                leftOffset   = 0;
                topOffset    = LL - turtleBitmap.Height;
                rightOffset  = turtleBitmap.Width;
                bottomOffset = LL;
            }

            invalidationBoundingBox.left   = +dest.x + xoffset + leftOffset;
            invalidationBoundingBox.top    = -dest.y + yoffset + topOffset;
            invalidationBoundingBox.right  = +dest.x + xoffset + rightOffset;
            invalidationBoundingBox.bottom = -dest.y + yoffset + bottomOffset;

            // Make sure that the left side of the rectangle is less than the right side
            if (invalidationBoundingBox.right < invalidationBoundingBox.left)
            {
                const LONG oldLeftValue = invalidationBoundingBox.left;

                invalidationBoundingBox.left  = invalidationBoundingBox.right;
                invalidationBoundingBox.right = oldLeftValue;
            }

            // Make sure that the top of the rectangle is above (less than) the bottom side
            if (invalidationBoundingBox.bottom < invalidationBoundingBox.top)
            {
                const LONG oldBottomValue = invalidationBoundingBox.bottom;

                invalidationBoundingBox.bottom = invalidationBoundingBox.top;
                invalidationBoundingBox.top    = oldBottomValue;
            }
        }
    }
    else
    {
        // The turtle is drawn with lines, so we need to calculate the bounding box
        // of these lines.

        // First calculate the bounding box independent of zoom and scroll position.
        invalidationBoundingBox.left   =  100000;
        invalidationBoundingBox.top    =  100000;
        invalidationBoundingBox.right  = -100000;
        invalidationBoundingBox.bottom = -100000;
        for (int j = 0; j < 4; j++)
        {
            if (g_SelectedTurtle->Points[j].bValid)
            {
                invalidationBoundingBox.left   = min(invalidationBoundingBox.left,   (long) (g_SelectedTurtle->Points[j].from.x));
                invalidationBoundingBox.top    = min(invalidationBoundingBox.top,    (long) (g_SelectedTurtle->Points[j].from.y));
                invalidationBoundingBox.right  = max(invalidationBoundingBox.right,  (long) (g_SelectedTurtle->Points[j].from.x));
                invalidationBoundingBox.bottom = max(invalidationBoundingBox.bottom, (long) (g_SelectedTurtle->Points[j].from.y));
                needsInvalidation = true;
            }
        }
    }

    if (needsInvalidation)
    {
        InvalidateRectangleOnScreen(invalidationBoundingBox);
    }
}


NODE *lsetpixel(NODE *args)
{
    ASSERT_TURTLE_INVARIANT;

    POINT dest;
    if (!WorldCoordinateToScreenCoordinate(g_SelectedTurtle->Position, dest))
    {
        return Unbound;
    }

    // get args
    COLORREF color = GetColorArgument(args);

    if (NOT_THROWING)
    {
        // memory
        HDC MemDC = GetMemoryDeviceContext();

        HBITMAP oldBitmap = (HBITMAP) SelectObject(MemDC, MemoryBitMap);

        if (EnablePalette)
        {
            OldPalette = SelectPalette(MemDC, ThePalette, FALSE);
            RealizePalette(MemDC);
        }

        SetPixel(
            MemDC,
            +dest.x + xoffset,
            -dest.y + yoffset,
            color);

        SelectObject(MemDC, oldBitmap);
        if (EnablePalette)
        {
            SelectPalette(MemDC, OldPalette, FALSE);
        }

        //screen
        HDC ScreenDC = GetScreenDeviceContext();

        draw_turtle(false);

        HPALETTE oldPalette2;
        if (EnablePalette)
        {
            oldPalette2 = SelectPalette(ScreenDC, ThePalette, FALSE);
            RealizePalette(ScreenDC);
        }

        if (zoom_flag)
        {
            RECT temprect;

            temprect.left   = +dest.x + xoffset;
            temprect.top    = -dest.y + yoffset;
            temprect.right  = +dest.x + xoffset;
            temprect.bottom = -dest.y + yoffset;

            InvalidateRectangleOnScreen(temprect);
        }
        else
        {
            SetPixel(
                ScreenDC,
                +dest.x - GetScreenHorizontalScrollPosition() + xoffset,
                -dest.y - GetScreenVerticalScrollPosition()   + yoffset,
                color);
        }

        if (EnablePalette)
        {
            SelectPalette(ScreenDC, oldPalette2, FALSE);
        }

        draw_turtle(true);
    }

    return Unbound;
}

static
int
getindexcolor(
    const COLORREF & color
    )
{
    for (int i=0;i<16;i++)
    {
        if (color == colortable[i])
        {
            return i;
        }
    }
    return -1;
}


// function that returns the RGB vector of the pixel the turtle is on top of
NODE *lpixel(NODE *)
{
    ASSERT_TURTLE_INVARIANT;

    POINT dest;
    if (!WorldCoordinateToScreenCoordinate(g_SelectedTurtle->Position, dest))
    {
        return cons_list(
            make_intnode((FIXNUM) - 1),
            make_intnode((FIXNUM) - 1),
            make_intnode((FIXNUM) - 1));
    }

    // memory
    HDC MemDC = GetMemoryDeviceContext();
    HBITMAP oldBitmap = (HBITMAP) SelectObject(MemDC, MemoryBitMap);

    if (EnablePalette)
    {
        OldPalette = SelectPalette(MemDC, ThePalette, FALSE);
        RealizePalette(MemDC);
    }

    COLORREF the_color = GetPixel(MemDC, dest.x + xoffset, -dest.y + yoffset);

    if (EnablePalette)
    {
        SelectPalette(MemDC, OldPalette, FALSE);
    }

    if (bIndexMode)
    {
        int icolor = getindexcolor(the_color);
        if (icolor >= 0) 
        {
            return(make_intnode(icolor));
        }
    }

    return cons_list(
        make_intnode((FIXNUM) GetRValue(the_color)),
        make_intnode((FIXNUM) GetGValue(the_color)),
        make_intnode((FIXNUM) GetBValue(the_color)));
}

void logofill(bool bOld)
{
    POINT dest;
    if (!WorldCoordinateToScreenCoordinate(g_SelectedTurtle->Position, dest))
    {
        return;
    }

    HBRUSH JunkBrush = CreateBrushIndirect(&FloodBrush);

    // memory
    HDC MemDC = GetMemoryDeviceContext();
    HBITMAP oldBitmap = (HBITMAP) SelectObject(MemDC, MemoryBitMap);

    if (EnablePalette)
    {
        OldPalette = SelectPalette(MemDC, ThePalette, FALSE);
        RealizePalette(MemDC);
    }

    SetTextColor(MemDC, pcolor);

    HBRUSH oldBrush = (HBRUSH) SelectObject(MemDC, JunkBrush);

    if (bOld)
    {
        ExtFloodFill(
            MemDC,
            +dest.x + xoffset,
            -dest.y + yoffset,
            pcolor,
            FLOODFILLBORDER);
    }
    else
    {
        COLORREF tcolor = GetPixel(MemDC, dest.x + xoffset, -dest.y + yoffset) | 0x02000000;

        ExtFloodFill(
            MemDC,
            +dest.x + xoffset,
            -dest.y + yoffset,
            tcolor,
            FLOODFILLSURFACE);
    }

    if (EnablePalette)
    {
        SelectPalette(MemDC, OldPalette, FALSE);
    }

    SelectObject(MemDC, oldBrush);
    SelectObject(MemDC, oldBitmap);

    DeleteObject(JunkBrush);
}


static NODE* color_helper(const Color & col)
{
    if (bIndexMode)
    {
        int icolor = getindexcolor(RGB(col.red, col.green, col.blue));
        if (icolor >= 0)
        {
            return make_intnode(icolor);
        }
    }

    return cons_list(
        make_intnode((FIXNUM) col.red),
        make_intnode((FIXNUM) col.green),
        make_intnode((FIXNUM) col.blue));
}

NODE *lpencolor(NODE *)
{
    ASSERT_TURTLE_INVARIANT;

    return color_helper(GetPenStateForSelectedTurtle().Color);
}


// Do all of the things necessary when the pen color changes:
// * Sets the pen color on the active turtle
// * Updates the palette, if necessary
// * Updates the global pen
// * Updates the values in the status window
void ChangeActivePenColor(int Red, int Green, int Blue)
{
    Color & penColor = GetPenStateForSelectedTurtle().Color;
    penColor.red   = Red;
    penColor.green = Green;
    penColor.blue  = Blue;

    if (EnablePalette)
    {
        pcolor = LoadColor(Red, Green, Blue);
    }
    else
    {
        pcolor = RGB(Red, Green, Blue);
    }

    UpdateNormalPen(GetPenStateForSelectedTurtle().Width, pcolor);

    update_status_pencolor();
}


// function to return flood color as a RGB list
NODE *lfloodcolor(NODE *)
{
    ASSERT_TURTLE_INVARIANT;

    return color_helper(dfld);
}

// Do all of the things necessary when the flood color changes:
// * Sets the global flood color
// * Updates the palette, if necessary
// * Updates the global flood color brush
// * Updates the values in the status window
void ChangeActiveFloodColor(int Red, int Green, int Blue)
{
    dfld.red   = Red;
    dfld.green = Green;
    dfld.blue  = Blue;

    if (EnablePalette)
    {
        fcolor = LoadColor(dfld.red, dfld.green, dfld.blue);
    }
    else
    {
        fcolor = RGB(dfld.red, dfld.green, dfld.blue);
    }

    FloodBrush.lbStyle = BS_SOLID;
    FloodBrush.lbColor = fcolor;
    FloodBrush.lbHatch = HS_VERTICAL;

    update_status_floodcolor();
}

// function to return screen color as a RGB list
NODE *lscreencolor(NODE *)
{
    return color_helper(dscn);
}

// Do all of the things necessary when the screen color changes:
// * Sets the global screen color
// * Updates the palette, if necessary
// * Updates the global screen brush (and erase brush)
// * Updates the values in the status window
void ChangeActiveScreenColor(int Red, int Green, int Blue)
{
    dscn.red   = Red;
    dscn.green = Green;
    dscn.blue  = Blue;

    if (EnablePalette)
    {
        scolor = LoadColor(dscn.red, dscn.green, dscn.blue);
    }
    else
    {
        scolor = RGB(dscn.red, dscn.green, dscn.blue);
    }

    ScreenBrush.lbStyle = BS_SOLID;
    ScreenBrush.lbColor = scolor;
    ScreenBrush.lbHatch = HS_VERTICAL;

    // When the screen changes we change the erase pen which basically
    // writes the screen color
    UpdateErasePen(GetPenStateForSelectedTurtle().Width, scolor);

    HBRUSH TempBrush = CreateBrushIndirect(&ScreenBrush);

    // memory
    HDC MemDC = GetMemoryDeviceContext();

    HBITMAP oldBitmap = (HBITMAP) SelectObject(MemDC, MemoryBitMap);

    if (EnablePalette)
    {
        OldPalette = SelectPalette(MemDC, ThePalette, FALSE);
        RealizePalette(MemDC);
    }

    FillRect(MemDC, &FullRect, TempBrush);

    if (EnablePalette)
    {
        SelectPalette(MemDC, OldPalette, FALSE);
    }

    SelectObject(MemDC, oldBitmap);
    DeleteObject(TempBrush);

    ::InvalidateRect(GetScreenWindow(), NULL, TRUE);

    update_status_screencolor();
}

int get_pen_width()
{
    return GetPenStateForSelectedTurtle().Width;
}

int get_pen_height()
{
    return get_pen_width();
}

void set_pen_width(int w)
{
    GetPenStateForSelectedTurtle().Width = w;

    // we erase with the same pen width as we write
    UpdateNormalPen(w, pcolor);
    UpdateErasePen(w,  scolor);
}

void set_pen_height(int h)
{
    set_pen_width(h);
}

NODE *lclearpalette(NODE *)
{
    // kill the palette and recreate it with just black and white
    if (EnablePalette)
    {
        DeleteObject(ThePalette);

        MyLogPalette->palNumEntries = 2;

        update_status_paletteuse();

        ThePalette = CreatePalette(MyLogPalette);

        ::InvalidateRect(GetMainWindow(), NULL, TRUE);
    }

    return Unbound;
}

NODE *lstatus(NODE *)
{
    ASSERT_TURTLE_INVARIANT;

    OpenStatusWindow();
    return Unbound;
}

NODE *lnostatus(NODE *)
{
    CloseStatusWindow();
    return Unbound;
}


// The zoom control flag determines whether or not we can use the faster line
// drawing method of drawing directly to the screen buffer, or use the slower
// method of drawing to the backbuffer and invalidating part of the screen.
// This is only faster when there is no zooming.
// And it's only correct to do when there are no widgets on the screen, such
// as ones created with BUTTONCREATE or LISTBOXCREATE.
void UpdateZoomControlFlag()
{
    if ((the_zoom != 1.0) || CheckOnScreenControls())
    {
        zoom_flag = true;
    }
    else
    {
        zoom_flag = false;
    }
}

// The real work of zooming is done in Paint this just adjusts the scroller
// to something reasonable so that what was basically in the center of the
// screen still is. It also readjusts the ranges on the scrollers.
void zoom_helper(FLONUM NewZoomFactor)
{
    if (the_zoom != NewZoomFactor)
    {
        the_zoom = NewZoomFactor;

        AdjustScrollPositionToZoomFactor(NewZoomFactor);

        // hide turtle while we do this
        draw_turtle(false);

        UpdateZoomControlFlag();

        draw_turtle(true);

        // paint the entire window
        InvalidateRect(GetScreenWindow(), NULL, TRUE);
    }
}

NODE *lzoom(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    NODE *val = positive_numeric_arg(arg);
    if (stopping_flag != THROWING)
    {
        FLONUM temp_zoom = numeric_node_to_flonum(val);

        zoom_helper(temp_zoom);
    }

    return Unbound;
}


NODE *lbitblock(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    POINT turtleLocation;
    if (!WorldCoordinateToScreenCoordinate(
            g_SelectedTurtle->Position, 
            turtleLocation))
    {
        // the turtle is not on the screen
        return Unbound;
    }

    // get args
    int cutWidth  = getint(nonnegative_int_arg(arg));
    int cutHeight = getint(nonnegative_int_arg(cdr(arg)));

    if (NOT_THROWING)
    {
        // only do the blit if a non-zero area was specified
        if (cutWidth != 0 && cutHeight != 0)
        {
            HBRUSH fillBrush = CreateBrushIndirect(&FloodBrush);

            // memory
            HDC     memDC     = GetMemoryDeviceContext();
            HBITMAP oldBitmap = (HBITMAP) SelectObject(memDC, MemoryBitMap);

            if (EnablePalette)
            {
                OldPalette = SelectPalette(memDC, ThePalette, FALSE);
                RealizePalette(memDC);
            }

            RECT memoryRect;
            memoryRect.left   = +turtleLocation.x + xoffset;
            memoryRect.right  = memoryRect.left + cutWidth;
            memoryRect.bottom = -turtleLocation.y + yoffset + LL;
            memoryRect.top    = memoryRect.bottom - cutHeight;

            FillRect(memDC, &memoryRect, fillBrush);

            SelectObject(memDC, oldBitmap);
            if (EnablePalette)
            {
                SelectPalette(memDC, OldPalette, FALSE);
            }

            //screen
            if (zoom_flag)
            {
                // It's easier to invalidate the screen and force a 
                // repaint from the image memory.
                InvalidateRect(GetScreenWindow(), NULL, FALSE);
            }
            else
            {
                // Invalidate the portion of the screen that corresponds
                // to the region of memory that we filled.
                // Ever since we stopped calling GetDC() and ReleaseDC()
                // to get the screen DC, simply calling FillRect() on the
                // screen causes repainting problems.
                // I suspect that calling ReleaseDC() implicitly invalidated
                // the screen, which may be why it was so much slower.
                InvalidateRectangleOnScreen(memoryRect);
            }

            DeleteObject(fillBrush);
        }
    }

    return Unbound;
}


// Converts the FMSLogo bitmode to the Window raster mode
static
DWORD
BitModeToRasterMode(
    FIXNUM BitMode
    )
{
    switch (BitMode)
    {
    case 1:
        return SRCCOPY;

    case 2:
        return SRCPAINT;

    case 3: 
        return SRCAND;

    case 4:
        return SRCINVERT;

    case 5:
        return SRCERASE;

    case 6:
        return NOTSRCCOPY;

    case 7:
        return NOTSRCERASE;

    case 8:
        return MERGEPAINT;

    case 9:
        return DSTINVERT;

    default:
        // notify the caller that the bitmode was invalid
        return 0;
    }
}

// Converts the Window raster mode to a FMSLogo bitmode.
static
FIXNUM
RasterModeToBitMode(
    DWORD RasterMode
    )
{
    // return the logo "code" for the bit mode
    switch (RasterMode)
    {
    case 0:
    case SRCCOPY: 
        return 1;

    case SRCPAINT: 
        return 2;

    case SRCAND: 
        return 3;

    case SRCINVERT: 
        return 4;

    case SRCERASE:
        return 5;

    case NOTSRCCOPY:
        return 6;

    case NOTSRCERASE:
        return 7;

    case MERGEPAINT: 
        return 8;

    case DSTINVERT:
        return 9;
    }

    assert(0 && "can't happen");
    return 0;
}

static
DWORD
BitModeArgsToRasterMode(
    NODE * BitModeArguments
    )
{
    NODE * bitModeNode = ranged_integer_arg(BitModeArguments, 1, 9);
    if (stopping_flag == THROWING)
    {
        return 0;
    }

    return BitModeToRasterMode(getint(bitModeNode));
}


NODE *lbitmode(NODE *)
{
    ASSERT_TURTLE_INVARIANT;

    // return the logo "code" for the bit mode
    FIXNUM temp = RasterModeToBitMode(g_BitMode);

    return make_intnode(temp);
}

NODE *lsetbitmode(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    // convert from logo "code" to Windows constants
    FIXNUM bitmode = BitModeArgsToRasterMode(arg);
    if (NOT_THROWING)
    {
        g_BitMode = bitmode;
    }
    return Unbound;
}

NODE *lturtlemode(NODE *)
{
    ASSERT_TURTLE_INVARIANT;

    // return the logo "code" for the bit mode
    FIXNUM turtlemode = RasterModeToBitMode(g_SelectedTurtle->BitmapRasterMode);
    return make_intnode(turtlemode);
}

NODE *lsetturtlemode(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    if (g_SelectedTurtle->BitmapRasterMode)
    {
        draw_turtle(false);

        // convert from logo "code" to Windows constants
        FIXNUM rastermode = BitModeArgsToRasterMode(arg);
        if (NOT_THROWING)
        {
            g_SelectedTurtle->BitmapRasterMode = rastermode;
        }

        draw_turtle(true);
    }

    return Unbound;
}

NODE *lbitindex(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;
    // return the current bitmap index
    return make_intnode((FIXNUM) (g_SelectedBitmap - g_Bitmaps));
}

NODE *lsetbitindex(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    // set the current bitmap index if within range
    int i = getint(nonnegative_int_arg(arg));
    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    if (g_BitmapsLimit <= i)
    {
        GrowBitmapsArray(i + 1);
        if (stopping_flag == THROWING)
        {
            return Unbound;
        }
    }

    g_SelectedBitmap = g_Bitmaps + i;

    return Unbound;
}


static
void
CopyFromBitmapArrayToClipboard()
{
    // Open the clipboard, dump what's in there and return the Bitmap
    ::OpenClipboard(GetMainWindow());

    ::EmptyClipboard();

    ::SetClipboardData(
        CF_BITMAP,
        g_Bitmaps[0].MemoryBitMap);

    if (EnablePalette)
    {
        // If we have a palette given him a DIB and a palette too
        ::SetClipboardData(
            CF_DIB,
            BitmapToDIB(
                g_Bitmaps[0].MemoryBitMap,
                ThePalette));

        ::SetClipboardData(
            CF_PALETTE,
            CreatePalette(MyLogPalette));
    }
    else
    {
        // else give him a DIB using system palette
        ::SetClipboardData(
            CF_DIB,
            BitmapToDIB(
                g_Bitmaps[0].MemoryBitMap,
                NULL));
    }

    ::CloseClipboard();

    // Never mung with bitmaps that belong to ClipBoard
    g_Bitmaps[0].IsValid = false;
}



static
void
PasteFromClipboardToBitmapArray()
{
    ::OpenClipboard(GetMainWindow());

    // Try a DIB first
    HANDLE tempDIB = (HBITMAP) ::GetClipboardData(CF_DIB);
    if (tempDIB != NULL)
    {
        // The clipboard holds a DIB.  Try to get the palette.
        HPALETTE tempPal = (HPALETTE) ::GetClipboardData(CF_PALETTE);

        // we work in bmps here
        g_Bitmaps[0].MemoryBitMap = ::DIBToBitmap(tempDIB, tempPal);

        // Fill our logical palette with the Palette from the clipboard
        if (EnablePalette && (tempPal != NULL))
        {
            MyLogPalette->palNumEntries = ::GetPaletteEntries(
                tempPal,
                0,
                256,
                &MyLogPalette->palPalEntry[0]);

            // now rebuild palette
            ::DeleteObject(ThePalette);
            ThePalette = ::CreatePalette(MyLogPalette);
            update_status_paletteuse();
        }

        // Let code know below that we have something
        g_Bitmaps[0].IsValid = true;

        // We created a BitMap from the DIB that we only need for the
        // purpose of this "paste", next paste could be something new.
        // so get rid of it once we have pasted it here.

        ::EmptyClipboard();
        ::SetClipboardData(CF_BITMAP, g_Bitmaps[0].MemoryBitMap);

        // If we have a palette given him a DIB and a palette too
        if (EnablePalette)
        {
            ::SetClipboardData(
                CF_DIB,
                BitmapToDIB(g_Bitmaps[0].MemoryBitMap, ThePalette));

            ::SetClipboardData(
                CF_PALETTE,
                CreatePalette(MyLogPalette));
        }
        else
        {
            // else give him a DIB using system palette
            ::SetClipboardData(
                CF_DIB,
                BitmapToDIB(g_Bitmaps[0].MemoryBitMap, NULL));
        }
    }
    else
    {
        // else try for a bitmap
        g_Bitmaps[0].MemoryBitMap = (HBITMAP) ::GetClipboardData(CF_BITMAP);

        // flag that we have one if it exists, no need to delete the
        // bitmap here because clipboard still owns it.

        if (g_Bitmaps[0].MemoryBitMap != NULL)
        {
            g_Bitmaps[0].IsValid = true;
        }
        else
        {
            g_Bitmaps[0].IsValid = false;
        }
    }

    // if we have something fetch its size

    if (g_Bitmaps[0].IsValid)
    {
        BITMAP temp;

        ::GetObject(
            g_Bitmaps[0].MemoryBitMap,
            sizeof(BITMAP),
            (LPSTR) &temp);

        g_Bitmaps[0].Width = temp.bmWidth;
        g_Bitmaps[0].Height = temp.bmHeight;
    }

    // we have everything we need
    ::CloseClipboard();
}


static
NODE *
BitCopyOrCut(NODE *arg, bool IsCut)
{
    POINT dest;
    if (!WorldCoordinateToScreenCoordinate(g_SelectedTurtle->Position, dest))
    {
        return Unbound;
    }

    int tempWidth = getint(nonnegative_int_arg(arg));
    int tempHeight = getint(nonnegative_int_arg(cdr(arg)));

    if (NOT_THROWING)
    {
        bool havebitmap = false;

        // if we had a old cut get rid of it, we won't go in for clipboard
        if (g_SelectedBitmap->IsValid)
        {
            // if same size reuse the bitmap
            if ((tempWidth == g_SelectedBitmap->Width) &&
                (tempHeight == g_SelectedBitmap->Height))
            {
                havebitmap = true;
            }
            else
            {
                // else get rid of it and make a new one later
                DeleteObject(g_SelectedBitmap->MemoryBitMap);
            }
            g_SelectedBitmap->IsValid = false;
        }

        g_SelectedBitmap->Width  = tempWidth;
        g_SelectedBitmap->Height = tempHeight;

        // only if we have a surface continue
        if ((g_SelectedBitmap->Width != 0) && (g_SelectedBitmap->Height != 0))
        {
            // flag it so we will delete it
            g_SelectedBitmap->IsValid = true;

            HDC screenDC = GetScreenDeviceContext();
            HDC memDC    = GetMemoryDeviceContext();

            HBITMAP oldBitmap = (HBITMAP) SelectObject(memDC, MemoryBitMap);

            if (!havebitmap)
            {
                g_SelectedBitmap->MemoryBitMap = CreateCompatibleBitmap(
                    screenDC,
                    g_SelectedBitmap->Width,
                    g_SelectedBitmap->Height);
            }

            if (!g_SelectedBitmap->MemoryBitMap)
            {
                ShowErrorMessageAndStop(LOCALIZED_ERROR_BITMAPCUTFAILED);
                return Unbound;
            }


            HDC tempMemDC = CreateCompatibleDC(screenDC);

            HBITMAP oldBitmap2 = (HBITMAP) SelectObject(
                tempMemDC,
                g_SelectedBitmap->MemoryBitMap);

            BitBlt(
                tempMemDC,
                0,
                0,
                g_SelectedBitmap->Width,
                g_SelectedBitmap->Height,
                memDC,
                +dest.x + xoffset,
                -dest.y + yoffset + LL - g_SelectedBitmap->Height,
                SRCCOPY);

            SelectObject(tempMemDC, oldBitmap2);
            DeleteDC(tempMemDC);

            if (IsCut)
            {
                // this is a cut operation (as opposed to a copy operation)

                // memory
                RECT tempRect;
                SetRect(
                    &tempRect,
                    +dest.x + xoffset,
                    -dest.y + yoffset + LL - g_SelectedBitmap->Height,
                    +dest.x + xoffset + g_SelectedBitmap->Width,
                    -dest.y + yoffset + LL);

                HBRUSH tempBrush = CreateBrushIndirect(&ScreenBrush);

                FillRect(memDC, &tempRect, tempBrush);

                //screen
                draw_turtle(false);

                if (zoom_flag)
                {
                    // TRect temp;
                    //
                    // temp.Set(
                    //   (+g_SelectedTurtle->Position.x - MainWindowx->Scroller->XPos / the_zoom + xoffset                                  ) * the_zoom,
                    //   (-g_SelectedTurtle->Position.y - MainWindowx->Scroller->YPos / the_zoom + yoffset + LL - g_SelectedBitmap->Height) * the_zoom,
                    //   (+g_SelectedTurtle->Position.x - MainWindowx->Scroller->XPos / the_zoom + xoffset + g_SelectedBitmap->Width      ) * the_zoom,
                    //   (-g_SelectedTurtle->Position.y - MainWindowx->Scroller->YPos / the_zoom + yoffset + LL                             ) * the_zoom);
                    //
                    // temp.Normalize();
                    // temp.Inflate(1+the_zoom,1+the_zoom);
                    InvalidateRect(GetScreenWindow(), NULL, FALSE);
                }
                else
                {
                    RECT tempRect;
                    SetRect(
                        &tempRect,
                        +g_SelectedTurtle->Position.x - GetScreenHorizontalScrollPosition() + xoffset,
                        -g_SelectedTurtle->Position.y - GetScreenVerticalScrollPosition()   + yoffset + LL - g_SelectedBitmap->Height,
                        +g_SelectedTurtle->Position.x - GetScreenHorizontalScrollPosition() + xoffset + g_SelectedBitmap->Width,
                        -g_SelectedTurtle->Position.y - GetScreenVerticalScrollPosition()   + yoffset + LL);

                    FillRect(screenDC, &tempRect, tempBrush);
                }

                DeleteObject(tempBrush);

                draw_turtle(true);
            }

            SelectObject(memDC, oldBitmap);

            if (ClipboardIsSelectedBitmap())
            {
                CopyFromBitmapArrayToClipboard();
            }
        }
    }

    return Unbound;
}


NODE *lbitcut(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;
    return BitCopyOrCut(arg, true);
}

NODE *lbitcopy(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;
    return BitCopyOrCut(arg, false);
}

NODE *lbitfit(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    FIXNUM newWidth  = getint(nonnegative_int_arg(arg));
    FIXNUM newHeight = getint(nonnegative_int_arg(cdr(arg)));

    if (NOT_THROWING)
    {
        // If clipboard check with clipboard only
        if (ClipboardIsSelectedBitmap())
        {
            PasteFromClipboardToBitmapArray();
        }

        // resize the bitmap if we have a surface to fit to and from
        if (newWidth != 0 && newHeight != 0 && g_SelectedBitmap->IsValid)
        {
            HDC ScreenDC = GetScreenDeviceContext();
            HDC MemDC    = GetMemoryDeviceContext();

            HBITMAP savedMemBitmap = (HBITMAP) SelectObject(MemDC, g_SelectedBitmap->MemoryBitMap);

            HPALETTE savedScreenPalette;
            HPALETTE savedMemoryPalette;
            if (EnablePalette)
            {
                savedScreenPalette = SelectPalette(ScreenDC, ThePalette, FALSE);
                RealizePalette(ScreenDC);

                savedMemoryPalette = SelectPalette(MemDC, ThePalette, FALSE);
                RealizePalette(MemDC);
            }

            HBITMAP newMemoryBitmap = CreateCompatibleBitmap(ScreenDC, newWidth, newHeight);
            if (newMemoryBitmap != NULL)
            {
                HDC tempMemDC = CreateCompatibleDC(ScreenDC);
                HBITMAP savedTempMemoryBitmap = (HBITMAP) SelectObject(tempMemDC, newMemoryBitmap);

                HPALETTE savedTempMemoryPalette;
                if (EnablePalette)
                {
                    savedTempMemoryPalette = SelectPalette(tempMemDC, ThePalette, FALSE);
                    RealizePalette(tempMemDC);
                }

                if (g_OsVersionInformation.dwPlatformId == VER_PLATFORM_WIN32_NT)
                {
                    SetStretchBltMode(tempMemDC, HALFTONE);
                }
                else
                {
                    // HALFTONE is not supported on Win 95/98/ME
                    SetStretchBltMode(tempMemDC, COLORONCOLOR);
                }

                // Load hour-glass cursor.
                HCURSOR oldCursor =::SetCursor(hCursorWait);

                StretchBlt(
                    tempMemDC,
                    0,
                    0,
                    newWidth,
                    newHeight,
                    MemDC,
                    0,
                    0,
                    g_SelectedBitmap->Width,
                    g_SelectedBitmap->Height,
                    SRCCOPY);

                // Restore the arrow cursor.
                ::SetCursor(oldCursor);

                if (EnablePalette)
                {
                    SelectPalette(tempMemDC, savedTempMemoryPalette, FALSE);
                }

                SelectObject(tempMemDC, savedTempMemoryBitmap);
                DeleteDC(tempMemDC);

                // commit to using the new "bitfitted" bitmap
                DeleteObject(g_SelectedBitmap->MemoryBitMap);
                g_SelectedBitmap->MemoryBitMap = newMemoryBitmap;

                g_SelectedBitmap->Width  = newWidth;
                g_SelectedBitmap->Height = newHeight;
            }
            else
            {
                err_logo(OUT_OF_MEM, NIL);
            }


            if (EnablePalette)
            {
                SelectPalette(MemDC,    savedMemoryPalette, FALSE);
                SelectPalette(ScreenDC, savedScreenPalette, FALSE);
            }

            SelectObject(MemDC, savedMemBitmap);

            if (ClipboardIsSelectedBitmap())
            {
                CopyFromBitmapArrayToClipboard();
            }
        }
    }
    return Unbound;
}

NODE *lbitpaste(NODE *)
{
    ASSERT_TURTLE_INVARIANT;

    POINT dest;
    if (!WorldCoordinateToScreenCoordinate(g_SelectedTurtle->Position, dest))
    {
        return Unbound;
    }

    if (NOT_THROWING)
    {
        // If clipboard check with clipboard only
        if (ClipboardIsSelectedBitmap())
        {
            PasteFromClipboardToBitmapArray();
        }

        // only if we have something to paste
        if (g_SelectedBitmap->IsValid)
        {

            if (ClipboardIsSelectedBitmap())
            {
                // never leave the clipboard's IsValid flag true
                g_SelectedBitmap->IsValid = false;
            }

            HDC ScreenDC = GetScreenDeviceContext();

            HDC TempMemDC = CreateCompatibleDC(ScreenDC);
            HBITMAP oldBitmap2 = (HBITMAP) SelectObject(
                TempMemDC,
                g_SelectedBitmap->MemoryBitMap);

            //memory
            HDC MemDC = GetMemoryDeviceContext();
            HBITMAP oldBitmap = (HBITMAP) SelectObject(MemDC, MemoryBitMap);

            BitBlt(
                MemDC,
                +dest.x + xoffset,
                -dest.y + yoffset + LL - g_SelectedBitmap->Height,
                (int) (g_SelectedBitmap->Width),
                (int) (g_SelectedBitmap->Height),
                TempMemDC,
                0,
                0,
                g_BitMode);

            SelectObject(MemDC, oldBitmap);

            //screen

            draw_turtle(false);

            if (zoom_flag)
            {
                // TRect temp;
                //
                // temp.Set(
                //     (+g_SelectedTurtle->Position.x - MainWindowx->Scroller->XPos / the_zoom + xoffset                                  ) * the_zoom,
                //     (-g_SelectedTurtle->Position.y - MainWindowx->Scroller->YPos / the_zoom + yoffset + LL - g_SelectedBitmap->Height) * the_zoom,
                //     (+g_SelectedTurtle->Position.x - MainWindowx->Scroller->XPos / the_zoom + xoffset + g_SelectedBitmap->Width      ) * the_zoom,
                //     (-g_SelectedTurtle->Position.y - MainWindowx->Scroller->YPos / the_zoom + yoffset + LL                             ) * the_zoom);
                //
                // temp.Normalize();
                // temp.Inflate(1+the_zoom,1+the_zoom);

                InvalidateRect(GetScreenWindow(), NULL, FALSE);
            }
            else
            {
                BitBlt(
                    ScreenDC,
                    +dest.x - GetScreenHorizontalScrollPosition() + xoffset,
                    -dest.y - GetScreenVerticalScrollPosition()   + yoffset + LL - g_SelectedBitmap->Height,
                    (int) (g_SelectedBitmap->Width),
                    (int) (g_SelectedBitmap->Height),
                    TempMemDC,
                    0,
                    0,
                    g_BitMode);
            }

            draw_turtle(true);

            SelectObject(TempMemDC, oldBitmap2);
            DeleteDC(TempMemDC);

            // Clipboard owns what we paste in not what we converted
        }
        else
        {
            // notify the user that the clipboard is empty
            ShowErrorMessageAndStop(LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE);
        }
    }

    return Unbound;
}

NODE *lbitpastetoindex(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    // set the current bitmap index if within range
    int i = getint(nonnegative_int_arg(arg));
    int x = int_arg(cdr(arg));
    int y = int_arg(cdr(cdr(arg)));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    if (g_BitmapsLimit <= i)
    {
        // notify the user that the bitmap index is out of range
        ShowErrorMessageAndStop(LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE);
        return Unbound;
    }
    
    if (!g_Bitmaps[i].IsValid)
    {
        // nofity the user that there is no bitmap at this index
        ShowErrorMessageAndStop(LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP);
        return Unbound;
    }

    // If ClipBoard check with ClipBoard only
    if (ClipboardIsSelectedBitmap())
    {
        PasteFromClipboardToBitmapArray();
    }

    // only if we have something to paste
    if (g_SelectedBitmap->IsValid)
    {

        if (ClipboardIsSelectedBitmap())
        {
            // never leave the clipboard's IsValid flag true
            g_SelectedBitmap->IsValid = false;
        }

        HDC ScreenDC = GetScreenDeviceContext();

        HDC TempMemDC = CreateCompatibleDC(ScreenDC);
        HBITMAP oldBitmap2 = (HBITMAP) SelectObject(
            TempMemDC,
            g_SelectedBitmap->MemoryBitMap);

        //memory
        HDC     MemDC     = GetMemoryDeviceContext();
        HBITMAP oldBitmap = (HBITMAP) SelectObject(MemDC, g_Bitmaps[i].MemoryBitMap);

        BitBlt(
            MemDC,
            +x,
            g_Bitmaps[i].Height - y - g_SelectedBitmap->Height,
            g_SelectedBitmap->Width,
            g_SelectedBitmap->Height,
            TempMemDC,
            0,
            0,
            g_BitMode);

        SelectObject(MemDC, oldBitmap);

        SelectObject(TempMemDC, oldBitmap2);
        DeleteDC(TempMemDC);

        // Clipboard owns what we paste in not what we converted
    }
    else
    {
        // notify the user that the clipboard is empty
        ShowErrorMessageAndStop(LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE);
    }

    return Unbound;
}

NODE *lsetturtle(NODE *args)
{
    ASSERT_TURTLE_INVARIANT;

    NODE * val = ranged_integer_arg(args, -TOTAL_SPECIAL_TURTLES, FIXNUM_MAX);
    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    int turtleId = getint(val);
    if (turtleId < 0)
    {
        if (cdr(args) != NIL)
        {
            // unique pen modes are meaningless for the special
            // turtles, so we consider this bad input.
            err_logo(TOO_MUCH, NIL);
            return Unbound;
        }

        // this is a special turtle.
        // Remap <-1, -2, -3> to <0, 1, 2>
        g_SelectedTurtle = g_SpecialTurtles - turtleId - 1;
    }
    else
    {
        // This is a normal turtle

        // read the optional "has unique pen" input
        bool hasUniquePen         = false; // by default, share a global pen
        bool overrideHasUniquePen = false; // by default, keep the current setting
        if (cdr(args) != NIL)
        {
            hasUniquePen         = boolean_arg(cdr(args));
            overrideHasUniquePen = true;
            if (stopping_flag == THROWING)
            {
                return Unbound;
            }
        }

        if (g_TurtlesLimit <= turtleId)
        {
            // The physical array is smaller than the requested turtle
            // index, so we must grow the turtle array.

            if (turtleId + 1 > (size_t)-1 / sizeof(*g_Turtles))
            {
                // this allocation would result in an integer overflow
                err_logo(OUT_OF_MEM, NIL);
                return Unbound;
            }

            size_t newSize = (turtleId + 1) * sizeof(*g_Turtles);
            Turtle * newTurtles = (Turtle*) realloc(g_Turtles, newSize);
            if (newTurtles == NULL)
            {
                // could not grow the turtles array to hold turtleId
                err_logo(OUT_OF_MEM, NIL);
                return Unbound;
            }

            // commit to the new array
            g_Turtles      = newTurtles;
            g_TurtlesLimit = turtleId + 1;
        }

        g_SelectedTurtle = &g_Turtles[turtleId];
        if (turtleId > g_MaxTurtle)
        {
            // This turtle has not yet been created.
            // Create this turtle and all of the turtles up to it.
            for (int i = g_MaxTurtle + 1; i <= turtleId; i++)
            {
                InitializeTurtle(&g_Turtles[i]);
                g_Turtles[i].HasOwnPenState = hasUniquePen;
            }
            
            g_MaxTurtle = turtleId;
        }

        if (overrideHasUniquePen)
        {
            // The caller specified a UseUniquePen input, so
            // we override whatever value was set in the turtle.
            g_SelectedTurtle->HasOwnPenState = hasUniquePen;
        }

        // Update the current brush.
        // ChangeActivePenColor() updates the brushes color and width.
        Color & activePenColor = GetPenStateForSelectedTurtle().Color;
        ChangeActivePenColor(
            activePenColor.red,
            activePenColor.green,
            activePenColor.blue);
    }

    draw_turtles(false);

    // update everything in the status window that can change
    // when the turtle changes.
    update_status_penstyle();
    update_status_penwidth();
    update_status_turtleposition();
    update_status_pencontact();
    update_status_turtlevisability();
    update_status_turtleheading();
    update_status_turtlepitch();
    update_status_turtleroll();
    update_status_turtlewhich();

    g_Wanna = g_SelectedTurtle->Position;

    draw_turtles(true);

    return Unbound;
}

NODE *lturtle(NODE *)
{
    ASSERT_TURTLE_INVARIANT;

    int active_turtle = GetSelectedTurtleIndex();
    return make_intnode(active_turtle);
}

NODE *lturtles(NODE *)
{
    ASSERT_TURTLE_INVARIANT;
    return make_intnode(g_MaxTurtle);
}

NODE *lhasownpenp(NODE*)
{
    return true_or_false(g_SelectedTurtle->HasOwnPenState);
}

static COLORREF InterpolateColors(COLORREF A, COLORREF B, double Alpha)
{
    if (A == B)
    {
        return A;
    }

    // Alpha used to go from 0 -> 1.
    // The domain of each color component is only 0-255, so
    // without a loss of precision, we can change this to integral
    // math.
    const int alphaInt         = (int)(Alpha * 4096.5);
    const int oneMinusAlphaInt = 4096 - alphaInt;

    BYTE red   = (GetRValue(A) * oneMinusAlphaInt + GetRValue(B) * alphaInt) / 4096;
    BYTE green = (GetGValue(A) * oneMinusAlphaInt + GetGValue(B) * alphaInt) / 4096;
    BYTE blue  = (GetBValue(A) * oneMinusAlphaInt + GetBValue(B) * alphaInt) / 4096;

    return RGB(red, green, blue);
}

void turtlepaste(int TurtleToPaste)
{
    ASSERT_TURTLE_INVARIANT;

    POINT dest;
    if (!WorldCoordinateToScreenCoordinate(g_Turtles[TurtleToPaste].Position, dest))
    {
        return;
    }

    // If clipboard check with clipboard only
    if (TurtleToPaste == 0)
    {
        PasteFromClipboardToBitmapArray();
    }

    // only if we have something to paste
    if (g_Bitmaps[TurtleToPaste].IsValid)
    {

        // if clipboard then never leave Cut Flag true
        if (TurtleToPaste == 0)
        {
            g_Bitmaps[TurtleToPaste].IsValid = false;
        }

        HDC ScreenDC  = GetScreenDeviceContext();
        HDC TempMemDC = CreateCompatibleDC(ScreenDC);

        HBITMAP oldBitmap2 = (HBITMAP) SelectObject(
            TempMemDC,
            g_Bitmaps[TurtleToPaste].MemoryBitMap);

        if (g_SelectedTurtle->IsSprite)
        {
            // TODO: figure out how to merge this with the bounding box
            // computation logic in ibmturt()

            // Compute the sine and cosine of the heading, but add special cases
            // for the multiples of 90 degress so that we get a crisp square
            // rotation instead of a slight deviation due to the imprecision
            // of sin() and cos() functions.
            FLONUM cosine;
            FLONUM sine;

            if (g_Turtles[TurtleToPaste].Heading == 90)
            {
                cosine = 0;
                sine   = 1;
            }
            else if (g_Turtles[TurtleToPaste].Heading == 180)
            {
                cosine = -1;
                sine   = 0;
            }
            else if (g_Turtles[TurtleToPaste].Heading == 270)
            {
                cosine = 0;
                sine   = -1;
            }
            else
            {
                cosine = cos(g_Turtles[TurtleToPaste].Heading * rads_per_degree);
                sine   = sin(g_Turtles[TurtleToPaste].Heading * rads_per_degree);
            }
            
            // The location of the centerpoint (or origin) of the turtle's bitmap about which to rotate
            const FLONUM xOrigin = g_Bitmaps[TurtleToPaste].Width  / 2.0;
            const FLONUM yOrigin = g_Bitmaps[TurtleToPaste].Height / 2.0;
                
            // Compute points of the image rotated about its center.
            FLONUM x0 = X_ROTATED(-xOrigin, -yOrigin, cosine, sine);
            FLONUM y0 = Y_ROTATED(-xOrigin, -yOrigin, cosine, sine);

            FLONUM x1 = X_ROTATED(-xOrigin, yOrigin, cosine, sine);
            FLONUM y1 = Y_ROTATED(-xOrigin, yOrigin, cosine, sine);

            FLONUM x2 = X_ROTATED(xOrigin, yOrigin, cosine, sine);
            FLONUM y2 = Y_ROTATED(xOrigin, yOrigin, cosine, sine);

            FLONUM x3 = X_ROTATED(xOrigin, -yOrigin, cosine, sine);
            FLONUM y3 = Y_ROTATED(xOrigin, -yOrigin, cosine, sine);

            // Compute the bounding box.  We grow the box by one to account for rounding errors.
            const int minx = (int) ((min(x0,min(x1, min(x2,x3))) - 1) * the_zoom);
            const int miny = (int) ((min(y0,min(y1, min(y2,y3))) - 1) * the_zoom);
            const int maxx = (int) ((max(x0,max(x1, max(x2,x3))) + 1) * the_zoom);
            const int maxy = (int) ((max(y0,max(y1, max(y2,y3))) + 1) * the_zoom);

            // Figure out where on the screen window the turtle belongs.
            const int xScreenOffset = (+dest.x + xoffset) * the_zoom - GetScreenHorizontalScrollPosition();
            const int yScreenOffset = (-dest.y + yoffset) * the_zoom - GetScreenVerticalScrollPosition();

            // Now do the rotating, one pixel at a time.
            // Find the pixel that cooresponds to each point in the destination
            // rectangle to guarantee that each pixel gets covered.
            const COLORREF TRANSPARENT_COLOR = RGB(255, 255, 255);
            if (EnablePalette)
            {
                // The display has a palette, so bilinear interpolation would not work.
                for (int y = miny; y < maxy; y++)
                {
                    for (int x = minx; x < maxx; x++)
                    {
                        int sourcex = (int)((X_ROTATED(x, y, cosine, sine) / the_zoom + xOrigin));
                        int sourcey = (int)((Y_ROTATED(x, y, cosine, sine) / the_zoom + yOrigin));

                        if (0 <= sourcex && sourcex < g_Bitmaps[TurtleToPaste].Width &&
                            0 <= sourcey && sourcey < g_Bitmaps[TurtleToPaste].Height)
                        {
                            const COLORREF pixel = ::GetPixel(TempMemDC, sourcex, sourcey);
                            if (pixel != TRANSPARENT_COLOR)
                            {
                                SetPixelV(
                                    ScreenDC,
                                    x + xScreenOffset,
                                    y + yScreenOffset,
                                    pixel);
                            }
                        }
                    }
                }
            }
            else
            {
                // Use bilinear interpolation to make the picture look nice at rough angles.
                for (int y = miny; y < maxy; y++)
                {
                    for (int x = minx; x < maxx; x++)
                    {
                        FLONUM sourcex = ((X_ROTATED(x, y, cosine, sine) / the_zoom + xOrigin));
                        FLONUM sourcey = ((Y_ROTATED(x, y, cosine, sine) / the_zoom + yOrigin));

                        if (0 <= sourcex && 0 <= sourcey)
                        {
                            if (sourcex < g_Bitmaps[TurtleToPaste].Width  - 1 &&
                                sourcey < g_Bitmaps[TurtleToPaste].Height - 1)
                            {
                                // full bilinear interpolation is necessary
                                FLONUM xFraction = modf(sourcex, &sourcex);
                                FLONUM yFraction = modf(sourcey, &sourcey);

                                COLORREF pixelx0y0 = ::GetPixel(TempMemDC, sourcex,     sourcey);
                                COLORREF pixelx0y1 = ::GetPixel(TempMemDC, sourcex,     sourcey + 1);
                                COLORREF pixelx1y0 = ::GetPixel(TempMemDC, sourcex + 1, sourcey);
                                COLORREF pixelx1y1 = ::GetPixel(TempMemDC, sourcex + 1, sourcey + 1);

                                if (pixelx0y0 == pixelx0y1 &&
                                    pixelx0y0 == pixelx1y0 &&
                                    pixelx0y0 == pixelx1y1)
                                {
                                    // If all of the adjacent pixels are the same, then
                                    // bilinear interpolation is unnecesasry.  For a typical
                                    // sprite image, this optimization yeilds a 10% speed
                                    // improvement.
                                    if (pixelx0y0 != TRANSPARENT_COLOR)
                                    {
                                        SetPixelV(
                                            ScreenDC,
                                            x + xScreenOffset,
                                            y + yScreenOffset,
                                            pixelx0y0);
                                    }
                                }
                                else
                                {
                                    // get the screen's value for each of the transparent pixels
                                    const COLORREF screenPixel = GetPixel(ScreenDC, x + xScreenOffset, y + yScreenOffset);

                                    if (pixelx0y0 == TRANSPARENT_COLOR)
                                    {
                                        pixelx0y0 = screenPixel;
                                    }
                                    if (pixelx1y0 == TRANSPARENT_COLOR)
                                    {
                                        pixelx1y0 = screenPixel;
                                    }
                                    if (pixelx0y1 == TRANSPARENT_COLOR)
                                    {
                                        pixelx0y1 = screenPixel;
                                    }
                                    if (pixelx1y1 == TRANSPARENT_COLOR)
                                    {
                                        pixelx1y1 = screenPixel;
                                    }

                                    // interpolate in the X direction, then the Y direction
                                    COLORREF pixely0 = InterpolateColors(pixelx0y0, pixelx1y0, xFraction);
                                    COLORREF pixely1 = InterpolateColors(pixelx0y1, pixelx1y1, xFraction);
                                    COLORREF pixel   = InterpolateColors(pixely0, pixely1, yFraction);

                                    SetPixelV(
                                        ScreenDC,
                                        x + xScreenOffset,
                                        y + yScreenOffset,
                                        pixel);
                                }
                            }
                            else if (sourcex < g_Bitmaps[TurtleToPaste].Width &&
                                     sourcey < g_Bitmaps[TurtleToPaste].Height - 1)
                            {
                                // We're at the right edge, so linear interpolation in Y is sufficient.
                                FLONUM yFraction = modf(sourcey, &sourcey);

                                COLORREF pixely0 = ::GetPixel(TempMemDC, g_Bitmaps[TurtleToPaste].Width - 1, sourcey);
                                COLORREF pixely1 = ::GetPixel(TempMemDC, g_Bitmaps[TurtleToPaste].Width - 1, sourcey + 1);

                                // get the screen's value for each of the transparent pixels
                                const COLORREF screenPixel = GetPixel(ScreenDC, x + xScreenOffset, y + yScreenOffset);

                                if (pixely0 == TRANSPARENT_COLOR)
                                {
                                    pixely0 = screenPixel;
                                }
                                if (pixely1 == TRANSPARENT_COLOR)
                                {
                                    pixely1 = screenPixel;
                                }

                                // interpolate in the Y direction
                                COLORREF pixel = InterpolateColors(pixely0, pixely1, yFraction);
                                SetPixelV(
                                    ScreenDC,
                                    x + xScreenOffset,
                                    y + yScreenOffset,
                                    pixel);
                            }
                            else if (sourcex < g_Bitmaps[TurtleToPaste].Width - 1 &&
                                     sourcey < g_Bitmaps[TurtleToPaste].Height)
                            {
                                // We're at the bottom edge, so linear interpolation in X is sufficient.
                                FLONUM xFraction = modf(sourcex, &sourcex);

                                COLORREF pixelx0 = ::GetPixel(TempMemDC, sourcex,     g_Bitmaps[TurtleToPaste].Height - 1);
                                COLORREF pixelx1 = ::GetPixel(TempMemDC, sourcex + 1, g_Bitmaps[TurtleToPaste].Height - 1);

                                // get the screen's value for each of the transparent pixels
                                const COLORREF screenPixel = GetPixel(ScreenDC, x + xScreenOffset, y + yScreenOffset);

                                if (pixelx0 == TRANSPARENT_COLOR)
                                {
                                    pixelx0 = screenPixel;
                                }
                                if (pixelx1 == TRANSPARENT_COLOR)
                                {
                                    pixelx1 = screenPixel;
                                }

                                // interpolate in the X direction
                                COLORREF pixel = InterpolateColors(pixelx0, pixelx1, xFraction);
                                SetPixelV(
                                    ScreenDC,
                                    x + xScreenOffset,
                                    y + yScreenOffset,
                                    pixel);
                            }
                            else if (sourcex < g_Bitmaps[TurtleToPaste].Width &&
                                     sourcey < g_Bitmaps[TurtleToPaste].Height)
                            {
                                // we're at the corner, so we don't need any interpolation
                                const COLORREF pixel = ::GetPixel(TempMemDC, sourcex, sourcey);
                                if (pixel != TRANSPARENT_COLOR)
                                {
                                    SetPixelV(
                                        ScreenDC,
                                        x + xScreenOffset,
                                        y + yScreenOffset,
                                        pixel);
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            //screen
            if (zoom_flag)
            {
                SetMapMode(ScreenDC, MM_ANISOTROPIC);
                SetWindowOrgEx(ScreenDC, 0, 0, 0);
                SetWindowExtEx(ScreenDC, BitMapWidth, BitMapHeight, 0);
                SetViewportOrgEx(ScreenDC, 0, 0, 0);
                SetViewportExtEx(ScreenDC, (int) (BitMapWidth * the_zoom), (int) (BitMapHeight * the_zoom), 0);

                BitBlt(
                    ScreenDC,
                    +dest.x - GetScreenHorizontalScrollPosition() / the_zoom + xoffset,
                    -dest.y - GetScreenVerticalScrollPosition() / the_zoom + yoffset + LL - g_Bitmaps[TurtleToPaste].Height,
                    g_Bitmaps[TurtleToPaste].Width,
                    g_Bitmaps[TurtleToPaste].Height,
                    TempMemDC,
                    0,
                    0,
                    g_Turtles[TurtleToPaste].BitmapRasterMode);
            }
            else
            {
                BitBlt(
                    ScreenDC,
                    +dest.x - GetScreenHorizontalScrollPosition() + xoffset,
                    -dest.y - GetScreenVerticalScrollPosition() + yoffset + LL - g_Bitmaps[TurtleToPaste].Height,
                    g_Bitmaps[TurtleToPaste].Width,
                    g_Bitmaps[TurtleToPaste].Height,
                    TempMemDC,
                    0,
                    0,
                    g_Turtles[TurtleToPaste].BitmapRasterMode);
            }
        }

        SelectObject(TempMemDC, oldBitmap2);
        DeleteDC(TempMemDC);
    }
    else
    {
        // notify the user that this turtle has no picture
        char errorMessage[255];
        sprintf(errorMessage, LOCALIZED_ERROR_TURTLEHASNOPICTURE, TurtleToPaste);
        ShowErrorMessage(errorMessage);

        // un-bitmap this turtle to prevent future errors
        g_Turtles[TurtleToPaste].BitmapRasterMode = 0;
        g_Turtles[TurtleToPaste].IsSprite         = false;
    }
}

NODE *lscrollx(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    // get args and scroll the scroller
    NODE *args = numeric_arg(arg);

    if (NOT_THROWING)
    {
        int delta = getint(args);

        if (delta == 0)
        {
            RECT screenRect;
            GetClientRect(GetScreenWindow(), &screenRect);

            SetScreenScrollPosition(
                ((BitMapWidth * the_zoom) / 2) - (0.5 * screenRect.right),
                GetScreenVerticalScrollPosition());
        }
        else
        {
            SetScreenScrollPosition(
                GetScreenHorizontalScrollPosition() + delta,
                GetScreenVerticalScrollPosition());
        }
    }

    return Unbound;
}

NODE *lscrolly(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    // get args and scroll the scroller
    NODE * args = numeric_arg(arg);

    if (NOT_THROWING)
    {
        int delta = getint(args);

        if (delta == 0)
        {
            RECT screenRect;
            GetClientRect(GetScreenWindow(), &screenRect);

            SetScreenScrollPosition(
                GetScreenHorizontalScrollPosition(),
                ((BitMapHeight * the_zoom)/ 2) - (0.5 * screenRect.bottom));
        }
        else
        {
            SetScreenScrollPosition(
                GetScreenHorizontalScrollPosition(),
                GetScreenVerticalScrollPosition() + delta);
        }
    }

    return Unbound;
}

NODE *lsetfocus(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    CStringPrintedNode windowCaption(car(arg));

    HWND window;

    if (0 == stricmp("FMSLogo", windowCaption) ||
        0 == stricmp("MSWLogo Screen", windowCaption) ||
        0 == stricmp("FMSLogo Screen", windowCaption))
    {
        // special-case: set the focus on the screen
        window = GetScreenWindow();
    }
    else
    {
        // get handle to Window with arg as Caption
        window = FindWindow(NULL, windowCaption);
    }

    // Now set focus to it, if it exists
    if (window != NULL)
    {
        ::SetFocus(window);
    }

    GiveFocusToEditbox = false;

    return Unbound;
}

NODE *lgetfocus(NODE *)
{
    ASSERT_TURTLE_INVARIANT;

    char textbuf[MAX_BUFFER_SIZE];
    memset(textbuf, 0, MAX_BUFFER_SIZE);

    // Get handle to active window
    HWND TempH = GetActiveWindow();

    // It better exist, get its caption
    if (TempH != NULL)
    {
        ::GetWindowText(TempH, textbuf, MAX_BUFFER_SIZE);
    }

    GiveFocusToEditbox = false;

    // Return caption as a list
    NODE * arg = make_strnode(textbuf);
    NODE * val = arg; // parser(arg, false);
    return val;
}

NODE *lwindowset(NODE *args)
{
    CStringPrintedNode caption(car(args));

    int mode = getint(nonnegative_int_arg(cdr(args)));

    if (NOT_THROWING)
    {
        HWND window;

        // For compatibility with other translations of FMSLogo (with
        // possibly alternate names for the commander), we always treat
        // the window "commander" as meaning the commander.
        if (0 == stricmp(caption, "commander"))
        {
            // For backward compatibility with MSWLogo, we must undock
            // the commander into its own window so that window operations
            // on it have the expected effect.
            UndockCommanderWindow();

            window = GetCommanderWindow();
        }
        else
        {
            // get handle to Window with arg as Caption
            window = FindWindow(NULL, caption);
        }

        // if it exists set its state it.
        if (window != NULL)
        {
            ShowWindow(window, mode);
            GiveFocusToEditbox = false;
        }
    }

    return Unbound;
}

void ibm_clear_screen(void)
{
    ASSERT_TURTLE_INVARIANT;

    HBRUSH tempBrush = ::CreateBrushIndirect(&ScreenBrush);
    if (tempBrush != NULL)
    {
        // memory
        HDC     memoryDC  = GetMemoryDeviceContext();
        HBITMAP oldBitmap = (HBITMAP) ::SelectObject(memoryDC, MemoryBitMap);

        ::FillRect(memoryDC, &FullRect, tempBrush);

        ::SetBkColor(memoryDC, scolor);
        ::SetBkMode(memoryDC, TRANSPARENT);

        ::SelectObject(memoryDC, oldBitmap);

        ::DeleteObject(tempBrush);
    }

    InvalidateRect(GetScreenWindow(), NULL, FALSE);
}


static
int CALLBACK
FindFont(
    const LOGFONT    *  LogFont,     // pointer to logical-font data
    const TEXTMETRIC *  TextMetric,  // pointer to physical-font data
    unsigned long       FontType,    // type of font
    LPARAM              lParam       // address of application-defined data
    )
{
    struct font_find_t * context = reinterpret_cast<struct font_find_t *>(lParam);

    // check for a match
    if (stricmp(context->fontname, LogFont->lfFaceName) == 0)
    {
        // take a copy, flag one was found and return
        FontRec = *LogFont;
        context->found = true;
        return 0;  // stop enumerating fonts
    }

    return 1; // keep enumerating fonts
}


static
int CALLBACK
GatherFontFaces(
    const LOGFONT    *  LogFont,     // pointer to logical-font data
    const TEXTMETRIC *  TextMetric,  // pointer to physical-font data
    unsigned long       FontType,    // type of font
    LPARAM              lParam       // address of application-defined data
    )
{
    CAppendableList * fontfaces = reinterpret_cast<CAppendableList *>(lParam);

    // Create a new node for this font face name.
    // By convention font face names are a list containing a string.
    NODE * fontFaceNode = cons_list(make_strnode(LogFont->lfFaceName));

    // Append the font face name to the end of the list.
    fontfaces->AppendElement(fontFaceNode);

    return 1; // keep enumerating fonts
}


static
int CALLBACK
PrintFont(
    const LOGFONT    * LogFont,     // pointer to logical-font data
    const TEXTMETRIC * TextMetric,  // pointer to physical-font data
    unsigned long      FontType,    // type of font
    LPARAM             lParam       // address of application-defined data
    )
{
    printfx("[%s]", LogFont->lfFaceName);
    return 1; // keep enumerating fonts
}


static
void
setfont(
    const char *fontname
    )
{
    HDC hdc = GetDC(::GetFocus());

    // set the font name that we're looking for (FontRec will get filled if found)
    struct font_find_t context; 
    context.found    = false;
    context.fontname = fontname;
    EnumFontFamilies(
        hdc,
        NULL,
        FindFont,
        reinterpret_cast<LPARAM>(&context));

    if (!context.found)
    {
        // The font wasn't found.  Print all available fonts
        printfx(
            LOCALIZED_ERROR_FONTNOTFOUND,
            fontname);

        EnumFontFamilies(hdc, NULL, PrintFont, 0L);
    }

    ReleaseDC(::GetFocus(), hdc);
}

bool
HtmlHelpInitialize(
    void
    )
{
    if (g_HtmlHelpFunc != NULL)
    {
        // The HTML Help subsystem has already been initialized
        return true;
    }

    // Load the ActiveX control
    g_HtmlHelpLib = ::LoadLibrary("hhctrl.ocx");
    if (g_HtmlHelpLib == NULL) 
    {
        ::MessageBox(
            GetDesktopWindow(), 
            LOCALIZED_ERROR_HHCTRLNOTLOADED, 
            LOCALIZED_ERROR,
            MB_OK);
        return false;
    }

    // Get the HtmlHelpA() function pointer
    g_HtmlHelpFunc = (HTMLHELPFUNC) ::GetProcAddress(
        g_HtmlHelpLib, 
        ATOM_HTMLHELP_API_ANSI);
    if (g_HtmlHelpFunc == NULL)
    {
        ::MessageBox(
            GetDesktopWindow(),
            LOCALIZED_ERROR_HHCTRLATOMNOTFOUND,
            LOCALIZED_ERROR,
            MB_OK);

        HtmlHelpUninitialize();
        return false;
    }

    // success
    return true;
}

void
HtmlHelpUninitialize(
    void
    )
{
    if (g_HtmlHelpFunc != NULL)
    {
        g_HtmlHelpFunc(NULL, NULL, HH_CLOSE_ALL, 0);
        g_HtmlHelpFunc = NULL;
    }

    if (g_HtmlHelpLib != NULL)
    {
        ::FreeLibrary(g_HtmlHelpLib);
        g_HtmlHelpLib = NULL;
    }
}



// if arg is NULL then we jump to index
void do_help(const char *arg)
{
    if (!HtmlHelpInitialize())
    {
        return;
    }

    g_HtmlHelpFunc(
        GetDesktopWindow(), 
        szHelpFileName,
        HH_DISPLAY_TOPIC,
        0);

    HH_AKLINK aklink = {0};
    aklink.cbStruct     = sizeof aklink;
    aklink.fReserved    = FALSE;
    aklink.pszKeywords  = arg;
    aklink.pszUrl       = NULL;
    aklink.pszMsgText   = NULL;
    aklink.pszMsgTitle  = NULL;
    aklink.pszWindow    = "Main";
    aklink.fIndexOnFail = TRUE;

    g_HtmlHelpFunc(
        GetDesktopWindow(), 
        szHelpFileName,
        HH_KEYWORD_LOOKUP, 
        (DWORD) &aklink);
}

NODE *lhelp(NODE *arg)
{
    // if arg then pass to do_help
    if (arg != NIL)
    {
        CStringPrintedNode item(car(arg));
        do_help(item);
    }
    else
    {
        // else just pop up help
        do_help(NULL);
    }

    return Unbound;
}

NODE *lwinhelp(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    CStringPrintedNode textbuf(car(arg));

    // if 2nd arg then pass to winhelp
    if (cdr(arg) != NIL)
    {
        CStringPrintedNode textbuf2(car(cdr(arg)));

        WinHelp(
            GetMainWindow(),
            textbuf,
            HELP_PARTIALKEY,
            reinterpret_cast<DWORD>(textbuf2.GetString()));
    }
    else
    {
        // else just give help on file (arg 1)
        WinHelp(GetMainWindow(), textbuf, HELP_INDEX, 0L);
    }

    return Unbound;
}

NODE *lfontfacenames(NODE *arg)
{
    HDC hdc = GetDC(::GetFocus());

    CAppendableList fontFaceNames; 

    EnumFontFamilies(
        hdc,
        NULL,
        GatherFontFaces,
        reinterpret_cast<LPARAM>(&fontFaceNames));

    ReleaseDC(::GetFocus(), hdc);

    return fontFaceNames.GetList();
}

NODE *lsetlabelfont(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    NODE *args = list_arg(arg);
    if (NOT_THROWING)
    {
        if (args == NIL)
        {
            // no font name was given.
            setfont("");
            return Unbound;
        }

        CStringPrintedNode textbuf(car(args));

        // Get the FontRec filled with a match to textbuf
        setfont(textbuf);

        // now fill in the rest of the (optional) fields if given
        if (cdr(args) != NIL)
        {
            FontRec.lfHeight = int_arg(args = cdr(args));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfWidth = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfOrientation = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfWeight = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfItalic = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfUnderline = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfStrikeOut = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfCharSet = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfOutPrecision = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfClipPrecision = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfQuality = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfPitchAndFamily = getint(nonnegative_int_arg(args = cdr(args)));
        }
    }

    return Unbound;
}

NODE *llabelfont(NODE *)
{
    ASSERT_TURTLE_INVARIANT;

    // put the Font name in a list
    NODE *targ = make_strnode(FontRec.lfFaceName);
    NODE *val = parser(targ, false);

    // now return the whole thing as a list

    return
        cons(val,
        cons(make_intnode((FIXNUM) FontRec.lfHeight),
        cons(make_intnode((FIXNUM) FontRec.lfWidth),
        cons(make_intnode((FIXNUM) FontRec.lfOrientation),
        cons(make_intnode((FIXNUM) FontRec.lfWeight),
        cons(make_intnode((FIXNUM) FontRec.lfItalic),
        cons(make_intnode((FIXNUM) FontRec.lfUnderline),
        cons(make_intnode((FIXNUM) FontRec.lfStrikeOut),
        cons(make_intnode((FIXNUM) FontRec.lfCharSet),
        cons(make_intnode((FIXNUM) FontRec.lfOutPrecision),
        cons(make_intnode((FIXNUM) FontRec.lfClipPrecision),
        cons(make_intnode((FIXNUM) FontRec.lfQuality),
        cons(make_intnode((FIXNUM) FontRec.lfPitchAndFamily),
        NIL)))))))))))));
}

NODE *lmachine(NODE *)
{
    ASSERT_TURTLE_INVARIANT;


    // Get the desktop dimensions
    HDC tempDC = GetDC(0);

    int ScreenWidth  = GetDeviceCaps(tempDC, HORZRES);
    int ScreenHeight = GetDeviceCaps(tempDC, VERTRES);

    ReleaseDC(0, tempDC);


    // Get the working area dimensions
    int workingAreaWidth;
    int workingAreaHeight;
    GetWorkingAreaDimensions(workingAreaWidth, workingAreaHeight);


    // Get FMSLogo's window dimensions
    RECT wrect;
    GetWindowRect(GetMainWindow(), &wrect);

    // return a list with system specific information
    return
        cons(make_intnode((FIXNUM) 1),
        cons(make_intnode((FIXNUM) 32),
        cons(make_intnode((FIXNUM) BitMapWidth),
        cons(make_intnode((FIXNUM) BitMapHeight),
        cons(make_intnode((FIXNUM) (EnablePalette ? 1 : 0)),
        cons(make_intnode((FIXNUM) (LOBYTE(LOWORD(GetVersion())))),
        cons(make_intnode((FIXNUM) (HIBYTE(LOWORD(GetVersion())))),
        cons(make_intnode((FIXNUM) workingAreaWidth),
        cons(make_intnode((FIXNUM) workingAreaHeight),
        cons(make_intnode((FIXNUM) ScreenWidth),
        cons(make_intnode((FIXNUM) ScreenHeight),
        cons(make_intnode((FIXNUM) (wrect.right - wrect.left)),
        cons(make_intnode((FIXNUM) (wrect.bottom - wrect.top)),
        NIL)))))))))))));
}

SIZE labelsize(const char *s)
{
    ASSERT_TURTLE_INVARIANT;

    SIZE size = {0};

    HDC screen = GetScreenDeviceContext();

    // get a handle to the label's font
    HFONT tempFont = CreateFontIndirect(&FontRec);
    if (tempFont != NULL)
    {
        HFONT oldFont = (HFONT) SelectObject(screen, tempFont);

        GetTextExtentPoint(screen, s, strlen(s), &size);

        // restore the original font
        SelectObject(screen, oldFont);

        DeleteObject(tempFont);
    }

    return size;
}

void label(const char *s)
{
    ASSERT_TURTLE_INVARIANT;

    POINT dest;
    if (!WorldCoordinateToScreenCoordinate(g_SelectedTurtle->Position, dest))
    {
        return;
    }

    // memory
    HDC     MemDC     = GetMemoryDeviceContext();
    HBITMAP oldBitmap = (HBITMAP) SelectObject(MemDC, MemoryBitMap);

    if (EnablePalette)
    {
        OldPalette = SelectPalette(MemDC, ThePalette, FALSE);
        RealizePalette(MemDC);
    }

    SetBkColor(MemDC, scolor);
    SetBkMode(MemDC, TRANSPARENT);

    if (GetPenStateForSelectedTurtle().IsErasing)
    {
        SetTextColor(MemDC, scolor);
    }
    else
    {
        SetTextColor(MemDC, pcolor);
    }

    FontRec.lfEscapement = (360.0 - (g_SelectedTurtle->Heading - 90.0)) * 10;
    HFONT tempFont = CreateFontIndirect(&FontRec);
    HFONT oldFont = (HFONT) SelectObject(MemDC, tempFont);

    TextOut(
        MemDC,
        +dest.x + xoffset,
        -dest.y + yoffset,
        s,
        strlen(s));

    if (EnablePalette)
    {
        SelectPalette(MemDC, OldPalette, FALSE);
    }

    SelectObject(MemDC, oldFont);
    SelectObject(MemDC, oldBitmap);


    // screen
    HDC ScreenDC = GetScreenDeviceContext();

    if (EnablePalette)
    {
        OldPalette = SelectPalette(ScreenDC, ThePalette, FALSE);
        RealizePalette(ScreenDC);
    }

    SetBkColor(ScreenDC, scolor);
    SetBkMode(ScreenDC, TRANSPARENT);

    if (GetPenStateForSelectedTurtle().IsErasing)
    {
        SetTextColor(ScreenDC, scolor);
    }
    else
    {
        SetTextColor(ScreenDC, pcolor);
    }

    oldFont = (HFONT) SelectObject(ScreenDC, tempFont);

    if (zoom_flag)
    {
        // no need to erase, we're just drawing over it
        InvalidateRect(GetScreenWindow(), NULL, FALSE);
    }
    else
    {
        TextOut(
            ScreenDC,
            +dest.x - GetScreenHorizontalScrollPosition() + xoffset,
            -dest.y - GetScreenVerticalScrollPosition()   + yoffset,
            s,
            strlen(s));
    }

    SelectObject(ScreenDC, oldFont);

    if (EnablePalette)
    {
        SelectPalette(ScreenDC, OldPalette, FALSE);
    }

    DeleteObject(tempFont);
}

void MyMessageScan()
{
    // depending on yield flag check for messages
    if (yield_flag)
    {
        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}


void init_videomode()
{
    // Get video mode parameters
    HDC screenDeviceContext = GetDC(0);
    if (screenDeviceContext)
    {
        int bitsPerPixel = GetDeviceCaps(screenDeviceContext, BITSPIXEL);
        int totalPlanes  = GetDeviceCaps(screenDeviceContext, PLANES);

        MaxColors = pow(2.0, bitsPerPixel + totalPlanes);

        ReleaseDC(0, screenDeviceContext);
    }

    // Get Dialog Units for Controls
    BaseUnitsx = LOWORD(GetDialogBaseUnits());
    BaseUnitsy = HIWORD(GetDialogBaseUnits());

    // check if a palette exists
    HDC screen = CreateDC("DISPLAY", NULL, NULL, NULL);
    if (screen != NULL)
    {
        if ((GetDeviceCaps(screen, RASTERCAPS) & RC_PALETTE) == 0)
        {
            EnablePalette = false;
        }
        else
        {
            EnablePalette = true;
        }

        DeleteDC(screen);
    }

    /* If palette then build one */
    if (EnablePalette)
    {
        MyLogPalette = (LPLOGPALETTE) new char[sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * MaxColors];
        MyLogPalette->palVersion = 0x300;
        MyLogPalette->palNumEntries = 2;

        MyLogPalette->palPalEntry[0].peRed = 0;
        MyLogPalette->palPalEntry[0].peGreen = 0;
        MyLogPalette->palPalEntry[0].peBlue = 0;
        MyLogPalette->palPalEntry[0].peFlags = 0;

        MyLogPalette->palPalEntry[1].peRed = 255;
        MyLogPalette->palPalEntry[1].peGreen = 255;
        MyLogPalette->palPalEntry[1].peBlue = 255;
        MyLogPalette->palPalEntry[1].peFlags = 0;

        ThePalette = CreatePalette(MyLogPalette);
    }
}

void init_bitmaps()
{
    // allocate the array of bitmaps
    g_BitmapsLimit   = 1;
    g_Bitmaps        = (CUTMAP *) calloc(sizeof(*g_Bitmaps), g_BitmapsLimit);
    g_SelectedBitmap = &g_Bitmaps[0];
}

void uninit_bitmaps()
{
    // Note Bitmap index 0 belongs to clipboard
    for (CUTMAP* bmp = g_Bitmaps + 1;
         bmp < g_Bitmaps + g_BitmapsLimit;
         bmp++)
    {
        if (bmp->IsValid)
        {
            DeleteObject(bmp->MemoryBitMap);
        }
    }

    free(g_Bitmaps);
}

void init_penstate()
{
    g_PenState.Color.red   = 0x00;
    g_PenState.Color.green = 0x00;
    g_PenState.Color.blue  = 0x00;
    g_PenState.Width     = 1;
    g_PenState.Mode      = COPY_PUT;
    g_PenState.IsErasing = false;
}


void init_turtles()
{
    g_TurtlesLimit = 1;
    g_MaxTurtle    = 0;
    g_Turtles      = (Turtle *) calloc(sizeof(*g_Turtles), g_TurtlesLimit);
    g_SelectedTurtle = &g_Turtles[g_MaxTurtle];

    InitializeTurtle(g_SelectedTurtle);

    // init the special turtles
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_LOCATION].IsSpecial   = true;
    g_SpecialTurtles[SPECIAL_TURTLE_LIGHT_LOCATION].IsSpecial = true;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].IsSpecial   = true;
}

void uninit_turtles()
{
    free(g_Turtles);
}

void exit_program(void)
{
    if (is_executing())
    {
        IsTimeToHalt = true;
    }
    IsTimeToExit = true;
}
