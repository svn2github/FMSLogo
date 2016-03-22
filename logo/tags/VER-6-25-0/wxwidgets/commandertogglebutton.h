#ifndef WX_PRECOMP
    #include <wx/tglbtn.h>
#endif

class CCommander;
class wxKeyEvent;

class CCommanderToggleButton : public wxToggleButton
{
public:

    CCommanderToggleButton(
        CCommander * Parent, 
        wxWindowID   Id,
        const char * DownLabel,
        const char * UpLabel
        );

    void SetPressedState(bool IsPressed);

    void OnKeyDown(wxKeyEvent& event);

private:

    const char * m_DownLabel;
    const char * m_UpLabel;

    DECLARE_NO_COPY_CLASS(CCommanderToggleButton);
    DECLARE_EVENT_TABLE();
};

