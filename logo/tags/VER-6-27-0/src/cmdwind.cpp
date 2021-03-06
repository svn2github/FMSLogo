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

#include <owl/compat.h>

#include "cmdwind.h"
#include "logorc.h"
#include "localizedstrings.h"
#include "main.h"
#include "startup.h"
#include "eval.h"
#include "wrksp.h"
#include "graphwin.h"
#include "utils.h"
#include "statwind.h"
#include "eval.h"
#include "init.h"
#include "error.h"
#include "coms.h"
#include "print.h"
#include "logodata.h"
#include "mem.h"
#include "parse.h"
#include "mainwind.h"
#include "mainframe.h"
#include "debugheap.h"

#define SELECTBOTTOMLINE

TMyCommandWindow::TMyCommandWindow(
    TWindow *Parent,
    TResId   ResId
    ) : 
    TDialog(Parent, ResId),
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
    Font(NULL),
    m_EditboxHeight(10 * BaseUnitsy / 8),
    m_ButtonWidth(34 * BaseUnitsx / 4)
{
    SetCaption(LOCALIZED_COMMANDER);
    hAccel = GetApplication()->LoadAccelerators("COMMANDERACC");
}

TMyCommandWindow::~TMyCommandWindow()
{
    if (Font)
    {
        DeleteObject(Font);
    }
}

void
TMyCommandWindow::UpdateFont(const LOGFONT & NewFont)
{
    HFONT font = CreateFontIndirect(&NewFont);
    if (font != NULL)
    {
        // use the new font
        Editbox.SetWindowFont(font, TRUE);
        Listbox.SetWindowFont(font, TRUE);

        // calculate the desired height for the edit box
        HDC editboxDC = GetDC(Editbox.HWindow);
        if (editboxDC != NULL)
        {
            HFONT oldFont = (HFONT) SelectObject(editboxDC, font);

            TEXTMETRIC metrics;
            BOOL isOk = GetTextMetrics(editboxDC, &metrics);
            if (isOk)
            {
                // font height + some padding
                m_EditboxHeight = metrics.tmHeight + 6;
            }

            SelectObject(editboxDC, oldFont);

            ReleaseDC(Editbox.HWindow, editboxDC);
        }

        // commit to the new font
        if (Font)
        {
            DeleteObject(Font);
        }
        Font = font;
    }
}

