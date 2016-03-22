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
   const char far* text,
   int x,
   int y,
   int w,
   int h,
   const char far* fileName,
   TModule* module
) : TRichEdit(parent, id, text, x, y, w, h, fileName, module)
   {
   PopupMenu.AppendMenu(MF_STRING, CM_EDITUNDO,   "Undo");
   PopupMenu.AppendMenu(MF_SEPARATOR, 0, NULL);
   PopupMenu.AppendMenu(MF_STRING, CM_EDITCUT,    "Cut");
   PopupMenu.AppendMenu(MF_STRING, CM_EDITCOPY,   "Copy");
   PopupMenu.AppendMenu(MF_STRING, CM_EDITPASTE,  "Paste");
   PopupMenu.AppendMenu(MF_STRING, CM_EDITDELETE, "Delete");
   }

TRichEditWithPopup::~TRichEditWithPopup()
   {
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


DEFINE_RESPONSE_TABLE1(TRichEditWithPopup, TRichEdit)
  EV_WM_RBUTTONUP,
  EV_COMMAND(CM_EDITPASTE, CmPasteAsText),
END_RESPONSE_TABLE;



//
// constructor for a TEditWindow
//
// initializes its data fields using passed parameters and default values
// constructs its child edit control
//
TEditWindow::TEditWindow(
   TWindow *    parent,
   const char *	title,
   TModule *    module
) : TFrameWindow(parent, title, 0, false, module)
   {
   Editor = new TRichEditWithPopup(this, ID_EDITOR, 0, 0, 0, 0, 0, 0, module);
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

void TEditWindow::EvRButtonUp(UINT, TPoint &)
   {
   DefaultProcessing();
   }

void TEditWindow::CmFilePrint()
   {
   // Create Printout window and set characteristics.
   TRichEditPrintout printout(*MainWindowx->Printer, *Editor, "Logo");
   printout.SetBanding(false);

   // Bring up the Print dialog and print the document.
   MainWindowx->Printer->Print(this, printout, true);
   }

//
// reads an instance of TEditWindow from the passed ipstream
//
void *TEditWindow::Streamer::Read(ipstream &is, uint32 /*version*/)const
   {
   TEditWindow *o = GetObject();
   ReadBaseObject((TWindow *) o, is);

   is >> (TEditFile *) o->Editor;

   return o;
   }

//
// writes the TEditWindow to the passed opstream
//
void TEditWindow::Streamer::Write(opstream &os)const
   {
   TEditWindow *o = GetObject();
   WriteBaseObject((TWindow *) o, os);
   os << o->Editor;
   }

DEFINE_RESPONSE_TABLE1(TEditWindow, TFrameWindow)
  EV_WM_SIZE,
  EV_WM_SETFOCUS,
  EV_WM_RBUTTONUP,
  EV_COMMAND(CM_FILEPRINT, CmFilePrint),
END_RESPONSE_TABLE;

IMPLEMENT_STREAMABLE1(TEditWindow, TFrameWindow);

