#ifdef __WXMSW__
#  include <windows.h>  // for LOGFONT
#endif

#include "commander.h"

#include <wx/msgdlg.h>
#include <wx/sizer.h>
#include <wx/defs.h>
#include <wx/fontdlg.h>
#include <wx/richtext/richtextctrl.h>

#include "fmslogo.h"
#include "mainframe.h"
#include "statusdialog.h"
#include "workspaceeditor.h"
#include "localizedstrings.h"
#include "utils.h"
#include "logocore.h"
#include "logodata.h"
#include "commanderbutton.h"
#include "commandertogglebutton.h"
#include "commanderinput.h"
#include "commanderhistory.h"
#include "dynamicbuffer.h"
#include "parse.h"
#include "error.h"
#include "eval.h"
#include "graphics.h"
#include "graphwin.h"
#include "status.h"
#include "fontutils.h"
#include "mmwind.h"
#include "stringadapter.h"

bool g_IsOkayToUseCommanderWindow = true;

// holds the history
static CDynamicBuffer g_HistoryBuffer;

// Menu IDs
enum
{
   ID_COMMANDER_HALT = wxID_HIGHEST,
   ID_COMMANDER_TRACE,
   ID_COMMANDER_PAUSE,
   ID_COMMANDER_STATUS,
   ID_COMMANDER_STEP,
   ID_COMMANDER_UNSTEP,
   ID_COMMANDER_RESET,
   ID_COMMANDER_EXECUTE,
   ID_COMMANDER_EDALL,
   ID_COMMANDER_HISTORY,
   ID_COMMANDER_NEXTINSTRUCTION,

   ID_COMMANDER_NEXT_WINDOW,
};

// ----------------------------------------------------------------------------
// CCommander
// ----------------------------------------------------------------------------

