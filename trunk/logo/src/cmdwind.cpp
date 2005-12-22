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

TMyCommandWindow::TMyCommandWindow(
   TWindow *AParent,
   LPCSTR   ResId
) : TDialog(AParent, ResId),
   TraceButton(this, ID_TRACE),
   ResetButton(this, ID_RESET),
   PauseButton(this, ID_PAUSE),
   HaltButton(this, ID_HALT),
   StatusButton(this, ID_STATUS),
   YieldButton(this, ID_YIELD),
   EdallButton(this, ID_EDALL),
   ExecuteButton(this, ID_EXECUTE),
   Editbox(this, ID_EDITINPUT, 0),
   Listbox(this, ID_LISTBOX, 0),
   Font(NULL)
   {
   }

TMyCommandWindow::~TMyCommandWindow()
   {
   if (Font)
      {
      DeleteObject(Font);
      }
   }

void TMyCommandWindow::SetupWindow()
   {
   TDialog::SetupWindow();

   LOGFONT lf;
   GetPrivateProfileFont("CommanderFont", lf);

   Font = CreateFontIndirect(&lf);

   Editbox.Create();
   Editbox.SetWindowFont(Font, TRUE);

   Listbox.Create();
   Listbox.SetWindowFont(Font, TRUE);

   TraceButton.Create();

   ResetButton.Create();

   PauseButton.Create();

   HaltButton.Create();

   StatusButton.Create();

   YieldButton.Create();

   EdallButton.Create();

   ExecuteButton.Create();

   RecalculateLayout();
   }


char *TMyCommandWindow::GetClassName()
   {
   return "LogoCommander";
   }

void TMyCommandWindow::RecalculateLayout()
   {
   // scale and pos. each sub-window in commander window based on its size
   TRect buttonRect;
   TraceButton.GetClientRect(buttonRect);

   TRect commanderRect;
   GetClientRect(commanderRect);

   int total_width   = commanderRect.Width();
   int total_height  = commanderRect.Height();
   int button_height = buttonRect.Height();
   int button_width  = buttonRect.Width();

   const int x_border = 4;
   const int y_border = 4;
   const int padding  = 6;

   // Set the height of the editbox based on the height
   // of the current commander font.
   int editbox_height = button_height;

   HDC edit_dc = GetDC(Editbox.HWindow);
   if (edit_dc != NULL)
      {
      TEXTMETRIC metrics;

      HFONT oldFont = (HFONT) SelectObject(edit_dc, Font);

      BOOL isOk = GetTextMetrics(edit_dc, &metrics);
      if (isOk)
         {
         // font height + some padding
         int height_for_font = metrics.tmHeight + 6;
         if (editbox_height < height_for_font)
            {
            editbox_height = height_for_font;
            }
         }

      SelectObject(edit_dc, oldFont);

      ReleaseDC(Editbox.HWindow, edit_dc);
      }

   Listbox.SetWindowPos(NULL, x_border, 0,                                       total_width - button_width * 2 - x_border - padding, total_height - editbox_height - padding, SWP_NOZORDER);
   Editbox.SetWindowPos(NULL, x_border, total_height - editbox_height - y_border, total_width - button_width * 2 - x_border - padding, editbox_height,                         SWP_NOZORDER);

   HaltButton.SetWindowPos(NULL,   total_width - button_width * 2 - x_border, button_height * 0 + y_border, button_width, button_height, SWP_NOZORDER);
   TraceButton.SetWindowPos(NULL,  total_width - button_width * 1 - x_border, button_height * 0 + y_border, button_width, button_height, SWP_NOZORDER);
   PauseButton.SetWindowPos(NULL,  total_width - button_width * 2 - x_border, button_height * 1 + y_border, button_width, button_height, SWP_NOZORDER);
   StatusButton.SetWindowPos(NULL, total_width - button_width * 1 - x_border, button_height * 1 + y_border, button_width, button_height, SWP_NOZORDER);
   YieldButton.SetWindowPos(NULL,  total_width - button_width * 2 - x_border, button_height * 2 + y_border, button_width, button_height, SWP_NOZORDER);
   ResetButton.SetWindowPos(NULL,  total_width - button_width * 1 - x_border, button_height * 2 + y_border, button_width, button_height, SWP_NOZORDER);

   ExecuteButton.SetWindowPos(NULL, total_width - button_width * 2 - x_border, total_height - button_height - y_border, button_width, button_height, SWP_NOZORDER);
   EdallButton.SetWindowPos(NULL,   total_width - button_width * 1 - x_border, total_height - button_height - y_border, button_width, button_height, SWP_NOZORDER);
   }

