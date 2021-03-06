#ifdef __WXMSW__
#  include <windows.h>  // for LOGFONT
#endif

#include "commander.h"

#include <wx/msgdlg.h>
#include <wx/sizer.h>
#include <wx/defs.h>
#include <wx/richtext/richtextctrl.h>

#include "fmslogo.h"
#include "mainframe.h"
#include "statusdialog.h"
#include "workspaceeditor.h"
#include "localizedstrings.h"
#include "utils.h"
#include "logocore.h"
#include "commanderbutton.h"
#include "commandertogglebutton.h"
#include "commanderinput.h"
#include "commanderhistory.h"
#include "dynamicbuffer.h"
#include "fontutils.h"

bool g_GiveFocusToInputControl = false;
bool g_IsOkayToUseCommanderWindow = true;

bool g_StepFlag   = false;
bool g_TraceFlag  = false;

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

    m_ExecuteButton->SetDefault();

    // Pick a good size for the buttons.
    // The rest will be re-sized to match it
    m_TraceButton->SetSize(0, 0, 100, 20);

    // HACK: should be:
    //  m_NextInstructionHeight(10 * BaseUnitsy / 8),
    //  m_ButtonWidth(34 * BaseUnitsx / 4)
    m_NextInstructionHeight = 10;
    m_ButtonWidth           = 100;


    // set the font to whatever is defind in the configuraton
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
            buttonLabels[i],
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
}

void CCommander::UpdateStepButtonState()
{
    m_StepButton->SetPressedState(g_StepFlag);
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
    m_TraceButton->SetPressedState(g_TraceFlag);
}

void CCommander::UpdateStatusButtonState()
{
    bool isShowing = CFmsLogo::GetMainFrame()->StatusDialogIsShowing();
    m_StatusButton->SetPressedState(isShowing);
}

void CCommander::OnHaltButton(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(
        "Halt button pressed", 
        "Info",
        wxOK | wxICON_INFORMATION, 
        this);
}

void CCommander::OnTraceButton(wxCommandEvent& WXUNUSED(event))
{
    // toggle trace state 
    g_TraceFlag = !g_TraceFlag;
    UpdateTraceButtonState();

    m_NextInstruction->SetFocus();
}

void CCommander::OnPauseButton(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(
        "Pause button pressed", 
        "Info",
        wxOK | wxICON_INFORMATION, 
        this);
}

void CCommander::OnStatusButton(wxCommandEvent& WXUNUSED(event))
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
    }
    UpdateStatusButtonState();
    m_NextInstruction->SetFocus();
}

void CCommander::OnStepButton(wxCommandEvent& WXUNUSED(event))
{
    // toggle yield state
    g_StepFlag = !g_StepFlag;
    UpdateStepButtonState();

    m_NextInstruction->SetFocus();
}

void CCommander::OnResetButton(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(
        "Reset button pressed", 
        "Info",
        wxOK | wxICON_INFORMATION, 
        this);
}

void
do_execution(
    const char * LogoInstruction
    )
{
    wxString message;
    message.Printf("Running %s\n", LogoInstruction);
    //wxMessageBox(message, "TODO: Logo Engine", wxOK);
}

void clearcombobox()
{
    // clear the recall box
    CCommanderHistory * commanderHistory = CFmsLogo::GetMainFrame()->GetCommander()->m_History;

    commanderHistory->Clear();

    // TODO: is it necessary to move the position
    // commanderHistory->MoveEnd();
}

// Appends "str" to the end of the what is in the Commander's Recall box.
// If "str" doesn't fit, then some text will be removed from the top to make it fit.
void putcombobox(const char *str)
{
    // only if OK to write to recall box do we do it
    if (g_IsOkayToUseCommanderWindow)
    {
        CCommanderHistory * commanderHistory = CFmsLogo::GetMainFrame()->GetCommander()->m_History;

        for (int i = 0; i < 16; i++)
        {
            // remember where we started
            wxTextPos uBefore = commanderHistory->GetLastPosition();

            // output to list box 
            commanderHistory->AppendText(str);
            wxTextPos uCheck = commanderHistory->GetLastPosition();
            commanderHistory->AppendText("\n");
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

            // strip 4k off top
            wxRichTextRange rangeToRemove(0, 4096);
            commanderHistory->Delete(rangeToRemove);

            commanderHistory->SetEditable(false);
        }

        // If all else fails try erasing everything.
        // we should never get here.
        clearcombobox();
        commanderHistory->AppendText(str);
        commanderHistory->AppendText("\n");
    }
}


// Process a Logo instruction, as it is processed by the GUI when you click
// on the "Execute" button.  This can be used by other UI elements, such as
// the "Reset" button, to teach the user what a UI element is doing.
void
RunLogoInstructionFromGui(
    const char * LogoInstruction
    )
{
    if (LogoInstruction[0] != '\0')
    {
        // The instruction is real.  Do something with it.

        // copy to list box for command recall
        putcombobox(LogoInstruction);

#if 0
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
#endif

        do_execution(LogoInstruction);
    }
}

