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

static int CutIndex = 0; // Pointer into CutBmp initially "ClipBoard"

struct font_find_t
   {
   const char *fontname;
   bool        found;
   };

static DWORD g_BitMode = SRCCOPY;

#ifdef NDEBUG
#  define ASSERT_TURTLE_INVARIANT
#else
#  define ASSERT_TURTLE_INVARIANT CTurtlesInvariant invariant;

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
      assert(turtle_max < TURTLES);

      // the turtle_which is within range
      assert(0 <= turtle_which);
      assert((turtle_which <= turtle_max) ||
             (TURTLES - TURTLEN <= turtle_which && turtle_which <= TURTLES));

      for (int i = 0; i <= turtle_max; i++)
         {
         assert(
            g_Turtles[i].IsShown == true ||
            g_Turtles[i].IsShown == false);

         assert(
            g_Turtles[i].Bitmap == 0           ||
            g_Turtles[i].Bitmap == SRCCOPY     ||
            g_Turtles[i].Bitmap == SRCPAINT    ||
            g_Turtles[i].Bitmap == SRCAND      ||
            g_Turtles[i].Bitmap == SRCINVERT   ||
            g_Turtles[i].Bitmap == SRCERASE    ||
            g_Turtles[i].Bitmap == NOTSRCCOPY  ||
            g_Turtles[i].Bitmap == NOTSRCERASE ||
            g_Turtles[i].Bitmap == MERGEPAINT  ||
            g_Turtles[i].Bitmap == DSTINVERT);
         }

      // the CutIndex is within range
      assert(0 <= CutIndex);
      assert(CutIndex < MaxBitCuts);

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

void
gifsave_helper(
   char *textbuf,
   int iDelay_,
   int bAppendMode_,
   int iLoop_,
   int iTrans_,
   int iMaxColorDepth
)
   {
   iDelay      = iDelay_;
   bAppendMode = bAppendMode_;
   iLoop       = iLoop_;
   iTrans      = iTrans_;

   MainWindowx->DumpBitmapFile(TempBmpName, iMaxColorDepth);
   lsetcursorwait(NIL);
   if (gbmBmpToGif(TempBmpName, textbuf) != 0)
      {
      ShowErrorMessageAndStop(LOCALIZED_ERROR_GIFSAVEFAILED);
      }
   lsetcursorarrow(NIL);
   unlink(TempBmpName);
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
   /* same as BITMAP-SAVE but gets file name from logo command */
   char textbuf[MAX_BUFFER_SIZE];
   cnv_strnode_string(textbuf, args);

   /* check for optional callback routine */
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
      gifsave_helper(textbuf, iDelay, bAppendMode, iLoop, iTrans, iMaxColorDepth);
      }

   return Unbound;
   }

NODE *lbitsave(NODE *args)
   {
   /* same as BITMAP-SAVE but gets file name from logo command */
   char textbuf[MAX_BUFFER_SIZE];
   cnv_strnode_string(textbuf, args);

   if (NOT_THROWING)
      {
      int iMaxBitCount = 32;

      if (cdr(args) != NIL)
         {
         NODE *val1 = integer_arg(cdr(args));
         if (NOT_THROWING)
            {
            iMaxBitCount = getint(val1);
            }
         }

      MainWindowx->DumpBitmapFile(textbuf, iMaxBitCount);
      }

   return Unbound;
   }

void gifload_helper(char *textbuf, DWORD &dwPixelWidth, DWORD &dwPixelHeight)
   {
   lsetcursorwait(NIL);
   if (gbmGifToBmp(textbuf, TempBmpName) != 0)
      {
      ShowErrorMessageAndStop(LOCALIZED_ERROR_GIFREADFAILED);
      }
   lsetcursorarrow(NIL);
   MainWindowx->LoadBitmapFile(TempBmpName, dwPixelWidth, dwPixelHeight);
   unlink(TempBmpName);
   }

NODE *lgifload(NODE *arg)
   {
   /* same as BITMAP-SAVE but gets file name from logo command */

   char textbuf[MAX_BUFFER_SIZE];
   cnv_strnode_string(textbuf, arg);

   if (NOT_THROWING)
      {
      DWORD dwPixelWidth = 1;
      DWORD dwPixelHeight = 1;
      gifload_helper(textbuf, dwPixelWidth, dwPixelHeight);
      }

   return Unbound;
   }

