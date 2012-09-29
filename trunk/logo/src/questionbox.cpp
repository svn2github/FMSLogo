// Copyright (C) 2012 by the David Costanzo
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
//

#include "questionbox.h"

#include <algorithm>

#include "logorc.h"
#include "mainframe.h"
#include "localizedstrings.h"
#include "debugheap.h"


TQuestionBox::TQuestionBox(
    TWindow *    Parent,
    const char * Title,
    const char * Question
    ) : TDialog(Parent, IDD_QUESTIONBOX),
        m_Question(this, ID_QUESTIONBOX_QUESTION),
        m_Answer(this, ID_QUESTIONBOX_ANSWER),
        m_OkButton(this, IDOK),
        m_CancelButton(this, IDCANCEL),
        m_QuestionBuffer(Question),
        m_AnswerBuffer(NULL)
{
    SetCaption(Title);
}

TQuestionBox::~TQuestionBox()
{
    delete [] m_AnswerBuffer;
}

void TQuestionBox::SetupWindow()
{
    TDialog::SetupWindow();

    // Note that the buttons must be first and go from right-to-left
    static const MENUITEM staticText[] = {
        {LOCALIZED_QUESTIONBOX_OK,     IDOK},
        {LOCALIZED_QUESTIONBOX_CANCEL, IDCANCEL},
    };

    // Set the text in all of the static controls
    SetTextOnChildWindows(this, staticText, ARRAYSIZE(staticText));

    m_OkButton.Create();
    m_CancelButton.Create();
    m_Question.Create();
    m_Question.SetText(m_QuestionBuffer);
    m_Answer.Create();

    //
    // Resize and reposition all of the controls based on how
    // much space the title and question take up.
    //

    TWindowDC questionDeviceContext(m_Question);

    // Initially, the device context's font is set to System, which
    // is what the title is drawn in.
    TSize titleSize = questionDeviceContext.GetTextExtent(
        Title,
        strlen(Title));

    HFONT questionFont = m_Question.GetWindowFont();
    if (questionFont != NULL)
    {
        questionDeviceContext.SelectObject(questionFont);
    }

    // Determine the extent of the question,
    // using some minimum value so that the dialog box
    // doesn't get too small.
    const int MINIMUM_TEXT_WIDTH = 200;
    int questionX = MINIMUM_TEXT_WIDTH;
    int questionY = 0;

    const char * lineStart = m_QuestionBuffer;
    while (*lineStart != '\0')
    {
        // Find where this line ends
        const char * lineEnd = lineStart;
        while (*lineEnd != '\0' && *lineEnd != '\r' && *lineEnd != '\n')
        {
            lineEnd++;
        }

        // Get the size of this line
        TSize lineSize = questionDeviceContext.GetTextExtent(
            lineStart,
            lineEnd - lineStart);

        // Grow the amount of space we're holding for the question
        // to include this line.
        questionX  = std::max(lineSize.X(), questionX);
        questionY += lineSize.Y();

        // Increment to the next line
        if (lineEnd[0] == '\r' && lineEnd[1] == '\n')
        {
            // Treat CRLF as a single newline, like the dialog box will.
            lineStart = lineEnd + 2;
        }
        else if (lineEnd[0] != '\0')
        {
            // Advance past the newline or carriage return.
            lineStart = lineEnd + 1;
        }
        else
        {
            // Set lineStart at the NUL to break out of the loop.
            lineStart = lineEnd;
        }
    }

    const int answerHeight = 22;
    const int padding      = 5;
    const int buttonWidth  = 70;
    const int buttonHeight = 26;

    // The window should be wide enough to hold
    // both the complete title and the complete question.
    const int overallWidth = std::max(questionX, titleSize.X());

    m_Question.SetWindowPos(
        NULL,
        padding,
        padding,
        questionX,
        questionY,
        SWP_NOZORDER);

    // The answer field is positioned just below the question.
    const int answerLineTop = padding + questionY + padding;
    m_Answer.SetWindowPos(
        NULL,
        padding,          // left
        answerLineTop,    // top
        overallWidth,     // width
        answerHeight,     // height
        SWP_NOZORDER);

    // The OK and cancel buttons are just below the answer
    const int buttonLineTop = answerLineTop + answerHeight + padding;

    m_OkButton.SetWindowPos(
        NULL,
        overallWidth - 2 * buttonWidth,    // left
        buttonLineTop,                     // top
        buttonWidth,                       // width
        buttonHeight,                      // height
        SWP_NOZORDER);

    // The OK and cancel buttons are just below the answer
    m_CancelButton.SetWindowPos(
        NULL,
        padding + overallWidth - buttonWidth, // left
        buttonLineTop,                        // top
        buttonWidth,                          // width
        buttonHeight,                         // height
        SWP_NOZORDER);

    //
    // Resize the window to fit the controls
    //

    // Calculate how much space the window frame takes up.
    const TRect overallRect = GetWindowRect();
    const TRect clientRect  = GetClientRect();

    int extraWidth  = overallRect.Width()  - clientRect.Width();
    int extraHeight = overallRect.Height() - clientRect.Height();

    SetWindowPos(
        NULL,
        0,
        0,
        extraWidth + overallWidth + 2 * padding,
        extraHeight + buttonLineTop + buttonHeight + padding,
        SWP_NOMOVE);

    if (questionFont != NULL)
    {
        questionDeviceContext.RestoreFont();
    }
}

void TQuestionBox::CmOk()
{
    // reset any value that may be in the editor
    delete [] m_AnswerBuffer;

    // copy the data from the rich edit into a flat buffer
    int answerLength = m_Answer.GetWindowTextLength();

    m_AnswerBuffer = new char [answerLength + 1];
    if (m_AnswerBuffer != NULL)
    {
        m_Answer.GetWindowText(m_AnswerBuffer, answerLength + 1);
    }

    TDialog::CmOk();
}

const char * TQuestionBox::GetAnswer() const
{
    return m_AnswerBuffer;
}

DEFINE_RESPONSE_TABLE1(TQuestionBox, TDialog)
    EV_COMMAND(IDOK, CmOk),
END_RESPONSE_TABLE;
