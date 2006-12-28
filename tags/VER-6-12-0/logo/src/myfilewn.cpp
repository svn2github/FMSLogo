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

TMyFileWindow::TMyFileWindow(
   TWindow *AParent,
   LPCSTR   ATitle,
   LPCSTR   AFileName,
   NODE *   args,
   bool     check_for_errors
) : TEditWindow(AParent, ATitle),
    hEdtFont(NULL),
    args_list(args),
    FileName(NULL),
    check_for_errors(check_for_errors)
   {
   Attr.AccelTable = "IDM_FILECOMMANDS";
   FileName = AFileName ? strnewdup(AFileName) : NULL;
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

      wsprintf(err, LOCALIZED_ERROR_CANTREADFILE, fileName);
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

   FILE* file = fopen(fileName, "wb");
   if (file == NULL) 
      {
      char msg[MAXPATH + 33];

      wsprintf(msg, LOCALIZED_ERROR_CANTWRITEFILE, fileName);
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

      Editor->GetSubText(editBuffer, 0, editBufferLength);

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
      // Notify the user that this feature is only for experts
      MainWindowx->CommandWindow->MessageBox(
         LOCALIZED_SAVEISFOREXPERTSONLY,
         LOCALIZED_SAVETOWORKSPACE,
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
         // notify the user that:
         // 1) The changes in the editor failed to load
         // 2) The cursor is positioned just after the last 
         //    successful definition
         MainWindowx->CommandWindow->MessageBox(
            LOCALIZED_CURSORISATLASTGOODDEFINITION,
            LOCALIZED_EDITFAILEDTOLOAD,
            MB_OK | MB_ICONERROR);

         // "force" a change so that we still in "dirty" state
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

   size_t theTextLength = abs(end - start);
   char * theText = new char[theTextLength + 1];
   Editor->GetSubText(theText, start, end);
   theText[theTextLength] = '\0';
   
   char * ptr = theText;

   // strip comments
   bool more = true;
   while (more)
      {
      char * ptr2 = strchr(ptr, ';');

      if (ptr2 != NULL)
         {
         // overwrite the comment character with a space
         *ptr2 = ' ';

         // put whitespace over everything until the end-of-string
         // the end-of-line, or a comment continuer
         while (*ptr2 != '\0' &&
                *ptr2 != '\n' &&
                *ptr2 != '\r' &&
                *ptr2 != '~')
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

   const char *p = FileName ? FileName : "("LOCALIZED_UNTITLED")";

   if (!Title || !*Title)
      {
      SetWindowText(p);
      }
   else
      {
      char newCaption[256];

      newCaption[0] = '\0';
      strncat(newCaption, Title, sizeof(newCaption) - strlen(newCaption));
      strncat(newCaption, " - ", sizeof(newCaption) - strlen(newCaption));
      strncat(newCaption, p,     sizeof(newCaption) - strlen(newCaption));

      SetWindowText(newCaption);
      }
   }


void TMyFileWindow::SetupWindow()
   {
   TEditWindow::SetupWindow();

   //
   // Construct the main menu
   //
   static const MENUITEM fileMenuItems[] = {
      {LOCALIZED_EDITOR_FILE_SAVEANDEXIT,     CM_FILESAVEANDEXIT},
      {LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE, CM_FILESAVETOWORKSPACE},
      {LOCALIZED_EDITOR_FILE_PRINT,           CM_FILEPRINT},
      {0},
      {LOCALIZED_EDITOR_FILE_EXIT,            CM_EDALLEXIT},
   };

   static const MENUITEM editMenuItems[] = {
      {LOCALIZED_EDITOR_EDIT_UNDO,      CM_EDITUNDO},
      {0},
      {LOCALIZED_EDITOR_EDIT_CUT,       CM_EDITCUT},
      {LOCALIZED_EDITOR_EDIT_COPY,      CM_EDITCOPY},
      {LOCALIZED_EDITOR_EDIT_PASTE,     CM_EDITPASTE},
      {LOCALIZED_EDITOR_EDIT_DELETE,    CM_EDITDELETE},
      {0},
      {LOCALIZED_EDITOR_EDIT_CLEARALL,  CM_EDITCLEAR},
      {LOCALIZED_EDITOR_EDIT_SELECTALL, CM_EDITSELECTALL},
   };

   static const MENUITEM searchMenuItems[] = {
      {LOCALIZED_EDITOR_SEARCH_FIND,    CM_EDITFIND},
      {LOCALIZED_EDITOR_SEARCH_REPLACE, CM_EDITREPLACE},
      {LOCALIZED_EDITOR_SEARCH_NEXT,    CM_EDITFINDNEXT},
   };

   static const MENUITEM setMenuItems[] = {
      {LOCALIZED_EDITOR_SET_FONT,       CM_EDITSETFONT}
   };
 
   static const MENUITEM helpMenuItems[] = {
      {LOCALIZED_EDITOR_HELP_INDEX,       CM_HELP},
      {LOCALIZED_EDITOR_HELP_EDITOR,      CM_HELPEDIT},
      {LOCALIZED_EDITOR_HELP_TOPICSEARCH, CM_HELPEDIT_TOPIC},
   };

   TMenu mainMenu(CreateMenu());
   AppendPopupMenu(mainMenu, LOCALIZED_EDITOR_FILE,   fileMenuItems,   ARRAYSIZE(fileMenuItems));
   AppendPopupMenu(mainMenu, LOCALIZED_EDITOR_EDIT,   editMenuItems,   ARRAYSIZE(editMenuItems));
   AppendPopupMenu(mainMenu, LOCALIZED_EDITOR_SEARCH, searchMenuItems, ARRAYSIZE(searchMenuItems));
   AppendPopupMenu(mainMenu, LOCALIZED_EDITOR_SET,    setMenuItems,    ARRAYSIZE(setMenuItems));
   mainMenu.AppendMenu(MF_STRING, CM_TEST, LOCALIZED_EDITOR_TEST);
   AppendPopupMenu(mainMenu, LOCALIZED_EDITOR_HELP,   helpMenuItems,   ARRAYSIZE(helpMenuItems));
   SetMenu(mainMenu);



   SetFileName(FileName);

   if (FileName && !Read())
      {
      SetFileName(0);
      }
   
   LOGFONT lf;
   GetConfigurationFont("EditFont", lf);
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
   GetConfigurationFont("EditFont", lf);

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
      SetConfigurationFont("EditFont", lf);

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
   error_happen = process_special_conditions();

   return realsave;
   }

void TMyFileWindow::EvDestroy()
   {
   if (args_list != NIL || check_for_errors)
      {
      error_happen = false;

      int realsave = EndEdit();

      if (error_happen)
         {
         // Notify the user that:
         // 1) The changes in the editor failed to load
         // 2) The cursor is positioned just after the last 
         //    successful definition
         //
         // Ask if they want to reedit.

         if (MainWindowx->CommandWindow->MessageBox(
                LOCALIZED_CURSORISATLASTGOODDEFINITION"\n"
                   "\n"
                   LOCALIZED_RETURNTOEDIT,
                LOCALIZED_EDITFAILEDTOLOAD,
                MB_YESNO | MB_ICONERROR) == IDYES)
            {
            // open up another editor
            MainWindowx->MyPopupEdit(TempPathName, args_list, check_for_errors);
            unlink(TempPathName);
            IsDirty = true;
            }
         else
            {
            error_happen = false;
            MainWindowx->CommandWindow->Editbox.SetFocus();
            }
         }
      else
         {
         // no errors happened
         if (args_list != NIL)
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
            }

         unlink(TempPathName);
         MainWindowx->CommandWindow->Editbox.SetFocus();
         }
      }
   else
      {
      // else execute callback for user callable editor
      callthing *callevent = callthing::CreateFunctionEvent(edit_editexit);
      calllists.insert(callevent);
      }


   // Get location and size of our window on the screen so we can
   // come back up in the same spot next time we are invoked.

   if (!IsIconic())
      {
      TRect wrect;
      GetWindowRect(wrect);

      // Make a string with our window location and size.
      SetConfigurationQuadruple(
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
         LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE,
         LOCALIZED_CONTENTSCHANGED,
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

