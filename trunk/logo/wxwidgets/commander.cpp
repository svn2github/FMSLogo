#include <windows.h>

#include "commander.h"

#include "wx/msgdlg.h"
#include "wx/button.h"
#include "wx/sizer.h"

#include "wx/richtext/richtextctrl.h"

#include "localizedstrings.h"
#include "utils.h"
#include "logocore.h"


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

CCommander::CCommander(wxWindow *parent)
   : wxWindow(parent, wxID_ANY)
{

    m_History = new wxRichTextCtrl(this, ID_COMMANDER_HISTORY);

    m_NextInstruction = new wxTextCtrl(this, ID_COMMANDER_NEXTINSTRUCTION);

    m_HaltButton    = new wxButton(this, ID_COMMANDER_HALT,    LOCALIZED_COMMANDER_HALT);
    m_TraceButton   = new wxButton(this, ID_COMMANDER_TRACE,   LOCALIZED_COMMANDER_TRACE);
    m_PauseButton   = new wxButton(this, ID_COMMANDER_PAUSE,   LOCALIZED_COMMANDER_PAUSE);
    m_StatusButton  = new wxButton(this, ID_COMMANDER_STATUS,  LOCALIZED_COMMANDER_STATUS);
    m_StepButton    = new wxButton(this, ID_COMMANDER_STEP,    LOCALIZED_COMMANDER_STEP);
    m_ResetButton   = new wxButton(this, ID_COMMANDER_RESET,   LOCALIZED_COMMANDER_RESET);
    m_ExecuteButton = new wxButton(this, ID_COMMANDER_EXECUTE, LOCALIZED_COMMANDER_EXECUTE);
    m_EdallButton   = new wxButton(this, ID_COMMANDER_EDALL,   LOCALIZED_COMMANDER_EDALL);

    // Pick a good size for the buttons.
    // The rest will be re-sized to match it
    m_TraceButton->SetSize(0, 0, 100, 20);

    // HACK: should be:
    //  m_NextInstructionHeight(10 * BaseUnitsy / 8),
    //  m_ButtonWidth(34 * BaseUnitsx / 4)
    m_NextInstructionHeight = 10;
    m_ButtonWidth           = 100;


    LOGFONT nativeFont;
    GetConfigurationFont("CommanderFont", nativeFont);

    // note: this was copied from wxNativeFontInfo::ToString() in src/msw/font.cpp
    wxString nativeInfo;
    nativeInfo.Printf(
        "%d;%ld;%ld;%ld;%ld;%ld;%d;%d;%d;%d;%d;%d;%d;%d;%s",
        0, // version
        nativeFont.lfHeight,
        nativeFont.lfWidth,
        nativeFont.lfEscapement,
        nativeFont.lfOrientation,
        nativeFont.lfWeight,
        nativeFont.lfItalic,
        nativeFont.lfUnderline,
        nativeFont.lfStrikeOut,
        nativeFont.lfCharSet,
        nativeFont.lfOutPrecision,
        nativeFont.lfClipPrecision,
        nativeFont.lfQuality,
        nativeFont.lfPitchAndFamily,
        nativeFont.lfFaceName);

    wxFont font;
    font.SetNativeFontInfo(nativeInfo);
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

    int longestWidth = 0;

    for (size_t i = 0; i < ARRAYSIZE(buttonLabels); i++)
    {
        int  buttonWidth;
        int  buttonHeight;

        m_EdallButton->GetTextExtent(
            buttonLabels[i],
            &buttonWidth,
            &buttonHeight);
        if (longestWidth < buttonWidth)
        {
            longestWidth = buttonWidth;
        }
    }

    m_ButtonWidth = longestWidth + 20;
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
    wxMessageBox(
        "Trace button pressed", 
        "Info",
        wxOK | wxICON_INFORMATION, 
        this);
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
    wxMessageBox(
        "Status button pressed", 
        "Info",
        wxOK | wxICON_INFORMATION, 
        this);
}

void CCommander::OnStepButton(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(
        "Step button pressed", 
        "Info",
        wxOK | wxICON_INFORMATION, 
        this);
}

void CCommander::OnResetButton(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(
        "Reset button pressed", 
        "Info",
        wxOK | wxICON_INFORMATION, 
        this);
}

void CCommander::OnExecuteButton(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(
        "Execute button pressed", 
        "Info",
        wxOK | wxICON_INFORMATION, 
        this);
}

void CCommander::OnEdallButton(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(
        "Edall button pressed",
        "Info",
        wxOK | wxICON_INFORMATION, 
        this);
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

void CCommander::RecalculateLayout()
{
    // scale and pos. each sub-window in commander window based on its size
    const wxSize buttonSize    = m_TraceButton->GetClientSize();

    const wxSize commanderSize = GetClientSize();

    const int total_width   = commanderSize.GetWidth();
    const int total_height  = commanderSize.GetHeight();
    const int button_height = buttonSize.GetHeight();
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

BEGIN_EVENT_TABLE(CCommander, wxWindow)
    EVT_BUTTON(ID_COMMANDER_HALT,    CCommander::OnHaltButton)
    EVT_BUTTON(ID_COMMANDER_TRACE,   CCommander::OnTraceButton)
    EVT_BUTTON(ID_COMMANDER_PAUSE,   CCommander::OnPauseButton)
    EVT_BUTTON(ID_COMMANDER_STATUS,  CCommander::OnStatusButton)
    EVT_BUTTON(ID_COMMANDER_STEP,    CCommander::OnStepButton)
    EVT_BUTTON(ID_COMMANDER_RESET,   CCommander::OnResetButton)
    EVT_BUTTON(ID_COMMANDER_EXECUTE, CCommander::OnExecuteButton)
    EVT_BUTTON(ID_COMMANDER_EDALL,   CCommander::OnEdallButton)
    EVT_SIZE(                        CCommander::OnSize)
END_EVENT_TABLE()
