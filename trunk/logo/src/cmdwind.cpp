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

static int halt_flag = 0; // Flag to signal it's OK to halt

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
   Listbox(this, ID_LISTBOX),
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
   GetConfigurationFont("CommanderFont", lf);

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

   EdallButton.SetWindowPos(NULL,   total_width - button_width * 1 - x_border, total_height - button_height - y_border, button_width, button_height, 0);
   ExecuteButton.SetWindowPos(NULL, total_width - button_width * 2 - x_border, total_height - button_height - y_border, button_width, button_height, 0);

   ResetButton.SetWindowPos(NULL,  total_width - button_width * 1 - x_border, button_height * 2 + y_border, button_width, button_height, 0);
   YieldButton.SetWindowPos(NULL,  total_width - button_width * 2 - x_border, button_height * 2 + y_border, button_width, button_height, 0);
   StatusButton.SetWindowPos(NULL, total_width - button_width * 1 - x_border, button_height * 1 + y_border, button_width, button_height, 0);
   PauseButton.SetWindowPos(NULL,  total_width - button_width * 2 - x_border, button_height * 1 + y_border, button_width, button_height, 0);
   TraceButton.SetWindowPos(NULL,  total_width - button_width * 1 - x_border, button_height * 0 + y_border, button_width, button_height, 0);
   HaltButton.SetWindowPos(NULL,   total_width - button_width * 2 - x_border, button_height * 0 + y_border, button_width, button_height, 0);

   Editbox.SetWindowPos(NULL, x_border, total_height - editbox_height - y_border, total_width - button_width * 2 - x_border - padding, editbox_height,                          0);
   Listbox.SetWindowPos(NULL, x_border, 0,                                        total_width - button_width * 2 - x_border - padding, total_height - editbox_height - padding, 0);

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
   // OEM keys are not defined in Borland 5.0.2's header files
   const WPARAM VK_OEM_1   = 186;
   const WPARAM VK_OEM_102 = 226;

   // we want the space bar
   if (KeyEventWParam == VK_SPACE)
      {
      return true;
      }

   // we want the backspace and delete keys
   if (KeyEventWParam == VK_BACK || KeyEventWParam == VK_DELETE)
      {
      return true;
      }

   // we want alphanumeric keys
   if ('0' <= KeyEventWParam && KeyEventWParam <= 'Z')
      {
      return true;
      }

   // we want the printing characters from the numpad
   if (VK_NUMPAD0 <= KeyEventWParam && KeyEventWParam <= VK_DIVIDE)
      {
      return true;
      }

   // we want the "OEM" keys, which are usually punctiation and international characters
   if (VK_OEM_1 <= KeyEventWParam && KeyEventWParam <= VK_OEM_102)
      {
      return true;
      }

   // there are a few navigational keys that we also want.
   if (KeyEventWParam == VK_HOME || 
       KeyEventWParam == VK_END  || 
       KeyEventWParam == VK_RIGHT)
      {
      return true;
      }

   // reject everything else
   return false;
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

bool process_special_conditions()
   {
   bool error_happened = false;

   if (stopping_flag == THROWING)
      {
      if (compare_node(throw_node, Error, true) == 0)
         {
         err_print();
         error_happened = true;
         }
      else if (compare_node(throw_node, System, true) == 0)
         {
         PostQuitMessage(1); // set the exit code to 1
         prepare_to_exit(true);
         }
      else if (compare_node(throw_node, Toplevel, true) != 0)
         {
         err_logo(NO_CATCH_TAG, throw_node);
         err_print();
         error_happened = true;
         }

      stopping_flag = RUN;
      }

   if (stopping_flag == STOP || stopping_flag == OUTPUT)
      {
      // This is probably a bug, not a user error.
      // We shouldn't be able to get here without throwing
      // an AT_TOPLEVEL error, which would result in a 
      // stopping_flag of THROWING.
      ndprintf(
         stdout, 
         "You must be in a procedure to use OUTPUT or STOP.\n");
      stopping_flag = RUN;
      }


   return error_happened;
   }

