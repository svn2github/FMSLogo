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

const int MAX_PENDING_CONNECTS = 4;  // The backlog allowed for listen()

calllist calllists;

void qlist::insert(void * a)
   {
   // class "event list queue" member to insert event
   if (last)
      {
      qlink * ph = last->next;
      qlink * h = new qlink(a, NULL, NULL);
      last->next = h;
      h->prev = last;
      h->next = ph;
      ph->prev = h;
      last = last->next;
      }
   else
      {
      last = new qlink(a, NULL, NULL);
      last->next = last;
      last->prev = last;
      }
   }

void * qlist::get(void)
   {
   // class "event list queue" member to get the next event
   if (last == NULL)
      {
      return NULL;
      }

   return last->next->e;
   }

void qlist::zap(void)
   {
   // class "event list queue" member function to remove the first event
   if (last == NULL) 
      {
      return;
      }

   qlink * p = last->next;

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

   if (l == NULL) 
      {
      return;
      }

   do
      {
      qlink *ll = l;
      l = l->next;
      delete ll;
      }
   while (l != last);
   }


callthing * callthing::CreateKeyboardEvent(char * function, int key)
   {
   callthing * callevent = new callthing;
   callevent->kind = EVENTTYPE_Keyboard;
   callevent->func = function;
   callevent->arg1 = key;

   return callevent;
   }

callthing * callthing::CreateMouseEvent(char * function, int x, int y)
   {
   callthing * callevent = new callthing;
   callevent->kind = EVENTTYPE_Mouse;
   callevent->func = function;
   callevent->arg1 = x;
   callevent->arg2 = y;

   return callevent;
   }

callthing * callthing::CreateFunctionEvent(char * function)
   {
   callthing * callevent = new callthing;
   callevent->kind = EVENTTYPE_YieldFunction;
   callevent->func = function;

   return callevent;
   }

callthing * callthing::CreateNoYieldFunctionEvent(char * function)
   {
   callthing * callevent = new callthing;
   callevent->kind = EVENTTYPE_NoYieldFunction;
   callevent->func = function;

   return callevent;
   }

callthing * callthing::CreateNetworkReceiveReadyEvent(CNetworkConnection * NetworkConnection, const char * packet)
   {
   callthing * callevent = new callthing;
   callevent->kind = EVENTTYPE_NetworkReceiveReady;
   
   callevent->networkconnection = NetworkConnection;

   // copy m_OnReceiveReady now because it might be freed by the time 
   // the event is processed.
   callevent->func = strdup(NetworkConnection->m_OnReceiveReady);

   // copy the network packet into the event (instead of into NetworkConnection) 
   // so that it can be processed in the order in which is was received.
   callevent->networkpacket = strdup(packet);

   return callevent;
   }

callthing::~callthing()
   {
   switch (kind)
      {
      case EVENTTYPE_NetworkReceiveReady:
         free(func);
         free(networkpacket);
         break;
      }
   }

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
      if (g_Turtles[j].IsShown)
         {
         if (g_Turtles[j].Bitmap)
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

   // Must of rewrote this at least 26 times :-) and it still does not
   // work in some situations. This is just the "Paint" of printing.
   // See the print module for all the other stuff.

   // do we even have a chance?
   if ((GetDeviceCaps(PrintDC, RASTERCAPS) & RC_STRETCHDIB) == 0)
      {
      // notify the user that the printer does not support scaling
      MessageBox(
         LOCALIZED_ERROR_PRINTERCANTSCALE, 
         LOCALIZED_ERROR);
      return;
      }

   WORD PrintbitCount = GetDeviceCaps(PrintDC, BITSPIXEL);
   PrintbitCount *= GetDeviceCaps(PrintDC, PLANES);

   // If a mono printer lets let it try to dither a 256 grey scale image
   if (PrintbitCount == 1)
      {
      PrintbitCount = 8;
      }

   // Get screen bitCount
   HDC ScreenDC = GetDC(0);

   WORD ScreenbitCount = GetDeviceCaps(ScreenDC, BITSPIXEL);
   ScreenbitCount *= GetDeviceCaps(ScreenDC, PLANES);

   // Don't bother creating a DIB with more colors than we have
   if (ScreenbitCount < PrintbitCount) 
      {
      PrintbitCount = ScreenbitCount;
      }

   // Round to nearest legal bitmap color depth
   if      (                        (PrintbitCount <  1)) PrintbitCount =  1;
   else if ((PrintbitCount >  1) && (PrintbitCount <  4)) PrintbitCount =  4;
   else if ((PrintbitCount >  4) && (PrintbitCount <  8)) PrintbitCount =  8;
   else if ((PrintbitCount >  8) && (PrintbitCount < 16)) PrintbitCount = 16;
   else if ((PrintbitCount > 16) && (PrintbitCount < 24)) PrintbitCount = 24;
   else if ((PrintbitCount > 24)                        ) PrintbitCount = 32;

   PrintbitCount = GetConfigurationInt("PrintColorDepth", PrintbitCount);

   WORD size;
   if (PrintbitCount <= 8)
      {
      size = sizeof(BITMAPINFOHEADER) + ((1 << PrintbitCount) * sizeof(RGBQUAD));
      }
   else
      {
      size = sizeof(BITMAPINFOHEADER);
      }

   BITMAPINFO * PrintBitmapInfo = (BITMAPINFO *) new char[size];

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

   // we don't need hour glass here because print module takes care of it 

   // allocate space for the raw DIB data
   unsigned char * BitsPtr = new unsigned char [PrintBitmapInfo->bmiHeader.biSizeImage];
   memset(BitsPtr, 0x00, PrintBitmapInfo->bmiHeader.biSizeImage);

   // get printer size per inch 
   long TempWidth = GetDeviceCaps(PrintDC, LOGPIXELSX);
   long TempHeight = GetDeviceCaps(PrintDC, LOGPIXELSY);

   // if palette allocate it
   if (EnablePalette)
      {
      OldPalette = SelectPalette(ScreenDC, ThePalette, FALSE);
      RealizePalette(ScreenDC);
      }

   // set up an assured contrast ?
   SetTextColor(PrintDC, 0x00000000L);
   SetBkColor(PrintDC, 0x00ffffffL);

   long ScanLines = GetDIBits(
      ScreenDC,
      MemoryBitMap,
      0,
      BitMapHeight,
      BitsPtr,
      PrintBitmapInfo,
      DIB_RGB_COLORS);

   // check we got something
   if (ScanLines != 0)
      {
      // if "active area" just print that 
      long Status;

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
      else
         {
         // else print the whole thing
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
         // TODO: message the last error into the current locale
         MessageBox(
            LOCALIZED_ERROR_CANTDRAWIMAGE, 
            LOCALIZED_ERROR);

         char buffer[64];
         MessageBox(
            itoa(GetLastError(), buffer, 10), 
            LOCALIZED_ERROR_SUBCODE);
         }
      }
    else
      {
      // can't do it
      MessageBox(
         LOCALIZED_ERROR_CANTEXTRACTIMAGE,
         LOCALIZED_ERROR);
      }

   // restore resources 
   if (EnablePalette)
      {
      SelectPalette(ScreenDC, OldPalette, FALSE);
      }

   delete [] BitsPtr;

   ReleaseDC(0, ScreenDC);

   delete PrintBitmapInfo;
   }


