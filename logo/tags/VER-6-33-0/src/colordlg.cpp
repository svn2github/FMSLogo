// Copyright (C) 1995 by the Regents of the University of California
// Copyright (C) 1995 by George Mills
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#include <stdio.h>

#include "colordlg.h"
#include "main.h"
#include "graphwin.h"
#include "graphics.h"
#include "status.h"
#include "logorc.h"
#include "mainframe.h"
#include "localizedstrings.h"
#include "logodata.h"
#include "debugheap.h"

const unsigned int CN_CLICKED = 1;     // color control notifications

TColorControl::TColorControl(
    TWindow      * Parent,
    UINT           ResourceId,
    const TColor & Color
    ) : 
    TControl(Parent, ResourceId),
    m_Color(Color)
{
}

//
// Must use EvPaint since TControl assumes a pre-defined class control has a
// window's class that paints it. (see source\owl\control.cpp)
//
void TColorControl::EvPaint()
{
    TPaintDC dc(*this);

    if (EnablePalette)
    {
        int oldentries = MyLogPalette->palNumEntries;
        RGBCOLOR lColor = LoadColor(GetRValue(m_Color), GetGValue(m_Color), GetBValue(m_Color));
        OldPalette = SelectPalette(dc, ThePalette, FALSE);
        RealizePalette(dc);

        dc.FillRect(GetClientRect(), TBrush((COLORREF)lColor));

        SelectPalette(dc, OldPalette, FALSE);
        MyLogPalette->palNumEntries = oldentries;
        DeleteObject(ThePalette);
        update_status_paletteuse();
        ThePalette = CreatePalette(MyLogPalette);
    }
    else
    {
        dc.FillRect(GetClientRect(), TBrush(m_Color));
    }
}

void TColorControl::SetColor(const TColor & NewColor)
{
    m_Color = NewColor;
    Invalidate();
}

//
// Notify parent of a CN_CLICKED event by sending a WM_COMMAND message
//
void TColorControl::EvLButtonDown(UINT, TPoint &)
{
    Parent->SendNotification(Attr.Id, CN_CLICKED, HWindow);
}


DEFINE_RESPONSE_TABLE1(TColorControl, TControl)
    EV_WM_LBUTTONDOWN,
    EV_WM_PAINT,
END_RESPONSE_TABLE;

//----------------------------------------------------------------------------

TColorDialog::TColorDialog(
    TWindow            *   Parent,
    const TColor         & InitialColor,
    const char         *   Caption,
    const char         *   LogoCommand,
    class TColorDialog * & ExternalReference
    ) :
    TDialog(Parent, IDD_SETCOLOR),
    m_ColorBar1(this, ID_COLORBAR1),
    m_ColorBar2(this, ID_COLORBAR2),
    m_ColorBar3(this, ID_COLORBAR3),
    m_SelColor(this, ID_SELCOLOR, InitialColor),
    m_LogoCommand(LogoCommand),
    m_ExternalReference(ExternalReference)
{

    static const UINT childIds[] = 
    {
        ID_COLOR1,
        ID_COLOR2,
        ID_COLOR3,
        ID_COLOR4,
        ID_COLOR5,
        ID_COLOR6,
        ID_COLOR7,
        ID_COLOR8,
    };

    // initialize the child controls to match the color-by-index values
    for (size_t i = 0; i < ARRAYSIZE(childIds); i++)
    {
        const TColor color(
            GetRValue(colortable[i]),
            GetGValue(colortable[i]),
            GetBValue(colortable[i]));

        new TColorControl(this, childIds[i], color);
    }
   
    SetCaption(Caption);
}

// Handlers for each custom control
void TColorDialog::ClickControl1()
{
    SetColorFromControl(ID_COLOR1);
}
void TColorDialog::ClickControl2()
{
    SetColorFromControl(ID_COLOR2);
}
void TColorDialog::ClickControl3()
{
    SetColorFromControl(ID_COLOR3);
}
void TColorDialog::ClickControl4()
{
    SetColorFromControl(ID_COLOR4);
}
void TColorDialog::ClickControl5()
{
    SetColorFromControl(ID_COLOR5);
}
void TColorDialog::ClickControl6()
{
    SetColorFromControl(ID_COLOR6);
}
void TColorDialog::ClickControl7()
{
    SetColorFromControl(ID_COLOR7);
}
void TColorDialog::ClickControl8()
{
    SetColorFromControl(ID_COLOR8);
}

// Update the selected color control and bars with the chosen color
void TColorDialog::SetColorFromControl(UINT Id)
{
    TColorControl *control = TYPESAFE_DOWNCAST(ChildWithId(Id), TColorControl);
    if (control)
    {
        const TColor & newColor = control->GetColor();
        m_SelColor.SetColor(newColor);
        UpdateBars(newColor);
    }
}

// Update the selected color control with the current slider values
void TColorDialog::SetColorFromSlider()
{
    TColor newColor(
        m_ColorBar1.GetPosition(),
        m_ColorBar2.GetPosition(),
        m_ColorBar3.GetPosition());

    m_SelColor.SetColor(newColor);
}

void TColorDialog::SetupWindow()
{
    TDialog::SetupWindow();
    UpdateBars(m_SelColor.GetColor());

    // set the text in all of the controls
    static const MENUITEM text[] = 
    {
       {LOCALIZED_SETCOLOR_RED,    ID_SETCOLOR_RED},
       {LOCALIZED_SETCOLOR_GREEN,  ID_SETCOLOR_GREEN},
       {LOCALIZED_SETCOLOR_BLUE,   ID_SETCOLOR_BLUE},
       {LOCALIZED_SETCOLOR_OK,     IDOK},
       {LOCALIZED_SETCOLOR_CANCEL, IDCANCEL},
       {LOCALIZED_SETCOLOR_APPLY,  ID_APPLY},
    };

    SetTextOnChildWindows(this, text, ARRAYSIZE(text));
}