void CCommander::OnExecuteButton(wxCommandEvent& WXUNUSED(event))
{
    g_GiveFocusToInputControl = true;

    // read what's in the input control
    const wxString logoInstruction(m_NextInstruction->GetValue());

    // clear the input control, now that we have read its contents
    m_NextInstruction->Clear();

    RunLogoInstructionFromGui(logoInstruction.c_str());

    // calling RunLogoInstructionFromGui() can delete the "this" pointer,
    // if it executes FULLSCREEN, TEXTSCREEN, or SPLITSCREEN.
    // Therefore, we must not touch any member variable at this point.
    if (g_GiveFocusToInputControl)
    {
        CFmsLogo::GetMainFrame()->GetCommander()->m_NextInstruction->SetFocus();
    }
}

void CCommander::OnEdallButton(wxCommandEvent& WXUNUSED(event))
{
    CMainFrame * mainFrame = CFmsLogo::GetMainFrame();

    CWorkspaceEditor * editor = mainFrame->GetWorkspaceEditor();
    if (editor == NULL)
    {
        // create an editor
        editor = mainFrame->CreateWorskpaceEditor();
    }

    // make sure that the editor is visible
    editor->Iconize(false);
    editor->Show();
    editor->Raise();
}

void CCommander::OnClose(wxCloseEvent& event)
{
    if ( event.CanVeto() )
    {
        wxMessageBox(_T("Use the menu item to close this dialog"),
                     _T("Modeless dialog"),
                     wxOK | wxICON_INFORMATION, this);

        event.Veto();
    }
}

CCommander * CCommander::GetCommander()
{
    return this;
}

void CCommander::RecalculateLayout()
{
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
    m_NextInstruction->GetTextExtent("Tg", &width, &height);

    // font height + some padding
    m_NextInstructionHeight = height + 10;
}

void CCommander::OnSize(wxSizeEvent& event)
{
    RecalculateLayout();
}


// TODO: rename so that it doesn't have "post" in it
void CCommander::PostKeyDownToInputControl(wxKeyEvent& Event)
{
    fprintf(stderr, "PostKeyDownToInputControl() called\n");
    m_NextInstruction->SetFocus();
    m_NextInstruction->EmulateKeyPress(Event);
}

void CCommander::OnKeyDown(wxKeyEvent& Event)
{
    if (m_NextInstruction->WantsKeyEvent(Event.GetKeyCode()))
    {
        PostKeyDownToInputControl(Event);
    }
    else
    {
        fprintf(stderr, "skipping keydown event on CCommander\n");
        Event.Skip();
    }
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
    EVT_SIZE(CCommander::OnSize)
    EVT_KEY_DOWN(CCommander::OnKeyDown)
END_EVENT_TABLE()

// ----------------------------------------------------------------------------
// CCommanderDialog
// ----------------------------------------------------------------------------

CCommanderDialog::CCommanderDialog(wxWindow * Parent)
    : wxDialog(
        Parent,
        wxID_ANY,
        wxString(LOCALIZED_COMMANDER),
        wxDefaultPosition,
        wxDefaultSize,
#ifdef __WXMSW__
        wxDEFAULT_DIALOG_STYLE | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxRESIZE_BORDER)
#else
        wxCAPTION | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxRESIZE_BORDER)
#endif
{
    m_Commander = new CCommander(this);


#ifdef __WXMSW__ // utils.cpp only builds on Windows

    // restore the commander window's height
    int x      = 0;
    int y      = 0;
    int width  = 0;
    int height = 0;
    GetConfigurationQuadruple("Commander", &x, &y, &width, &height);
    SetSize(x, y, width, height);
#endif

    wxSizer * sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(m_Commander, 0, wxEXPAND);

    SetSizer(sizer);
    sizer->Fit(this);
}

CCommander * CCommanderDialog::GetCommander()
{
    return m_Commander;
}

void CCommanderDialog::OnSize(wxSizeEvent& event)
{
    int width;
    int height;
    GetClientSize(&width, &height);

    m_Commander->SetSize(width, height);
}

void CCommanderDialog::OnClose(wxCloseEvent& event)
{
    if (event.CanVeto())
    {
        event.Veto();
    }
    else
    {
        // Save the location and size of our window so we can
        // come back up in the same spot next time we are invoked.
        if (!IsIconized())
        {
            const wxRect windowRectangle = GetRect();

            SetConfigurationQuadruple(
                "Commander",
                windowRectangle.GetLeft(),
                windowRectangle.GetTop(),
                windowRectangle.GetWidth(),
                windowRectangle.GetHeight());
        }
        Destroy();
    }
}

BEGIN_EVENT_TABLE(CCommanderDialog, wxDialog)
    EVT_SIZE(CCommanderDialog::OnSize)
    EVT_CLOSE(CCommanderDialog::OnClose)
END_EVENT_TABLE()
