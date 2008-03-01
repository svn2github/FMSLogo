#ifndef WX_PRECOMP
  #include "wx/richtext/richtextctrl.h"
#endif

class CCommander;

class CCommanderHistory : public wxRichTextCtrl
{
public:
    CCommanderHistory(CCommander* Parent, wxWindowID Id);

    bool IsCursorAtBottom() const;
    void CopyCurrentLineToCommanderInput() const;

    void OnKeyDown(wxKeyEvent& event);
    void OnChar(wxKeyEvent& event);

private:
    CCommander * GetCommander() const;

    DECLARE_NO_COPY_CLASS(CCommanderHistory);
    DECLARE_EVENT_TABLE();
};
