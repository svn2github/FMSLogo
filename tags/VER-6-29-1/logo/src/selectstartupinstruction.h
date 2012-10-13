// -*- c++ -*-
// Copyright (C) 2009 by David Costanzo
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

#ifndef __SELECTSTARTUPINSTRUCTION_H_
#define __SELECTSTARTUPINSTRUCTION_H_

#include <owl\dialog.h>
#include <owl\listbox.h>
#include "logocore.h"

class CSelectStartupInstructionDialog : public TDialog
{
public:
    enum EXPLAINTEXT
    {
        EXPLAINTEXT_None,
        EXPLAINTEXT_StartupNotDefined,
        EXPLAINTEXT_StartupEmpty,
        EXPLAINTEXT_StartupNotList,
    };

    CSelectStartupInstructionDialog(
        TWindow *    Parent,
        EXPLAINTEXT  ExplainText
        );

    void ShowDialog();

    const char * GetSelectedInstruction() const;

protected:
    bool CanClose();
    void SetupWindow();

    void DoListBox(UINT);
    void DoEditControl(UINT);
    void CmOk(TCommandEnabler& commandHandler);

    char m_SelectedInstruction[MAX_BUFFER_SIZE]; // buffer to hold selected instruction list

private:
    const char * m_ExplainText;

    DECLARE_RESPONSE_TABLE(CSelectStartupInstructionDialog);
};

#endif //__SELECTSTARTUPINSTRUCTION_H_
