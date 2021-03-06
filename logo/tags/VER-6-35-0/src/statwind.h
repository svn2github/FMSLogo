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

#ifndef __STATWIND_H_
#define __STATWIND_H_

#include <owl/dialog.h>

class CStatusWindow : public TDialog
{
public:
    CStatusWindow(TWindow * Parent);

protected:
    void EvDestroy();
    void SetupWindow();

    DECLARE_RESPONSE_TABLE(CStatusWindow);
};

#endif // __STATWIND_H_