void TMyCommandWindow::EvSize(UINT arg1, TSize & arg2)
   {
   TDialog::EvSize(arg1, arg2);

   RecalculateLayout();

   Invalidate(true);
   }

bool
TMyCommandWindow::EditBoxWantsKeyEvent(
   WPARAM KeyEventWParam
)
   {
   return isprint(KeyEventWParam) || KeyEventWParam == VK_SPACE;
   }


void
TMyCommandWindow::PostKeyDownToEditBox(
   WPARAM KeyEventWParam,
   LPARAM KeyEventLParam
)
   {
   Editbox.SetFocus();

   Editbox.PostMessage(
      WM_KEYDOWN,
      KeyEventWParam,
      KeyEventLParam);
   }


static
char *
GetTextFromWindow(
   const TWindow & Window
)
   {
   // copy the text in the commander history
   int    windowTextLength = Window.GetWindowTextLength();
   size_t textBufferLength = windowTextLength + 1; // for NUL

   char *textBuffer = new char [textBufferLength];
   if (textBuffer != NULL)
      {
      memset(textBuffer, 0, textBufferLength);

      Window.GetWindowText(textBuffer, textBufferLength);
      }

   return textBuffer;
   }

void TMyCommandWindow::DoEditBox(UINT)
   {
   }

void TMyCommandWindow::DoListBox(UINT)
   {
   }

void TMyCommandWindow::UpdateYieldButtonState()
   {
   if (stepflag)
      {
      YieldButton.SetWindowText("UnStep");
      YieldButton.SetCheck(BF_CHECKED);
      }
   else
      {
      YieldButton.SetWindowText("Step");
      YieldButton.SetCheck(BF_UNCHECKED);
      }
   }

void TMyCommandWindow::UpdateTraceButtonState()
   {
   if (traceflag)
      {
      TraceButton.SetWindowText("UnTrace");
      TraceButton.SetCheck(BF_CHECKED);
      }
   else
      {
      TraceButton.SetWindowText("Trace");
      TraceButton.SetCheck(BF_UNCHECKED);
      }
   }

void TMyCommandWindow::UpdateStatusButtonState()
   {
   if (status_flag)
      {
      StatusButton.SetWindowText("NoStatus");
      StatusButton.SetCheck(BF_CHECKED);
      }
   else
      {
      StatusButton.SetWindowText("Status");
      StatusButton.SetCheck(BF_UNCHECKED);
      }
   }

// Copies the state of the widgets from one commander window
// to another.
bool 
TMyCommandWindow::Duplicate(
   const TMyCommandWindow & Original
   )
   {
   // copy the text of the "Step" button
   UpdateYieldButtonState();

   // copy the text of the "Trace" button
   UpdateTraceButtonState();

   // copy the text of the "Status" button
   UpdateStatusButtonState();

   char * buffer;

   buffer = GetTextFromWindow(Original.Listbox);
   if (buffer != NULL)
      {
      Listbox.SetText(buffer);
      delete [] buffer;
      }
   Listbox.SetCursorAtBottom();

   buffer = GetTextFromWindow(Original.Editbox);
   if (buffer != NULL)
      {
      Editbox.SetText(buffer);
      delete [] buffer;
      }

   return true;
   }

