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

#include "allwind.h"
#include "htmlhelp.h"

extern bool bIndexMode;

extern int gbmBmpToGif(const char *BmpName, const char *GifName);
extern int gbmGifToBmp(const char *GifName, const char *BmpName);

int iDelay;
int bAppendMode;
int iLoop;
int iTrans;

HTMLHELPFUNC g_HtmlHelpFunc;
HMODULE      g_HtmlHelpLib;

CUTMAP * g_SelectedBitmap;
CUTMAP * g_Bitmaps;
int      g_BitmapsLimit;

struct font_find_t
{
    const char *fontname;
    bool        found;
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

    ERR_TYPES status = MainWindowx->DumpBitmapFile(TempBmpName, iMaxColorDepth);
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
    unlink(TempBmpName);

    return status;
}


static
COLORREF
GetRGBorIndexColor(
    NODE* args
    )
{
    COLORREF color = (COLORREF) -1;

    // get args
    if (is_list(car(args)))
    {
        NODE * arg = pos_int_vector_3_arg(args);

        if (NOT_THROWING)
        {
            const int red   = numeric_node_to_fixnum(car(arg));
            const int green = numeric_node_to_fixnum(cadr(arg));
            const int blue  = numeric_node_to_fixnum(cadr(cdr(arg)));

            if (EnablePalette)
            {
                color = LoadColor(red, green, blue);
            }
            else
            {
                color = RGB(red, green, blue);
            }
        }

        bIndexMode = false;
    }
    else
    {
        NODE * cnode = numeric_arg(args);

        if (NOT_THROWING)
        {
            const int color_index = numeric_node_to_fixnum(cnode) % 16;

            if (EnablePalette)
            {
                color = LoadColor(
                    GetRValue(colortable[color_index]),
                    GetGValue(colortable[color_index]),
                    GetBValue(colortable[color_index]));
            }
            else
            {
                color = colortable[color_index];
            }
        }

        bIndexMode = true;
    }

    return color;
}

NODE *lgifsave(NODE *args)
{
    // same as BITMAP-SAVE but gets file name from logo command
    char gifFileName[MAX_BUFFER_SIZE];
    cnv_strnode_string(gifFileName, args);

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
                                        iTrans = GetRGBorIndexColor(cdr(cdr(cdr(cdr(cdr(args))))));
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
    char bmpFileName[MAX_BUFFER_SIZE];
    cnv_strnode_string(bmpFileName, args);
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

    ERR_TYPES status = MainWindowx->DumpBitmapFile(bmpFileName, iMaxBitCount);
    if (status != SUCCESS)
    {
        err_logo(status, NIL);
        return Unbound;
    }

    return Unbound;
}

ERR_TYPES
gifload_helper(
    const char * GifFileName,
    DWORD      & dwPixelWidth,
    DWORD      & dwPixelHeight
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
    ERR_TYPES status = MainWindowx->LoadBitmapFile(
        TempBmpName,
        dwPixelWidth,
        dwPixelHeight);

    // cleanup
    unlink(TempBmpName);
    return status;
}

NODE *lgifload(NODE *arg)
{
    char gifFileName[MAX_BUFFER_SIZE];
    cnv_strnode_string(gifFileName, arg);
    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    DWORD dwPixelWidth = 1;
    DWORD dwPixelHeight = 1;
    ERR_TYPES status = gifload_helper(gifFileName, dwPixelWidth, dwPixelHeight);
    if (status != SUCCESS)
    {
        err_logo(status, NIL);
        return Unbound;
    }

    return Unbound;
}

NODE *lgifsize(NODE *args)
{
    char gifFileName[MAX_BUFFER_SIZE];
    cnv_strnode_string(gifFileName, args);
    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    DWORD dwPixelWidth = 0;
    DWORD dwPixelHeight = 0;
    ERR_TYPES status = gifload_helper(gifFileName, dwPixelWidth, dwPixelHeight);
    if (status != SUCCESS)
    {
        err_logo(status, NIL);
        return Unbound;
    }

    return cons_list(
        make_intnode((FIXNUM) dwPixelWidth),
        make_intnode((FIXNUM) dwPixelHeight));
}

