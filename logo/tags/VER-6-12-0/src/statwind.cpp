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

bool status_flag = false;   // Flag to signal status box is popped up


CStatusWindow::CStatusWindow(
   TWindow *    Parent
   ) : TDialog(Parent, IDD_STATUS)
   {
   SetCaption(LOCALIZED_STATUS);
   }

void CStatusWindow::SetupWindow()
   {
   TDialog::SetupWindow();

   // flag so that updates are sent
   status_flag = true;

   // update button
   MainWindowx->CommandWindow->UpdateStatusButtonState();

   // build default coords
   int x = 0;
   int y = 0;
   int w = 0;
   int h = 0;

   // Get last location and size of command window from configuration settings.
   GetConfigurationQuadruple("Status", &x, &y, &w, &h); 
   checkwindow(&x, &y, &w, &h);

   // now set position
   SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE);

   // set the static text fields
   static const MENUITEM text[] = {
      {LOCALIZED_STATUS_CONTACT,     ID_STATUS_CONTACT},
      {LOCALIZED_STATUS_PENCOLOR,    ID_STATUS_PENCOLOR},
      {LOCALIZED_STATUS_FLOODCOLOR,  ID_STATUS_FLOODCOLOR},
      {LOCALIZED_STATUS_SCREENCOLOR, ID_STATUS_SCREENCOLOR},
      {LOCALIZED_STATUS_PALETTE,     ID_STATUS_PALETTE},
      {LOCALIZED_STATUS_WIDTH,       ID_STATUS_WIDTH},
      {LOCALIZED_STATUS_POSITION,    ID_STATUS_POSITION},
      {LOCALIZED_STATUS_WHICH,       ID_STATUS_WHICH},
      {LOCALIZED_STATUS_VISIBILITY,  ID_STATUS_VISIBILITY},
      {LOCALIZED_STATUS_STYLE,       ID_STATUS_STYLE},
      {LOCALIZED_STATUS_HEADING,     ID_STATUS_HEADING},
      {LOCALIZED_STATUS_PITCH,       ID_STATUS_PITCH},
      {LOCALIZED_STATUS_ROLL,        ID_STATUS_ROLL},
      {LOCALIZED_STATUS_PEN,         ID_STATUS_PEN},
      {LOCALIZED_STATUS_ORIENTATION, ID_STATUS_ORIENTATION},
      {LOCALIZED_STATUS_TURTLE,      ID_STATUS_TURTLE},
      {LOCALIZED_STATUS_COLOR,       ID_STATUS_COLOR},
      {LOCALIZED_STATUS_KERNEL,      ID_STATUS_KERNEL},
      {LOCALIZED_STATUS_CALLS,       ID_STATUS_CALLS},
      {LOCALIZED_STATUS_PEAKMEMORY,  ID_STATUS_PEAKMEMORY},
   };

   SetTextOnChildWindows(this, text, ARRAYSIZE(text));

   // update all fields
   update_status_evals();
   update_status_floodcolor();
   update_status_memory();
   update_status_paletteuse();
   update_status_pencolor();
   update_status_pencontact();
   update_status_penstyle();
   update_status_penwidth();
   update_status_screencolor();
   update_status_turtleheading();
   update_status_turtlepitch();
   update_status_turtleposition();
   update_status_turtleroll();
   update_status_turtlevisability();
   update_status_turtlewhich();
   update_status_vectors();
   }

void CStatusWindow::EvDestroy()
   {
   // we are processing the close event before
   // the window has been closed.
   status_flag = false;

   // Get location and size of our window on the screen so we can
   // come back up in the same spot next time we are invoked.
   TRect wrect;
   GetWindowRect(wrect);

   // save the current location
   SetConfigurationQuadruple(
      "Status",
      wrect.Left(),
      wrect.Top(),
      wrect.Width(),
      wrect.Height());

   MainWindowx->CommandWindow->UpdateStatusButtonState();

   // the window will delete itself
   MainWindowx->StatusWindow = NULL;
   TDialog::EvDestroy();
   }

DEFINE_RESPONSE_TABLE1(CStatusWindow, TDialog)
  EV_WM_DESTROY,
END_RESPONSE_TABLE;

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
         g_Turtles[turtle_which].Position.x,
         g_Turtles[turtle_which].Position.y,
         g_Turtles[turtle_which].Position.z);

      MainWindowx->StatusWindow->SetDlgItemText(ID_TURTLEPOSITION, text);
      }
   }


void update_status_pencolor(void)
   {
   update_status_color_helper(ID_PENCOLOR, dpen);
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
         strcpy(text, "N/A");
         }

      MainWindowx->StatusWindow->SetDlgItemText(ID_PALETTEUSE, text);
      }
   }

void update_status_penwidth(void)
   {
   if (status_flag)
      {
      char text[256];
      sprintf(text, "%d", g_PenWidth);
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
         sprintf(text, "%1.2f", g_Turtles[turtle_which].Heading);
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
      if (current_write_mode == XOR_PUT)
         {
         text = LOCALIZED_STATUS_PENREVERSE;
         }
      else
         {
         text = LOCALIZED_STATUS_PENNORMAL;
         }

      if (in_erase_mode)
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
      if (g_Turtles[turtle_which].IsPenUp)
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

      if (g_Turtles[turtle_which].IsShown)
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

      if (ThreeD.iPolyCount)
         {
#ifdef NOASM
         sprintf(text, "%ld/%ld", ThreeD.iPolyCount, ThreeD.iSplitPolyCount);
#else
         sprintf(text, "%ld", ThreeD.iPolyCount);
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
