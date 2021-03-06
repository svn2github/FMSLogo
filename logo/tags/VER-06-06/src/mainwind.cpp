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

#define MAX_PENDING_CONNECTS 4   // The backlog allowed for listen()


void qlist::insert(ent a, int t)
   {

   /* class "event list queue" member to insert event */

   qlink *h;
   qlink *ph;

   if (last)
      {
      ph = last->next;
      h = new qlink(a, NULL, NULL, t);
      last->next = h;
      h->prev = last;
      h->next = ph;
      ph->prev = h;
      last = last->next;
      }
   else
      {
      last = new qlink(a, NULL, NULL, t);
      last->next = last;
      last->prev = last;
      }
   }

ent qlist::get(void)
   {

   /* class "event list queue" member to get event */

   if (last == NULL) return NULL;

   return (last->next->e);
   }

void qlist::zap(void)
   {

   /* class "event list queue" member to zap all events */

   qlink *p;

   if (last == NULL) return;

   p = last->next;

   if (last == p)
      {
      last = NULL;
      }
   else
      {
      p->prev->next = p->next;
      p->next->prev = p->prev;
      }

   delete p;

   }

void qlist::clear()
   {
   qlink *l = last;

   if (l == NULL) return;

   do
      {
      qlink *ll = l;
      l = l->next;
      delete ll;
      }
   while (l != last);
   }

calllist calllists;


TScreenWindow::TScreenWindow(
   TWindow *AParent,
   LPCSTR   ATitle
) : TWindow(AParent, ATitle)
   {
   if (!bFixed)
      {
      Attr.Style |= WS_VSCROLL | WS_HSCROLL;
      }
   Attr.Style |= WS_BORDER;
   	
   Scroller = new TScroller(this, 1, 1, BitMapWidth, BitMapHeight);
   }

TScreenWindow::~TScreenWindow()
   {
      delete Scroller;
   }

void TScreenWindow::SetupWindow()
   {
   TWindow::SetupWindow();

   /* adjust scrollers */
   const TRect clientRect = GetClientRect();

   Scroller->SetRange(
      BitMapWidth - clientRect.Width(),
      BitMapHeight - clientRect.Height());

   Scroller->ScrollTo(
      (BitMapWidth  - clientRect.Width()) / 2,
      (BitMapHeight - clientRect.Height()) / 2);
   }



void TScreenWindow::Paint(TDC &PaintDC, bool /* erase */, TRect &PaintRect)
   {

   /*
      This is a compromise between speed and memory (as is most code).
      All drawing is written to the backing store 1 to 1 even when zoomed.
      When zoomed all drawing and painting is scaled to the display on the fly.
      Painting can be a bit slow while zoomed. It also can be inaccurate when
      mixing scaled painting and scaled drawing. Printing is never zoomed.
      User can use Bitfit if he/she wants data scaled.

      Must of rewrote this routine 20 times, at least.
    */

   // grab the client area's backing store (a bitmap)
   HDC screenDC = GetDC(HWindow);
   HDC memoryDC = CreateCompatibleDC(screenDC);

   HBITMAP oldBitmap = (HBITMAP) SelectObject(memoryDC, MemoryBitMap);

   HPALETTE oldPalette  = NULL;
   HPALETTE oldPalette2 = NULL;

   /* if palette allocate it */

   if (EnablePalette)
      {
      oldPalette = SelectPalette(PaintDC, ThePalette, FALSE);
      RealizePalette(PaintDC);

      oldPalette2 = SelectPalette(memoryDC, ThePalette, FALSE);
      RealizePalette(memoryDC);
      }

   /* if 1 to 1 the just do normal paint */

   if (the_zoom == 1.0)
      {
      BitBlt(
         PaintDC,
         PaintRect.Left(),
         PaintRect.Top(),
         PaintRect.Width(),
         PaintRect.Height(),
         memoryDC,
         PaintRect.Left(),
         PaintRect.Top(),
         SRCCOPY);
      }

   /* else compute scaling and then display */

   else if (the_zoom > 1.0)
      {
      TRect TempRect;

      TempRect = PaintRect;

      TempRect.Inflate(((int) (the_zoom+0.5))*2, ((int) (the_zoom+0.5))*2);

      TempRect.left   /= the_zoom;
      TempRect.top    /= the_zoom;
      TempRect.right  /= the_zoom;
      TempRect.bottom /= the_zoom;

      if (TempRect.left < 0)
         {
         TempRect.left = 0;
         }
      if (TempRect.top < 0)
         {
         TempRect.top = 0;
         }
      if (TempRect.right > BitMapWidth)
         {
         TempRect.right = BitMapWidth;
         }
      if (TempRect.bottom > BitMapHeight)
         {
         TempRect.bottom = BitMapHeight;
         }

      SetStretchBltMode(PaintDC, COLORONCOLOR);

      StretchBlt(
         PaintDC,
         TempRect.Left()   * the_zoom,
         TempRect.Top()    * the_zoom,
         TempRect.Width()  * the_zoom,
         TempRect.Height() * the_zoom,
         memoryDC,
         TempRect.Left()  ,
         TempRect.Top()   ,
         TempRect.Width() ,
         TempRect.Height(),
         SRCCOPY);
      }
   else
      {
      /* else compute scaling and then display */
      SetStretchBltMode(PaintDC, COLORONCOLOR);

      StretchBlt(
         PaintDC,
         0,
         0,
         BitMapWidth * the_zoom,
         BitMapHeight * the_zoom,
         memoryDC,
         0,
         0,
         BitMapWidth,
         BitMapHeight,
         SRCCOPY);
      }

   /* restore resources */

   if (EnablePalette)
      {
      SelectPalette(memoryDC, oldPalette2, FALSE);
      SelectPalette(PaintDC, oldPalette, FALSE);
      }

   SelectObject(memoryDC, oldBitmap);
   DeleteDC(memoryDC);
   ReleaseDC(HWindow, screenDC);

   /* if turtle do it */

   SetROP2(PaintDC, R2_NOT);

   for (int j = 0; j <= turtle_max; j++)
      {
      if (turtle_shown[j])
         {
         if (turtle_bitmap[j])
            {
            turtlepaste(j);
            }
         else
            {
            for (int i = 0; i < 4; i++)
               {
               if (TurtlePoints[j][i].bValid)
                  {
                  MoveToEx(PaintDC,
                     TurtlePoints[j][i].from.x * the_zoom,
                     TurtlePoints[j][i].from.y * the_zoom, 0);

                  LineTo(PaintDC,
                     TurtlePoints[j][i].to.x * the_zoom,
                     TurtlePoints[j][i].to.y * the_zoom);
                  }
               }
            }
         }
      }
   }

void TScreenWindow::Printit(TDC &PrintDC)
   {

   /*
      Must of rewrote this at least 25 times :-) and it still does not
      work in some situations. This is just the "Paint" of printing.
      See the print module for all the other stuff.
   */

   long TempWidth;
   long TempHeight;
   long ScanLines;
   long Status;

   LPSTR BitsPtr;
   HBITMAP BitsHandle;

   BITMAPINFO *PrintBitmapInfo;

   WORD PrintbitCount;
   WORD ScreenbitCount;
   WORD size;

   /* do we even have a chance ? */

   if ((GetDeviceCaps(PrintDC, RASTERCAPS) & RC_STRETCHDIB) == 0)
      {
      MessageBox("Print driver does not support this function", "Error");
      return;
      }

   PrintbitCount = GetDeviceCaps(PrintDC, BITSPIXEL);
   PrintbitCount *= GetDeviceCaps(PrintDC, PLANES);

   // If a mono printer lets let it try to dither a 256 grey scale image
   if (PrintbitCount == 1) PrintbitCount = 8;

   // Get screen bitCount
   HDC ScreenDC = GetDC(0);

   ScreenbitCount = GetDeviceCaps(ScreenDC, BITSPIXEL);
   ScreenbitCount *= GetDeviceCaps(ScreenDC, PLANES);

   // Don't bother creating a DIB with more colors than we have
   if (ScreenbitCount < PrintbitCount) PrintbitCount = ScreenbitCount;

   // Round to nearest legal bitmap color depth
   if      (                        (PrintbitCount <  1)) PrintbitCount =  1;
   else if ((PrintbitCount >  1) && (PrintbitCount <  4)) PrintbitCount =  4;
   else if ((PrintbitCount >  4) && (PrintbitCount <  8)) PrintbitCount =  8;
   else if ((PrintbitCount >  8) && (PrintbitCount < 16)) PrintbitCount = 16;
   else if ((PrintbitCount > 16) && (PrintbitCount < 24)) PrintbitCount = 24;
   else if ((PrintbitCount > 24)                        ) PrintbitCount = 32;

   PrintbitCount = GetPrivateProfileInt("LOGO", "PrintColorDepth", PrintbitCount, "LOGO.INI");

   if (PrintbitCount <= 8)
      {
      size = sizeof(BITMAPINFOHEADER) + ((1 << PrintbitCount) * sizeof(RGBQUAD));
      }
   else
      {
      size = sizeof(BITMAPINFOHEADER);
      }

   PrintBitmapInfo = (BITMAPINFO *) new char[size];

   PrintBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   PrintBitmapInfo->bmiHeader.biWidth = BitMapWidth;
   PrintBitmapInfo->bmiHeader.biHeight = BitMapHeight;
   PrintBitmapInfo->bmiHeader.biPlanes = 1;
   PrintBitmapInfo->bmiHeader.biBitCount = PrintbitCount;
   PrintBitmapInfo->bmiHeader.biCompression = BI_RGB;
   PrintBitmapInfo->bmiHeader.biSizeImage = ((((PrintBitmapInfo->bmiHeader.biWidth * PrintBitmapInfo->bmiHeader.biBitCount) + 31) / 32) * 4) * PrintBitmapInfo->bmiHeader.biHeight;
   PrintBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
   PrintBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
   PrintBitmapInfo->bmiHeader.biClrUsed = 0;
   PrintBitmapInfo->bmiHeader.biClrImportant = 0;

   /* we don't need hour glass here because print module takes care of it */

   BitsHandle = (HBITMAP) GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, PrintBitmapInfo->bmiHeader.biSizeImage);

   /* If fail try again after a compact */

   if (!BitsHandle)
      {
      GlobalCompact(-1);
      BitsHandle = (HBITMAP) GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, PrintBitmapInfo->bmiHeader.biSizeImage);
      }

   /* if we got the memory continue */

   if (BitsHandle)
      {

      /* get printer size per inch */

      TempWidth = GetDeviceCaps(PrintDC, LOGPIXELSX);
      TempHeight = GetDeviceCaps(PrintDC, LOGPIXELSY);

      /* if palette allocate it */

      if (EnablePalette)
         {
         OldPalette = SelectPalette(ScreenDC, ThePalette, FALSE);
         RealizePalette(ScreenDC);
         }

      /* set up an assured contrast ? */

      SetTextColor(PrintDC, 0x00000000L);
      SetBkColor(PrintDC, 0x00ffffffL);

      /* where is that memory anyway */

      BitsPtr = (LPSTR) GlobalLock((HGLOBAL) BitsHandle);

      ScanLines = GetDIBits(
         ScreenDC,
         MemoryBitMap,
         0,
         BitMapHeight,
         BitsPtr,
         PrintBitmapInfo,
         DIB_RGB_COLORS);

      /* check we got something */

      if (ScanLines != 0)
         {
         /* if "active area" just print that */

         if (IsPrinterSettingCustom)
            {
            Status = StretchDIBits(
               PrintDC,
               0,
               0,
               (TempWidth * (PrinterAreaXHigh - PrinterAreaXLow)) / PrinterAreaPixels,
               (TempHeight * (PrinterAreaYHigh - PrinterAreaYLow)) / PrinterAreaPixels,
               +PrinterAreaXLow + xoffset,
               BitMapHeight - (-PrinterAreaYLow + yoffset),
               PrinterAreaXHigh - PrinterAreaXLow,
               PrinterAreaYHigh - PrinterAreaYLow,
               BitsPtr,
               PrintBitmapInfo,
               DIB_RGB_COLORS,
               SRCCOPY);
            }

         /* else print the whole thing */
         else
            {
            Status = StretchDIBits(
               PrintDC,
               0,
               0,
               (TempWidth * BitMapWidth) / PrinterAreaPixels,
               (TempHeight * BitMapHeight) / PrinterAreaPixels,
               0,
               0,
               BitMapWidth,
               BitMapHeight,
               BitsPtr,
               PrintBitmapInfo,
               DIB_RGB_COLORS,
               SRCCOPY);
            }

         if (Status <= 0)
            {
            MessageBox("Cannot draw image", "Error");
            char buffer[64];
            MessageBox(itoa(GetLastError(), buffer, 10), "Sub Code");
            }
         }
       else
         {
         /* can't do it */
         MessageBox("Cannot extract image", "Error");
         }

      /* restore resources */

      if (EnablePalette)
         {
         SelectPalette(ScreenDC, OldPalette, FALSE);
         }

      GlobalUnlock(BitsHandle);

      GlobalFree(BitsHandle);
      }
   else
      {
      /* can't do it */
      MessageBox("No Memory to Print", "Error");
      }

   ReleaseDC(0, ScreenDC);

   delete PrintBitmapInfo;
   }


