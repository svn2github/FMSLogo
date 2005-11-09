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
) : TEditWindow(AParent, ATitle),
    hEdtFont(NULL),
    args_list(args),
    FileName(NULL)
   {
   AssignMenu("IDM_FILECOMMANDS");
   Attr.AccelTable = "IDM_FILECOMMANDS";
   FileName = AFileName ? strnewdup(AFileName) : 0;
   }

TMyFileWindow::~TMyFileWindow()
   {
   if (hEdtFont)
      {
      DeleteObject(hEdtFont);
      }
      
   if (HWindow)
      {
      HMENU oldMenu = GetMenu();
      if (oldMenu)
         {
         ::DestroyMenu(oldMenu);
         }
      }

   delete FileName;
   }

//
// saves the contents of the TEdit child control into the file currently
// being editted
//
// returns true if the file was saved or Editor->IsModified returns false
// (contents already saved)
//
bool TMyFileWindow::Save()
   {
   if (Editor->IsModified())
      {
      if (FileName != NULL)
         {
         return Write();
         }
      }
   else
      {
      return true; //editor's contents haven't been changed
      }

   return false;
   }

//
// reads the contents of a previously-specified file into the TEdit
// child control
//
bool TMyFileWindow::Read(const char *fileName)
   {
   Editor->LimitText(0x7FFFFFF);

   if (!fileName)
      {
      if (FileName)
         {
         fileName = FileName;
         }
      else
         {
         return false;
         }
      }

   bool success = false;
   FILE* file = fopen(fileName, "rb");

   if (file != NULL)
      {
      // seek to the end
      fseek(file, 0, SEEK_END);

      long charsToRead = ftell(file);

      rewind(file);

      if (charsToRead < INT_MAX && charsToRead > 0)
         {
         Editor->Clear();
         //
         // Lock and resize Editor's buffer to the size of the file
         // Then if OK, read the file into editBuffer
         //
         char *editBuffer = new char[charsToRead + 1];
         if (editBuffer)
            {
            if (fread(editBuffer, sizeof(char), charsToRead, file) == charsToRead)
               {
               editBuffer[charsToRead] = '\0';
               success = true;
               Editor->SetWindowText(editBuffer);
               Editor->ClearModify();
               }
            delete [] editBuffer;
            }
         }
      fclose(file);
      }

   if (!success)
      {
      char err[MAXPATH + 33];

      wsprintf(err, "Unable to read file \"%s\" from disk", FileName);
      MessageBox(err, GetModule()->GetName(), MB_ICONEXCLAMATION | MB_OK);
      }
   return success;
   }

