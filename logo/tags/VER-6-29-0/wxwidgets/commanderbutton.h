#ifndef WX_PRECOMP
    #include "wx/button.h"
#endif

class CCommander;

class CCommanderButton : public wxButton
{
public:
    CCommanderButton(CCommander* Parent, wxWindowID Id, const wxString& Label);
    virtual ~CCommanderButton(){};

    void OnKeyDown(wxKeyEvent& event);

private:
    DECLARE_NO_COPY_CLASS(CCommanderButton);
    DECLARE_EVENT_TABLE();
};
