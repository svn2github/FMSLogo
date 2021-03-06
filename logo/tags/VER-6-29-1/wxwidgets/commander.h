// -*- c++ -*-

#include <wx/panel.h>
#include <wx/dialog.h>

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
    void Execute();
    void Duplicate(CCommander & Source);

    void GiveControlToInputBox();
    void GiveControlToHistoryBox();

    void ProcessKeyDownEventAtInputControl(wxKeyEvent& Event);

    void AppendToCommanderHistory(const char * String);
    void AppendToCommanderHistory(char Char);

    CCommanderHistory * GetHistory();
    CCommanderInput   * GetInput();
    wxButton          * GetEdallButton();

    const wxSize GetRecommendedMinimumSize() const;

    // HACK: friend functions
    friend void putcombobox(const char *str);
    friend void clearcombobox();

private:
    // Prevent objects from being declared as a stack variables
    ~CCommander();

    // Event handlers
    void OnHaltButton(wxCommandEvent& Event);
    void OnTraceButton(wxCommandEvent& Event);
    void OnPauseButton(wxCommandEvent& Event);
    void OnStatusButton(wxCommandEvent& Event);
    void OnStepButton(wxCommandEvent& Event);
    void OnResetButton(wxCommandEvent& Event);
    void OnExecuteButton(wxCommandEvent& Event);
    void OnEdallButton(wxCommandEvent& Event);
    void OnEnter(wxCommandEvent & Event);
    void OnSize(wxSizeEvent& Event);

    // Private helper functions
    void RecalculateLayout();
    void UpdateFont(const wxFont & NewFont);

    // Private member variables
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

    DECLARE_NO_COPY_CLASS(CCommander);
    DECLARE_EVENT_TABLE();
};

class CCommanderDialog : public wxDialog
{
public:
    CCommanderDialog(wxWindow *Parent);
    CCommander * GetCommander();

private:
    // event handlers
    void OnClose(wxCloseEvent& Event);
    void OnNavigateNextWindow(wxCommandEvent& Event);

    // member variables
    CCommander * m_Commander;

    DECLARE_NO_COPY_CLASS(CCommanderDialog);
    DECLARE_EVENT_TABLE();
};


void
RunLogoInstructionFromGui(
    char * LogoInstruction
    );