void TScreenWindow::EvKeyDown(UINT, UINT, UINT)
   {
   TMessage Msg = __GetTMessage();

   // if keyboard was on and up and down is enabled then continue
   if (KeyboardCapture == KEYBOARDCAPTURE_KeyDownKeyUp)
      {
      callthing *callevent = callthing::CreateKeyboardEvent(keyboard_keydown, Msg.WParam);

      calllists.insert(callevent);
      checkqueue();

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
   else if (KeyboardCapture == KEYBOARDCAPTURE_Off &&
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

   if (KeyboardCapture == KEYBOARDCAPTURE_KeyDownKeyUp)
      {
      // if keyboard was on and up and down is enabled then continue
      callthing * callevent = callthing::CreateKeyboardEvent(keyboard_keyup, Msg.WParam);

      calllists.insert(callevent);
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

   if (KeyboardCapture == KEYBOARDCAPTURE_KeyDown)
      {
      // if keyboard was on and NOT up and down is enabled then continue
      callthing * callevent = callthing::CreateKeyboardEvent(keyboard_keyup, Msg.WParam);

      calllists.insert(callevent);
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
   SetFocus();
   SetCapture();

   if (MouseCaptureIsEnabled)
      {
      // if user turned on mouse the queue up event
      callthing * callevent = callthing::CreateMouseEvent(mouse_lbuttondown, point.x, point.y);

      calllists.insert(callevent);
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
   ReleaseCapture();

   if (MouseCaptureIsEnabled)
      {
      // if user turned on mouse the queue up event
      callthing * callevent = callthing::CreateMouseEvent(mouse_lbuttonup, point.x, point.y);

      calllists.insert(callevent);
      checkqueue();
      }
   }

void TScreenWindow::EvRButtonDown(UINT, TPoint &point)
   {
   SetFocus();
   SetCapture();

   if (MouseCaptureIsEnabled)
      {
      // if user turned on mouse the queue up event
      callthing * callevent = callthing::CreateMouseEvent(mouse_rbuttondown, point.x, point.y);

      calllists.insert(callevent);
      checkqueue();
      }
   }

void TScreenWindow::EvRButtonUp(UINT, TPoint &point)
   {
   ReleaseCapture();

   if (MouseCaptureIsEnabled)
      {
      // if user turned on mouse the queue up event
      callthing * callevent = callthing::CreateMouseEvent(mouse_rbuttonup, point.x, point.y);

      calllists.insert(callevent);
      checkqueue();
      }
   }

void TScreenWindow::EvMouseMove(UINT, TPoint &point)
   {
   if (MouseCaptureIsEnabled)
      {
      // if user turned on mouse the queue up event
      callthing * callevent = callthing::CreateMouseEvent(mouse_mousemove, point.x, point.y);

      calllists.insert(callevent);
      checkqueue();
      }
   }

void TScreenWindow::GetScrollRatios(FLONUM & XRatio, FLONUM & YRatio)
   {
   // find out where we are (percentage of pos/range for x and y)

   if (Scroller->XRange <= 1)
      {
      XRatio = 0.5; // center
      }
   else
      {
      // Subtract 1 because the range includes the endpoint.
      // 0-100 implies range = 101
      XRatio = (FLONUM) Scroller->XPos / (FLONUM) (Scroller->XRange - 1);
      }

   if (Scroller->YRange <= 1)
      {
      YRatio = 0.5; // center
      }
   else
      {
      // Subtract 1 because the range includes the endpoint.
      // 0-100 implies range = 101
      YRatio = (FLONUM) Scroller->YPos / (FLONUM) (Scroller->YRange - 1);
      }
   }

void TScreenWindow::AdjustScrollPositionToZoomFactor(FLONUM ZoomFactor)
   {

   //
   // Get the scrollbar position as a ratio of position/range
   //
   FLONUM xRatio;
   FLONUM yRatio;
   GetScrollRatios(xRatio, yRatio);

   //
   // Calculate the new scrollbar ranges
   //
   TRect screenRect;
   GetClientRect(screenRect);

   FLONUM xRange = (BitMapWidth * ZoomFactor) - screenRect.right;
   FIXNUM xRangeRounded = g_round(xRange);
   if (xRangeRounded < 0)
      {
      xRangeRounded = 0;
      }

   FLONUM yRange = (BitMapHeight * ZoomFactor) - screenRect.bottom;
   FIXNUM yRangeRounded = g_round(yRange);
   if (yRangeRounded < 0)
      {
      yRangeRounded = 0;
      }


   //
   // update the scoller
   //

   // Add 1 because the range includes the endpoint.
   // 0-100 implies range = 101
   Scroller->SetRange(xRangeRounded + 1, yRangeRounded + 1);

   // Position the scrollbar to the same ratio as before
   Scroller->ScrollTo(g_round(xRatio * xRange), g_round(yRatio * yRange));
}


void TScreenWindow::EvSize(UINT arg1, TSize &arg2)
   {
   TWindow::EvSize(arg1, arg2);

   // readjust scroller range so that thumb at each extreme 
   // corresponds to edge of extreme image.
   AdjustScrollPositionToZoomFactor(the_zoom);
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
    EditWindow(NULL),
    CommandWindow(new TMyCommandWindow(0, "IDD_DOCKEDCOMMANDER")),
    StatusWindow(NULL),
    PrinterAreaWindow(NULL),
    FileEditWindow(NULL),
    PaneSplitterWindow(PaneSplitter),
    ScreenWindow(new TScreenWindow(0, "FMSLogo Screen")),
    IsNewFile(true),
    IsNewBitmap(true),
    IsCommanderDocked(false)
   {
   /* main window initialization */
   strcpy(BitmapName, "logo.bmp");
   strcpy(FileName, "logo.lgo");


   /* check if a palette exists */
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

TMainFrame::~TMainFrame()
   {
   /* clean things up */
   DeleteObject(MemoryBitMap);
   delete CommandWindow;

   delete ScreenWindow;

   /* if palette clean it too */
   if (EnablePalette)
      {
      DeleteObject(ThePalette);
      delete MyLogPalette;
      }
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
   HWND editH = ::FindWindow(NULL, LOCALIZED_EDITOR_TITLE);

   // if editor is running we could lose unsaved changes
   if (editH)
      {
      ::ShowWindow(editH, SW_SHOWNORMAL);
      ::SetWindowPos(editH, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
      GiveFocusToEditbox = false;

      if (MessageBox(
             LOCALIZED_CHANGESINEDITORMAYBELOST,
             LOCALIZED_EDITSESSIONISRUNNING,
             MB_OKCANCEL | MB_ICONQUESTION) != IDOK)
         {
         return false;
         }
      }


   if (is_executing())
      {
      // The language engine is not halted.
      // Warn user and give chance to abort shutdown.
      if (IsTimeToHalt)
         {
         // we already tried warn user of doom
         if (MessageBox(
                LOCALIZED_NOTHALTEDREALLYEXIT,
                LOCALIZED_LOGOISNOTHALTED,
                MB_OKCANCEL | MB_ICONQUESTION) != IDOK)
            {
            return false;
            }
         }
      else
         {
         // let the user optionally halt first
         if (MessageBox(
                LOCALIZED_NOTHALTEDREALLYHALT,
                LOCALIZED_LOGOISNOTHALTED,
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
      TSaveBeforeExitDialog saveChangesDialog(this);

      saveChangesDialog.Execute();
      int exitCode = saveChangesDialog.GetExitCode();
      if (exitCode == IDCANCEL)
         {
         // don't exit FMSLogo
         IsTimeToHalt  = false;
         IsTimeToExit  = false;
         stopping_flag = RUN;
         return false;
         }
      else if (exitCode == IDYES)
         {
         // save and then exit

         // HACK: Set TimeToExit and TimeToHalt to false
         // so that writing the file to disk doesn't abort.
         // This is hack because the code should not modify
         // global variables--there should be a way to tell 
         // CMFileSave to ignore errors.
         bool savedIsTimeToExit = IsTimeToExit;
         bool savedIsTimeToHalt = IsTimeToHalt;

         IsTimeToExit = false;
         IsTimeToHalt = false;
         CMFileSave();

         IsTimeToExit = savedIsTimeToExit;
         IsTimeToHalt = savedIsTimeToHalt;
         }
      }

      // if we made it here we are OK to exit
      return true;
   }

void TMainFrame::CMExit()
   {
   // here on FILE-EXIT main window (screen)
   if (is_executing())
      {
      IsTimeToHalt = true;
      }
   IsTimeToExit = true;
   }

bool TMainFrame::WriteDIB(FILE* File, int MaxBitCount)
   {
   // grab a DC 
   HDC screen = CreateDC("DISPLAY", NULL, NULL, NULL);

   // hard code to screen mode
   WORD SavebitCount = GetDeviceCaps(screen, BITSPIXEL);
   SavebitCount *= GetDeviceCaps(screen, PLANES);

   if (MaxBitCount < SavebitCount)
      {
      if ((MaxBitCount == 1) || (MaxBitCount == 4) || (MaxBitCount == 8))
         {
         SavebitCount = MaxBitCount;
         }
      }

   // compute size of bitmap
   if (SavebitCount == 16)
      {
      SavebitCount = 24;
      }
   if (SavebitCount == 32)
      {
      SavebitCount = 24;
      }

   WORD size;
   if (SavebitCount <= 8)
      {
      size = sizeof(BITMAPINFOHEADER) + ((1 << SavebitCount) * sizeof(RGBQUAD));
      }
   else
      {
      size = sizeof(BITMAPINFOHEADER);
      }

   BITMAPINFO * SaveBitmapInfo = (BITMAPINFO *) new char[size];

   SaveBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   SaveBitmapInfo->bmiHeader.biWidth = BitMapWidth;
   SaveBitmapInfo->bmiHeader.biHeight = BitMapHeight;
   SaveBitmapInfo->bmiHeader.biPlanes = 1;
   SaveBitmapInfo->bmiHeader.biBitCount = SavebitCount;
   SaveBitmapInfo->bmiHeader.biCompression = BI_RGB;
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
   unsigned char * BitsPtr = new unsigned char[SaveBitmapInfo->bmiHeader.biSizeImage];
   memset(BitsPtr, 0x00, SaveBitmapInfo->bmiHeader.biSizeImage);

   // if palette yank it in 
   HPALETTE oldPalette2;
   if (EnablePalette)
      {
      oldPalette2 = SelectPalette(screen, ThePalette, FALSE);
      RealizePalette(screen);
      }

   // if custom then use custom dimensions
   if (IsPrinterSettingCustom)
      {
      HBITMAP AreaMemoryBitMap = CreateCompatibleBitmap(
         screen,
         PrinterAreaXHigh - PrinterAreaXLow,
         PrinterAreaYHigh - PrinterAreaYLow);

      if (!AreaMemoryBitMap)
         {
         ShowErrorMessageAndStop(LOCALIZED_WRITEFAILEDNOMEMORY);
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
   else
      {
      // else do whole thing
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

   // restore some of the resources
   if (EnablePalette)
      {
      SelectPalette(screen, oldPalette2, FALSE);
      }

   DeleteDC(screen);

   // build header
   BITMAPFILEHEADER BitmapFileHeader;
   BitmapFileHeader.bfType = 19778;
   BitmapFileHeader.bfSize = size + sizeof(BITMAPFILEHEADER) + (int) (SaveBitmapInfo->bmiHeader.biWidth * SaveBitmapInfo->bmiHeader.biHeight * (SavebitCount / 8));
   BitmapFileHeader.bfReserved1 = 0;
   BitmapFileHeader.bfReserved2 = 0;
   BitmapFileHeader.bfOffBits = size + sizeof(BITMAPFILEHEADER);

   // write headers
   fwrite(&BitmapFileHeader, sizeof(char), sizeof(BitmapFileHeader), File);
   fwrite(SaveBitmapInfo, sizeof(char), size, File);

   // write out raw DIB data to file
   fwrite(BitsPtr, sizeof(char), SaveBitmapInfo->bmiHeader.biSizeImage, File);

   delete [] BitsPtr;
   delete SaveBitmapInfo;

   return true;
   }

bool TMainFrame::DumpBitmapFile(LPCSTR Filename, int MaxBitCount)
   {
   // open and check if ok 
   FILE* file = fopen(Filename, "wb");
   if (file != NULL)
      {
      // Load hour-glass cursor.
      HCURSOR oldCursor = ::SetCursor(hCursorWait);

      // do it and if error then let user know 
      if (!WriteDIB(file, MaxBitCount))
         {
         ShowErrorMessageAndStop(LOCALIZED_COULDNOTWRITEBMP);
         }

      // Restore the arrow cursor
      ::SetCursor(oldCursor);

      fclose(file);
      }
   else
      {
      // else file never opened
      ShowErrorMessageAndStop(LOCALIZED_COULDNOTOPENBMP);
      }

   return true;
   }


// Attempt to open a Windows 3.0 device independent bitmap
bool TMainFrame::OpenDIB(FILE* File, DWORD &dwPixelWidth, DWORD &dwPixelHeight)
   {
   // get header 
   rewind(File);

   BITMAPFILEHEADER BitmapFileHeader;
   fread(&BitmapFileHeader, sizeof(char), sizeof(BitmapFileHeader), File);

   // bfOffbits should be equal to BitmapInfoHeader
   BITMAPINFO * ReadBitmapInfo = (BITMAPINFO *) new char[BitmapFileHeader.bfOffBits - sizeof(BitmapFileHeader)];
   fread(ReadBitmapInfo, sizeof(char), BitmapFileHeader.bfOffBits - sizeof(BitmapFileHeader), File);

   // save some typing 
   DWORD NewPixelWidth = ReadBitmapInfo->bmiHeader.biWidth;
   DWORD NewPixelHeight = ReadBitmapInfo->bmiHeader.biHeight;

   if (dwPixelWidth)
      {
      /* do what the spec says */
      if (ReadBitmapInfo->bmiHeader.biClrUsed == 0)
         {
         ReadBitmapInfo->bmiHeader.biClrUsed = 1 << ReadBitmapInfo->bmiHeader.biBitCount;
         }

      /* only allow bitcount equal to display capability */
      WORD ReadbitCount = ReadBitmapInfo->bmiHeader.biBitCount;

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


      /* compute image size if not set */
      if (ReadBitmapInfo->bmiHeader.biSizeImage == 0)
         {
         long longWidth = (((NewPixelWidth * ReadbitCount) + 31) / 32) * 4;

         ReadBitmapInfo->bmiHeader.biSizeImage = longWidth * NewPixelHeight;
         }

      // pack and allocate
      unsigned char * BitsPtr = new unsigned char[ReadBitmapInfo->bmiHeader.biSizeImage];
      memset(BitsPtr, 0x00, ReadBitmapInfo->bmiHeader.biSizeImage);

      // read the file into the bitmap
      fread(BitsPtr, sizeof(char), ReadBitmapInfo->bmiHeader.biSizeImage, File);

      // Create DC comaptible with screen 
      HDC screen = GetDC(MainWindowx->ScreenWindow->HWindow);

      HDC memoryDC = CreateCompatibleDC(screen);
      HDC DCHandle = CreateCompatibleDC(screen);

      HPALETTE oldPalette  = NULL;
      HPALETTE oldPalette2 = NULL;

      // if palette yank it
      if (EnablePalette)
         {
         oldPalette = SelectPalette(memoryDC, ThePalette, FALSE);
         RealizePalette(memoryDC);

         oldPalette2 = SelectPalette(screen, ThePalette, FALSE);
         RealizePalette(screen);
         }

      // now create the bitmap with the bits just loaded
      HBITMAP NewBitmapHandle = CreateDIBitmap(
         screen,
         &ReadBitmapInfo->bmiHeader,
         CBM_INIT,
         BitsPtr,
         ReadBitmapInfo,
         0);

      // now dump the bits 
      delete [] BitsPtr;
      
      if (EnablePalette)
         {
         SelectPalette(screen, oldPalette2, FALSE);
         }

      ReleaseDC(MainWindowx->ScreenWindow->HWindow, screen);


      // now that things are clean we can check if we are ok 

      if (!NewBitmapHandle)
         {
         return false;
         }

      // We've now made a bonefide bitmap. 
      // But we want to copy it into the existing backing store.
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

            from3d.x = g_Turtles[turtle_which].Position.x / WorldWidth;
            from3d.y = g_Turtles[turtle_which].Position.y / WorldHeight;
            from3d.z = g_Turtles[turtle_which].Position.z / WorldDepth;

            if (!ThreeD.TransformPoint(from3d, dest))
               {
               return true;
               }
            }
         else
            {
            dest.x = g_round(g_Turtles[turtle_which].Position.x);
            dest.y = g_round(g_Turtles[turtle_which].Position.y);
            }

         BitBlt(
            memoryDC,
            +dest.x + xoffset,
            -dest.y + yoffset + LL - NewPixelHeight,
            NewPixelWidth,
            NewPixelHeight, 
            DCHandle, 
            0, 
            0, 
            SRCCOPY);
         }

      // return resources
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
      }

   delete [] ReadBitmapInfo;

   dwPixelWidth  = NewPixelWidth;
   dwPixelHeight = NewPixelHeight;
   return true;
   }

bool TMainFrame::LoadBitmapFile(LPCSTR Filename, DWORD &dwPixelWidth, DWORD &dwPixelHeight)
   {
   // Test if the passed file is a Windows 3.0 DIB bitmap and if so read it
   const char * errorMessage = NULL;
   bool retval;

   // open then check if open 
   FILE* file = fopen(Filename, "rb");
   if (file != NULL)
      {

      // check if valid bitmap
      fseek(file, 14, SEEK_SET);

      long TestWin30Bitmap = 0;
      fread(&TestWin30Bitmap, sizeof(char), sizeof(TestWin30Bitmap), file);
      if (TestWin30Bitmap == 40)
         {
         // Load hour-glass cursor.
         HCURSOR oldCursor = ::SetCursor(hCursorWait);

         // if loaded ok then invalidate to display 
         if (OpenDIB(file, dwPixelWidth, dwPixelHeight))
            {
            ScreenWindow->Invalidate(true);
            }
         else
            {
            errorMessage = LOCALIZED_COULDNOTCREATEBMP;
            }

         // Restore the arrow cursor.
         ::SetCursor(oldCursor);
         }
      else
         {
         /* not a bitmap */
         errorMessage = LOCALIZED_NOTVALIDBMP;
         }
      fclose(file);
      }
   else
      {
      /* else file not there */
      errorMessage = LOCALIZED_COULDNOTOPENBMP;
      }

   // if no message the we are ok else display error message
   if (errorMessage == NULL)
      {
      retval = true;
      }
   else
      {
      ShowErrorMessageAndStop(errorMessage);
      retval = false;
      }

   return retval;
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
   FileData.SetFilter(LOCALIZED_FILEFILTER_IMAGE);
   strcpy(FileData.FileName, "*.bmp");
   FileData.DefExt = "bmp";

   /* if user found a file then try to load it  */

   if (TFileOpenDialog(this, FileData).Execute() == IDOK)
      {
      char ext[_MAX_EXT];
      
      IsNewBitmap = FALSE;
      strcpy(BitmapName, FileData.FileName);
      
      _splitpath(BitmapName, NULL, NULL, NULL, ext);
      if (stricmp(ext, ".gif") == 0)
         {
         gifload_helper(BitmapName, dwPixelWidth, dwPixelHeight);
         }
      else
         {
         LoadBitmapFile(BitmapName, dwPixelWidth, dwPixelHeight);
         }
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
   // if new then nulify File name
   if (IsNewBitmap)
      {
      BitmapName[0] = '\0';
      }

   // Get file name from user and then save the file
   TOpenSaveDialog::TData FileData;
   FileData.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_EXPLORER;
   FileData.SetFilter(LOCALIZED_FILEFILTER_IMAGE);
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
   _splitpath(BitmapName, NULL, NULL, NULL, ext);
   if (stricmp(ext, ".gif") == 0)
      {
      gifsave_helper(BitmapName, -1, 0, -1, -1, 8);
      }
   else
      {
      DumpBitmapFile(BitmapName, 32);
      }
   }

void TMainFrame::EraseContentsOfWorkspace()
   {
   NODE * workspace_contents = vref(lcontents(NIL));
   lerase(workspace_contents);
   deref(workspace_contents);
   }

void TMainFrame::CMFileNew()
   {
   // if doing new and dirty give user a chance to abort the new
   if (IsDirty)
      {
      // Warn the user that File-New will erase the contents 
      // of the workspace and give them a chance to cancel the
      // operation.
      if (MainWindowx->CommandWindow->MessageBox(
             LOCALIZED_FILENEWWILLERASEWORKSPACE,
             LOCALIZED_YOUHAVEUNSAVEDCHANGES,
             MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL)
         {
         return;
         }
      }

   // else start with a clean plate
   IsNewFile = true;
   IsDirty = false;

   EraseContentsOfWorkspace();
   }

void TMainFrame::CMFileLoad()
   {
   if (IsDirty)
      {
      // Warn the user that File-Load may erase the contents 
      // of the workspace and give them a chance to cancel the
      // operation.
      if (MainWindowx->CommandWindow->MessageBox(
             LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE,
             LOCALIZED_YOUHAVEUNSAVEDCHANGES,
             MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL)
         {
         return;
         }
      }

   // show the user a file-picker dialog
   TOpenSaveDialog::TData FileData;
   FileData.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER;
   FileData.SetFilter(LOCALIZED_FILEFILTER_LOGO);
   strcpy(FileData.FileName, "*.lgo");
   FileData.DefExt = "lgo";

   // if user found a file then try to load it
   if (TFileOpenDialog(this, FileData).Execute() == IDOK)
      {
      IsNewFile = false;

      start_execution();

      strcpy(FileName, FileData.FileName);
      bool isOk = fileload(FileName);
      if (!isOk) 
         {
         err_logo(
            FILE_ERROR, 
            make_static_strnode(LOCALIZED_ERROR_FILESYSTEM_CANTOPEN));
         }

      // handle any error that may have occured
      process_special_conditions();

      stop_execution();
      }
   }

void TMainFrame::CMFileOpen()
   {
   if (IsDirty)
      {
      // Warn the user that File-Open will erase the contents 
      // of the workspace and give them a chance to cancel the
      // operation.
      if (MainWindowx->CommandWindow->MessageBox(
             LOCALIZED_FILEOPENWILLERASEWORKSPACE,
             LOCALIZED_YOUHAVEUNSAVEDCHANGES,
             MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL)
         {
         return;
         }
      }

   // show the user a file-picker dialog
   TOpenSaveDialog::TData FileData;
   FileData.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER;
   FileData.SetFilter(LOCALIZED_FILEFILTER_LOGO);
   strcpy(FileData.FileName, "*.lgo");
   FileData.DefExt = "lgo";

   // if user found a file then try to open it
   if (TFileOpenDialog(this, FileData).Execute() == IDOK)
      {
      // start with a clean plate
      IsNewFile = false;
      IsDirty   = false;

      // erase the contents of the workspace
      EraseContentsOfWorkspace();

      start_execution();

      strcpy(FileName, FileData.FileName);
      bool isOk = fileload(FileName);
      if (!isOk) 
         {
         err_logo(
            FILE_ERROR, 
            make_static_strnode(LOCALIZED_ERROR_FILESYSTEM_CANTOPEN));
         }

      // handle any error that may have occured
      process_special_conditions();

      stop_execution();
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
   // if new the nulify File name
   if (IsNewFile)
      {
      FileName[0] = '\0';
      }

   // Get file name from user and then save the file
   TOpenSaveDialog::TData FileData;
   FileData.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_EXPLORER;
   FileData.SetFilter(LOCALIZED_FILEFILTER_LOGO);
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
   process_special_conditions();
   }

void TMainFrame::CMBitmapPrinterArea()
   {
   bool bAok;

   // copy real to dynamic
   TPrinterAreaXLow        = PrinterAreaXLow;
   TPrinterAreaXHigh       = PrinterAreaXHigh;
   TPrinterAreaYLow        = PrinterAreaYLow;
   TPrinterAreaYHigh       = PrinterAreaYHigh;
   TPrinterAreaPixels      = PrinterAreaPixels;
   IsTPrinterSettingCustom = IsPrinterSettingCustom;

   do
      {
      bAok = true;

      // if user does not cancel then copy dynamic to real
      if (TMyPrinterAreaWindow(this).Execute() == IDOK)
         {

         if ((TPrinterAreaXLow >= TPrinterAreaXHigh) || (TPrinterAreaYLow >= TPrinterAreaYHigh))
            {
            MainWindowx->CommandWindow->MessageBox(
               LOCALIZED_ERROR_BADINPUT,
               LOCALIZED_ACTIVEAREA);
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

            SetConfigurationInt("Printer.XLow",   PrinterAreaXLow);
            SetConfigurationInt("Printer.XHigh",  PrinterAreaXHigh);
            SetConfigurationInt("Printer.YLow",   PrinterAreaYLow);
            SetConfigurationInt("Printer.YHigh",  PrinterAreaYHigh);
            SetConfigurationInt("Printer.Pixels", PrinterAreaPixels);
            }
         }
      } while (!bAok);
   }

void TMainFrame::CMFileEdit()
   {
   // create and show a dialog for which procedure to edit
   CEditProcedureWindow(this).ShowDialog();
   }

void TMainFrame::CMFileErase()
   {
   // create and show a dialog for which procedure to edit
   CEraseProcedureWindow(this).ShowDialog();
   }


void TMainFrame::CreateEditWindow(const char *FileName, NODE *args, bool check_for_errors)
   {
   // NOTE: EditWindow is deleted when "this" is deleted.
   EditWindow = new TMyFileWindow(
      this, 
      LOCALIZED_EDITOR_TITLE,
      FileName, 
      args, 
      check_for_errors);

   // Do configuration stuff. Build default coords
   int x = (int) (MaxWidth * 0.25);
   int y = (int) (MaxHeight * 0.25);
   int w = (int) (MaxWidth * 0.75);
   int h = (int) (MaxHeight * ScreenSz * 0.75);

   GetConfigurationQuadruple("Editor", &x, &y, &w, &h); 
   checkwindow(&x, &y, &w, &h);

   /* now set them */
   EditWindow->Attr.Style = WS_VISIBLE | WS_POPUPWINDOW | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
   EditWindow->Editor->Attr.Style |= ES_NOHIDESEL;

   // let user edit
   EditWindow->Create();

   // force a resize to fix RichEdit ScrollBar not appearing automatically
   EditWindow->SetWindowPos(0, x, y, w + 1, h, SWP_NOZORDER);
   EditWindow->SetWindowPos(0, x, y, w, h, SWP_NOZORDER);

   if (args != NULL || check_for_errors)
      {
      // retitle without filename
      EditWindow->SetWindowText(LOCALIZED_EDITOR_TITLE);
      }
   }

void TMainFrame::MyPopupEdit(const char *FileName, NODE *args, bool check_for_errors)
   {
   CreateEditWindow(FileName, args, check_for_errors);

   if (args != NULL || check_for_errors)
      {
      // if an error occured "force" a change so that we still in "dirty" state
      if (error_happen)
         {
         error_happen = false;
         EditWindow->Editor->Insert(" ");
         EditWindow->Editor->DeleteSubText(0, 1);
         int iLine = EditWindow->Editor->GetLineFromPos(LinesLoadedOnEdit);
         EditWindow->Editor->Scroll(0, iLine);
         EditWindow->Editor->SetSelection(LinesLoadedOnEdit, LinesLoadedOnEdit);
         }
      }

   GiveFocusToEditbox = false;
   }

void TMainFrame::MyPopupEditToError(const char *FileName)
   {
   // copy the input file to the editor's temporary file
   FILE * srcfile = fopen(FileName, "r");
   if (srcfile != NULL)
      {
      FILE * dstfile = fopen(TempPathName, "w");
      if (dstfile != NULL)
         {
         int ch;
         while ((ch = fgetc(srcfile)) != EOF)
            {
            fputc(ch, dstfile);
            }
         fclose(dstfile);
         }
      fclose(srcfile);
      }

   CreateEditWindow(FileName, NIL, true);

   // exit the editor to force it to notice the error.
   error_happen = false;
   EditWindow->CMExit();
   }

   
static
void
CreateTemplateLogoFileForEditor(
   const char * FileName,
   NODE       * Args
)
   {
   FILE* logoFile = fopen(FileName, "w");
   if (logoFile != NULL)
      {
      if (Args != NULL)
         {
         fwrite("to\n", 1, 3, logoFile);
         fwrite("end\n", 1, 4, logoFile);
         }
      else
         {
         fwrite("\n", 1, 1, logoFile);
         }
      }
      fclose(logoFile);
   }


int TMainFrame::PopupEditorForFile(const char *FileName, NODE *args)
   {
   // If no file (or empty) create template
   FILE * logoFile = fopen(FileName, "r");
   if (logoFile != NULL)
      {
      // file exists.  check if it's empty.
      bool fileIsEmpty = getc(logoFile) == EOF;
      fclose(logoFile);

      if (fileIsEmpty)
         {
         CreateTemplateLogoFileForEditor(FileName, args);
         }
      }
   else
      {
      // file doesn't exist.  Create it.
      CreateTemplateLogoFileForEditor(FileName, args);
      }

   MainWindowx->MyPopupEdit(FileName, args, false);
   return 0;
   }


bool TMainFrame::MyPopupInput(char *Output, const char *Prompt)
   {
   // get user input

   if (TInputDialog(
          this, 
          Prompt, 
          LOCALIZED_INPUT, 
          Output, 
          MAX_BUFFER_SIZE).Execute() == IDOK)
      {
      return true;
      }
   else
      {
      return false;
      }
   }

void
FillMenu(
   TMenu &           Menu,
   const MENUITEM *  MenuItems,
   size_t            MenuItemsLength
   )
   {
   for (size_t i = 0; i < MenuItemsLength; i++)
      {
      if (MenuItems[i].MenuText != NULL)
         {
         Menu.AppendMenu(
            MF_STRING, 
            MenuItems[i].MenuId,
            MenuItems[i].MenuText);
         }
      else
         {
         Menu.AppendMenu(
            MF_SEPARATOR, 
            0, 
            NULL);
         }
      }
   }

void
AppendPopupMenu(
   TMenu &           MainMenu,
   const char *      PopupMenuText,
   const MENUITEM *  PopupMenuItems,
   size_t            PopupMenuItemsLength
   )
   {
   // create the popup menu
   TMenu popupMenu(NoAutoDelete);

   // fill the popup menu with its items
   FillMenu(popupMenu, PopupMenuItems, PopupMenuItemsLength);

   // append the popup menu to the main menu
   MainMenu.AppendMenu(MF_POPUP, popupMenu, PopupMenuText);
   }

void TMainFrame::SetupWindow()
   {
   TDecoratedFrame::SetupWindow();

   //
   // Construct the main menu
   //
   static const MENUITEM fileMenuItems[] = {
      {LOCALIZED_FILE_NEW,    CM_FILENEW},
      {LOCALIZED_FILE_LOAD,   CM_FILELOAD},
      {LOCALIZED_FILE_OPEN,   CM_FILEOPEN},
      {LOCALIZED_FILE_SAVE,   CM_FILESAVE},
      {LOCALIZED_FILE_SAVEAS, CM_FILESAVEAS},
      {0},
      {LOCALIZED_FILE_EDIT,   CM_FILEEDIT},
      {LOCALIZED_FILE_ERASE,  CM_FILEERASE},
      {0},
      {LOCALIZED_FILE_EXIT,   CM_EXIT},
   };

   static const MENUITEM bitmapMenuItems[] = {
      {LOCALIZED_BITMAP_NEW,           CM_BITMAPNEW},
      {LOCALIZED_BITMAP_LOAD,          CM_BITMAPOPEN},
      {LOCALIZED_BITMAP_SAVE,          CM_BITMAPSAVE},
      {LOCALIZED_BITMAP_SAVEAS,        CM_BITMAPSAVEAS},
      {0},
      {LOCALIZED_BITMAP_PRINT,         CM_BITMAPPRINT},
      {LOCALIZED_BITMAP_PRINTERSETUP,  CM_BITMAPPRINTERSETUP},
      {0},
      {LOCALIZED_BITMAP_ACTIVEAREA,    CM_BITMAPPRINTERAREA},
   };

   static const MENUITEM setMenuItems[] = {
      {LOCALIZED_SET_PENSIZE,       CM_SETPENSIZE},
      {0},
      {LOCALIZED_SET_LABELFONT,     CM_SETFONT},
      {LOCALIZED_SET_COMMANDERFONT, CM_SETCOMMANDERFONT},
      {0},
      {LOCALIZED_SET_PENCOLOR,      CM_SETPENCOLOR},
      {LOCALIZED_SET_FLOODCOLOR,    CM_SETFLOODCOLOR},
      {LOCALIZED_SET_SCREENCOLOR,   CM_SETSCREENCOLOR},
   };

   static const MENUITEM zoomMenuItems[] = {
      {LOCALIZED_ZOOM_IN,     CM_ZOOMIN},
      {LOCALIZED_ZOOM_OUT,    CM_ZOOMOUT},
      {LOCALIZED_ZOOM_NORMAL, CM_ZOOMNORMAL},
   };
 
   static const MENUITEM helpMenuItems[] = {
      {LOCALIZED_HELP_INDEX,         CM_HELP},
      {LOCALIZED_HELP_MCI,           CM_HELPMCI},
      {LOCALIZED_HELP_HELP,          CM_HELPHELP},
      {0},
      {LOCALIZED_HELP_TUTORIAL,      CM_HELPTUTORIAL},
      {LOCALIZED_HELP_DEMO,          CM_HELPDEMO},
      {LOCALIZED_HELP_EXAMPLE,       CM_HELPEXAMPLES},
      {LOCALIZED_HELP_RELEASENOTES,  CM_HELPRELEASENOTES},
      {0},
      {LOCALIZED_HELP_ABOUTFMSLOGO,  CM_HELPABOUT},
      {LOCALIZED_HELP_MS,            CM_HELPABOUTMS},
   };

   TMenu mainMenu(CreateMenu());
   AppendPopupMenu(mainMenu, LOCALIZED_FILE,   fileMenuItems,   ARRAYSIZE(fileMenuItems));
   AppendPopupMenu(mainMenu, LOCALIZED_BITMAP, bitmapMenuItems, ARRAYSIZE(bitmapMenuItems));
   AppendPopupMenu(mainMenu, LOCALIZED_SET,    setMenuItems,    ARRAYSIZE(setMenuItems));
   AppendPopupMenu(mainMenu, LOCALIZED_ZOOM,   zoomMenuItems,   ARRAYSIZE(zoomMenuItems));
   AppendPopupMenu(mainMenu, LOCALIZED_HELP,   helpMenuItems,   ARRAYSIZE(helpMenuItems));
   SetMenu(mainMenu);

   PaneSplitterWindow->SetSplitterCushion(MIN_COMMANDER_HEIGHT);
   PaneSplitterWindow->SetSplitterWidth(DEFAULT_SPLITTER_WIDTH);

   PaneSplitterWindow->SplitPane(
      ScreenWindow,
      0,
      psHorizontal);
   
   if (bFixed) 
      {
      // HACK: fix up the frame window's size so that the screen's
      // size matches what the clinet passed in on the command line.
      // There MUST be a simpler/better way, but I do not know
      // how to set the size of the screen client area directly.
      TRect screenWindowRect = ScreenWindow->GetWindowRect();
      int deltax = Attr.W - screenWindowRect.Width();
      int deltay = Attr.H - screenWindowRect.Height();
      
      TRect mainWindowRect;
      mainWindowRect.SetWH(
         0,
         0,
         Attr.W + deltax,
         Attr.H + deltay);

      SetWindowPos(
         NULL,
         mainWindowRect,
         SWP_NOZORDER | SWP_NOMOVE | SWP_NOCOPYBITS);
      }

   IsCommanderDocked = false;
   DockCommanderWindow();

   IsOkayToUseCommanderWindow = true;

   // it's show time for our little friend
   draw_turtle(true);
   }

void TMainFrame::UndockCommanderWindow()
   {
   if (IsCommanderDocked) 
      {
      TMyCommandWindow * newCommandWindow = new TMyCommandWindow(
         ScreenWindow, 
         "IDD_UNDOCKEDCOMMANDER");
      newCommandWindow->Create();
      newCommandWindow->Duplicate(*CommandWindow);
      newCommandWindow->ShowWindow(SW_SHOW);

      if (bFixed)
         {
         // The user requested that we never change the size of the drawing surface,
         // so we must shrink the main window to hold just the screen.
         TRect screenWindowRect;
         screenWindowRect.SetWH(
            0,
            0,
            Attr.W,
            Attr.H - CommandWindow->GetWindowRect().Height() - PaneSplitterWindow->GetSplitterWidth());

         SetWindowPos(
            NULL,
            screenWindowRect,
            SWP_NOZORDER | SWP_NOMOVE | SWP_NOCOPYBITS);
         }

      PaneSplitterWindow->RemovePane(
         CommandWindow,
         TShouldDelete::NoDelete);
         
      // HACK: Reset the window title because the commander's
      // history box appends a "-" (it thinks it's tied
      // to a file and I can't figure out how to tell it
      // that it's not.
      SetWindowText(GetApplication()->GetName());

      delete CommandWindow;
      CommandWindow = newCommandWindow;
      CommandWindow->Editbox.SetFocus();
      IsCommanderDocked = false;
      }
   }

void TMainFrame::DockCommanderWindow()
   {
   if (!IsCommanderDocked) 
      {
      TMyCommandWindow * newCommandWindow = new TMyCommandWindow(
         0, 
         "IDD_DOCKEDCOMMANDER");

      // restore the commander window's height
      int commanderWindowX      = 0;
      int commanderWindowY      = 0;
      int commanderWindowWidth  = 0;
      int commanderWindowHeight = DEFAULT_COMMANDER_HEIGHT;
      GetConfigurationQuadruple(
         "Commander",
         &commanderWindowX,
         &commanderWindowY,
         &commanderWindowWidth,
         &commanderWindowHeight);

      // sanity-check the input
      commanderWindowHeight = max(commanderWindowHeight, MIN_COMMANDER_HEIGHT);


      if (bFixed)
         {
         // The user requested that we never change the size of the drawing surface,
         // so we must grpw the main window to hold the commander window.

         TRect originalWindowRect;
         originalWindowRect.SetWH(
            Attr.X,
            Attr.Y,
            Attr.W,
            Attr.H);

         // grow the main window to hold the splitter and the commander
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
            SWP_NOZORDER | SWP_NOMOVE | SWP_NOCOPYBITS);
         }

      // HACK: Hide the current commander window before adding
      // the new one to the splitter.  This somehow forces a 
      // refresh of the entire screen window.  Without it, the
      // scrollbars sometimes don't show up (I don't know why).
      // This is a hack because I'm sure there's a more direct
      // way to force the scrollbars to show up.
      //
      // See bug #1372200 for details.
      CommandWindow->Show(SW_HIDE);

      PaneSplitterWindow->SplitPane(
         ScreenWindow,
         newCommandWindow,
         psHorizontal);

      const int moveDistance =
         newCommandWindow->GetWindowRect().Height() -
         commanderWindowHeight;

      PaneSplitterWindow->MoveSplitter(
         ScreenWindow,
         moveDistance);

      newCommandWindow->Duplicate(*CommandWindow);

      // redraw the entire screen window
      ScreenWindow->Invalidate(true);
      newCommandWindow->Invalidate(true);

      // HACK: Reset the window title because the commander's
      // history box appends a "-" (it thinks it's tied
      // to a file and I can't figure out how to tell it
      // that it's not.
      SetWindowText(GetApplication()->GetName());

      delete CommandWindow;
      CommandWindow = newCommandWindow;
      CommandWindow->Editbox.SetFocus();
      IsCommanderDocked = true;
      }
   }


void TMainFrame::MyPopupStatusKill()
   {
   // Get location and size of our window on the screen so we can
   // come back up in the same spot next time we are invoked.
   TRect wrect;
   StatusWindow->GetWindowRect(wrect);

   // save the current location
   SetConfigurationQuadruple(
      "Status",
      wrect.Left(),
      wrect.Top(),
      wrect.Width(),
      wrect.Height());

   // now kill the status window
   status_flag = false;

   delete StatusWindow;
   StatusWindow = NULL;
   CommandWindow->UpdateStatusButtonState();
   }

// popup status window
void TMainFrame::MyPopupStatus()
   {
   // flag so that updates are sent
   status_flag = true;

   // pop it up
   StatusWindow = new TMyStatusWindow(this, "DIALOGSTATUS");
   StatusWindow->Create();

   // update button
   CommandWindow->UpdateStatusButtonState();

   // build default coords
   int x = 0;
   int y = 0;
   int w = 0;
   int h = 0;

   // Get last location and size of command window from configuration settings.
   GetConfigurationQuadruple("Status", &x, &y, &w, &h); 
   checkwindow(&x, &y, &w, &h);

   // now set position
   StatusWindow->SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE);

   // update all fields
   update_status_evals();
   update_status_floodcolor();
   update_status_memory();
   update_status_paletteuse();
   update_status_pencolor();
   update_status_pencontact();
   update_status_penstyle();
   update_status_penwidth();
   update_status_screencolor();
   update_status_turtleheading();
   update_status_turtlepitch();
   update_status_turtleposition();
   update_status_turtleroll();
   update_status_turtlevisability();
   update_status_turtlewhich();
   update_status_vectors();

   StatusWindow->ShowWindow(SW_SHOW);
   }


void TMainFrame::CMControlExecute()
   {

   HWND EditH = FindWindow(NULL, LOCALIZED_EDITOR_TITLE);
   HWND TempH = GetActiveWindow();

   // if Main is active find alternate
   if (TempH == MainWindowx->HWindow)
      {

      // if commander up then focus to input box

      if (!CommandWindow->IsIconic())
         {
         CommandWindow->Editbox.SetFocus();
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

      RunLogoInstructionFromGui(logoInstruction);
      }
   }

void TMainFrame::CMSetCommanderFont()
   {
   CommandWindow->ChooseNewFont();
   }

void TMainFrame::CMSetPenSize()
   {
   TSize theSize(get_pen_width(), get_pen_height());

   // if OK then make change
   if (TSizeDialog(this, theSize).Execute() == IDOK)
      {
      char logoInstruction[256];

      sprintf(
          logoInstruction,
          "SETPENSIZE [%d %d]",
          theSize.X(),
          theSize.Y());

      RunLogoInstructionFromGui(logoInstruction);
      }
   }

void 
TMainFrame::ChooseColor(
   COLORREF       InitialColor,
   const char *   EnglishDescription,
   const char *   LogoCommand
   )
   {
   TColor color(InitialColor);

   if (TColorDialog(this, color, EnglishDescription).Execute() == IDOK)
      {
      // the user pressed "OK" so we change the color
      char logoInstruction[256];

      sprintf(
          logoInstruction,
          "%s [%d %d %d]",
          LogoCommand,
          color.Red(),
          color.Green(),
          color.Blue());

      RunLogoInstructionFromGui(logoInstruction);
      }
   }

void TMainFrame::CMSetPenColor()
   {
   ChooseColor(pcolor, "Pen Color", "SETPENCOLOR");
   }

void TMainFrame::CMSetFloodColor()
   {
   ChooseColor(fcolor, "Flood Color", "SETFLOODCOLOR");
   }

void TMainFrame::CMSetScreenColor()
   {
   ChooseColor(scolor, "Screen Color", "SETSCREENCOLOR");
   }

void TMainFrame::CMHelp()
   {
   do_help(NULL);
   }

void TMainFrame::CMHelpMCI()
   {
   WinHelp(MCIHelpFileName, HELP_INDEX, 0);
   }

void TMainFrame::CMHelpHelp()
   {
   WinHelp("WINHELP.HLP", HELP_FINDER, 0);
   }

void TMainFrame::CMHelpDemo()
   {
   do_execution("demo");
   }

void TMainFrame::CMHelpTutorial()
   {
   do_help("Where to Start");
   }


static
void
OpenFileWithDefaultApplication(
   HWND          HWindow,
   const char *  FileName
)
   {
   HINSTANCE childApplication = ShellExecute(
      HWindow,        // handle to parent window
      "open",         // operation to perform
      FileName,       // pointer to filename string
      NULL,           // pointer to string that specifies executable-file parameters
      NULL,           // pointer to string that specifies default directory
      SW_SHOWNORMAL); // whether file is shown when opened
   if (childApplication != NULL)
      {
      CloseHandle(childApplication);
      }
   }


void TMainFrame::CMHelpExamples()
   {
   char szFileName[EXE_NAME_MAX_SIZE + 1];
   MakeHelpPathName(szFileName, "EXAMPLES\\INDEX.HTML");

   OpenFileWithDefaultApplication(HWindow, szFileName);
   }

void TMainFrame::CMHelpReleaseNotes()
   {
   char szFileName[EXE_NAME_MAX_SIZE + 1];
   MakeHelpPathName(szFileName, "FMSLOGO.TXT");

   OpenFileWithDefaultApplication(HWindow, szFileName);
   }

// Set the text of each dialog element programmatically, rather 
// than in the resource files so that that Windows XP uses Unicode,
// instead of the system code page.  This allows Greek to show up
// in Greek.
class CAboutFmsLogoDialog : public TDialog
{
public:
   CAboutFmsLogoDialog(TWindow * Parent) : 
      TDialog(Parent, "ABOUTBOX")
      {
      SetCaption(LOCALIZED_ABOUTFMS);
      }

protected:
   void SetupWindow()
      {
      TDialog::SetupWindow();

      // set the text in all of the static controls
      SetDlgItemText(ID_ABOUTFMS_VERSION,         LOCALIZED_ABOUTFMS_VERSION);
      SetDlgItemText(ID_ABOUTFMS_GUI,             LOCALIZED_ABOUTFMS_GUI);
      SetDlgItemText(ID_ABOUTFMS_INSTALLER,       LOCALIZED_ABOUTFMS_INSTALLER);
      SetDlgItemText(ID_ABOUTFMS_ADVENTURE,       LOCALIZED_ABOUTFMS_ADVENTURE);
      SetDlgItemText(ID_ABOUTFMS_SPECIALTHANKS,   LOCALIZED_ABOUTFMS_SPECIALTHANKS);
      SetDlgItemText(ID_ABOUTFMS_GPL,             LOCALIZED_ABOUTFMS_GPL);
      SetDlgItemText(ID_ABOUTFMS_NEWSGROUP,       LOCALIZED_ABOUTFMS_NEWSGROUP);
      SetDlgItemText(ID_ABOUTFMS_MULTIMEDIALOGIC, LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC);
      SetDlgItemText(IDOK,                        LOCALIZED_ABOUTFMS_OK);
      SetDlgItemText(ID_ABOUTFMS_CORE,            LOCALIZED_ABOUTFMS_CORE);
      }
};

void TMainFrame::CMHelpAbout()
   {
   CAboutFmsLogoDialog(this).Execute();
   }


// Set the text of each dialog element programmatically, rather 
// than in the resource files so that that Windows XP uses Unicode,
// instead of the system code page.  This allows Greek to show up
// in Greek.
class CAboutMultipleSclerosisDialog : public TDialog
{
public:
   CAboutMultipleSclerosisDialog(TWindow * Parent) : 
      TDialog(Parent, "ABOUTMSBOX")
      {
      SetCaption(LOCALIZED_ABOUTMS);
      }

protected:
   void SetupWindow()
      {
      TDialog::SetupWindow();

      // set the text in all of the static controls
      SetDlgItemText(ID_ABOUTMS_CONSIDERDONATING, LOCALIZED_ABOUTMS_CONSIDERDONATING);
      SetDlgItemText(ID_ABOUTMS_FMS,              LOCALIZED_ABOUTMS_FMS);
      SetDlgItemText(IDOK,                        LOCALIZED_ABOUTMS_OK);
      }
};

void TMainFrame::CMHelpAboutMS()
   {
   CAboutMultipleSclerosisDialog(this).Execute();
   }


// Execute File:Print command
void TMainFrame::CMBitmapPrint()
   {
   TRulerOut Printout("Logo Picture");
   Printout.SetBanding(false);
   Printer.Print(this, Printout, true);
   }


// Execute File:Printer-setup command

void TMainFrame::CMBitmapPrinterSetup()
   {
   Printer.Setup(this);
   }

void TMainFrame::EvDestroy()
   {
   // don't save the window size if it's minimized, the commander is undocked,
   // or if FMSLogo was started with the -F option.
   if (!IsIconic() && IsCommanderDocked && !bFixed)
      {
      // Get location and size of our window on the screen so we can
      // come back up in the same spot next time we are invoked.
      const TRect mainWindowRect = GetWindowRect();

      // save the current location
      SetConfigurationQuadruple(
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

   if (WSAGETASYNCERROR(lParam) != 0)
      {
      MessageBox(
         WSAGetLastErrorString(WSAGETASYNCERROR(lParam)),
         "WSAAsyncGetHostByNameCallBack()");
      // err_logo(STOP_ERROR,NIL);
      return 0;
      }

   if (!g_ClientConnection.IsEnabled())
      {
      // The network client side has been shut down.
      // This message must have been delayed.
      return 0;
      }

   // update flags based on event type
   switch (WSAGETSELECTEVENT(lParam))
      {
      case FD_READ:
         g_ClientConnection.AsyncReceive(this, "recv(sendsock)");
         return 0;

      case FD_WRITE:
         // allow another frame to go out.
         g_ClientConnection.m_IsBusy = false;
         break;

      case FD_CONNECT:
         // flag it's ok to start firing
         g_ClientConnection.m_IsConnected = true;
         break;

      case FD_CLOSE:
         // done
         g_ClientConnection.AsyncClose(this);
         break;
      }

   // we don't distinguish between all event types
   g_ClientConnection.PostOnSendReadyEvent(this);
   return 0;
   }

static
void
InitializeSocketAddress(
   SOCKADDR_IN & SocketAddress,
   PHOSTENT      HostEntry,
   unsigned int  Port
   )
   {
   // always start clean
   memset(&SocketAddress, 0, sizeof(SOCKADDR_IN));

   // what else is there
   SocketAddress.sin_family = AF_INET;

   memcpy(&SocketAddress.sin_addr, HostEntry->h_addr, HostEntry->h_length);

   SocketAddress.sin_port = htons(Port); // Convert to network ordering
   }

LRESULT TMainFrame::OnNetworkConnectSendFinish(WPARAM /* wParam */, LPARAM lParam)
   {
   TMessage msg = __GetTMessage();

   if (WSAGETASYNCERROR(lParam) != 0)
      {
      MessageBox(
         WSAGetLastErrorString(WSAGETASYNCERROR(lParam)),
         "WSAAsyncGetHostByNameCallBack()");
      // err_logo(STOP_ERROR,NIL);
      return 0;
      }

   if (!g_ClientConnection.IsEnabled())
      {
      // The client-side is not initialized.
      // This must be a delayed event coming in after shutdown.
      MessageBox(
         LOCALIZED_ERROR_NETWORKSHUTDOWN,
         LOCALIZED_ERROR_NETWORK);
      return 0;
      }

   SOCKADDR_IN send_dest_sin;

   InitializeSocketAddress(
      send_dest_sin,
      g_ClientConnection.m_HostEntry,
      g_ClientConnection.m_Port);

   // watch for connect
   if (WSAAsyncSelect(
          g_ClientConnection.m_Socket,
          MainWindowx->HWindow,
          WM_NETWORK_CONNECTSENDACK,
          FD_CONNECT | FD_WRITE | FD_READ | FD_CLOSE) == SOCKET_ERROR)
      {
      MessageBox(WSAGetLastErrorString(0), "WSAAsyncSelect(sendSock) FD_CONNECT");
      // err_logo(STOP_ERROR,NIL);
      }

   // lets try now
   int rval = connect(g_ClientConnection.m_Socket, (PSOCKADDR) & send_dest_sin, sizeof(send_dest_sin));
   if (rval == SOCKET_ERROR)
      {
      if (WSAGetLastError() != WSAEWOULDBLOCK)
         {
         MessageBox(WSAGetLastErrorString(0), "connect(sendsock)");
         // err_logo(STOP_ERROR,NIL);
         return 0;
         }
      }

#ifdef UDP
   // fake an FD_CONNECT for UDP, these would of been called by winsock if TCP
   OnNetworkConnectSendAck(0, MAKELONG(FD_CONNECT, FD_CONNECT));
#endif

   // fire event that connection is made
   g_ClientConnection.PostOnSendReadyEvent(this);
   return 0;
   }

LRESULT TMainFrame::OnNetworkListenReceiveAck(WPARAM /* wParam */, LPARAM lParam)
   {
   SOCKADDR_IN acc_sin;       // Accept socket address - internet style
   int acc_sin_len;           // Accept socket address length

   TMessage msg = __GetTMessage();

   if (WSAGETASYNCERROR(lParam) != 0)
      {
      MessageBox(
         WSAGetLastErrorString(WSAGETASYNCERROR(lParam)),
         "WSAAsyncGetHostByNameCallBack()");
      // err_logo(STOP_ERROR,NIL);
      return 0;
      }

   if (!g_ServerConnection.IsEnabled())
      {
      // The server-side is not initialized.
      // This must be a delayed event coming in after shutdown.
      return 0;
      }


   // based on event do the right thing
   switch (WSAGETSELECTEVENT(lParam))
      {
      case FD_READ:
         g_ServerConnection.AsyncReceive(this, "recv(receivesock)");
         return 0;

      case FD_ACCEPT:
         // disabled for UDP
#ifndef USE_UDP
         acc_sin_len = sizeof(acc_sin);

         g_ServerConnection.m_Socket = accept(
            g_ServerConnection.m_Socket, 
            (struct sockaddr *) &acc_sin, 
            &acc_sin_len);
         if (g_ServerConnection.m_Socket == INVALID_SOCKET)
            {
            MessageBox(WSAGetLastErrorString(0), "accept(receivesock)");
            // err_logo(STOP_ERROR,NIL);
            return 0;
            }
#endif
         g_ServerConnection.m_IsConnected = true;

         break;

      case FD_CLOSE:

         g_ServerConnection.AsyncClose(this);
         break;

      case FD_WRITE:

         // allow another frame to go out.
         g_ServerConnection.m_IsBusy = false;
         break;
      }

   // all other events just queue the event
   g_ServerConnection.PostOnSendReadyEvent(this);
   return 0;
   }


LRESULT TMainFrame::OnNetworkListenReceiveFinish(WPARAM /* wParam */, LPARAM lParam)
   {
   TMessage msg = __GetTMessage();

   if (WSAGETASYNCERROR(lParam) != 0)
      {
      MessageBox(
         WSAGetLastErrorString(WSAGETASYNCERROR(lParam)),
         "WSAAsyncGetHostByNameCallBack()");
      // err_logo(STOP_ERROR,NIL);
      return 0;
      }

   if (!g_ServerConnection.IsEnabled())
      {
      // TODO: print an error about the network being shutdown
      return 0;
      }

   SOCKADDR_IN receive_local_sin;

   InitializeSocketAddress(
      receive_local_sin,
      g_ServerConnection.m_HostEntry,
      g_ServerConnection.m_Port);

   // Associate an address with a socket. (bind)
   int rval = bind(
      g_ServerConnection.m_Socket, 
      (struct sockaddr *) &receive_local_sin, 
      sizeof(receive_local_sin));
   if (rval == SOCKET_ERROR)
      {
      MessageBox(WSAGetLastErrorString(0), "bind(receivesock)");
      // err_logo(STOP_ERROR,NIL);
      return 0;
      }

   // listen for connect

#ifndef USE_UDP
   if (listen(g_ServerConnection.m_Socket, MAX_PENDING_CONNECTS) == SOCKET_ERROR)
      {
      MessageBox(WSAGetLastErrorString(0), "listen(receivesock)");
      // err_logo(STOP_ERROR,NIL);
      return 0;
      }
#endif

   // watch for when connect happens
   rval = WSAAsyncSelect(
      g_ServerConnection.m_Socket,
      MainWindowx->HWindow,
      WM_NETWORK_LISTENRECEIVEACK,
      FD_ACCEPT | FD_READ | FD_WRITE | FD_CLOSE);
   if (rval == SOCKET_ERROR)
      {
      MessageBox(WSAGetLastErrorString(0), "WSAAsyncSelect(receivesock) FD_ACCEPT");
      // err_logo(STOP_ERROR,NIL);
      }

   // fake an FD_ACCEPT for UDP, this automatically happens on TCP

#ifdef USE_UDP
   OnNetworkListenReceiveAck(0, MAKELONG(FD_ACCEPT, FD_ACCEPT));
#endif

   // queue this event
   g_ServerConnection.PostOnSendReadyEvent(this);
   return 0;
   }

LRESULT TMainFrame::MMMCINotify(WPARAM, LPARAM)
   {
   TMessage msg = __GetTMessage();

   // if user fired up a callback mci event the queue it up here
   callthing * callevent = callthing::CreateNoYieldFunctionEvent(mci_callback);

   calllists.insert(callevent);

   PostMessage(WM_CHECKQUEUE, 0, 0);

   return (LRESULT) msg.Result;
   }

void TMainFrame::EvTimer(UINT)
   {
   TMessage msg = __GetTMessage();

   // if user fired up a callback mci event the queue it up here

   callthing *callevent;
   // The ID can only be 1-31.
   // select appropriate function event type
   if (msg.WParam > 16)
      {
      // yieldable
      callevent = callthing::CreateFunctionEvent(timer_callback[msg.WParam]);
      }
   else
      {
      // not safe to yield
      callevent = callthing::CreateNoYieldFunctionEvent(timer_callback[msg.WParam]);
      }

   calllists.insert(callevent);
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


void TMainFrame::CmSelectAll()
   {
   // delegate the window event to whichever window has focus
   HWND activeWindow = GetFocus();
   if (activeWindow != HWindow)
      {
      ::SendMessage(activeWindow, WM_COMMAND, CM_EDITSELECTALL, 0);
      }
   }

DEFINE_RESPONSE_TABLE1(TMainFrame, TDecoratedFrame)
  EV_WM_DESTROY,
  EV_WM_TIMER,
  EV_WM_SIZE,
  EV_COMMAND(CM_FILENEW, CMFileNew),
  EV_COMMAND(CM_FILELOAD, CMFileLoad),
  EV_COMMAND(CM_FILEOPEN, CMFileOpen),
  EV_COMMAND(CM_FILESAVE, CMFileSave),
  EV_COMMAND(CM_FILESAVEAS, CMFileSaveAs),
  EV_COMMAND(CM_FILEEDIT, CMFileEdit),
  EV_COMMAND(CM_FILEERASE, CMFileErase),
  EV_COMMAND(CM_EDITSELECTALL, CmSelectAll),
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

