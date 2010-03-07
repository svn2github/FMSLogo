// -*- c++ -*-
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

#ifndef __AREAWND_H_
#define __AREAWND_H_

#include <owl\dialog.h>
#include <owl\printer.h>

struct NODE;

class CPrinterAreaWindow : public TDialog
{
public:

    CPrinterAreaWindow(TWindow * Parent);

    int m_XLow;
    int m_XHigh;
    int m_YLow;
    int m_YHigh;
    int m_PixelsPerInch;

protected:
    void SetupWindow();
    void CloseWindow(int);
    void DoReset(UINT);

private:
    void ResetWindow();

    DECLARE_RESPONSE_TABLE(CPrinterAreaWindow);
};

// function definitions
extern bool IsActiveAreaOneToOneWithScreen(void);
extern NODE *lsetactivearea(NODE *arg);
extern NODE *lactivearea(NODE *arg);

extern NODE *lportopen(NODE *args);
extern NODE *lportclose(NODE *arg);
extern NODE *lportreadchar(NODE *arg);
extern NODE *lportwritechar(NODE *args);
extern NODE *lportreadarray(NODE *args);
extern NODE *lportwritearray(NODE *args);
extern NODE *lportflush(NODE *args);
extern NODE *lportmode(NODE *args);
extern NODE *linportb(NODE *args);
extern NODE *loutportb(NODE *args);
extern NODE *linport(NODE *args);
extern NODE *loutport(NODE *args);
extern NODE *lingameport(NODE *args);

extern NODE *lsetfocus(NODE *args);
extern NODE *lgetfocus(NODE *arg);
extern NODE *lwindowset(NODE *args);

extern NODE *lnetaccepton(NODE *args);
extern NODE *lnetacceptoff(NODE *arg);
extern NODE *lnetacceptsendvalue(NODE *args);
extern NODE *lnetacceptreceivevalue(NODE *arg);
extern NODE *lnetconnecton(NODE *args);
extern NODE *lnetconnectoff(NODE *arg);
extern NODE *lnetconnectsendvalue(NODE *args);
extern NODE *lnetconnectreceivevalue(NODE *arg);
extern NODE *lnetstartup(NODE *args);
extern NODE *lnetshutdown(NODE *arg);


// global variables
extern int g_PrinterAreaXLow;
extern int g_PrinterAreaXHigh;
extern int g_PrinterAreaYLow;
extern int g_PrinterAreaYHigh;
extern int g_PrinterAreaPixels;

#endif // __AREAWND_H_

