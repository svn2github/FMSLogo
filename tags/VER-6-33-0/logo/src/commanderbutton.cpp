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

#include <owl/compat.h>

#include "commanderbutton.h"
#include "cmdwind.h"
#include "debugheap.h"

TCommanderButton::TCommanderButton(
    TMyCommandWindow* parent,
    int               id
    ) : TButton(parent, id),
        Parent(parent)
{
}

TCommanderButton::~TCommanderButton()
{
}


void TCommanderButton::EvKeyDown(UINT, UINT, UINT)
{
    TMessage Msg = __GetTMessage();

    if (Parent->EditBoxWantsKeyEvent(Msg.WParam))
    {
        // we don't want this key press.
        // give it to the commander's edit box.
        Parent->PostKeyDownToEditBox(
            Msg.WParam,
            Msg.LParam);
    }
}

DEFINE_RESPONSE_TABLE1(TCommanderButton, TButton)
    EV_WM_KEYDOWN,
END_RESPONSE_TABLE;