void do_execution(char * logocommand)
   {
   NODE *exec_list = NIL;
   NODETYPES this_type;
   int i;

   // if something there continue

   if (strlen(logocommand) != 0)
      {

      // if executing then it's ok to halt
      halt_flag++;
      if (halt_flag < 1)
        {
        halt_flag = 1;
        }

      // this code emulates the TTY model used in UCBLOGO main loop

      this_type = STRING;

      // do control character processing processing
      for (char * c = logocommand; *c != '\0'; c++)
         {
         if (*c == '\\')
            {
            strcpy(c, c + 1);
            if (*c)
               {
               if (*c == 'n') *c = '\n';
               *c = setparity(*c);
               }
            this_type = BACKSLASH_STRING;
            }
         }

      check_reserve_tank();

      /* turn text into a NODE and parse it */
      current_line = reref(
         current_line, 
         make_strnode(logocommand, (int) strlen(logocommand), this_type, strnzcpy));

      exec_list = reref(exec_list, parser(current_line, TRUE));

      /* now process it */

      val_status = 0;
      if (exec_list != NIL)
        {
        eval_driver(exec_list);
        }

      // process special conditions

      for (i = 0; i < 1; i++)
         {
         if (stopping_flag == THROWING)
            {
            if (compare_node(throw_node, Error, TRUE) == 0)
               {
               err_print();
               }
            else if (compare_node(throw_node, System, TRUE) == 0)
               {
               break;
               }
            else if (compare_node(throw_node, Toplevel, TRUE) != 0)
               {
               err_logo(NO_CATCH_TAG, throw_node);
               err_print();
               }
            stopping_flag = RUN;
            }

         if (stopping_flag == STOP || stopping_flag == OUTPUT)
            {
            print_node(
                stdout,
                make_static_strnode(
                  "You must be in a procedure to use OUTPUT or STOP.\n"));
            stopping_flag = RUN;
            }
         }

      /* deallocate the line */

      current_line = reref(current_line, NIL);

      /* this is a hack to force garbage collector to properly clean up */

      if (exec_list != NIL)
         {
         settype(exec_list, CONS);
         exec_list = reref(exec_list, NIL);
         }

      /* not ok to halt now */

      halt_flag--;
      if (halt_flag < 0)
         {
         halt_flag = 0;
         }
      }

   }

void TMyCommandWindow::DoButtonExecute(UINT)
   {
   char selectedtext[MAX_BUFFER_SIZE];

   selectedtext[0] = '\0';

   // get what's in the edit box
   getcombobox(selectedtext);

   // if real do something with it
   if (strlen(selectedtext) != 0)
      {

      // copy to list box for command recall
      putcombobox(selectedtext);

      /* if dribble then dribble */

      if (dribblestream != NULL)
        {
        fprintf(dribblestream, "%s\n", selectedtext);
        }

      // reset erract loop error history
      erract_errtype = FATAL;

      // reset evaluation counter (call counter) and execute
      eval_count = 0;
      vector_count = 0;

      if (status_flag)
        {
        update_status_evals();
        update_status_vectors();
        }

      do_execution(selectedtext);
      }

   // calling do_execution() will delete the "this" pointer,
   // if it executes FULLSCREEN, TEXTSCREEN, or SPLITSCREEN.
   // Therefore, we must not touch any member variable at this point.
   if (!JustDidEdit)
      {
      MainWindowx->CommandWindow->Editbox.SetFocus();
      }
   JustDidEdit = false;
   }

void TMyCommandWindow::DoButtonEdall(UINT)
   {
   do_execution("EDALL");
   }

void TMyCommandWindow::DoButtonStatus(UINT)
   {

   // toggle status state along with poping up and killing the status window

   if (status_flag)
      {
      MainWindowx->MyPopupStatusKill();
      Editbox.SetFocus();
      }
   else
      {
      MainWindowx->MyPopupStatus();
      }
   }

void TMyCommandWindow::DoButtonReset(UINT)
   {
   /* just do a clear screen and return focus */
   char logoInstruction[] = "CLEARSCREEN";
   putcombobox(logoInstruction);
   do_execution(logoInstruction);

   Editbox.SetFocus();
   }


void TMyCommandWindow::DoButtonYield(UINT)
   {
   /* toggle yield state */
   stepflag = !stepflag;
   UpdateYieldButtonState();
   Editbox.SetFocus();
   }

void TMyCommandWindow::DoButtonPause(UINT)
   {

   // if ok to halt then it's ok to pause if we get here
   Editbox.SetFocus();
   if (halt_flag != 0)
      {
      IsTimeToPause = true;
      }
   }

// Will put back later
//
//void do_pause_update(long arg)
//   {
//   char buffer[256];
//   if (arg)
//      {
//      sprintf(buffer, "Pause-%d", arg);
//      }
//   else
//      {
//      sprintf(buffer, "Pause");
//      }
//   MainWindowx->CommandWindow->PauseButton->SetWindowText(buffer);
//   }


