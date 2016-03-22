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

#include "areawind.h"
#include "activearea.h"
#include "logorc.h"
#include "localizedstrings.h"
#include "mainwind.h"
#include "main.h"
#include "debugheap.h"


CPrinterAreaWindow::CPrinterAreaWindow(
    TWindow * ParentWindow
    ) : 
    TDialog(ParentWindow, IDD_SELECTACTIVEAREA),
    m_XLow(g_PrinterAreaXLow),
    m_XHigh(g_PrinterAreaXHigh),
    m_YLow(g_PrinterAreaYLow),
    m_YHigh(g_PrinterAreaYHigh),
    m_PixelsPerInch(g_PrinterAreaPixels)
{
    SetCaption(LOCALIZED_SELECTACTIVEAREA);
}

void CPrinterAreaWindow::SetupWindow()
{
    TDialog::SetupWindow();

    static const MENUITEM staticText[] = 
    {
        {LOCALIZED_SELECTACTIVEAREA_EFFECT,       ID_SELECTACTIVEAREA_EFFECT},
        {LOCALIZED_SELECTACTIVEAREA_YHIGH,        ID_SELECTACTIVEAREA_YHIGH},
        {LOCALIZED_SELECTACTIVEAREA_YLOW,         ID_SELECTACTIVEAREA_YLOW},
        {LOCALIZED_SELECTACTIVEAREA_XHIGH,        ID_SELECTACTIVEAREA_XHIGH},
        {LOCALIZED_SELECTACTIVEAREA_XLOW,         ID_SELECTACTIVEAREA_XLOW},
        {LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH, ID_SELECTACTIVEAREA_STEPSPERINCH},
        {LOCALIZED_SELECTACTIVEAREA_RESET,        ID_RESETEXTENT},
        {LOCALIZED_SELECTACTIVEAREA_CANCEL,       IDCANCEL},
        {LOCALIZED_SELECTACTIVEAREA_OK,           IDOK},
    };

    // set the text in all of the static controls
    SetTextOnChildWindows(this, staticText, ARRAYSIZE(staticText));

    // display active parameters
    ResetWindow();
}


// The next 4 routines fetch the active area dimensions 
void CPrinterAreaWindow::CloseWindow(int arg)
{
    // read from the dialog to the member variables
    m_XLow  = GetDlgItemInt(ID_XLOW);
    m_XHigh = GetDlgItemInt(ID_XHIGH);
    m_YLow  = GetDlgItemInt(ID_YLOW);
    m_YHigh = GetDlgItemInt(ID_YHIGH);

    m_PixelsPerInch = GetDlgItemInt(ID_PIXELS);

    TDialog::CloseWindow(arg);
}

void CPrinterAreaWindow::ResetWindow()
{
    // display active parameters
    SetDlgItemInt(ID_XLOW,  m_XLow);
    SetDlgItemInt(ID_XHIGH, m_XHigh);
    SetDlgItemInt(ID_YLOW,  m_YLow);
    SetDlgItemInt(ID_YHIGH, m_YHigh);

    SetDlgItemInt(ID_PIXELS, m_PixelsPerInch);
}

void CPrinterAreaWindow::DoReset(UINT)
{
    // restore to defaults
    m_XLow  = -BitMapWidth  / 2;
    m_XHigh = +BitMapWidth  / 2;
    m_YLow  = -BitMapHeight / 2;
    m_YHigh = +BitMapHeight / 2;

    m_PixelsPerInch = max(BitMapWidth, BitMapHeight) / 8;

    ResetWindow();
}

DEFINE_RESPONSE_TABLE1(CPrinterAreaWindow, TDialog)
    EV_CHILD_NOTIFY_ALL_CODES(ID_RESETEXTENT, DoReset),
END_RESPONSE_TABLE;

