/*
 *  Copyright (C) 2006 by David Costanzo
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <windows.h>

#include "savebeforeexitdialog.h"

#include "main.h"
#include "logorc.h"
#include "localizedstrings.h"

#include "mainwind.h"

CSaveBeforeExitDialog::CSaveBeforeExitDialog(
    TWindow *Parent
    ) : TDialog(Parent, IDD_SAVEBEFOREEXIT),
        m_ExitStatus(IDCANCEL)
{
    SetCaption(LOCALIZED_UNSAVEDCHANGES);
}

void CSaveBeforeExitDialog::SetupWindow()
{
    TDialog::SetupWindow();

    // Note that the buttons must be first and go from right-to-left
    static const MENUITEM staticText[] = {
        {LOCALIZED_UNSAVEDCHANGES_CANCEL,      IDCANCEL},
        {LOCALIZED_UNSAVEDCHANGES_DONTSAVE,    IDNO},
        {LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT, IDYES},
        {LOCALIZED_UNSAVEDCHANGES_MESSAGE1,    ID_UNSAVEDCHANGES_MESSAGE1},
        {LOCALIZED_UNSAVEDCHANGES_MESSAGE2,    ID_UNSAVEDCHANGES_MESSAGE2},
    };

    // set the text in all of the static controls
    SetTextOnChildWindows(this, staticText, ARRAYSIZE(staticText));

    // 3 because we only care about the buttons.
    SIZE buttonSizes[3] = {{0,0}};

    for (int i = 0; i < ARRAYSIZE(buttonSizes); i++)
    {
        HWND hwnd = GetItemHandle(staticText[i].MenuId);
        if (hwnd != NULL)
        {
            HDC  dc = GetDC(hwnd);
            if (dc != NULL)
            {
                GetTextExtentPoint(
                    dc,
                    staticText[i].MenuText,
                    strlen(staticText[i].MenuText),
                    &buttonSizes[i]);

                ReleaseDC(hwnd, dc);
            }
        }
    }

    const int spacingX = 8;                  // spacing between buttons
    const int spacingY = 8;                  // spacing between bottom and window

    const int paddingX = 2 * BaseUnitsx / 4; // padding inside the button

    // figure out how much width we need to hold the buttons
    int totalWidth = spacingX;
    for (int i = 0; i < ARRAYSIZE(buttonSizes); i++)
    {
        totalWidth += buttonSizes[i].cx + paddingX + spacingX;
    }

    // get the overall dialog box's dimensions
    TRect clientRect;
    GetClientRect(clientRect);

    if (clientRect.Width() < totalWidth)
    {
        // The client area isn't large enough to hold our buttons.
        // We must grow it.
        TRect windowRectangle;
        GetWindowRect(windowRectangle);

        SetWindowPos(
            0,
            0,  // x
            0,  // y
            windowRectangle.Width() - clientRect.Width() + totalWidth, // width
            windowRectangle.Height(),                                  // height
            SWP_NOMOVE | SWP_NOZORDER);

        // re-get the client rectangle
        GetClientRect(clientRect);
    }

    // get cancel button's dimension
    HWND cancelButton = GetItemHandle(IDCANCEL);
    if (cancelButton == NULL)
    {
        // we can't correct the button layout
        return;
    }

    RECT cancelButtonRect;
    BOOL isOk = ::GetClientRect(cancelButton, &cancelButtonRect);
    if (!isOk)
    {
        // we can't correct the button layout
        return;
    }

    const int buttonHeight = cancelButtonRect.bottom;
    const int buttonY      = clientRect.bottom - buttonHeight - spacingY;

    // Now set the size/position of each button by moving
    // from left-to-right.
    int buttonX = clientRect.Width() - spacingX;
    for (int i = 0; i < ARRAYSIZE(buttonSizes); i++)
    {
        // resize the button to fix the text
        HWND hwnd = GetItemHandle(staticText[i].MenuId);
        if (hwnd != NULL)
        {
            buttonX -= buttonSizes[i].cx + spacingX + paddingX;

            ::SetWindowPos(
                hwnd, 
                NULL, 
                buttonX,
                buttonY,
                buttonSizes[i].cx + paddingX,
                buttonHeight,
                SWP_NOZORDER);
        }
    }
}

void CSaveBeforeExitDialog::EvSaveBeforeExit()
{
    m_ExitStatus = IDYES;
    CloseWindow();
}

void CSaveBeforeExitDialog::EvExitWithoutSaving()
{
    m_ExitStatus = IDNO;
    CloseWindow();
}

int CSaveBeforeExitDialog::GetExitCode()
{
    return m_ExitStatus;
}

DEFINE_RESPONSE_TABLE1(CSaveBeforeExitDialog, TDialog)
    EV_BN_CLICKED(IDYES, EvSaveBeforeExit),
    EV_BN_CLICKED(IDNO,  EvExitWithoutSaving),
END_RESPONSE_TABLE;