void TMyCommandWindow::DoButtonTrace(UINT)
   {
   /* toggle trace state */
   traceflag = !traceflag;
   UpdateTraceButtonState();

   Editbox.SetFocus();
   }

void TMyCommandWindow::DoButtonHalt(UINT)
   {

   for (int i = 1; i < 32; i++)
      {
      MainWindowx->KillTimer(i);
      }

   /* if ok to halt and we get here then halt */
   Editbox.SetFocus();
   if (halt_flag != 0)
      {
      IsTimeToHalt = true;
      }
   }

void TMyCommandWindow::EvDestroy()
   {

   // Save the location and size of our window so we can
   // come back up in the same spot next time we are invoked.
   if (!IsIconic())
      {
      TRect wrect;
      GetWindowRect(wrect);

      SetPrivateProfileQuadruple(
         "LOGO",
         "Commander",
         wrect.Left(),
         wrect.Top(),
         wrect.Width(),
         wrect.Height());
      }

   TWindow::EvDestroy();
   }

void TMyCommandWindow::CmCancel()
   {
   }

void TMyCommandWindow::CmOk()
   {
   }

void TMyCommandWindow::EvClose()
   {
   }

void TMyCommandWindow::ChooseNewFont()
   {
   LOGFONT lf;
   GetPrivateProfileFont("CommanderFont", lf);

   // initialize the font chooser with the current font preference
   CHOOSEFONT CF;
   memset(&CF, 0, sizeof CF);

   CF.lStructSize = sizeof CF;
   CF.hwndOwner = MainWindowx->HWindow;
   CF.Flags = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT;
   CF.nFontType = SCREEN_FONTTYPE;
   CF.lpLogFont = &lf;
   CF.hInstance = 0;

   if (ChooseFont(&CF))
      {
      // safe the new font preference to persistent storage
      SetPrivateProfileFont("CommanderFont", lf);

      HFONT hFont = CreateFontIndirect(&lf);
      Listbox.SetWindowFont(hFont, TRUE);
      Editbox.SetWindowFont(hFont, TRUE);

      // commit to the new font
      if (Font)
         {
         DeleteObject(Font);
         }
      Font = hFont;

      RecalculateLayout();
      Invalidate(true);
      }
   }


NODE *lhalt(NODE *)
   {
   MainWindowx->CommandWindow->PostMessage(WM_COMMAND, ID_HALT, ID_HALT);
   return Unbound;
   }

NODE *lyield(NODE *)
   {

   // set flag and update button label

   yield_flag = 1;
   // MainWindowx->CommandWindow->YieldButton->SetWindowText("NoYield");
   return Unbound;
   }

NODE *lnoyield(NODE *)
   {

   // clear flag and update button label

   yield_flag = 0;
   // MainWindowx->CommandWindow->YieldButton->SetWindowText("Yield");
   return Unbound;
   }

/* Editbox members */

TMyEditboxWindow::TMyEditboxWindow(TWindow *AParent, int AId, WORD Alen)
: TEdit(AParent, AId, Alen)
   {
   }

TMyEditboxWindow::~TMyEditboxWindow()
   {
   }

void TMyEditboxWindow::EvKeyDown(UINT, UINT, UINT)
   {
   TMessage Msg = __GetTMessage();

   // if up/down arrow keys then focus to list box

   switch (Msg.WParam)
      {
      case VK_UP:
         {
         // advance to the bottom of the listbox
         MainWindowx->CommandWindow->Listbox.SetCursorAtBottom();

         // give focus to the listbox
         MainWindowx->CommandWindow->Listbox.SetFocus();
         break;
         }
      case VK_F1:
         {
         ContextHelp(MainWindowx->CommandWindow->HWindow, this);
         break;
         }
      }

   DefaultProcessing();
   }

/* Listbox members */

TMyListboxWindow::TMyListboxWindow(
   TWindow *AParent,
   int      AId,
   WORD     Alen
) : TEdit(AParent, AId, Alen)
   {
   }

TMyListboxWindow::~TMyListboxWindow()
   {
   }

