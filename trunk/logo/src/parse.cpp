/*
 *      parse.cpp       logo parser module              dvb
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

#include <algorithm>

FILE *loadstream = stdin;
FILE *dribblestream = NULL;
bool input_blocking = false;
NODE *deepend_proc_name = NIL;
NODE *g_ToLine          = NIL;

INPUTMODE input_mode = INPUTMODE_None;

static CDynamicBuffer g_ReadBuffer;

// A class for allocating and manipulating a buffer that
// is suitable for use with make_strnode_from_allocated_buffer().
// The intent of this class is to eliminate the need to copy
// the a buffer when allocating a string node.
class CStringNodeBuffer
{
    friend CBufferInvariant;

public:
    CStringNodeBuffer();
    ~CStringNodeBuffer();

    void TakeOwnershipOfBuffer();

    char * GetString();
    size_t GetStringLength() const;

    void AppendString(const char * ToAppend);
    void AppendChar(char ToAppend);

private:
    void GrowBy(size_t ExtraLength);

    char  *  m_Buffer;       // the buffer that holds the string
    size_t   m_BufferLength; // the size of the allocated buffer
    char *   m_StringLimit;  // a pointer to one beyond the end of the string
    bool     m_IsOwner;      // if this object must free m_Buffer
};

#ifdef NDEBUG
#  define ASSERT_STRINGNODE_INVARIANT
#else
#  define ASSERT_STRINGNODE_INVARIANT CBufferInvariant invariant(*this)

class CBufferInvariant
{
public:
    CBufferInvariant(const CStringNodeBuffer & StringNodeBuffer)
        : m_StringNodeBuffer(StringNodeBuffer)
    {
        AssertInvariant();
    }

    ~CBufferInvariant()
    {
        AssertInvariant();
    }

    void AssertInvariant() const
    {
        assert(m_StringNodeBuffer.m_Buffer != NULL);
        assert(m_StringNodeBuffer.m_Buffer + sizeof(unsigned short) <= m_StringNodeBuffer.m_StringLimit);
        assert(m_StringNodeBuffer.m_StringLimit - m_StringNodeBuffer.m_Buffer < (signed)m_StringNodeBuffer.m_BufferLength);
    }

private:
    const CStringNodeBuffer & m_StringNodeBuffer;
};

#endif // NDEBUG

CStringNodeBuffer::CStringNodeBuffer()
{
    const size_t DEFAULT_SIZE = 256;

    // allocate enough for the header, the string, and the NUL terminator
    m_BufferLength = sizeof(unsigned short) + DEFAULT_SIZE + 1;
    m_Buffer       = static_cast<char *>(malloc(m_BufferLength));
    m_StringLimit  = m_Buffer + sizeof(unsigned short);
    m_IsOwner      = true;
}

CStringNodeBuffer::~CStringNodeBuffer()
{
    if (m_IsOwner)
    {
        free(m_Buffer);
    }
}

void CStringNodeBuffer::TakeOwnershipOfBuffer()
{
    ASSERT_STRINGNODE_INVARIANT;

    // Reduce the size of the buffer to only what is needed.
    realloc(m_Buffer, m_StringLimit - m_Buffer + 1);

    // initialize the reference count to zero.
    *reinterpret_cast<unsigned short *>(m_Buffer) = 0;

    // set a flag that we don't own m_Buffer.
    m_IsOwner = false;
}

char * CStringNodeBuffer::GetString()
{
    ASSERT_STRINGNODE_INVARIANT;

    // NUL-terminate the buffer
    *m_StringLimit = '\0';
    return m_Buffer;
}

size_t CStringNodeBuffer::GetStringLength() const
{
    ASSERT_STRINGNODE_INVARIANT;

    return m_StringLimit - m_Buffer - sizeof(unsigned short);
}

void CStringNodeBuffer::GrowBy(size_t ExtraLength)
{
    ASSERT_STRINGNODE_INVARIANT;

    // if it won't fit, then make the buffer bigger
    size_t requiredLength = m_StringLimit - m_Buffer + ExtraLength + 1;
    if (m_BufferLength < requiredLength)
    {
        // Double the size of the buffer, instead of only requesting 
        // requiredLength bytes.  If we don't do this, then reading
        // long words takes a *very* long time because we repeatedly
        // reallocate the buffer to be one byte larger.
        size_t usedPortion = m_StringLimit - m_Buffer;
        size_t newsize = std::max(m_BufferLength * 2, requiredLength);

        m_Buffer       = (char *) realloc(m_Buffer, newsize);
        m_StringLimit  = m_Buffer + usedPortion;
        m_BufferLength = newsize;
    }
}

// Append a NUL-terminated string to the combo buffer
void CStringNodeBuffer::AppendString(const char * ToAppend)
{
    ASSERT_STRINGNODE_INVARIANT;

    // resize combo_buff to be large enough to hold ToAppend
    size_t toAppendLength = strlen(ToAppend);
    GrowBy(toAppendLength);

    // append ToAppend
    memcpy(m_StringLimit, ToAppend, toAppendLength);
    m_StringLimit += toAppendLength;
}

void CStringNodeBuffer::AppendChar(char ToAppend)
{
    ASSERT_STRINGNODE_INVARIANT;

    // resize combo_buff to be large enough to hold ToAppend
    GrowBy(1);

    // append ToAppend
    *m_StringLimit = ToAppend;
    m_StringLimit++;
}



// This is a hack to purge the "INPUTMODE_TO" buffer when
// loading from the editor.  If this is not done, any unused
// portion will hang around and be silently used the next time
// TO is run.
void rd_clearbuffer(FILE *strm)
{
    if (input_mode == INPUTMODE_To && strm == stdin)
    {
        g_ReadBuffer.Empty();
    }
}

int rd_getc(FILE *strm)
{
    int c;

    if (strm != stdin)
    {
        c = getc(strm);
    }
    else
    {
        if (g_ReadBuffer.IsEmpty())
        {
            // the buffer is empty, so we should read more
            switch (input_mode)
            {
                char tmpbuffer[MAX_BUFFER_SIZE];

            case INPUTMODE_To:
                {
                    char toline[MAX_BUFFER_SIZE];
                    cnv_strnode_string(toline, g_ToLine);

                    TMiniEditor editor(MainWindowx, toline);

                    if (IDOK != editor.Execute())
                    {
                        // the user cancelled the definition
                        err_logo(STOP_ERROR, NIL);
                    }
                    else
                    {
                        const char * definition = editor.GetText();

                        // copy the new definition into the read buffer.
                        const char * src = definition;
                        while (*src != '\0')
                        {
                            if (src[0] == '\r' && src[1] == '\n')
                            {
                                // Skip past the CR in a CRLF sequence because 
                                // the caller expects a UNIX EOL sequence.
                                src++;
                            }

                            g_ReadBuffer.AppendChar(*src);
                            *src++;
                        }

                        g_ReadBuffer.AppendChar('\n');
                        g_ReadBuffer.AppendString(End.GetName());
                    }
                }
                if (MainWindowx != NULL)
                {
                    // HACK: Reset the window title because the mini-editor's
                    // edit box appends a "-" (it thinks it's tied to a file 
                    // and I can't figure out how to tell it that it's not.
                    MainWindowx->FixWindowTitle();
                }
                break;

            case INPUTMODE_List:
                if (!promptuser(tmpbuffer, LOCALIZED_PROMPT_LIST))
                {
                    // Halt when done
                    err_logo(STOP_ERROR, NIL);
                }
                g_ReadBuffer.AppendString(tmpbuffer);
                break;

            case INPUTMODE_Pause:
                if (!promptuser(tmpbuffer, LOCALIZED_PROMPT_PAUSE))
                {
                    // continue when done
                    g_ReadBuffer.AppendString(tmpbuffer);
                    g_ReadBuffer.AppendString("continue");
                }
                else
                {
                    g_ReadBuffer.AppendString(tmpbuffer);
                }
                break;

            case INPUTMODE_None:
                if (!promptuser(tmpbuffer, LOCALIZED_PROMPT_INPUT))
                {
                    // Halt when done
                    err_logo(STOP_ERROR, NIL);
                }
                g_ReadBuffer.AppendString(tmpbuffer);
                break;
            }

            check_stop(true);
            g_ReadBuffer.AppendChar('\n');
        }

        c = g_ReadBuffer.PopChar();
    }

    return c;
}

static
inline
void rd_print_prompt(const char * /*str*/)
{
    //ndprintf(stdout,"%t",str);
}

