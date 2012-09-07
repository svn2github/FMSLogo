/*
 *  Copyright (C) 1995 by the Regents of the University of California
 *  Copyright (C) 1995 by George Mills
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

#include "statwind.h"
#include "status.h"
#include "logorc.h"
#include "main.h"
#include "mainframe.h"
#include "mainwind.h"
#include "cmdwind.h"
#include "utils.h"
#include "localizedstrings.h"

CStatusWindow::CStatusWindow(
    TWindow *    Parent
    ) : TDialog(Parent, IDD_STATUS)
{
    SetCaption(LOCALIZED_STATUS);
}

void CStatusWindow::SetupWindow()
{
    TDialog::SetupWindow();

    // flag so that updates are sent
    status_flag = true;

    // update button
    MainWindowx->CommandWindow->UpdateStatusButtonState();

    // build default coords
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    // Get last location and size of command window from configuration settings.
    GetConfigurationQuadruple("Status", &x, &y, &w, &h); 
    checkwindow(&x, &y, &w, &h);

    // now set position
    SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE);

    // set the static text fields
    static const MENUITEM text[] = {
        {LOCALIZED_STATUS_CONTACT,     ID_STATUS_CONTACT},
        {LOCALIZED_STATUS_PENCOLOR,    ID_STATUS_PENCOLOR},
        {LOCALIZED_STATUS_FLOODCOLOR,  ID_STATUS_FLOODCOLOR},
        {LOCALIZED_STATUS_SCREENCOLOR, ID_STATUS_SCREENCOLOR},
        {LOCALIZED_STATUS_PALETTE,     ID_STATUS_PALETTE},
        {LOCALIZED_STATUS_WIDTH,       ID_STATUS_WIDTH},
        {LOCALIZED_STATUS_POSITION,    ID_STATUS_POSITION},
        {LOCALIZED_STATUS_WHICH,       ID_STATUS_WHICH},
        {LOCALIZED_STATUS_VISIBILITY,  ID_STATUS_VISIBILITY},
        {LOCALIZED_STATUS_STYLE,       ID_STATUS_STYLE},
        {LOCALIZED_STATUS_HEADING,     ID_STATUS_HEADING},
        {LOCALIZED_STATUS_PITCH,       ID_STATUS_PITCH},
        {LOCALIZED_STATUS_ROLL,        ID_STATUS_ROLL},
        {LOCALIZED_STATUS_PEN,         ID_STATUS_PEN},
        {LOCALIZED_STATUS_ORIENTATION, ID_STATUS_ORIENTATION},
        {LOCALIZED_STATUS_TURTLE,      ID_STATUS_TURTLE},
        {LOCALIZED_STATUS_COLOR,       ID_STATUS_COLOR},
        {LOCALIZED_STATUS_KERNEL,      ID_STATUS_KERNEL},
        {LOCALIZED_STATUS_CALLS,       ID_STATUS_CALLS},
        {LOCALIZED_STATUS_PEAKMEMORY,  ID_STATUS_PEAKMEMORY},
    };

    SetTextOnChildWindows(this, text, ARRAYSIZE(text));

    // update all fields
    update_status_evals();
    update_status_floodcolor();
    update_status_memory();
    update_status_paletteuse();
    update_status_pencolor();
    update_status_pencontact();
    update_status_penstyle();
    update_status_penwidth();
    update_status_screencolor();
    update_status_turtleheading();
    update_status_turtlepitch();
    update_status_turtleposition();
    update_status_turtleroll();
    update_status_turtlevisability();
    update_status_turtlewhich();
    update_status_vectors();
}

void CStatusWindow::EvDestroy()
{
    // we are processing the close event before
    // the window has been closed.
    status_flag = false;

    // Get location and size of our window on the screen so we can
    // come back up in the same spot next time we are invoked.
    TRect wrect;
    GetWindowRect(wrect);

    // save the current location
    SetConfigurationQuadruple(
        "Status",
        wrect.Left(),
        wrect.Top(),
        wrect.Width(),
        wrect.Height());

    MainWindowx->CommandWindow->UpdateStatusButtonState();

    // the window will delete itself
    MainWindowx->StatusWindow = NULL;
    TDialog::EvDestroy();
}

DEFINE_RESPONSE_TABLE1(CStatusWindow, TDialog)
    EV_WM_DESTROY,
END_RESPONSE_TABLE;

