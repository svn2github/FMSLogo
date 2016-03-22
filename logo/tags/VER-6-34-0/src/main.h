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

#ifndef __MAIN_H_
#define __MAIN_H_

#include "3dsolid.h"
#include "error.h"
#include "logocore.h"
#include "print.h"

struct NODE;

// Functions
extern void single_step_box(NODE *the_line);
extern void ShowMessage(const char * Title, const char * Message);
extern void ShowMessageAndStop(const char * Title, const char * Message);
extern void ShowErrorMessageAndStop(const char * Message);
extern void ShowErrorMessage(const char * Message);
extern void ShowErrorMessage(ERR_TYPES ErrorCode);
extern void RunLogoInstructionFromGui(char * LogoInstruction);
extern void putcombobox(const char * Text, MESSAGETYPE MessageType);
extern void clearcombobox();
extern char * promptuser(const char *prompt);
extern void ChangeActivePenColor(int Red, int Green, int Blue);
extern void ChangeActiveFloodColor(int Red, int Green, int Blue);
extern void ChangeActiveScreenColor(int Red, int Green, int Blue);
extern void ContextHelp(class TEdit *Editor);

// global variables
extern bool bFixed;
extern NODE *exec_list;
extern bool error_happen;
extern char edit_editexit[];

extern class TMainFrame *MainWindowx;

extern int BitMapWidth;
extern int BitMapHeight;
extern bool IsOkayToUseCommanderWindow;

extern int *TopOfStack;

#endif // _MAIN_H_