void TScreenWindow::EvKeyDown(UINT, UINT, UINT)
   {
   TMessage Msg = __GetTMessage();

   callthing *callevent;

   // if keyboard was on and up and down is enabled then continue
   if (keyboard_on == 2)
      {

      // if key is down skip it

//    if (!(Msg.LParam & 0x40000000L))
         {
         callevent = new callthing;

         callevent->func = keyboard_keydown;
         callevent->arg1 = Msg.WParam;
         callevent->kind = 2;

         calllists.insert(callevent, 2);
         checkqueue();
         }

         // Don't do scrolling
         return;
      }

   // scroll main window with arrow keys
   if (Msg.WParam == VK_PRIOR ||
       Msg.WParam == VK_UP)
      {
      Scroller->ScrollBy(0, -Scroller->YLine);
      }
   else if (Msg.WParam == VK_NEXT ||
            Msg.WParam == VK_DOWN)
      {
      Scroller->ScrollBy(0, Scroller->YLine);
      }
   else if (Msg.WParam == VK_LEFT)
      {
      Scroller->ScrollBy(-Scroller->XLine, 0);
      }
   else if (Msg.WParam == VK_RIGHT)
      {
      Scroller->ScrollBy(Scroller->XLine, 0);
      }
   else if (keyboard_on == 0 &&
            MainWindowx->CommandWindow->EditBoxWantsKeyEvent(Msg.WParam))
      {
      // we don't handle this key.
      // give focus to the edit box and send the press to it.
      MainWindowx->CommandWindow->PostKeyDownToEditBox(
         Msg.WParam,
         Msg.LParam);
      }
   else
      {
      // else do your normal stuff
      DefaultProcessing();
      }
   }

void TScreenWindow::EvKeyUp(UINT, UINT, UINT)
   {
   TMessage Msg = __GetTMessage();

   callthing *callevent;

   if (keyboard_on == 2)
      {
      // if keyboard was on and up and down is enabled then continue
      callevent = new callthing;

      callevent->func = keyboard_keyup;
      callevent->arg1 = Msg.WParam;
      callevent->kind = 2;

      calllists.insert(callevent, 2);
      checkqueue();
      }
   else
      {
      // else do your normal stuff
      DefaultProcessing();
      }
   }

void TScreenWindow::EvChar(UINT, UINT, UINT)
   {
   TMessage Msg = __GetTMessage();

   callthing *callevent;

   if (keyboard_on == 1)
      {
      // if keyboard was on and NOT up and down is enabled then continue
      callevent = new callthing;

      callevent->func = keyboard_keyup;
      callevent->arg1 = Msg.WParam;
      callevent->kind = 2;

      calllists.insert(callevent, 2);
      checkqueue();
      }
   else
      {
      // else do your normal stuff
      DefaultProcessing();
      }
   }

void TScreenWindow::EvLButtonDown(UINT, TPoint &point)
   {
   callthing *callevent;

   SetFocus();
   SetCapture();

   if (mouse_on == 1)
      {
      // if user turned on mouse the queue up event
      callevent = new callthing;

      callevent->func = mouse_lbuttondown;
      callevent->arg1 = point.x;
      callevent->arg2 = point.y;
      callevent->kind = 1;

      calllists.insert(callevent, 1);
      checkqueue();
      }
   else
      {
      // else do your normal processing
      DefaultProcessing();
      }
   }

void TScreenWindow::EvLButtonUp(UINT, TPoint &point)
   {
   callthing *callevent;

   ReleaseCapture();

   if (mouse_on == 1)
      {
      // if user turned on mouse the queue up event
      callevent = new callthing;

      callevent->func = mouse_lbuttonup;
      callevent->arg1 = point.x;
      callevent->arg2 = point.y;
      callevent->kind = 1;

      calllists.insert(callevent, 1);
      checkqueue();
      }
   }

void TScreenWindow::EvRButtonDown(UINT, TPoint &point)
   {
   callthing *callevent;

   SetFocus();
   SetCapture();

   if (mouse_on == 1)
      {
      // if user turned on mouse the queue up event

      callevent = new callthing;

      callevent->func = mouse_rbuttondown;
      callevent->arg1 = point.x;
      callevent->arg2 = point.y;
      callevent->kind = 1;

      calllists.insert(callevent, 1);
      checkqueue();
      }
   }

void TScreenWindow::EvRButtonUp(UINT, TPoint &point)
   {
   callthing *callevent;

   ReleaseCapture();

   if (mouse_on == 1)
      {
      // if user turned on mouse the queue up event
      callevent = new callthing;

      callevent->func = mouse_rbuttonup;
      callevent->arg1 = point.x;
      callevent->arg2 = point.y;
      callevent->kind = 1;

      calllists.insert(callevent, 1);
      checkqueue();
      }

   }

void TScreenWindow::EvMouseMove(UINT, TPoint &point)
   {
   callthing *callevent;

   // if user turned on mouse the queue up event

   if (mouse_on == 1)
      {
      callevent = new callthing;

      callevent->func = mouse_mousemove;
      callevent->arg1 = point.x;
      callevent->arg2 = point.y;
      callevent->kind = 1;

      calllists.insert(callevent, 1);
      checkqueue();
      }
   }


void TScreenWindow::EvSize(UINT arg1, TSize &arg2)
   {
   TWindow::EvSize(arg1, arg2);
   
   // Adjust scroller range so that thumb at each extreme corresponds
   // to edge of extreme image.
   TRect clientRect;
   GetClientRect(clientRect);

   int Xr = (BitMapWidth * the_zoom) - clientRect.right;
   int Yr = (BitMapHeight * the_zoom) - clientRect.bottom;

   if (Xr < 0)
      {
      Xr = 0;
      }

   if (Yr < 0)
      {
      Yr = 0;
      }

   NUMBER XRatio;
   NUMBER YRatio;

   if (Scroller->XRange <= 0)
      {
      XRatio = 0.5;
      }
   else
      {
      XRatio = (NUMBER) Scroller->XPos / (NUMBER) Scroller->XRange;
      }

   if (Scroller->YRange <= 0)
      {
      YRatio = 0.5;
      }
   else
      {
      YRatio = (NUMBER) Scroller->YPos / (NUMBER) Scroller->YRange;
      }

   Scroller->SetRange(Xr, Yr);
   Scroller->ScrollTo(XRatio * Xr, YRatio * Yr);
   
   }


DEFINE_RESPONSE_TABLE1(TScreenWindow, TWindow)
  EV_WM_KEYUP,
  EV_WM_KEYDOWN,
  EV_WM_CHAR,
  EV_WM_LBUTTONDOWN,
  EV_WM_LBUTTONUP,
  EV_WM_RBUTTONDOWN,
  EV_WM_RBUTTONUP,
  EV_WM_MOUSEMOVE,
  EV_WM_SIZE,
END_RESPONSE_TABLE;


TMainFrame::TMainFrame(
   TWindow *       AParent,
   LPCSTR          ATitle,
   TPaneSplitter * PaneSplitter
) : TDecoratedFrame(AParent, ATitle, PaneSplitter),
    PaneSplitterWindow(PaneSplitter)
   {
   /* main window initialization */

   AssignMenu("IDM_COMMANDS");

   /* check if a palette exists */
   HDC screen = CreateDC("DISPLAY", NULL, NULL, NULL);
   if (screen != NULL)
      {
      if ((GetDeviceCaps(screen, RASTERCAPS) & RC_PALETTE) == 0)
         {
         EnablePalette = 0;
         }
      else
         {
         EnablePalette = 1;
         }

      DeleteDC(screen);
   }

   /* create printer object */

   Printer = new TPrinter;

   /* flag that screen clean */

   IsNewFile = true;
   IsNewBitmap = true;

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


   // create the drawing surface
   ScreenWindow = new TScreenWindow(0, "FMSLogo Screen");

   // create resourced window
   CommandWindow = new TMyCommandWindow(0, "DIALOGCOMMAND");
//   CommandWindow->Create();

   strcpy(BitmapName, "Logo.Bmp");
   strcpy(FileName, "Logo.Lgo");
   }

