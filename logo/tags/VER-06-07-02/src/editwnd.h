//----------------------------------------------------------------------------
// ObjectWindows - (C) Copyright 1991, 1993 by Borland International
//   Definition of class TEditWindow.  This defines the OWL 1.0 compatible
//   text edit window
//----------------------------------------------------------------------------
#ifndef __EDITWND_H
#define __EDITWND_H

#include "owl\richedit.h"
#include "owl\framewin.h"

//_CLASSDEF(TEditWindow)

//
//  class TEditWindow
//  ----- -----------
//
class TRichEditWithPopup : public TRichEdit
{
public:
   TRichEditWithPopup(
      TWindow* parent,
      int id,
      const char far* text,
      int x,
      int y,
      int w,
      int h,
      const char far* fileName = 0,
      TModule* module = 0);

   ~TRichEditWithPopup();

   void  CmHelpEditTopic(); // CM_HELPEDIT_TOPIC

protected:

   void  EvRButtonUp(UINT, TPoint &);
   void  CmPasteAsText();   // CM_PASTE

   TPopupMenu PopupMenu;

   DECLARE_RESPONSE_TABLE(TRichEditWithPopup);
};

class TEditWindow : public TFrameWindow
   {
 public:
   TRichEditWithPopup *Editor;

   TEditWindow(TWindow * parent, const char far * title, TModule * module = 0);

 protected:
   //
   // message response functions
   //
   void  EvSize(UINT sizeType, TSize &);
   void  EvSetFocus(HWND lostFocus);

   //
   // menu command handlers
   //
   void  CmFilePrint();     // CM_FILEPRINT

   DECLARE_RESPONSE_TABLE(TEditWindow);
   }
;

#endif //__EDITWND_H

