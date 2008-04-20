#include "statusdialog.h"

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/statbox.h>

#include "commander.h"
#include "fmslogo.h"
#include "mainframe.h"
#include "localizedstrings.h"
#include "logocore.h" // for ARRAYSIZE
#include "utils.h"

// Menu IDs
enum
{
   ID_STATUS_CONTACT = wxID_HIGHEST,
   ID_STATUS_PENCOLOR,
   ID_STATUS_FLOODCOLOR,
   ID_STATUS_SCREENCOLOR,
   ID_STATUS_PALETTE,
   ID_STATUS_WIDTH,
   ID_STATUS_VISIBILITY,
   ID_STATUS_STYLE,
   ID_STATUS_HEADING,
   ID_STATUS_PITCH,
   ID_STATUS_ROLL,
   ID_STATUS_PEN,
   ID_STATUS_ORIENTATION,
   ID_STATUS_TURTLE,
   ID_STATUS_COLOR,
   ID_STATUS_KERNEL,
   ID_STATUS_CALLS,
   ID_STATUS_PEAKMEMORY,
};

// ----------------------------------------------------------------------------
// CStatusDialog
// ----------------------------------------------------------------------------

CStatusDialog::CStatusDialog(wxWindow * Parent)
    : wxDialog(
        Parent, 
        wxID_ANY, 
        wxString(LOCALIZED_STATUS), 
        wxDefaultPosition, 
        wxDefaultSize, 
        wxCAPTION | wxCLOSE_BOX | wxSYSTEM_MENU)
{
#ifdef __WXMSW__ // utils.cpp only builds on Windows

    // build default coords
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    // Get last location and size of command window from configuration settings.
    GetConfigurationQuadruple("Status", &x, &y, &w, &h); 
    // TODO: checkwindow(&x, &y, &w, &h);

    // now set position
    Move(x, y);
#endif

    struct STATICBOX
    {
        const char *        Category;
        const char *        FieldName[4];
        wxStaticText * *    FieldValue[4];
    } data[] = {
        {
            LOCALIZED_STATUS_PEN,
            {
                LOCALIZED_STATUS_CONTACT,
                LOCALIZED_STATUS_WIDTH, 
                LOCALIZED_STATUS_STYLE,
            },
            {
                &m_PenContact,
                &m_PenWidth,
                &m_PenStyle,
            },
        },
        {
            LOCALIZED_STATUS_ORIENTATION,
            {
                LOCALIZED_STATUS_HEADING,
                LOCALIZED_STATUS_PITCH, 
                LOCALIZED_STATUS_ROLL,
            },
            {
                &m_TurtleHeading,
                &m_TurtlePitch,
                &m_TurtleRoll,
            },
        },
        {
            LOCALIZED_STATUS_TURTLE,
            {
                LOCALIZED_STATUS_POSITION,
                LOCALIZED_STATUS_WHICH, 
                LOCALIZED_STATUS_VISIBILITY,
            },
            {
                &m_TurtlePosition,
                &m_TurtleId,
                &m_TurtleVisibility,
            },
        },
        {
            LOCALIZED_STATUS_COLOR,
            {
                LOCALIZED_STATUS_PENCOLOR,
                LOCALIZED_STATUS_FLOODCOLOR, 
                LOCALIZED_STATUS_SCREENCOLOR,
                LOCALIZED_STATUS_PALETTE,
            },
            {
                &m_PenColor,
                &m_FloodColor,
                &m_ScreenColor,
                &m_PaletteUse,
            },
        },
        {
            LOCALIZED_STATUS_KERNEL,
            {
                LOCALIZED_STATUS_CALLS,
                LOCALIZED_STATUS_PEAKMEMORY, 
                LOCALIZED_STATUS_VECTORS":",
                LOCALIZED_STATUS_POLYGONS":",
            },
            {
                &m_TotalCalls,
                &m_PeakMemory,
                &m_TotalVectors,
                &m_TotalPolygons,
            },
        },
    };

    wxBoxSizer *topLevelSizer = new wxBoxSizer(wxVERTICAL);

    for (size_t i = 0; i < ARRAYSIZE(data); i++)
    {
        wxStaticBoxSizer * staticBoxSizer = new wxStaticBoxSizer(
            wxHORIZONTAL,
            this, 
            data[i].Category);

        topLevelSizer->Add(
            staticBoxSizer, 
            0, 
            wxALIGN_CENTER | wxALL | wxEXPAND, 
            5);

        wxBoxSizer * fieldNameSizer  = new wxBoxSizer(wxVERTICAL);
        staticBoxSizer->Add(fieldNameSizer);

        wxBoxSizer * fieldValueSizer = new wxBoxSizer(wxVERTICAL);
        staticBoxSizer->Add(fieldValueSizer);

        for (size_t j = 0; j < ARRAYSIZE(data[i].FieldName); j++)
        {
            if (data[i].FieldName[j] == NULL)
            {
                // we've done all the fields for this static box
                break;
            }

            wxStaticText * fieldName = new wxStaticText(
                this,
                wxID_ANY,
                data[i].FieldName[j],
                wxDefaultPosition,
                wxDefaultSize, 
                wxALIGN_LEFT);

            fieldNameSizer->Add(
                fieldName,
                0, 
                wxEXPAND);

            wxStaticText * fieldValue = new wxStaticText(
                this,
                wxID_ANY,
                wxEmptyString,
                wxDefaultPosition,
                wxDefaultSize, 
                wxALIGN_LEFT);

            fieldValueSizer->Add(
                fieldValue,
                0, 
                wxEXPAND | wxLEFT | wxRIGHT,
                5);

            *data[i].FieldValue[j] = fieldValue;
        }
    }

    SetSizer(topLevelSizer);

    // TODO: make this dynamic
    SetPenContact(true);
    SetPenWidth(5);
    SetPenStyle("normal");
    SetTurtleHeading(90.5);
    SetTurtlePitch(0.0);
    SetTurtleRoll(0.0);
    SetTurtlePosition(100, 200, 0);
    SetTurtleId(1);
    SetTurtleVisibility(true);
    SetPenColor(0, 0, 0);
    SetFloodColor(0, 0, 0);
    SetScreenColor(255, 255, 255);
    SetPaletteUse(-1);
    SetCalls(123);
    SetPeakMemory(6000);
    SetVectors(0);
    SetPolygons(0);

    topLevelSizer->SetSizeHints(this);
    topLevelSizer->Fit(this);
}

