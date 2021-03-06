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

/* File edit Window members */

TMyFileWindow::TMyFileWindow(
   TWindow *AParent,
   LPCSTR   ATitle,
   LPCSTR   AFileName,
   NODE *   args
) : TFileWindow(AParent, ATitle, AFileName),
    hEdtFont(NULL)
   {
   args_list = args;

   AssignMenu("IDM_FILECOMMANDS");
   Attr.AccelTable = "FILECOMMANDS";
   }

TMyFileWindow::~TMyFileWindow()
   {
   if (hEdtFont)
     {
     DeleteObject(hEdtFont);
     }
   }

void TMyFileWindow::CMExit()
   {
   // here on FILE-EXIT in editor
   SendMessage(WM_CLOSE);
   }

void TMyFileWindow::CMSaveAndExit()
   {
   Save();
   CMExit();
   }

void TMyFileWindow::CMSaveToWorkspace()
   {
   if (!bExpert)
      {
      MainWindowx->CommandWindow->MessageBox(
         "This feature is for expert mode only (use Save and Exit)",
         "Save to Workspace",
         MB_OK);
      return;
      }

   Save();

   if (args_list != NULL)
      {
      error_happen = 0;

      EndEdit();

      unlink(TempPathName);
      IsDirty = 1;

      if (error_happen)
         {
         MainWindowx->CommandWindow->MessageBox(
            "The cursor will be positioned just after last successful definition.\n"
               "Check Commander Window for possible error Message.",
            "Your Edit has FAILED to load",
            MB_OK);

         error_happen = 0;
         Editor->SetSelection(0, 0);
         Editor->Insert(" ");
         Editor->DeleteSubText(0, 1);
         int iLine = Editor->GetLineFromPos(LinesLoadedOnEdit);
         Editor->Scroll(0, iLine);
         Editor->SetSelection(LinesLoadedOnEdit, LinesLoadedOnEdit);
         }
      }
   }

void TMyFileWindow::CMHelpEdit()
   {
   do_help("Editor");
   }

void TMyFileWindow::CMHelp()
   {
   MainWindowx->CMHelp();
   //   WinHelp(szHelpFileName,HELP_INDEX,0L);
   }

void TMyFileWindow::CMHelpEditTopic()
   {
   bool didHelp = false;

   // get the keyword selected
   UINT start;
   UINT end;
   Editor->GetSelection(start, end);
   if ((start < end) && (end-start < 80))
      {
      char theText[100];
      Editor->GetSubText(theText, start, end);

      // clean up line before passing to help
      if (strlen(theText) > 0)
         {
         int i = strlen(theText) - 1;
         while ((i > 0) && (theText[i] == ' '))
            {
            theText[i--] = '\0';
            }

         if (strlen(theText) > 0)
            {
            i = 0;
            while ((i < strlen(theText)) && (theText[i] == ' '))
               {
               i++;
               }

            char * ptr = theText + i;

            if (strlen(ptr) > 0)
               {
               if (strchr(ptr,'\r'))
                  {
                  *strchr(ptr,'\r') = '\0';
                  }

               if (strlen(ptr) > 0)
                  {
                  if (strchr(ptr,'\n'))
                     {
                     *strchr(ptr,'\n') = '\0';
                     }

                  if (strlen(ptr) > 0)
                     {
                     do_help(ptr);
                     }
                     didHelp = true;
                  }
               }
            }
         }
      }

   if (!didHelp)
      {
      do_help(NULL);
      }
   }

void TMyFileWindow::CMTest()
   {

   // get the code selected
   UINT start;
   UINT end;
   Editor->GetSelection(start, end);
   char * theText = new char[abs(end - start) + 1];
   Editor->GetSubText(theText, start, end);
   char * ptr = theText;

   // strip comments
   bool more = true;
   while (more)
      {
      char * ptr2 = strchr(ptr, ';');

      if (ptr2 != NULL)
         {
         *ptr2 = ' ';
         while ((*ptr2 != '\n') && (*ptr2 != '\r') && (*ptr2 != '~') && (*ptr2 != '\n'))
            {
            *ptr2++ = ' ';
            }
         }
      else
         {
         more = false;
         }
      }

   // paste continuation
   more = true;
   while (more)
      {
      char * ptr2 = strchr(ptr, '~');

      if (ptr2 != NULL)
         {
         *ptr2 = ' ';
         char * ptr3 = strchr(ptr2, '\n');
         if (ptr3 != NULL)
            {
            *ptr3 = ' ';
            *(ptr3 - 1) = ' ';
            }
         }
      else
         {
         more = false;
         }
      }

   // for each real line left execute it
   more = true;
   while (more)
      {
      char * ptr2 = strchr(ptr, '\n');

      if (ptr2 != NULL)
         {
         *ptr2 = '\0';
         *(ptr2 - 1) = '\0';
         }

      putcombobox(ptr);
      do_execution(ptr);

      if (ptr2 != NULL)
         {
         ptr = ptr2 + 1;
         }
      else
         {
         more = false;
         }
      }

   delete [] theText;
   }


void TMyFileWindow::SetupWindow()
   {
   TFileWindow::SetupWindow();

   LOGFONT lf;
   GetPrivateProfileFont("EditFont", lf);
   hEdtFont = CreateFontIndirect(&lf);
   Editor->SetWindowFont(hEdtFont, true);
   }