CCommander::CCommander(wxWindow *Parent)
    : wxPanel(Parent, wxID_ANY)
{
    m_History = new CCommanderHistory(this, ID_COMMANDER_HISTORY);

    m_NextInstruction = new CCommanderInput(this, ID_COMMANDER_NEXTINSTRUCTION);

    m_HaltButton = new CCommanderButton(
        this,
        ID_COMMANDER_HALT,
        LOCALIZED_COMMANDER_HALT);

    m_TraceButton = new CCommanderToggleButton(
        this,
        ID_COMMANDER_TRACE,
        LOCALIZED_COMMANDER_NOTRACE,
        LOCALIZED_COMMANDER_TRACE);

    m_PauseButton = new CCommanderButton(
        this,
        ID_COMMANDER_PAUSE,
        LOCALIZED_COMMANDER_PAUSE);

    m_StatusButton = new CCommanderToggleButton(
        this,
        ID_COMMANDER_STATUS,
        LOCALIZED_COMMANDER_NOSTATUS,
        LOCALIZED_COMMANDER_STATUS);

    m_StepButton = new CCommanderToggleButton(
        this,
        ID_COMMANDER_STEP,
        LOCALIZED_COMMANDER_UNSTEP,
        LOCALIZED_COMMANDER_STEP);

    m_ResetButton = new CCommanderButton(
        this,
        ID_COMMANDER_RESET,
        LOCALIZED_COMMANDER_RESET);

    m_ExecuteButton = new CCommanderButton(
        this,
        ID_COMMANDER_EXECUTE,
        LOCALIZED_COMMANDER_EXECUTE);

    m_EdallButton = new CCommanderButton(
        this,
        ID_COMMANDER_EDALL,
        LOCALIZED_COMMANDER_EDALL);

    // set the button font to be 10 points
    wxFont buttonFont = m_HaltButton->GetFont();
    buttonFont.SetPointSize(10);

    m_HaltButton->SetFont(buttonFont);
    m_TraceButton->SetFont(buttonFont);
    m_PauseButton->SetFont(buttonFont);
    m_StatusButton->SetFont(buttonFont);
    m_StepButton->SetFont(buttonFont);
    m_ResetButton->SetFont(buttonFont);
    m_ExecuteButton->SetFont(buttonFont);
    m_EdallButton->SetFont(buttonFont);

    // Pick a good size for the buttons.
    // The rest will be re-sized to match it
    m_TraceButton->SetSize(0, 0, 100, 20);

    m_NextInstructionHeight = 10 * BaseUnitsy / 8;
    m_ButtonWidth           = 34 * BaseUnitsx / 4;

    // set the font to whatever is defined in the configuraton
    wxFont font;
    font.SetFamily(wxFONTFAMILY_TELETYPE); // default to using a fixed-width font
    GetConfigurationFont("CommanderFont", font);
    UpdateFont(font);


    // calculate the desired width for the buttons
    // by iterating through all labels that we put on buttons 
    // and figuring out the length of the longest one.
    const char * buttonLabels[] = {
        LOCALIZED_COMMANDER_HALT,
        LOCALIZED_COMMANDER_TRACE,
        LOCALIZED_COMMANDER_NOTRACE,
        LOCALIZED_COMMANDER_PAUSE,
        LOCALIZED_COMMANDER_STATUS,
        LOCALIZED_COMMANDER_NOSTATUS,
        LOCALIZED_COMMANDER_STEP,
        LOCALIZED_COMMANDER_UNSTEP,
        LOCALIZED_COMMANDER_RESET,
        LOCALIZED_COMMANDER_EXECUTE,
        LOCALIZED_COMMANDER_EDALL,
    };

    int largestWidth  = 0;
    int largestHeight = 0;

    for (size_t i = 0; i < ARRAYSIZE(buttonLabels); i++)
    {
        int  buttonWidth;
        int  buttonHeight;

        m_EdallButton->GetTextExtent(
            WXSTRING(buttonLabels[i]),
            &buttonWidth,
            &buttonHeight);
        if (largestWidth < buttonWidth)
        {
            largestWidth = buttonWidth;
        }

        if (largestHeight < buttonHeight)
        {
            largestHeight = buttonHeight;
        }
    }

    m_ButtonWidth  = largestWidth  + 20;
    m_ButtonHeight = largestHeight + 8;

    // now, update the state of all the toggle buttons
    UpdateStepButtonState();
    UpdateStatusButtonState();
    UpdateTraceButtonState();

    // Configure the keyboard shortcuts
    wxAcceleratorEntry acceleratorEntries[1];

    // Ctrl+D is identical to EDALL
    acceleratorEntries[0].Set(wxACCEL_CTRL, 'D', ID_COMMANDER_EDALL);

    wxAcceleratorTable acceleratorTable(
        ARRAYSIZE(acceleratorEntries),
        acceleratorEntries);

    SetAcceleratorTable(acceleratorTable);
}

CCommander::~CCommander()
{
}

void CCommander::ChooseNewFont()
{
    wxFontDialog fontChooser;

    // Seed the font picker with the current configuration
    wxFont currentCommanderFont;
    currentCommanderFont.SetFamily(wxFONTFAMILY_TELETYPE);
    GetConfigurationFont("CommanderFont", currentCommanderFont);
    fontChooser.GetFontData().SetInitialFont(currentCommanderFont);

    // Show the font picker
    int rval = fontChooser.ShowModal();
    if (rval == wxID_OK)
    {
        // Get the font which the user selected.
        const wxFont & newCommanderFont = fontChooser.GetFontData().GetChosenFont();

        // Save the new font preference to persistent storage.
        SetConfigurationFont("CommanderFont", newCommanderFont);

        // Update the font which the UI is using.
        UpdateFont(newCommanderFont);

        // Resize the UI controls to account for the new font.
        RecalculateLayout();
        Refresh(true);
    }
}

void CCommander::UpdateStepButtonState()
{
    m_StepButton->SetPressedState(stepflag);
}


CCommanderHistory * CCommander::GetHistory()
{
    return m_History;
}

CCommanderInput * CCommander::GetInput()
{
    return m_NextInstruction;
}

wxButton * CCommander::GetEdallButton()
{
    return m_EdallButton;
}

