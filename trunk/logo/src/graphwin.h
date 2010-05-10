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

#ifndef __GRAPHWIN_H_
#define __GRAPHWIN_H_

#include "logocore.h"

// function declarations
extern bool HtmlHelpInitialize();
extern void HtmlHelpUninitialize();
extern NODE *lstatus(NODE *arg);
extern NODE *lnostatus(NODE *arg);
extern void zoom_helper(FLONUM temp_zoom);
extern void UpdateZoomControlFlag();
extern NODE *lzoom(NODE *arg);
extern NODE *lwinhelp(NODE *arg);
extern NODE *lhelp(NODE *arg);
extern NODE *lsetlabelfont(NODE *arg);
extern NODE *lfontfacenames(NODE *arg);
extern NODE *llabelfont(NODE *arg);
extern NODE *lsetfocus(NODE *args);
extern NODE *lgetfocus(NODE *arg);
extern NODE *lwindowset(NODE *args);
extern void logofill(bool bOld);
extern SIZE labelsize(const char *s);
extern void label(const char *s);
extern void UpdateErasePen(int Width, COLORREF Color);
extern void UpdateNormalPen(int Width, COLORREF Color);
extern void init_bitmaps();
extern void uninit_bitmaps();
extern void ibmturt(bool hide);
extern void do_help(const char *arg);
extern void ibm_clear_screen(void);
extern int get_pen_width(void);
extern void set_pen_width(int w);
extern int get_pen_height(void);
extern void set_pen_height(int h);

#endif // __GRAPHWIN_H_