NODE *reader(FILE *FileStream, const char * Prompt)
{
    int paren   = 0;
    int bracket = 0;
    int brace   = 0;

    bool vbar      = false;
    bool contin    = true;
    bool incomment = false;

    static const char ender[] = "\nEND\n";
    const char *enderProgress = ender;

    static const char localizedEnder[] = "\n" LOCALIZED_ALTERNATE_END "\n";
    const char *localizedEnderProgress = localizedEnder;

    NODETYPES this_type = STRING;

    if (!strcmp(Prompt, "RW"))
    {
        /* called by readword */
        Prompt = "";
        contin = false;
    }

    bool dribbling = (dribblestream != NULL && FileStream == stdin);

    if (FileStream == stdin)
    {
        if (*Prompt != '\0')
        {
            rd_print_prompt(Prompt);

            if (dribbling)
            {
                fprintf(dribblestream, "%s", Prompt);
            }
        }

        input_blocking = true;
        clear_is_running_erract_flag();
    }

    CStringNodeBuffer lineBuffer;

    // this setjmp matches with the longjmp in unblock_input(), which 
    // is called when a PAUSE continues
    if (!setjmp(iblk_buf))
    {
        int c = rd_getc(FileStream);
        while (c != EOF && (c != '\n' || vbar || paren || bracket || brace))
        {
            if (dribbling) 
            {
                putc(c, dribblestream);
            }

            // if c is a backslash, then read the next character and escape it
            if (c == '\\')
            {
                c = rd_getc(FileStream);
                if (c == EOF)
                {
                    break;
                }

                if (dribbling) 
                {
                    putc(c, dribblestream);
                }
                if (c == 'n') 
                {
                    c = '\n'; //ggm
                }

                // mark this character as being backslashed
                c = setparity(c);

                // the resulting string will be backslashed
                this_type = BACKSLASH_STRING;

                if (c == setparity('\n') && FileStream == stdin)
                {
                    rd_print_prompt("\\ ");

                    if (dribbling)
                    {
                        fprintf(dribblestream, "\\ ");
                    }
                }
            }

            lineBuffer.AppendChar(c);

            if (input_mode == INPUTMODE_To)
            {
                // We are parsing a TO.  Check if we hit the TO ender.

                // Is this the English ender?
                if (uncapital(c) == uncapital(*enderProgress))
                {
                    enderProgress++;
                    if (*enderProgress == '\0')
                    {
                        // We found the ender while still 
                        // inside a [, |, (, or {.
                        err_logo(DEEPEND, deepend_proc_name);
                        break;
                    }
                }
                else
                {
                    // start over on the ender
                    enderProgress = ender;
                }

                // Is this the localized (non-English) ender?
                if (uncapital(c) == uncapital(*localizedEnderProgress))
                {
                    localizedEnderProgress++;
                    if (*localizedEnderProgress == '\0')
                    {
                        // We found the ender while still 
                        // inside a [, |, (, or {.
                        err_logo(DEEPEND, deepend_proc_name);
                        break;
                    }
                }
                else
                {
                    // start over on the localized ender
                    localizedEnderProgress = localizedEnder;
                }
            }

            if (!incomment)
            {
                if (c == '|')
                {
                    vbar = !vbar;
                }
                else if (contin && !vbar)
                {
                    switch (c)
                    {
                    case '(': 
                        paren++;
                        break;
              
                    case ')':
                        if (paren)
                        {
                            paren--;
                        }
                        break;

                    case '[':
                        bracket++;
                        break;

                    case ']':
                        if (bracket)
                        {
                            bracket--;
                        }
                        break;

                    case '{':
                        brace++;
                        break;

                    case '}':
                        if (brace)
                        {
                            brace--;
                        }
                        break;

                    case ';':
                        incomment = true;
                        break;
                    }
                }
            }

            // any string that contains special characters needs to be
            // converted to a VBAR string so that it can be printed
            // out and re-read without a loss of data.  See bug #2516248.
            if (this_type == STRING && is_special_character(c))
            {
                this_type = VBAR_STRING;
            }

            if (c == '\n')
            {
                // newlines end comment
                incomment = false;
                if (FileStream == stdin)
                {
                    rd_print_prompt(vbar ? "| " : "~ ");

                    if (dribbling)
                    {
                        fprintf(dribblestream, vbar ? "| " : "~ ");
                    }
                }
            }

            while (!vbar && c == '~' && (c = rd_getc(FileStream)) != EOF)
            {
                CDynamicBuffer whitespace;

                // Copy linear whitespace to the "whitespace" buffer.
                // We want to ignore if it the goes to the end of the
                // line, but we want to keep it if it does not.
                while (c == ' ' || c == '\t')
                {
                    whitespace.AppendChar(c);
                    c = rd_getc(FileStream);
                }

                if (c != '\n')
                {
                    // append the linear whitespace that we skipped (if any)
                    const char * whitespaceString = whitespace.GetBuffer();
                    if (whitespaceString != NULL)
                    {
                        lineBuffer.AppendString(whitespaceString);
                        if (dribbling)
                        {
                            fprintf(dribblestream, "%s", whitespaceString);
                        }
                    }
                }

                if (dribbling)
                {
                    putc(c, dribblestream);
                }

                lineBuffer.AppendChar(c);

                if (c == '\n' && FileStream == stdin)
                {
                    incomment = false;

                    rd_print_prompt("~ ");

                    if (dribbling)
                    {
                        fprintf(dribblestream, "~ ");
                    }
                }
            }

            c = rd_getc(FileStream);
        }
    }

    input_blocking = false;

    if (dribbling)
    {
        putc('\n', dribblestream);
    }

    lineBuffer.TakeOwnershipOfBuffer();

    NODE * line = make_strnode_no_copy(
        lineBuffer.GetString() + sizeof(unsigned short),
        lineBuffer.GetString(),
        lineBuffer.GetStringLength(),
        this_type);

    if (line == Null_Word)
    {
        // make_strnode_no_copy did not reference the
        // string buffer so we must free it.
        free(lineBuffer.GetString());
    }

    return line;
}

