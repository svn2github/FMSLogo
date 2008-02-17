#ifndef WX_PRECOMP
    #include "wx/textctrl.h"
#endif

class CCommander;

class CCommanderInput : public wxTextCtrl
{
public:
    CCommanderInput(CCommander* Parent, wxWindowID Id);

    void OnKeyDown(wxKeyEvent& event);

    static bool WantsKeyEvent(int KeyCode);

private:
    DECLARE_NO_COPY_CLASS(CCommanderInput);
    DECLARE_EVENT_TABLE();
};
