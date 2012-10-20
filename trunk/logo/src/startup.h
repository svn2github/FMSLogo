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

#ifndef __STARTUP_H_
#define __STARTUP_H_

#include "graphics.h"

// global variable declarations
extern Color dfld;
extern Color dscn;

extern char LibPathName[];
extern char TempPathName[];
extern char TempBmpName[];
extern char TempClipName[];
extern char szHelpFileName[];

#ifndef WX_PURE
extern OSVERSIONINFO g_OsVersionInformation;
extern char          g_FmslogoBaseDirectory[MAX_PATH+1];
#endif // WX_PURE


extern void DisableDataExecutionProtection();
extern void MakeHelpPathName(char *szFileName, const char *);
extern void init_graphics();
extern void init_osversion();
extern void init_cursors();

#endif // __STARTUP_H_
