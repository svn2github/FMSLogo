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

#include <stdio.h>
#include <owl/scroller.h>

#include "main.h"
#include "mainframe.h"
#include "cmdwind.h"
#include "myfilewn.h"
#include "startup.h"
#include "minieditor.h"
#include "init.h"
#include "dynamicbuffer.h"

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

HWND GetParentWindowForDialog()
{
    return GetCommanderWindow();
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

void DockCommanderWindow()
{
    MainWindowx->DockCommanderWindow();
}

int ShowEditorForFile(const char *FileName, NODE *args)
{
    return TMainFrame::PopupEditorForFile(FileName, args);
}


void 
ShowProcedureMiniEditor(
    const char     * ToLine,
    CDynamicBuffer & ReadBuffer
    )
{
    TMiniEditor editor(MainWindowx, ToLine);

    if (IDOK != editor.Execute())
    {
        // The user cancelled the definition
        err_logo(STOP_ERROR, NIL);
    }
    else
    {
        const char * definition = editor.GetText();

        // copy the new definition into the read buffer.
        const char * src = definition;
        while (*src != '\0')
        {
            if (src[0] == '\r' && src[1] == '\n')
            {
                // Skip past the CR in a CRLF sequence because 
                // the caller expects a UNIX EOL sequence.
                src++;
            }

            ReadBuffer.AppendChar(*src);
            src++;
        }

        ReadBuffer.AppendChar('\n');
        ReadBuffer.AppendString(End.GetName());
    }

    if (MainWindowx != NULL)
    {
        // HACK: Reset the window title because the mini-editor's
        // edit box appends a "-" (it thinks it's tied to a file 
        // and I can't figure out how to tell it that it's not.
        MainWindowx->FixWindowTitle();
    }
}


void
TraceOutput(
    const char * FormatString,
    ...
    )
{
    va_list args;

    va_start(args, FormatString);
    vfprintf(stderr, FormatString, args);
    va_end(args);
}
