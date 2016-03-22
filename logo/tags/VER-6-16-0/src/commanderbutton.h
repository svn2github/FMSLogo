/*
*
*       Copyright (C) 2005 by David Costanzo
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

//----------------------------------------------------------------------------
// This is a subclass of TButton that sends all button clicks
// to the commander window's edit control.
//----------------------------------------------------------------------------

#ifndef __COMMANDERBUTTON_H
#define __COMMANDERBUTTON_H

#include "owl\button.h"

class TCommanderButton : public TButton
{
public:
   TCommanderButton(
      class TMyCommandWindow* parent,
      int id
      );

   ~TCommanderButton();

protected:

   void EvKeyDown(UINT, UINT, UINT);

private:
   class TMyCommandWindow* Parent;


private:
   // hide compiler generated routines
   TCommanderButton(const TCommanderButton &);
   operator=(const TCommanderButton &);

   DECLARE_RESPONSE_TABLE(TCommanderButton);
};

#endif // __COMMANDERBUTTON_H


