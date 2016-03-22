// -*- c++ -*-
//
//  Copyright (C) 2006 by David Costanzo
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef _SAVEBEFOREEXITDIALOG_H_
#define _SAVEBEFOREEXITDIALOG_H_

class CSaveBeforeExitDialog : public TDialog
{
public:

    CSaveBeforeExitDialog(TWindow * Parent);
    int GetExitCode();

protected:
    void SetupWindow();

private:

    void EvSaveBeforeExit();
    void EvExitWithoutSaving();

    int m_ExitStatus;

    DECLARE_RESPONSE_TABLE(CSaveBeforeExitDialog);
};

#endif // _SAVEBEFOREEXITDIALOG_H_