void TMyFileWindow::CMEditSetFont()
   {
   // initialize the font chooser to the current font preference
   LOGFONT lf;
   GetPrivateProfileFont("EditFont", lf);

   // clear the struct
   CHOOSEFONT CF;
   memset(&CF, 0, sizeof(CF));
   CF.lStructSize = sizeof(CF);
   CF.hwndOwner = MainWindowx->HWindow;
   CF.Flags = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT;
   CF.nFontType = SCREEN_FONTTYPE;
   CF.lpLogFont = &lf;
   CF.hInstance = 0;

   if (::ChooseFont(&CF))
      {
      // save the new font preference to persistent storage
      SetPrivateProfileFont("EditFont", lf);

      HFONT hFont = CreateFontIndirect(&lf);
      Editor->SetWindowFont(hFont, true);

      if (hEdtFont)
         {
         DeleteObject(hEdtFont);
         }
      hEdtFont = hFont;

      // The next block of code looks like it does nothing,
      // but it forces a redraw, which forces the existing text
      // to adopt the new font.
      // Without this code, you have to change each line of text
      // in order to update it to the new font.
      TRect rect;
      GetWindowRect(rect);
      SetWindowPos(0, rect.Left(), rect.Top(), rect.Width() + 1, rect.Height(), SWP_NOZORDER);
      SetWindowPos(0, rect, SWP_NOZORDER);
      }
   }

int TMyFileWindow::EndEdit()
   {

   int realsave = lendedit();

   // check for error

   for (int i = 0; i < 1; i++)
      {
      if (stopping_flag == THROWING)
         {
         if (compare_node(throw_node, Error, TRUE) == 0)
            {
            err_print();
            error_happen = 1;
            }
         else if (compare_node(throw_node, System, TRUE) == 0) break;
         else if (compare_node(throw_node, Toplevel, TRUE) != 0)
            {
            err_logo(NO_CATCH_TAG, throw_node);
            err_print();
            error_happen = 1;
            }
         stopping_flag = RUN;
         }
      if (stopping_flag == STOP || stopping_flag == OUTPUT)
         {
         print_node(
            stdout,
            make_static_strnode("You must be in a procedure to use OUTPUT or STOP.\n"));
         stopping_flag = RUN;
         }
      }

   return realsave;
   }

void TMyFileWindow::EvDestroy()
   {
   int realsave;
   callthing *callevent;

   // if args_list specified no user callabled editor

   if (args_list != NULL)
      {
      error_happen = 0;

      realsave = EndEdit();

      // if error the ask user to reedit

      if (error_happen)
         {
         if (MainWindowx->CommandWindow->MessageBox(
               "The cursor will be positioned just after last successful definition.\nCheck Commander Window for possible error Message.\n"
                  "\n"
                  "Return to edit?",
               "Your Edit has FAILED to load",
               MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
            {
            if (TMyWindow_MyPopupEdit(TempPathName, args_list))
               {
               MainWindowx->CommandWindow->MessageBox(
                  "Cannot restart editor",
                  "Fatal",
                  MB_OK | MB_ICONQUESTION);
               }
            else
               {
               unlink(TempPathName);
               IsDirty = 1;
               }
            }
         else
            {
            error_happen = 0;
            MainWindowx->CommandWindow->Editbox->SetFocus();
            }
         }
      else
         {
         // check for quit before erasing

         if (realsave)
            {
            lerase(args_list);

            // Since we erased we must load again, but no errors
            lendedit();
            }

         // free up args_list

         args_list = reref(args_list, NIL);

         unlink(TempPathName);
         MainWindowx->CommandWindow->Editbox->SetFocus();
         }
      }

   // else execute callback for user callable editor

   else
      {
      callevent = new callthing;

      callevent->func = edit_editexit;
      callevent->kind = 3;

      calllists.insert(callevent, 3);
      }


   // Get location and size of our window on the screen so we can
   // come back up in the same spot next time we are invoked.

   if (!IsIconic())
      {
      TRect wrect;
      GetWindowRect(wrect);

      // Make a string with our window location and size.
      SetPrivateProfileQuadruple(
         "LOGO",
         "Editor",
         wrect.Left(),
         wrect.Top(),
         wrect.Width(),
         wrect.Height());
      }

   TFileWindow::DefaultProcessing();
   }


bool TMyFileWindow::CanClose()
   {
   // if changed better ask user
   if (Editor->IsModified())
      {
      int rslt = MessageBox(
         "Contents have changed. Save to workspace?",
         "Contents Changed",
         MB_YESNOCANCEL | MB_ICONQUESTION);
      if (rslt == IDYES)
         {
         return Save();
         }
      else
         {
         return rslt != IDCANCEL;
         }
      }

   return true;
   }

DEFINE_RESPONSE_TABLE1(TMyFileWindow, TFileWindow)
  EV_COMMAND(CM_EDALLEXIT, CMExit),
  EV_COMMAND(CM_FILESAVETOWORKSPACE, CMSaveToWorkspace),
  EV_COMMAND(CM_FILESAVEANDEXIT, CMSaveAndExit),
  EV_COMMAND(CM_HELP, CMHelp),
  EV_COMMAND(CM_HELPEDIT, CMHelpEdit),
  EV_COMMAND(CM_HELPEDIT_TOPIC, CMHelpEditTopic),
  EV_COMMAND(CM_TEST, CMTest),
  EV_COMMAND(CM_EDITSETFONT, CMEditSetFont),
  EV_WM_DESTROY,
END_RESPONSE_TABLE;

