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

extern COLORREF colortable[];
extern BOOL bIndexMode;

extern HBITMAP DIBToBitmap(HANDLE hDIB, HPALETTE hPal);
extern HANDLE BitmapToDIB(HBITMAP hBitmap, HPALETTE hPal);
extern int gbmBmpToGif(char *BmpName, char *GifName);
extern int gbmGifToBmp(char *GifName, char *BmpName);

int iDelay;
int bAppendMode;
int iLoop;
int iTrans;
int LL = 1;

static int CutIndex = 0;            // Pointer into CutBmp initially "ClipBoard"

static const char *tempfont;
static int found;
static long bitmode = SRCCOPY;

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
   lsetcursorwait();
   if (gbmBmpToGif(TempBmpName, textbuf) != 0)
      {
      MainWindowx->MessageBox(
         "Problem Generating GIF, check memory and diskspace",
         "Error");
      err_logo(STOP_ERROR, NIL);
      }
   lsetcursorarrow();
   unlink(TempBmpName);
   }

COLORREF GetRGBorIndexColor(NODE* &args)
   {
   NODE *cnode;
   int icolor;
   NODE *arg;

   COLORREF color = (COLORREF) -1;

   // get args

   if (is_list(car(args)))
      {

      arg = pos_int_vector_3_arg(args);

      if (NOT_THROWING)
         {
         if (EnablePalette)
            {
            color = LoadColor(
                ((nodetype(     car(arg) ) == FLOAT) ? (FIXNUM) getfloat(     car(arg) ) : getint(     car(arg)) ),
                ((nodetype(    cadr(arg) ) == FLOAT) ? (FIXNUM) getfloat(    cadr(arg) ) : getint(    cadr(arg)) ),
                ((nodetype(cadr(cdr(arg))) == FLOAT) ? (FIXNUM) getfloat(cadr(cdr(arg))) : getint(cadr(cdr(arg)))));
            }
         else
            {
            color = RGB(
               ((nodetype(     car(arg) ) == FLOAT) ? (FIXNUM) getfloat(     car(arg) ) : getint(     car(arg)) ),
               ((nodetype(    cadr(arg) ) == FLOAT) ? (FIXNUM) getfloat(    cadr(arg) ) : getint(    cadr(arg)) ),
               ((nodetype(cadr(cdr(arg))) == FLOAT) ? (FIXNUM) getfloat(cadr(cdr(arg))) : getint(cadr(cdr(arg)))));
            }
         }

      bIndexMode = FALSE;
   }
   else
      {
      cnode = numeric_arg(args);

      if (NOT_THROWING)
         {

         icolor = (nodetype(cnode) == FLOAT) ?
            (FIXNUM) getfloat(cnode) :
            getint(cnode);

         icolor = icolor % 16;
         if (EnablePalette)
            {
            color = LoadColor(
               GetRValue(colortable[icolor]),
               GetGValue(colortable[icolor]),
               GetBValue(colortable[icolor]));
            }
         else
            {
            color = colortable[icolor];
            }
         }

      bIndexMode = TRUE;
      }

   return color;
   }