void TMyCommandWindow::SetupWindow()
{
    TDialog::SetupWindow();

    Editbox.Create();

    Listbox.Create();

    // Create the windows for the buttons and set the text.
    // We set the text so that Windows XP will use Unicode text,
    // instead of the ANSI text in the resource file.
    // If we don't do this, the text uses the wrong code page and
    // Greek looks like gibberish.
    TraceButton.Create();
    UpdateTraceButtonState();

    ResetButton.Create();
    ResetButton.SetWindowText(LOCALIZED_COMMANDER_RESET);

    PauseButton.Create();
    PauseButton.SetWindowText(LOCALIZED_COMMANDER_PAUSE);

    HaltButton.Create();
    HaltButton.SetWindowText(LOCALIZED_COMMANDER_HALT);

    StatusButton.Create();
    UpdateStatusButtonState();

    YieldButton.Create();
    UpdateYieldButtonState();

    EdallButton.Create();
    EdallButton.SetWindowText(LOCALIZED_COMMANDER_EDALL);

    ExecuteButton.Create();
    ExecuteButton.SetWindowText(LOCALIZED_COMMANDER_EXECUTE);

    LOGFONT lf;
    GetConfigurationFont("CommanderFont", lf);

    UpdateFont(lf);

    // calculate the desired width for the buttons
    HDC buttonDC = GetDC(EdallButton.HWindow);
    if (buttonDC != NULL)
    {
        // Iterate through all labels that we put on buttons 
        // and figure out the length of the longest one.
        const char * buttonLabels[] = 
        {
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

        LONG longestWidth = 0;

        for (int i = 0; i < ARRAYSIZE(buttonLabels); i++)
        {
            SIZE buttonLabelSize;

            BOOL isOk = GetTextExtentPoint32(
                buttonDC,
                buttonLabels[i],
                strlen(buttonLabels[i]),
                &buttonLabelSize);
            if (isOk)
            {
                if (longestWidth < buttonLabelSize.cx)
                {
                    // we found a new longest string
                    longestWidth = buttonLabelSize.cx;
                }
            }
        }
      
        m_ButtonWidth = longestWidth + 20;

        ReleaseDC(EdallButton.HWindow, buttonDC);
    }

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

    const int total_width   = commanderRect.Width();
    const int total_height  = commanderRect.Height();
    const int button_height = buttonRect.Height();
    const int button_width  = m_ButtonWidth;

    const int x_border = 4;
    const int y_border = 4;
    const int padding  = 6;

    EdallButton.SetWindowPos(NULL,   total_width - button_width * 1 - x_border, total_height - button_height - y_border, button_width, button_height, 0);
    ExecuteButton.SetWindowPos(NULL, total_width - button_width * 2 - x_border, total_height - button_height - y_border, button_width, button_height, 0);
    
    ResetButton.SetWindowPos(NULL,  total_width - button_width * 1 - x_border, button_height * 2 + y_border, button_width, button_height, 0);
    YieldButton.SetWindowPos(NULL,  total_width - button_width * 2 - x_border, button_height * 2 + y_border, button_width, button_height, 0);
    StatusButton.SetWindowPos(NULL, total_width - button_width * 1 - x_border, button_height * 1 + y_border, button_width, button_height, 0);
    PauseButton.SetWindowPos(NULL,  total_width - button_width * 2 - x_border, button_height * 1 + y_border, button_width, button_height, 0);
    TraceButton.SetWindowPos(NULL,  total_width - button_width * 1 - x_border, button_height * 0 + y_border, button_width, button_height, 0);
    HaltButton.SetWindowPos(NULL,   total_width - button_width * 2 - x_border, button_height * 0 + y_border, button_width, button_height, 0);

    Editbox.SetWindowPos(NULL, x_border, total_height - m_EditboxHeight - y_border, total_width - button_width * 2 - x_border - padding, m_EditboxHeight,                          0);
    Listbox.SetWindowPos(NULL, x_border, 0,                                        total_width - button_width * 2 - x_border - padding, total_height - m_EditboxHeight - padding, 0);

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
        YieldButton.SetWindowText(LOCALIZED_COMMANDER_UNSTEP);
        YieldButton.SetCheck(BF_CHECKED);
    }
    else
    {
        YieldButton.SetWindowText(LOCALIZED_COMMANDER_STEP);
        YieldButton.SetCheck(BF_UNCHECKED);
    }
}

void TMyCommandWindow::UpdateTraceButtonState()
{
    if (traceflag)
    {
        TraceButton.SetWindowText(LOCALIZED_COMMANDER_NOTRACE);
        TraceButton.SetCheck(BF_CHECKED);
    }
    else
    {
        TraceButton.SetWindowText(LOCALIZED_COMMANDER_TRACE);
        TraceButton.SetCheck(BF_UNCHECKED);
    }
}

