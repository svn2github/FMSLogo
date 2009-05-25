// -*- c++ -*-
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
        const char * text,
        int x,
        int y,
        int w,
        int h,
        const char * fileName = 0
        );

    ~TRichEditWithPopup();

    void  CmHelpEditTopic(); // CM_HELPEDIT_TOPIC

protected:
    TRichEditWithPopup(TWindow* parent, int id);

    // CM_EDITSELECTALL
    void CmSelectAll();       
    void CmSelectAllEnable(TCommandEnabler& commandHandler);

    void EvRButtonUp(UINT, TPoint &);
    void CmPasteAsText();         // CM_PASTE
    void CmFindMatchingParen();   // CM_FINDMATCHINGPAREN 
    void CmSelectMatchingParen(); // CM_SELECTMATCHINGPAREN 

    int GetCaretPosition();
    void SetCaretPosition(uint32 CaretCharIndex);
    void UpdateCaretPosition(uint32 CaretCharIndex);
    int SearchForwardForMatchingParen(int CaretPosition, char ParenToMatch);
    int SearchBackwardForMatchingParen(int CaretPosition, char ParenToMatch);

    TPopupMenu PopupMenu;

    DECLARE_RESPONSE_TABLE(TRichEditWithPopup);
};

class TEditWindow : public TFrameWindow
{
public:
    TRichEditWithPopup *Editor;

    TEditWindow(TWindow * parent, const char * title);

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
};

#endif //__EDITWND_H
