// -*- c++ -*-

#ifndef _MINIEDITORTEXTCTRL_H_
#define _MINIEDITORTEXTCTRL_H_

#ifndef WX_PRECOMP
  #include <wx/richtext/richtextctrl.h>
#endif

class wxKeyEvent;

class CMiniEditorTextCtrl : public wxRichTextCtrl
{
public:
    CMiniEditorTextCtrl(wxWindow *Parent, wxWindowID Id, const wxSize & Size);
    ~CMiniEditorTextCtrl();

    void OnKeyDown(wxKeyEvent& Event);

private:
    DECLARE_NO_COPY_CLASS(CMiniEditorTextCtrl);
    DECLARE_EVENT_TABLE();
};

#endif // _MINIEDITORTEXTCTRL_H_
