// Copyright 1998-2001 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>

#include "Platform.h"

#include "PropSet.h"
#include "Accessor.h"
#include "KeyWords.h"
#include "Scintilla.h"
#include "SciLexer.h"
#include "StyleContext.h"

#ifdef SCI_NAMESPACE
using namespace Scintilla;
#endif

static inline bool IsAWordChar(const int ch) 
{
    switch (ch)
    {
    case ' ':
    case '\t':
    case '\n':
    case '\r':

    case '(':
    case ')':
    case '{':
    case '}':
    case '[':
    case ']':

    case '+':
    case '-':
    case '/':
    case '*':
    case '>':
    case '<':
    case '=':
        return false;

    default:
        return true;
    }
}

static inline bool IsAWordStart(const int ch) 
{
    return isalnum(ch) || ch == '_' || ch == '?';
}

static inline bool IsStateString(const int state)
{
    return ((state == SCE_FMS_STRING) || (state == SCE_FMS_STRING_VBAR));
}

static inline bool IsStateComment(const int state)
{
    return ((state == SCE_FMS_COMMENT) || (state == SCE_FMS_COMMENTBACKSLASH));
}

static
void
ColorizeFmsLogoDoc(
    unsigned int   startPos,
    int            length, 
    int            initStyle,
    WordList    *  keywordlists[],
    Accessor    &  styler
    ) 
{
    WordList &keywords  = *keywordlists[0];
    WordList &keywords2 = *keywordlists[1];
    WordList &keywords3 = *keywordlists[2];
    WordList &keywords4 = *keywordlists[3];
    WordList &keywords5 = *keywordlists[4];
    WordList dynkeylist;

    char s[100];

    StyleContext sc(startPos, length, initStyle, styler);
    for (; sc.More(); sc.Forward()) 
    {
        // Handle line continuation generically.
        if (sc.ch == '~') 
        {
            if (sc.chNext == '\n' || sc.chNext == '\r') 
            {
                // This was a line continuation, which breaks a comment
                if (IsStateComment(sc.state))
                {
                    sc.SetState(SCE_FMS_DEFAULT);
                }

                sc.Forward();
                if (sc.ch == '\r' && sc.chNext == '\n') 
                {
                    sc.Forward();
                }
                continue;
            }
        }

        // Determine if the current state should terminate.
        switch (sc.state)
        {
        case SCE_FMS_OPERATOR:
            sc.SetState(SCE_FMS_DEFAULT);
            break;

        case SCE_FMS_NUMBER:
            if (!IsAWordChar(sc.ch)) 
            {
                sc.SetState(SCE_FMS_DEFAULT);
            }
            break;

        case SCE_FMS_IDENTIFIER:
            if (!IsAWordChar(sc.ch))
            {
                sc.GetCurrent(s, sizeof(s));
				
                if (keywords.InList(s)) 
                {
                    sc.ChangeState(SCE_FMS_KEYWORD1);
                }
                else if (keywords2.InList(s)) 
                {
                    sc.ChangeState(SCE_FMS_KEYWORD2);
                }
                else if (keywords3.InList(s)) 
                {
                    sc.ChangeState(SCE_FMS_KEYWORD3);
                }
                else if (keywords4.InList(s)) 
                {
                    sc.ChangeState(SCE_FMS_KEYWORD4);
                }
                else if (keywords5.InList(s)) 
                {
                    sc.ChangeState(SCE_FMS_KEYWORD5);
                }
                else if (dynkeylist.InList(s)) 
                {
                    sc.ChangeState(SCE_FMS_KEYWORD6);
                }
                sc.SetState(SCE_FMS_DEFAULT);
            }
            break;

        case SCE_FMS_TO:
            char s[100];
            sc.GetCurrent(s, sizeof(s));
            sc.ChangeState(SCE_FMS_TO);
            sc.ForwardSetState(SCE_FMS_TODEF);
            break;

        case SCE_FMS_TODEF:
            if (IsASpace(sc.ch))
            {
                char s[100];
                sc.GetCurrent(s, sizeof(s));
#if 0				
                if (!dynkeylist.InList(s))
                {
                    aUCBLogo_dynkeystring+=wxString(s)+" ";
                    dynkeylist.Clear();
                    dynkeylist.Set(aUCBLogo_dynkeystring);
                    sc.ChangeState(SCE_FMS_KEYWORD6);
                }
#endif
                sc.ChangeState(SCE_FMS_KEYWORD6);
                sc.SetState(SCE_FMS_DEFAULT);
            }
            break;

        case SCE_FMS_END:
            sc.GetCurrent(s, sizeof(s));
			
            sc.ChangeState(SCE_FMS_END);
            sc.SetState(SCE_FMS_DEFAULT);
            break;
		
        case SCE_FMS_STRING:
            if (sc.ch == '|')
            {
                sc.SetState(SCE_FMS_STRING_VBAR);
                sc.Forward();
            }
            else if (sc.ch == '\\') 
            {
                sc.Forward();
            }
            else if (sc.atLineEnd  ||
                     sc.ch == ' '  ||
                     sc.ch == '\t' ||
                     sc.ch == '('  ||
                     sc.ch == ')'  ||
                     sc.ch == '['  ||
                     sc.ch == ']'  ||
                     sc.ch == '{'  ||
                     sc.ch == '}'  ||
                     sc.ch == ';') 
            {
                sc.SetState(SCE_FMS_DEFAULT);
            }
            break;

        case SCE_FMS_STRING_VBAR:
            while (sc.ch != '|' && sc.More())
            {
                sc.Forward();
            }
            sc.SetState(SCE_FMS_STRING);
            break;

        case SCE_FMS_VBAR:
            while (sc.ch != '|' && sc.More())
            {
                sc.Forward();
            }
            sc.SetState(SCE_FMS_DEFAULT);
            sc.Forward();
            break;

        case SCE_FMS_COMMENT:
            // comments end at a newline, but can be continued
            // onto the next line if the newline is preceeded by
            // a backslash
            if (sc.Match("~\r\n") || sc.Match("~\n"))
            {
                // transition to continuation char state?
                sc.SetState(SCE_FMS_DEFAULT);
            }
            else if (sc.atLineEnd)
            {
                sc.SetState(SCE_FMS_DEFAULT);
            }
            else if (sc.ch == '\\')
            {
                sc.SetState(SCE_FMS_COMMENTBACKSLASH);
            }
            break;

        case SCE_FMS_COMMENTBACKSLASH:
            if (sc.ch == '\r' || sc.ch == '\n')
            {
                sc.Forward();
                if (sc.ch == '\r' || sc.ch == '\n')
                {
                    // This was a backslash followed by a newline.
                    sc.Forward();
                }
            }
            sc.SetState(SCE_FMS_COMMENT);
            break;

        case SCE_FMS_VARIABLE:
            if (sc.ch == '|')
            {
                sc.SetState(SCE_FMS_VARIABLE_VBAR);
                sc.Forward();
            }
            else if (sc.ch == '\\') 
            {
                sc.Forward();
            }
            else if (!IsAWordChar(sc.ch))
            {
                sc.SetState(SCE_FMS_DEFAULT);
            }
            break;

        case SCE_FMS_VARIABLE_VBAR:
            while (sc.ch != '|' && sc.More())
            {
                sc.Forward();
            }
            sc.SetState(SCE_FMS_VARIABLE);
            sc.Forward();
            break;

        default:
            break;
        }

        // Determine if a new state should be entered.
        if (sc.state == SCE_FMS_DEFAULT) 
        {
            if (sc.atLineStart 
                && (sc.ch==' ' ||
                    sc.ch=='\t' ||
                    toupper(sc.ch)=='T' ||
                    toupper(sc.ch)=='B' ||
                    toupper(sc.ch)=='E'))
            {
                int opos=sc.currentPos;
                while ((sc.ch==' ' || sc.ch=='\t') && sc.More())
                {
                    sc.Forward();
                }

                if (sc.Match("to ")) 
                {
                    sc.SetState(SCE_FMS_TO);
                    sc.Forward();
                }
                else if (sc.Match("be ")) 
                {
                    sc.SetState(SCE_FMS_TO);
                    sc.Forward();
                }
                else if (sc.Match("end")) 
                {
                    sc.SetState(SCE_FMS_END);
                    sc.Forward();
                    sc.Forward();
                }
                else
                {
                    if (opos >= 1)
                    {
                        sc.currentPos=opos-1;
                    }
                    sc.Forward();
                }
            }
            else if (IsADigit(sc.ch) || (sc.ch == '.' && IsADigit(sc.chNext))) 
            {
                sc.SetState(SCE_FMS_NUMBER);
            }
            else if (sc.ch == ':')
            {
                sc.SetState(SCE_FMS_VARIABLE);
            }
            else if (sc.ch == '|')
            {
                sc.SetState(SCE_FMS_VBAR);
            }
            else if (sc.ch == ';' && sc.chPrev != '\\') 
            {
                sc.SetState(SCE_FMS_COMMENT);
            }
            else if (sc.ch == '\"') 
            {
                sc.SetState(SCE_FMS_STRING);
            }
            else if (isoperator(static_cast<char>(sc.ch)))
            {
                sc.SetState(SCE_FMS_OPERATOR);
            }
        }
    }
    sc.Complete();
}


static void FoldFmsLogoDoc(unsigned int, int, int, WordList *[], Accessor &)
{
}

static const char * const g_FmsLogoWordLists[] = 
{
    "Structural keywords",
    "Primitives",
    "Library procedures",
    "Abbreviations",
    "Special Variables",
    0,
};

LexerModule lmFmsLogo(SCLEX_FMSLOGO, ColorizeFmsLogoDoc, "FMSLogo", FoldFmsLogoDoc, g_FmsLogoWordLists);