void TMyListboxWindow::EvKeyDown(UINT, UINT, UINT)
   {
   TMessage Msg = __GetTMessage();

   // if Down off bottom then focus to edit box

   if (Msg.WParam == VK_DOWN)
      {
      UINT from;
      UINT to;

      GetSelection(from, to);
      if (GetTextLen() == to)
         {
         MainWindowx->CommandWindow->Editbox.SetFocus();
         return;
         }
      }

   DefaultProcessing();

   if (Msg.WParam == VK_UP   ||
       Msg.WParam == VK_DOWN ||
       Msg.WParam == VK_LEFT ||
       Msg.WParam == VK_UP)
      {
      char buf[MAX_BUFFER_SIZE];

      GetLine(buf, MAX_BUFFER_SIZE, GetLineFromPos(-1));
      MainWindowx->CommandWindow->Editbox.SetText(buf);
      }
   else if (Msg.WParam == VK_F1)
      {
      ContextHelp(MainWindowx->CommandWindow->HWindow, this);
      }
   else if (MainWindowx->CommandWindow->EditBoxWantsKeyEvent(Msg.WParam))
      {
         // we don't handle this key.
         // give focus to the edit box and send the press to it.
         MainWindowx->CommandWindow->PostKeyDownToEditBox(
            Msg.WParam,
            Msg.LParam);
      }
   }

void TMyListboxWindow::EvLButtonDown(UINT /* modKeys */, TPoint & /* point */)
   {
   DefaultProcessing();

   char buf[MAX_BUFFER_SIZE];
   GetLine(buf, MAX_BUFFER_SIZE, GetLineFromPos(-1));
   MainWindowx->CommandWindow->Editbox.SetText(buf);
   }

void TMyListboxWindow::EvLButtonDblClk(UINT /* modKeys */, TPoint & /* point */)
   {
   DefaultProcessing();

   char buf[MAX_BUFFER_SIZE];
   GetLine(buf, MAX_BUFFER_SIZE, GetLineFromPos(-1));
   MainWindowx->CommandWindow->Editbox.SetText(buf);
   MainWindowx->CommandWindow->DoButtonExecute(0);
   }

void TMyListboxWindow::SetCursorAtBottom()
   {
   int endOfText = GetTextLen();
   SetSelection(endOfText, endOfText);

   int totalLines = GetNumLines();
   Scroll(0, totalLines);

   Invalidate(true);
   }

DEFINE_RESPONSE_TABLE1(TMyEditboxWindow, TEdit)
  EV_WM_KEYDOWN,
END_RESPONSE_TABLE;

DEFINE_RESPONSE_TABLE1(TMyListboxWindow, TEdit)
  EV_WM_KEYDOWN,
  EV_WM_LBUTTONDOWN,
  EV_WM_LBUTTONDBLCLK,
END_RESPONSE_TABLE;

DEFINE_RESPONSE_TABLE1(TMyCommandWindow, TDialog)
  EV_WM_SIZE,
  EV_WM_DESTROY,
  EV_WM_CLOSE,
  EV_CHILD_NOTIFY_ALL_CODES(ID_LISTBOX, DoListBox),
  EV_CHILD_NOTIFY_ALL_CODES(ID_EDITINPUT, DoEditBox),
  EV_CHILD_NOTIFY_ALL_CODES(ID_EXECUTE, DoButtonExecute),
  EV_CHILD_NOTIFY_ALL_CODES(ID_EDALL, DoButtonEdall),
  EV_CHILD_NOTIFY_ALL_CODES(ID_HALT, DoButtonHalt),
  EV_CHILD_NOTIFY_ALL_CODES(ID_STATUS, DoButtonStatus),
  EV_CHILD_NOTIFY_ALL_CODES(ID_YIELD, DoButtonYield),
  EV_CHILD_NOTIFY_ALL_CODES(ID_PAUSE, DoButtonPause),
  EV_CHILD_NOTIFY_ALL_CODES(ID_TRACE, DoButtonTrace),
  EV_CHILD_NOTIFY_ALL_CODES(ID_RESET, DoButtonReset),
  EV_COMMAND(IDCANCEL, CmCancel),
  EV_COMMAND(IDOK, CmOk),
END_RESPONSE_TABLE;