void start_execution()
   {
   // if executing then it's ok to halt
   assert(0 <= halt_flag);

   halt_flag++;
   if (halt_flag < 1)
      {
      halt_flag = 1;
      }
   }

void stop_execution()
   {
   // not ok to halt now
   assert(1 <= halt_flag);

   halt_flag--;
   if (halt_flag < 0)
      {
      halt_flag = 0;
      }
   }

bool is_executing()
   {
   assert(0 <= halt_flag);
   return halt_flag != 0;
   }

void do_execution(char * logocommand)
   {
   // if something there continue
   if (strlen(logocommand) != 0)
      {
      start_execution();

      // this code emulates the TTY model used in UCBLOGO main loop
      NODETYPES this_type = STRING;

      // do control character processing processing
      for (char * c = logocommand; *c != '\0'; c++)
         {
         if (*c == '\\')
            {
            strcpy(c, c + 1);
            if (*c)
               {
               if (*c == 'n') 
                  {
                  *c = '\n';
                  }
               *c = setparity(*c);
               }
            this_type = BACKSLASH_STRING;
            }
         }

      check_reserve_tank();

      // Set the stopping_flag to RUN so that we don't print any spurious 
      // warnings about using OUTPUT or STOP while not in a procedure.
      // This is important because do_execution() can be called to process
      // event handlers while evaluator() is running.
      // See bug #1479111 for details.
      int      saved_val_status    = val_status;
      CTRLTYPE saved_stopping_flag = stopping_flag;
      NODE *   saved_output_node   = vref(output_node);
      NODE *   saved_current_line  = current_line;

      stopping_flag = RUN;

      // turn text into a NODE and parse it
      current_line = vref(make_strnode(
         logocommand, 
         (int) strlen(logocommand), 
         this_type, 
         strnzcpy));

      NODE * exec_list = vref(parser(current_line, true));

      // now process it
      val_status = 0;
      eval_driver(exec_list);

      process_special_conditions();

      // restore the stopping flag
      stopping_flag = saved_stopping_flag;
      val_status    = saved_val_status;

      deref(output_node);
      output_node = saved_output_node;

      // deallocate the line
      deref(current_line);
      current_line = saved_current_line;

      // this is a hack to force garbage collector to properly clean up
      if (exec_list != NIL)
         {
         settype(exec_list, CONS);
         deref(exec_list);
         }

      stop_execution();
      }
   }

void TMyCommandWindow::DoButtonExecute(UINT)
   {
   GiveFocusToEditbox = true;

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
   if (GiveFocusToEditbox)
      {
      MainWindowx->CommandWindow->Editbox.SetFocus();
      }
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
   if (is_executing())
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
   if (is_executing())
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

      SetConfigurationQuadruple(
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
   GetConfigurationFont("CommanderFont", lf);

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
      SetConfigurationFont("CommanderFont", lf);

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

void TMyEditboxWindow::CmSelectAll()
   {
   int endOfText = GetTextLen();
   SetSelection(0, endOfText);
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
         ContextHelp(this);
         break;
         }
      }

   DefaultProcessing();
   }

/* Listbox members */

TMyListboxWindow::TMyListboxWindow(
   TWindow *AParent,
   int      AId
   ) : TRichEditWithPopup(AParent, AId),
   m_IsControlKeyDown(false),
   m_IsLeftControlKeyDown(false),
   m_IsRightControlKeyDown(false)
   {
   PopupMenu.AppendMenu(MF_STRING, CM_EDITCOPY,      "Copy");
   PopupMenu.AppendMenu(MF_STRING, CM_EDITSELECTALL, "Select All");
   PopupMenu.AppendMenu(MF_SEPARATOR, 0, NULL);
   PopupMenu.AppendMenu(MF_STRING, CM_HELPEDIT_TOPIC, "Topic Search");
   }

bool TMyListboxWindow::CanClose()
   {
   // always return true because this is not tied to a file
   return true;
   }

void TMyListboxWindow::SetupWindow()
   {
   TRichEditWithPopup::SetupWindow();

   SetBkgndColor(TColor::SysMenu);
   }

TMyListboxWindow::~TMyListboxWindow()
   {
   }