NODE *lgifsave(NODE *args)
   {
   char textbuf[MAX_BUFFER_SIZE];
   NODE *val1;
   NODE *val3;
   NODE *val4;
   int iMaxColorDepth;
   int iDelay;
   int bAppendMode;
   int iLoop;
   int iTrans;

   /* same as BITMAP-SAVE but gets file name from logo command */

   cnv_strnode_string(textbuf, args);

   /* check for optional callback routine */

   iDelay = -1;
   bAppendMode = 0;
   iLoop = -1;
   iMaxColorDepth = 8;
   iTrans = -1;

   if (cdr(args) != NIL)
      {
      val1 = integer_arg(cdr(args));
      if (NOT_THROWING)
         {
         iDelay = getint(val1);
         if (cdr(cdr(args)) != NIL)
            {
            bAppendMode = torf_arg(cdr(cdr(args)));
            if (NOT_THROWING)
               {
               if (cdr(cdr(cdr(args))) != NIL)
                  {
                  val3 = integer_arg(cdr(cdr(cdr(args))));
                  if (NOT_THROWING)
                     {
                     iLoop = getint(val3);
                     if (cdr(cdr(cdr(cdr(args)))) != NIL)
                        {
                        val4 = integer_arg(cdr(cdr(cdr(cdr(args)))));
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

   return (UNBOUND);
   }

NODE *lbitsave(NODE *args)
   {
   char textbuf[MAX_BUFFER_SIZE];
   int iMaxBitCount;
   NODE *val1;

   /* same as BITMAP-SAVE but gets file name from logo command */

   cnv_strnode_string(textbuf, args);

   if (NOT_THROWING)
      {
      iMaxBitCount = 32;
      
      if (cdr(args) != NIL)
         {
         val1 = integer_arg(cdr(args));
         if (NOT_THROWING)
            {
            iMaxBitCount = getint(val1);
            }
         }
      
      MainWindowx->DumpBitmapFile(textbuf, iMaxBitCount);
      }

   return (UNBOUND);
   }

void gifload_helper(char *textbuf, DWORD &dwPixelWidth, DWORD &dwPixelHeight)
   {
   lsetcursorwait();
   if (gbmGifToBmp(textbuf, TempBmpName) != 0)
      {
      MainWindowx->CommandWindow->MessageBox(
         "Problem Reading GIF, check memory and diskspace",
         "Error");
      err_logo(STOP_ERROR, NIL);
      }
   lsetcursorarrow();
   MainWindowx->LoadBitmapFile(TempBmpName, dwPixelWidth, dwPixelHeight);
   unlink(TempBmpName);
   }

NODE *lgifload(NODE *arg)
   {
   char textbuf[MAX_BUFFER_SIZE];
   DWORD dwPixelWidth = 1;
   DWORD dwPixelHeight = 1;

   /* same as BITMAP-SAVE but gets file name from logo command */

   cnv_strnode_string(textbuf, arg);

   if (NOT_THROWING)
      {
      gifload_helper(textbuf, dwPixelWidth, dwPixelHeight);
      }

   return (UNBOUND);
   }

NODE *lgifsize(NODE *args)
   {
   char textbuf[MAX_BUFFER_SIZE];
   DWORD dwPixelWidth = 0;
   DWORD dwPixelHeight = 0;

   /* same as BITMAP-SAVE but gets file name from logo command */

   cnv_strnode_string(textbuf, args);

   if (NOT_THROWING)
      {
      gifload_helper(textbuf, dwPixelWidth, dwPixelHeight);

      return (
         cons(make_intnode((FIXNUM) dwPixelWidth),
         cons(make_intnode((FIXNUM) dwPixelHeight),
         NIL
         )));
      }

   return (UNBOUND);
   }

NODE *lbitload(NODE *arg)
   {
   char textbuf[MAX_BUFFER_SIZE];
   DWORD dwPixelWidth = 1;
   DWORD dwPixelHeight = 1;

   /* same as BITMAP-LOAD except callable from logo command */

   cnv_strnode_string(textbuf, arg);

   if (NOT_THROWING)
      {
      MainWindowx->LoadBitmapFile(textbuf, dwPixelWidth, dwPixelHeight);
      }

   return (UNBOUND);
   }

NODE *lbitloadsize(NODE *arg)
   {
   char textbuf[MAX_BUFFER_SIZE];
   DWORD dwPixelWidth = 0;
   DWORD dwPixelHeight = 0;

   /* same as BITMAP-LOAD except callable from logo command */

   cnv_strnode_string(textbuf, arg);

   if (NOT_THROWING)
      {
      MainWindowx->LoadBitmapFile(textbuf, dwPixelWidth, dwPixelHeight);

      return (
         cons(make_intnode((FIXNUM) dwPixelWidth),
         cons(make_intnode((FIXNUM) dwPixelHeight),
         NIL
         )));
      }

   return (UNBOUND);
   }

NODE *lbitsize(void)
   {
   BITMAP temp;

   HANDLE hDIB;
   HBITMAP hMemoryBitMap;
   LPBITMAPINFOHEADER lpDIBHdr;

   temp.bmWidth  = 0;
   temp.bmHeight = 0;

   // If ClipBoard check with ClipBoard only
   if (CutIndex == 0)
      {
      ::OpenClipboard(MainWindowx->HWindow);

      // Try a DIB first
      hDIB = (HBITMAP) ::GetClipboardData(CF_DIB);

      // If it exists get the size
      if (hDIB)
         {
         lpDIBHdr = (LPBITMAPINFOHEADER) GlobalLock(hDIB);

         if (lpDIBHdr)
            {
            temp.bmWidth  = lpDIBHdr->biWidth;
            temp.bmHeight = lpDIBHdr->biHeight;
            GlobalUnlock(hDIB);
            }
         }

      // else try for a bitmap
      else
         {
         hMemoryBitMap = (HBITMAP) ::GetClipboardData(CF_BITMAP);

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

   return (
      cons(make_intnode((FIXNUM) temp.bmWidth),
      cons(make_intnode((FIXNUM) temp.bmHeight),
      NIL)));
   }

NODE *lsetpixel(NODE *args)
   {
   HDC ScreenDC;
   HDC MemDC;
   NODE *arg;
   NODE *cnode;
   COLORREF color;
   int icolor;

   POINT dest;

   if (current_mode == perspectivemode)
      {
      VECTOR from3d;

      from3d.x = turtle_p[turtle_which].x / WorldWidth;
      from3d.y = turtle_p[turtle_which].y / WorldHeight;
      from3d.z = turtle_p[turtle_which].z / WorldDepth;

      if (!ThreeD.TransformPoint(from3d, dest)) return (UNBOUND);
      }
   else
      {
      dest.x = g_round(turtle_p[turtle_which].x);
      dest.y = g_round(turtle_p[turtle_which].y);
      }

   // get args

   if (is_list(car(args)))
      {
      arg = pos_int_vector_3_arg(args);

      if (NOT_THROWING)
         {
         if (EnablePalette)
            {
            color = LoadColor(
               ((nodetype(     car(arg) ) == FLOAT) ? (FIXNUM) getfloat(     car(arg) ) : getint(     car(arg)) ),
               ((nodetype(    cadr(arg) ) == FLOAT) ? (FIXNUM) getfloat(    cadr(arg) ) : getint(    cadr(arg)) ),
               ((nodetype(cadr(cdr(arg))) == FLOAT) ? (FIXNUM) getfloat(cadr(cdr(arg))) : getint(cadr(cdr(arg)))));
            }
         else
            {
            color = RGB(
               ((nodetype(     car(arg) ) == FLOAT) ? (FIXNUM) getfloat(     car(arg) ) : getint(     car(arg)) ),
               ((nodetype(    cadr(arg) ) == FLOAT) ? (FIXNUM) getfloat(    cadr(arg) ) : getint(    cadr(arg)) ),
               ((nodetype(cadr(cdr(arg))) == FLOAT) ? (FIXNUM) getfloat(cadr(cdr(arg))) : getint(cadr(cdr(arg)))));
            }
         }

      bIndexMode = FALSE;
      }
   else
      {
      cnode = numeric_arg(args);

      if (NOT_THROWING)
         {
         icolor = (nodetype(cnode) == FLOAT) ?
            (FIXNUM) getfloat(cnode) :
            getint(cnode);

         icolor = icolor % 16;
         if (EnablePalette)
            {
            color = LoadColor(
               GetRValue(colortable[icolor]),
               GetGValue(colortable[icolor]),
               GetBValue(colortable[icolor]));
            }
         else
            {
            color = colortable[icolor];
            }
         }

      bIndexMode = TRUE;
      }

   if (NOT_THROWING)
      {

      ScreenDC = GetDC(MainWindowx->ScreenWindow->HWindow);

      // memory

      MemDC = CreateCompatibleDC(ScreenDC);
      OldBitmap = (HBITMAP) SelectObject(MemDC, MemoryBitMap);

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

      SelectObject(MemDC, OldBitmap);
      if (EnablePalette)
         {
         SelectPalette(MemDC, OldPalette, FALSE);
         }
      DeleteDC(MemDC);

      //screen

      draw_turtle(0);

      if (EnablePalette)
         {
         OldPalette2 = SelectPalette(ScreenDC, ThePalette, FALSE);
         RealizePalette(ScreenDC);
         }

      if (zoom_flag)
         {
         TRect TempRect;

         SetRect(&TempRect,
            (+dest.x - MainWindowx->ScreenWindow->Scroller->XPos / the_zoom + xoffset) * the_zoom,
            (-dest.y - MainWindowx->ScreenWindow->Scroller->YPos / the_zoom + yoffset) * the_zoom,
            (+dest.x - MainWindowx->ScreenWindow->Scroller->XPos / the_zoom + xoffset) * the_zoom,
            (-dest.y - MainWindowx->ScreenWindow->Scroller->YPos / the_zoom + yoffset) * the_zoom);

         TempRect.Inflate(1+the_zoom,1+the_zoom);

         MainWindowx->ScreenWindow->InvalidateRect(TempRect, false);
         }
      else
         {
         SetPixel(ScreenDC,
            +dest.x - MainWindowx->ScreenWindow->Scroller->XPos + xoffset,
            -dest.y - MainWindowx->ScreenWindow->Scroller->YPos + yoffset,
            color);
         }

      if (EnablePalette)
         {
         SelectPalette(ScreenDC, OldPalette2, FALSE);
         }

      ReleaseDC(MainWindowx->ScreenWindow->HWindow, ScreenDC);

      draw_turtle(1);

      }

   return (UNBOUND);
   }

int getindexcolor(COLORREF color)
   {
   for (int i=0;i<16;i++) if (color == colortable[i]) return i;
   return -1;
   }

// function that returns the RGB vector of the pixel the turtle is on top of

NODE *lpixel()
   {
   HDC MemDC;
   HDC ScreenDC;
   COLORREF the_color;

   POINT dest;

   if (current_mode == perspectivemode)
      {
      VECTOR from3d;

      from3d.x = turtle_p[turtle_which].x / WorldWidth;
      from3d.y = turtle_p[turtle_which].y / WorldHeight;
      from3d.z = turtle_p[turtle_which].z / WorldDepth;

      if (!ThreeD.TransformPoint(from3d, dest))
         {
         return (
            cons(make_intnode((FIXNUM) - 1),
               cons(make_intnode((FIXNUM) - 1),
                  cons(make_intnode((FIXNUM) - 1),
                     NIL
                  ))));
         }
      }
   else
      {
      dest.x = g_round(turtle_p[turtle_which].x);
      dest.y = g_round(turtle_p[turtle_which].y);
      }

   ScreenDC = GetDC(MainWindowx->ScreenWindow->HWindow);

   // memory

   MemDC = CreateCompatibleDC(ScreenDC);
   OldBitmap = (HBITMAP) SelectObject(MemDC, MemoryBitMap);

   if (EnablePalette)
      {
      OldPalette = SelectPalette(MemDC, ThePalette, FALSE);
      RealizePalette(MemDC);
      }

   the_color = GetPixel(MemDC, dest.x + xoffset, -dest.y + yoffset);

   if (EnablePalette)
      {
      SelectPalette(MemDC, OldPalette, FALSE);
      }

   DeleteDC(MemDC);
   ReleaseDC(MainWindowx->ScreenWindow->HWindow, ScreenDC);

   if (bIndexMode)
      {
      int icolor = getindexcolor(the_color);
      if (icolor >= 0) return(make_intnode(icolor));
      }

   return (
      cons(make_intnode((FIXNUM) GetRValue(the_color)),
      cons(make_intnode((FIXNUM) GetGValue(the_color)),
      cons(make_intnode((FIXNUM) GetBValue(the_color)),
      NIL))));
   }

void logofill(BOOL bOld)
   {

   POINT dest;

   if (current_mode == perspectivemode)
      {
      VECTOR from3d;

      from3d.x = turtle_p[turtle_which].x / WorldWidth;
      from3d.y = turtle_p[turtle_which].y / WorldHeight;
      from3d.z = turtle_p[turtle_which].z / WorldDepth;

      if (!ThreeD.TransformPoint(from3d, dest)) return;
      }
   else
      {
      dest.x = g_round(turtle_p[turtle_which].x);
      dest.y = g_round(turtle_p[turtle_which].y);
      }

   HDC ScreenDC = GetDC(MainWindowx->ScreenWindow->HWindow);

   HBRUSH JunkBrush = CreateBrushIndirect(&FloodBrush);

   // memory
   HDC MemDC = CreateCompatibleDC(ScreenDC);
   OldBitmap = (HBITMAP) SelectObject(MemDC, MemoryBitMap);

   if (EnablePalette)
      {
      OldPalette = SelectPalette(MemDC, ThePalette, FALSE);
      RealizePalette(MemDC);
      }

   SetTextColor(MemDC, pcolor);

   OldBrush = (HBRUSH) SelectObject(MemDC, JunkBrush);

   if (bOld)
      {
      ExtFloodFill(
         MemDC,
         +dest.x + xoffset,
         -dest.y + yoffset, pcolor, FLOODFILLBORDER);
      }
   else
      {
      COLORREF tcolor = GetPixel(MemDC, dest.x + xoffset, -dest.y + yoffset) | 0x02000000;

      ExtFloodFill(
         MemDC,
         +dest.x + xoffset,
         -dest.y + yoffset, tcolor, FLOODFILLSURFACE);
      }

   if (EnablePalette)
      {
      SelectPalette(MemDC, OldPalette, FALSE);
      }

   SelectObject(MemDC, OldBrush);
   SelectObject(MemDC, OldBitmap);

   DeleteDC(MemDC);
   DeleteObject(JunkBrush);
   ReleaseDC(MainWindowx->ScreenWindow->HWindow, ScreenDC);
   }

NODE *lpencolor()
   {
   if (bIndexMode)
      {
      int icolor = getindexcolor(RGB(dpenr, dpeng, dpenb));
      if (icolor >= 0) return(make_intnode(icolor));
      }

   return (
      cons(make_intnode((FIXNUM) dpenr),
      cons(make_intnode((FIXNUM) dpeng),
      cons(make_intnode((FIXNUM) dpenb),
      NIL))));
   }

// function to set the pen color while updating palette, if need be

void thepencolor(int r, int g, int b)
   {

   dpenr = r;
   dpeng = g;
   dpenb = b;

   if (EnablePalette)
      {
      pcolor = LoadColor((int) dpenr, (int) dpeng, (int) dpenb);
      }
   else
      {
      pcolor = RGB(dpenr, dpeng, dpenb);
      }

   NormalPen.lopnStyle = PS_INSIDEFRAME;
   NormalPen.lopnWidth.x = width;
   NormalPen.lopnColor = pcolor;
   }

// function to return flood color as a RGB list

NODE *lfloodcolor()
   {
   if (bIndexMode)
      {
      int icolor = getindexcolor(RGB(dfldr, dfldg, dfldb));
      if (icolor >= 0) return(make_intnode(icolor));
      }

   return (
      cons(make_intnode((FIXNUM) dfldr),
      cons(make_intnode((FIXNUM) dfldg),
      cons(make_intnode((FIXNUM) dfldb),
      NIL
      ))));
   }

// funtion to set the flood color while updating palette if need be

void thefloodcolor(int r, int g, int b)
   {

   dfldr = r;
   dfldg = g;
   dfldb = b;

   if (EnablePalette)
      {
      fcolor = LoadColor((int) dfldr, (int) dfldg, (int) dfldb);
      }
   else
      {
      fcolor = RGB(dfldr, dfldg, dfldb);
      }

   FloodBrush.lbStyle = BS_SOLID;
   FloodBrush.lbColor = fcolor;
   FloodBrush.lbHatch = HS_VERTICAL;
   }

// function to return screen color as a RGB list

NODE *lscreencolor()
   {
   if (bIndexMode)
      {
      int icolor = getindexcolor(RGB(dscnr, dscng, dscnb));
      if (icolor >= 0) return(make_intnode(icolor));
      }

   return (
      cons(make_intnode((FIXNUM) dscnr),
      cons(make_intnode((FIXNUM) dscng),
      cons(make_intnode((FIXNUM) dscnb),
      NIL
      ))));
   }

// funtion to set the screen color while updating palette if need be

void thescreencolor(int r, int g, int b)
   {
   dscnr = r;
   dscng = g;
   dscnb = b;

   if (EnablePalette)
      {
      scolor = LoadColor((int) dscnr, (int) dscng, (int) dscnb);
      }
   else
      {
      scolor = RGB(dscnr, dscng, dscnb);
      }

   ScreenBrush.lbStyle = BS_SOLID;
   ScreenBrush.lbColor = scolor;
   ScreenBrush.lbHatch = HS_VERTICAL;

   // When the screen changes we change the erase pen which basically
   // writes the screen color

   ErasePen.lopnStyle = PS_INSIDEFRAME;
   ErasePen.lopnWidth.x = width;
   ErasePen.lopnColor = scolor;

   HBRUSH TempBrush = CreateBrushIndirect(&ScreenBrush);

   HDC ScreenDC = GetDC(MainWindowx->ScreenWindow->HWindow);

   // memory

   HDC MemDC = CreateCompatibleDC(ScreenDC);
   OldBitmap = (HBITMAP) SelectObject(MemDC, MemoryBitMap);

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

   SelectObject(MemDC, OldBitmap);
   DeleteDC(MemDC);
   ReleaseDC(MainWindowx->ScreenWindow->HWindow, ScreenDC);

   DeleteObject(TempBrush);

   MainWindowx->ScreenWindow->Invalidate(true);
   }

int get_ibm_pen_width()
   {
   return width;
   }


void set_ibm_pen_width(int w)
   {
   width = w;

   // we erase with the same pen width as we write

   NormalPen.lopnStyle = PS_INSIDEFRAME;
   NormalPen.lopnWidth.x = width;
   NormalPen.lopnColor = pcolor;

   ErasePen.lopnStyle = PS_INSIDEFRAME;
   ErasePen.lopnWidth.x = width;
   ErasePen.lopnColor = scolor;
   }

NODE *lclearpalette(void)
   {

   // kill the palette and recreate it with just black and white

   if (NOT_THROWING)
      {
      if (EnablePalette)
         {
         DeleteObject(ThePalette);

         MyLogPalette->palNumEntries = 2;

         if (status_flag) update_status_paletteuse();

         ThePalette = CreatePalette(MyLogPalette);

         ::InvalidateRect(MainWindowx->HWindow, NULL, TRUE);
         }
      }

   return (UNBOUND);
   }

NODE *lstatus(void)
   {

   // if status not running then run it

   if (!status_flag)
      {
      MainWindowx->MyPopupStatus();
      JustDidEdit = 1;
      }
   return (UNBOUND);
   }

NODE *lnostatus(void)
   {

   // if running then kill it

   if (status_flag)
      {
      MainWindowx->MyPopupStatusKill();
      }
   return (UNBOUND);
   }


void UpdateZoomControlFlag()
   {
   if ((the_zoom != 1.0) || CheckOnScreenControls())
      {
      zoom_flag = 1;
      }
   else
      {
      zoom_flag = 0;
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

void zoom_helper(NUMBER temp_zoom)
   {

   if (the_zoom != temp_zoom)
      {

      the_zoom = temp_zoom;

      TRect MainRect;
      MainWindowx->ScreenWindow->GetClientRect(MainRect);

      // calculate new scroller ranges
      int Xr = (BitMapWidth * the_zoom) - MainRect.right;
      int Yr = (BitMapHeight * the_zoom) - MainRect.bottom;

      if (Xr < 0) Xr = 0;
      if (Yr < 0) Yr = 0;

      // find out where we are (percentage of pos/range for x and y)
      NUMBER XRatio;
      NUMBER YRatio;

      if (MainWindowx->ScreenWindow->Scroller->XRange <= 0)
         {
         XRatio = 0.5;
         }
      else
         {
         XRatio = (NUMBER) MainWindowx->ScreenWindow->Scroller->XPos /
                  (NUMBER) MainWindowx->ScreenWindow->Scroller->XRange;
         }

      if (MainWindowx->ScreenWindow->Scroller->YRange <= 0)
         {
         YRatio = 0.5;
         }
      else
         {
         YRatio = (NUMBER) MainWindowx->ScreenWindow->Scroller->YPos /
                  (NUMBER) MainWindowx->ScreenWindow->Scroller->YRange;
         }

      // set the new ranges
      MainWindowx->ScreenWindow->Scroller->SetRange(Xr, Yr);

      // Position to the same percentage down the scroll bars as before
      MainWindowx->ScreenWindow->Scroller->ScrollTo(XRatio * Xr, YRatio * Yr);

      // hide turtle while we do this
      draw_turtle(0);

      UpdateZoomControlFlag();

      draw_turtle(1);

      // paint
      MainWindowx->ScreenWindow->Invalidate(true);
      }
   }

NODE *lzoom(NODE *arg)
   {
   NUMBER temp_zoom;

   NODE *val;

   // get arg

   val = numeric_arg(arg);

   if (nodetype(val) == INT) temp_zoom = (NUMBER) getint(val);
   else temp_zoom = getfloat(val);

   if (temp_zoom <= 0.0) temp_zoom = 1.0;

   zoom_helper(temp_zoom);

   return (UNBOUND);
   }


NODE *lbitblock(NODE *arg)
   {
   HDC ScreenDC;
   HDC MemDC;
   HBRUSH TempBrush;
   RECT TempRect;
   int CutWidth;
   int CutHeight;

   POINT dest;

   if (current_mode == perspectivemode)
      {
      VECTOR from3d;

      from3d.x = turtle_p[turtle_which].x / WorldWidth;
      from3d.y = turtle_p[turtle_which].y / WorldHeight;
      from3d.z = turtle_p[turtle_which].z / WorldDepth;

      if (!ThreeD.TransformPoint(from3d, dest)) return (UNBOUND);
      }
   else
      {
      dest.x = g_round(turtle_p[turtle_which].x);
      dest.y = g_round(turtle_p[turtle_which].y);
      }

   // get args

   CutWidth = getint(pos_int_arg(arg));
   CutHeight = getint(pos_int_arg(cdr(arg)));

   if (NOT_THROWING)
      {

      // only if a surface was specified continue or UAEs big time

      if ((CutWidth != 0) && (CutHeight != 0))
         {

         TempBrush = CreateBrushIndirect(&FloodBrush);

         ScreenDC = GetDC(MainWindowx->ScreenWindow->HWindow);

         // memory

         MemDC = CreateCompatibleDC(ScreenDC);
         OldBitmap = (HBITMAP) SelectObject(MemDC, MemoryBitMap);

         if (EnablePalette)
            {
            OldPalette = SelectPalette(MemDC, ThePalette, FALSE);
            RealizePalette(MemDC);
            }

         SetRect(&TempRect,
            +dest.x + xoffset,
            -dest.y + yoffset + LL - CutHeight,
            +dest.x + xoffset + CutWidth,
            -dest.y + yoffset + LL);

         FillRect(MemDC, &TempRect, TempBrush);

         SelectObject(MemDC, OldBitmap);
         if (EnablePalette)
            {
            SelectPalette(MemDC, OldPalette, FALSE);
            }
         DeleteDC(MemDC);

         //screen

         draw_turtle(0);

         if (EnablePalette)
            {
            OldPalette2 = SelectPalette(ScreenDC, ThePalette, FALSE);
            RealizePalette(ScreenDC);
            }

         if (zoom_flag)
            {
            MainWindowx->ScreenWindow->Invalidate(false);
            }
         else
            {
            SetRect(
               &TempRect,
               +dest.x - MainWindowx->ScreenWindow->Scroller->XPos + xoffset,
               -dest.y - MainWindowx->ScreenWindow->Scroller->YPos + yoffset + LL - CutHeight,
               +dest.x - MainWindowx->ScreenWindow->Scroller->XPos + xoffset + CutWidth,
               -dest.y - MainWindowx->ScreenWindow->Scroller->YPos + yoffset + LL);

            FillRect(ScreenDC, &TempRect, TempBrush);
            }

         if (EnablePalette)
            {
            SelectPalette(ScreenDC, OldPalette2, FALSE);
            }

         ReleaseDC(MainWindowx->ScreenWindow->HWindow, ScreenDC);

         DeleteObject(TempBrush);

         draw_turtle(1);

         }

      }
   return (UNBOUND);
   }

NODE *lbitmode(void)
   {
   int temp;

   // return the logo "code" for the bit mode

   switch (bitmode)
      {
       case SRCCOPY: temp = 1; break;
       case SRCPAINT: temp = 2; break;
       case SRCAND: temp = 3; break;
       case SRCINVERT: temp = 4; break;
       case SRCERASE: temp = 5; break;
       case NOTSRCCOPY: temp = 6; break;
       case NOTSRCERASE: temp = 7; break;
       case MERGEPAINT: temp = 8; break;
       case DSTINVERT: temp = 9; break;
      }

   return (make_intnode((FIXNUM) temp));
   }

NODE *lsetbitmode(NODE *arg)
   {

   // convert from logo "code" to Windows constants

   switch (int_arg(arg))
      {
       case 1: bitmode = SRCCOPY; break;
       case 2: bitmode = SRCPAINT; break;
       case 3: bitmode = SRCAND; break;
       case 4: bitmode = SRCINVERT; break;
       case 5: bitmode = SRCERASE; break;
       case 6: bitmode = NOTSRCCOPY; break;
       case 7: bitmode = NOTSRCERASE; break;
       case 8: bitmode = MERGEPAINT; break;
       case 9: bitmode = DSTINVERT; break;
       default:
           {
              MainWindowx->CommandWindow->MessageBox("Illegal Bitmode", "Error");
              err_logo(STOP_ERROR, NIL);
           }
      }

   return (UNBOUND);
   }

NODE *lturtlemode(void)
   {
   int temp;

   // return the logo "code" for the bit mode

   switch (turtle_bitmap[turtle_which])
      {
       case 0:
       case SRCCOPY: temp = 1; break;
       case SRCPAINT: temp = 2; break;
       case SRCAND: temp = 3; break;
       case SRCINVERT: temp = 4; break;
       case SRCERASE: temp = 5; break;
       case NOTSRCCOPY: temp = 6; break;
       case NOTSRCERASE: temp = 7; break;
       case MERGEPAINT: temp = 8; break;
       case DSTINVERT: temp = 9; break;
      }

   return (make_intnode((FIXNUM) temp));
   }

NODE *lsetturtlemode(NODE *arg)
   {

   // convert from logo "code" to Windows constants

   if (turtle_bitmap[turtle_which])
      {
      prepare_to_draw;
      draw_turtle(0);

      switch (int_arg(arg))
         {
          case 1: turtle_bitmap[turtle_which] = SRCCOPY; break;
          case 2: turtle_bitmap[turtle_which] = SRCPAINT; break;
          case 3: turtle_bitmap[turtle_which] = SRCAND; break;
          case 4: turtle_bitmap[turtle_which] = SRCINVERT; break;
          case 5: turtle_bitmap[turtle_which] = SRCERASE; break;
          case 6: turtle_bitmap[turtle_which] = NOTSRCCOPY; break;
          case 7: turtle_bitmap[turtle_which] = NOTSRCERASE; break;
          case 8: turtle_bitmap[turtle_which] = MERGEPAINT; break;
          case 9: turtle_bitmap[turtle_which] = DSTINVERT; break;
          default:
              {
                 MainWindowx->CommandWindow->MessageBox("Illegal Bitmode", "Error");
                 err_logo(STOP_ERROR, NIL);
              }
         }

      draw_turtle(1);
      done_drawing;
      }

   return (UNBOUND);
   }

NODE *lbitindex(void)
   {
   // return the current bitmap index

   return (make_intnode((FIXNUM) CutIndex));
   }

NODE *lsetbitindex(NODE *arg)
   {
   int i;

   // set the current bitmap index if within range

   i = getint(pos_int_arg(arg));

   if (i < MaxBitCuts)
      {
      CutIndex = i;
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox("BitMap Index out of range", "Error");
      err_logo(STOP_ERROR, NIL);
      }

   return (UNBOUND);
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

   CutBmp[CutBmpIndex].CutFlag = 0;
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
         if (status_flag)
            {
            update_status_paletteuse();
            }
         }

      // Let code know below that we have something

      CutBmp[CutBmpIndex].CutFlag = 1;

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
         CutBmp[CutBmpIndex].CutFlag = 1;
         }
      else
         {
         CutBmp[CutBmpIndex].CutFlag = 0;
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


NODE *lbitcut(NODE *arg)
   {
   HDC ScreenDC;
   HDC MemDC;
   HDC TempMemDC;

   HBRUSH TempBrush;

   RECT TempRect;

   int TempWidth;
   int TempHeight;
   int havebitmap;

   POINT dest;

   if (current_mode == perspectivemode)
      {
      VECTOR from3d;

      from3d.x = turtle_p[turtle_which].x / WorldWidth;
      from3d.y = turtle_p[turtle_which].y / WorldHeight;
      from3d.z = turtle_p[turtle_which].z / WorldDepth;

      if (!ThreeD.TransformPoint(from3d, dest)) return (UNBOUND);
      }
   else
      {
      dest.x = g_round(turtle_p[turtle_which].x);
      dest.y = g_round(turtle_p[turtle_which].y);
      }

   havebitmap = 0;

   TempWidth = getint(pos_int_arg(arg));
   TempHeight = getint(pos_int_arg(cdr(arg)));

   if (NOT_THROWING)
      {

      // if we had a old cut get rid of it, we won't go in for clipboard

      if (CutBmp[CutIndex].CutFlag)
         {

         // if same size reuse the bitmap

         if ((TempWidth == CutBmp[CutIndex].CutWidth) && (TempHeight == CutBmp[CutIndex].CutHeight))
            {
            havebitmap = 1;
            }

         // else get rid of it and make a new one later

         else
            {
            DeleteObject(CutBmp[CutIndex].CutMemoryBitMap);
            }
         CutBmp[CutIndex].CutFlag = 0;
         }

      CutBmp[CutIndex].CutWidth = TempWidth;
      CutBmp[CutIndex].CutHeight = TempHeight;

      // only if we have a surface continue

      if ((CutBmp[CutIndex].CutWidth != 0) && (CutBmp[CutIndex].CutHeight != 0))
         {

         // flag it so we will delete it

         CutBmp[CutIndex].CutFlag = 1;

         ScreenDC = GetDC(MainWindowx->ScreenWindow->HWindow);

         MemDC = CreateCompatibleDC(ScreenDC);
         OldBitmap = (HBITMAP) SelectObject(MemDC, MemoryBitMap);

         if (!havebitmap) CutBmp[CutIndex].CutMemoryBitMap = CreateCompatibleBitmap(ScreenDC, (int) (CutBmp[CutIndex].CutWidth), (int) (CutBmp[CutIndex].CutHeight));
         if (!CutBmp[CutIndex].CutMemoryBitMap)
            {
            MainWindowx->CommandWindow->MessageBox(
               "Cut failed, Possibly not enough Memory",
               "Error");
            err_logo(STOP_ERROR, NIL);
            return (UNBOUND);
            }

         TempMemDC = CreateCompatibleDC(ScreenDC);
         OldBitmap2 = (HBITMAP) SelectObject(TempMemDC, CutBmp[CutIndex].CutMemoryBitMap);

         BitBlt(
            TempMemDC,
            0,
            0,
            (int) (CutBmp[CutIndex].CutWidth),
            (int) (CutBmp[CutIndex].CutHeight),
            MemDC,
            +dest.x + xoffset,
            -dest.y + yoffset + LL - CutBmp[CutIndex].CutHeight,
            SRCCOPY);

         SelectObject(TempMemDC, OldBitmap2);
         DeleteDC(TempMemDC);

         // memory

         SetRect(
            &TempRect,
            +dest.x + xoffset,
            -dest.y + yoffset + LL - CutBmp[CutIndex].CutHeight,
            +dest.x + xoffset + CutBmp[CutIndex].CutWidth,
            -dest.y + yoffset + LL);

         TempBrush = CreateBrushIndirect(&ScreenBrush);

         FillRect(MemDC, &TempRect, TempBrush);

         SelectObject(MemDC, OldBitmap);
         DeleteDC(MemDC);

         //screen

         draw_turtle(0);

         if (zoom_flag)
            {
//            TRect temp;
//
//            temp.Set(
//               (+turtle_p[turtle_which].x - MainWindowx->Scroller->XPos / the_zoom + xoffset                                  ) * the_zoom,
//               (-turtle_p[turtle_which].y - MainWindowx->Scroller->YPos / the_zoom + yoffset + LL - CutBmp[CutIndex].CutHeight) * the_zoom,
//               (+turtle_p[turtle_which].x - MainWindowx->Scroller->XPos / the_zoom + xoffset + CutBmp[CutIndex].CutWidth      ) * the_zoom,
//               (-turtle_p[turtle_which].y - MainWindowx->Scroller->YPos / the_zoom + yoffset + LL                             ) * the_zoom);
//
//            temp.Normalize();
//            temp.Inflate(1+the_zoom,1+the_zoom);

            MainWindowx->ScreenWindow->Invalidate(false);
            }
         else
            {
            SetRect(&TempRect,
               +turtle_p[turtle_which].x - MainWindowx->ScreenWindow->Scroller->XPos + xoffset,
               -turtle_p[turtle_which].y - MainWindowx->ScreenWindow->Scroller->YPos + yoffset + LL - CutBmp[CutIndex].CutHeight,
               +turtle_p[turtle_which].x - MainWindowx->ScreenWindow->Scroller->XPos + xoffset + CutBmp[CutIndex].CutWidth,
               -turtle_p[turtle_which].y - MainWindowx->ScreenWindow->Scroller->YPos + yoffset + LL);

            FillRect(ScreenDC, &TempRect, TempBrush);
            }

         ReleaseDC(MainWindowx->ScreenWindow->HWindow, ScreenDC);

         DeleteObject(TempBrush);

         draw_turtle(1);

         // if CutIndex == 0 then do Clipboard

         if (CutIndex == 0)
            {
            CopyCutIndexToClipboard(CutIndex);
            }
         }

      }
   return (UNBOUND);
   }

NODE *lbitcopy(NODE *arg)
   {
   HDC ScreenDC;
   HDC MemDC;
   HDC TempMemDC;
   int TempWidth;
   int TempHeight;
   int havebitmap;

   POINT dest;

   if (current_mode == perspectivemode)
      {
      VECTOR from3d;

      from3d.x = turtle_p[turtle_which].x / WorldWidth;
      from3d.y = turtle_p[turtle_which].y / WorldHeight;
      from3d.z = turtle_p[turtle_which].z / WorldDepth;

      if (!ThreeD.TransformPoint(from3d, dest)) return (UNBOUND);
      }
   else
      {
      dest.x = g_round(turtle_p[turtle_which].x);
      dest.y = g_round(turtle_p[turtle_which].y);
      }

   havebitmap = 0;

   TempWidth = getint(pos_int_arg(arg));
   TempHeight = getint(pos_int_arg(cdr(arg)));

   if (NOT_THROWING)
      {

      // if we had a old cut get rid of it, we won't go in for clipboard

      if (CutBmp[CutIndex].CutFlag)
         {

         // if same size reuse the bitmap

         if ((TempWidth == CutBmp[CutIndex].CutWidth) &&
             (TempHeight == CutBmp[CutIndex].CutHeight))
            {
            havebitmap = 1;
            }
         else
            {
            // else get rid of it and make a new one later
            DeleteObject(CutBmp[CutIndex].CutMemoryBitMap);
            }
         CutBmp[CutIndex].CutFlag = 0;
         }

      CutBmp[CutIndex].CutWidth = TempWidth;
      CutBmp[CutIndex].CutHeight = TempHeight;

      // only if we have a surface continue

      if ((CutBmp[CutIndex].CutWidth != 0) && (CutBmp[CutIndex].CutHeight != 0))
         {

         // flag it so we will delete it

         CutBmp[CutIndex].CutFlag = 1;

         ScreenDC = GetDC(MainWindowx->ScreenWindow->HWindow);

         MemDC = CreateCompatibleDC(ScreenDC);
         OldBitmap = (HBITMAP) SelectObject(MemDC, MemoryBitMap);

         if (!havebitmap) CutBmp[CutIndex].CutMemoryBitMap = CreateCompatibleBitmap(ScreenDC, (int) (CutBmp[CutIndex].CutWidth), (int) (CutBmp[CutIndex].CutHeight));
         if (!CutBmp[CutIndex].CutMemoryBitMap)
            {
            MainWindowx->CommandWindow->MessageBox(
               "Cut failed, Possibly not enough Memory",
               "Error");
            err_logo(STOP_ERROR, NIL);
            return (UNBOUND);
            }

         TempMemDC = CreateCompatibleDC(ScreenDC);
         OldBitmap2 = (HBITMAP) SelectObject(TempMemDC, CutBmp[CutIndex].CutMemoryBitMap);

         BitBlt(
            TempMemDC,
            0,
            0,
            (int) (CutBmp[CutIndex].CutWidth),
            (int) (CutBmp[CutIndex].CutHeight),
            MemDC,
            +dest.x + xoffset,
            -dest.y + yoffset + LL - CutBmp[CutIndex].CutHeight, SRCCOPY);

         SelectObject(TempMemDC, OldBitmap2);
         DeleteDC(TempMemDC);

         SelectObject(MemDC, OldBitmap);
         DeleteDC(MemDC);

         ReleaseDC(MainWindowx->ScreenWindow->HWindow, ScreenDC);

         // if CutIndex == 0 then do Clipboard

         if (CutIndex == 0)
            {
            CopyCutIndexToClipboard(CutIndex);
            }
         }
      }
   return (UNBOUND);
   }

NODE *lbitfit(NODE *arg)
   {
   HDC ScreenDC;
   HDC MemDC;
   HDC TempMemDC;

   NUMBER FitHeight;
   NUMBER FitWidth;

   HBITMAP TempMemoryBitMap;

   FitWidth = getint(pos_int_arg(arg));
   FitHeight = getint(pos_int_arg(cdr(arg)));

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

         ScreenDC = GetDC(MainWindowx->ScreenWindow->HWindow);

         MemDC = CreateCompatibleDC(ScreenDC);
         OldBitmap = (HBITMAP) SelectObject(MemDC, CutBmp[CutIndex].CutMemoryBitMap);

         if (EnablePalette)
            {
            OldPalette2 = SelectPalette(ScreenDC, ThePalette, FALSE);
            RealizePalette(ScreenDC);

            OldPalette = SelectPalette(MemDC, ThePalette, FALSE);
            RealizePalette(MemDC);
            }

         TempMemoryBitMap = CreateCompatibleBitmap(ScreenDC, (int) (FitWidth), (int) (FitHeight));
         if (!TempMemoryBitMap)
            {
            MainWindowx->CommandWindow->MessageBox("Fit failed, Possibly not enough Memory", "Error");
            err_logo(STOP_ERROR, NIL);
            return (UNBOUND);
            }

         TempMemDC = CreateCompatibleDC(ScreenDC);
         OldBitmap2 = (HBITMAP) SelectObject(TempMemDC, TempMemoryBitMap);

         if (EnablePalette)
            {
            SelectPalette(ScreenDC, OldPalette2, FALSE);
            }

         ReleaseDC(MainWindowx->ScreenWindow->HWindow, ScreenDC);

         if (EnablePalette)
            {
            OldPalette2 = SelectPalette(TempMemDC, ThePalette, FALSE);
            RealizePalette(TempMemDC);
            }

         SetStretchBltMode(TempMemDC, COLORONCOLOR);

         // Load hour-glass cursor.
         hCursor =::SetCursor(hCursorWait);

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

         // Reload arrow cursor.
         ::SetCursor(hCursor);

         if (EnablePalette)
            {
            SelectPalette(MemDC, OldPalette, FALSE);
            SelectPalette(TempMemDC, OldPalette2, FALSE);
            }

         SelectObject(TempMemDC, OldBitmap2);
         DeleteDC(TempMemDC);

         SelectObject(MemDC, OldBitmap);
         DeleteDC(MemDC);

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
   return (UNBOUND);
   }

NODE *lbitpaste(void)
   {
   HDC ScreenDC;
   HDC MemDC;
   HDC TempMemDC;

   POINT dest;

   if (current_mode == perspectivemode)
      {
      VECTOR from3d;

      from3d.x = turtle_p[turtle_which].x / WorldWidth;
      from3d.y = turtle_p[turtle_which].y / WorldHeight;
      from3d.z = turtle_p[turtle_which].z / WorldDepth;

      if (!ThreeD.TransformPoint(from3d, dest)) return (UNBOUND);
      }
   else
      {
      dest.x = g_round(turtle_p[turtle_which].x);
      dest.y = g_round(turtle_p[turtle_which].y);
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
            CutBmp[CutIndex].CutFlag = 0;
            }

         ScreenDC = GetDC(MainWindowx->ScreenWindow->HWindow);

         TempMemDC = CreateCompatibleDC(ScreenDC);
         OldBitmap2 = (HBITMAP) SelectObject(TempMemDC, CutBmp[CutIndex].CutMemoryBitMap);

         //memory

         MemDC = CreateCompatibleDC(ScreenDC);
         OldBitmap = (HBITMAP) SelectObject(MemDC, MemoryBitMap);

         BitBlt(
            MemDC,
            +dest.x + xoffset,
            -dest.y + yoffset + LL - CutBmp[CutIndex].CutHeight,
            (int) (CutBmp[CutIndex].CutWidth),
            (int) (CutBmp[CutIndex].CutHeight),
            TempMemDC, 0, 0, bitmode);

         SelectObject(MemDC, OldBitmap);
         DeleteDC(MemDC);

         //screen

         draw_turtle(0);

         if (zoom_flag)
            {
//            TRect temp;
//
//            temp.Set(
//               (+turtle_p[turtle_which].x - MainWindowx->Scroller->XPos / the_zoom + xoffset                                  ) * the_zoom,
//               (-turtle_p[turtle_which].y - MainWindowx->Scroller->YPos / the_zoom + yoffset + LL - CutBmp[CutIndex].CutHeight) * the_zoom,
//               (+turtle_p[turtle_which].x - MainWindowx->Scroller->XPos / the_zoom + xoffset + CutBmp[CutIndex].CutWidth      ) * the_zoom,
//               (-turtle_p[turtle_which].y - MainWindowx->Scroller->YPos / the_zoom + yoffset + LL                             ) * the_zoom);
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
               bitmode);
            }

         ReleaseDC(MainWindowx->ScreenWindow->HWindow, ScreenDC);

         draw_turtle(1);

         SelectObject(TempMemDC, OldBitmap2);
         DeleteDC(TempMemDC);

         // Clipboard owns what we paste in not what we converted
         }
      else
         {
         MainWindowx->CommandWindow->MessageBox("Nothing to Paste", "Error");
         err_logo(STOP_ERROR, NIL);
         }
      }
   return (UNBOUND);
   }

NODE *lbitpastetoindex(NODE *arg)
   {
   HDC ScreenDC;
   HDC MemDC;
   HDC TempMemDC;

   // set the current bitmap index if within range
   int i = getint(pos_int_arg(arg));
   int x = getint(pos_int_arg(cdr(arg)));
   int y = getint(pos_int_arg(cdr(cdr(arg))));

   if (i < MaxBitCuts)
      {
      //      CutIndex = i;
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox("BitMap Index out of range", "Error");
      err_logo(STOP_ERROR, NIL);
      return (UNBOUND);
      }

   if (!CutBmp[i].CutFlag)
      {
      MainWindowx->CommandWindow->MessageBox(
         "BitMap at Index must be initialized with a bitmap",
         "Error");
      err_logo(STOP_ERROR, NIL);
      return (UNBOUND);
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
            CutBmp[CutIndex].CutFlag = 0;
            }

         ScreenDC = GetDC(MainWindowx->ScreenWindow->HWindow);

         TempMemDC = CreateCompatibleDC(ScreenDC);
         OldBitmap2 = (HBITMAP) SelectObject(TempMemDC, CutBmp[CutIndex].CutMemoryBitMap);

         //memory

         MemDC = CreateCompatibleDC(ScreenDC);
         OldBitmap = (HBITMAP) SelectObject(MemDC, CutBmp[i].CutMemoryBitMap);

         BitBlt(
            MemDC,
            +x,
            CutBmp[i].CutHeight - y - CutBmp[CutIndex].CutHeight,
            (int) (CutBmp[CutIndex].CutWidth),
            (int) (CutBmp[CutIndex].CutHeight),
            TempMemDC,
            0,
            0,
            bitmode);

         SelectObject(MemDC, OldBitmap);
         DeleteDC(MemDC);

         ReleaseDC(MainWindowx->ScreenWindow->HWindow, ScreenDC);

         SelectObject(TempMemDC, OldBitmap2);
         DeleteDC(TempMemDC);

         // Clipboard owns what we paste in not what we converted
         }
      else
         {
         MainWindowx->CommandWindow->MessageBox("Nothing to Paste", "Error");
         err_logo(STOP_ERROR, NIL);
         }
      }
   return (UNBOUND);
   }

NODE *lsetturtle(NODE *arg)
   {
   NODE *val;
   int temp;

   val = numeric_arg(arg);

   if (NOT_THROWING)
      {
      draw_turtles(0);
      temp = getint(val);
      if ((temp >= (TURTLES - TURTLEN)) || (temp < -TURTLEN))
         {
         MainWindowx->CommandWindow->MessageBox("Bad Turtle Id", "Error");
         err_logo(STOP_ERROR, NIL);
         }
      else
         {

         turtle_which = temp;

         if (turtle_which > turtle_max)
            {
            for (int i = turtle_max + 1; i <= turtle_which; i++)
               {
               turtle_p[i].x = 0.0;
               turtle_p[i].y = 0.0;
               turtle_p[i].z = 0.0;
               turtle_heading[i] = 0.0;
               turtle_shown[i] = TRUE;
               turtle_bitmap[i] = 0;
               turtle_matrix[i].e11 = 1.0;
               turtle_matrix[i].e12 = 0.0;
               turtle_matrix[i].e13 = 0.0;
               turtle_matrix[i].e21 = 0.0;
               turtle_matrix[i].e22 = 1.0;
               turtle_matrix[i].e23 = 0.0;
               turtle_matrix[i].e31 = 0.0;
               turtle_matrix[i].e32 = 0.0;
               turtle_matrix[i].e33 = 1.0;
               }
            turtle_max = turtle_which;
            }

         if (turtle_which < 0) turtle_which = (TURTLES - (TURTLEN+1)) - turtle_which;

         if (status_flag)
            {
            update_status_turtlevisability();
            update_status_turtleposition();
            update_status_turtleheading();
            update_status_turtleroll();
            update_status_turtlepitch();
            update_status_pencontact();
            update_status_turtlewhich();
            }

extern FLONUM wanna_x;
extern FLONUM wanna_y;
extern FLONUM wanna_z;

         wanna_x = turtle_p[turtle_which].x;
         wanna_y = turtle_p[turtle_which].y;
         wanna_z = turtle_p[turtle_which].z;

         draw_turtles(1);
         }
      }

   return (UNBOUND);
   }

NODE *lturtle()
   {
   if (turtle_which >= TURTLES - TURTLEN)
      return (make_intnode(-(turtle_which - (TURTLES - (TURTLEN+1)))));
   else
      return (make_intnode(turtle_which));
   }

NODE *lturtles()
   {
   return (make_intnode(turtle_max));
   }

void turtlepaste(int turtle_which)
   {
   HDC ScreenDC;
   HDC TempMemDC;

   POINT dest;

   if (current_mode == perspectivemode)
      {
      VECTOR from3d;

      from3d.x = turtle_p[turtle_which].x / WorldWidth;
      from3d.y = turtle_p[turtle_which].y / WorldHeight;
      from3d.z = turtle_p[turtle_which].z / WorldDepth;

      if (!ThreeD.TransformPoint(from3d, dest)) return;
      }
   else
      {
      dest.x = g_round(turtle_p[turtle_which].x);
      dest.y = g_round(turtle_p[turtle_which].y);
      }

   if (NOT_THROWING)
      {

      // If ClipBoard check with ClipBoard only

      if (turtle_which == 0)
         {
         PasteFromClipboardToCutIndex(turtle_which);
         }

      // only if we have something to paste

      if (CutBmp[turtle_which].CutFlag)
         {

         // if clipboard then never leave Cut Flag true

         if (turtle_which == 0)
            {
            CutBmp[turtle_which].CutFlag = 0;
            }

         ScreenDC = GetDC(MainWindowx->ScreenWindow->HWindow);

         TempMemDC = CreateCompatibleDC(ScreenDC);
         OldBitmap2 = (HBITMAP) SelectObject(TempMemDC, CutBmp[turtle_which].CutMemoryBitMap);

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
               -dest.y - MainWindowx->ScreenWindow->Scroller->YPos / the_zoom + yoffset + LL - CutBmp[turtle_which].CutHeight,
               (int) (CutBmp[turtle_which].CutWidth),
               (int) (CutBmp[turtle_which].CutHeight),
               TempMemDC, 0, 0, turtle_bitmap[turtle_which]);
            }
         else
            {
            BitBlt(
               ScreenDC,
               +dest.x - MainWindowx->ScreenWindow->Scroller->XPos + xoffset,
               -dest.y - MainWindowx->ScreenWindow->Scroller->YPos + yoffset + LL - CutBmp[turtle_which].CutHeight,
               (int) (CutBmp[turtle_which].CutWidth),
               (int) (CutBmp[turtle_which].CutHeight),
               TempMemDC, 0, 0, turtle_bitmap[turtle_which]);
            }

         ReleaseDC(MainWindowx->ScreenWindow->HWindow, ScreenDC);

         SelectObject(TempMemDC, OldBitmap2);
         DeleteDC(TempMemDC);
         }
      else
         {
         turtle_bitmap[turtle_which] = 0;
         char szWinLocStr[WININISIZ];
         sprintf(szWinLocStr, "Turtle %d has no picture, will Halt", turtle_which);
         MainWindowx->CommandWindow->MessageBox(szWinLocStr, "Error");
         err_logo(STOP_ERROR, NIL);
         }
      }
   }

NODE *lscrollx(NODE *arg)
   {
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

   return (UNBOUND);
   }

NODE *lscrolly(NODE *arg)
   {
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

   return (UNBOUND);
   }

NODE *lsetfocus(NODE *arg)
   {
   char textbuf[MAX_BUFFER_SIZE];
   cnv_strnode_string(textbuf, arg);

   if (0 == stricmp("MSWLogo Screen", textbuf) ||
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

   JustDidEdit = 1;

   return (UNBOUND);
   }

NODE *lgetfocus(void)
   {
   NODE *arg;
   NODE *val;

   char textbuf[MAX_BUFFER_SIZE];
   memset(textbuf, 0, MAX_BUFFER_SIZE);

   // Get handle to active window
   HWND TempH = GetActiveWindow();

   // It better exist, get it's caption

   if (TempH != NULL)
      {
      ::GetWindowText(TempH, textbuf, MAX_BUFFER_SIZE);
      }

   JustDidEdit = 1;

   // Return caption as a list

   arg = make_strnode(textbuf, NULL, strlen(textbuf), STRING, strnzcpy);
   val = arg; // parser(arg, FALSE);
   return (val);
   }

NODE *lwindowset(NODE *args)
   {
   char textbuf[MAX_BUFFER_SIZE];
   int value;

   HWND EditH;

   cnv_strnode_string(textbuf, args);
   value = getint(pos_int_arg(cdr(args)));

   // get handle to Window with arg as Caption

   EditH = FindWindow(NULL, textbuf);

   // if it exists icon it.

   if (EditH != NULL)
      {
      ShowWindow(EditH, value);
      }

   JustDidEdit = 1;

   return (UNBOUND);
   }

void ibm_clear_screen(void)
   {
   HBRUSH tempBrush = ::CreateBrushIndirect(&ScreenBrush);
   if (tempBrush != NULL)
      {
      HDC screen = ::GetDC(MainWindowx->ScreenWindow->HWindow);

      // memory
      HDC memoryDC = ::CreateCompatibleDC(screen);
      HBITMAP oldBitmap = (HBITMAP) ::SelectObject(memoryDC, MemoryBitMap);

      ::FillRect(memoryDC, &FullRect, tempBrush);

      ::SetBkColor(memoryDC, scolor);
      ::SetBkMode(memoryDC, TRANSPARENT);

      ::SelectObject(memoryDC, oldBitmap);
      ::DeleteDC(memoryDC);

      ::ReleaseDC(MainWindowx->ScreenWindow->HWindow, screen);
      ::DeleteObject(tempBrush);
   }

   MainWindowx->ScreenWindow->Invalidate(false);
   }

void option_helper(short *var, NODE *arg)
   {
   NODE *val = integer_arg(arg);
   if (NOT_THROWING)
      {
      *var = (short) getint(val);
      }
   }

int CALLBACK
FindFont(
    const LOGFONT    *  LogFont,     // pointer to logical-font data
    const TEXTMETRIC *  TextMetric,  // pointer to physical-font data
    unsigned long       FontType,    // type of font
    LPARAM              lParam       // address of application-defined data
)
   {
   // check for a match
   if (stricmp(tempfont, LogFont->lfFaceName) == 0)
      {
      // take a copy, flag one was found and return
      FontRec = *LogFont;
      found = 1;
      return 0;  // stop enumerating fonts
      }

   return 1; // keep enumerating fonts
   }


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


void setfont(const char *fontname)
   {
   HDC hdc = GetDC(::GetFocus());

   // set global font to compare to (FontRec will get filled if found)
   // BUG: use the user context, instead of global variables
   found = 0;
   tempfont = fontname;
   EnumFontFamilies(hdc, NULL, FindFont, NULL);

   // if not found enumerate again with printing enabled
   if (!found)
      {
      printfx(
         "Sorry, no font named %s was found.  Choose one of the following:\n",
         fontname);

      EnumFontFamilies(hdc, NULL, PrintFont, NULL);
      }

   ReleaseDC(::GetFocus(), hdc);
   }

void do_help(char *arg)
   {

   /* if arg NULL then jump to index else try to lookup key */

   if (arg == NULL)
      {
      MainWindowx->WinHelp(szHelpFileName, HELP_INDEX, 0L);
      }
   else
      {
      MainWindowx->WinHelp(szHelpFileName, HELP_PARTIALKEY, (DWORD) arg);
      }
   JustDidEdit = 1;
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

   return (UNBOUND);
   }

NODE *lwinhelp(NODE *arg)
   {
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

   return (UNBOUND);
   }

NODE *lsetlabelfont(NODE *arg)
   {

   NODE *args = list_arg(arg);
   if (car(args) == NIL)
      {
      return (NIL);
      }

   if (NOT_THROWING)
      {
      char textbuf[MAX_BUFFER_SIZE];
      cnv_strnode_string(textbuf, args);

      // Get the FontRec filled with a match to textbuf
      setfont(textbuf);

      // now fill in the rest of the fields if given

      if (cdr(args) != NIL)
         FontRec.lfHeight = int_arg(args = cdr(args));
      if (cdr(args) != NIL)
         FontRec.lfWidth = getint(pos_int_arg(args = cdr(args)));
      if (cdr(args) != NIL)
         FontRec.lfOrientation = getint(pos_int_arg(args = cdr(args)));
      if (cdr(args) != NIL)
         FontRec.lfWeight = getint(pos_int_arg(args = cdr(args)));
      if (cdr(args) != NIL)
         FontRec.lfItalic = getint(pos_int_arg(args = cdr(args)));
      if (cdr(args) != NIL)
         FontRec.lfUnderline = getint(pos_int_arg(args = cdr(args)));
      if (cdr(args) != NIL)
         FontRec.lfStrikeOut = getint(pos_int_arg(args = cdr(args)));
      if (cdr(args) != NIL)
         FontRec.lfCharSet = getint(pos_int_arg(args = cdr(args)));
      if (cdr(args) != NIL)
         FontRec.lfOutPrecision = getint(pos_int_arg(args = cdr(args)));
      if (cdr(args) != NIL)
         FontRec.lfClipPrecision = getint(pos_int_arg(args = cdr(args)));
      if (cdr(args) != NIL)
         FontRec.lfQuality = getint(pos_int_arg(args = cdr(args)));
      if (cdr(args) != NIL)
         FontRec.lfPitchAndFamily = getint(pos_int_arg(args = cdr(args)));

      // update status window

      //      if (status_flag)
      //         {
      //         update_status_fontwieght();
      //         update_status_fontsize();
      //         update_status_fontname();
      //         }
      }

   return (UNBOUND);
   }

NODE *llabelfont(void)
   {
   NODE *val;
   NODE *targ;

   // put the Font name in a list

   targ = make_strnode(FontRec.lfFaceName, NULL, strlen(FontRec.lfFaceName), STRING, strnzcpy);
   val = parser(targ, FALSE);

   // now return the whole thing as a list

   return (
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
                                             NIL
                                          )
                                       )
                                    )
                                 )
                              )
                           )
                        )
                     )
                  )
               )
            )
         )
      )
   );

   }

