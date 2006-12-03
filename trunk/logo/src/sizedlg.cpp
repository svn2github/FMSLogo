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
   const TSize & OutputSize
   )
   : TControl(Parent, ResId), 
     m_Size(OutputSize)
   {
   DisableTransfer();
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

UINT TSizeControl::Transfer(void *buffer, TTransferDirection direction)
   {
   if (direction == tdGetData)
      {
      memcpy(buffer, &m_Size, sizeof m_Size);
      }
   else if (direction == tdSetData)
      {
      memcpy(&m_Size, buffer, sizeof m_Size);
      }

   return sizeof m_Size;
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


static void DisableChildTransfer(TWindow *w, void *)
   {
   w->DisableTransfer();
   }

TSizeDialog::TSizeDialog(
   TWindow *       Parent, 
   TSize   &       OutputSize
   )
   : TDialog(Parent, IDD_SETPENSIZE)
   {
   SetCaption(LOCALIZED_SETPENSIZE);

   new TSizeControl(this, ID_SIZE1, TSize(1, 1));
   new TSizeControl(this, ID_SIZE2, TSize(2, 2));
   new TSizeControl(this, ID_SIZE3, TSize(3, 3));
   new TSizeControl(this, ID_SIZE4, TSize(4, 4));
   new TSizeControl(this, ID_SIZE5, TSize(6, 6));
   new TSizeControl(this, ID_SIZE6, TSize(8, 8));
   new TSizeControl(this, ID_SIZE7, TSize(16, 16));
   new TSizeControl(this, ID_SIZE8, TSize(32, 32));

   m_SizeBar = new TScrollBar(this, ID_SIZEBAR);

   ForEach(DisableChildTransfer);

   m_SelSize = new TSizeControl(this, ID_SELSIZE, OutputSize);
   m_SelSize->EnableTransfer();

   TransferBuffer = &OutputSize;
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
      m_SelSize->SetSize(size);
      UpdateBars(size);
      }
   }

// Update the selected size control with the current slider values
void TSizeDialog::SetSizeFmSlider()
   {
   int width = m_SizeBar->GetPosition();
   m_SelSize->SetSize(TSize(width, width));
   }

void TSizeDialog::SetupWindow()
   {
   TDialog::SetupWindow();

   SetDlgItemText(IDOK,                LOCALIZED_SETPENSIZE_OK);
   SetDlgItemText(IDCANCEL,            LOCALIZED_SETPENSIZE_CANCEL);
   SetDlgItemText(ID_SETPENSIZE_SIZE,  LOCALIZED_SETPENSIZE_SIZE);

   UpdateBars(m_SelSize->GetSize());
   }

void TSizeDialog::TransferData(TTransferDirection transferFlag)
   {
   TDialog::TransferData(transferFlag);
   if (transferFlag == tdSetData) 
      {
      UpdateBars(m_SelSize->GetSize());
      }
   }

void TSizeDialog::UpdateBars(const TSize & NewSize)
   {
   m_SizeBar->SetRange(1, 32);
   m_SizeBar->SetPosition(NewSize.X());
   }


DEFINE_RESPONSE_TABLE1(TSizeDialog, TDialog)
  EV_CHILD_NOTIFY(ID_SIZE1, CN_CLICKED, ClickFmControl1),
  EV_CHILD_NOTIFY(ID_SIZE2, CN_CLICKED, ClickFmControl2),
  EV_CHILD_NOTIFY(ID_SIZE3, CN_CLICKED, ClickFmControl3),
  EV_CHILD_NOTIFY(ID_SIZE4, CN_CLICKED, ClickFmControl4),
  EV_CHILD_NOTIFY(ID_SIZE5, CN_CLICKED, ClickFmControl5),
  EV_CHILD_NOTIFY(ID_SIZE6, CN_CLICKED, ClickFmControl6),
  EV_CHILD_NOTIFY(ID_SIZE7, CN_CLICKED, ClickFmControl7),
  EV_CHILD_NOTIFY(ID_SIZE8, CN_CLICKED, ClickFmControl8),
  EV_SB_ENDSCROLL(ID_SIZEBAR, SetSizeFmSlider),
END_RESPONSE_TABLE;
