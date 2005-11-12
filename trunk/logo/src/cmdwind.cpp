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
   TraceButton(NULL),
   ResetButton(NULL),
   PauseButton(NULL),
   HaltButton(NULL),
   StatusButton(NULL),
   YieldButton(NULL),
   EdallButton(NULL),
   ExecuteButton(NULL),
   Editbox(NULL),
   Listbox(NULL),
   Font(NULL)
   {
   }

TMyCommandWindow::~TMyCommandWindow()
   {
   }

void TMyCommandWindow::SetupWindow()
   {
   TDialog::SetupWindow();

   LOGFONT lf;
   GetPrivateProfileFont("CommanderFont", lf);

   Font = CreateFontIndirect(&lf);

   Editbox = new TMyEditboxWindow(this, ID_EDITINPUT, 0);
   Editbox->Create();
   Editbox->SetWindowFont(Font, TRUE);

   Listbox = new TMyListboxWindow(this, ID_LISTBOX, 0);
   Listbox->Create();
   Listbox->SetWindowFont(Font, TRUE);

   TraceButton = new TCommanderButton(this, ID_TRACE);
   TraceButton->Create();

   ResetButton = new TCommanderButton(this, ID_RESET);
   ResetButton->Create();

   PauseButton = new TCommanderButton(this, ID_PAUSE);
   PauseButton->Create();

   HaltButton = new TCommanderButton(this, ID_HALT);
   HaltButton->Create();

   StatusButton = new TCommanderButton(this, ID_STATUS);
   StatusButton->Create();

   YieldButton = new TCommanderButton(this, ID_YIELD);
   YieldButton->Create();

   EdallButton = new TCommanderButton(this, ID_EDALL);
   EdallButton->Create();

   ExecuteButton = new TCommanderButton(this, ID_EXECUTE);
   ExecuteButton->Create();

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
   TraceButton->GetClientRect(buttonRect);

   TRect commanderRect;
   GetClientRect(commanderRect);

   int total_width   = commanderRect.Width();
   int total_height  = commanderRect.Height();
   int button_height = buttonRect.Height();
   int button_width  = buttonRect.Width();

   const int x_border = 4;
   const int y_border = 4;
   const int padding  = 6;

   Listbox->SetWindowPos(NULL, x_border, 0,                                       total_width - button_width * 2 - x_border - padding, total_height - button_height - padding, SWP_NOZORDER);
   Editbox->SetWindowPos(NULL, x_border, total_height - button_height - y_border, total_width - button_width * 2 - x_border - padding, button_height,                          SWP_NOZORDER);

   HaltButton->SetWindowPos(NULL,   total_width - button_width * 2 - x_border, button_height * 0 + y_border, button_width, button_height, SWP_NOZORDER);
   TraceButton->SetWindowPos(NULL,  total_width - button_width * 1 - x_border, button_height * 0 + y_border, button_width, button_height, SWP_NOZORDER);
   PauseButton->SetWindowPos(NULL,  total_width - button_width * 2 - x_border, button_height * 1 + y_border, button_width, button_height, SWP_NOZORDER);
   StatusButton->SetWindowPos(NULL, total_width - button_width * 1 - x_border, button_height * 1 + y_border, button_width, button_height, SWP_NOZORDER);
   YieldButton->SetWindowPos(NULL,  total_width - button_width * 2 - x_border, button_height * 2 + y_border, button_width, button_height, SWP_NOZORDER);
   ResetButton->SetWindowPos(NULL,  total_width - button_width * 1 - x_border, button_height * 2 + y_border, button_width, button_height, SWP_NOZORDER);

   ExecuteButton->SetWindowPos(NULL, total_width - button_width * 2 - x_border, total_height - button_height - y_border, button_width, button_height, SWP_NOZORDER);
   EdallButton->SetWindowPos(NULL,   total_width - button_width * 1 - x_border, total_height - button_height - y_border, button_width, button_height, SWP_NOZORDER);
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
   Editbox->SetFocus();

   Editbox->PostMessage(
      WM_KEYDOWN,
      KeyEventWParam,
      KeyEventLParam);
   }

void TMyCommandWindow::DoEditBox(UINT)
   {
   }

void TMyCommandWindow::DoListBox(UINT)
   {
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

   // if we just poped up editor then don't set focus to commander input
   if (!JustDidEdit)
      {
      Editbox->SetFocus();
      }
   JustDidEdit = false;
   }

void TMyCommandWindow::DoButtonEdall(UINT)
   {
   do_execution("Edallbtn");
   }

