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
#include "graphics.h"

struct NODE;

enum KEYBOARDCAPTURE
{
    KEYBOARDCAPTURE_Off,
    KEYBOARDCAPTURE_KeyDown,
    KEYBOARDCAPTURE_KeyDownKeyUp,
};

enum INPUTMODE
{
    INPUTMODE_None,
    INPUTMODE_To,
    INPUTMODE_List,
    INPUTMODE_Pause,
};



// Functions
extern void single_step_box(NODE *the_line);
extern struct PENSTATE & GetPenStateForSelectedTurtle();
extern void GetWorkingAreaDimensions(int & workingAreaWidth, int & workingAreaHeight);
extern void ShowMessage(const char * Title, const char * Message);
extern void ShowMessageAndStop(const char * Title, const char * Message);
extern void ShowErrorMessageAndStop(const char * Message);
extern void ShowErrorMessage(const char * Message);
extern void ShowErrorMessage(ERR_TYPES ErrorCode);
extern void MyMessageScan(void);
extern void RunLogoInstructionFromGui(char * LogoInstruction);
extern void putcombobox(const char *str);
extern void clearcombobox(void);
extern COLORREF LoadColor(int dpenr, int dpeng, int dpenb);
extern void exit_program(void);
extern bool promptuser(char *str, const char *prompt);
extern void move_to(FLONUM x, FLONUM y);
extern void line_to(FLONUM x, FLONUM y);
extern void move_to_3d(FLONUM x, FLONUM y, FLONUM z);
extern void line_to_3d(const Point & ToPoint);
extern void ChangeActivePenColor(int Red, int Green, int Blue);
extern void ChangeActiveFloodColor(int Red, int Green, int Blue);
extern void ChangeActiveScreenColor(int Red, int Green, int Blue);
extern void MakeHelpPathName(char *szFileName, LPCSTR);
extern void ContextHelp(class TEdit *Editor);

// global variables
extern bool yield_flag;
extern int GCMAX;
extern bool bExpert;
extern bool bFixed;
extern NODE **hash_table;
extern NODE *current_line;
extern NODE *exec_list;
extern char TempPathName[];
extern bool IsTimeToExit;
extern bool IsTimeToPause;
extern bool IsTimeToHalt;
extern bool traceflag;
extern bool IsDirty;
extern bool error_happen;
extern long eval_count;
extern long vector_count;
extern int memory_count;
extern enum KEYBOARDCAPTURE KeyboardCapture;
extern int keyboard_value;
extern bool MouseCaptureIsEnabled;
extern int mouse_posx;
extern int mouse_posy;
extern int xoffset;
extern int yoffset;
extern char *keyboard_status;
extern char *keyboard_keydown;
extern char *keyboard_keyup;
extern char *mouse_lbuttondown;
extern char *mouse_lbuttonup;
extern char *mouse_rbuttondown;
extern char *mouse_rbuttonup;
extern char *mouse_mousemove;
extern char edit_editexit[];
extern char mci_callback[];
extern char *timer_callback[];
extern bool EnablePalette;
extern HBITMAP MemoryBitMap;
extern HCURSOR hCursorWait;
extern HCURSOR hCursorArrow;
extern HPALETTE ThePalette;
extern LPLOGPALETTE MyLogPalette;

extern FLONUM the_zoom;
extern Point  g_OldPos;

extern char LibPathName[];
extern char TempPathName[];
extern char TempBmpName[];
extern char TempClipName[];
extern char szHelpFileName[];

extern HPALETTE OldPalette;

extern LOGFONT FontRec;

extern LOGPEN g_LogicalNormalPen;
extern HPEN   g_NormalPen;

extern LOGPEN g_LogicalErasePen;
extern HPEN   g_ErasePen;

extern LOGBRUSH FloodBrush;
extern LOGBRUSH ScreenBrush;

extern RECT FullRect;

extern class TMainFrame *MainWindowx;

extern Color dfld;
extern Color dscn;
extern int BitMapWidth;
extern int BitMapHeight;
extern int WorldWidth;
extern int WorldHeight;
extern int WorldDepth;
extern bool IsOkayToUseCommanderWindow;
extern bool stepflag;
extern bool GiveFocusToEditbox;
extern int BaseUnitsx;
extern int BaseUnitsy;

extern COLORREF scolor;
extern COLORREF fcolor;
extern COLORREF pcolor;
extern bool zoom_flag;
extern long MaxColors;

extern OSVERSIONINFO g_OsVersionInformation;

extern int *TopOfStack;

extern TThreeDSolid ThreeD;

#endif // _MAIN_H_
