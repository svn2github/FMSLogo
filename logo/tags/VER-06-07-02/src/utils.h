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

#ifndef __UTILS_H
#define __UTILS_H

void
GetPrivateProfileQuadruple(
   const char *        Section,
   const char *        Key,
   int *               Value1,
   int *               Value2,
   int *               Value3,
   int *               Value4
);

void
SetPrivateProfileQuadruple(
    const char *        Section,
    const char *        Key,
    int                 Value1,
    int                 Value2,
    int                 Value3,
    int                 Value4
);

bool
SetPrivateProfileFont(
   LPCSTR     ApplicationName,
   LOGFONT  & LogFont
);

bool
GetPrivateProfileFont(
   LPCSTR     ApplicationName,
   LOGFONT  & LogFont
);

void
SetPrivateProfileInt(
    const char *        Section,
    const char *        Key,
    int                 Value
);

#endif // __UTILS_H_