void CCommander::UpdateTraceButtonState()
{
    m_TraceButton->SetPressedState(traceflag);
}

void CCommander::UpdateStatusButtonState()
{
    bool isShowing = CFmsLogo::GetMainFrame()->StatusDialogIsShowing();
    m_StatusButton->SetPressedState(isShowing);
}

void CCommander::Halt()
{
    // End all timers that could have been started
    // by a call to SETTIMER.
    halt_all_timers();

    // Set a flag so that the Logo engine will halt
    // when it has finished processing the current
    // instruction.
    if (is_executing())
    {
        IsTimeToHalt = true;
    }
}

void CCommander::OnHaltButton(wxCommandEvent& WXUNUSED(Event))
{
    Halt();
}

void CCommander::OnTraceButton(wxCommandEvent& WXUNUSED(Event))
{
    // toggle trace state 
    traceflag = !traceflag;
    UpdateTraceButtonState();
}

void CCommander::OnPauseButton(wxCommandEvent& WXUNUSED(Event))
{
    // If it's ok to halt then it's ok to pause.
    if (is_executing())
    {
        IsTimeToPause = true;
    }
}

void CCommander::OnStatusButton(wxCommandEvent& WXUNUSED(Event))
{
    CMainFrame * mainFrame = CFmsLogo::GetMainFrame();
    if (mainFrame->StatusDialogIsShowing())
    {
        // the status dialog is currently showing, so we want to hide it.
        mainFrame->HideStatus();
    }
    else
    {
        // the status dialog is not showing, so we want to show it.
        mainFrame->ShowStatus();
        m_StatusButton->SetFocus();
    }
    UpdateStatusButtonState();
}

void CCommander::ToggleStep()
{
    // Toggle the single-step state
    stepflag = !stepflag;
    UpdateStepButtonState();
}

void CCommander::OnStepButton(wxCommandEvent& WXUNUSED(Event))
{
    ToggleStep();
}

void CCommander::OnResetButton(wxCommandEvent& WXUNUSED(Event))
{
    // run 'CLEARSCREEN' and return focus
    char instruction[MAX_BUFFER_SIZE];
   
    cap_strnzcpy(
        instruction,
        LOCALIZED_ALTERNATE_CLEARSCREEN, 
        STRINGLENGTH(LOCALIZED_ALTERNATE_CLEARSCREEN));
    
    RunLogoInstructionFromGui(instruction);
}

void clearcombobox()
{
    // clear the recall box
    CCommanderHistory * commanderHistory = CFmsLogo::GetMainFrame()->GetCommander()->GetHistory();

    commanderHistory->Clear();
}

// Appends "str" to the end of the what is in the Commander's Recall box.
// If "str" doesn't fit, then some text will be removed from the top to make it fit.
void putcombobox(const char *str)
{
    // Check that the commander's history field is ready for input.
    if (g_IsOkayToUseCommanderWindow)
    {
        CCommanderHistory * commanderHistory = CFmsLogo::GetMainFrame()->GetCommander()->m_History;

        // REVISIT: This looping logic was taken from MSWLogo and I'm
        // not sure that it works in wxWidgets.  There might be a more
        // direct way to handle out-of-memory errors.
        for (int i = 0; i < 16; i++)
        {
            // remember where we started
            wxTextPos uBefore = commanderHistory->GetLastPosition();

            // Output to commander history.
            // Don't append the empty string because that results in appending
            // a newline.  When combined with the newline that gets added
            // below, this would have the side-effect of inserting two lines.
            if (str != NULL && str[0] != '\0')
            {
                commanderHistory->AppendText(WXSTRING(str));
            }

            // Append the newline
            wxTextPos uCheck = commanderHistory->GetLastPosition();
            commanderHistory->AppendText(WXSTRING("\n"));
            wxTextPos uAfter = commanderHistory->GetLastPosition();

            // if the newline was inserted ok, get out
            if (uCheck + 1 == uAfter)
            {
                commanderHistory->ShowPosition(uAfter);
                return;
            }

            // strip what we inserted
            commanderHistory->SetEditable(true);

            wxRichTextRange addedRange(uBefore, uAfter);
            commanderHistory->DeleteSelection();

            // Strip 4k off top
            wxRichTextRange rangeToRemove(0, 4096);
            commanderHistory->Delete(rangeToRemove);
        }

        // If all else fails try erasing everything.
        // We should never get here.
        commanderHistory->SetValue(WXSTRING(str));
    }
}


