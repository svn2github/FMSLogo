#include <windows.h>

#include "wx/window.h"

class wxButton;
class wxRichTextCtrl;
class wxTextCtrl;

class CCommander : public wxWindow
{
public:
    CCommander(wxWindow *parent);
    ~CCommander() {};

    void OnButton(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
    void OnSize(wxSizeEvent& event);

private:
    wxButton *m_HaltButton;
    wxButton *m_TraceButton;
    wxButton *m_PauseButton;
    wxButton *m_StatusButton;
    wxButton *m_StepButton;
    wxButton *m_ResetButton;
    wxButton *m_ExecuteButton;
    wxButton *m_EdallButton;

    wxRichTextCtrl* m_History;
    wxTextCtrl    * m_NextInstruction;

    int m_NextInstructionHeight;
    int m_ButtonWidth;

    void RecalculateLayout();
    void UpdateFont(const wxFont & NewFont);

    DECLARE_EVENT_TABLE();
};
