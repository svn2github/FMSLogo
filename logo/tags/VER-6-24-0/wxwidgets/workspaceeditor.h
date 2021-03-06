// -*- c++ -*-

#include "wx/frame.h"

class wxRichTextCtrl;

class CWorkspaceEditor: public wxFrame
{
public:
    CWorkspaceEditor(wxWindow * Parent);

    // Menu commands
    void Quit(wxCommandEvent& Event);
    void SetFont(wxCommandEvent& Event);
    void OnClose(wxCloseEvent& Event);

private:
    wxRichTextCtrl * m_RichTextControl;

    DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CWorkspaceEditor);
};