void TColorDialog::UpdateBars(const TColor & NewColor)
{
    m_ColorBar1.SetRange(0, 255);
    m_ColorBar1.SetPosition(NewColor.Red());

    m_ColorBar2.SetRange(0, 255);
    m_ColorBar2.SetPosition(NewColor.Green());

    m_ColorBar3.SetRange(0, 255);
    m_ColorBar3.SetPosition(NewColor.Blue());
}

const TColor & TColorDialog::GetSelectedColor() const
{
    return m_SelColor.GetColor();
}

void TColorDialog::EvVScroll(uint scrollCode, uint thumbPos, HWND hWndCtl)
{
    // Handle and ignore WM_VSCROLL messages so that
    // OWL doesn't go into an infinite regress trying
    // to foward the message to itself on Lenovo laptops.
}

void TColorDialog::EvHScroll(uint scrollCode, uint thumbPos, HWND hWndCtl)
{
    switch (scrollCode)
    {
    case SB_THUMBTRACK:
    case SB_THUMBPOSITION:
        // Update the position of the scrollbar
        // to match the positition of the thumb.
        if (hWndCtl == m_ColorBar1.HWindow)
        {
            m_ColorBar1.SetPosition(thumbPos);
        }
        else if (hWndCtl == m_ColorBar2.HWindow)
        {
            m_ColorBar2.SetPosition(thumbPos);
        }
        else if (hWndCtl == m_ColorBar3.HWindow)
        {
            m_ColorBar3.SetPosition(thumbPos);
        }
        SetColorFromSlider();
        return;
    }

    TDialog::EvHScroll(scrollCode, thumbPos, hWndCtl);
}

void TColorDialog::DoApply(UINT)
{
    const TColor & color = GetSelectedColor();

    // the user pressed "OK" so we change the color
    char upperCaseCommand[MAX_BUFFER_SIZE];

    cap_strnzcpy(
        upperCaseCommand,
        m_LogoCommand,
        strlen(m_LogoCommand));

    char logoInstruction[256];

    sprintf(
        logoInstruction,
        "%s [%d %d %d]",
        upperCaseCommand,
        color.Red(),
        color.Green(),
        color.Blue());

    RunLogoInstructionFromGui(logoInstruction);
}

void TColorDialog::CmOk()
{
    DoApply(CN_CLICKED);
    TDialog::CmOk();
}

void TColorDialog::EvDestroy()
{
    // NULL-out the reference that TMainFrame is holding
    // so that it knows the window is no longer valid.
    // This object will get deleted on its own.
    m_ExternalReference = NULL;
    TDialog::EvDestroy();
}

DEFINE_RESPONSE_TABLE1(TColorDialog, TDialog)
    EV_WM_DESTROY,
    EV_CHILD_NOTIFY(ID_COLOR1, CN_CLICKED, ClickControl1),
    EV_CHILD_NOTIFY(ID_COLOR2, CN_CLICKED, ClickControl2),
    EV_CHILD_NOTIFY(ID_COLOR3, CN_CLICKED, ClickControl3),
    EV_CHILD_NOTIFY(ID_COLOR4, CN_CLICKED, ClickControl4),
    EV_CHILD_NOTIFY(ID_COLOR5, CN_CLICKED, ClickControl5),
    EV_CHILD_NOTIFY(ID_COLOR6, CN_CLICKED, ClickControl6),
    EV_CHILD_NOTIFY(ID_COLOR7, CN_CLICKED, ClickControl7),
    EV_CHILD_NOTIFY(ID_COLOR8, CN_CLICKED, ClickControl8),
    EV_SB_LINEDOWN (ID_COLORBAR1, SetColorFromSlider),
    EV_SB_LINEUP   (ID_COLORBAR1, SetColorFromSlider),
    EV_SB_PAGEUP   (ID_COLORBAR1, SetColorFromSlider),
    EV_SB_PAGEDOWN (ID_COLORBAR1, SetColorFromSlider),
    EV_SB_ENDSCROLL(ID_COLORBAR1, SetColorFromSlider),
    EV_SB_LINEDOWN (ID_COLORBAR2, SetColorFromSlider),
    EV_SB_LINEUP   (ID_COLORBAR2, SetColorFromSlider),
    EV_SB_PAGEUP   (ID_COLORBAR2, SetColorFromSlider),
    EV_SB_PAGEDOWN (ID_COLORBAR2, SetColorFromSlider),
    EV_SB_ENDSCROLL(ID_COLORBAR2, SetColorFromSlider),
    EV_SB_LINEDOWN (ID_COLORBAR3, SetColorFromSlider),
    EV_SB_LINEUP   (ID_COLORBAR3, SetColorFromSlider),
    EV_SB_PAGEUP   (ID_COLORBAR3, SetColorFromSlider),
    EV_SB_PAGEDOWN (ID_COLORBAR3, SetColorFromSlider),
    EV_SB_ENDSCROLL(ID_COLORBAR3, SetColorFromSlider),
    EV_WM_VSCROLL,
    EV_WM_HSCROLL,
    EV_CHILD_NOTIFY_ALL_CODES(ID_APPLY, DoApply),
    EV_COMMAND(IDOK, CmOk),
END_RESPONSE_TABLE;
