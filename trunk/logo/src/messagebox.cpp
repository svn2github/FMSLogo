/*
 *  Copyright (C) 1995 by the Regents of the University of California
 *  Copyright (C) 1995 by George Mills
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */
#include <windows.h>

#include "messagebox.h"
#include "screenwindow.h"
#include "error.h"

#include "localizedstrings.h"


void 
ShowMessage(
    const char * Title,
    const char * Message
    )
{
    ::MessageBox(GetCommanderWindow(), Message, Title, MB_OK);
}

void
ShowErrorMessage(
    const char * Message
    )
{
    ShowMessage(LOCALIZED_ERROR, Message);
}

// Maps ErrorCode to a string and displays it in a message box
void
ShowErrorMessage(
    ERR_TYPES  ErrorCode
    )
{
    const char * errorMessage = NULL;

    switch (ErrorCode)
    {
    case IMAGE_GIF_LOAD_FAILED:
        errorMessage = LOCALIZED_ERROR_GIFREADFAILED;
        break;

    case IMAGE_GIF_SAVE_FAILED:
        errorMessage = LOCALIZED_ERROR_GIFSAVEFAILED;
        break;

    case IMAGE_BMP_OPEN_FAILED:
        errorMessage = LOCALIZED_COULDNOTOPENBMP;
        break;

    case IMAGE_BMP_CREATE_FAILED:
        errorMessage = LOCALIZED_COULDNOTCREATEBMP;
        break;

    case IMAGE_BMP_WRITE_FAILED:
        errorMessage = LOCALIZED_COULDNOTWRITEBMP;
        break;

    case IMAGE_BMP_INVALID:
        errorMessage = LOCALIZED_NOTVALIDBMP;
        break;
    }

    if (errorMessage != NULL)
    {
        ShowErrorMessage(errorMessage);
    }
}

// Shows a message box and sets the logo error.
// This helper was created because these two operations appear next
// to each other very often, not because coupling the operations is 
// good design.
void 
ShowMessageAndStop(
    const char * Title,
    const char * Message
    )
{
    ShowMessage(Title, Message);
    err_logo(STOP_ERROR, NIL);
}

void
ShowErrorMessageAndStop(
    const char * Message
    )
{
    ShowMessageAndStop(LOCALIZED_ERROR, Message);
}
