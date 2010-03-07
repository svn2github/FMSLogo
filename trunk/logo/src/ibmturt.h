// -*- c++ -*-
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

#ifndef __IBMTURT_H_
#define __IBMTURT_H_

#include <windows.h>


// File ibmterm.cpp
extern void single_step_box(NODE *the_line);
extern void checkqueue(void);
extern void emptyqueue(void);
extern void do_help(const char *arg);
extern void checkwindow(int *x, int *y, int *w, int *h);
extern bool check_stop(bool scan_for_messages);
extern void ibm_clear_screen(void);
extern void pen_down(void);
extern void pen_reverse(void);
extern void pen_erase(void);
extern int get_pen_width(void);
extern void set_pen_width(int w);
extern int get_pen_height(void);
extern void set_pen_height(int h);
extern void set_list_pen_pattern(NODE *arg);
extern void get_pen_pattern(char *pat);
extern NODE *get_node_pen_pattern(void);
extern NODE *get_node_pen_mode(void);
extern void label(const char *s);
extern SIZE labelsize(const char *s);
extern void logofill(bool bOld);
extern void erase_screen(void);
extern bool button(void);
extern void tone(FIXNUM pitch, FIXNUM duration);

#endif // __IBMTURT_H_