NODE *lbitload(NODE *arg)
{
    // same as BITMAP-LOAD except callable from logo command
    char bitmapFileName[MAX_BUFFER_SIZE];
    cnv_strnode_string(bitmapFileName, arg);
    if (stopping_flag == THROWING)
    {
        return Unbound;
    }


    DWORD dwPixelWidth = 1;
    DWORD dwPixelHeight = 1;
    ERR_TYPES status = MainWindowx->LoadBitmapFile(
        bitmapFileName,
        dwPixelWidth,
        dwPixelHeight);
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
    char bitmapFileName[MAX_BUFFER_SIZE];
    cnv_strnode_string(bitmapFileName, arg);
    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    DWORD dwPixelWidth = 0;
    DWORD dwPixelHeight = 0;
    ERR_TYPES status = MainWindowx->LoadBitmapFile(bitmapFileName, dwPixelWidth, dwPixelHeight);
    if (status != SUCCESS)
    {
        err_logo(status, NIL);
        return Unbound;
    }

    return cons_list(
        make_intnode((FIXNUM) dwPixelWidth),
        make_intnode((FIXNUM) dwPixelHeight));
}

NODE *lbitsize(NODE *)
{
    BITMAP temp;
    temp.bmWidth  = 0;
    temp.bmHeight = 0;

    if (ClipboardIsSelectedBitmap())
    {
        // The selected bitmap is whatever is on the clipboard

        ::OpenClipboard(MainWindowx->HWindow);

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
// turtle on the 2D screen.
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



NODE *lsetpixel(NODE *args)
{
    ASSERT_TURTLE_INVARIANT;

    POINT dest;
    if (!WorldCoordinateToScreenCoordinate(g_SelectedTurtle->Position, dest))
    {
        return Unbound;
    }

    // get args
    COLORREF color = GetRGBorIndexColor(args);

    if (NOT_THROWING)
    {
        // memory
        HDC MemDC = MainWindowx->ScreenWindow->GetMemoryDeviceContext();

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
        HDC ScreenDC = MainWindowx->ScreenWindow->GetScreenDeviceContext();

        draw_turtle(false);

        HPALETTE oldPalette2;
        if (EnablePalette)
        {
            oldPalette2 = SelectPalette(ScreenDC, ThePalette, FALSE);
            RealizePalette(ScreenDC);
        }

        if (zoom_flag)
        {
            TRect temprect;

            SetRect(
                &temprect,
                (+dest.x - MainWindowx->ScreenWindow->Scroller->XPos / the_zoom + xoffset) * the_zoom,
                (-dest.y - MainWindowx->ScreenWindow->Scroller->YPos / the_zoom + yoffset) * the_zoom,
                (+dest.x - MainWindowx->ScreenWindow->Scroller->XPos / the_zoom + xoffset) * the_zoom,
                (-dest.y - MainWindowx->ScreenWindow->Scroller->YPos / the_zoom + yoffset) * the_zoom);

            temprect.Inflate(1+the_zoom,1+the_zoom);

            MainWindowx->ScreenWindow->InvalidateRect(temprect, false);
        }
        else
        {
            SetPixel(
                ScreenDC,
                +dest.x - MainWindowx->ScreenWindow->Scroller->XPos + xoffset,
                -dest.y - MainWindowx->ScreenWindow->Scroller->YPos + yoffset,
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
    HDC MemDC = MainWindowx->ScreenWindow->GetMemoryDeviceContext();
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
    HDC MemDC = MainWindowx->ScreenWindow->GetMemoryDeviceContext();
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
    HDC MemDC = MainWindowx->ScreenWindow->GetMemoryDeviceContext();

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

    MainWindowx->ScreenWindow->Invalidate(true);

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
    if (NOT_THROWING)
    {
        if (EnablePalette)
        {
            DeleteObject(ThePalette);

            MyLogPalette->palNumEntries = 2;

            update_status_paletteuse();

            ThePalette = CreatePalette(MyLogPalette);

            ::InvalidateRect(MainWindowx->HWindow, NULL, TRUE);
        }
    }

    return Unbound;
}

NODE *lstatus(NODE *)
{
    ASSERT_TURTLE_INVARIANT;

    MainWindowx->MyPopupStatus();
    return Unbound;
}

NODE *lnostatus(NODE *)
{
    MainWindowx->MyPopupStatusKill();
    return Unbound;
}


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

    if (the_zoom != 1.0)
    {
        MainWindowx->ScreenWindow->Scroller->TrackMode = FALSE;
    }
    else
    {
        MainWindowx->ScreenWindow->Scroller->TrackMode = TRUE;
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

        TScreenWindow * const screen = MainWindowx->ScreenWindow;

        screen->AdjustScrollPositionToZoomFactor(NewZoomFactor);

        // hide turtle while we do this
        draw_turtle(false);

        UpdateZoomControlFlag();

        draw_turtle(true);

        // paint
        screen->Invalidate(true);
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
    int cutWidth = getint(pos_int_arg(arg));
    int cutHeight = getint(pos_int_arg(cdr(arg)));

    if (NOT_THROWING)
    {
        // only do the blit if a non-zero area was specified
        if (cutWidth != 0 && cutHeight != 0)
        {
            HBRUSH fillBrush = CreateBrushIndirect(&FloodBrush);

            TScreenWindow * const screen = MainWindowx->ScreenWindow;

            // memory
            HDC memDC = screen->GetMemoryDeviceContext();
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
                screen->Invalidate(false);
            }
            else
            {
                // Shift the coordinates of the memory rectange by how
                // much the screen is scrolled to get the screen coordinates.
                const UINT scrollerX = screen->Scroller->XPos;
                const UINT scrollerY = screen->Scroller->YPos;

                RECT screenRect;
                screenRect.left   = memoryRect.left   - scrollerX;
                screenRect.right  = memoryRect.right  - scrollerX;
                screenRect.top    = memoryRect.top    - scrollerY;
                screenRect.bottom = memoryRect.bottom - scrollerY;

                // Invalidate the portion of the screen that corresponds
                // to the region of memory that we filled.
                // Ever since we stopped calling GetDC() and ReleaseDC()
                // to get the screen DC, simply calling FillRect() on the
                // screen causes repainting problems.
                // I suspect that calling ReleaseDC() implicitly invalidated
                // the screen, which may be why it was so much slower.
                InvalidateRect(screen->HWindow, &screenRect, false);
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
    int i = getint(pos_int_arg(arg));
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
    // Open, dump what's in there and give him the Bitmap
    ::OpenClipboard(MainWindowx->HWindow);

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
    ::OpenClipboard(MainWindowx->HWindow);

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

    int tempWidth = getint(pos_int_arg(arg));
    int tempHeight = getint(pos_int_arg(cdr(arg)));

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

            HDC screenDC = MainWindowx->ScreenWindow->GetScreenDeviceContext();
            HDC memDC    = MainWindowx->ScreenWindow->GetMemoryDeviceContext();

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

                    MainWindowx->ScreenWindow->Invalidate(false);
                }
                else
                {
                    TScroller * const scroller = MainWindowx->ScreenWindow->Scroller;
                    SetRect(
                        &tempRect,
                        +g_SelectedTurtle->Position.x - scroller->XPos + xoffset,
                        -g_SelectedTurtle->Position.y - scroller->YPos + yoffset + LL - g_SelectedBitmap->Height,
                        +g_SelectedTurtle->Position.x - scroller->XPos + xoffset + g_SelectedBitmap->Width,
                        -g_SelectedTurtle->Position.y - scroller->YPos + yoffset + LL);

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

    FIXNUM newWidth  = getint(pos_int_arg(arg));
    FIXNUM newHeight = getint(pos_int_arg(cdr(arg)));

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
            HDC ScreenDC = MainWindowx->ScreenWindow->GetScreenDeviceContext();
            HDC MemDC    = MainWindowx->ScreenWindow->GetMemoryDeviceContext();

            HBITMAP oldBitmap = (HBITMAP) SelectObject(MemDC, g_SelectedBitmap->MemoryBitMap);

            HPALETTE oldPalette2;
            if (EnablePalette)
            {
                oldPalette2 = SelectPalette(ScreenDC, ThePalette, FALSE);
                RealizePalette(ScreenDC);

                OldPalette = SelectPalette(MemDC, ThePalette, FALSE);
                RealizePalette(MemDC);
            }

            HBITMAP newMemoryBitmap = CreateCompatibleBitmap(ScreenDC, newWidth, newHeight);
            if (newMemoryBitmap == NULL)
            {
                err_logo(OUT_OF_MEM, NIL);
                return Unbound;
            }

            HDC TempMemDC = CreateCompatibleDC(ScreenDC);
            HBITMAP oldBitmap2 = (HBITMAP) SelectObject(TempMemDC, newMemoryBitmap);

            if (EnablePalette)
            {
                SelectPalette(ScreenDC, oldPalette2, FALSE);
            }


            if (EnablePalette)
            {
                oldPalette2 = SelectPalette(TempMemDC, ThePalette, FALSE);
                RealizePalette(TempMemDC);
            }

            if (g_OsVersionInformation.dwPlatformId == VER_PLATFORM_WIN32_NT)
            {
                SetStretchBltMode(TempMemDC, HALFTONE);
            }
            else
            {
                // HALFTONE is not supported on Win 95/98/ME
                SetStretchBltMode(TempMemDC, COLORONCOLOR);
            }

            // Load hour-glass cursor.
            HCURSOR oldCursor =::SetCursor(hCursorWait);

            StretchBlt(
                TempMemDC,
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
                SelectPalette(MemDC, OldPalette, FALSE);
                SelectPalette(TempMemDC, oldPalette2, FALSE);
            }

            SelectObject(TempMemDC, oldBitmap2);
            DeleteDC(TempMemDC);

            SelectObject(MemDC, oldBitmap);

            DeleteObject(g_SelectedBitmap->MemoryBitMap);
            g_SelectedBitmap->MemoryBitMap = newMemoryBitmap;

            g_SelectedBitmap->Width  = newWidth;
            g_SelectedBitmap->Height = newHeight;

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

            HDC ScreenDC = MainWindowx->ScreenWindow->GetScreenDeviceContext();

            HDC TempMemDC = CreateCompatibleDC(ScreenDC);
            HBITMAP oldBitmap2 = (HBITMAP) SelectObject(
                TempMemDC,
                g_SelectedBitmap->MemoryBitMap);

            //memory
            HDC MemDC = MainWindowx->ScreenWindow->GetMemoryDeviceContext();
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

                MainWindowx->ScreenWindow->Invalidate(false);
            }
            else
            {
                BitBlt(
                    ScreenDC,
                    +dest.x - MainWindowx->ScreenWindow->Scroller->XPos + xoffset,
                    -dest.y - MainWindowx->ScreenWindow->Scroller->YPos + yoffset + LL - g_SelectedBitmap->Height,
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
    int i = getint(pos_int_arg(arg));
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

        HDC ScreenDC = MainWindowx->ScreenWindow->GetScreenDeviceContext();

        HDC TempMemDC = CreateCompatibleDC(ScreenDC);
        HBITMAP oldBitmap2 = (HBITMAP) SelectObject(
            TempMemDC,
            g_SelectedBitmap->MemoryBitMap);

        //memory
        HDC MemDC = MainWindowx->ScreenWindow->GetMemoryDeviceContext();
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

    NODE * val = ranged_integer_arg(args, -TOTAL_SPECIAL_TURTLES, MAXINT);
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

        HDC ScreenDC = MainWindowx->ScreenWindow->GetScreenDeviceContext();

        HDC TempMemDC = CreateCompatibleDC(ScreenDC);
        HBITMAP oldBitmap2 = (HBITMAP) SelectObject(
            TempMemDC,
            g_Bitmaps[TurtleToPaste].MemoryBitMap);

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
                +dest.x - MainWindowx->ScreenWindow->Scroller->XPos / the_zoom + xoffset,
                -dest.y - MainWindowx->ScreenWindow->Scroller->YPos / the_zoom + yoffset + LL - g_Bitmaps[TurtleToPaste].Height,
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
                +dest.x - MainWindowx->ScreenWindow->Scroller->XPos + xoffset,
                -dest.y - MainWindowx->ScreenWindow->Scroller->YPos + yoffset + LL - g_Bitmaps[TurtleToPaste].Height,
                g_Bitmaps[TurtleToPaste].Width,
                g_Bitmaps[TurtleToPaste].Height,
                TempMemDC,
                0,
                0,
                g_Turtles[TurtleToPaste].BitmapRasterMode);
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
            TRect screenRect;
            MainWindowx->ScreenWindow->GetClientRect(screenRect);

            MainWindowx->ScreenWindow->Scroller->ScrollTo(
                ((BitMapWidth * the_zoom) / 2) - (0.5 * screenRect.right),
                MainWindowx->ScreenWindow->Scroller->YPos);
        }
        else
        {
            MainWindowx->ScreenWindow->Scroller->ScrollTo(
                MainWindowx->ScreenWindow->Scroller->XPos + delta,
                MainWindowx->ScreenWindow->Scroller->YPos);
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
            TRect screenRect;
            MainWindowx->ScreenWindow->GetClientRect(screenRect);

            MainWindowx->ScreenWindow->Scroller->ScrollTo(
                MainWindowx->ScreenWindow->Scroller->XPos,
                ((BitMapHeight * the_zoom)/ 2) - (0.5 * screenRect.bottom));
        }
        else
        {
            MainWindowx->ScreenWindow->Scroller->ScrollTo(
                MainWindowx->ScreenWindow->Scroller->XPos,
                MainWindowx->ScreenWindow->Scroller->YPos + delta);
        }
    }

    return Unbound;
}

NODE *lsetfocus(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    char textbuf[MAX_BUFFER_SIZE];
    cnv_strnode_string(textbuf, arg);

    if (0 == stricmp("FMSLogo", textbuf) ||
        0 == stricmp("MSWLogo Screen", textbuf) ||
        0 == stricmp("FMSLogo Screen", textbuf))
    {
        // special-case: set the focus on the screen
        MainWindowx->ScreenWindow->SetFocus();
    }
    else
    {
        // get handle to Window with arg as Caption
        HWND window = FindWindow(NULL, textbuf);

        // Now set focus to it, if it exists
        if (window != NULL)
        {
            ::SetFocus(window);
        }
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
    char caption[MAX_BUFFER_SIZE];
    cnv_strnode_string(caption, args);

    int mode = getint(pos_int_arg(cdr(args)));

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
            MainWindowx->UndockCommanderWindow();

            window = MainWindowx->CommandWindow->HWindow;
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
        HDC memoryDC = MainWindowx->ScreenWindow->GetMemoryDeviceContext();
        HBITMAP oldBitmap = (HBITMAP) ::SelectObject(memoryDC, MemoryBitMap);

        ::FillRect(memoryDC, &FullRect, tempBrush);

        ::SetBkColor(memoryDC, scolor);
        ::SetBkMode(memoryDC, TRANSPARENT);

        ::SelectObject(memoryDC, oldBitmap);

        ::DeleteObject(tempBrush);
    }

    MainWindowx->ScreenWindow->Invalidate(false);
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

        EnumFontFamilies(hdc, NULL, PrintFont, NULL);
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
        NULL);

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
        char textbuf[MAX_BUFFER_SIZE];
        cnv_strnode_string(textbuf, arg);

        do_help(textbuf);
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

    char textbuf[MAX_BUFFER_SIZE];
    cnv_strnode_string(textbuf, arg);

    // if 2nd arg then pass to winhelp
    if (cdr(arg) != NIL)
    {
        char textbuf2[MAX_BUFFER_SIZE];
        cnv_strnode_string(textbuf2, cdr(arg));
        MainWindowx->WinHelp(textbuf, HELP_PARTIALKEY, (DWORD) textbuf2);
    }
    else
    {
        // else just give help on file (arg 1)
        MainWindowx->WinHelp(textbuf, HELP_INDEX, 0L);
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

        char textbuf[MAX_BUFFER_SIZE];
        cnv_strnode_string(textbuf, args);

        // Get the FontRec filled with a match to textbuf
        setfont(textbuf);

        // now fill in the rest of the (optional) fields if given
        if (cdr(args) != NIL)
        {
            FontRec.lfHeight = int_arg(args = cdr(args));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfWidth = getint(pos_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfOrientation = getint(pos_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfWeight = getint(pos_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfItalic = getint(pos_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfUnderline = getint(pos_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfStrikeOut = getint(pos_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfCharSet = getint(pos_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfOutPrecision = getint(pos_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfClipPrecision = getint(pos_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfQuality = getint(pos_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfPitchAndFamily = getint(pos_int_arg(args = cdr(args)));
        }

        // update status window

        // update_status_fontwieght();
        // update_status_fontsize();
        // update_status_fontname();
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
    TRect wrect;
    MainWindowx->GetWindowRect(wrect);


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

    HDC screen = MainWindowx->ScreenWindow->GetScreenDeviceContext();

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
    HDC MemDC = MainWindowx->ScreenWindow->GetMemoryDeviceContext();

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
    HDC ScreenDC = MainWindowx->ScreenWindow->GetScreenDeviceContext();

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
        MainWindowx->ScreenWindow->Invalidate(false);
    }
    else
    {
        TextOut(
            ScreenDC,
            +dest.x - MainWindowx->ScreenWindow->Scroller->XPos + xoffset,
            -dest.y - MainWindowx->ScreenWindow->Scroller->YPos + yoffset,
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


void exit_program(void)
{
    if (is_executing())
    {
        IsTimeToHalt = true;
    }
    IsTimeToExit = true;
}
