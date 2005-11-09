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

TMyPrinterAreaWindow::TMyPrinterAreaWindow(
   TWindow *AParent,
   LPCSTR   ATitle
) : TDialog(AParent, ATitle)
   {
   }

TMyPrinterAreaWindow::~TMyPrinterAreaWindow()
   {
   }

/* These next 4 routines fetch the active area dimensions */

void TMyPrinterAreaWindow::CloseWindow(int arg)
   {
   TPrinterAreaXLow  = GetDlgItemInt(ID_XLOW);
   TPrinterAreaXHigh = GetDlgItemInt(ID_XHIGH);
   TPrinterAreaYLow  = GetDlgItemInt(ID_YLOW);
   TPrinterAreaYHigh = GetDlgItemInt(ID_YHIGH);

   TPrinterAreaPixels = GetDlgItemInt(ID_PIXELS);
   
   if ((TPrinterAreaXLow  == -BitMapWidth  / 2) &&
       (TPrinterAreaXHigh == +BitMapWidth  / 2) &&
       (TPrinterAreaYLow  == -BitMapHeight / 2) &&
       (TPrinterAreaYHigh == +BitMapHeight / 2))
       {
       IsTPrinterSettingCustom = false;
       }
   else
       {
       IsTPrinterSettingCustom = true;
       }

   TDialog::CloseWindow(arg);
   }

void TMyPrinterAreaWindow::ResetWindow()
   {
   // display active parameters
   SetDlgItemInt(ID_XLOW,  TPrinterAreaXLow);
   SetDlgItemInt(ID_XHIGH, TPrinterAreaXHigh);
   SetDlgItemInt(ID_YLOW,  TPrinterAreaYLow);
   SetDlgItemInt(ID_YHIGH, TPrinterAreaYHigh);

   SetDlgItemInt(ID_PIXELS, TPrinterAreaPixels);
   }

void TMyPrinterAreaWindow::SetupWindow()
   {
   TDialog::SetupWindow();

   // display active parameters
   ResetWindow();
   }

void TMyPrinterAreaWindow::DoReset(UINT)
   {
   // hack to init things

   TPrinterAreaXLow  = -BitMapWidth / 2;
   TPrinterAreaXHigh = +BitMapWidth / 2;
   TPrinterAreaYLow  = -BitMapHeight / 2;
   TPrinterAreaYHigh = +BitMapHeight / 2;

   TPrinterAreaPixels = max(BitMapWidth, BitMapHeight) / 8;

   ResetWindow();
   }

NODE *lsetactivearea(NODE *arg)
   {
   NODE * args = vector_4_arg(arg);

   // better be a list

   if (NOT_THROWING)
      {
      // apply all args that are given
      NODE * xlow  = car(args);
      NODE * ylow  = car(cdr(args));
      NODE * xhigh = car(cdr(cdr(args)));
      NODE * yhigh = car(cdr(cdr(cdr(args))));

      PrinterAreaXLow  = ((nodetype(xlow)  == FLOAT) ? getfloat(xlow)  : (FLONUM) getint(xlow));
      PrinterAreaYLow  = ((nodetype(ylow)  == FLOAT) ? getfloat(ylow)  : (FLONUM) getint(ylow));
      PrinterAreaXHigh = ((nodetype(xhigh) == FLOAT) ? getfloat(xhigh) : (FLONUM) getint(xhigh));
      PrinterAreaYHigh = ((nodetype(yhigh) == FLOAT) ? getfloat(yhigh) : (FLONUM) getint(yhigh));

      if ((PrinterAreaXLow >= PrinterAreaXHigh) || (PrinterAreaYLow >= PrinterAreaYHigh))
         {
         MainWindowx->CommandWindow->MessageBox("Bad argument", "Active Area");
         err_logo(STOP_ERROR, NIL);
         return (UNBOUND);
         }

      char szWinLocStr[WININISIZ];
      sprintf(szWinLocStr, "%d", PrinterAreaXLow);
      WritePrivateProfileString("Printer", "XLow", szWinLocStr, "LOGO.INI");
      sprintf(szWinLocStr, "%d", PrinterAreaXHigh);
      WritePrivateProfileString("Printer", "XHigh", szWinLocStr, "LOGO.INI");
      sprintf(szWinLocStr, "%d", PrinterAreaYLow);
      WritePrivateProfileString("Printer", "YLow", szWinLocStr, "LOGO.INI");
      sprintf(szWinLocStr, "%d", PrinterAreaYHigh);
      WritePrivateProfileString("Printer", "YHigh", szWinLocStr, "LOGO.INI");

      if ((PrinterAreaXLow  == -BitMapWidth  / 2) &&
          (PrinterAreaXHigh == +BitMapWidth  / 2) &&
          (PrinterAreaYLow  == -BitMapHeight / 2) &&
          (PrinterAreaYHigh == +BitMapHeight / 2))
         {
         IsPrinterSettingCustom = false;
         }
      else
         {
         IsPrinterSettingCustom = true;
         }
      }

   return UNBOUND;
   }

NODE *lactivearea(NODE *)
   {
   return cons_list(
      make_intnode((FIXNUM) PrinterAreaXLow),
      make_intnode((FIXNUM) PrinterAreaYLow),
      make_intnode((FIXNUM) PrinterAreaXHigh),
      make_intnode((FIXNUM) PrinterAreaYHigh));
   }


DEFINE_RESPONSE_TABLE1(TMyPrinterAreaWindow, TDialog)
  EV_CHILD_NOTIFY_ALL_CODES(ID_RESETEXTENT, DoReset),
END_RESPONSE_TABLE;

