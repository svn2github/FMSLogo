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

#ifndef __PRINT_H_
#define __PRINT_H_

#include <stdio.h>

// function declarations
extern void real_print_node(FILE *strm, const NODE *nd, int depth, int width);
extern void update_coords(char ch);
extern void print_char(FILE *strm, char ch);
extern void print_space(FILE *strm);
extern void ndprintf(FILE *strm, const char *fmt, ...);
extern void print_helper(FILE *strm, NODE *nd);
extern void print_node(FILE *strm, NODE *nd);
extern void print_nobrak(FILE *strm, NODE *nd);
extern void new_line(FILE *strm);
extern NODE *lshow(NODE *args);
extern NODE *ltype(NODE *args);
extern NODE *lprint(NODE *args);

// global variables
extern int   print_stringlen;
extern char *print_stringptr;
extern bool  print_backslashes;


#endif // __PRINT_H_
