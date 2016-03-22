// -*- c++ -*-

#include <wx/panel.h>
#include <wx/dialog.h>

class wxTextCtrl;
class wxSizer;
class CCommanderButton;
class CCommanderToggleButton;
class CCommanderHistory;
class CCommanderInput;
class wxButton;

class CCommander : public wxPanel
{
public:
    CCommander(wxWindow *Parent);

    CCommander * GetCommander();

    void ChooseNewFont();

    void UpdateTraceButtonState();
    void UpdateStepButtonState();
    void UpdateStatusButtonState();

    void ToggleStep();
    void Halt();

    void GiveControlToInputBox();
    void GiveControlToHistoryBox();

    void PostKeyDownToInputControl(wxKeyEvent& Event);

    void AppendToCommanderHistory(const char * String);
    void AppendToCommanderHistory(char Char);

    CCommanderHistory * GetHistory();
    CCommanderInput   * GetInput();
    wxButton          * GetEdallButton();

    // HACK: friend functions
    friend void putcombobox(const char *str);
    friend void clearcombobox();

private:

    // Event handlers
    void OnHaltButton(wxCommandEvent& Event);
    void OnTraceButton(wxCommandEvent& Event);
    void OnPauseButton(wxCommandEvent& Event);
    void OnStatusButton(wxCommandEvent& Event);
    void OnStepButton(wxCommandEvent& Event);
    void OnResetButton(wxCommandEvent& Event);
    void OnExecuteButton(wxCommandEvent& Event);
    void OnEdallButton(wxCommandEvent& Event);

    void OnSize(wxSizeEvent& Event);
    void OnKeyDown(wxKeyEvent& Event);

    CCommanderButton        * m_HaltButton;
    CCommanderToggleButton  * m_TraceButton;
    CCommanderButton        * m_PauseButton;
    CCommanderToggleButton  * m_StatusButton;
    CCommanderToggleButton  * m_StepButton;
    CCommanderButton        * m_ResetButton;
    CCommanderButton        * m_ExecuteButton;
    CCommanderButton        * m_EdallButton;

    CCommanderHistory * m_History;
    CCommanderInput   * m_NextInstruction;

    int m_NextInstructionHeight;

    int m_ButtonWidth;
    int m_ButtonHeight;

    void RecalculateLayout();
    void UpdateFont(const wxFont & NewFont);

    DECLARE_NO_COPY_CLASS(CCommander);
    DECLARE_EVENT_TABLE();
};

class CCommanderDialog : public wxDialog
{
public:
    CCommanderDialog(wxWindow *parent);
    CCommander * GetCommander();

    bool EditBoxWantsKeyEvent() const;

private:
    // event handlers
    void OnSize(wxSizeEvent& event);
    void OnClose(wxCloseEvent& event);

    // member variables
    CCommander * m_Commander;

    DECLARE_NO_COPY_CLASS(CCommanderDialog);
    DECLARE_EVENT_TABLE();
};


void
RunLogoInstructionFromGui(
    char * LogoInstruction
    );
