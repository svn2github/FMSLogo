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

#ifndef __ASSEMBLY_H_
#define __ASSEMBLY_H_

extern void MyBeep(unsigned int dwFreq, unsigned int dwDuration);
extern void Myoutportb(short portid, unsigned char value);
extern unsigned char Myinportb(short portid);
extern void Myoutport(short portid, short value);
extern short Myinport(short portid);
extern int Myingameport (short portid, short mask);

#endif // __ASSEMBLY_H_