NODE *lgifsize(NODE *args)
   {
   /* same as BITMAP-SAVE but gets file name from logo command */

   char textbuf[MAX_BUFFER_SIZE];
   cnv_strnode_string(textbuf, args);

   if (NOT_THROWING)
      {
      DWORD dwPixelWidth = 0;
      DWORD dwPixelHeight = 0;
      gifload_helper(textbuf, dwPixelWidth, dwPixelHeight);

      return cons_list(
         make_intnode((FIXNUM) dwPixelWidth),
         make_intnode((FIXNUM) dwPixelHeight));
      }

   return Unbound;
   }

NODE *lbitload(NODE *arg)
   {
   /* same as BITMAP-LOAD except callable from logo command */

   char textbuf[MAX_BUFFER_SIZE];
   cnv_strnode_string(textbuf, arg);

   if (NOT_THROWING)
      {
      DWORD dwPixelWidth = 1;
      DWORD dwPixelHeight = 1;
      MainWindowx->LoadBitmapFile(textbuf, dwPixelWidth, dwPixelHeight);
      }

   return Unbound;
   }

NODE *lbitloadsize(NODE *arg)
   {
   /* same as BITMAP-LOAD except callable from logo command */

   char textbuf[MAX_BUFFER_SIZE];
   cnv_strnode_string(textbuf, arg);

   if (NOT_THROWING)
      {
      DWORD dwPixelWidth = 0;
      DWORD dwPixelHeight = 0;
      MainWindowx->LoadBitmapFile(textbuf, dwPixelWidth, dwPixelHeight);

      return cons_list(
         make_intnode((FIXNUM) dwPixelWidth),
         make_intnode((FIXNUM) dwPixelHeight));
      }

   return Unbound;
   }

