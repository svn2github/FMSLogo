// -*- c++ -*-

#ifndef _MINIEDITORTEXTCTRL_H_
#define _MINIEDITORTEXTCTRL_H_

#include "logocodectrl.h"

class wxKeyEvent;

class CMiniEditorTextCtrl : public CLogoCodeCtrl
{
public:
    CMiniEditorTextCtrl(wxWindow *Parent, wxWindowID Id);
    ~CMiniEditorTextCtrl();

    void OnKeyDown(wxKeyEvent& Event);

private:
    DECLARE_NO_COPY_CLASS(CMiniEditorTextCtrl);
    DECLARE_EVENT_TABLE();
};

#endif // _MINIEDITORTEXTCTRL_H_