//
// writes the contents of the TEdit child control to a previously-specified
// file
//
bool TMyFileWindow::Write(const char * fileName)
   {
   if (!fileName)
      {
      if (FileName)
         {
         fileName = FileName;
         }
      else
         {
         return false;
         }
      }

   FILE* file = fopen(fileName, "w");
   if (file == NULL) 
      {
      char msg[MAXPATH + 33];

      wsprintf(msg, "Unable to write file \"%s\" to disk", FileName);
      MessageBox(msg, GetModule()->GetName(), MB_ICONEXCLAMATION | MB_OK);
      return false;
      }

   bool success = false;

   int    windowTextLength = Editor->GetWindowTextLength();
   size_t editBufferLength = windowTextLength + 2; // "\r\n"
   char *editBuffer = new char [editBufferLength];
   if (editBuffer != NULL)
      {
      memset(editBuffer, 0, editBufferLength);

      Editor->GetWindowText(editBuffer, windowTextLength);
      if (windowTextLength != 0 && editBuffer[windowTextLength - 1] != '\n')
         {
         editBuffer[windowTextLength + 0] = '\r';
         editBuffer[windowTextLength + 1] = '\n';
         }
      else
         {
         editBufferLength = windowTextLength;
         }

      size_t bytesWritten = fwrite(
         editBuffer,
         sizeof(char),
         editBufferLength,
         file);
      if (bytesWritten == editBufferLength)
         {
         success = true;
         }

      if (success)
         {
         Editor->ClearModify();
         }

      delete [] editBuffer;
      }

   fclose(file);

   return success;
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
      error_happen = false;

      EndEdit();

      unlink(TempPathName);
      IsDirty = true;

      if (error_happen)
         {
         MainWindowx->CommandWindow->MessageBox(
            "The cursor will be positioned just after last successful definition.\n"
               "Check Commander Window for possible error Message.",
            "Your Edit has FAILED to load",
            MB_OK);

         error_happen = false;
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
   Editor->CmHelpEditTopic();
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

//
// sets the file name of the window and updates the caption
//
void TMyFileWindow::SetFileName(const char *fileName)
   {
   // BUG: this should be strcmp while accounting for NULL
   if (FileName != fileName)
      {
      delete FileName;
      FileName = fileName ? strnewdup(fileName) : 0;
      }

   const char *p = FileName ? FileName : "(Untitled)";

   if (!Title || !*Title)
      {
      SetWindowText(p);
      }
   else
      {
      char newCaption[81];

      wsprintf(newCaption, "%s - %s", Title, p);
      SetWindowText(newCaption);
      }
   }


void TMyFileWindow::SetupWindow()
   {
   TEditWindow::SetupWindow();
   SetFileName(FileName);

   if (FileName && !Read())
      {
      SetFileName(0);
      }
   
   LOGFONT lf;
   GetPrivateProfileFont("EditFont", lf);
   hEdtFont = CreateFontIndirect(&lf);
   Editor->SetWindowFont(hEdtFont, true);

   // We must clear the modify flag again, because
   // updating the font counts as a modification on WinXP
   Editor->ClearModify();
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

      // Changing the font counts a modification as far as
      // the edit control is concerned, but not as far as
      // Logo is concerned.
      // Therefore, we must preserve the IsModified() state
      // ourselves to prevent spurious warnings when closing
      // an unedited document.
      bool editorIsModified = Editor->IsModified();

      HFONT hFont = CreateFontIndirect(&lf);
      Editor->SetWindowFont(hFont, true);

      if (hEdtFont)
         {
         DeleteObject(hEdtFont);
         }
      hEdtFont = hFont;

      if (!editorIsModified)
         {
         Editor->ClearModify();
         }

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

bool TMyFileWindow::EndEdit()
   {

   bool realsave = endedit();

   // check for error

   for (int i = 0; i < 1; i++)
      {
      if (stopping_flag == THROWING)
         {
         if (compare_node(throw_node, Error, TRUE) == 0)
            {
            err_print();
            error_happen = true;
            }
         else if (compare_node(throw_node, System, TRUE) == 0) break;
         else if (compare_node(throw_node, Toplevel, TRUE) != 0)
            {
            err_logo(NO_CATCH_TAG, throw_node);
            err_print();
            error_happen = true;
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

   // if args_list specified no user callabled editor

   if (args_list != NULL)
      {
      error_happen = false;

      int realsave = EndEdit();

      // if error the ask user to reedit

      if (error_happen)
         {
         if (MainWindowx->CommandWindow->MessageBox(
               "The cursor will be positioned just after last successful definition.\n"
                  "Check Commander Window for possible error Message.\n"
                  "\n"
                  "Return to edit?",
               "Your Edit has FAILED to load",
               MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
            {
            if (TMainFrame::PopupEditorForFile(TempPathName, args_list))
               {
               MainWindowx->CommandWindow->MessageBox(
                  "Cannot restart editor",
                  "Fatal",
                  MB_OK | MB_ICONQUESTION);
               }
            else
               {
               unlink(TempPathName);
               IsDirty = true;
               }
            }
         else
            {
            error_happen = false;
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
            endedit();
            }

         // free up args_list

         args_list = reref(args_list, NIL);

         unlink(TempPathName);
         MainWindowx->CommandWindow->Editbox->SetFocus();
         }
      }
   else
      {
      // else execute callback for user callable editor
      callthing *callevent = new callthing;

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

   TEditWindow::DefaultProcessing();
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

DEFINE_RESPONSE_TABLE1(TMyFileWindow, TEditWindow)
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

