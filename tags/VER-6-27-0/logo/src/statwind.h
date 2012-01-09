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

#ifdef FMSLOGO_SCREENSAVER

// stub out status updates
#define update_status_evals()
#define update_status_floodcolor()
#define update_status_memory()
#define update_status_paletteuse()
#define update_status_pencolor()
#define update_status_pencontact()
#define update_status_penstyle()
#define update_status_penwidth()
#define update_status_screencolor()
#define update_status_turtleheading()
#define update_status_turtlepitch()
#define update_status_turtleposition()
#define update_status_turtleroll()
#define update_status_turtlevisability()
#define update_status_turtlewhich()
#define update_status_vectors()
extern bool status_flag;

#else

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


extern void update_status_evals(void);
extern void update_status_floodcolor(void);
extern void update_status_memory(void);
extern void update_status_paletteuse(void);
extern void update_status_pencolor(void);
extern void update_status_pencontact(void);
extern void update_status_penstyle(void);
extern void update_status_penwidth(void);
extern void update_status_screencolor(void);
extern void update_status_turtleheading(void);
extern void update_status_turtlepitch(void);
extern void update_status_turtleposition(void);
extern void update_status_turtleroll(void);
extern void update_status_turtlevisability(void);
extern void update_status_turtlewhich(void);
extern void update_status_vectors(void);

// global variables
extern bool status_flag;

#endif // FMSLOGO_SCREENSAVER

#endif // __STATWIND_H_
