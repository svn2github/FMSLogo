#ifndef WX_PRECOMP
    #include "wx/textctrl.h"
#endif

class CCommander;

class CCommanderInput : public wxTextCtrl
{
public:
    CCommanderInput(CCommander* Parent, wxWindowID Id);

    static bool WantsKeyEvent(int KeyCode);
    void Duplicate(CCommanderInput & Source);

private:
    
    // event handlers
    void OnKeyDown(wxKeyEvent& event);

    DECLARE_NO_COPY_CLASS(CCommanderInput);
    DECLARE_EVENT_TABLE();
};