void TMyCommandWindow::UpdateStatusButtonState()
{
    if (status_flag)
    {
        StatusButton.SetWindowText(LOCALIZED_COMMANDER_NOSTATUS);
        StatusButton.SetCheck(BF_CHECKED);
    }
    else
    {
        StatusButton.SetWindowText(LOCALIZED_COMMANDER_STATUS);
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


void TMyCommandWindow::DoButtonExecute(UINT)
{
    GiveFocusToEditbox = true;

    char   buffer[MAX_BUFFER_SIZE];
    char * text;

    // figure out how many characters are in the combobox
    int textLength = Editbox.GetLineLength(0);
    if (textLength < MAX_BUFFER_SIZE)
    {
        // this is small enough that we don't need an allocation
        text = buffer;
    }
    else
    {
        // this is too large to hold in our static buffer,
        // so we must dynamically allocate the memory.
        text = new char[textLength + sizeof(char)];
    }

    // GetText() always appends the NUL terminator
    Editbox.GetText(text, textLength + 1);
    Editbox.Clear();

    RunLogoInstructionFromGui(text);

    if (text != buffer)
    {
        // we must delete what we allocated
        delete [] text;
    }


    // calling RunLogoInstructionFromGui() can delete the "this" pointer,
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
    }
    else
    {
        MainWindowx->MyPopupStatus();
    }

    Editbox.SetFocus();
}

void TMyCommandWindow::DoButtonReset(UINT)
{
    // run 'CLEARSCREEN' and return focus
    char instruction[MAX_BUFFER_SIZE];
   
    cap_strnzcpy(
        instruction,
        LOCALIZED_ALTERNATE_CLEARSCREEN, 
        STRINGLENGTH(LOCALIZED_ALTERNATE_CLEARSCREEN));
    
    RunLogoInstructionFromGui(instruction);

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
//{
//   char buffer[256];
//   if (arg)
//   {
//      sprintf(buffer, "Pause-%d", arg);
//   }
//   else
//   {
//      sprintf(buffer, "Pause");
//   }
//   MainWindowx->CommandWindow->PauseButton->SetWindowText(buffer);
//}


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

void TMyCommandWindow::CmEditAll()
{
    do_execution("EDALL");
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
        // save the new font preference to persistent storage
        SetConfigurationFont("CommanderFont", lf);

        UpdateFont(lf);

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
    // set flag
    yield_flag = true;
    return Unbound;
}

NODE *lnoyield(NODE *)
{
    // clear flag
    yield_flag = false;
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
        // advance to the bottom of the listbox
        MainWindowx->CommandWindow->Listbox.SetCursorAtBottom();

        // give focus to the listbox
        MainWindowx->CommandWindow->Listbox.SetFocus();
        break;

    case VK_F1:
        ContextHelp(this);
        break;
    }

    DefaultProcessing();
}

void TMyEditboxWindow::EvSetFocus(THandle hWndGetFocus)
{
    DefaultProcessing();

    // unselect anything that is selected in the listbox to 
    // prevent the confusion of potentially seeing something
    // selected in both the commander's edit box and the history.
    UINT begin;
    UINT end;
    MainWindowx->CommandWindow->Listbox.GetSelection(begin, end);
    MainWindowx->CommandWindow->Listbox.SetSelection(begin, begin);
}

/* Listbox members */

TMyListboxWindow::TMyListboxWindow(
    TWindow *AParent,
    int      AId
    ) : 
    TRichEditWithPopup(AParent, AId),
    m_IsControlKeyDown(false),
    m_IsLeftControlKeyDown(false),
    m_IsRightControlKeyDown(false)
{
    PopupMenu.AppendMenu(MF_STRING, CM_EDITCOPY,      LOCALIZED_POPUP_COPY);
    PopupMenu.AppendMenu(MF_STRING, CM_EDITSELECTALL, LOCALIZED_POPUP_SELECTALL);
    PopupMenu.AppendMenu(MF_SEPARATOR, 0, NULL);
    PopupMenu.AppendMenu(MF_STRING, CM_HELPEDIT_TOPIC, LOCALIZED_POPUP_HELP);
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

void TMyListboxWindow::CmFileSave()
{
    // Delegate this to the main window so that we save
    // the workspace, instead of the contents of the commander 
    // listbox.
    MainWindowx->CMFileSave();
}

void TMyListboxWindow::CmFileSaveAs()
{
    // Delegate this to the main window so that we save
    // the workspace, instead of the contents of the commander 
    // listbox.
    MainWindowx->CMFileSaveAs();
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

    int currentline = GetLineFromPos(-1);

    // Look for the first line backwards from the current line
    // that doesn't ends in an EOL sequence.
    // This tells us where this line really begins (ignoring word-wrapping)
    for (int prevline = currentline - 1;
         0 <= prevline;
         prevline--)
    {
        bool isok = GetLine(buf, sizeof buf, prevline);
        if (!isok)
        {
            break;
        }

        // advance to the last char in buf
        char * ptr = buf + strlen(buf) - 1;
        if (*ptr == '\n' || *ptr == '\r')
        {
            // we reached a line that ends in an EOL
            break;
        }

        // This line does not end in an EOL sequence.
        // Therefore, it is part of the current line.
        currentline = prevline;
    }
   
    // read as many word-wrapped lines as it takes to get to the end of a real line
    char * ptr = buf;
    char * end = buf + sizeof(buf) - 1;
    while (ptr < end)
    {
        bool isok = GetLine(ptr, end - ptr, currentline);
        if (!isok)
        {
            break;
        }

        if (*ptr == '\0')
        {
            // The line was blank.  
            // This happens when the commander is squished such that
            // it can't hold a single character.
            // We must detect this condition and break out to avoid an inifnite loop.
            // See bug #1652924 for details.
            break;
        }

        // advance to the last char in buf
        ptr = ptr + strlen(ptr) - 1;

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
         buf <= stringend && IsSpace(*stringend);
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
        // If the caret moves down off bottom, then give focus to edit box.
        // NOTE: This logic must come before DefaultProcessing() when the cursor 
        // is already at the bottom in order to prevent an extra beep.
        if (Msg.WParam == VK_DOWN && !HasSelection())
        {
            if (IsCursorAtBottom())
            {
                MainWindowx->CommandWindow->Editbox.SetFocus();
                return;
            }
        }

        // up&down keys move up and down
        DefaultProcessing();
        CopyCurrentLineToEditBox();

#ifndef SELECTBOTTOMLINE
        // If the caret moves down off bottom, then give focus to edit box.
        if (Msg.WParam == VK_DOWN && !HasSelection())
        {
            if (IsCursorAtBottom())
            {
                MainWindowx->CommandWindow->Editbox.SetFocus();
            }
        }
#endif

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

void TMyListboxWindow::CmEnableCommand(TCommandEnabler& commandHandler)
{
    // Enables this command.
    // Used to keep Save and Save As enabled on the main window.
    commandHandler.Enable(true);
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

#ifndef SELECTBOTTOMLINE
    // Don't select the empty line at the bottom.
    int totalLines = GetNumLines();
    if (totalLines != 0)
    {
        endOfText = GetLineIndex(totalLines - 2);
    }
#endif

    SetSelection(endOfText, endOfText);

    // copy the bottom line to the edit box
    CopyCurrentLineToEditBox();

    Invalidate(true);
}

bool TMyListboxWindow::IsCursorAtBottom() const
{
    UINT from;
    UINT to;
    GetSelection(from, to);
    return GetTextLen() == to;
}

DEFINE_RESPONSE_TABLE1(TMyEditboxWindow, TEdit)
    EV_WM_SETFOCUS,
    EV_WM_KEYDOWN,
    EV_COMMAND(CM_EDITSELECTALL, CmSelectAll),
END_RESPONSE_TABLE;

DEFINE_RESPONSE_TABLE1(TMyListboxWindow, TRichEditWithPopup)
    EV_WM_CHAR,
    EV_WM_KEYDOWN,
    EV_WM_KEYUP,
    EV_WM_LBUTTONDOWN,
    EV_WM_LBUTTONDBLCLK,
    EV_WM_MOUSEMOVE,
    EV_COMMAND(CM_EDITPASTE,  CmEditPaste),
    EV_COMMAND(CM_FILESAVE,   CmFileSave),
    EV_COMMAND(CM_FILESAVEAS, CmFileSaveAs),
    EV_COMMAND_ENABLE(CM_FILESAVE,   CmEnableCommand),  // always enabled
    EV_COMMAND_ENABLE(CM_FILESAVEAS, CmEnableCommand),  // always enabled   
    EV_COMMAND_ENABLE(CM_EDITPASTE,  CmDisableCommand), // always disabled
    EV_COMMAND_ENABLE(CM_EDITCUT,    CmDisableCommand), // always disabled
    EV_COMMAND_ENABLE(CM_EDITUNDO,   CmDisableCommand), // always disabled
    EV_COMMAND_ENABLE(CM_EDITDELETE, CmDisableCommand), // always disabled
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
    EV_COMMAND(IDCANCEL,   CmCancel),
    EV_COMMAND(IDOK,       CmOk),
    EV_COMMAND(CM_EDITALL, CmEditAll),
END_RESPONSE_TABLE;

