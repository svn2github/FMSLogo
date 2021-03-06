/*
*
*       Copyright (C) 1995 by the Regents of the University of California
*       Copyright (C) 1995 by George Mills
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

#include "allwind.h"

/* status window members */
TMyStatusWindow::TMyStatusWindow(
   TWindow *    AParent,
   LPCSTR       ATitle
) : TDialog(AParent, ATitle)
   {
   }

TMyStatusWindow::~TMyStatusWindow()
   {
   }

void update_status_turtleposition(void)
   {
   char text[256];

   sprintf(
      text,
      "%1.0f,%1.0f,%1.0f",
      turtle_p[turtle_which].x,
      turtle_p[turtle_which].y,
      turtle_p[turtle_which].z);

   MainWindowx->StatusWindow->SetDlgItemText(ID_TURTLEPOSITION, text);
   }

void update_status_pencolor(void)
   {
   char text[256];

   sprintf(
      text,
      "%d,%d,%d",
      (int) dpenr,
      (int) dpeng,
      (int) dpenb);

   MainWindowx->StatusWindow->SetDlgItemText(ID_PENCOLOR, text);
   }

void update_status_floodcolor(void)
   {
   char text[256];

   sprintf(
      text,
      "%d,%d,%d",
      (int) dfldr,
      (int) dfldg,
      (int) dfldb);

   MainWindowx->StatusWindow->SetDlgItemText(ID_FLOODCOLOR, text);
   }

void update_status_screencolor(void)
   {
   char text[256];

   sprintf(
      text,
      "%d,%d,%d",
      (int) dscnr,
      (int) dscng,
      (int) dscnb);

   MainWindowx->StatusWindow->SetDlgItemText(ID_SCREENCOLOR, text);
   }

void update_status_paletteuse(void)
   {
   char text[256];

   if (EnablePalette)
      {
      sprintf(text, "%d", MyLogPalette->palNumEntries);
      }
   else
      {
      strcpy(text, "N/A");
      }

   MainWindowx->StatusWindow->SetDlgItemText(ID_PALETTEUSE, text);
   }

void update_status_penwidth(void)
   {
   char text[256];
   sprintf(text, "%d", width);
   MainWindowx->StatusWindow->SetDlgItemText(ID_PENWIDTH, text);
   }

void update_status_turtleheading(void)
   {
   char text[256];
   if (current_mode == perspectivemode)
      {
      sprintf(text, "%1.2f", rotation_z());
      }
   else
      {
      sprintf(text, "%1.2f", turtle_heading[turtle_which]);
      }
   MainWindowx->StatusWindow->SetDlgItemText(ID_TURTLEHEADING, text);
   }

void update_status_penstyle(void)
   {
   const char * text;
   if (current_write_mode == XOR_PUT)
      {
      text = "Reverse";
      }
   else
      {
      text = "Normal";
      }

   if (in_erase_mode)
      {
      text = "Erase";
      }
   MainWindowx->StatusWindow->SetDlgItemText(ID_PENSTYLE, text);
   }

void update_status_pencontact(void)
   {
   const char * text;
   if (pen_vis == 0)
      {
      text = "Down";
      }
   else
      {
      text = "Up";
      }

   MainWindowx->StatusWindow->SetDlgItemText(ID_PENCONTACT, text);
   }

void update_status_turtlevisability(void)
   {
   const char * text;

   if (turtle_shown[turtle_which])
      {
      text = "Shown";
      }
   else
      {
      text = "Hidden";
      }

   MainWindowx->StatusWindow->SetDlgItemText(ID_TURTLEVISABILITY, text);
   }

void update_status_turtlepitch(void)
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

void update_status_turtleroll(void)
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

void update_status_turtlewhich(void)
   {
   char text[256];

   if (turtle_which >= TURTLES - TURTLEN)
      {
      sprintf(text, "%ld", (long) (-(turtle_which - (TURTLES - (TURTLEN+1)))));
      }
   else
      {
      sprintf(text, "%ld", (long) turtle_which);
      }

   MainWindowx->StatusWindow->SetDlgItemText(ID_TURTLEWHICH, text);
   }

void update_status_evals(void)
   {
   char text[256];
   sprintf(text, "%ld", eval_count);

   MainWindowx->StatusWindow->SetDlgItemText(ID_EVALS, text);
   }

void update_status_vectors(void)
   {
   char text[256];

   if (ThreeD.iPolyCount)
      {
#ifdef NOASM
      sprintf(text, "%ld/%ld", ThreeD.iPolyCount, ThreeD.iSplitPolyCount);
#else
      sprintf(text, "%ld", ThreeD.iPolyCount);
#endif
      MainWindowx->StatusWindow->SetDlgItemText(ID_THINGS, "Polygons:");
      }
   else
      {
      sprintf(text, "%ld", vector_count);
      MainWindowx->StatusWindow->SetDlgItemText(ID_THINGS, "Vectors:");
      }

   MainWindowx->StatusWindow->SetDlgItemText(ID_VECTORS, text);
   }

void update_status_memory(void)
   {
   char text[256];
   sprintf(text, "%ld Nodes", (long) ((long) memory_count * (long) SEG_SIZE));

   MainWindowx->StatusWindow->SetDlgItemText(ID_MEMORY, text);
   }

