// -*- c++ -*-
#ifndef _LOGOCODECTRL_H_
#define _LOGOCODECTRL_H_

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

    bool SetFont(const wxFont & Font);

    void FindMatchingParen();
    void SelectMatchingParen();
    void AutoComplete();
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

    bool IsDirty() const;
    void ReopenAfterError();

    // Event handlers that a caller might delegate to.
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
    void OnSelectAll(wxCommandEvent& Event);
    void OnUpdateSelectAll(wxUpdateUIEvent& Event);
    void OnHelpTopicSearch(wxCommandEvent& Event);

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
    void OnSavePointReached(wxStyledTextEvent& event);
    void OnSavePointLeft(wxStyledTextEvent& event);
    void OnContextMenu(wxContextMenuEvent& Event);


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

    // Whether or not the contents of the editor have changed
    // since they were last synchronized with the file.
    bool m_IsDirty;
};

#endif // _LOGOCODECTRL_H_