TMainFrame::~TMainFrame()
   {
   int i;

   /* clean things up */

   delete Printer;
   DeleteObject(MemoryBitMap);
   delete CommandWindow;


   /* if palette clean it too */
   if (EnablePalette)
      {
      DeleteObject(ThePalette);
      delete MyLogPalette;
      }

   free(gcstack);
   free(hash_table);

   /* Note Bitmap index 0 belongs to Clipboard */

   for (i = 1; i < MaxBitCuts; i++)
      if (CutBmp[i].CutFlag) DeleteObject(CutBmp[i].CutMemoryBitMap);
   free(CutBmp);

   if (hCursorWait) DestroyCursor(hCursorWait);
   if (hCursorArrow) DestroyCursor(hCursorArrow);
   }


void TMainFrame::GetWindowClass(WNDCLASS &WndClass)
   {
   TDecoratedFrame::GetWindowClass(WndClass);
   WndClass.lpszMenuName = "Logo";
   WndClass.hIcon = GetApplication()->LoadIcon("LOGOICON");
   }


char * TMainFrame::GetClassName()
   {
   return "Logo";
   }


bool TMainFrame::CanClose()
   {
   HWND editH = ::FindWindow(NULL, "Editor");

   // if editor is running could loose changes
   if (editH)
      {
      ::ShowWindow(editH, SW_SHOWNORMAL);
      ::SetWindowPos(editH, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
      JustDidEdit = 1;

      if (MessageBox(
            "Changes in this edit session may be lost.\n"
               "\n"
               "Do you really want to exit FMSLogo?",
            "An Edit session is running",
            MB_OKCANCEL | MB_ICONQUESTION) != IDOK)
         {
         return false;
         }
      }

   // if not halted warn user and give chance to abort shutdown

   if (halt_flag != 0)
      {
      // if we already tried warn user of doom
      if (Time_To_Halt)
         {
         if (MessageBox(
               "FMSLogo does not like exiting while not halted.\n"
                  "\n"
                  "Do you really want to exit FMSLogo?",
               "Logo is not Halted",
               MB_OKCANCEL | MB_ICONQUESTION) != IDOK)
            {
            return false;
            }
         }
         // else let the user optionally halt first
      else
         {
         if (MessageBox(
               "FMSLogo does not like exiting while not halted.\n"
                  "\n"
               	  "Do you really want to Halt FMSLogo?",
               "Logo is not Halted",
               MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
            {
            CommandWindow->DoButtonHalt(0);
            }
         return false;
         }
      }

   // if dirty warn user and give chance to abort shutdown
   if (IsDirty)
      {
      if (MessageBox(
            "You will lose any changes if you don't save your workspace to disk.\n"
               "\n"
               "Do you really want to exit FMSLogo?",
            "You have not saved to disk",
            MB_OKCANCEL | MB_ICONQUESTION) != IDOK)
         {
         return false;
         }
      }

      // if we made it here we are OK
      return true;
   }

void TMainFrame::CMExit()
   {

   /* here on FILE-EXIT main window (screen) */

   if (halt_flag != 0)
      {
      Time_To_Halt = 1;
      }
   Time_To_Exit = 1;
   }

BOOL TMainFrame::WriteDIB(int TheFile, int MaxBitCount)
   {
   WORD size;

   LPSTR BitsPtr;
   HBITMAP BitsHandle;
   BITMAPFILEHEADER BitmapFileHeader;
   BITMAPINFO *SaveBitmapInfo;

   /* grab a DC */
   HDC screen = CreateDC("DISPLAY", NULL, NULL, NULL);

   /* hard code to screen mode */

   WORD SavebitCount = GetDeviceCaps(screen, BITSPIXEL);
   SavebitCount *= GetDeviceCaps(screen, PLANES);

   if (MaxBitCount < SavebitCount)
      {
      if ((MaxBitCount == 1) || (MaxBitCount == 4) || (MaxBitCount == 8))
         {
         SavebitCount = MaxBitCount;
         }
      }

   /* compute size of bitmap */

   if (SavebitCount == 16)
      {
      SavebitCount = 24;
      }
   if (SavebitCount == 32)
      {
      SavebitCount = 24;
      }

   if (SavebitCount <= 8)
      {
      size = sizeof(BITMAPINFOHEADER) + ((1 << SavebitCount) * sizeof(RGBQUAD));
      }
   else
      {
      size = sizeof(BITMAPINFOHEADER);
      }

   SaveBitmapInfo = (BITMAPINFO *) new char[size];

   SaveBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   SaveBitmapInfo->bmiHeader.biWidth = BitMapWidth;
   SaveBitmapInfo->bmiHeader.biHeight = BitMapHeight;
   SaveBitmapInfo->bmiHeader.biPlanes = 1;
   SaveBitmapInfo->bmiHeader.biBitCount = SavebitCount;
   SaveBitmapInfo->bmiHeader.biCompression = BI_RGB;
   SaveBitmapInfo->bmiHeader.biSizeImage = ((((SaveBitmapInfo->bmiHeader.biWidth * SaveBitmapInfo->bmiHeader.biBitCount) + 31) / 32) * 4) * SaveBitmapInfo->bmiHeader.biHeight;
   SaveBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
   SaveBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
   SaveBitmapInfo->bmiHeader.biClrUsed = 0;
   SaveBitmapInfo->bmiHeader.biClrImportant = 0;

   if (IsPrinterSettingCustom)
      {
      SaveBitmapInfo->bmiHeader.biWidth = PrinterAreaXHigh - PrinterAreaXLow;
      SaveBitmapInfo->bmiHeader.biHeight = PrinterAreaYHigh - PrinterAreaYLow;
      }

   SaveBitmapInfo->bmiHeader.biSizeImage = ((((SaveBitmapInfo->bmiHeader.biWidth * SaveBitmapInfo->bmiHeader.biBitCount) + 31) / 32) * 4) * SaveBitmapInfo->bmiHeader.biHeight;

   // allocate space for the raw DIB data

   BitsHandle = (HBITMAP) GlobalAlloc(
      GMEM_MOVEABLE | GMEM_ZEROINIT,
      SaveBitmapInfo->bmiHeader.biSizeImage);

   /* bummer */

   if (!BitsHandle)
      {
      DeleteDC(screen);
      return FALSE;
      }

   /* go find it */

   BitsPtr = (LPSTR) GlobalLock((HGLOBAL) BitsHandle);

   /* if palette yank it in */

   if (EnablePalette)
      {
      OldPalette2 = SelectPalette(screen, ThePalette, FALSE);
      RealizePalette(screen);
      }

   /* if custom then use custom dimensions */

   if (IsPrinterSettingCustom)
      {
      HBITMAP AreaMemoryBitMap = CreateCompatibleBitmap(
         screen,
         PrinterAreaXHigh - PrinterAreaXLow,
         PrinterAreaYHigh - PrinterAreaYLow);

      if (!AreaMemoryBitMap)
         {
         MessageBox("Write failed, Possibly no Memory", "Error");
         err_logo(STOP_ERROR, NIL);
         }

      HDC     memoryDC     = CreateCompatibleDC(screen);
      HBITMAP memoryBitmap = (HBITMAP) SelectObject(memoryDC, MemoryBitMap);

      HDC     areaMemoryDC     = CreateCompatibleDC(screen);
      HBITMAP areaMemoryBitmap = (HBITMAP) SelectObject(areaMemoryDC, AreaMemoryBitMap);

      BitBlt(
         areaMemoryDC,
         0,
         0,
         PrinterAreaXHigh - PrinterAreaXLow,
         PrinterAreaYHigh - PrinterAreaYLow,
         memoryDC,
         +PrinterAreaXLow + xoffset,
         -PrinterAreaYHigh + yoffset,
         SRCCOPY);

      SelectObject(areaMemoryDC, areaMemoryBitmap);
      DeleteDC(areaMemoryDC);

      SelectObject(memoryDC, memoryBitmap);
      DeleteDC(memoryDC);

      // convert logo bitmap to raw DIB in BitsPtr
      GetDIBits(
         screen,
         AreaMemoryBitMap,
         0,
         PrinterAreaYHigh - PrinterAreaYLow,
         BitsPtr,
         SaveBitmapInfo,
         DIB_RGB_COLORS);

      DeleteObject(AreaMemoryBitMap);
      }

   /* else do whole thing */

   else
      {
      // convert logo bitmap to raw DIB in BitsPtr
      GetDIBits(
         screen,
         MemoryBitMap,
         0,
         BitMapHeight,
         BitsPtr,
         SaveBitmapInfo,
         DIB_RGB_COLORS);
      }

   /* restore some of the resourese */
   if (EnablePalette)
      {
      SelectPalette(screen, OldPalette2, FALSE);
      }

   DeleteDC(screen);

   // build header */
   BitmapFileHeader.bfType = 19778;
   BitmapFileHeader.bfSize = size + sizeof(BITMAPFILEHEADER) + (int) (SaveBitmapInfo->bmiHeader.biWidth * SaveBitmapInfo->bmiHeader.biHeight * (SavebitCount / 8));
   BitmapFileHeader.bfReserved1 = 0;
   BitmapFileHeader.bfReserved2 = 0;
   BitmapFileHeader.bfOffBits = size + sizeof(BITMAPFILEHEADER);

   // write header
   _lwrite(TheFile, (LPSTR) &BitmapFileHeader, sizeof(BitmapFileHeader));

   _lwrite(TheFile, (LPSTR) SaveBitmapInfo, size);

   // write out raw DIB data to file

   GlobalUnlock(BitsHandle);

   PutBitmapData(TheFile, BitsHandle, SaveBitmapInfo->bmiHeader.biSizeImage);

   GlobalFree(BitsHandle);

   delete SaveBitmapInfo;

   return TRUE;
   }

BOOL TMainFrame::DumpBitmapFile(LPSTR Name, int MaxBitCount)
   {
   /* open and check if ok */

   int file = _lcreat(Name, 0);
   if (file != -1)
      {
      // Load hour-glass cursor.
      hCursor =::SetCursor(hCursorWait);

      /* do it and if error then let user know */

      if (!WriteDIB(file, MaxBitCount))
         {
         MessageBox("Could not Write .BMP", "Error");
         err_logo(STOP_ERROR, NIL);
         }

      // Reload arrow cursor.
      ::SetCursor(hCursor);

      _lclose(file);
      }
   else
      {
      /* else file never opened */
      MessageBox("Could not Open .BMP", "Error");
      err_logo(STOP_ERROR, NIL);
      }

   return TRUE;
   }

/* Attempt to open a Windows 3.0 device independent bitmap. */

BOOL TMainFrame::OpenDIB(int TheFile, DWORD &dwPixelWidth, DWORD &dwPixelHeight)
   {
   WORD ReadbitCount;

   long longWidth;
   LPSTR BitsPtr;
   BITMAPINFO *ReadBitmapInfo;

   HBITMAP BitsHandle;
   HBITMAP NewBitmapHandle;


   BITMAPFILEHEADER BitmapFileHeader;

   /* get header */

   _llseek(TheFile, 0, 0);
   _lread(TheFile, (LPSTR) & BitmapFileHeader, sizeof(BitmapFileHeader));

   /* bfOffbits should be equal to BitmapInfoHeader */

   ReadBitmapInfo = (BITMAPINFO *) new char[BitmapFileHeader.bfOffBits - sizeof(BitmapFileHeader)];

   _lread(TheFile, (LPSTR) ReadBitmapInfo, BitmapFileHeader.bfOffBits - sizeof(BitmapFileHeader));

   if (dwPixelWidth)
      {

      /* do what the spec says */

      if (ReadBitmapInfo->bmiHeader.biClrUsed == 0)
         {
         ReadBitmapInfo->bmiHeader.biClrUsed = 1 << ReadBitmapInfo->bmiHeader.biBitCount;
         }

      /* only allow bitcount equal to display capability */

      ReadbitCount = ReadBitmapInfo->bmiHeader.biBitCount;

      /* if palette load up palette from bitmap color table */

      if (EnablePalette)
         {
         if (ReadbitCount == 8)
            {
            for (int i = 0; i < ReadBitmapInfo->bmiHeader.biClrUsed; i++)
               {
               LoadColor(
                  ReadBitmapInfo->bmiColors[i].rgbRed,
                  ReadBitmapInfo->bmiColors[i].rgbGreen,
                  ReadBitmapInfo->bmiColors[i].rgbBlue);
               }
            }
         else
            {
            /* fill palette with a wide range */
            for (int i = 0; i < 5; i++)
               for (int j = 0; j < 5; j++)
                  for (int k = 0; k < 5; k++)
                     LoadColor(i * 42, j * 42, k * 42);
            }
         }
      
      /* save some typing */
      DWORD NewPixelWidth = ReadBitmapInfo->bmiHeader.biWidth;
      DWORD NewPixelHeight = ReadBitmapInfo->bmiHeader.biHeight;

      /* compute image size if not set */

      if (ReadBitmapInfo->bmiHeader.biSizeImage == 0)
         {
         longWidth = (((NewPixelWidth * ReadbitCount) + 31) / 32) * 4;

         ReadBitmapInfo->bmiHeader.biSizeImage = longWidth * NewPixelHeight;
         }
      
      /* pack and allocate */
      
      BitsHandle = (HBITMAP) GlobalAlloc(
         GMEM_MOVEABLE | GMEM_ZEROINIT,
         ReadBitmapInfo->bmiHeader.biSizeImage);
      
      /* sorry */
      
      if (!BitsHandle)
         {
         delete [] ReadBitmapInfo;
         return FALSE;
         }

      /* read the file into the bitmap */

      GetBitmapData(TheFile, BitsHandle, ReadBitmapInfo->bmiHeader.biSizeImage);

      /* Create DC comaptible with screen */

      HDC screen = GetDC(MainWindowx->ScreenWindow->HWindow);

      HDC memoryDC = CreateCompatibleDC(screen);
      HDC DCHandle = CreateCompatibleDC(screen);

      HPALETTE oldPalette  = NULL;
      HPALETTE oldPalette2 = NULL;

      /* if palette yank it */

      if (EnablePalette)
         {
         oldPalette = SelectPalette(memoryDC, ThePalette, FALSE);
         RealizePalette(memoryDC);

         oldPalette2 = SelectPalette(screen, ThePalette, FALSE);
         RealizePalette(screen);
         }

      /* find it */

      BitsPtr = (LPSTR) GlobalLock((HGLOBAL) BitsHandle);

      /* now create the bitmap with the bits just loaded */

      NewBitmapHandle = CreateDIBitmap(
         screen,
         &ReadBitmapInfo->bmiHeader,
         CBM_INIT,
         BitsPtr,
         ReadBitmapInfo,
         0);

      /* now dump the bits */

      GlobalUnlock(BitsHandle);
      GlobalFree(BitsHandle);

      delete [] ReadBitmapInfo;

      if (EnablePalette)
         {
         SelectPalette(screen, oldPalette2, FALSE);
         }

      ReleaseDC(MainWindowx->ScreenWindow->HWindow, screen);

      /* now that things are clean we can check if we are ok */

      if (!NewBitmapHandle)
         {
         return FALSE;
         }

      /*
      We've now made a bonafied bitmap. But we want to copy it into the
      existing backing store.
      */

      if (EnablePalette)
         {
         oldPalette2 = SelectPalette(DCHandle, ThePalette, FALSE);
         RealizePalette(DCHandle);
         }

      HBITMAP oldBitmap  = (HBITMAP) SelectObject(memoryDC, MemoryBitMap);
      HBITMAP oldBitmap2 = (HBITMAP) SelectObject(DCHandle, NewBitmapHandle);

      /* if either dimension is more than half then put in corner */
      if ((NewPixelWidth > (BitMapWidth / 2)) || (NewPixelHeight > (BitMapHeight / 2)))
         {
         BitBlt(
            memoryDC,
            0,
            0,
            NewPixelWidth,
            NewPixelHeight,
            DCHandle,
            0,
            0,
            SRCCOPY);
         }
      else
         {
         /* else put at turtle */
         POINT dest;

         if (current_mode == perspectivemode)
            {
            VECTOR from3d;

            from3d.x = turtle_p[turtle_which].x / WorldWidth;
            from3d.y = turtle_p[turtle_which].y / WorldHeight;
            from3d.z = turtle_p[turtle_which].z / WorldDepth;

            if (!ThreeD.TransformPoint(from3d, dest))
               {
               return TRUE;
               }
            }
         else
            {
            dest.x = g_round(turtle_p[turtle_which].x);
            dest.y = g_round(turtle_p[turtle_which].y);
            }

         BitBlt(
            memoryDC,
            +dest.x + xoffset,
            -dest.y + yoffset + LL - NewPixelHeight,
            NewPixelWidth,
            NewPixelHeight, DCHandle, 0, 0, SRCCOPY);
         }

      /* return resources */

      if (EnablePalette)
         {
         SelectPalette(memoryDC, oldPalette, FALSE);
         SelectPalette(DCHandle, oldPalette2, FALSE);
         }

      SelectObject(memoryDC, oldBitmap);
      DeleteDC(memoryDC);

      SelectObject(DCHandle, oldBitmap2);
      DeleteDC(DCHandle);

      DeleteObject(NewBitmapHandle);
      
      dwPixelWidth  = NewPixelWidth;
      dwPixelHeight = NewPixelHeight;
      }

   return TRUE;
   }

BOOL TMainFrame::LoadBitmapFile(LPSTR Name, DWORD &dwPixelWidth, DWORD &dwPixelHeight)
   {

   // Test if the passed file is a Windows 3.0 DIB bitmap and if so read it
   long TestWin30Bitmap;
   const char * errorMessage = NULL;
   BOOL retval;

   /* open then check if open */

   int file = _lopen(Name, OF_READ);
   if (file != -1)
      {

      /* check if valid bitmap */

      _llseek(file, 14, 0);
      _lread(file, (LPSTR) & TestWin30Bitmap, sizeof(TestWin30Bitmap));
      if (TestWin30Bitmap == 40)
         {
         // Load hour-glass cursor.
         hCursor =::SetCursor(hCursorWait);

         /* if loaded ok then invalidate to display */

         if (OpenDIB(file, dwPixelWidth, dwPixelHeight))
            {
            ScreenWindow->Invalidate(true);
            }
         else
            {
            errorMessage = "Unable to create Windows 3.0 bitmap";
            }

         // Reload arrow cursor.
         ::SetCursor(hCursor);
         }
      else
         {
         /* not a bitmap */
         errorMessage = "Not a Windows 3.0 bitmap";
         }
      _lclose(file);
      }
   else
      {
      /* else file not there */
      errorMessage = "Cannot open bitmap file";
      }

   /* if no message the we are ok else display error message */

   if (errorMessage == NULL)
      {
      retval = TRUE;
      }
   else
      {
      MessageBox(errorMessage, "Error", MB_OK);
      err_logo(STOP_ERROR, NIL);
      retval = FALSE;
      }

   return retval;
   }

/* Copies the bitmap bit data from the file into memory. Since
copying cannot cross a segment (64K) boundary, we are forced
to do segment arithmetic to compute the next segment.  Created
a LongType type to simplify the process. */

void TMainFrame::GetBitmapData(int TheFile, HANDLE BitsHandle, long BitsByteSize)
   {
   long Count;
   long Start;
   long ToAddr;
   long Bits;

   Bits = (long) GlobalLock(BitsHandle);

   Start = 0L;

   Count = BitsByteSize;

   while (Count > 0)
      {
      ToAddr = Bits + Start;

      if (Count > 0x4000)
         {
         Count = 0x4000;
         }
      _lread(TheFile, (LPSTR) ToAddr, (WORD) Count);
      Start = Start + Count;
      Count = BitsByteSize - Start;
      }

   GlobalUnlock(BitsHandle);
   }

/* Copys the bitmap bit data from the memory into file. Since
copying cannot cross a segment (64K) boundary, we are forced
to do segment arithmetic to compute the next segment.  Created
a LongType type to simplify the process. */

void TMainFrame::PutBitmapData(int TheFile, HANDLE BitsHandle, long BitsByteSize)
   {
   long Count;
   long Start;
   long ToAddr;
   long Bits;

   Bits = (long) GlobalLock(BitsHandle);

   Start = 0L;

   Count = BitsByteSize;

   while (Count > 0)
      {
      ToAddr = Bits + Start;

      if (Count > 0x4000)
         {
         Count = 0x4000;
         }

      _lwrite(TheFile, (LPSTR) ToAddr, (WORD) Count);
      Start = Start + Count;
      Count = BitsByteSize - Start;
      }

   GlobalUnlock(BitsHandle);
   }


void TMainFrame::EvSize(UINT arg1, TSize &arg2)
   {
   TDecoratedFrame::EvSize(arg1, arg2);   
   DefaultProcessing();
   }

void TMainFrame::CMBitmapNew()
   {

   // reset the on-screen bitmap
   HBRUSH brush = ::CreateBrushIndirect(&ScreenBrush);
   if (brush != NULL)
      {
      HDC deviceContext = ::GetDC(MainWindowx->ScreenWindow->HWindow);

      HDC memoryDC = ::CreateCompatibleDC(deviceContext);
      if (memoryDC != NULL)
         {
         ::SelectObject(memoryDC, MemoryBitMap);

         ::FillRect(memoryDC, &FullRect, brush);

         ::SetBkColor(memoryDC, scolor);
         ::SetBkMode(memoryDC, TRANSPARENT);

         ::DeleteDC(memoryDC);
         }

      ::ReleaseDC(MainWindowx->ScreenWindow->HWindow, deviceContext);
      ::DeleteObject(brush);
   }

   // mark the screen window as invalid
   MainWindowx->ScreenWindow->Invalidate(true);
   IsNewBitmap = true;
   }

void TMainFrame::CMBitmapOpen()
   {
   DWORD dwPixelWidth = 1;
   DWORD dwPixelHeight = 1;

   TOpenSaveDialog::TData FileData;
   FileData.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER;
   FileData.SetFilter("Bitmap Files (*.BMP)|*.BMP|GIF Files (*.GIF)|*.GIF|All Files (*.*)|*.*|");
   strcpy(FileData.FileName, "*.BMP");
   FileData.DefExt = "bmp";

   /* if user found a file then try to load it  */

   if (TFileOpenDialog(this, FileData).Execute() == IDOK)
      {
      char ext[_MAX_EXT];
      
      IsNewBitmap = FALSE;
      strcpy(BitmapName, FileData.FileName);
      
      _splitpath(BitmapName, NULL, NULL, NULL, ext);
      if (stricmp(ext, ".GIF") == 0)
         gifload_helper(BitmapName, dwPixelWidth, dwPixelHeight);
      else
         LoadBitmapFile(BitmapName, dwPixelWidth, dwPixelHeight);
      }
   }

void TMainFrame::CMBitmapSave()
   {
   // if new file then switch to save file as, else save
   if (IsNewBitmap)
      {
      SaveBitmapAs();
      }
   else
      {
      SaveBitmap();
      }
   }

void TMainFrame::SaveBitmapAs()
   {
   TOpenSaveDialog::TData FileData;

   /* if new then nulify File name */

   if (IsNewBitmap)
      {
      BitmapName[0] = '\0';
      }

   /* Get file name from user and then save the file */

   FileData.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_EXPLORER;
   FileData.SetFilter("Bitmap Files (*.BMP)|*.BMP|GIF Files (*.GIF)|*.GIF|All Files (*.*)|*.*|");
   strcpy(FileData.FileName, BitmapName);
   FileData.DefExt = "bmp";

   if (TFileSaveDialog(this, FileData).Execute() == IDOK)
      {
      IsNewBitmap = false;
      strcpy(BitmapName, FileData.FileName);
      SaveBitmap();
      }
   }

void TMainFrame::CMBitmapSaveAs()
   {
   SaveBitmapAs();
   }

void TMainFrame::SaveBitmap()
   {
   char ext[_MAX_EXT];
   _splitpath( BitmapName, NULL, NULL, NULL, ext );
   if (stricmp(ext, ".GIF") == 0)
      gifsave_helper(BitmapName, -1, 0, -1, -1, 8);
   else
      DumpBitmapFile(BitmapName, 32);
   }

void TMainFrame::CMFileNew()
   {
   NODE *arg;

   // if doing new and dirty give user a chance to abort the new

   if (IsDirty)
      {
      if (MainWindowx->CommandWindow->MessageBox(
             "Executing a new will erase all definitions.\n"
                "\n"
                "Continue with New?",
             "You have not saved to disk",
             MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL)
         {
         return;
         }
      }

   // else start with a clean plate

   IsNewFile = TRUE;
   IsDirty = FALSE;

   arg = lcontents();

   lerase(arg);
   }


void
TMainFrame::CheckForFileError()
   {

   if (stopping_flag == THROWING)
      {
      if (compare_node(throw_node, Error, TRUE) == 0)
         {
         err_print();
         }
      else if (compare_node(throw_node, System, TRUE) == 0)
         {
         return;
         }
      else if (compare_node(throw_node, Toplevel, TRUE) != 0)
         {
         err_logo(NO_CATCH_TAG, throw_node);
         err_print();
         }
      stopping_flag = RUN;
      }

   if (stopping_flag == STOP || stopping_flag == OUTPUT)
      {
      print_node(
         stdout,
         make_static_strnode(
            "You must be in a procedure to use OUTPUT or STOP.\n"));
      stopping_flag = RUN;
      }
   }


void TMainFrame::CMFileOpen()
   {
   if (IsDirty)
      {
      if (MainWindowx->CommandWindow->MessageBox(
            "The file being loaded may over write your changes.\n"
                "\n"
                "Continue with Load?",
            "You have not saved to disk",
            MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL)
         {
         return;
         }
      }

   /* if user found a file the try to load it  */

   TOpenSaveDialog::TData FileData;
   FileData.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER;
   FileData.SetFilter("Logo Files (*.LGO)|*.LGO|All Files (*.*)|*.*|");
   strcpy(FileData.FileName, "*.LGO");
   FileData.DefExt = "lgo";

   /* if user found a file then try to load it  */

   if (TFileOpenDialog(this, FileData).Execute() == IDOK)
      {
      IsNewFile = false;
      halt_flag++;
      if (halt_flag < 1) halt_flag = 1;
      strcpy(FileName, FileData.FileName);
      fileload(FileName);

      // handle any error that may have occured
      CheckForFileError();

      halt_flag--;
      if (halt_flag < 0)
         {
         halt_flag = 0;
         }
      }
   }

void TMainFrame::CMFileSave()
   {
   // if new file the switch to save file as, else save
   if (IsNewFile)
      {
      SaveFileAs();
      }
   else
      {
      SaveFile();
      }
   }

void TMainFrame::SaveFileAs()
   {
   /* if new the nulify File name */

   if (IsNewFile)
      {
      FileName[0] = '\0';
      }

   /* Get file name from user and then save the file */
   TOpenSaveDialog::TData FileData;
   FileData.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_EXPLORER;
   FileData.SetFilter("Logo Files (*.LGO)|*.LGO|All Files (*.*)|*.*|");
   strcpy(FileData.FileName, FileName);
   FileData.DefExt = "lgo";

   if (TFileSaveDialog(this, FileData).Execute() == IDOK)
      {
      IsNewFile = false;
      strcpy(FileName, FileData.FileName);
      SaveFile();
      }
   }

void TMainFrame::CMFileSaveAs()
   {
   SaveFileAs();
   }

void TMainFrame::SaveFile()
   {
   filesave(FileName);

   // handle any error that may have occured
   CheckForFileError();
   }

void TMainFrame::CMBitmapPrinterArea()
   {
   bool bAok;

   /* copy real to dynamic */

   TPrinterAreaXLow        = PrinterAreaXLow;
   TPrinterAreaXHigh       = PrinterAreaXHigh;
   TPrinterAreaYLow        = PrinterAreaYLow;
   TPrinterAreaYHigh       = PrinterAreaYHigh;
   TPrinterAreaPixels      = PrinterAreaPixels;
   IsTPrinterSettingCustom = IsPrinterSettingCustom;

   do
      {
      bAok = true;

      /* if user does not cancel then copy dynamic to real */

      if (TMyPrinterAreaWindow(this, "PrinterArea").Execute() == IDOK)
         {
         char szWinLocStr[WININISIZ];

         if ((TPrinterAreaXLow >= TPrinterAreaXHigh) || (TPrinterAreaYLow >= TPrinterAreaYHigh))
            {
            MainWindowx->CommandWindow->MessageBox("Bad arguments", "Active Area");
            bAok = false;
            }
         else
            {
            PrinterAreaXLow   = TPrinterAreaXLow;
            PrinterAreaXHigh  = TPrinterAreaXHigh;
            PrinterAreaYLow   = TPrinterAreaYLow;
            PrinterAreaYHigh  = TPrinterAreaYHigh;
            if (TPrinterAreaPixels < 1)
               {
               TPrinterAreaPixels = 1;
               }
            PrinterAreaPixels      = TPrinterAreaPixels;
            IsPrinterSettingCustom = IsTPrinterSettingCustom;

            sprintf(szWinLocStr, "%d", PrinterAreaXLow);
            WritePrivateProfileString("Printer", "XLow", szWinLocStr, "LOGO.INI");
            sprintf(szWinLocStr, "%d", PrinterAreaXHigh);
            WritePrivateProfileString("Printer", "XHigh", szWinLocStr, "LOGO.INI");
            sprintf(szWinLocStr, "%d", PrinterAreaYLow);
            WritePrivateProfileString("Printer", "YLow", szWinLocStr, "LOGO.INI");
            sprintf(szWinLocStr, "%d", PrinterAreaYHigh);
            WritePrivateProfileString("Printer", "YHigh", szWinLocStr, "LOGO.INI");
            sprintf(szWinLocStr, "%d", PrinterAreaPixels);
            WritePrivateProfileString("Printer", "Pixels", szWinLocStr, "LOGO.INI");
            }
         }
      } while (!bAok);
   }

void TMainFrame::CMFileEdit()
   {
   NODE *arg;

   // create dialog for which procedure to edit

   TMyFileEditWindow FileEditWindow(this, "DIALOGEDIT");

   FileEditWindow.FileEditAll = 0;

   // now do it

   if (FileEditWindow.Execute() == IDOK)
      {

      // if user clicked ALL get all procedures

      if (FileEditWindow.FileEditAll == 1)
         {
         arg = lprocedures();
         }

      // else find what user selected

      else
         {
         arg = cons(make_strnode(SelectedText, NULL, strlen(SelectedText), STRING, strnzcpy), NIL);
         }

      // if something edit it

      if (arg != NIL) ledit(arg);

      }
   }

void TMainFrame::CMFileErase()
   {
   NODE *arg;

   // create dialog for which procedure to erase

   TMyFileEditWindow FileEditWindow(this, "DIALOGERASE");

   FileEditWindow.FileEditAll = 0;

   // now do it

   if (FileEditWindow.Execute() == IDOK)
      {
      if (FileEditWindow.FileEditAll == 1)
         {
         // if user clicked EDALL get all procedures
         arg = lprocedures();

         IsNewFile = TRUE;
         IsDirty = FALSE;
         }
      else
         {
         // else find what user selected
         arg = cons(make_strnode(SelectedText, NULL, strlen(SelectedText), STRING, strnzcpy), NIL);
         }

      // if something erase it

      if (arg != NIL)
         {
         lerase(arg);
         }
      }
   }

void TMainFrame::MyPopupEdit(char *FileName, NODE *args)
   {
   /* if called with NULL filename then prompt user */
   EditWindow = new TMyFileWindow(this, "Editor", FileName, args);

   /* Do win.ini stuff. Build default coords */

   int x = (int) (MaxWidth * 0.25);
   int y = (int) (MaxHeight * 0.25);
   int w = (int) (MaxWidth * 0.75);
   int h = (int) (MaxHeight * ScreenSz * 0.75);

   GetPrivateProfileQuadruple(
      "LOGO",
      "Editor",
      &x,
      &y,
      &w,
      &h);

   checkwindow(&x, &y, &w, &h);

   /* now set them */

   EditWindow->Attr.Style = WS_VISIBLE | WS_POPUPWINDOW | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

   /* flag for how to handle focus */

   if (args != NULL)
      {
      JustDidEdit = 1;
      }

   EditWindow->Editor->Attr.Style |= ES_NOHIDESEL;

   // let user edit
   EditWindow->Create();

   // force a resize to fix RichEdit ScrollBar not appearing automatically
   EditWindow->SetWindowPos(0, x, y, w + 1, h, SWP_NOZORDER);
   EditWindow->SetWindowPos(0, x, y, w, h, SWP_NOZORDER);

   if (args != NULL)
      {

      // retitle without filename
      EditWindow->SetWindowText("Editor");

      // if an error occured "force" a change so that we still in
      // "dirty" state
      if (error_happen)
         {
         error_happen = 0;
         EditWindow->Editor->Insert(" ");
         EditWindow->Editor->DeleteSubText(0, 1);
         int iLine = EditWindow->Editor->GetLineFromPos(LinesLoadedOnEdit);
         EditWindow->Editor->Scroll(0, iLine);
         EditWindow->Editor->SetSelection(LinesLoadedOnEdit, LinesLoadedOnEdit);
         }
      }
   }

int TMainFrame::MyPopupInput(char *str, char *pmt)
   {
   // get user input

   if (TInputDialog(this, pmt, "Input:", str, MAX_BUFFER_SIZE).Execute() == IDOK)
      {
      return 1;
      }
   else
      {
      return 0;
      }
   }

void TMainFrame::SetupWindow()
   {
   TDecoratedFrame::SetupWindow();

   PaneSplitterWindow->SetSplitterCushion(MIN_COMMANDER_HEIGHT);
   PaneSplitterWindow->SetSplitterWidth(DEFAULT_SPLITTER_WIDTH);

   // grow the main window to hold the splitter and the commander
   const TRect originalWindowRect = GetWindowRect();

   // restore the commander window's height
   int commanderWindowX      = 0;
   int commanderWindowY      = 0;
   int commanderWindowWidth  = 0;
   int commanderWindowHeight = DEFAULT_COMMANDER_HEIGHT;
   GetPrivateProfileQuadruple(
      "LOGO",
      "Commander",
      &commanderWindowX,
      &commanderWindowY,
      &commanderWindowWidth,
      &commanderWindowHeight);

   // sanity-check the input
   commanderWindowHeight = max(commanderWindowHeight, MIN_COMMANDER_HEIGHT);

   const int totalHeight =
      originalWindowRect.Height() +
      PaneSplitterWindow->GetSplitterWidth() +
      commanderWindowHeight;

   const TRect newWindowRect(
      originalWindowRect.Left(),
      originalWindowRect.Top(),
      originalWindowRect.Right(),
      originalWindowRect.Top() + totalHeight);

   SetWindowPos(
      NULL,
      newWindowRect,
      SWP_NOZORDER);

   PaneSplitterWindow->SplitPane(
      ScreenWindow,
      0,
      psHorizontal);

   PaneSplitterWindow->SplitPane(
      ScreenWindow,
      CommandWindow,
      psHorizontal);

   const int moveDistance =
      CommandWindow->GetWindowRect().Height() -
      commanderWindowHeight;

   PaneSplitterWindow->MoveSplitter(
      ScreenWindow,
      moveDistance);

   Command_OK = 1;


   // it's show time for our little friend
   draw_turtle(1);
   term_init();
   }


void TMainFrame::MyPopupStatusKill()
   {
   status_flag = 0;

   // Get location and size of our window on the screen so we can
   // come back up in the same spot next time we are invoked.
   TRect wrect;
   StatusWindow->GetWindowRect(wrect);

   // save the current location
   SetPrivateProfileQuadruple(
      "LOGO",
      "Status",
      wrect.Left(),
      wrect.Top(),
      wrect.Width(),
      wrect.Height());

   // now kill the status window
   delete StatusWindow;
   CommandWindow->SetDlgItemText(ID_STATUS, "Status");
   }

// popup status window
void TMainFrame::MyPopupStatus()
   {
   // flag so that updates are sent
   status_flag = 1;
   uCurrentTime = GetCurrentTime();

   // pop it up
   StatusWindow = new TMyStatusWindow(this, "DIALOGSTATUS");
   StatusWindow->Create();

   // update button
   CommandWindow->SetDlgItemText(ID_STATUS, "NoStatus");

   // build default coords
   int x = 0;
   int y = 0;
   int w = 0;
   int h = 0;

   // Get last location and size of command window from WIN.INI file.
   GetPrivateProfileQuadruple(
      "LOGO",
      "Status",
      &x,
      &y,
      &w,
      &h);

   checkwindow(&x, &y, &w, &h);

   // now set position
   StatusWindow->SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE);

   // update all fields
   update_status_turtleposition();
   update_status_pencolor();
   update_status_floodcolor();
   update_status_screencolor();
   update_status_paletteuse();
   update_status_penwidth();
   update_status_turtleheading();
   update_status_turtleroll();
   update_status_turtlepitch();
   update_status_penstyle();
   update_status_pencontact();
   update_status_turtlevisability();
   update_status_turtlepitch();
   update_status_turtleroll();
   update_status_turtlewhich();
   update_status_evals();
   update_status_memory();
   update_status_vectors();

   StatusWindow->ShowWindow(SW_SHOW);
   }


void TMainFrame::CMControlExecute()
   {

   HWND EditH = FindWindow(NULL, "Editor");
   HWND TempH = GetActiveWindow();

   // if Main is active find alternate
   if (TempH == MainWindowx->HWindow)
      {

      // if commander up then focus to input box

      if (!CommandWindow->IsIconic())
         {
         CommandWindow->Editbox->SetFocus();
         }

      // else if an editor is available go there
      else if (EditH != NULL)
         {
         if (!::IsIconic(EditH))
            {
            ::SetFocus(EditH);
            }
         }
      }

   // else if active is commander find alternate
   else if (TempH == CommandWindow->HWindow)
      {

      // if a available editor maybe go there

      if (EditH != NULL)
         {

         // if really available then go there

         if (!::IsIconic(EditH))
            {
            ::SetFocus(EditH);
            }
         else
            {
            // else go to main
            SetFocus();
            }
         }
      else
         {
         // else go to main
         SetFocus();
         }
      }
   else
      {
      // else go to main
      SetFocus();
      }
   }

void TMainFrame::CMZoomIn()
   {
   zoom_helper(the_zoom * 2.0);
   }

void TMainFrame::CMZoomOut()
   {
   zoom_helper(the_zoom * 0.5);
   }

void TMainFrame::CMZoomNormal()
   {
   zoom_helper(1.0);
   }

void TMainFrame::CMSetFont()
   {
   LOGFONT logFont;
   logFont = FontRec;

   // clear the struct
   CHOOSEFONT chooseFont;
   memset(&chooseFont, 0x00, sizeof chooseFont);

   // fill it with the right stuff
   chooseFont.lStructSize = sizeof(chooseFont);
   chooseFont.hwndOwner = MainWindowx->HWindow;
   chooseFont.Flags = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT;
   chooseFont.nFontType = SCREEN_FONTTYPE;
   chooseFont.lpLogFont = &logFont;
   chooseFont.hInstance = 0;

   if (ChooseFont(&chooseFont))
      {
      // commit to the new font
      char logoInstruction[512];

      sprintf(
          logoInstruction,
          "SETLABELFONT [[%s] %d %d %d %d %d %d %d %d %d %d %d %d]",
          logFont.lfFaceName,
          logFont.lfHeight,
          logFont.lfWidth,
          logFont.lfOrientation,
          logFont.lfWeight,
          logFont.lfItalic,
          logFont.lfUnderline,
          logFont.lfStrikeOut,
          logFont.lfCharSet,
          logFont.lfOutPrecision,
          logFont.lfClipPrecision,
          logFont.lfQuality,
          logFont.lfPitchAndFamily);

      putcombobox(logoInstruction);
      do_execution(logoInstruction);
      }
   }

void TMainFrame::CMSetCommanderFont()
   {
   CommandWindow->ChooseNewFont();
   }

void TMainFrame::CMSetPenSize()
   {
   TColor TheSize(pen_width, pen_width, pen_width);

   // if OK then make change

   if (TSizeDialog(this, TheSize, "Pen Size").Execute() == IDOK)
      {
      
      char logoInstruction[256];

      sprintf(
          logoInstruction,
          "SETPENSIZE [%d %d]",
          TheSize.Red(),
          TheSize.Green());

      putcombobox(logoInstruction);
      do_execution(logoInstruction);
      }

   }

void TMainFrame::CMSetPenColor()
   {
   TColor TheColor(pcolor);

   // if OK then make change

   if (TColorDialog(this, TheColor, "Pen Color").Execute() == IDOK)
      {
      char logoInstruction[256];

      sprintf(
          logoInstruction,
          "SETPENCOLOR [%d %d %d]",
          TheColor.Red(),
          TheColor.Green(),
          TheColor.Blue());

      putcombobox(logoInstruction);
      do_execution(logoInstruction);
      }

   }

void TMainFrame::CMSetFloodColor()
   {
   TColor TheColor(fcolor);

   // if OK then make changes

   if (TColorDialog(this, TheColor, "Flood Color").Execute() == IDOK)
      {
      char logoInstruction[256];

      sprintf(
          logoInstruction,
          "SETFLOODCOLOR [%d %d %d]",
          TheColor.Red(),
          TheColor.Green(),
          TheColor.Blue());

      putcombobox(logoInstruction);
      do_execution(logoInstruction);
      }
   }

void TMainFrame::CMSetScreenColor()
   {
   TColor TheColor(scolor);

   // if OK then make changes

   if (TColorDialog(this, TheColor, "Screen Color").Execute() == IDOK)
      {
      char logoInstruction[256];

      sprintf(
          logoInstruction,
          "SETSCREENCOLOR [%d %d %d]",
          TheColor.Red(),
          TheColor.Green(),
          TheColor.Blue());

      putcombobox(logoInstruction);
      do_execution(logoInstruction);
      }

   }

void TMainFrame::CMHelp()
   {
   WinHelp(szHelpFileName, HELP_FINDER, 0L);
   }

void TMainFrame::CMHelpMCI()
   {
   WinHelp(MCIHelpFileName, HELP_INDEX, 0L);
   }

void TMainFrame::CMHelpHelp()
   {
   WinHelp("WINHELP.HLP", HELP_FINDER, 0L);
   }

void TMainFrame::CMHelpDemo()
   {
   do_execution("demo");
   }

void TMainFrame::CMHelpTutorial()
   {
   do_help("Where to Start");
   }

void TMainFrame::CMHelpExamples()
   {
   char szFileName[EXE_NAME_MAX_SIZE + 1];

   MakeHelpPathName(szFileName, "EXAMPLES\\INDEX.HTML");

   HINSTANCE examples = ShellExecute(
      HWindow,        // handle to parent window
      "open",         // operation to perform
      szFileName,     // pointer to filename string
      NULL,           // pointer to string that specifies executable-file parameters
      NULL,           // pointer to string that specifies default directory
      SW_SHOWNORMAL); // whether file is shown when opened
   if (examples != NULL)
      {
      CloseHandle(examples);
      }
   }

void TMainFrame::CMHelpReleaseNotes()
   {
   char szFileName[EXE_NAME_MAX_SIZE + 1];

   strcpy(szFileName, "NOTEPAD ");
   MakeHelpPathName(&szFileName[8], "FMSLOGO.TXT");
   WinExec(szFileName, SW_SHOWNORMAL);
   }

void TMainFrame::CMHelpAbout()
   {
   TDialog(this, "AboutBox").Execute();
   }

void TMainFrame::CMHelpAboutMS()
   {
   TDialog(this, "AboutMSBox").Execute();
   }

// Execute File:Print command

void TMainFrame::CMBitmapPrint()
   {
   if (Printer)
      {
      TRulerOut Printout("Logo Picture");
      Printout.SetBanding(false);
      Printer->Print(this, Printout, true);
      }
   }


// Execute File:Printer-setup command

void TMainFrame::CMBitmapPrinterSetup()
   {
   if (Printer) Printer->Setup(this);
   }

void TMainFrame::EvDestroy()
   {
   // don't save sizes if iconed
   if (!IsIconic())
      {
      // Get location and size of our window on the screen so we can
      // come back up in the same spot next time we are invoked.
      const TRect mainWindowRect = GetWindowRect();

      // save the current location
      SetPrivateProfileQuadruple(
         "LOGO",
         "Screen",
         mainWindowRect.Left(),
         mainWindowRect.Top(),
         mainWindowRect.Width(),
         mainWindowRect.Height());
      }

   TWindow::EvDestroy();
   }

LRESULT TMainFrame::WMCheckQueue(WPARAM, LPARAM)
   {
   TMessage msg = __GetTMessage();

   checkqueue();
   return (LRESULT) msg.Result;
   }

LRESULT TMainFrame::OnNetworkConnectSendAck(WPARAM /* wParam */, LPARAM lParam)
   {
   TMessage msg = __GetTMessage();
   char Buffer[MAX_PACKET_SIZE];
   int status;
   callthing *callevent;

   if (WSAGETASYNCERROR(lParam) != 0)
      {
      MessageBox(
         WSAGetLastErrorString(WSAGETASYNCERROR(lParam)),
         "WSAAsyncGetHostByNameCallBack()");
      //    err_logo(STOP_ERROR,NIL);
      return 0L;
      }

   // queue message if send is enabled

   if (network_send_on == 1)
      {

      // update flags based on event type

      switch (WSAGETSELECTEVENT(lParam))
         {
          case FD_READ:
             memset(Buffer, 0, MAX_PACKET_SIZE);

             // get a copy first for examination
             if ((status = lprecv(sendSock, Buffer, MAX_PACKET_SIZE - 1, MSG_PEEK)) == SOCKET_ERROR)
                {
                // int iErrorCode;

                // if block wait til we get called again

                if ((/* iErrorCode = */ lpWSAGetLastError()) == WSAEWOULDBLOCK) return 0L;

                MessageBox(WSAGetLastErrorString(0), "recv(sendsock)");
                //             err_logo(STOP_ERROR,NIL);
                return 0L;
                }

                 // if something is there (better be) then process it

             if (status != 0)
                {
                char *pBuffer;
                int i;

                // last byte is not end of packet then try to find one
                if (Buffer[status - 1] |= 0)
                   {
                   // find last end of packet

                   for (i = status - 1; i >= 0; i--) if (Buffer[i] == 0) break;

                   // if not found
                   if (i < 0)
                      {
                      // if not full wait for more
                      if (status < MAX_PACKET_SIZE - 1) return 0L;

                      // read the whole thing anyway
                      i = MAX_PACKET_SIZE - 2;
                      }

                    // read for real up to a last packet boundary
                    memset(Buffer, 0, MAX_PACKET_SIZE);
                    status = lprecv(sendSock, Buffer, i + 1, 0);
                    }
                 else
                    {
                    // read the whole thng for real
                    memset(Buffer, 0, MAX_PACKET_SIZE);
                    status = lprecv(sendSock, Buffer, MAX_PACKET_SIZE - 1, 0);
                    }

                  i = 0;
                  // now queue up a separate message for each packet

                  while (1)
                    {
                    pBuffer = (char *) malloc(strlen(&Buffer[i]) + 1);
                    strcpy(pBuffer, &Buffer[i]);

                    callevent = new callthing;

                    callevent->func = network_send_receive;
                    callevent->arg1 = LOWORD(pBuffer);
                    callevent->arg2 = HIWORD(pBuffer);
                    callevent->kind = 6;

                    calllists.insert(callevent, callevent->kind);

                    PostMessage(WM_CHECKQUEUE, 0, 0);
                    //                checkqueue();
                    i += strlen(&Buffer[i]) + 1;
                    if (i >= status) break;
                    }
                 }

              return 0L;

          case FD_WRITE:

              // allow another frame to go out.
              bSendBusy = FALSE;
              break;

          case FD_CONNECT:

              // flag it's ok to start firing
              bSendConnected = TRUE;
              break;

          case FD_CLOSE:

              // done
              bSendConnected = FALSE;
              break;
         }

      // we don't distinguish between all event types

      callevent = new callthing;

      callevent->func = network_send_send;
      callevent->arg1 = 0;
      callevent->arg2 = 0;
      callevent->kind = 4;

      calllists.insert(callevent, 4);

      PostMessage(WM_CHECKQUEUE, 0, 0);
      //    checkqueue();
      }

   return 0L;
   }

LRESULT TMainFrame::OnNetworkConnectSendFinish(WPARAM /* wParam */, LPARAM lParam)
   {
   TMessage msg = __GetTMessage();

   // should these not be automatic?
   SOCKADDR_IN send_dest_sin;

   if (WSAGETASYNCERROR(lParam) != 0)
      {
      MessageBox(
         WSAGetLastErrorString(WSAGETASYNCERROR(lParam)),
         "WSAAsyncGetHostByNameCallBack()");
      //    err_logo(STOP_ERROR,NIL);
      return 0L;
      }

   // always start clean

   memset(&send_dest_sin, 0, sizeof(SOCKADDR_IN));

   // what else is there
   send_dest_sin.sin_family = AF_INET;

   if (phes)
      {
      memcpy((char FAR *) &(send_dest_sin.sin_addr), phes->h_addr, phes->h_length);
      }
   else
      {
      MessageBox(
         "Unexpected Error, Network may be shutdown",
         "Network Error");
      //    err_logo(STOP_ERROR,NIL);
      return 0L;
      }

   // set ports
   send_dest_sin.sin_port = lphtons(sendPort);/* Convert to network ordering  */

   // watch for connect
   if (lpWSAAsyncSelect(
         sendSock,
         MainWindowx->HWindow,
         WM_NETWORK_CONNECTSENDACK,
         FD_CONNECT | FD_WRITE | FD_READ | FD_CLOSE) == SOCKET_ERROR)
      {
      MessageBox(WSAGetLastErrorString(0), "WSAAsyncSelect(sendSock) FD_CONNECT");
      //    err_logo(STOP_ERROR,NIL);
      }

   // lets try now
   if (lpconnect(sendSock, (PSOCKADDR) & send_dest_sin, sizeof(send_dest_sin)) == SOCKET_ERROR)
      {
      // int iErrorCode;

      if ((/* iErrorCode = */ lpWSAGetLastError()) != WSAEWOULDBLOCK)
         {
         MessageBox(WSAGetLastErrorString(0), "connect(sendsock)");
         //       err_logo(STOP_ERROR,NIL);
         return 0L;
         }
      }

#ifdef UDP
   // fake an FD_CONNECT for UDP, these would of been called by winsock if TCP
   OnNetworkConnectSendAck(0, MAKELONG(FD_CONNECT, FD_CONNECT));
#endif

   // fire event that connection is made

   if (network_send_on == 1)
      {
      callthing *callevent = new callthing;

      callevent->func = network_send_send;
      callevent->arg1 = 0;
      callevent->arg2 = 0;
      callevent->kind = 4;

      calllists.insert(callevent, 4);

      PostMessage(WM_CHECKQUEUE, 0, 0);
      //    checkqueue();
      }

   return 0L;
   }

LRESULT TMainFrame::OnNetworkListenReceiveAck(WPARAM /* wParam */, LPARAM lParam)
   {
   SOCKADDR_IN acc_sin;       // Accept socket address - internet style
   int acc_sin_len;           // Accept socket address length
   int status;
   char Buffer[MAX_PACKET_SIZE];
   callthing *callevent;

   TMessage msg = __GetTMessage();

   if (WSAGETASYNCERROR(lParam) != 0)
      {
      MessageBox(
         WSAGetLastErrorString(WSAGETASYNCERROR(lParam)),
         "WSAAsyncGetHostByNameCallBack()");
      //    err_logo(STOP_ERROR,NIL);
      return 0L;
      }

   // if receive is on process it

   if (network_receive_on == 1)
      {

      // based on event do the right thing
      switch (WSAGETSELECTEVENT(lParam))
         {
         case FD_READ:
            memset(Buffer, 0, MAX_PACKET_SIZE);

            // get a copy first for examination
            if ((status = lprecv(receiveSock, Buffer, MAX_PACKET_SIZE - 1, MSG_PEEK)) == SOCKET_ERROR)
               {
               // int iErrorCode;

               // if block wait til we get called again
               if ((/* iErrorCode = */ lpWSAGetLastError()) == WSAEWOULDBLOCK) return 0L;

               MessageBox(
                  WSAGetLastErrorString(0),
                  "recv(receivesock)");
               //             err_logo(STOP_ERROR,NIL);
               return 0L;
               }

            // if something is there (better be) then process it
            if (status != 0)
               {
               char *pBuffer;
               int i;

               // last byte is not end of packet then try to find one
               if (Buffer[status - 1] |= 0)
                  {
                  for (i = status - 1; i >= 0; i--) if (Buffer[i] == 0) break;

                  // if not found

                  if (i < 0)
                     {
                     // if not full wait for more
                     if (status < MAX_PACKET_SIZE - 1) return 0L;

                     // read the whole thing anyway
                     i = MAX_PACKET_SIZE - 2;
                     }

                  // read for real up to a last packet boundary
                  memset(Buffer, 0, MAX_PACKET_SIZE);
                  status = lprecv(receiveSock, Buffer, i + 1, 0);
                  }
               else
                  {
                  // read the whole thng for real
                  memset(Buffer, 0, MAX_PACKET_SIZE);
                  status = lprecv(receiveSock, Buffer, MAX_PACKET_SIZE - 1, 0);
                  }

               i = 0;
               // now queue up a seperate message for each packet

               while (1)
                  {
                  pBuffer = (char *) malloc(strlen(&Buffer[i]) + 1);
                  strcpy(pBuffer, &Buffer[i]);

                  callevent = new callthing;

                  callevent->func = network_receive_receive;
                  callevent->arg1 = LOWORD(pBuffer);
                  callevent->arg2 = HIWORD(pBuffer);
                  callevent->kind = 5;

                  calllists.insert(callevent, callevent->kind);

                  PostMessage(WM_CHECKQUEUE, 0, 0);
                  //                checkqueue();

                  i += strlen(&Buffer[i]) + 1;
                  if (i >= status) break;
                  }
               }

            return 0L;

          case FD_ACCEPT:
              bReceiveConnected = TRUE;

              // disabled for UDP

#ifndef USE_UDP
              acc_sin_len = sizeof(acc_sin);

              if ((receiveSock = lpaccept(receiveSock, (struct sockaddr FAR *) &acc_sin, (int FAR *) &acc_sin_len)) == INVALID_SOCKET)
                 {
                 MessageBox(WSAGetLastErrorString(0), "accept(receivesock)");
                 //          err_logo(STOP_ERROR,NIL);
                 }
#endif
              break;

          case FD_CLOSE:

              // done

              bReceiveConnected = FALSE;
              break;

          case FD_WRITE:

              // allow another frame to go out.

              bReceiveBusy = FALSE;
              break;

          default:
              MessageBox("Unexpected Message", "Status");
              //       err_logo(STOP_ERROR,NIL);
              break;

         }

      // all other events just queue the event

      callevent = new callthing;

      callevent->func = network_receive_send;
      callevent->arg1 = 0;
      callevent->arg2 = 0;
      callevent->kind = 4;

      calllists.insert(callevent, callevent->kind);

      PostMessage(WM_CHECKQUEUE, 0, 0);
      //                checkqueue();

      }

   return 0L;
   }

LRESULT TMainFrame::OnNetworkListenReceiveFinish(WPARAM /* wParam */, LPARAM lParam)
   {
   TMessage msg = __GetTMessage();

   SOCKADDR_IN receive_local_sin;      // Local socket - internet style

   if (WSAGETASYNCERROR(lParam) != 0)
      {
      MessageBox(
         WSAGetLastErrorString(WSAGETASYNCERROR(lParam)),
         "WSAAsyncGetHostByNameCallBack()");
      //    err_logo(STOP_ERROR,NIL);
      return 0L;
      }

   // always start clean

   memset(&receive_local_sin, 0, sizeof(SOCKADDR_IN));

   // what else is there

   receive_local_sin.sin_family = AF_INET;

   memcpy(&(receive_local_sin.sin_addr), pher->h_addr, pher->h_length);

   // set ports

   receive_local_sin.sin_port = lphtons(receivePort);/* Convert to network ordering*/
   //   Associate an address with a socket. (bind)

   if (lpbind(receiveSock, (struct sockaddr FAR *) &receive_local_sin, sizeof(receive_local_sin)) == SOCKET_ERROR)
      {
      MessageBox(WSAGetLastErrorString(0), "bind(receivesock)");
      //    err_logo(STOP_ERROR,NIL);
      return 0L;
      }

   // listen for connect

#ifndef USE_UDP
   if (lplisten(receiveSock, MAX_PENDING_CONNECTS) == SOCKET_ERROR)
      {
      MessageBox(WSAGetLastErrorString(0), "listen(receivesock)");
      //    err_logo(STOP_ERROR,NIL);
      return 0L;
      }
#endif

   // watch for when connect happens

   if (lpWSAAsyncSelect(
         receiveSock,
         MainWindowx->HWindow,
         WM_NETWORK_LISTENRECEIVEACK,
         FD_ACCEPT | FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR)
      {
      MessageBox(WSAGetLastErrorString(0), "WSAAsyncSelect(receivesock) FD_ACCEPT");
      //    err_logo(STOP_ERROR,NIL);
      }

   // fake an FD_ACCEPT for UDP, this automatically happens on TCP

#ifdef USE_UDP
   OnNetworkListenReceiveAck(0, MAKELONG(FD_ACCEPT, FD_ACCEPT));
#endif

   // queue this event

   if (network_receive_on == 1)
      {
      callthing *callevent = new callthing;

      callevent->func = network_receive_send;
      callevent->arg1 = 0;
      callevent->arg2 = 0;
      callevent->kind = 4;

      calllists.insert(callevent, 4);

      PostMessage(WM_CHECKQUEUE, 0, 0);
      //    checkqueue();
      }

   return 0L;
   }

LRESULT TMainFrame::MMMCINotify(WPARAM, LPARAM)
   {
   TMessage msg = __GetTMessage();

   // if user fired up a callback mci event the queue it up here

   callthing *callevent;

   callevent = new callthing;

   callevent->func = mci_callback;
   callevent->kind = 4;

   calllists.insert(callevent, 4);

   PostMessage(WM_CHECKQUEUE, 0, 0);

   return (LRESULT) msg.Result;
   }

void TMainFrame::EvTimer(UINT)
   {
   TMessage msg = __GetTMessage();

   // if user fired up a callback mci event the queue it up here

   callthing *callevent;

   callevent = new callthing;

   // the ID can only be 1-31 and select appropriate callback code

   callevent->func = timer_callback[msg.WParam];
   if (msg.WParam > 16)
      {
      callevent->kind = 3;
      calllists.insert(callevent, 3);
      }
   else
      {
      callevent->kind = 4;
      calllists.insert(callevent, 4);
      }

   PostMessage(WM_CHECKQUEUE, 0, 0);
   }


void checkwindow(int *x, int *y, int *w, int *h)
   {
   RECT MaxRect;
   SystemParametersInfo(SPI_GETWORKAREA, 0, &MaxRect, 0);
   int MinX = MaxRect.left;
   int MinY = MaxRect.top;

   // sanity check window coordinates

   if (*x < MinX) *x = MinX;
   if (*y < MinY) *y = MinY;
   if (*w > MaxWidth) *w = MaxWidth;
   if (*h > MaxHeight) *h = MaxHeight;
   if ((*x + *w) > (MaxWidth + MinX)) *x = *x - (*x + *w - (MaxWidth + MinX));
   if ((*y + *h) > (MaxHeight + MinY)) *y = *y - (*y + *h - (MaxHeight + MinY));
   }

DEFINE_RESPONSE_TABLE1(TMainFrame, TDecoratedFrame)
  EV_WM_DESTROY,
  EV_WM_TIMER,
  EV_WM_SIZE,
  EV_COMMAND(CM_FILENEW, CMFileNew),
  EV_COMMAND(CM_FILEOPEN, CMFileOpen),
  EV_COMMAND(CM_FILESAVE, CMFileSave),
  EV_COMMAND(CM_FILESAVEAS, CMFileSaveAs),
  EV_COMMAND(CM_FILEEDIT, CMFileEdit),
  EV_COMMAND(CM_FILEERASE, CMFileErase),
  EV_COMMAND(CM_EXIT, CMExit),
  EV_COMMAND(CM_BITMAPNEW, CMBitmapNew),
  EV_COMMAND(CM_BITMAPOPEN, CMBitmapOpen),
  EV_COMMAND(CM_BITMAPSAVE, CMBitmapSave),
  EV_COMMAND(CM_BITMAPSAVEAS, CMBitmapSaveAs),
  EV_COMMAND(CM_BITMAPPRINT, CMBitmapPrint),
  EV_COMMAND(CM_BITMAPPRINTERSETUP, CMBitmapPrinterSetup),
  EV_COMMAND(CM_BITMAPPRINTERAREA, CMBitmapPrinterArea),
  EV_COMMAND(CM_HELP, CMHelp),
  EV_COMMAND(CM_HELPTUTORIAL, CMHelpTutorial),
  EV_COMMAND(CM_HELPDEMO, CMHelpDemo),
  EV_COMMAND(CM_HELPEXAMPLES, CMHelpExamples),
  EV_COMMAND(CM_HELPRELEASENOTES, CMHelpReleaseNotes),
  EV_COMMAND(CM_HELPMCI, CMHelpMCI),
  EV_COMMAND(CM_HELPHELP, CMHelpHelp),
  EV_COMMAND(CM_HELPABOUT, CMHelpAbout),
  EV_COMMAND(CM_HELPABOUTMS, CMHelpAboutMS),
  EV_COMMAND(CM_CONTROLEXECUTE, CMControlExecute),
  EV_COMMAND(CM_SETFONT, CMSetFont),
  EV_COMMAND(CM_SETCOMMANDERFONT, CMSetCommanderFont),
  EV_COMMAND(CM_SETPENCOLOR, CMSetPenColor),
  EV_COMMAND(CM_SETPENSIZE, CMSetPenSize),
  EV_COMMAND(CM_SETFLOODCOLOR, CMSetFloodColor),
  EV_COMMAND(CM_SETSCREENCOLOR, CMSetScreenColor),
  EV_COMMAND(CM_ZOOMIN, CMZoomIn),
  EV_COMMAND(CM_ZOOMOUT, CMZoomOut),
  EV_COMMAND(CM_ZOOMNORMAL, CMZoomNormal),
  EV_MESSAGE(WM_CHECKQUEUE, WMCheckQueue),
  EV_MESSAGE(MM_MCINOTIFY, MMMCINotify),
  EV_MESSAGE(WM_NETWORK_CONNECTSENDACK, OnNetworkConnectSendAck),
  EV_MESSAGE(WM_NETWORK_CONNECTSENDFINISH, OnNetworkConnectSendFinish),
  EV_MESSAGE(WM_NETWORK_LISTENRECEIVEACK, OnNetworkListenReceiveAck),
  EV_MESSAGE(WM_NETWORK_LISTENRECEIVEFINISH, OnNetworkListenReceiveFinish),
END_RESPONSE_TABLE;

