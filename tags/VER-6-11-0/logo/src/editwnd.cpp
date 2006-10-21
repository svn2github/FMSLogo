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

TRichEditWithPopup::TRichEditWithPopup(
   TWindow* parent,
   int id,
   const char * text,
   int x,
   int y,
   int w,
   int h,
   const char * fileName
) : TRichEdit(parent, id, text, x, y, w, h, fileName)
   {
   PopupMenu.AppendMenu(MF_STRING, CM_EDITUNDO,   "Undo");
   PopupMenu.AppendMenu(MF_SEPARATOR, 0, NULL);
   PopupMenu.AppendMenu(MF_STRING, CM_EDITCUT,    "Cut");
   PopupMenu.AppendMenu(MF_STRING, CM_EDITCOPY,   "Copy");
   PopupMenu.AppendMenu(MF_STRING, CM_EDITPASTE,  "Paste");
   PopupMenu.AppendMenu(MF_STRING, CM_EDITDELETE, "Delete");
   PopupMenu.AppendMenu(MF_STRING, CM_EDITSELECTALL, "Select All");
   PopupMenu.AppendMenu(MF_SEPARATOR, 0, NULL);
   PopupMenu.AppendMenu(MF_STRING, CM_HELPEDIT_TOPIC, "Topic Search");
   }

// protected constructor does not supply a menu
TRichEditWithPopup::TRichEditWithPopup(
   TWindow* parent,
   int      id
) : TRichEdit(parent, id, NULL, 0, 0, 0, 0)
   {
   }

TRichEditWithPopup::~TRichEditWithPopup()
   {
   }

void TRichEditWithPopup::CmSelectAll()
   {
   int endOfText = GetTextLen();
   SetSelection(0, endOfText);
   }

void TRichEditWithPopup::CmSelectAllEnable(TCommandEnabler& commandHandler)
   {
   UINT textLength = GetTextLen();
   bool isNotEmpty = textLength != 0;
   commandHandler.Enable(isNotEmpty);
   }

void TRichEditWithPopup::EvRButtonUp(UINT, TPoint & point)
   {
   ClientToScreen(point);
   PopupMenu.TrackPopupMenu(TPM_LEFTBUTTON, point, 0, HWindow);
   }

// paste as raw text so that we don't preserve any
// formatting of rich text.
void TRichEditWithPopup::CmPasteAsText()
   {
   OpenClipboard();

   HGLOBAL hText = GetClipboardData(CF_TEXT);

   if (hText)
      {
      LPCSTR lpText = (LPCSTR) GlobalLock(hText);
      Insert(lpText);
      GlobalUnlock(hText);
      }

   CloseClipboard();
   }


// paste as raw text so that we don't preserve any
// formatting of rich text.
void TRichEditWithPopup::CmHelpEditTopic()
   {
   ContextHelp(this);
   }


DEFINE_RESPONSE_TABLE1(TRichEditWithPopup, TRichEdit)
   EV_WM_RBUTTONUP,
   EV_COMMAND(CM_EDITPASTE,            CmPasteAsText),
   EV_COMMAND(CM_EDITSELECTALL,        CmSelectAll),
   EV_COMMAND(CM_HELPEDIT_TOPIC,       CmHelpEditTopic),
   EV_COMMAND_ENABLE(CM_EDITSELECTALL, CmSelectAllEnable),
END_RESPONSE_TABLE;



//
// constructor for a TEditWindow
//
// initializes its data fields using passed parameters and default values
// constructs its child edit control
//
TEditWindow::TEditWindow(
   TWindow *    parent,
   const char *	title
) : TFrameWindow(parent, title, 0, false)
   {
   Editor = new TRichEditWithPopup(this, ID_EDITOR, 0, 0, 0, 0, 0, 0);
   Editor->Attr.ExStyle |= WS_EX_RIGHTSCROLLBAR;
   Editor->Attr.Style |= ES_NOHIDESEL | ES_AUTOHSCROLL | ES_AUTOVSCROLL;
   }

//
// responds to an incoming WM_SIZE message by resizing the child edit
// control to fill the TEditWindow's client area
//
void TEditWindow::EvSize(UINT sizeType, TSize &size)
   {
   TWindow::EvSize(sizeType, size);
   Editor->SetWindowPos(0, 0, 0, size.cx, size.cy, SWP_NOZORDER);
   }

//
// responds to an incoming WM_SETFOCUS message by setting the focus to
// the child edit control
//
void TEditWindow::EvSetFocus(HWND)
   {
   Editor->SetFocus();
   }

void TEditWindow::CmFilePrint()
   {
   // Create Printout window and set characteristics.
   TRichEditPrintout printout(MainWindowx->Printer, *Editor, "Logo");
   printout.SetBanding(false);

   // Bring up the Print dialog and print the document.
   MainWindowx->Printer.Print(this, printout, true);
   }

void TEditWindow::CmSelectAll()
   {
   // delegate to the Editor window
   Editor->SendMessage(WM_COMMAND, CM_EDITSELECTALL, 0);
   }

DEFINE_RESPONSE_TABLE1(TEditWindow, TFrameWindow)
  EV_WM_SIZE,
  EV_WM_SETFOCUS,
  EV_COMMAND(CM_FILEPRINT, CmFilePrint),
  EV_COMMAND(CM_EDITSELECTALL, CmSelectAll),
END_RESPONSE_TABLE;