NODE *lbitsize(NODE *)
   {
   BITMAP temp;
   temp.bmWidth  = 0;
   temp.bmHeight = 0;

   // If ClipBoard check with ClipBoard only
   if (CutIndex == 0)
      {
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
      if (CutBmp[CutIndex].CutFlag)
         {
         ::GetObject(
            CutBmp[CutIndex].CutMemoryBitMap,
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
   ASSERT_TURTLE_INVARIANT

   POINT dest;
   if (!WorldCoordinateToScreenCoordinate(g_Turtles[turtle_which].Position, dest))
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
   ASSERT_TURTLE_INVARIANT

   POINT dest;
   if (!WorldCoordinateToScreenCoordinate(g_Turtles[turtle_which].Position, dest))
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
   if (!WorldCoordinateToScreenCoordinate(g_Turtles[turtle_which].Position, dest))
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
   ASSERT_TURTLE_INVARIANT

   return color_helper(dpen);
   }

// function to set the pen color while updating palette, if need be

void thepencolor(int r, int g, int b)
   {
   dpen.red   = r;
   dpen.green = g;
   dpen.blue  = b;

   if (EnablePalette)
      {
      pcolor = LoadColor(dpen.red, dpen.green, dpen.blue);
      }
   else
      {
      pcolor = RGB(dpen.red, dpen.green, dpen.blue);
      }

   UpdateNormalPen(g_PenWidth, pcolor);
   }

// function to return flood color as a RGB list

NODE *lfloodcolor(NODE *)
   {
   ASSERT_TURTLE_INVARIANT

   return color_helper(dfld);
   }

// funtion to set the flood color while updating palette if need be

void thefloodcolor(int r, int g, int b)
   {

   dfld.red   = r;
   dfld.green = g;
   dfld.blue  = b;

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
   }

// function to return screen color as a RGB list
NODE *lscreencolor(NODE *)
   {
   return color_helper(dscn);
   }

// Set the screen color and update palette, if necessary
void thescreencolor(int r, int g, int b)
   {
   dscn.red   = r;
   dscn.green = g;
   dscn.blue  = b;

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
   UpdateErasePen(g_PenWidth, scolor);

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
   }

int get_pen_width()
   {
   return g_PenWidth;
   }

int get_pen_height()
   {
   return get_pen_width();
   }

void set_pen_width(int w)
   {
   g_PenWidth = w;

   // we erase with the same pen width as we write
   UpdateNormalPen(g_PenWidth, pcolor);
   UpdateErasePen(g_PenWidth,  scolor);
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
   ASSERT_TURTLE_INVARIANT

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
   ASSERT_TURTLE_INVARIANT

   // get arg
   NODE *val = numeric_arg(arg);

   FLONUM temp_zoom = numeric_node_to_flonum(val);

   if (temp_zoom <= 0.0)
      {
      temp_zoom = 1.0;
      }

   zoom_helper(temp_zoom);

   return Unbound;
   }


NODE *lbitblock(NODE *arg)
   {
   ASSERT_TURTLE_INVARIANT

   POINT turtleLocation;
   if (!WorldCoordinateToScreenCoordinate(
          g_Turtles[turtle_which].Position, 
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
         HDC screenDC = screen->GetScreenDeviceContext();
         draw_turtle(false);

         
         HPALETTE oldPalette2;
         if (EnablePalette)
            {
            oldPalette2 = SelectPalette(screenDC, ThePalette, FALSE);
            RealizePalette(screenDC);
            }

         if (zoom_flag)
            {
            // It's easier to invalidate the screen and forcing a 
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

            FillRect(screenDC, &screenRect, fillBrush);
            }

         if (EnablePalette)
            {
            SelectPalette(screenDC, oldPalette2, FALSE);
            }

         DeleteObject(fillBrush);

         draw_turtle(true);
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
         // notify the user that the bitmode was invalid
         ShowErrorMessageAndStop(LOCALIZED_ERROR_BITMODEBADBITMODE);
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

NODE *lbitmode(NODE *)
   {
   ASSERT_TURTLE_INVARIANT

   // return the logo "code" for the bit mode
   FIXNUM temp = RasterModeToBitMode(g_BitMode);

   return make_intnode(temp);
   }

NODE *lsetbitmode(NODE *arg)
   {
   ASSERT_TURTLE_INVARIANT

   // convert from logo "code" to Windows constants
   FIXNUM bitmode = BitModeToRasterMode(int_arg(arg)); 
   if (NOT_THROWING)
      {
      g_BitMode = bitmode;
      }
   return Unbound;
   }

NODE *lturtlemode(NODE *)
   {
   ASSERT_TURTLE_INVARIANT

   // return the logo "code" for the bit mode
   FIXNUM turtlemode = RasterModeToBitMode(g_Turtles[turtle_which].Bitmap);
   return make_intnode(turtlemode);
   }

NODE *lsetturtlemode(NODE *arg)
   {
   ASSERT_TURTLE_INVARIANT

   if (g_Turtles[turtle_which].Bitmap)
      {
      draw_turtle(false);

      // convert from logo "code" to Windows constants
      FIXNUM turtlemode = BitModeToRasterMode(int_arg(arg)); 
      if (NOT_THROWING)
         {
         g_Turtles[turtle_which].Bitmap = turtlemode;
         }

      draw_turtle(true);
      }

   return Unbound;
   }

NODE *lbitindex(NODE *arg)
   {
   ASSERT_TURTLE_INVARIANT
   // return the current bitmap index
   return make_intnode((FIXNUM) CutIndex);
   }

NODE *lsetbitindex(NODE *arg)
   {
   ASSERT_TURTLE_INVARIANT

   // set the current bitmap index if within range
   int i = getint(pos_int_arg(arg));

   if (i < MaxBitCuts)
      {
      CutIndex = i;
      }
   else
      {
      // notify the user that the bit index was out-of-range
      ShowErrorMessageAndStop(LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE);
      }

   return Unbound;
   }


static
void
CopyCutIndexToClipboard(
   int CutBmpIndex
)
   {
   // Open, dump what's in there and give him the Bitmap
   ::OpenClipboard(MainWindowx->HWindow);

   ::EmptyClipboard();

   ::SetClipboardData(
      CF_BITMAP,
      CutBmp[CutBmpIndex].CutMemoryBitMap);

   if (EnablePalette)
      {
      // If we have a palette given him a DIB and a palette too
      ::SetClipboardData(
         CF_DIB,
         BitmapToDIB(
            CutBmp[CutBmpIndex].CutMemoryBitMap,
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
            CutBmp[CutBmpIndex].CutMemoryBitMap,
            NULL));
      }

   ::CloseClipboard();

   // Never mung with bitmaps that belong to ClipBoard

   CutBmp[CutBmpIndex].CutFlag = false;
   }



static
void
PasteFromClipboardToCutIndex(
   int CutBmpIndex
)
   {
   ::OpenClipboard(MainWindowx->HWindow);

   // Try a DIB first
   HANDLE TempDIB = (HBITMAP) ::GetClipboardData(CF_DIB);

   if (TempDIB != NULL)
      {
      // The clipboard holds a DIB.  Try to get the palette.
      HPALETTE TempPal = (HPALETTE) ::GetClipboardData(CF_PALETTE);

      // we work in bmps here
      CutBmp[CutBmpIndex].CutMemoryBitMap = ::DIBToBitmap(TempDIB, TempPal);

      // Fill our logical palette with the Palette from the clipboard
      if (EnablePalette && (TempPal != NULL))
         {
         MyLogPalette->palNumEntries = ::GetPaletteEntries(
            TempPal,
            0,
            256,
            &(MyLogPalette->palPalEntry[0]));

         // now rebuild palette
         ::DeleteObject(ThePalette);
         ThePalette = ::CreatePalette(MyLogPalette);
         update_status_paletteuse();
         }

      // Let code know below that we have something

      CutBmp[CutBmpIndex].CutFlag = true;

      // We created a BitMap from the DIB that we only need for the
      // purpose of this "paste", next paste could be something new.
      // so get rid of it once we have pasted it here.

      ::EmptyClipboard();
      ::SetClipboardData(CF_BITMAP, CutBmp[CutBmpIndex].CutMemoryBitMap);

      // If we have a palette given him a DIB and a palette too
      if (EnablePalette)
         {
         ::SetClipboardData(
            CF_DIB,
            BitmapToDIB(CutBmp[CutBmpIndex].CutMemoryBitMap, ThePalette));

         ::SetClipboardData(
            CF_PALETTE,
            CreatePalette(MyLogPalette));
         }
      else
         {
         // else give him a DIB using system palette
         ::SetClipboardData(
            CF_DIB,
            BitmapToDIB(CutBmp[CutBmpIndex].CutMemoryBitMap, NULL));
         }
      }
    else
      {
      // else try for a bitmap
      CutBmp[CutBmpIndex].CutMemoryBitMap = (HBITMAP) ::GetClipboardData(CF_BITMAP);

      // flag that we have one if it exists, no need to delete the
      // bitmap here because clipboard still owns it.

      if (CutBmp[CutBmpIndex].CutMemoryBitMap != NULL)
         {
         CutBmp[CutBmpIndex].CutFlag = true;
         }
      else
         {
         CutBmp[CutBmpIndex].CutFlag = false;
         }
      }

   // if we have something fetch its size

   if (CutBmp[CutBmpIndex].CutFlag)
      {
      BITMAP temp;

      ::GetObject(
         CutBmp[CutBmpIndex].CutMemoryBitMap,
         sizeof(BITMAP),
         (LPSTR) &temp);

      CutBmp[CutBmpIndex].CutWidth = temp.bmWidth;
      CutBmp[CutBmpIndex].CutHeight = temp.bmHeight;
      }

   // we have everything we need
   ::CloseClipboard();
   }


static
NODE *
BitCopyOrCut(NODE *arg, bool IsCut)
   {
   POINT dest;
   if (!WorldCoordinateToScreenCoordinate(g_Turtles[turtle_which].Position, dest))
      {
      return Unbound;
      }

   int TempWidth = getint(pos_int_arg(arg));
   int TempHeight = getint(pos_int_arg(cdr(arg)));

   if (NOT_THROWING)
      {
      bool havebitmap = false;

      // if we had a old cut get rid of it, we won't go in for clipboard
      if (CutBmp[CutIndex].CutFlag)
         {
         // if same size reuse the bitmap
         if ((TempWidth == CutBmp[CutIndex].CutWidth) &&
             (TempHeight == CutBmp[CutIndex].CutHeight))
            {
            havebitmap = true;
            }
         else
            {
            // else get rid of it and make a new one later
            DeleteObject(CutBmp[CutIndex].CutMemoryBitMap);
            }
         CutBmp[CutIndex].CutFlag = false;
         }

      CutBmp[CutIndex].CutWidth = TempWidth;
      CutBmp[CutIndex].CutHeight = TempHeight;

      // only if we have a surface continue
      if ((CutBmp[CutIndex].CutWidth != 0) && (CutBmp[CutIndex].CutHeight != 0))
         {
         // flag it so we will delete it
         CutBmp[CutIndex].CutFlag = true;

         HDC ScreenDC = MainWindowx->ScreenWindow->GetScreenDeviceContext();
         HDC MemDC    = MainWindowx->ScreenWindow->GetMemoryDeviceContext();

         HBITMAP oldBitmap = (HBITMAP) SelectObject(MemDC, MemoryBitMap);

         if (!havebitmap)
            {
            CutBmp[CutIndex].CutMemoryBitMap = CreateCompatibleBitmap(
               ScreenDC,
               CutBmp[CutIndex].CutWidth,
               CutBmp[CutIndex].CutHeight);
            }

         if (!CutBmp[CutIndex].CutMemoryBitMap)
            {
            ShowErrorMessageAndStop(LOCALIZED_ERROR_BITMAPCUTFAILED);
            return Unbound;
            }


         HDC TempMemDC = CreateCompatibleDC(ScreenDC);

         HBITMAP oldBitmap2 = (HBITMAP) SelectObject(
            TempMemDC,
            CutBmp[CutIndex].CutMemoryBitMap);

         BitBlt(
            TempMemDC,
            0,
            0,
            CutBmp[CutIndex].CutWidth,
            CutBmp[CutIndex].CutHeight,
            MemDC,
            +dest.x + xoffset,
            -dest.y + yoffset + LL - CutBmp[CutIndex].CutHeight,
            SRCCOPY);

         SelectObject(TempMemDC, oldBitmap2);
         DeleteDC(TempMemDC);

         if (IsCut)
            {
            // this is a cut operation (as opposed to a copy operation)

            // memory
            RECT TempRect;
            SetRect(
               &TempRect,
               +dest.x + xoffset,
               -dest.y + yoffset + LL - CutBmp[CutIndex].CutHeight,
               +dest.x + xoffset + CutBmp[CutIndex].CutWidth,
               -dest.y + yoffset + LL);

            HBRUSH TempBrush = CreateBrushIndirect(&ScreenBrush);

            FillRect(MemDC, &TempRect, TempBrush);

            //screen
            draw_turtle(false);

            if (zoom_flag)
               {
//               TRect temp;
//
//               temp.Set(
//                  (+g_Turtles[turtle_which].Position.x - MainWindowx->Scroller->XPos / the_zoom + xoffset                                  ) * the_zoom,
//                  (-g_Turtles[turtle_which].Position.y - MainWindowx->Scroller->YPos / the_zoom + yoffset + LL - CutBmp[CutIndex].CutHeight) * the_zoom,
//                  (+g_Turtles[turtle_which].Position.x - MainWindowx->Scroller->XPos / the_zoom + xoffset + CutBmp[CutIndex].CutWidth      ) * the_zoom,
//                  (-g_Turtles[turtle_which].Position.y - MainWindowx->Scroller->YPos / the_zoom + yoffset + LL                             ) * the_zoom);
//
//               temp.Normalize();
//               temp.Inflate(1+the_zoom,1+the_zoom);

               MainWindowx->ScreenWindow->Invalidate(false);
               }
            else
               {
               SetRect(
                  &TempRect,
                  +g_Turtles[turtle_which].Position.x - MainWindowx->ScreenWindow->Scroller->XPos + xoffset,
                  -g_Turtles[turtle_which].Position.y - MainWindowx->ScreenWindow->Scroller->YPos + yoffset + LL - CutBmp[CutIndex].CutHeight,
                  +g_Turtles[turtle_which].Position.x - MainWindowx->ScreenWindow->Scroller->XPos + xoffset + CutBmp[CutIndex].CutWidth,
                  -g_Turtles[turtle_which].Position.y - MainWindowx->ScreenWindow->Scroller->YPos + yoffset + LL);

               FillRect(ScreenDC, &TempRect, TempBrush);
               }

            DeleteObject(TempBrush);

            draw_turtle(true);
         }

         SelectObject(MemDC, oldBitmap);

         // if CutIndex == 0 then do Clipboard
         if (CutIndex == 0)
            {
            CopyCutIndexToClipboard(CutIndex);
            }
         }
      }

   return Unbound;
   }


NODE *lbitcut(NODE *arg)
   {
   ASSERT_TURTLE_INVARIANT
   return BitCopyOrCut(arg, true);
   }

NODE *lbitcopy(NODE *arg)
   {
   ASSERT_TURTLE_INVARIANT
   return BitCopyOrCut(arg, false);
   }

NODE *lbitfit(NODE *arg)
   {
   ASSERT_TURTLE_INVARIANT

   FLONUM FitWidth = getint(pos_int_arg(arg));
   FLONUM FitHeight = getint(pos_int_arg(cdr(arg)));

   if (NOT_THROWING)
      {

      // If ClipBoard check with ClipBoard only
      if (CutIndex == 0)
         {
         PasteFromClipboardToCutIndex(CutIndex);
         }

      // only if we have a surface to fit to and from continue
      if ((FitWidth != 0) && (FitHeight != 0) && CutBmp[CutIndex].CutFlag)
         {

         HDC ScreenDC = MainWindowx->ScreenWindow->GetScreenDeviceContext();
         HDC MemDC    = MainWindowx->ScreenWindow->GetMemoryDeviceContext();

         HBITMAP oldBitmap = (HBITMAP) SelectObject(MemDC, CutBmp[CutIndex].CutMemoryBitMap);

         HPALETTE oldPalette2;
         if (EnablePalette)
            {
            oldPalette2 = SelectPalette(ScreenDC, ThePalette, FALSE);
            RealizePalette(ScreenDC);

            OldPalette = SelectPalette(MemDC, ThePalette, FALSE);
            RealizePalette(MemDC);
            }

         HBITMAP TempMemoryBitMap = CreateCompatibleBitmap(ScreenDC, (int) FitWidth, (int) FitHeight);
         if (!TempMemoryBitMap)
            {
            ShowErrorMessageAndStop(LOCALIZED_ERROR_BITMAPFITFAILED);
            return Unbound;
            }

         HDC TempMemDC = CreateCompatibleDC(ScreenDC);
         HBITMAP oldBitmap2 = (HBITMAP) SelectObject(TempMemDC, TempMemoryBitMap);

         if (EnablePalette)
            {
            SelectPalette(ScreenDC, oldPalette2, FALSE);
            }


         if (EnablePalette)
            {
            oldPalette2 = SelectPalette(TempMemDC, ThePalette, FALSE);
            RealizePalette(TempMemDC);
            }

         SetStretchBltMode(TempMemDC, COLORONCOLOR);

         // Load hour-glass cursor.
         HCURSOR oldCursor =::SetCursor(hCursorWait);

         StretchBlt(
            TempMemDC,
            0,
            0,
            FitWidth,
            FitHeight,
            MemDC,
            0,
            0,
            CutBmp[CutIndex].CutWidth,
            CutBmp[CutIndex].CutHeight,
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

         DeleteObject(CutBmp[CutIndex].CutMemoryBitMap);
         CutBmp[CutIndex].CutMemoryBitMap = TempMemoryBitMap;

         CutBmp[CutIndex].CutWidth = FitWidth;
         CutBmp[CutIndex].CutHeight = FitHeight;

         if (CutIndex == 0)
            {
            CopyCutIndexToClipboard(CutIndex);
            }
         }
      }
   return Unbound;
   }

NODE *lbitpaste(NODE *)
   {
   ASSERT_TURTLE_INVARIANT

   POINT dest;
   if (!WorldCoordinateToScreenCoordinate(g_Turtles[turtle_which].Position, dest))
      {
      return Unbound;
      }

   if (NOT_THROWING)
      {

      // If ClipBoard check with ClipBoard only
      if (CutIndex == 0)
         {
         PasteFromClipboardToCutIndex(CutIndex);
         }

      // only if we have something to paste
      if (CutBmp[CutIndex].CutFlag)
         {

         // if clipboard then never leave Cut Flag true
         if (CutIndex == 0)
            {
            CutBmp[CutIndex].CutFlag = false;
            }

         HDC ScreenDC = MainWindowx->ScreenWindow->GetScreenDeviceContext();

         HDC TempMemDC = CreateCompatibleDC(ScreenDC);
         HBITMAP oldBitmap2 = (HBITMAP) SelectObject(
            TempMemDC,
            CutBmp[CutIndex].CutMemoryBitMap);

         //memory
         HDC MemDC = MainWindowx->ScreenWindow->GetMemoryDeviceContext();
         HBITMAP oldBitmap = (HBITMAP) SelectObject(MemDC, MemoryBitMap);

         BitBlt(
            MemDC,
            +dest.x + xoffset,
            -dest.y + yoffset + LL - CutBmp[CutIndex].CutHeight,
            (int) (CutBmp[CutIndex].CutWidth),
            (int) (CutBmp[CutIndex].CutHeight),
            TempMemDC,
            0,
            0,
            g_BitMode);

         SelectObject(MemDC, oldBitmap);

         //screen

         draw_turtle(false);

         if (zoom_flag)
            {
//            TRect temp;
//
//            temp.Set(
//               (+g_Turtles[turtle_which].Position.x - MainWindowx->Scroller->XPos / the_zoom + xoffset                                  ) * the_zoom,
//               (-g_Turtles[turtle_which].Position.y - MainWindowx->Scroller->YPos / the_zoom + yoffset + LL - CutBmp[CutIndex].CutHeight) * the_zoom,
//               (+g_Turtles[turtle_which].Position.x - MainWindowx->Scroller->XPos / the_zoom + xoffset + CutBmp[CutIndex].CutWidth      ) * the_zoom,
//               (-g_Turtles[turtle_which].Position.y - MainWindowx->Scroller->YPos / the_zoom + yoffset + LL                             ) * the_zoom);
//
//            temp.Normalize();
//            temp.Inflate(1+the_zoom,1+the_zoom);

            MainWindowx->ScreenWindow->Invalidate(false);
            }
         else
            {
            BitBlt(
               ScreenDC,
               +dest.x - MainWindowx->ScreenWindow->Scroller->XPos + xoffset,
               -dest.y - MainWindowx->ScreenWindow->Scroller->YPos + yoffset + LL - CutBmp[CutIndex].CutHeight,
               (int) (CutBmp[CutIndex].CutWidth),
               (int) (CutBmp[CutIndex].CutHeight),
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
   ASSERT_TURTLE_INVARIANT

   // set the current bitmap index if within range
   int i = getint(pos_int_arg(arg));
   int x = int_arg(cdr(arg));
   int y = int_arg(cdr(cdr(arg)));

   if (MaxBitCuts <= i)
      {
      // notify the user that the bitmap index is out of range
      ShowErrorMessageAndStop(LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE);
      return Unbound;
      }

   if (!CutBmp[i].CutFlag)
      {
      // nofity the user that there is no bitmap at this index
      ShowErrorMessageAndStop(LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP);
      return Unbound;
      }

   if (NOT_THROWING)
      {

      // If ClipBoard check with ClipBoard only

      if (CutIndex == 0)
         {
         PasteFromClipboardToCutIndex(CutIndex);
         }

      // only if we have something to paste
      if (CutBmp[CutIndex].CutFlag)
         {

         // if clipboard then never leave Cut Flag true
         if (CutIndex == 0)
            {
            CutBmp[CutIndex].CutFlag = false;
            }

         HDC ScreenDC = MainWindowx->ScreenWindow->GetScreenDeviceContext();

         HDC TempMemDC = CreateCompatibleDC(ScreenDC);
         HBITMAP oldBitmap2 = (HBITMAP) SelectObject(
            TempMemDC,
            CutBmp[CutIndex].CutMemoryBitMap);

         //memory
         HDC MemDC = MainWindowx->ScreenWindow->GetMemoryDeviceContext();
         HBITMAP oldBitmap = (HBITMAP) SelectObject(MemDC, CutBmp[i].CutMemoryBitMap);

         BitBlt(
            MemDC,
            +x,
            CutBmp[i].CutHeight - y - CutBmp[CutIndex].CutHeight,
            CutBmp[CutIndex].CutWidth,
            CutBmp[CutIndex].CutHeight,
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
      }
   return Unbound;
   }

NODE *lsetturtle(NODE *arg)
   {
   ASSERT_TURTLE_INVARIANT

   NODE * val = integer_arg(arg);

   if (NOT_THROWING)
      {
      draw_turtles(false);
      int temp = getint(val);
      if ((temp >= (TURTLES - TURTLEN)) || (temp < -TURTLEN))
         {
         // notify the user that the turtle ID is out of range
         ShowErrorMessageAndStop(LOCALIZED_ERROR_BADTURTLEID);
         }
      else
         {
         turtle_which = temp;

         if (turtle_which > turtle_max)
            {
            for (int i = turtle_max + 1; i <= turtle_which; i++)
               {
               g_Turtles[i].Position.x = 0.0;
               g_Turtles[i].Position.y = 0.0;
               g_Turtles[i].Position.z = 0.0;
               g_Turtles[i].Heading   = 0.0;
               g_Turtles[i].IsShown   = true;
               g_Turtles[i].IsPenUp   = false;
               g_Turtles[i].Bitmap = 0;
               g_Turtles[i].Matrix.e11 = 1.0;
               g_Turtles[i].Matrix.e12 = 0.0;
               g_Turtles[i].Matrix.e13 = 0.0;
               g_Turtles[i].Matrix.e21 = 0.0;
               g_Turtles[i].Matrix.e22 = 1.0;
               g_Turtles[i].Matrix.e23 = 0.0;
               g_Turtles[i].Matrix.e31 = 0.0;
               g_Turtles[i].Matrix.e32 = 0.0;
               g_Turtles[i].Matrix.e33 = 1.0;
               }
            turtle_max = turtle_which;
            }

         if (turtle_which < 0)
            {
            turtle_which = (TURTLES - (TURTLEN+1)) - turtle_which;
            }

         update_status_turtleposition();
         update_status_pencontact();
         update_status_turtlevisability();
         update_status_turtleheading();
         update_status_turtlepitch();
         update_status_turtleroll();
         update_status_turtlewhich();

         g_Wanna = g_Turtles[turtle_which].Position;

         draw_turtles(true);
         }
      }

   return Unbound;
   }

NODE *lturtle(NODE *)
   {
   ASSERT_TURTLE_INVARIANT

   int active_turtle;
   if (turtle_which >= TURTLES - TURTLEN)
      {
      // this is one of the special turtles (below 0)
      active_turtle = -(turtle_which - (TURTLES - (TURTLEN+1)));
      }
   else
      {
      // this is a normal turtle
      active_turtle = turtle_which;
      }

   return make_intnode(active_turtle);
   }

NODE *lturtles(NODE *)
   {
   ASSERT_TURTLE_INVARIANT
   return make_intnode(turtle_max);
   }

void turtlepaste(int TurtleToPaste)
   {
   ASSERT_TURTLE_INVARIANT

   POINT dest;
   if (!WorldCoordinateToScreenCoordinate(g_Turtles[TurtleToPaste].Position, dest))
      {
      return;
      }

   if (NOT_THROWING)
      {

      // If ClipBoard check with ClipBoard only
      if (TurtleToPaste == 0)
         {
         PasteFromClipboardToCutIndex(TurtleToPaste);
         }

      // only if we have something to paste
      if (CutBmp[TurtleToPaste].CutFlag)
         {

         // if clipboard then never leave Cut Flag true
         if (TurtleToPaste == 0)
            {
            CutBmp[TurtleToPaste].CutFlag = false;
            }

         HDC ScreenDC = GetDC(MainWindowx->ScreenWindow->HWindow);

         HDC TempMemDC = CreateCompatibleDC(ScreenDC);
         HBITMAP oldBitmap2 = (HBITMAP) SelectObject(
            TempMemDC,
            CutBmp[TurtleToPaste].CutMemoryBitMap);

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
               -dest.y - MainWindowx->ScreenWindow->Scroller->YPos / the_zoom + yoffset + LL - CutBmp[TurtleToPaste].CutHeight,
               CutBmp[TurtleToPaste].CutWidth,
               CutBmp[TurtleToPaste].CutHeight,
               TempMemDC,
               0,
               0,
               g_Turtles[TurtleToPaste].Bitmap);
            }
         else
            {
            BitBlt(
               ScreenDC,
               +dest.x - MainWindowx->ScreenWindow->Scroller->XPos + xoffset,
               -dest.y - MainWindowx->ScreenWindow->Scroller->YPos + yoffset + LL - CutBmp[TurtleToPaste].CutHeight,
               CutBmp[TurtleToPaste].CutWidth,
               CutBmp[TurtleToPaste].CutHeight,
               TempMemDC,
               0,
               0,
               g_Turtles[TurtleToPaste].Bitmap);
            }

         ReleaseDC(MainWindowx->ScreenWindow->HWindow, ScreenDC);

         SelectObject(TempMemDC, oldBitmap2);
         DeleteDC(TempMemDC);
         }
      else
         {
         // notify the user that this turtle has no picture
         g_Turtles[TurtleToPaste].Bitmap = 0;
         char errorMessage[255];
         sprintf(errorMessage, LOCALIZED_ERROR_TURTLEHASNOPICTURE, TurtleToPaste);
         ShowErrorMessageAndStop(errorMessage);
         }
      }
   }

NODE *lscrollx(NODE *arg)
   {
   ASSERT_TURTLE_INVARIANT

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
   ASSERT_TURTLE_INVARIANT

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
   ASSERT_TURTLE_INVARIANT

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
   ASSERT_TURTLE_INVARIANT

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
   ASSERT_TURTLE_INVARIANT

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
   ASSERT_TURTLE_INVARIANT

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
   ASSERT_TURTLE_INVARIANT

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
   ASSERT_TURTLE_INVARIANT

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
   ASSERT_TURTLE_INVARIANT


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
   ASSERT_TURTLE_INVARIANT

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
   ASSERT_TURTLE_INVARIANT

   POINT dest;
   if (!WorldCoordinateToScreenCoordinate(g_Turtles[turtle_which].Position, dest))
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

   if (in_erase_mode)
      {
      SetTextColor(MemDC, scolor);
      }
   else
      {
      SetTextColor(MemDC, pcolor);
      }

   FontRec.lfEscapement = (360.0 - (g_Turtles[turtle_which].Heading - 90.0)) * 10;
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

   if (in_erase_mode)
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

void exit_program(void)
   {
   if (is_executing())
      {
      IsTimeToHalt = true;
      }
   IsTimeToExit = true;
   }
