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


//
// constructor for a TFileWindow
//
// initializes its data members using passed parameters and default values
//
TFileWindow::TFileWindow(
   TWindow *    parent,
   const char * title,
   const char * fileName,
   TModule *    module
) : TEditWindow(parent, title, module)
   {
   FileName = fileName ? strnewdup(fileName) : 0;
   }

   //
// dispose of the file name
//
TFileWindow::~TFileWindow()
   {
   if (!HWindow)
      {
      return;
      }

   HMENU oldMenu = GetMenu();

   if (oldMenu)
      {
      ::DestroyMenu(oldMenu);
      }

   delete FileName;
   }

//
// performs setup for a TFileWindow, appending 'Untitled' to its caption
//
void TFileWindow::SetupWindow()
   {
   TEditWindow::SetupWindow();
   SetFileName(FileName);

   if (FileName && !Read())
      {
      SetFileName(0);
      }
   }

//
// sets the file name of the window and updates the caption
//
void TFileWindow::SetFileName(const char *fileName)
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


//
// begins the edit of a new file, after determining that it is Ok to
// clear the TEdit's text
//
void TFileWindow::NewFile()
   {
   if (CanClear())
      {
      Editor->Clear();
      Editor->Invalidate();
      Editor->ClearModify();
      SetFileName(0);
      }
   }

//
// replaces the current file with the given file
//
void TFileWindow::ReplaceWith(const char *fileName)
   {
   if (Read(fileName))
      {
      Editor->Invalidate();
      SetFileName(fileName);
      }
   }

//
// brings up a dialog allowing the user to open a file into this
// window
//
// same as selecting File|Open from the menus
//
void TFileWindow::Open()
   {
   //  char  tmpName[MAXPATH];

   //  if (CanClear() &&
   //      TFileDialog(this, SD_FILEOPEN, strcpy(tmpName, "*.*")).Execute() == IDOK)
   //    ReplaceWith(tmpName);
   }

//
// reads the contents of a previously-specified file into the TEdit
// child control
//
bool TFileWindow::Read(const char *fileName)
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
   int file = _lopen(fileName, OF_READ);

   if (file != -1)
      {
      long charsToRead = _llseek(file, 0, SEEK_END);
      _llseek(file, 0, SEEK_SET);

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
            if (_lread(file, editBuffer, charsToRead) == charsToRead)
               {
               editBuffer[charsToRead] = '\0';
               success = true;
               Editor->SetWindowText(editBuffer);
               Editor->ClearModify();
               }
            delete [] editBuffer;
            }
         }
      _lclose(file);
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
// saves the contents of the TEdit child control into the file currently
// being editted
//
// returns true if the file was saved or Editor->IsModified returns false
//(contents already saved)
//
bool TFileWindow::Save()
   {
   if (Editor->IsModified())
      {
      if (!FileName)
         {
         return SaveAs();
         }
      else
      	{
           return Write();
      	}
      }
   else
      {
      return true; //editor's contents haven't been changed
      }
   }

//
// saves the contents of the TEdit child control into a file whose name
// is retrieved from the user, through execution of a "Save" file dialog
//
// returns true if the file was saved
//
bool TFileWindow::SaveAs()
   {
   return false;
   }

//
// writes the contents of the TEdit child control to a previously-specified
// file
//
bool TFileWindow::Write(const char *fileName)
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

   int file = _lcreat(fileName, 0);
   if (file == -1)
      {
      char msg[MAXPATH + 33];

      wsprintf(msg, "Unable to write file \"%s\" to disk", FileName);
      MessageBox(msg, GetModule()->GetName(), MB_ICONEXCLAMATION | MB_OK);
      return false;
      }

   bool success = false;

   char *editBuffer = (char *) malloc(Editor->GetWindowTextLength() + 4);
   memset(editBuffer, 0, Editor->GetWindowTextLength() + 4);
   if (editBuffer)
      {

      long iLength = Editor->GetWindowTextLength();
      Editor->GetWindowText(editBuffer, iLength + 1);
      if (editBuffer[iLength - 1] != '\n')
         {
         editBuffer[iLength + 0] = '\r';
         editBuffer[iLength + 1] = '\n';
         editBuffer[iLength + 2] = '\0';
         }

      success = _lwrite(
         file,
         editBuffer,
         Editor->GetWindowTextLength() + 4) != (WORD) - 1;
      free(editBuffer);

      if (success)
         {
         Editor->ClearModify();
         }
      }
   _lclose(file);

   return success;
   }

//
// returns a bool value indicating whether or not it is Ok to clear
// the TEdit's text
//
// returns true if the text has not been changed, or if the user Oks the
// clearing of the text
//
bool TFileWindow::CanClear()
   {
   if (Editor->IsModified())
      {
      int result;
      char msg[MAXPATH + 28];

      if (!FileName)
         {
         strcpy(msg, "Untitled file has changed.  Save?");
         }
      else
         {
         wsprintf(msg, "File \"%s\" has changed.  Save?", FileName);
         }

      result = MessageBox(msg, "File Changed", MB_YESNOCANCEL | MB_ICONQUESTION);

      return result == IDYES ? Save() : result != IDCANCEL;
      }
   return true;
   }

//
// reads an instance of TFileWindow from the passed ipstream
//
void *TFileWindow::Streamer::Read(ipstream &is, uint32 /*version*/)const
   {
   TFileWindow *o = GetObject();
   ReadBaseObject((TEditWindow *) o, is);
   o->FileName = is.freadString();
   return o;
   }

//
// writes the TFileWindow to the passed opstream
//
void TFileWindow::Streamer::Write(opstream &os)const
   {
   TFileWindow *o = GetObject();
   WriteBaseObject((TEditWindow *) o, os);
   os.fwriteString(o->FileName ? o->FileName : "");
   }


DEFINE_RESPONSE_TABLE1(TFileWindow, TEditWindow)
  EV_COMMAND(CM_FILENEW, CmFileNew),
  EV_COMMAND(CM_FILEOPEN, CmFileOpen),
  EV_COMMAND(CM_FILESAVE, CmFileSave),
  EV_COMMAND(CM_FILESAVEAS, CmFileSaveAs),
END_RESPONSE_TABLE;

IMPLEMENT_STREAMABLE1(TFileWindow, TEditWindow);

