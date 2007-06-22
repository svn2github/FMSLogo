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

const unsigned int CN_CLICKED = 1;     // size control notifications


TSizeControl::TSizeControl(
   TWindow *     Parent, 
   int           ResId, 
   const TSize & Size
   )
   : TControl(Parent, ResId), 
     m_Size(Size)
   {
   }

//
// Must use EvPaint since TControl assumes a pre-defined class control has a
// window's class that paints it. (see source\owl\control.cpp)
//
void TSizeControl::EvPaint()
   {
   TPaintDC dc(*this);
   TPen pen(TColor(0, 0, 0), m_Size.X());
   TRect rect(GetClientRect());

   dc.FillRect(rect, TBrush(TColor(255, 255, 255)));
   dc.SelectObject(pen);
   dc.MoveTo(rect.left, (rect.bottom - rect.top) / 2);
   dc.LineTo(rect.right, (rect.bottom - rect.top) / 2);
   //   dc.Rectangle(rect);
   }

void TSizeControl::SetSize(const TSize & NewSize)
   {
   m_Size = NewSize;
   Invalidate();
   }

//
// Notify parent of a CN_CLICKED event by sending a WM_COMMAND message
//
void TSizeControl::EvLButtonDown(UINT, TPoint &)
   {
   Parent->SendNotification(Attr.Id, CN_CLICKED, HWindow);
   }

DEFINE_RESPONSE_TABLE1(TSizeControl, TControl)
  EV_WM_LBUTTONDOWN,
  EV_WM_PAINT,
END_RESPONSE_TABLE;

//----------------------------------------------------------------------------

TSizeDialog::TSizeDialog(
   TWindow *       Parent, 
   const TSize &   InitialSize,
   TSizeDialog * & ExternalReference
   ) 
   : TDialog(Parent, IDD_SETPENSIZE),
     m_SizeBar(this, ID_SIZEBAR),
     m_SelSize(this, ID_SELSIZE, InitialSize),
     m_ExternalReference(ExternalReference)
   {
   static const struct {
      UINT ChildId;
      int  PenWidth;
   } data[] = {
      {ID_SIZE1, 1},
      {ID_SIZE2, 2},
      {ID_SIZE3, 3},
      {ID_SIZE4, 4},
      {ID_SIZE5, 6},
      {ID_SIZE6, 8},
      {ID_SIZE7, 16},
      {ID_SIZE8, 32},
   };

   for (size_t i = 0; i < ARRAYSIZE(data); i++)
      {
      new TSizeControl(
         this, 
         data[i].ChildId,
         TSize(data[i].PenWidth, data[i].PenWidth));
      }

   SetCaption(LOCALIZED_SETPENSIZE);
   }

// Handlers for each custom control
void TSizeDialog::ClickFmControl1()
   {
   SetSizeFmControl(ID_SIZE1);
   }
void TSizeDialog::ClickFmControl2()
   {
   SetSizeFmControl(ID_SIZE2);
   }
void TSizeDialog::ClickFmControl3()
   {
   SetSizeFmControl(ID_SIZE3);
   }
void TSizeDialog::ClickFmControl4()
   {
   SetSizeFmControl(ID_SIZE4);
   }
void TSizeDialog::ClickFmControl5()
   {
   SetSizeFmControl(ID_SIZE5);
   }
void TSizeDialog::ClickFmControl6()
   {
   SetSizeFmControl(ID_SIZE6);
   }
void TSizeDialog::ClickFmControl7()
   {
   SetSizeFmControl(ID_SIZE7);
   }
void TSizeDialog::ClickFmControl8()
   {
   SetSizeFmControl(ID_SIZE8);
   }

// Update the selected size control and bars with the chosen size
void TSizeDialog::SetSizeFmControl(UINT Id)
   {
   TSizeControl *control = TYPESAFE_DOWNCAST(ChildWithId(Id), TSizeControl);
   if (control)
      {
      const TSize & size = control->GetSize();
      m_SelSize.SetSize(size);
      UpdateBars(size);
      }
   }

// Update the selected size control with the current slider values
void TSizeDialog::SetSizeFmSlider()
   {
   int width = m_SizeBar.GetPosition();
   m_SelSize.SetSize(TSize(width, width));
   }

void TSizeDialog::SetupWindow()
   {
   TDialog::SetupWindow();

   UpdateBars(m_SelSize.GetSize());

   // set the text in all of the controls
   static const MENUITEM text[] = {
      {LOCALIZED_SETPENSIZE_OK,     IDOK},
      {LOCALIZED_SETPENSIZE_CANCEL, IDCANCEL},
      {LOCALIZED_SETPENSIZE_SIZE,   ID_SETPENSIZE_SIZE},
      {LOCALIZED_SETPENSIZE_APPLY,  ID_APPLY},
   };

   SetTextOnChildWindows(this, text, ARRAYSIZE(text));
   }

void TSizeDialog::UpdateBars(const TSize & NewSize)
   {
   m_SizeBar.SetRange(1, 32);
   m_SizeBar.SetPosition(NewSize.X());
   }

const TSize & TSizeDialog::GetSelectedSize() const
   {
   return m_SelSize.GetSize();
   }

void TSizeDialog::DoApply(UINT)
   {
   const TSize & size = GetSelectedSize();

   char setpensize[MAX_BUFFER_SIZE];

   cap_strnzcpy(
      setpensize,
      LOCALIZED_ALTERNATE_SETPENSIZE,
      STRINGLENGTH(LOCALIZED_ALTERNATE_SETPENSIZE));

   char logoInstruction[256];

   sprintf(
      logoInstruction,
      "%s %d",
      setpensize,
      size.X());

   RunLogoInstructionFromGui(logoInstruction);
   }

void TSizeDialog::CmOk()
   {
   DoApply(CN_CLICKED);
   TDialog::CmOk();
   }

void TSizeDialog::EvDestroy()
   {
   // NULL-out the reference that TMainFrame is holding
   // so that it knows the window is no longer valid.
   // This object will get deleted on its own.
   m_ExternalReference = NULL;
   TDialog::EvDestroy();
   }


DEFINE_RESPONSE_TABLE1(TSizeDialog, TDialog)
  EV_WM_DESTROY,
  EV_CHILD_NOTIFY(ID_SIZE1, CN_CLICKED, ClickFmControl1),
  EV_CHILD_NOTIFY(ID_SIZE2, CN_CLICKED, ClickFmControl2),
  EV_CHILD_NOTIFY(ID_SIZE3, CN_CLICKED, ClickFmControl3),
  EV_CHILD_NOTIFY(ID_SIZE4, CN_CLICKED, ClickFmControl4),
  EV_CHILD_NOTIFY(ID_SIZE5, CN_CLICKED, ClickFmControl5),
  EV_CHILD_NOTIFY(ID_SIZE6, CN_CLICKED, ClickFmControl6),
  EV_CHILD_NOTIFY(ID_SIZE7, CN_CLICKED, ClickFmControl7),
  EV_CHILD_NOTIFY(ID_SIZE8, CN_CLICKED, ClickFmControl8),
  EV_SB_ENDSCROLL(ID_SIZEBAR, SetSizeFmSlider),
  EV_CHILD_NOTIFY_ALL_CODES(ID_APPLY, DoApply),
  EV_COMMAND(IDOK, CmOk),
END_RESPONSE_TABLE;
