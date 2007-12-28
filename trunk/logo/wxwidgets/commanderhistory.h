#ifndef WX_PRECOMP
  #include "wx/richtext/richtextctrl.h"
#endif

class CCommander;

class CCommanderHistory : public wxRichTextCtrl
{
public:
    CCommanderHistory(CCommander* Parent, wxWindowID Id);

    void OnKeyDown(wxKeyEvent& event);

private:
    DECLARE_NO_COPY_CLASS(CCommanderHistory);
    DECLARE_EVENT_TABLE();
};
