// -*- c++ -*-

#include <wx/panel.h>
#include <wx/dialog.h>

class wxButton;
class wxRichTextCtrl;
class wxTextCtrl;
class wxSizer;

class CCommander : public wxPanel
{
public:
    CCommander(wxWindow *parent);
    ~CCommander() {};

    void OnHaltButton(wxCommandEvent& event);
    void OnTraceButton(wxCommandEvent& event);
    void OnPauseButton(wxCommandEvent& event);
    void OnStatusButton(wxCommandEvent& event);
    void OnStepButton(wxCommandEvent& event);
    void OnResetButton(wxCommandEvent& event);
    void OnExecuteButton(wxCommandEvent& event);
    void OnEdallButton(wxCommandEvent& event);

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
    int m_ButtonHeight;

    void RecalculateLayout();
    void UpdateFont(const wxFont & NewFont);

    DECLARE_EVENT_TABLE();
};

class CCommanderDialog : public wxDialog
{
public:
    CCommanderDialog(wxWindow *parent);

    void OnSize(wxSizeEvent& event);
    void OnDestroy(wxWindowDestroyEvent & event);
    void OnClose(wxCloseEvent& event);

private:
    CCommander * m_Commander;

    DECLARE_EVENT_TABLE();
};