void CStatusDialog::SetPenContact(bool PenIsUp)
{
    const char * text;

    if (PenIsUp)
    {
        text = LOCALIZED_STATUS_PENUP;
    }
    else
    {
        text = LOCALIZED_STATUS_PENDOWN;
    }

    m_PenContact->SetLabel(text);
}

void CStatusDialog::SetPenWidth(int PenWidth)
{
    wxString penWidthString;
    penWidthString.Printf("%d", PenWidth);

    m_PenWidth->SetLabel(penWidthString);
}

void CStatusDialog::SetPenStyle(const char * PenStyle)
{
    m_PenStyle->SetLabel(PenStyle);
}


void CStatusDialog::SetTurtleHeading(double Heading)
{
    wxString headingString;
    headingString.Printf("%1.2f", Heading);

    m_TurtleHeading->SetLabel(headingString);
}


void CStatusDialog::SetTurtlePitch(double Pitch)
{
    wxString pitchString;
    pitchString.Printf("%1.2f", Pitch);

    m_TurtlePitch->SetLabel(pitchString);
}

void CStatusDialog::SetTurtleRoll(double Roll)
{
    wxString rollString;
    rollString.Printf("%1.2f", Roll);

    m_TurtleRoll->SetLabel(rollString);
}

void CStatusDialog::SetTurtlePosition(double X, double Y, double Z)
{
    wxString positionString;
    positionString.Printf("%1.0f,%1.0f,%1.0f", X, Y, Z);

    m_TurtlePosition->SetLabel(positionString);
}

void CStatusDialog::SetTurtleId(int TurtleId)
{
    wxString turtleIdString;
    turtleIdString.Printf("%d", TurtleId);

    m_TurtleId->SetLabel(turtleIdString);
}

void CStatusDialog::SetTurtleVisibility(bool IsShown)
{
    const char * text;

    if (IsShown)
    {
        text = LOCALIZED_STATUS_PENSHOWN;
    }
    else
    {
        text = LOCALIZED_STATUS_PENHIDDEN;
    }

    m_TurtleVisibility->SetLabel(text);
}