NODE *lmachine(void)
   {
   int ScreenWidth;
   int ScreenHeight;

   // build list with system specific information

   HDC tempDC = GetDC(0);

   ScreenWidth  = GetDeviceCaps(tempDC, HORZRES);
   ScreenHeight = GetDeviceCaps(tempDC, VERTRES);

   ReleaseDC(0, tempDC);

   TRect wrect;
   MainWindowx->GetWindowRect(wrect);

   return (
      cons(make_intnode((FIXNUM) 1),
      cons(make_intnode((FIXNUM) 32),
      cons(make_intnode((FIXNUM) BitMapWidth),
      cons(make_intnode((FIXNUM) BitMapHeight),
      cons(make_intnode((FIXNUM) EnablePalette),
      cons(make_intnode((FIXNUM) (LOBYTE(LOWORD(GetVersion())))),
      cons(make_intnode((FIXNUM) (HIBYTE(LOWORD(GetVersion())))),
      cons(make_intnode((FIXNUM) MaxWidth),
      cons(make_intnode((FIXNUM) MaxHeight),
      cons(make_intnode((FIXNUM) ScreenWidth),
      cons(make_intnode((FIXNUM) ScreenHeight),
      cons(make_intnode((FIXNUM) (wrect.right - wrect.left)),
      cons(make_intnode((FIXNUM) (wrect.bottom - wrect.top)),
      NIL))))))))))))));

   }