static
NODE *list_to_array(NODE *list)
{
    int len = list_length(list);

    NODE * result = make_array(len);
    setarrorg(result, 1);

    int i = 0;
    for (NODE * np = list; np; np = cdr(np))
    {
        (getarrptr(result))[i++] = vref(car(np));
    }

    return result;
}

#define parens(ch)      (ch == '(' || ch == ')' || ch == ';')
#define infixs(ch)      (ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == '=' || ch == '<' || ch == '>')
#define white_space(ch) (ch == ' ' || ch == '\t' || ch == '\n')

// Parses the text from "*inln" to "inlimit", or until the first "endchar" is found.
// If endchar==-1, then the only limit is inlimit.
// The parsed text is returned as a NODE* list.
// Nested arrays and lists are parsed into their structured form.
// parser_iterate() sets stopping_flag to THROWING if it encounters a syntax error.
//
// if "ignore_comments" is true then comments should be ignored
//
static
NODE *
parser_iterate(
    const char **inln,
    const char *inlimit,
    bool        ignore_comments, 
    int         endchar
    )
{
    const char *word_start = NULL;
    static char terminate = '\0'; // KLUDGE

    int word_length = 0;

    NODETYPES this_type = STRING;

    bool broken = false;
    bool vbar   = false;

    CAppendableList return_list;

    char ch;
    do
    {
        /* get the current character and increase pointer */
        ch = **inln;
        if (!vbar && word_length == 0) 
        {
            word_start = *inln;
        }
        if (++ (*inln) >= inlimit) 
        {
            *inln = &terminate;
        }

        /* skip through comments and line continuations */
        while (!vbar && 
               ((ignore_comments && ch == ';') || (ch == '~' && **inln == '\n')))
        {

            // If this is a line continuation, keep going 
            // until we reach the end of the next line
            while (ch == '~' && **inln == '\n')
            {
                if (++ (*inln) >= inlimit) 
                {
                    *inln = &terminate;
                }
                ch = **inln;
                if (word_length == 0)
                {
                    word_start = *inln;
                }
                else
                {
                    if (**inln == ']' || **inln == '[' ||
                        **inln == '{' || **inln == '}')
                    {
                        ch = ' ';
                        break;
                    }
                    else
                    {
                        broken = true;
                    }
                }
                if (++ (*inln) >= inlimit) 
                {
                    *inln = &terminate;
                }
            }

            // If this is a comment and we're supposed to ignore comments, 
            // keep going until the end of the line.
            if (ignore_comments && ch == ';')
            {
                // While ch is not the end of the string and
                // the next char is not the end of the line
                while (ch != '\0' && **inln != '\n')
                {
                    // advance to the next character
                    ch = **inln;
                    if (word_length == 0) 
                    {
                        word_start = *inln;
                    }
                    else 
                    {
                        broken = true;
                    }

                    if (++ (*inln) >= inlimit) 
                    {
                        *inln = &terminate;
                    }
                }

                // mark this as the end of a line
                if (ch != '\0' && ch != '~') 
                {
                    ch = '\n';
                }
            }
        }

        // flag that this word will be of BACKSLASH_STRING type
        if (getparity(ch)) 
        {
            this_type = BACKSLASH_STRING;
        }

        if (ch == '|')
        {
            vbar = !vbar;
            this_type = VBAR_STRING;
            broken = true;   // so we'll copy the chars
        }

        else if (vbar || (!white_space(ch) && ch != ']' &&
                          ch != '{' && ch != '}' &&
                          ch != '[' && ch != '\0'))
        {
            word_length++;
        }

        NODE *tnode = NIL;

        if (vbar) 
        {
            continue;
        }
        else if (ch == endchar && endchar != -1) 
        {
            break;
        }
        else if (ch == ']') 
        {
            err_logo(UNEXPECTED_BRACKET, NIL);
        }
        else if (ch == '}') 
        {
            err_logo(UNEXPECTED_BRACE, NIL);
        }
        else if (ch == '[')
        {
            // this is a '[', parse a new list 
            tnode = cons_list(parser_iterate(inln, inlimit, ignore_comments, ']'));
            if (**inln == '\0') 
            {
                ch = '\0';
            }
        }
        else if (ch == '{')
        {
            NODE * array_as_list = parser_iterate(inln, inlimit, ignore_comments, '}');
            tnode = cons_list(list_to_array(array_as_list));
            gcref(array_as_list);
            if (**inln == '@')
            {
                // parse the origin as a decimal number
                char * unparsedPortion;
                long origin = strtol((*inln) + 1, &unparsedPortion, 10);
                *inln = unparsedPortion;

                setarrorg(car(tnode), origin);
            }
            if (**inln == '\0') 
            {
                ch = '\0';
            }
        }
        else if (white_space(ch) || ch == '\0' ||
                 **inln == ']' || **inln == '[' ||
                 **inln == '{' || **inln == '}')
        {
            // this character or the next one will terminate string, make the word 
            if (word_length > 0)
            {

                char * (*copyRoutine) (char *, const char *, int);

                if (broken)
                {
                    // The logical line is broken across several lines,
                    // so it must be mended.
                    copyRoutine = ignore_comments ? mend_strnzcpy : mend_nosemi;
                }
                else
                {
                    // The logical line is entirely on a single line,
                    // so a normal string copy will suffice.
                    copyRoutine = strnzcpy;
                }

                NODE * string_node = make_strnode(
                    word_start, 
                    word_length, 
                    this_type, 
                    copyRoutine);

                tnode = cons_list(string_node);
                this_type = STRING;
                word_length = 0;
                broken = false;
            }
        }

        // put the word onto the end of the return list
        return_list.AppendList(tnode);
    } while (ch);


    return return_list.GetList();
}