void CStatusDialog::SetPenColor(int Red, int Green, int Blue)
{
    wxString colorString;
    colorString.Printf("%d,%d,%d", Red, Green, Blue);

    m_PenColor->SetLabel(colorString);
}

void CStatusDialog::SetScreenColor(int Red, int Green, int Blue)
{
    wxString colorString;
    colorString.Printf("%d,%d,%d", Red, Green, Blue);

    m_ScreenColor->SetLabel(colorString);
}

void CStatusDialog::SetFloodColor(int Red, int Green, int Blue)
{
    wxString colorString;
    colorString.Printf("%d,%d,%d", Red, Green, Blue);

    m_FloodColor->SetLabel(colorString);
}

void CStatusDialog::SetPaletteUse(int ColorsUsed)
{
    wxString paletteUseString;

    if (ColorsUsed < 0)
    {
        paletteUseString = "N/A";
    }
    else
    {
        paletteUseString.Printf("%d", ColorsUsed);
    }

    m_PaletteUse->SetLabel(paletteUseString);
}

void CStatusDialog::SetCalls(int TotalCalls)
{
    wxString totalCallsString;
    totalCallsString.Printf("%d", TotalCalls);

    m_TotalCalls->SetLabel(totalCallsString);
}

void CStatusDialog::SetPeakMemory(int TotalNodes)
{
    wxString peakMemoryString;
    peakMemoryString.Printf("%d "LOCALIZED_STATUS_NODES, TotalNodes);

    m_PeakMemory->SetLabel(peakMemoryString);
}

void CStatusDialog::SetVectors(int TotalVectors)
{
    wxString totalVectorsString;
    totalVectorsString.Printf("%d", TotalVectors);

    m_TotalVectors->SetLabel(totalVectorsString);
}

void CStatusDialog::SetPolygons(int TotalPolygons)
{
    wxString totalPolygonsString;
    totalPolygonsString.Printf("%d", TotalPolygons);

    m_TotalPolygons->SetLabel(totalPolygonsString);
}

void CStatusDialog::OnClose(wxCloseEvent& event)
{
#ifdef __WXMSW__ // utils.cpp only builds on Windows

    // Get location of our window on the screen so we can
    // come back up in the same spot next time we are invoked.

    // build default coords
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    GetPosition(&x, &y);

    // save the current location
    SetConfigurationQuadruple("Status", x, y, w, h);

#endif

    CMainFrame * mainFrame = CFmsLogo::GetMainFrame();

    mainFrame->m_StatusDialog = NULL;
    mainFrame->GetCommander()->UpdateStatusButtonState();

    Destroy();
}

BEGIN_EVENT_TABLE(CStatusDialog, wxDialog)
    EVT_CLOSE(CStatusDialog::OnClose)
END_EVENT_TABLE()

#if 0

static
void 
update_status_color_helper(
    int           ChildDialogId,
    const Color & TheColor
    )
{
    if (status_flag)
    {
        char colortext[256];

        sprintf(
            colortext,
            "%d,%d,%d",
            TheColor.red,
            TheColor.green,
            TheColor.blue);

        MainWindowx->StatusWindow->SetDlgItemText(ChildDialogId, colortext);
    }
}

void update_status_turtleposition(void)
{
    if (status_flag)
    {
        char text[256];

        sprintf(
            text,
            "%1.0f,%1.0f,%1.0f",
            g_Turtles[turtle_which].Position.x,
            g_Turtles[turtle_which].Position.y,
            g_Turtles[turtle_which].Position.z);

        MainWindowx->StatusWindow->SetDlgItemText(ID_TURTLEPOSITION, text);
    }
}


void update_status_pencolor(void)
{
    update_status_color_helper(ID_PENCOLOR, dpen);
}

void update_status_floodcolor(void)
{
    update_status_color_helper(ID_FLOODCOLOR, dfld);
}

void update_status_screencolor(void)
{
    update_status_color_helper(ID_SCREENCOLOR, dscn);
}

void update_status_paletteuse(void)
{
    if (status_flag)
    {
        char text[256];

        if (EnablePalette)
        {
            sprintf(text, "%d", MyLogPalette->palNumEntries);
        }
        else
        {
            strcpy(text, "N/A");
        }

        MainWindowx->StatusWindow->SetDlgItemText(ID_PALETTEUSE, text);
    }
}