// Process a Logo instruction, as it is processed by the GUI when you click
// on the "Execute" button.  This can be used by other UI elements, such as
// the "Reset" button, to teach the user what a UI element is doing.
void
RunLogoInstructionFromGui(
    char * LogoInstruction
    )
{
    if (LogoInstruction[0] != '\0')
    {
        // The instruction is real.  Do something with it.

        // copy to list box for command recall
        putcombobox(LogoInstruction);

        // if dribble then dribble 
        if (dribblestream != NULL)
        {
            fprintf(dribblestream, "%s\n", LogoInstruction);
        }

        // reset erract loop error history
        clear_is_running_erract_flag();

        // reset evaluation counter (call counter) and execute
        eval_count = 0;
        update_status_evals();

        vector_count = 0;
        update_status_vectors();

        do_execution(LogoInstruction);
    }
}

void CCommander::Execute()
{
    // read what's in the input control
    wxString logoInstruction(m_NextInstruction->GetValue());

    // clear the input control, now that we have read its contents
    m_NextInstruction->Clear();

    // BUG: This can potentially modify the contents of wxString's buffer
    RunLogoInstructionFromGui(const_cast<char*>(WXSTRING_TO_STRING(logoInstruction)));
}

void CCommander::OnExecuteButton(wxCommandEvent& WXUNUSED(Event))
{
    Execute();
}

void CCommander::OnEdallButton(wxCommandEvent& WXUNUSED(Event))
{
    // use a local buffer because do_execution can modify its parameter
    char command[] = "EDALL";
    do_execution(command);
}

void CCommander::OnEnter(wxCommandEvent & Event)
{
    if (is_executing())
    {
#ifndef WX_PURE
        // For compatibility with MSWLogo, simply beep if Logo is currently
        // running when the user presses Enter.  It might be preferable to
        // run the command anyway, but that was too significant a change for
        // a micro release.
        MessageBeep(MB_OK);
#endif // WX_PURE
    }
    else
    {
        Execute();
    }
}

CCommander * CCommander::GetCommander()
{
    return this;
}

const wxSize CCommander::GetRecommendedMinimumSize() const
{
    const int x_border = 4;
    const int y_border = 4;
    const int padding  = 6;

    const int minHistoryWidth = 100;

    const int minX = 
        x_border + 
        minHistoryWidth +
        padding +
        m_ButtonWidth +
        m_ButtonWidth +
        x_border;

    // height of one of the columns with buttons
    const int minButtonY =
        y_border +
        m_ButtonHeight * 4 +
        y_border;

    // height of the history/input column,
    // assuming history shows at least two rows
    const int minHistoryY =
        y_border +
        m_NextInstructionHeight * 2 +
        padding +
        m_NextInstructionHeight +
        y_border;

    return wxSize(
        minX,
        std::max(minButtonY, minHistoryY));
}

