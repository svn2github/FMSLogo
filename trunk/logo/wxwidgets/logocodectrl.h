// -*- c++ -*-

#include <wx/stc/stc.h>

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

private:

    void ScrollCaret();

    void
    FindMatchingParen(
        int & CurrentParenPosition,
        int & MatchingParenPosition
        );

    //DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CLogoCodeCtrl);
};