void TMyListboxWindow::EvKillFocus(THandle hWndGetFocus /* may be 0 */)
   {
   // unselect whatever is selected when we lose focus
   UINT begin;
   UINT end;
   GetSelection(begin, end);
   SetSelection(begin, begin);

   DefaultProcessing();
   }


void TMyListboxWindow::EvMouseMove(uint modKeys, TPoint& point)
   {
   DefaultProcessing();

   // The TRichEdit clas doesn't set the cursor to anything when 
   // it's in the docked commander window, so we must set it to 
   // the arrow cursor.
   //
   // Note that the I-Bar is inappropriate because you can't type into it.
   ::SetCursor(hCursorArrow);
   }

void TMyListboxWindow::CopyCurrentLineToEditBox()
   {
   char buf[1024] = {0};

   char * ptr = buf;
   char * end = buf + sizeof(buf) - 1;
   int currentline = GetLineFromPos(-1);
   
   // read as many word-wrapped lines as it takes to get to the end of a real line
   while (ptr < end)
      {
      bool isok = GetLine(ptr, end - ptr, currentline);
      if (!isok)
         {
         break;
         }

      // advance to the last char in buf
      ptr = ptr + strlen(ptr) - 1;
      assert(ptr < end && "ptr is not NUL-terminated");

      if (*ptr == '\n' || *ptr == '\r')
         {
         // we reached the end of the line
         break;
         }

      // This line doesn't end in an EOL sequence.
      // This must be a word-wrapped line.

      if (end <= ptr + 2)
         {
         // buf can't hold any more characters
         break;
         }

      if (*ptr != ' ')
         {
         // append a space to the end of buf
         ptr++;
         ptr[0] = ' ';
         ptr[1] = '\0';
         }

      // advance to the NUL
      ptr++;
      currentline++;
      }

   // remove trailing whitespace
   for (char * stringend = buf + strlen(buf) - 1;
        buf <= stringend && isspace(*stringend);
        stringend--)
      {
      *stringend = '\0';
      }

   MainWindowx->CommandWindow->Editbox.SetText(buf);
   }

void TMyListboxWindow::EvChar(uint key, uint repeatCount, uint flags)
   {
   // ignore this (it was already processed in EvKeyDown)
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

   // track when a control key is pressed down
   if (Msg.WParam == VK_CONTROL)
      {
      m_IsControlKeyDown = true;
      }
   else if (Msg.WParam == VK_LCONTROL)
      {
      m_IsLeftControlKeyDown = true;
      }
   else if (Msg.WParam == VK_RCONTROL)
      {
      m_IsRightControlKeyDown = true;
      }

   if (Msg.WParam == VK_RETURN)
      {
      DefaultProcessing();
      }
   else if (IsControlKeyDown() && 
       (Msg.WParam == VK_HOME || Msg.WParam == VK_END))
      {
      // CTRL+HOME scrolls to the top
      // CTRL+END scrolls to the bottom
      DefaultProcessing();
      CopyCurrentLineToEditBox();
      }
   else if (IsControlKeyDown() && Msg.WParam == 'C')
      {
      // CTRL+C should copy
      DefaultProcessing();
      }
   else if (Msg.WParam == VK_UP   ||
            Msg.WParam == VK_DOWN ||
            Msg.WParam == VK_LEFT)
      {
      // up&down keys move up and down
      DefaultProcessing();
      CopyCurrentLineToEditBox();
      }
   else if (Msg.WParam == VK_F1)
      {
      ContextHelp(this);
      }
   else if (MainWindowx->CommandWindow->EditBoxWantsKeyEvent(Msg.WParam))
      {
         // we don't handle this key.
         // give focus to the edit box and send the press to it.
         MainWindowx->CommandWindow->PostKeyDownToEditBox(
            Msg.WParam,
            Msg.LParam);
      }
   else if (Msg.WParam == VK_NEXT  ||
            Msg.WParam == VK_PRIOR)
      {
      // special-case the few commands that we want to process
      DefaultProcessing();
      CopyCurrentLineToEditBox();
      }
   else
      {
      DefaultProcessing();
      }
   }

