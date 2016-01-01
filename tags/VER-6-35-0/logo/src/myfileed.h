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

#ifndef __MYFILEED_H_
#define __MYFILEED_H_

#include <windows.h>
#include <owl/dialog.h>

struct NODE;

class CSelectProcedureWindow : public TDialog
{
public:

    CSelectProcedureWindow(
        TWindow *    Parent,
        const char * Caption
        );

    void ShowDialog();

protected:
    bool CanClose();
    void SetupWindow();

    virtual void OnChoice(NODE * Procedures) = 0;

    void DoAll();
    void DoDoubleClickProcedure();

    bool m_FileEditAll;              // true if all procedures were selected
    char m_SelectedProcedures[256];  // buffer to hold selected functions

private:
    DECLARE_RESPONSE_TABLE(CSelectProcedureWindow);
};

// shows a "Select Procedures to Edit" dialog
class CEditProcedureWindow : public CSelectProcedureWindow
{
public:
    CEditProcedureWindow(TWindow * Parent);

protected:
    void OnChoice(NODE * Procedures);
};

// shows a "Select Procedures to Erase" dialog
class CEraseProcedureWindow : public CSelectProcedureWindow
{
public:
    CEraseProcedureWindow(TWindow * Parent);

protected:
    void OnChoice(NODE * Procedures);
};

#endif // __MYFILEED_H_
