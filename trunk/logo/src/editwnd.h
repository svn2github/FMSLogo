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

#ifndef __EDITWND_H
#define __EDITWND_H

#include <owl\window.h>
#include <owl\richedit.h>

class TRichEditWithPopup : public TRichEdit
{
public:
    TRichEditWithPopup(TWindow* parent, int id);
    ~TRichEditWithPopup();

    void  CmHelpEditTopic(); // CM_HELPEDIT_TOPIC

    // CM_EDITSELECTALL
    void CmSelectAll();       
    void CmSelectAllEnable(TCommandEnabler& commandHandler);

    void EvRButtonUp(UINT, TPoint &);
    void CmPasteAsText();         // CM_PASTE
    void CmFindMatchingParen();   // CM_FINDMATCHINGPAREN 
    void CmSelectMatchingParen(); // CM_SELECTMATCHINGPAREN 

    int GetCaretPosition();
    void SetCaretPosition(uint32 CaretCharIndex);
    void UpdateCaretPosition(uint32 CaretCharIndex);
    int SearchForwardForMatchingParen(int CaretPosition, char ParenToMatch);
    int SearchBackwardForMatchingParen(int CaretPosition, char ParenToMatch);

    TPopupMenu PopupMenu;

    DECLARE_RESPONSE_TABLE(TRichEditWithPopup);
};

#endif //__EDITWND_H