bool TMyListboxWindow::IsControlKeyDown()
   {
   return m_IsControlKeyDown || m_IsLeftControlKeyDown || m_IsRightControlKeyDown;
   }

void TMyListboxWindow::EvKeyUp(UINT, UINT, UINT)
   {
   TMessage Msg = __GetTMessage();

   // track when a control key is released
   if (Msg.WParam == VK_CONTROL)
      {
      m_IsControlKeyDown = false;
      }
   else if (Msg.WParam == VK_LCONTROL)
      {
      m_IsLeftControlKeyDown = false;
      }
   else if (Msg.WParam == VK_RCONTROL)
      {
      m_IsRightControlKeyDown = false;
      }

   DefaultProcessing();
   }

void TMyListboxWindow::EvLButtonDown(UINT /* modKeys */, TPoint & /* point */)
   {
   DefaultProcessing();

   CopyCurrentLineToEditBox();
   }

void TMyListboxWindow::EvLButtonDblClk(UINT /* modKeys */, TPoint & /* point */)
   {
   DefaultProcessing();

   CopyCurrentLineToEditBox();
   MainWindowx->CommandWindow->DoButtonExecute(0);
   }

void TMyListboxWindow::CmDisableCommand(TCommandEnabler& commandHandler)
   {
   // disables this command.
   // used to disable paste/undo/cut operations.
   commandHandler.Enable(false);
   }


void TMyListboxWindow::SetCursorAtBottom()
   {
   // scroll to the bottom
   int top;
   int bottom;
   GetScrollRange(SB_VERT, top, bottom);
   SetScrollPos(SB_VERT, bottom);

   // set the selection to the end of the text.
   int endOfText = GetTextLen();
   SetSelection(endOfText, endOfText);

   // copy the bottom line to the edit box
   CopyCurrentLineToEditBox();

   Invalidate(true);
   }

DEFINE_RESPONSE_TABLE1(TMyEditboxWindow, TEdit)
   EV_WM_KEYDOWN,
   EV_COMMAND(CM_EDITSELECTALL, CmSelectAll),
END_RESPONSE_TABLE;

DEFINE_RESPONSE_TABLE1(TMyListboxWindow, TRichEditWithPopup)
   EV_WM_KILLFOCUS,
   EV_WM_CHAR,
   EV_WM_KEYDOWN,
   EV_WM_KEYUP,
   EV_WM_LBUTTONDOWN,
   EV_WM_LBUTTONDBLCLK,
   EV_WM_MOUSEMOVE,
   EV_COMMAND(CM_EDITPASTE, CmEditPaste),
   EV_COMMAND_ENABLE(CM_EDITPASTE,  CmDisableCommand),
   EV_COMMAND_ENABLE(CM_EDITCUT,    CmDisableCommand),
   EV_COMMAND_ENABLE(CM_EDITUNDO,   CmDisableCommand),
   EV_COMMAND_ENABLE(CM_EDITDELETE, CmDisableCommand),
END_RESPONSE_TABLE;

DEFINE_RESPONSE_TABLE1(TMyCommandWindow, TDialog)
   EV_WM_SIZE,
   EV_WM_DESTROY,
   EV_WM_CLOSE,
   EV_CHILD_NOTIFY_ALL_CODES(ID_EXECUTE, DoButtonExecute),
   EV_CHILD_NOTIFY_ALL_CODES(ID_EDALL,   DoButtonEdall),
   EV_CHILD_NOTIFY_ALL_CODES(ID_HALT,    DoButtonHalt),
   EV_CHILD_NOTIFY_ALL_CODES(ID_STATUS,  DoButtonStatus),
   EV_CHILD_NOTIFY_ALL_CODES(ID_YIELD,   DoButtonYield),
   EV_CHILD_NOTIFY_ALL_CODES(ID_PAUSE,   DoButtonPause),
   EV_CHILD_NOTIFY_ALL_CODES(ID_TRACE,   DoButtonTrace),
   EV_CHILD_NOTIFY_ALL_CODES(ID_RESET,   DoButtonReset),
   EV_COMMAND(IDCANCEL, CmCancel),
   EV_COMMAND(IDOK, CmOk),
END_RESPONSE_TABLE;

