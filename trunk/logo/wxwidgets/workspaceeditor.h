// -*- c++ -*-

#include "wx/frame.h"

class CLogoCodeCtrl;

class CWorkspaceEditor: public wxFrame
{
public:
    CWorkspaceEditor(wxWindow * Parent);

    // Menu commands
    void OnQuit(wxCommandEvent& Event);
    void OnCut(wxCommandEvent& Event);
    void OnSetFont(wxCommandEvent& Event);
    void OnFindMatchingParen(wxCommandEvent& Event);
    void OnSelectMatchingParen(wxCommandEvent& Event);

    void OnClose(wxCloseEvent& Event);

private:
    CLogoCodeCtrl * m_LogoCodeControl;

    DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CWorkspaceEditor);
};
