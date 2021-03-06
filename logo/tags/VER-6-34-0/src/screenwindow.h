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

#ifdef WX_PURE
typedef unsigned int UINT;
#else
#include <windows.h>
#endif // WX_PURE

#include "logodata.h"

#ifndef WX_PURE
HWND GetScreenWindow();
HWND GetMainWindow();
HWND GetEditorWindow();
HWND GetCommanderWindow();
HWND GetParentWindowForDialog();
#endif

UINT GetScreenHorizontalScrollPosition();
UINT GetScreenVerticalScrollPosition();
void SetScreenScrollPosition(UINT x, UINT y);

bool IsEditorOpen();

// This is called when FMSLogo attempts to load a file, such
// as one that was passed on the command line, and an error
// is encountered while evaluating the contents.
void OpenEditorToLocationOfFirstError(const char *FileName);

#ifndef WX_PURE
// Returns the device context for the main drawing surface (the screen).
HDC GetScreenDeviceContext();

// Returns the device context for MemoryBitMap
HDC GetMemoryDeviceContext();

// Returns a device context of a bitmap that is distinct from MemoryBitMap,
// but has the same characteristics (bit depth, width, height, etc.)
HDC GetBackBufferDeviceContext();

// Locates the window for which the message was generated and attempts to
// translate it as a keyboard accelerator (keyboard shortcut) using that
// window's accelerator table.
//
// Returns true if the message was translated (in which case it does
// not need to be handled further).  Returns false, otherwise (in which
// case it should be translated and dispatched).
//
// Note that this routine exists because the Logo engine is executed from
// the context of the message pump and we still want to be able to process
// user input while it's running.
bool TranslateKeyboardShortcut(MSG & Message);

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
