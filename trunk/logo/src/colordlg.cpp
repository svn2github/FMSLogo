/*
*
*       Copyright (C) 1995 by the Regents of the University of California
*       Copyright (C) 1995 by George Mills
*
*      This program is free software; you can redistribute it and/or modify
*      it under the terms of the GNU General Public License as published by
*      the Free Software Foundation; either version 2 of the License, or
*      (at your option) any later version.
*
*      This program is distributed in the hope that it will be useful,
*      but WITHOUT ANY WARRANTY; without even the implied warranty of
*      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*      GNU General Public License for more details.
*
*      You should have received a copy of the GNU General Public License
*      along with this program; if not, write to the Free Software
*      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
*/

#include "allwind.h"

const unsigned int CN_CLICKED = 1;     // color control notifications

TColorControl::TColorControl(
   TWindow      * Parent, 
   int            ResourceId, 
   const TColor & Color
   ) : TControl(Parent, ResourceId), 
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
      COLORREF lColor = LoadColor(GetRValue(m_Color), GetGValue(m_Color), GetBValue(m_Color));
      OldPalette = SelectPalette(dc, ThePalette, FALSE);
      RealizePalette(dc);

      dc.FillRect(GetClientRect(), TBrush(lColor));

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
   TWindow      * Parent,
   const TColor & InitialColor,
   const char   * Caption
   ) : 
   TDialog(Parent, IDD_SETCOLOR),
   m_ColorBar1(this, ID_COLORBAR1),
   m_ColorBar2(this, ID_COLORBAR2),
   m_ColorBar3(this, ID_COLORBAR3),
   m_SelColor(this, ID_SELCOLOR, InitialColor)
   {
   new TColorControl(this, ID_COLOR1, TColor(000, 000, 000));
   new TColorControl(this, ID_COLOR2, TColor(255, 255, 255));
   new TColorControl(this, ID_COLOR3, TColor(255, 000, 000));
   new TColorControl(this, ID_COLOR4, TColor(000, 255, 000));
   new TColorControl(this, ID_COLOR5, TColor(000, 000, 255));
   new TColorControl(this, ID_COLOR6, TColor(000, 255, 255));
   new TColorControl(this, ID_COLOR7, TColor(255, 000, 255));
   new TColorControl(this, ID_COLOR8, TColor(255, 255, 000));

   SetCaption(Caption);
   }

// Handlers for each custom control
void TColorDialog::ClickFmControl1()
   {
   SetColorFmControl(ID_COLOR1);
   }
void TColorDialog::ClickFmControl2()
   {
   SetColorFmControl(ID_COLOR2);
   }
void TColorDialog::ClickFmControl3()
   {
   SetColorFmControl(ID_COLOR3);
   }
void TColorDialog::ClickFmControl4()
   {
   SetColorFmControl(ID_COLOR4);
   }
void TColorDialog::ClickFmControl5()
   {
   SetColorFmControl(ID_COLOR5);
   }
void TColorDialog::ClickFmControl6()
   {
   SetColorFmControl(ID_COLOR6);
   }
void TColorDialog::ClickFmControl7()
   {
   SetColorFmControl(ID_COLOR7);
   }
void TColorDialog::ClickFmControl8()
   {
   SetColorFmControl(ID_COLOR8);
   }

// Update the selected color control and bars with the chosen color
void TColorDialog::SetColorFmControl(UINT Id)
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
void TColorDialog::SetColorFmSlider()
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
   static const MENUITEM text[] = {
      {LOCALIZED_SETCOLOR_RED,    ID_SETCOLOR_RED},
      {LOCALIZED_SETCOLOR_GREEN,  ID_SETCOLOR_GREEN},
      {LOCALIZED_SETCOLOR_BLUE,   ID_SETCOLOR_BLUE},
      {LOCALIZED_SETCOLOR_OK,     IDOK},
      {LOCALIZED_SETCOLOR_CANCEL, IDCANCEL},
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

DEFINE_RESPONSE_TABLE1(TColorDialog, TDialog)
  EV_CHILD_NOTIFY(ID_COLOR1, CN_CLICKED, ClickFmControl1),
  EV_CHILD_NOTIFY(ID_COLOR2, CN_CLICKED, ClickFmControl2),
  EV_CHILD_NOTIFY(ID_COLOR3, CN_CLICKED, ClickFmControl3),
  EV_CHILD_NOTIFY(ID_COLOR4, CN_CLICKED, ClickFmControl4),
  EV_CHILD_NOTIFY(ID_COLOR5, CN_CLICKED, ClickFmControl5),
  EV_CHILD_NOTIFY(ID_COLOR6, CN_CLICKED, ClickFmControl6),
  EV_CHILD_NOTIFY(ID_COLOR7, CN_CLICKED, ClickFmControl7),
  EV_CHILD_NOTIFY(ID_COLOR8, CN_CLICKED, ClickFmControl8),
  EV_SB_ENDSCROLL(ID_COLORBAR1, SetColorFmSlider),
  EV_SB_ENDSCROLL(ID_COLORBAR2, SetColorFmSlider),
  EV_SB_ENDSCROLL(ID_COLORBAR3, SetColorFmSlider),
END_RESPONSE_TABLE;

