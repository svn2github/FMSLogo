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

#include <windows.h>
#include "logodata.h"

HWND GetScreenWindow();
HWND GetMainWindow();
HWND GetEditorWindow();
HWND GetCommanderWindow();
UINT GetScreenHorizontalScrollPosition();
UINT GetScreenVerticalScrollPosition();
void SetScreenScrollPosition(UINT x, UINT y);
bool IsEditorOpen();
void OpenEditorToLocationOfFirstError(const char *FileName);

HDC GetScreenDeviceContext();
HDC GetMemoryDeviceContext();

void OpenStatusWindow();
void CloseStatusWindow();

void AdjustScrollPositionToZoomFactor(FLONUM NewZoomFactor);
void UndockCommanderWindow();
int ShowEditorForFile(const char *FileName, NODE *args);

void TraceOutput(const char * FormatString, ...);

#endif // __SCREENWINDOW_H_
