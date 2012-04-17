// -*- c++ -*-

#include <wx/stc/stc.h>
#include <wx/fdrepdlg.h>

class CLogoCodeCtrl : public wxStyledTextCtrl
{
public:
    CLogoCodeCtrl(
        wxWindow       * Parent,
        wxWindowID       Id       = wxID_ANY
        );

    void SetFont(wxFont & font);

    void FindMatchingParen();
    void SelectMatchingParen();
    bool IsTextSelected();

    void
    Find(
        wxFindReplaceFlags WxSearchFlags,
        const wxString &   StringToFind
        );

    void
    Replace(
        wxFindReplaceFlags WxSearchFlags,
        const wxString &   StringToFind,
        const wxString &   ReplacementString
        );

    void
    ReplaceAll(
        wxFindReplaceFlags WxSearchFlags,
        const wxString &   StringToFind,
        const wxString &   ReplacementString
        );

private:

    // Event handlers
    void OnUpdateUi(wxStyledTextEvent& event);


    // Helper functions
    void ScrollCaret();

    void
    SetScintillaSearchFlags(
        wxFindReplaceFlags WxSearchFlags
        );

    enum SEARCH_OPERATION
    {
        SEARCH_OPERATION_FindAndReplace,
        SEARCH_OPERATION_Find,
    };

    void
    DoSearchOperation(
        SEARCH_OPERATION   SearchOperation,
        wxFindReplaceFlags WxSearchFlags,
        const wxString &   StringToFind,
        const wxString &   ReplacementString
        );

    void
    FindMatchingParen(
        int & CurrentParenPosition,
        int & MatchingParenPosition
        );

    DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CLogoCodeCtrl);
};
