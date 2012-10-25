/*
 *  Copyright (C) 1995 by the Regents of the University of California
 *  Copyright (C) 1995 by George Mills
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
#include <stdio.h>

#include "status.h"
#include "statwind.h"
#include "main.h"
#include "mainframe.h"
#include "logorc.h"
#include "graphwin.h"
#include "startup.h"
#include "eval.h"
#include "mem.h"
#include "graphics.h"
#include "localizedstrings.h"
#include "debugheap.h"

bool status_flag = false;   // Flag to signal status box is popped up

static
void 
update_status_color_helper(
    int           ChildDialogId,
    const Color & TheColor
    )
{
    if (status_flag)
    {
        char colortext[256];

        sprintf(
            colortext,
            "%d,%d,%d",
            TheColor.red,
            TheColor.green,
            TheColor.blue);

        MainWindowx->StatusWindow->SetDlgItemText(ChildDialogId, colortext);
    }
}

void update_status_turtleposition(void)
{
    if (status_flag)
    {
        char text[256];

        sprintf(
            text,
            "%1.0f,%1.0f,%1.0f",
            g_SelectedTurtle->Position.x,
            g_SelectedTurtle->Position.y,
            g_SelectedTurtle->Position.z);

        MainWindowx->StatusWindow->SetDlgItemText(ID_TURTLEPOSITION, text);
    }
}


void update_status_pencolor(void)
{
    update_status_color_helper(ID_PENCOLOR, GetPenStateForSelectedTurtle().Color);
}

void update_status_floodcolor(void)
{
    update_status_color_helper(ID_FLOODCOLOR, dfld);
}

void update_status_screencolor(void)
{
    update_status_color_helper(ID_SCREENCOLOR, dscn);
}

void update_status_paletteuse(void)
{
    if (status_flag)
    {
        char text[256];

        if (EnablePalette)
        {
            sprintf(text, "%d", MyLogPalette->palNumEntries);
        }
        else
        {
            strcpy(text, LOCALIZED_STATUS_NOT_APPLICABLE);
        }

        MainWindowx->StatusWindow->SetDlgItemText(ID_PALETTEUSE, text);
    }
}

void update_status_penwidth(void)
{
    if (status_flag)
    {
        char text[256];
        sprintf(text, "%d", GetPenStateForSelectedTurtle().Width);
        MainWindowx->StatusWindow->SetDlgItemText(ID_PENWIDTH, text);
    }
}

void update_status_turtleheading(void)
{
    if (status_flag)
    {
        char text[256];
        if (current_mode == perspectivemode)
        {
            sprintf(text, "%1.2f", rotation_z());
        }
        else
        {
            sprintf(text, "%1.2f", g_SelectedTurtle->Heading);
        }
        MainWindowx->StatusWindow->SetDlgItemText(ID_TURTLEHEADING, text);
    }
}

void update_status_penstyle(void)
{
    if (status_flag)
    {
        // TODO: merge with get_node_pen_mode()
        const char * text;
        if (GetPenStateForSelectedTurtle().Mode == XOR_PUT)
        {
            text = LOCALIZED_STATUS_PENREVERSE;
        }
        else
        {
            text = LOCALIZED_STATUS_PENNORMAL;
        }

        if (GetPenStateForSelectedTurtle().IsErasing)
        {
            text = LOCALIZED_STATUS_PENERASE;
        }

        MainWindowx->StatusWindow->SetDlgItemText(ID_PENSTYLE, text);
    }
}

void update_status_pencontact(void)
{
    if (status_flag)
    {
        const char * text;
        if (g_SelectedTurtle->IsPenUp)
        {
            text = LOCALIZED_STATUS_PENUP;
        }
        else
        {
            text = LOCALIZED_STATUS_PENDOWN;
        }

        MainWindowx->StatusWindow->SetDlgItemText(ID_PENCONTACT, text);
    }
}

void update_status_turtlevisability(void)
{
    if (status_flag)
    {
        const char * text;

        if (g_SelectedTurtle->IsShown)
        {
            text = LOCALIZED_STATUS_PENSHOWN;
        }
        else
        {
            text = LOCALIZED_STATUS_PENHIDDEN;
        }

        MainWindowx->StatusWindow->SetDlgItemText(ID_TURTLEVISABILITY, text);
    }
}

void update_status_turtlepitch(void)
{
    if (status_flag)
    {
        char text[256];

        if (current_mode == perspectivemode)
        {
            sprintf(text, "%1.2f", rotation_x());
        }
        else
        {
            sprintf(text, "%1.2f", 0.0);
        }

        MainWindowx->StatusWindow->SetDlgItemText(ID_TURTLEPITCH, text);
    }
}

void update_status_turtleroll(void)
{
    if (status_flag)
    {
        char text[256];

        if (current_mode == perspectivemode)
        {
            sprintf(text, "%1.2f", rotation_y());
        }
        else
        {
            sprintf(text, "%1.2f", 0.0);
        }

        MainWindowx->StatusWindow->SetDlgItemText(ID_TURTLEROLL, text);
    }
}

void update_status_turtlewhich(void)
{
    if (status_flag)
    {
        char text[256];

        sprintf(text, "%d", GetSelectedTurtleIndex());

        MainWindowx->StatusWindow->SetDlgItemText(ID_TURTLEWHICH, text);
    }
}

void update_status_evals(void)
{
    if (status_flag)
    {
        char text[256];
        sprintf(text, "%ld", eval_count);

        MainWindowx->StatusWindow->SetDlgItemText(ID_EVALS, text);
    }
}

void update_status_vectors(void)
{
    if (status_flag)
    {
        char text[256];

        if (ThreeD.m_iPolyCount)
        {
#ifdef NOASM
            sprintf(text, "%ld/%ld", ThreeD.m_iPolyCount, ThreeD.m_iSplitPolyCount);
#else
            sprintf(text, "%ld", ThreeD.m_iPolyCount);
#endif
            MainWindowx->StatusWindow->SetDlgItemText(
                ID_THINGS, 
                LOCALIZED_STATUS_POLYGONS":");
        }
        else
        {
            sprintf(text, "%ld", vector_count);
            MainWindowx->StatusWindow->SetDlgItemText(
                ID_THINGS, 
                LOCALIZED_STATUS_VECTORS":");
        }

        MainWindowx->StatusWindow->SetDlgItemText(ID_VECTORS, text);
    }
}

void update_status_memory(void)
{
    if (status_flag)
    {
        char text[256];
        sprintf(text, "%ld "LOCALIZED_STATUS_NODES, memory_count * SEG_SIZE);

        MainWindowx->StatusWindow->SetDlgItemText(ID_MEMORY, text);
    }
}
