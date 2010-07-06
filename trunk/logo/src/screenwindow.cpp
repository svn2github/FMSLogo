// Copyright (C) 2005 by David Costanzo
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

//
// This file implements an adapter between the logo core engine
// and the OWL implementation of the screen window.
//

#include "screenwindow.h"

#include "main.h"
#include "mainframe.h"
#include "cmdwind.h"
#include "myfilewn.h"
#include "startup.h"
#include <owl/scroller.h>

HWND GetScreenWindow()
{
    return MainWindowx->ScreenWindow->HWindow;
}

HWND GetMainWindow()
{
    return MainWindowx->HWindow;
}

HWND GetCommanderWindow()
{
    return MainWindowx->CommandWindow->HWindow;
}

HWND GetEditorWindow()
{
    TMyFileWindow * editor = MainWindowx->GetEditor();
    if (editor == NULL)
    {
        return NULL;
    }

    return editor->HWindow;
}

UINT GetScreenHorizontalScrollPosition()
{
    return MainWindowx->ScreenWindow->Scroller->XPos;
}

void SetScreenScrollPosition(UINT x, UINT y)
{
    MainWindowx->ScreenWindow->Scroller->ScrollTo(x, y);
}

UINT GetScreenVerticalScrollPosition()
{
    return MainWindowx->ScreenWindow->Scroller->YPos;
}

bool IsEditorOpen()
{
    return MainWindowx != NULL && MainWindowx->IsEditorOpen();
}

void OpenEditorToLocationOfFirstError(const char *FileName)
{
    MainWindowx->MyPopupEditToError(FileName);
}


HDC GetScreenDeviceContext()
{
    return MainWindowx->ScreenWindow->GetScreenDeviceContext();
}

HDC GetMemoryDeviceContext()
{
    return MainWindowx->ScreenWindow->GetMemoryDeviceContext();
}

void OpenStatusWindow()
{
    MainWindowx->MyPopupStatus();
}

void CloseStatusWindow()
{
    MainWindowx->MyPopupStatusKill();
}

void AdjustScrollPositionToZoomFactor(FLONUM NewZoomFactor)
{
    MainWindowx->ScreenWindow->AdjustScrollPositionToZoomFactor(NewZoomFactor);
}

void UndockCommanderWindow()
{
    MainWindowx->UndockCommanderWindow();
}

int ShowEditorForFile(const char *FileName, NODE *args)
{
    return TMainFrame::PopupEditorForFile(TempPathName, args);
}
