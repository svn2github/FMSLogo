// -*- c++ -*-
#ifndef _QUESTIONBOX_H_
#define _QUESTIONBOX_H_

#include <owl/edit.h>
#include <owl/button.h>
#include <owl/dialog.h>

class TQuestionBox : public TDialog
{
public:
    TQuestionBox(
        TWindow    * Parent,
        const char * Title,
        const char * Question
        );

    ~TQuestionBox();

    const char * GetAnswer() const;

protected:
    void SetupWindow();
    void CmOk();

private:
    TStatic   m_Question;
    TEdit     m_Answer;
    TButton   m_OkButton;
    TButton   m_CancelButton;

    const char * m_QuestionBuffer;
    char *       m_AnswerBuffer;

private:
    DECLARE_RESPONSE_TABLE(TQuestionBox);
};

#endif // _QUESTIONBOX_H_