NODE *parser(NODE *nd, bool semi)
{
    NODE * string_node = cnv_node_to_strnode(nd);
    ref(string_node);

    int          slen  = getstrlen(string_node);
    const char * lnsav = getstrptr(string_node);
    NODE * rtn = parser_iterate(&lnsav, lnsav + slen, semi, -1);

    gcref(nd);
    deref(string_node);
    return rtn;
}

NODE *lparse(NODE *args)
{
    NODE *val = Unbound;

    NODE * arg = string_arg(args);
    if (NOT_THROWING)
    {
        val = parser(arg, false);
    }
    return val;
}

static
NODE *runparse_node(NODE *nd, NODE **ndsptr)
{
    if (nd == Minus_Tight)
    {
        return cons_list(nd);
    }

    NODE * snd = cnv_node_to_strnode(nd);
    ref(snd);
    const char *wptr  = getstrptr(snd);
    const int   wlen  = getstrlen(snd);
    NODETYPES   wtyp  = nodetype(snd);
    int         wcnt  = 0;

    CAppendableList return_list;

    bool monadic_minus = false;

    while (wcnt < wlen)
    {
        if (*wptr == ';')
        {
            *ndsptr = NIL;
            break;
        }

        NODE *tnode;

        if (*wptr == '"')
        {
            int tcnt = 0;
            const char * tptr = ++wptr;
            wcnt++;
            while (wcnt < wlen && !parens(*wptr))
            {
                if (wtyp == BACKSLASH_STRING && getparity(*wptr))
                {
                    wtyp = PUNBOUND; // flag for "\( case
                }
                wptr++, wcnt++, tcnt++;
            }

            NODE * strnode;
            if (wtyp == PUNBOUND)
            {
                wtyp = BACKSLASH_STRING;
                strnode = make_strnode(tptr, tcnt, wtyp, noparity_strnzcpy);
            }
            else
            {
                strnode = make_strnode(tptr, tcnt, wtyp, strnzcpy);
            }
            tnode = make_quote(intern(strnode));
        }
        else if (*wptr == ':')
        {
            int tcnt = 0;
            const char * tptr = ++wptr;
            wcnt++;
            while (wcnt < wlen && !parens(*wptr) && !infixs(*wptr))
            {
                wptr++, wcnt++, tcnt++;
            }
            tnode = make_colon(intern(make_strnode(tptr, tcnt, wtyp, strnzcpy)));
        }
        else if (wcnt == 0 && *wptr == '-' && !monadic_minus &&
                 wcnt+1 < wlen && !white_space(*(wptr + 1)))
        {
            /* minus sign with space before and no space after is unary */
            tnode = make_intnode(0);
            monadic_minus = true;
        }
        else if (parens(*wptr) || infixs(*wptr))
        {
            if (monadic_minus)
            {
                tnode         = Minus_Tight;
                monadic_minus = false;
            }
            else if (wcnt+1 < wlen && 
                     ((wptr[0] == '<' && (wptr[1] == '=' || wptr[1] == '>')) || 
                      (wptr[0] == '>' && wptr[1] == '=')))
            {
                // This is a two character infix operator: "<=" or ">=" or "<>"
                tnode = intern(make_strnode(wptr, 2, STRING, strnzcpy));
                wptr++, wcnt++;
            }
            else
            {
                tnode = intern(make_strnode(wptr, 1, STRING, strnzcpy));
            }
            wptr++, wcnt++;
        }
        else
        {
            int tcnt = 0;
            const char * tptr = wptr;
            // isnumb
            // 0 means digits so far, 
            // 1 means just saw 'e' so minus can be next
            // 2 means no longer eligible even if an 'e' comes along 
            // 3 means we saw a '?'
            // 4 means nothing yet;
            int isnumb = 4;
            if (*wptr == '?')
            {
                // turn ?5 to (? 5)
                isnumb = 3; 
                wptr++, wcnt++, tcnt++;
            }

            bool gotdot = false;
            while (wcnt < wlen    && 
                   !parens(*wptr) &&
                   (!infixs(*wptr) || (isnumb == 1 && (*wptr == '-' || *wptr == '+'))))
            {
                if (isnumb == 4 && isdigit(*wptr)) 
                {
                    // could be a number
                    isnumb = 0;
                }

                if (isnumb == 0 && (*wptr == 'e' || *wptr == 'E'))
                {
                    // just saw an 'e', so a '-' or '+' could be next
                    isnumb = 1;
                }
                else if ((!isdigit(*wptr) && (*wptr != '.' || gotdot)) || isnumb == 1)
                {
                    // can't be a number
                    // REVISIT: can we break out of the loop here?
                    isnumb = 2;
                }

                if (*wptr == '.') 
                {
                    gotdot = true;
                }
                wptr++, wcnt++, tcnt++;
            }

            if (MAX_NUMBER <= tcnt)
            {
                // too many characters to be a valid number
                isnumb = 2;
            }

            if (isnumb == 3 && tcnt > 1)
            {
                // turn ?5 into (? 5)

                // append "( ? 5" now
                NODE * qmtnode = cons_list(
                    Left_Paren,
                    Query,
                    cnv_node_to_numnode(make_strnode(tptr + 1, tcnt - 1, wtyp, strnzcpy)));

                return_list.AppendList(qmtnode);

                // append ")" later
                tnode = Right_Paren;
            }
            else if (isnumb < 2)
            {
                tnode = cnv_node_to_numnode(make_strnode(tptr, tcnt, wtyp, strnzcpy));
            }
            else
            {
                tnode = intern(make_strnode(tptr, tcnt, wtyp, strnzcpy));
            }
        }

        // append tnode to the end of return_list
        return_list.AppendElement(tnode);
    }
    deref(snd);
    return return_list.GetList();
}

