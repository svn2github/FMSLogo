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

#ifndef __SCREENWINDOW_H_
#define __SCREENWINDOW_H_

#ifndef WX_PURE
#include <windows.h>
#endif // WX_PURE

#include "logodata.h"

#ifndef WX_PURE
HWND GetScreenWindow();
HWND GetMainWindow();
HWND GetEditorWindow();
HWND GetCommanderWindow();
HWND GetParentWindowForDialog();
UINT GetScreenHorizontalScrollPosition();
UINT GetScreenVerticalScrollPosition();
void SetScreenScrollPosition(UINT x, UINT y);
#endif

bool IsEditorOpen();

// This is called when FMSLogo attempts to load a file, such
// as one that was passed on the command line, and an error
// is encountered while evaluating the contents.
void OpenEditorToLocationOfFirstError(const char *FileName);

#ifndef WX_PURE
HDC GetScreenDeviceContext();
HDC GetMemoryDeviceContext();
#endif

void OpenStatusWindow();
void CloseStatusWindow();

void AdjustScrollPositionToZoomFactor(FLONUM NewZoomFactor);
void UndockCommanderWindow();
void DockCommanderWindow();
int  ShowEditorForFile(const char *FileName, NODE *args);

// ShowProcedureMiniEditor is called when TO is executed and
// the input is expected to come from stdin (which is typically
// implemented as a modal dialog box.
//
// ToLine     - A text buffer that holds the TO instruction that
//              is being executed.
// ReadBuffer - A buffer to hold a new definition that was read.
//
void
ShowProcedureMiniEditor(
    const char           * ToLine,
    class CDynamicBuffer & ReadBuffer
    );

void TraceOutput(const char * FormatString, ...);

#endif // __SCREENWINDOW_H_
