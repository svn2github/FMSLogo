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

FILE *loadstream = stdin;
FILE *dribblestream = NULL;
bool input_blocking = false;
NODE *deepend_proc_name = NIL;
NODE *g_ToLine          = NIL;

INPUTMODE input_mode = INPUTMODE_None;

static CDynamicBuffer g_ReadBuffer;

static char *p_line = 0;
static char *p_end;
static int   p_len = MAX_PHYS_LINE;

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

                  g_ReadBuffer.AppendString("\nEnd");
                  }
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
                  g_ReadBuffer.AppendString("Continue");
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

   return ecma_clear(c);
   }

static
void rd_print_prompt(const char * /*str*/)
   {
   //ndprintf(stdout,"%t",str);
   }

#define into_line(chr) \
   { \
   if (phys_line >= p_end) \
      { \
      p_len += MAX_PHYS_LINE; \
      p_pos = phys_line - p_line; \
      p_line = (char *)realloc(p_line, p_len); \
      p_end = &p_line[p_len-1]; \
      phys_line = &p_line[p_pos]; \
      } \
   *phys_line++ = (chr); \
   }

NODE *reader(FILE *strm, const char *prompt)
   {
   static const char ender[] = "\nEND\n";

   int p_pos;

   int paren   = 0;
   int bracket = 0;
   int brace   = 0;

   bool vbar      = false;
   bool contin    = true;
   bool incomment = false;

   char *phys_line;
   const char *lookfor = ender;
   NODETYPES this_type = STRING;

   if (!strcmp(prompt, "RW"))
      {
      /* called by readword */
      prompt = "";
      contin = false;
      }

   bool dribbling = (dribblestream != NULL && strm == stdin);

   // allocate p_line if it hasn't been allocated yet
   if (p_line == NULL)
      {
      p_line = (char *) malloc(MAX_PHYS_LINE);
      if (p_line == NULL)
         {
         err_logo(OUT_OF_MEM, NIL);
         return Unbound;
         }
      p_end = &p_line[MAX_PHYS_LINE - 1];
      }

   phys_line = p_line;
   if (strm == stdin)
      {
      if (*prompt)
         {
         rd_print_prompt(prompt);

         if (dribblestream != NULL)
            {
            fprintf(dribblestream, "%s", prompt);
            }
         }

      input_blocking = true;
      clear_is_running_erract_flag();
      }

   int c = 0;

   if (!setjmp(iblk_buf))
      {
      c = rd_getc(strm);
      while (c != EOF && (vbar || paren || bracket || brace || c != '\n'))
         {
         if (dribbling) 
            {
            putc(c, dribblestream);
            }
         if (c == '\\' && (c = rd_getc(strm)) != EOF)
            {
            if (dribbling) 
               {
               putc(c, dribblestream);
               }
            if (c == 'n') 
               {
               c = '\n'; //ggm
               }
            c = setparity(c);
            this_type = BACKSLASH_STRING;
            if (c == setparity('\n') && strm == stdin)
               {
               rd_print_prompt("\\ ");

               if (dribbling)
                  {
                  fprintf(dribblestream, "\\ ");
                  }
               }
            }

         if (c != EOF) 
            {
            into_line(c);
            }

         if (*prompt && (c & 0x5F) == *lookfor)
            {
            lookfor++;
            if (*lookfor == '\0')
               {
               // We found the ender while still 
               // inside a [, |, (, or {.
               err_logo(DEEPEND, deepend_proc_name);
               break;
               }
            }
         else 
            {
            lookfor = ender;
            }

         if (c == '|' && !incomment) 
            {
            vbar = !vbar;
            }
         else if (contin && !vbar && !incomment)
            {
            if (c == '(') 
               {
               paren++;
               }
            else if (paren && c == ')') 
               {
               paren--;
               }
            else if (c == '[')
               {
               bracket++;
               }
            else if (bracket && c == ']')
               {
               bracket--;
               }
            else if (c == '{')
               {
               brace++;
               }
            else if (brace && c == '}')
               {
               brace--;
               }
            else if (c == ';')
               { 
               incomment = true;
               }
            }
         if (/* (vbar || paren ...) && */ c == '\n')
            {
            incomment = false;
            if (strm == stdin)
               {
               rd_print_prompt(vbar ? "| " : "~ ");

               if (dribbling)
                  {
                  fprintf(dribblestream, vbar ? "| " : "~ ");
                  }
               }
            }
         while (!vbar && c == '~' && (c = rd_getc(strm)) != EOF)
            {
            while (c == ' ' || c == '\t')
               {
               c = rd_getc(strm);
               }
            if (dribbling) 
               {
               putc(c, dribblestream);
               }
            into_line(c);
            if (c == '\n' && strm == stdin)
               {
               incomment = false;

               rd_print_prompt("~ ");

               if (dribbling)
                  {
                  fprintf(dribblestream, "~ ");
                  }
               }
            }

         if (c != EOF)
            {
            c = rd_getc(strm);
            }
         }
      }

   *phys_line = '\0';
   input_blocking = false;

   if (dribbling)
      {
      putc('\n', dribblestream);
      }
   if (c == EOF && strm == stdin)
      {
      clearerr(stdin);

      rd_print_prompt("\n");
      }
   if (phys_line == p_line)
      {
      return Null_Word; // so emptyp works
      }

   NODE * ret = make_strnode(p_line, (int) strlen(p_line), this_type, strnzcpy);
   return ret;
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
// The parsed text is returned as a NODE* list.
// Nested arrays and lists are parsed into their structured form.
// parser_iterate() sets stopping_flag to THROWING if it encounters a syntax error.
//
// if "ignore_comments" is true then comments should be ignored
static
NODE *
parser_iterate(
   const char **inln,
   const char *inlimit,
   bool        ignore_comments, 
   int         endchar
   )
   {
   const char *wptr = NULL;
   static char terminate = '\0'; // KLUDGE
   int windex = 0;
   NODETYPES this_type = STRING;

   bool broken = false;
   bool vbar   = false;

   CAppendableList return_list;

   char ch;
   do
      {
      /* get the current character and increase pointer */
      ch = **inln;
      if (!vbar && windex == 0) 
         {
         wptr = *inln;
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
            if (windex == 0)
               {
               wptr = *inln;
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
               if (windex == 0) 
                  {
                  wptr = *inln;
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
         windex++;
         }

      NODE *tnode = NIL;

      if (vbar) 
         {
         continue;
         }
      else if (ch == endchar) 
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
         if (windex > 0)
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
               wptr, 
               windex, 
               this_type, 
               copyRoutine);

            tnode = cons_list(string_node);
            this_type = STRING;
            windex = 0;
            broken = false;
            }
         }

      // put the word onto the end of the return list
      return_list.AppendList(tnode);
      }
   while (ch);


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
            tnode = Minus_Tight;
            }
         else
            {
            tnode = intern(make_strnode(wptr, 1, STRING, strnzcpy));
            }
         monadic_minus = false;
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
               // REVISIT: can be break out of the loop here?
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

   free(p_line);
   p_line = NULL;
   p_end  = NULL;
   p_len  = 0;
   }