NODE *runparse(NODE *ndlist)
{
    if (nodetype(ndlist) == RUN_PARSE)
    {
        // already run-parsed
        return parsed__runparse(ndlist);
    }

    if (!is_list(ndlist))
    {
        err_logo(BAD_DATA_UNREC, ndlist);
        return NIL;
    }

    if (ndlist != NIL)
    {
        NODE * curnd = car(ndlist);
        if (is_word(curnd)             && 
            getstrlen(curnd) >= 2      &&
            getstrptr(curnd) != NULL   && 
            getstrptr(curnd)[0] == '#' && 
            getstrptr(curnd)[1] == '!')
        {
            // shell-script #! treated as comment line
            return NIL;
        }
    }

    CAppendableList return_list;

    while (ndlist != NIL)
    {
        NODE *tnode;

        NODE * curnd = car(ndlist);
        ndlist = cdr(ndlist);
        if (!is_word(curnd))
        {
            tnode = cons_list(curnd);
        }
        else
        {
            if (!numberp(curnd))
            {
                tnode = runparse_node(curnd, &ndlist);
            }
            else
            {
                tnode = cons_list(cnv_node_to_numnode(curnd));
            }
        }

        // append tnode to the end of return_list
        return_list.AppendList(tnode);

        if (check_throwing) 
        {
            break;
        }
    }

    return return_list.GetList();
}

NODE *lrunparse(NODE *args)
{
    NODE * arg = car(args);
    while (nodetype(arg) == ARRAY && NOT_THROWING)
    {
        setcar(args, err_logo(BAD_DATA, arg));
        arg = car(args);
    }

    if (NOT_THROWING && !is_aggregate(arg))
    {
        arg = parser(arg, TRUE);
    }

    if (NOT_THROWING)
    {
        return runparse(arg);
    }

    return Unbound;
}


void uninitialize_parser()
{
    deref(deepend_proc_name);
    deepend_proc_name = NIL;

    g_ReadBuffer.Dispose();
}