void TMyCommandWindow::DoButtonStatus(UINT)
   {

   // toggle status state along with poping up and killing the status window

   if (status_flag)
      {
      MainWindowx->MyPopupStatusKill();
      Editbox->SetFocus();
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

   Editbox->SetFocus();
   }

void TMyCommandWindow::DoButtonYield(UINT)
   {
   /* toggle yield state */

   /*
      if (yield_flag)
         {
         yield_flag = 0;
         SendDlgItemMsg(ID_YIELD, WM_SETTEXT, 0, (DWORD) "Yield");
         }
      else
         {
         yield_flag = 1;
         SendDlgItemMsg(ID_YIELD, WM_SETTEXT, 0, (DWORD) "NoYield");
         }
   */
   if (stepflag)
      {
      stepflag = 0;
      SetDlgItemText(ID_YIELD, "Step");
      }
   else
      {
      stepflag = 1;
      SetDlgItemText(ID_YIELD, "UnStep");
      }

   Editbox->SetFocus();
   }

void TMyCommandWindow::DoButtonPause(UINT)
   {

   // if ok to halt then it's ok to pause if we get here
   Editbox->SetFocus();
   if (halt_flag != 0)
      {
      IsTimeToPause = true;
      }
   }

// Will put back later
//
//void do_pause_update(long arg)
//   {
//   if (arg)
//      {
//      sprintf(YABuffer,"Pause-%d",(int)arg);
//      }
//   else
//      {
//      sprintf(YABuffer,"Pause");
//      }
//   MainWindowx->CommandWindow->
//   SendDlgItemMsg(ID_PAUSE, WM_SETTEXT, 0, (DWORD)YABuffer);
//   }

void TMyCommandWindow::EvKeyDown(UINT, UINT, UINT)
   {
   TMessage Msg = __GetTMessage();

   if (EditBoxWantsKeyEvent(Msg.WParam))
      {
         // we don't want this key press.
         // give it to the edit box.
         PostKeyDownToEditBox(Msg.WParam, Msg.LParam);
      }
   }


void TMyCommandWindow::DoButtonTrace(UINT)
   {

   /* toggle trace state */

   if (traceflag)
      {
      traceflag = 0;
      SetDlgItemText(ID_TRACE, "Trace");
      }
   else
      {
      traceflag = 1;
      SetDlgItemText(ID_TRACE, "UnTrace");
      }

   Editbox->SetFocus();
   }

void TMyCommandWindow::DoButtonHalt(UINT)
   {

   for (int i = 1; i < 32; i++)
      {
      MainWindowx->KillTimer(i);
      }

   /* if ok to halt and we get here then halt */
   Editbox->SetFocus();
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

   delete Editbox;
   Editbox = NULL;

   delete Listbox;
   Listbox = NULL;

   delete TraceButton;
   TraceButton = NULL;

   delete ResetButton;
   ResetButton = NULL;

   delete PauseButton;
   PauseButton = NULL;

   delete HaltButton;
   HaltButton = NULL;

   delete StatusButton;
   StatusButton = NULL;

   delete YieldButton;
   YieldButton = NULL;

   delete EdallButton;
   EdallButton = NULL;

   delete ExecuteButton;
   ExecuteButton = NULL;

   if (Font)
      {
      DeleteObject(Font);
      Font = NULL;
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
      Listbox->SetWindowFont(hFont, TRUE);
      Editbox->SetWindowFont(hFont, TRUE);

      // commit to the new font
      if (Font)
         {
         DeleteObject(Font);
         }
      Font = hFont;
      }
   }


NODE *lhalt(NODE *)
   {
   MainWindowx->CommandWindow->PostMessage(WM_COMMAND, ID_HALT, ID_HALT);
   return UNBOUND;
   }

NODE *lyield(NODE *)
   {

   // set flag and update button label

   yield_flag = 1;
   //   MainWindowx->CommandWindow->
   //   SendDlgItemMsg(ID_YIELD, WM_SETTEXT, 0, (DWORD) "NoYield");
   return UNBOUND;
   }

NODE *lnoyield(NODE *)
   {

   // clear flag and update button label

   yield_flag = 0;
   //   MainWindowx->CommandWindow->
   //   SendDlgItemMsg(ID_YIELD, WM_SETTEXT, 0, (DWORD) "Yield");
   return UNBOUND;
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
           MainWindowx->CommandWindow->Listbox->SetFocus();
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

   if ((Msg.WParam == VK_DOWN))
      {
      UINT from;
      UINT to;

      GetSelection(from, to);
      if (GetTextLen() == to)
         {
         MainWindowx->CommandWindow->Editbox->SetFocus();
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
      MainWindowx->CommandWindow->Editbox->SetText(buf);
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
   MainWindowx->CommandWindow->Editbox->SetText(buf);
   }

void TMyListboxWindow::EvLButtonDblClk(UINT /* modKeys */, TPoint & /* point */)
   {
   DefaultProcessing();

   char buf[MAX_BUFFER_SIZE];
   GetLine(buf, MAX_BUFFER_SIZE, GetLineFromPos(-1));
   MainWindowx->CommandWindow->Editbox->SetText(buf);
   MainWindowx->CommandWindow->DoButtonExecute(0);
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
  EV_WM_KEYDOWN,
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