void CCommander::RecalculateLayout()
{
    // NOTE: This cannot use a wxSizer because different localized
    // versions of FMSLogo use different lengths of text for the buttons.
    // The problems:
    // 1) All buttons must be the same size, so the wxBoxSizer is inadequate.
    // 2) There must be a variable amount of space between the first three
    //    buttons and the fourth button in each column. This makes the
    //    wxGridSizer inadequate.
    // 3) The toggle buttons can change their text, but should be sized for
    //    the longer of the two text possibilities.

    // scale and pos. each sub-window in commander window based on its size
    const wxSize commanderSize = GetClientSize();

    const int total_width   = commanderSize.GetWidth();
    const int total_height  = commanderSize.GetHeight();
    const int button_height = m_ButtonHeight;
    const int button_width  = m_ButtonWidth;

    const int x_border = 4;
    const int y_border = 4;
    const int padding  = 6;

    m_EdallButton->SetSize(
        total_width - button_width * 1 - x_border, 
        total_height - button_height - y_border, 
        button_width, 
        button_height);

    m_ExecuteButton->SetSize(
        total_width - button_width * 2 - x_border, 
        total_height - button_height - y_border, 
        button_width, 
        button_height);

    m_ResetButton->SetSize(
        total_width - button_width * 1 - x_border, 
        button_height * 2 + y_border, 
        button_width, 
        button_height);

    m_StepButton->SetSize(
        total_width - button_width * 2 - x_border,
        button_height * 2 + y_border,
        button_width,
        button_height);

    m_StatusButton->SetSize(
        total_width - button_width * 1 - x_border, 
        button_height * 1 + y_border, 
        button_width, 
        button_height);

    m_PauseButton->SetSize( 
        total_width - button_width * 2 - x_border,
        button_height * 1 + y_border,
        button_width,
        button_height);

    m_TraceButton->SetSize(
        total_width - button_width * 1 - x_border, 
        button_height * 0 + y_border, 
        button_width, 
        button_height);

    m_HaltButton->SetSize( 
        total_width - button_width * 2 - x_border,
        button_height * 0 + y_border,
        button_width,
        button_height);

    m_NextInstruction->SetSize(
        x_border,
        total_height - m_NextInstructionHeight - y_border,
        total_width - button_width * 2 - x_border - padding,
        m_NextInstructionHeight);

    m_History->SetSize(
        x_border, 
        0,
        total_width - button_width * 2 - x_border - padding, 
        total_height - m_NextInstructionHeight - padding);
}

void
CCommander::UpdateFont(const wxFont & NewFont)
{
    m_History->SetFont(NewFont);
    m_NextInstruction->SetFont(NewFont);

    int width;
    int height;
    m_NextInstruction->GetTextExtent(WXSTRING("Tg"), &width, &height);

    // font height + some padding
    m_NextInstructionHeight = height + 10;
}

void CCommander::OnSize(wxSizeEvent& Event)
{
    RecalculateLayout();
    Event.Skip();
}

void CCommander::ProcessKeyDownEventAtInputControl(wxKeyEvent& Event)
{
    int keyCode = Event.GetKeyCode();

    // Special case for redirecting the right-arrow key press:
    // Move the insertion point to the far left for compatability
    // with the OWL-based FMSLogo.
    if (keyCode == WXK_RIGHT || keyCode == WXK_NUMPAD_RIGHT)
    {
        m_NextInstruction->SetInsertionPoint(0);
    }
    m_NextInstruction->SetFocus();
    m_NextInstruction->EmulateKeyPress(Event);
}

void CCommander::GiveControlToInputBox()
{
    // Give focus to the input edit control
    m_NextInstruction->SetFocus();
}

void CCommander::GiveControlToHistoryBox()
{
    // advance to the bottom of the listbox
    m_History->MoveEnd();
    wxTextPos endPosition = m_History->GetLastPosition();
    m_History->ShowPosition(endPosition);

    // give focus to the listbox
    m_History->SetFocus();
}

void
CCommander::AppendToCommanderHistory(
    const char * String
    )
{
    // Append the string to the buffer
    g_HistoryBuffer.AppendString(String);

    // process lines
    char * rawBuffer       = g_HistoryBuffer.GetBuffer();
    size_t rawBufferLength = g_HistoryBuffer.GetBufferLength();

    char * next_line = rawBuffer;
    for (size_t i = 0; i < rawBufferLength; i++)
    {
        if (rawBuffer[i] == '\n')
        {
            // if <lf> pump it out
            rawBuffer[i] = '\0';
            putcombobox(next_line);
            rawBuffer[i] = '\n';
            next_line = &rawBuffer[i + 1];
        }
    }

    // flush the last line (which doesn't end in \n)
    if (next_line[0] != '\0')
    {
        putcombobox(next_line);
    }

    // clear the contents of the buffer, since we wrote the entire thing
    g_HistoryBuffer.Empty();
}