SIZE labelsize(const char *s)
   {
   SIZE size = {0};
   
   HDC screen = GetDC(MainWindowx->ScreenWindow->HWindow);
   if (screen != NULL)
      {
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

      ReleaseDC(MainWindowx->ScreenWindow->HWindow, screen);
      }

   return size;
   }

void label(const char *s)
   {
   POINT dest;

   if (current_mode == perspectivemode)
      {
      VECTOR from3d;

      from3d.x = turtle_p[turtle_which].x / WorldWidth;
      from3d.y = turtle_p[turtle_which].y / WorldHeight;
      from3d.z = turtle_p[turtle_which].z / WorldDepth;

      if (!ThreeD.TransformPoint(from3d, dest)) return;
      }
   else
      {
      dest.x = g_round(turtle_p[turtle_which].x);
      dest.y = g_round(turtle_p[turtle_which].y);
      }

   HDC ScreenDC = GetDC(MainWindowx->ScreenWindow->HWindow);

   // memory
   HDC MemDC = CreateCompatibleDC(ScreenDC);
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

   FontRec.lfEscapement = (360.0 - (turtle_heading[turtle_which] - 90.0)) * 10;
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
   DeleteDC(MemDC);


   // screen
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

   ReleaseDC(MainWindowx->ScreenWindow->HWindow, ScreenDC);
   }

void exit_program(void)
   {
   if (halt_flag != 0)
      {
      Time_To_Halt = 1;
      }
   Time_To_Exit = 1;
   }