void update_status_turtleheading(void)
{
    if (status_flag)
    {
        char text[256];
        if (current_mode == perspectivemode)
        {
            sprintf(text, "%1.2f", rotation_z());
        }
        else
        {
            sprintf(text, "%1.2f", g_Turtles[turtle_which].Heading);
        }
        MainWindowx->StatusWindow->SetDlgItemText(ID_TURTLEHEADING, text);
    }
}

void update_status_penstyle(void)
{
    if (status_flag)
    {
        // TODO: merge with get_node_pen_mode()
        const char * text;
        if (current_write_mode == XOR_PUT)
        {
            text = LOCALIZED_STATUS_PENREVERSE;
        }
        else
        {
            text = LOCALIZED_STATUS_PENNORMAL;
        }

        if (in_erase_mode)
        {
            text = LOCALIZED_STATUS_PENERASE;
        }

        MainWindowx->StatusWindow->SetDlgItemText(ID_PENSTYLE, text);
    }
}

void update_status_pencontact(void)
{
    if (status_flag)
    {
        const char * text;
        if (g_Turtles[turtle_which].IsPenUp)
        {
            text = LOCALIZED_STATUS_PENUP;
        }
        else
        {
            text = LOCALIZED_STATUS_PENDOWN;
        }

        MainWindowx->StatusWindow->SetDlgItemText(ID_PENCONTACT, text);
    }
}

void update_status_turtlevisability(void)
{
    if (status_flag)
    {
        const char * text;

        if (g_Turtles[turtle_which].IsShown)
        {
            text = LOCALIZED_STATUS_PENSHOWN;
        }
        else
        {
            text = LOCALIZED_STATUS_PENHIDDEN;
        }

        MainWindowx->StatusWindow->SetDlgItemText(ID_TURTLEVISABILITY, text);
    }
}

void update_status_turtlepitch(void)
{
    if (status_flag)
    {
        char text[256];

        if (current_mode == perspectivemode)
        {
            sprintf(text, "%1.2f", rotation_x());
        }
        else
        {
            sprintf(text, "%1.2f", 0.0);
        }

        MainWindowx->StatusWindow->SetDlgItemText(ID_TURTLEPITCH, text);
    }
}

void update_status_turtleroll(void)
{
    if (status_flag)
    {
        char text[256];

        if (current_mode == perspectivemode)
        {
            sprintf(text, "%1.2f", rotation_y());
        }
        else
        {
            sprintf(text, "%1.2f", 0.0);
        }

        MainWindowx->StatusWindow->SetDlgItemText(ID_TURTLEROLL, text);
    }
}

void update_status_turtlewhich(void)
{
    if (status_flag)
    {
        char text[256];

        if (turtle_which >= TURTLES - TURTLEN)
        {
            sprintf(text, "%ld", (long) (-(turtle_which - (TURTLES - (TURTLEN+1)))));
        }
        else
        {
            sprintf(text, "%ld", (long) turtle_which);
        }

        MainWindowx->StatusWindow->SetDlgItemText(ID_TURTLEWHICH, text);
    }
}

void update_status_evals(void)
{
    if (status_flag)
    {
        char text[256];
        sprintf(text, "%ld", eval_count);

        MainWindowx->StatusWindow->SetDlgItemText(ID_EVALS, text);
    }
}

void update_status_vectors(void)
{
    if (status_flag)
    {
        char text[256];

        if (ThreeD.m_iPolyCount)
        {
#ifdef NOASM
            sprintf(text, "%ld/%ld", ThreeD.m_iPolyCount, ThreeD.m_iSplitPolyCount);
#else
            sprintf(text, "%ld", ThreeD.m_iPolyCount);
#endif
            MainWindowx->StatusWindow->SetDlgItemText(
                ID_THINGS, 
                LOCALIZED_STATUS_POLYGONS":");
        }
        else
        {
            sprintf(text, "%ld", vector_count);
            MainWindowx->StatusWindow->SetDlgItemText(
                ID_THINGS, 
                LOCALIZED_STATUS_VECTORS":");
        }

        MainWindowx->StatusWindow->SetDlgItemText(ID_VECTORS, text);
    }
}

void update_status_memory(void)
{
    if (status_flag)
    {
        char text[256];
        sprintf(text, "%ld "LOCALIZED_STATUS_NODES, memory_count * SEG_SIZE);

        MainWindowx->StatusWindow->SetDlgItemText(ID_MEMORY, text);
    }
}

#endif