void
CCommander::AppendToCommanderHistory(
    char Char
    )
{
    if (Char == '\n')
    {
        // if <lf> pump it out
        putcombobox(g_HistoryBuffer.GetBuffer());
        g_HistoryBuffer.Empty();
    }
    else
    {
        g_HistoryBuffer.AppendChar(Char);
    }
}

BEGIN_EVENT_TABLE(CCommander, wxPanel)
    EVT_BUTTON(ID_COMMANDER_HALT,    CCommander::OnHaltButton)
    EVT_BUTTON(ID_COMMANDER_PAUSE,   CCommander::OnPauseButton)
    EVT_BUTTON(ID_COMMANDER_RESET,   CCommander::OnResetButton)
    EVT_BUTTON(ID_COMMANDER_EXECUTE, CCommander::OnExecuteButton)
    EVT_BUTTON(ID_COMMANDER_EDALL,   CCommander::OnEdallButton)
    EVT_TOGGLEBUTTON(ID_COMMANDER_TRACE,   CCommander::OnTraceButton)
    EVT_TOGGLEBUTTON(ID_COMMANDER_STATUS,  CCommander::OnStatusButton)
    EVT_TOGGLEBUTTON(ID_COMMANDER_STEP,    CCommander::OnStepButton)
    EVT_TEXT_ENTER(ID_COMMANDER_NEXTINSTRUCTION, CCommander::OnEnter)
    EVT_SIZE(CCommander::OnSize)
END_EVENT_TABLE()

// ----------------------------------------------------------------------------
// CCommanderDialog
// ----------------------------------------------------------------------------

CCommanderDialog::CCommanderDialog(
    wxWindow   * Parent,
    CCommander * CommanderPanel
    ) :
    wxDialog(
        Parent,
        wxID_ANY,
        WXSTRING(LOCALIZED_COMMANDER),
        wxDefaultPosition,
        wxDefaultSize,
#ifdef __WXMSW__
        wxDEFAULT_DIALOG_STYLE | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxRESIZE_BORDER)
#else
        wxCAPTION | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxRESIZE_BORDER)
#endif
{
    // Put the commander inside the dialog box
    wxSizer * sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(CommanderPanel, 1, wxEXPAND);
    SetSizer(sizer);

    // Set the minimum size based on what's recommended to show
    // all of the controls in the commander.
    SetMinSize(ClientToWindowSize(CommanderPanel->GetRecommendedMinimumSize()));

    // Configure the keyboard shortcuts
    wxAcceleratorEntry acceleratorEntries[1];

    // Ctrl+Tab navigates to the next window.
    acceleratorEntries[0].Set(wxACCEL_CTRL, WXK_TAB, ID_COMMANDER_NEXT_WINDOW);

    wxAcceleratorTable acceleratorTable(
        ARRAYSIZE(acceleratorEntries),
        acceleratorEntries);

    SetAcceleratorTable(acceleratorTable);
}

void CCommanderDialog::OnClose(wxCloseEvent& Event)
{
    // Veto whenever possible so that we don't ever
    // close this dialog by user interaction.
    if (Event.CanVeto())
    {
        Event.Veto();
    }
    else
    {
        Event.Skip();
    }
}

void CCommanderDialog::OnNavigateNextWindow(wxCommandEvent& Event)
{
    CFmsLogo::GetMainFrame()->KeyboardNavigateTopLevelWindow(
        this,
        wxNavigationKeyEvent::IsForward);
}

BEGIN_EVENT_TABLE(CCommanderDialog, wxDialog)
    EVT_CLOSE(CCommanderDialog::OnClose)
    EVT_MENU(ID_COMMANDER_NEXT_WINDOW, CCommanderDialog::OnNavigateNextWindow)
END_EVENT_TABLE()
