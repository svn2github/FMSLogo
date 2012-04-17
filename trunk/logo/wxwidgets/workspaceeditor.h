// -*- c++ -*-

#include <wx/frame.h>
#include <wx/fdrepdlg.h>

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

    void OnFind(wxCommandEvent& Event);
    void OnUpdateFind(wxUpdateUIEvent& Event);
    void OnReplace(wxCommandEvent& Event);
    void OnUpdateReplace(wxUpdateUIEvent& Event);
    void OnFindNext(wxCommandEvent& Event);
    void OnUpdateFindNext(wxUpdateUIEvent& Event);

    void OnSetFont(wxCommandEvent& Event);
    void OnFindMatchingParen(wxCommandEvent& Event);
    void OnSelectMatchingParen(wxCommandEvent& Event);

    void OnFindDialog(wxFindDialogEvent& Event);
    void OnFindDialogNext(wxFindDialogEvent& Event);
    void OnFindDialogReplace(wxFindDialogEvent& Event);
    void OnFindDialogReplaceAll(wxFindDialogEvent& Event);
    void OnFindDialogClose(wxFindDialogEvent& Event);

    void OnClose(wxCloseEvent& Event);

    // Helper functions
    void SetScintillaSearchFlags();

    // member variables
    CLogoCodeCtrl       * m_LogoCodeControl;
    wxFindReplaceDialog * m_FindReplaceDialog;
    wxFindReplaceData     m_FindReplaceData;

    DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CWorkspaceEditor);
};
