#include "logocodectrl.h"

class CCommander;

class CCommanderInput : public CLogoCodeCtrl
{
public:
    CCommanderInput(CCommander* Parent, wxWindowID Id);

    static bool WantsKeyEvent(int KeyCode);
    void SimulateKeyPress(wxKeyEvent & KeyEvent);
    void SetText(const wxString & NewText);

private:
    // event handlers
    void OnKeyDown(wxKeyEvent & Event);
    void OnChar(wxKeyEvent & Event);
    void OnSetFocus(wxFocusEvent & Event);
    void OnKillFocus(wxFocusEvent & Event);
    void OnFindMatchingParen(wxCommandEvent& Event);
    void OnSelectMatchingParen(wxCommandEvent& Event);

    DECLARE_NO_COPY_CLASS(CCommanderInput);
    DECLARE_EVENT_TABLE();
};
