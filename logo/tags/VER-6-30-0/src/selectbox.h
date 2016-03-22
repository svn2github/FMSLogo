// -*- c++ -*-
/*
 *  Copyright (C) 2007 by David Costanzo
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

//----------------------------------------------------------------------------
// This is a simple dialog box that provides a listbox.
// It is used to implement SELECTBOX.
//----------------------------------------------------------------------------

#ifndef _SELECTBOX_H_
#define _SELECTBOX_H_

#include <owl/listbox.h>
#include <owl/dialog.h>

class CSelectBox : public TDialog 
{
public:
    CSelectBox(TWindow * Parent, const char * Caption, struct NODE * Choices);

    int  GetSelection() const;

protected:
    void SetupWindow();
    void CmOk();
    void OnDoubleClick();

private:
    TListBox      m_ListBox;
    int           m_Selection;
    struct NODE * m_Choices;

    DECLARE_RESPONSE_TABLE(CSelectBox);
};

#endif // __SELECTBOX_H_
