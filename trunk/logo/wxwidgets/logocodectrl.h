// -*- c++ -*-

#include <wx/stc/stc.h>
#include <wx/fdrepdlg.h>
#include <wx/print.h>

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

    void Print();

private:

    // A private helper class for printing
    class CLogoCodePrintout : public wxPrintout
    {
    public:
        CLogoCodePrintout(
            const wxString        & Title,
            wxStyledTextCtrl      & EditControl,
            wxPageSetupDialogData & PageSetup
            );

        bool OnPrintPage(int Page);
        bool HasPage(int Page);
        bool OnBeginDocument(int StartPage, int EndPage);

        void
        GetPageInfo(
            int *MinPage,
            int *MaxPage,
            int *SelPageFrom,
            int *SelPageTo
            );

    private:
        void ScaleForPrinting(wxDC * DeviceContext);

        wxStyledTextCtrl      & m_EditControl;
        wxPageSetupDialogData & m_PageSetup;

        int m_NextPrintStartPosition;

        // Physical printers cannot print all the way to the edge
        // of the paper and most programs want to leave a user-defined
        // margin that is larger than the physical margin as defined
        // by the printer.  FMSLogo always uses the physical margins.
        //
        // m_RenderRectangle is the region (relative to the physical
        // margins of the printer) where FMSLogo prints its content.
        //
        // m_PageRectangle is the physical dimensions of the
        // printable region on the paper.
        wxRect m_RenderRectangle;
        wxRect m_PageRectangle;
    };

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
