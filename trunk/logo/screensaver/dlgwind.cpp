/*
*
*       Copyright (C) 1995 by the Regents of the University of California
*       Copyright (C) 1995 by George Mills
*
*      This program is free software; you can redistribute it and/or modify
*      it under the terms of the GNU General Public License as published by
*      the Free Software Foundation; either version 2 of the License, or
*      (at your option) any later version.
*
*      This program is distributed in the hope that it will be useful,
*      but WITHOUT ANY WARRANTY; without even the implied warranty of
*      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*      GNU General Public License for more details.
*
*      You should have received a copy of the GNU General Public License
*      along with this program; if not, write to the Free Software
*      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
*/

#include "dlgwind.h"

#include "localizedstrings.h"
#include "init.h"
#include "argumentutils.h"
#include "graphwin.h"
#include "error.h"
#include "eval.h"
#include "logocore.h"
#include "lists.h"
#include "screenwindow.h"
#include "stringprintednode.h"
#include "print.h"
#include "debugheap.h"

NODE *lmessagebox(NODE *args)
{
    CStringPrintedNode banner(car(args));
    CStringPrintedNode body(car(cdr(args)), CStringPrintedNode::WithPrintLimits);

    if (NOT_THROWING)
    {
        if (::MessageBox(
                GetParentWindowForDialog(),
                body, 
                banner, 
                MB_OKCANCEL) == IDCANCEL)
        {
            err_logo(STOP_ERROR, NIL);
        }
    }

    return Unbound;
}


NODE *lyesnobox(NODE *args)
{
    CStringPrintedNode banner(car(args));
    CStringPrintedNode body(car(cdr(args)), CStringPrintedNode::WithPrintLimits);

    if (NOT_THROWING)
    {
        int status = ::MessageBox(
            GetParentWindowForDialog(),
            body.GetString(),
            banner.GetString(),
            MB_YESNOCANCEL | MB_ICONQUESTION);

        switch (status)
        {
        case IDYES:
            return Truex.GetNode();

        case IDNO:
            return Falsex.GetNode();

        case IDCANCEL:
            err_logo(STOP_ERROR, NIL);
            return Falsex.GetNode();
        }
    }

    return Unbound;
}

NODE *ldialogfileopen(NODE *args)
{
    char filename[MAX_PATH];
    PrintNodeToString(car(args), filename, ARRAYSIZE(filename));

    OPENFILENAME openFileName;
    ZeroMemory(&openFileName, sizeof openFileName);
    openFileName.lStructSize       = sizeof openFileName;
    openFileName.hwndOwner         = GetParentWindowForDialog();
    openFileName.hInstance         = NULL;
    openFileName.lpstrFilter       = LOCALIZED_FILEFILTER_ALLFILES;
    openFileName.lpstrCustomFilter = NULL;
    openFileName.nMaxCustFilter    = 0;
    openFileName.nFilterIndex      = 0;
    openFileName.lpstrFile         = filename;
    openFileName.nMaxFile          = ARRAYSIZE(filename);
    openFileName.lpstrFileTitle    = NULL;
    openFileName.nMaxFileTitle     = 0;
    openFileName.lpstrInitialDir   = NULL;
    openFileName.lpstrTitle        = NULL;
    openFileName.Flags             = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER;
    openFileName.nFileOffset       = 0;
    openFileName.nFileExtension    = 0;
    openFileName.lpstrDefExt       = NULL;
    openFileName.lCustData         = 0;
    openFileName.lpfnHook          = NULL;
    openFileName.lpTemplateName    = NULL;

    // if user found a file then try to load it
    if (GetOpenFileName(&openFileName))
    {
        return make_strnode(filename);
    }
    else
    {
        return NIL;
    }
}

NODE *ldialogfilesave(NODE *args)
{
    char filename[MAX_PATH];
    PrintNodeToString(car(args), filename, ARRAYSIZE(filename));

    OPENFILENAME openFileName;
    ZeroMemory(&openFileName, sizeof openFileName);
    openFileName.lStructSize       = sizeof openFileName;
    openFileName.hwndOwner         = GetParentWindowForDialog();
    openFileName.hInstance         = NULL;
    openFileName.lpstrFilter       = LOCALIZED_FILEFILTER_ALLFILES;
    openFileName.lpstrCustomFilter = NULL;
    openFileName.nMaxCustFilter    = 0;
    openFileName.nFilterIndex      = 0;
    openFileName.lpstrFile         = filename;
    openFileName.nMaxFile          = ARRAYSIZE(filename);
    openFileName.lpstrFileTitle    = NULL;
    openFileName.nMaxFileTitle     = 0;
    openFileName.lpstrInitialDir   = NULL;
    openFileName.lpstrTitle        = NULL;
    openFileName.Flags             = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER;
    openFileName.nFileOffset       = 0;
    openFileName.nFileExtension    = 0;
    openFileName.lpstrDefExt       = NULL;
    openFileName.lCustData         = 0;
    openFileName.lpfnHook          = NULL;
    openFileName.lpTemplateName    = NULL;

    // if user found a file then try to load it
    if (GetSaveFileName(&openFileName))
    {
        return make_strnode(filename, strlen(filename), STRING, strnzcpy);
    }
    else
    {
        return NIL;
    }
}

void uninitialize_windows()
{
}
