// -*- c++ -*-

#include "wx/frame.h"

class CLogoCodeCtrl;

class CWorkspaceEditor: public wxFrame
{
public:
    CWorkspaceEditor(wxWindow * Parent);

private:

    // Menu commands event handlers
    void OnQuit(wxCommandEvent& Event);

    void OnUndo(wxCommandEvent& Event);
    void OnUpdateUndo(wxUpdateUIEvent& Event);
    void OnRedo(wxCommandEvent& Event);
    void OnUpdateRedo(wxUpdateUIEvent& Event);
    void OnCut(wxCommandEvent& Event);
    void OnUpdateCut(wxUpdateUIEvent& Event);
    void OnCopy(wxCommandEvent& Event);
    void OnUpdateCopy(wxUpdateUIEvent& Event);
    void OnPaste(wxCommandEvent& Event);
    void OnUpdatePaste(wxUpdateUIEvent& Event);
    void OnDelete(wxCommandEvent& Event);
    void OnUpdateDelete(wxUpdateUIEvent& Event);
    void OnClear(wxCommandEvent& Event);
    void OnUpdateClear(wxUpdateUIEvent& Event);
    void OnSelectAll(wxCommandEvent& Event);
    void OnUpdateSelectAll(wxUpdateUIEvent& Event);

    void OnSetFont(wxCommandEvent& Event);
    void OnFindMatchingParen(wxCommandEvent& Event);
    void OnSelectMatchingParen(wxCommandEvent& Event);

    void OnClose(wxCloseEvent& Event);

    // member variables
    CLogoCodeCtrl * m_LogoCodeControl;

    DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CWorkspaceEditor);
};
