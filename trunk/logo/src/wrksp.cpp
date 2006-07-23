/*
*      wrksp.cpp       logo workspace management module                dvb
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

bool to_pending = false;
fpos_t LinesLoadedOnEdit;

static
NODE *make_procnode(NODE *lst, NODE *wrds, short min, short df, short max)
   {
   return cons_list(
      lst, 
      wrds,
      make_intnode((FIXNUM) min),
      make_intnode((FIXNUM) df),
      make_intnode((FIXNUM) max));
   }

static
NODE *get_bodywords(NODE *proc, NODE *name)
   {
   NODE *bodywords = bodywords__procnode(proc);

   if (bodywords != NIL) 
      {
      // bodywords__procnode(proc) was already created.
      // Just return it.
      return bodywords;
      }

   // bodywords__procnode(proc) isn't set yet.  Set it.

   // Create the "TO" line, which also contains the inputs
   CAppendableList toline;
   name = intern(name);
   toline.AppendElement(is_macro(name) ? Macro : To);
   toline.AppendElement(name);
   for (NODE * formals = formals__procnode(proc);
        formals != NIL;
        formals = cdr(formals))
      {
      NODE * formal = car(formals);

      NODE * tnode;
      if (is_list(formal))
         {
         // an input with a default value or a "rest" input
         tnode = cons(make_colon(car(formal)), cdr(formal));
         }
      else if (nodetype(formal) == INTEGER)
         {
         // a number, which indicates the default number of inputs
         tnode = formal;
         }
      else
         {
         // the name of a formal parameter (add a colon in front of it).
         tnode = make_colon(formal);
         }

      // append tnode to the "TO" line
      toline.AppendElement(tnode);
      }


   // Add the body of the procedure
   CAppendableList bodywordslist;
   bodywordslist.AppendElement(toline.GetList());
   for (NODE * line = bodylist__procnode(proc);
        line != NIL;
        line = cdr(line))
      {
      NODE * bodywords = runparse(car(line));

      bodywordslist.AppendElement(bodywords);
      }

   // add the END line
   bodywordslist.AppendElement(cons_list(End));

   // we're done making the bodywords list
   bodywords = bodywordslist.GetList();

   // cache the value of the bodywords so we won't have to
   // create it the next time.
   setbodywords__procnode(proc, bodywords);

   // return the bodywords
   return bodywords;
   }

static
NODE *name_arg(NODE *args)
   {
   while (is_aggregate(car(args)) && NOT_THROWING)
      {
      setcar(args, err_logo(BAD_DATA, car(args)));
      }
   return car(args);
   }

NODE *ltext(NODE *args)
   {
   NODE* name = name_arg(args);
   if (NOT_THROWING)
      {
      NODE* val = procnode__caseobj(intern(name));
      if (val == UNDEFINED)
         {
         err_logo(DK_HOW_UNREC, name);
         return Unbound;
         }
      else if (is_prim(val))
         {
         err_logo(IS_PRIM, name);
         return Unbound;
         }
      else
         {
         return text__procnode(val);
         }
      }
   return Unbound;
   }

NODE *lfulltext(NODE *args)
   {
   NODE* name = name_arg(args);
   if (NOT_THROWING)
      {
      NODE* val = procnode__caseobj(intern(name));
      if (val == UNDEFINED)
         {
         err_logo(DK_HOW_UNREC, name);
         return Unbound;
         }
      else if (is_prim(val))
         {
         err_logo(IS_PRIM, name);
         return Unbound;
         }
      else
         {
         return get_bodywords(val, name);
         }
      }
   return Unbound;
   }

static
void set_new_generation()
   {
   the_generation = reref(the_generation, cons_list(NIL));
   }

static
bool is_list_of_lists(const NODE *val) 
   {
   if (val == NIL) 
      {
      // base case: empty list
      return true;
      }

   if (!is_list(val))
      {
      // not even a list
      return false;
      }

   if (!is_list(car(val))) 
      {
      // a list of something other than lists
      return false;
      }

   return is_list_of_lists(cdr(val));
   }


// returns the number of default arguments for a procedure node
static
int
get_default_args_for_procedure(const NODE * procedure)
   {
   return is_prim(procedure) ? 
      getprimdflt(procedure) :
      getint(dfltargs__procnode(procedure));
   }

static
NODE *define_helper(NODE *args, int macro_flag)
   {
   /* macro_flag is -1 for anonymous function */
   NODE *name;
   NODE *val;
   int minimum = 0;
   int deflt = 0;
   int maximum = 0;
   int old_default = -1;

   if (macro_flag >= 0)
      {
      // macro or procedure
      name = name_arg(args);
      if (NOT_THROWING)
         {
         name = intern(name);
         val = procnode__caseobj(name);
         bool redef = variableIsTrue(Redefp);
         if (!redef && is_prim(val))
            {
            err_logo(IS_PRIM, name);
            return Unbound;
            }
         else if (val != UNDEFINED)
            {
            old_default = get_default_args_for_procedure(val);
            }
         }
      if (NOT_THROWING)
         {
         // make sure the bodylist is valid input
         val = cadr(args);
         while ((val == NIL || !is_list_of_lists(val)) &&
               NOT_THROWING)
            {
            setcar(cdr(args), err_logo(BAD_DATA, val));
            val = cadr(args);
            }
         }
      }
   else
      {
      // lambda 
      val = args;
      }


   if (NOT_THROWING)
      {
      args = car(val);
      if (args != NIL)
         {
         make_runparse(args);
         args = parsed__runparse(args);
         }
      setcar(val, args);
      while (args != NIL)
         {
         NODE* arg = car(args);
         if (arg != NIL && is_list(arg) && maximum != -1)
            {
            make_runparse(arg);
            arg = parsed__runparse(arg);
            setcar(args, arg);
            maximum++;
            if (cdr(arg) == NIL)
               {
               maximum = -1;
               }
            }
         else if (nodetype(arg) == INTEGER &&
               getint(arg) <= (unsigned) maximum &&
               getint(arg) >= minimum)
            {
            deflt = getint(arg);
            }
         else if (maximum == minimum)
            {
            minimum++;
            maximum++;
            deflt++;
            }
         else
            {
            err_logo(BAD_DATA_UNREC, arg);
            break;
            }

         args = cdr(args);
         if (check_throwing) 
            {
            break;
            }
         }
      }

   if (macro_flag < 0)
      {
      // lambda
      return make_procnode(val, NIL, minimum, deflt, maximum);
      }
   else if (NOT_THROWING)
      {
      // macro or procedure
      setprocnode__caseobj(
         name,
         make_procnode(val, NIL, minimum, deflt, maximum));

      if (macro_flag)
         {
         setflag__caseobj(name, PROC_MACRO);
         }
      else
         {
         clearflag__caseobj(name, PROC_MACRO);
         }

      if (deflt != old_default && old_default >= 0)
         {
         set_new_generation();
         }
      }
   return Unbound;
   }

NODE *ldefine(NODE *args)
   {
   return define_helper(args, FALSE);
   }

NODE *ldefmacro(NODE *args)
   {
   return define_helper(args, TRUE);
   }

NODE *anonymous_function(NODE *text)
   {
   return define_helper(text, -1);
   }

static
NODE *to_helper(NODE *args, bool is_macro)
   {
   if (ufun != NIL && loadstream == stdin)
      {
      err_logo(NOT_INSIDE, NIL);
      return Unbound;
      }

   if (args == NIL)
      {
      err_logo(NOT_ENOUGH, NIL);
      return Unbound;
      }

   input_mode = INPUTMODE_To;

   NODE *formals = NIL;

   int minimum = 0;
   int deflt = 0;
   int maximum = 0;
   int old_default = -1;

   NODE * proc_name = car(args);

   if (nodetype(proc_name) != CASEOBJ)
      {
      err_logo(BAD_DATA_UNREC, proc_name);
      }
   else if ((procnode__caseobj(proc_name) != UNDEFINED && loadstream == stdin)
         || is_prim(procnode__caseobj(proc_name)))
      {
      err_logo(ALREADY_DEFINED, proc_name);
      }
   else
      {
      NODE *old_proc = procnode__caseobj(proc_name);
      if (old_proc != UNDEFINED)
         {
         old_default = getint(dfltargs__procnode(old_proc));
         }

      //
      // read the formal parameters
      //
      NODE *formals_lastnode = NIL;
      args = cdr(args);
      while (args != NIL)
         {
         NODE * arg = car(args);
         args = cdr(args);
         if (nodetype(arg) == CONS && maximum != -1)
            {
            // this is either an input with a default value or a "rest" input
            make_runparse(arg);
            arg = parsed__runparse(arg);
            maximum++;
            if (nodetype(car(arg)) != COLON)
               {
               // input names must begin with a colon
               err_logo(BAD_DATA_UNREC, arg);
               break;
               }
            else
               {
               // this is an input with a defaut value
               setcar(arg, node__colon(car(arg)));
               }
            if (cdr(arg) == NIL)
               {
               // this is a "rest" input
               maximum = -1;
               }
            }
         else if (nodetype(arg) == COLON && maximum == minimum)
            {
            // this is a regular input
            arg = node__colon(arg);
            minimum++;
            maximum++;
            deflt++;
            }
         else if (nodetype(arg) == INTEGER &&
               getint(arg) <= (unsigned) maximum &&
               getint(arg) >= minimum)
            {
            // this is a number that specifies the number of default inputs
            deflt = getint(arg);
            }
         else
            {
            // unknown input type
            err_logo(BAD_DATA_UNREC, arg);
            break;
            }

         // append arg to the end of the "formals" list
         NODE *tnode = cons_list(arg);
         if (formals == NIL) 
            {
            formals = tnode;
            }
         else
            { 
            setcdr(formals_lastnode, tnode);
            }
         formals_lastnode = tnode;
         }
      }

   //
   // read the procedure body
   //
   if (NOT_THROWING)
      {
      NODE * body_words          = cons_list(current_line);
      NODE * body_words_lastnode = body_words;

      NODE * body_list          = cons_list(formals);
      NODE * body_list_lastnode = body_list;

      to_pending = true;      // for int or quit signal
      while (NOT_THROWING && to_pending && !feof(loadstream))
         {
         NODE * ttnode = reader(loadstream, "> ");

         // append ttnode to body_words
         NODE * tnode = cons_list(ttnode);
         setcdr(body_words_lastnode, tnode);
         body_words_lastnode = tnode;

         NODE * next_line = parser(car(body_words_lastnode), true);
         if (next_line != NIL && 
             compare_node(car(next_line), End, true) == 0)
            {
            // This line only contains "End", which denotes 
            // the end of this procedure.
            // Stop reading lines.
            gcref(next_line);
            break;
            }
         else if (next_line != NIL)
            {
            // append next_line to body_list
            NODE * next_line_list = cons_list(next_line);
            setcdr(body_list_lastnode, next_line_list);
            body_list_lastnode = next_line_list;
            }
         else
            {
            // the line is empty--ignore it
            gcref(next_line);
            }
         }


      //
      // package the procedure definition into the case object
      //
      if (to_pending && NOT_THROWING)
         {
         setprocnode__caseobj(
            proc_name,
            make_procnode(body_list, body_words, minimum, deflt, maximum));
         if (is_macro)
            {
            setflag__caseobj(proc_name, PROC_MACRO);
            }
         else
            {
            clearflag__caseobj(proc_name, PROC_MACRO);
            }

         if (deflt != old_default && old_default >= 0)
            {
            set_new_generation();
            }
         if (loadstream == stdin)
            {
            ndprintf(stdout, "%s defined\n", proc_name);
            }

         // Set the "dirty" flag so that closing FMSLogo will
         // prompt the user that they have unsaved changes.
         IsDirty = true;
         }
      else
         {
         // cleanup on error
         gcref(body_words);
         gcref(body_list);
         }

      to_pending = false;
      }
   else
      {
      gcref(formals);
      }

   input_mode = INPUTMODE_None;
   return Unbound;
   }

NODE *lto(NODE *args)
   {
   to_helper(args, false);
   return Unbound;
   }

NODE *lmacro(NODE *args)
   {
   to_helper(args, true);
   return Unbound;
   }

NODE *lmake(NODE *args)
   {
   NODE * what = name_arg(args);
   if (NOT_THROWING)
      {
      what = intern(what);
      setvalnode__caseobj(what, cadr(args));
      if (flag__caseobj(what, VAL_TRACED))
         {
         // This variable is traced.
         // Trace the assignment to the write stream.
         NODE *new_value            = vref(maybe_quote(cadr(args)));
         NODE *quoted_variable_name = vref(make_quote(what));

         ndprintf(
            writestream, 
            "Make %s %s", 
            quoted_variable_name, 
            new_value);

         deref(quoted_variable_name);
         deref(new_value);

         // trace the name of the procedure where the assignment happened.
         if (ufun != NIL)
            {
            ndprintf(writestream, " in %s\n%s", ufun, this_line);
            }
         new_line(writestream);
         }
      }
   return Unbound;
   }

static NODE *cnt_list = NIL;
static NODE *cnt_last = NIL;
static int want_buried = 0;

enum CNTLSTTYP
   {
   c_PROCS, 
   c_VARS, 
   c_PLISTS,
   };


static
int bck(int flag)
   {
   return (want_buried ? !flag : flag);
   }

static
void 
contents_map(
   NODE *    sym,
   CNTLSTTYP contents_list_type
)
   {
   int flag_check = PROC_BURIED;
	
   if (want_buried) 
      {
      flag_check = want_buried;
      }
	
   switch (contents_list_type)
      {
      case c_PROCS:
         if (procnode__object(sym) == UNDEFINED ||
             is_prim(procnode__object(sym)))
           {
           return;
           }
         if (bck(flag__object(sym, flag_check)))
           {
           return;
           }
         break;

      case c_VARS:
         flag_check <<= 1;
         if (valnode__object(sym) == Unbound) 
            {
            return;
            }
         if (bck(flag__object(sym, flag_check))) 
            {
            return;
            }
         break;

      case c_PLISTS:
         flag_check <<= 2;
         if (plist__object(sym) == NIL) 
            {
            return;
            }
         if (bck(flag__object(sym, flag_check))) 
            {
            return;
            }
         break;
      }

   if (cnt_list == NIL)
      {
      cnt_list = cons_list(canonical__object(sym));
      cnt_last = vref(cnt_list);
      }
   else
      {
      setcdr(cnt_last, cons_list(canonical__object(sym)));
      cnt_last = cdr(cnt_last);
      }
   }

// Modify a list such that each element in the list
// is inserted into its own, one-element list.
static
void ms_listlist(NODE *nd)
   {
   while (nd != NIL)
      {
      NODE* temp = cons_list(car(nd));
      setcar(nd, temp);
      nd = cdr(nd);
      }
   }

static
NODE *merge(NODE *a, NODE *b)
   {
   if (a == NIL) 
      {
      return b;
      }

   if (b == NIL) 
      {
      return a;
      }

   NODE *ret;
   NODE *tail;
   if (compare_node(car(a), car(b), false) < 0)
      {
      ret = a;
      tail = a;
      a = cdr(a);
      }
   else
      {
      ret = b;
      tail = b;
      b = cdr(b);
      }

   while (a != NIL && b != NIL)
      {
      if (compare_node(car(a), car(b), false) < 0)
         {
         tail->nunion.ncons.ncdr = a;
         a = cdr(a);
         }
      else
         {
         tail->nunion.ncons.ncdr = b;
         b = cdr(b);
         }
      tail = cdr(tail);
      }

   if (b == NIL) 
      {
      tail->nunion.ncons.ncdr = a;
      }
   else
      {
      tail->nunion.ncons.ncdr = b;
      }

   return ret;
   }

static
void mergepairs(NODE *nd)
   {
   NODE *temp;

   while (nd != NIL && cdr(nd) != NIL)
      {
      nd->nunion.ncons.ncar = merge(car(nd), cadr(nd));
      temp = cdr(nd);
      nd->nunion.ncons.ncdr = cddr(nd);
      temp->nunion.ncons.ncar = temp->nunion.ncons.ncdr = NIL;
      gc(temp);
      nd = cdr(nd);
      }
   }

static
NODE *mergesort(NODE *nd)
   {
   if (nd == NIL)
      {
      return NIL;
      }

   if (cdr(nd) == NIL) 
      {
      return nd;
      }

   ms_listlist(nd);
   while (cdr(nd) != NIL)
      {
      mergepairs(nd);
      }
   NODE * ret = car(nd);
   nd->nunion.ncons.ncar = NIL;
   gc(nd);
   return ret;
   }

static
NODE *
get_contents(
   CNTLSTTYP contents_type
   )
   {
   deref(cnt_list);
   cnt_list = NIL;
   cnt_last = NIL;

   for (int i = 0; i < HASH_LEN; i++)
      {
      for (NODE * nd = hash_table[i]; nd != NIL; nd = cdr(nd))
         {
         contents_map(car(nd), contents_type);
         }
      }

   cnt_list = mergesort(cnt_list);
   return (cnt_list);
   }

static
NODE *get_contents_list(int filter)
   {
   want_buried = filter;

   NODE *ret = NIL;

   ret = cons(get_contents(c_PLISTS), ret);

   ret = cons(get_contents(c_VARS), ret);

   ret = cons(get_contents(c_PROCS), ret);
	
   deref(cnt_list);
   cnt_list = NIL;

   return ret;
   }

NODE *lcontents(NODE *)
   {
   return get_contents_list(0);
   }

NODE *ltraced(NODE *)
   {
   return get_contents_list(PROC_TRACED);
   }

NODE *lstepped(NODE *)
   {
   return get_contents_list(PROC_STEPPED);
   }

NODE *lburied(NODE *)
   {
   return get_contents_list(PROC_BURIED);
   }

NODE *lprocedures(NODE *)
   {
   want_buried = 0;

   NODE * ret = get_contents(c_PROCS);
   ref(ret);
   deref(cnt_list);
   cnt_list = NIL;
   return unref(ret);
   }

NODE *lnames(NODE *)
   {
   want_buried = 0;

   NODE * ret = cons_list(NIL, get_contents(c_VARS));
   ref(ret);
   deref(cnt_list);
   cnt_list = NIL;
   return unref(ret);
   }

NODE *lplists(NODE *)
   {
   want_buried = 0;

   NODE * ret = cons_list(NIL, NIL, get_contents(c_PLISTS));
   ref(ret);
   deref(cnt_list);
   cnt_list = NIL;
   return unref(ret);
   }

static
NODE *one_list(NODE *nd)
   {
   if (!is_list(nd))
      {
      return cons_list(nd);
      }
   return nd;
   }

// constructs three separate lists from a "contents list" arg.
static
void three_lists(NODE *arg, NODE **proclst, NODE **varlst, NODE **plistlst)
   {
   // initialize all lists to the empty list
   *plistlst = *varlst = *proclst = NIL;

   if (nodetype(car(arg)) == CONS)
      {
      // The input is a list of something.
      // Advance to the first item in the list.
      arg = car(arg);
      }

   if (!is_list(car(arg)))
      {
      // the contents list is a list of procedure names
      *proclst = arg;
      }
   else
      {
      // the contents list is a list of lists
      *proclst = car(arg);
      if (cdr(arg) != NIL)
         {
         *varlst = one_list(cadr(arg));
         if (cddr(arg) != NIL)
            {
            *plistlst = one_list(car(cddr(arg)));
            
            if (cdr(cddr(arg)) != NIL)
               {
               // this was a list of more than three lists
               err_logo(BAD_DATA_UNREC, arg);
               *plistlst = *varlst = *proclst = NIL;
               }
            }
         }
      }

   if (!is_list(*proclst) || !is_list(*varlst) || !is_list(*plistlst))
      {
      err_logo(BAD_DATA_UNREC, arg);
      *plistlst = *varlst = *proclst = NIL;
      }
   }

static
char *expand_slash(const NODE *wd)
   {
   // figure out how many characters we need to expand
   int len = getstrlen(wd);
   int i = 0;
   int j = len;
   for (const char * cp = getstrptr(wd); 
        --j >= 0;
        )
      {
      if (getparity(*cp++)) 
         {
         i++;
         }
      }

   // allocate space for the expanded string
   char * result = (char *) malloc(len + i + 1);
   if (result == NULL)
      {
      err_logo(OUT_OF_MEM, NIL);
      return NULL;
      }

   // copy the string to result and add backslashes as we go
   char *cp2 = result;
   j = len;
   for (const char * cp = getstrptr(wd); 
        --j >= 0;
        )
      {
      if (getparity(*cp))
         {
         // backslash this character
         *cp2++ = '\\';
         }
      *cp2++ = clearparity(*cp++);
      }
   *cp2 = '\0';

   return result;
   }

static
NODE *po_helper(NODE *arg, int just_titles)  /* >0 for POT, <0 for EDIT       */
   {
   print_backslashes = true;

   NODE *proclst;
   NODE *varlst;
   NODE *plistlst;
   three_lists(arg, &proclst, &varlst, &plistlst);

   while (proclst != NIL)
      {
      if (is_aggregate(car(proclst)))
         {
         err_logo(BAD_DATA_UNREC, car(proclst));
         break;
         }

      NODE * tvar = procnode__caseobj(intern(car(proclst)));

      if (tvar == UNDEFINED)
         {
         if (just_titles < 0)
            {
            ndprintf(writestream, "to %p\nend\n\n", car(proclst));
            }
         else
            {
            err_logo(DK_HOW_UNREC, car(proclst));
            break;
            }
         }
      else if (is_prim(tvar))
         {
         err_logo(IS_PRIM, car(proclst));
         break;
         }
      else
         {
         tvar = get_bodywords(tvar, car(proclst));
         if (just_titles > 0)
            {
            print_nobrak(writestream, car(tvar));
            }
         else 
            {
            while (tvar != NIL)
               {
               if (is_list(car(tvar)))
                  {
                  print_nobrak(writestream, car(tvar));
                  }
               else
                  {
                  char *str = expand_slash(car(tvar));
                  if (writestream == stdout)
                     {
                     printfx(str);
                     if (dribblestream != NULL)
                        {
                        fprintf(dribblestream, "%s\n", str);
                        }
                     }
                  else
                     {
                     fprintf(writestream, "%s", str);
                     }
                  free(str);
                  }
               if (writestream != stdout) 
                  {
                  new_line(writestream);
                  }
               tvar = cdr(tvar);
               }
            }
         new_line(writestream);
         }
      proclst = cdr(proclst);
      if (check_throwing) break;
      }

   for (NODE * current_varlist_node = varlst;
        current_varlist_node != NIL;
        current_varlist_node = cdr(current_varlist_node))
      {
      if (check_throwing) 
         {
         break;
         }

      NODE * current_variable = car(current_varlist_node);
      if (is_aggregate(current_variable))
         {
         err_logo(BAD_DATA_UNREC, current_variable);
         break;
         }

      NODE * quoted_value = maybe_quote(valnode__caseobj(intern(current_variable)));
      if (quoted_value == Unbound)
         {
         if (just_titles >= 0)
            {
            err_logo(NO_VALUE, current_variable);
            break;
            }
         }
      else
         {
         NODE * quoted_variable_name = make_quote(current_variable);

         ndprintf(
            writestream, 
            "Make %s %s\n",
            quoted_variable_name,
            quoted_value);

         gcref(quoted_variable_name);
         }
      gcref(quoted_value);
      }

   while (plistlst != NIL && NOT_THROWING)
      {
      if (is_aggregate(car(plistlst)))
         {
         err_logo(BAD_DATA_UNREC, car(plistlst));
         break;
         }

      NODE * plist_name        = car(plistlst);
      NODE * quoted_plist_name = maybe_quote(plist_name);

      NODE * plist = plist__caseobj(intern(plist_name));
      if (plist != NIL && just_titles > 0)
         {
         ndprintf(
            writestream, 
            "Plist %s = %s\n",
            quoted_plist_name, 
            plist);
         }
      else 
         {
         while (plist != NIL)
            {
            NODE * quoted_property_name  = maybe_quote(car(plist));
            NODE * quoted_property_value = maybe_quote(cadr(plist));

            ndprintf(
               writestream, 
               "Pprop %s %s %s\n",
               quoted_plist_name,
               quoted_property_name,
               quoted_property_value);

            gcref(quoted_property_name);
            gcref(quoted_property_value);
            plist = cddr(plist);
            }
         }
      gcref(quoted_plist_name);

      plistlst = cdr(plistlst);
      if (check_throwing) break;
      }

   print_backslashes = false;

   gcref(proclst);
   gcref(varlst);
   gcref(plistlst);
   return Unbound;
   }

NODE *lpo(NODE *arg)
   {
   lsetcursorwait(NIL);
   po_helper(arg, 0);
   lsetcursorarrow(NIL);

   return Unbound;
   }

NODE *lpot(NODE *arg)
   {
   po_helper(arg, 1);
   return Unbound;
   }

NODE *lerase(NODE *arg)
   {
   NODE *proclst;
   NODE *varlst;
   NODE *plistlst;
   three_lists(arg, &proclst, &varlst, &plistlst);

   if (proclst != NIL)
      {
      set_new_generation();
      }

   while (proclst != NIL)
      {
      if (is_aggregate(car(proclst)))
         {
         err_logo(BAD_DATA_UNREC, car(proclst));
         break;
         }
      NODE * nd = intern(car(proclst));
      bool redef = variableIsTrue(Redefp);
      if (!redef && is_prim(procnode__caseobj(nd)))
         {
         err_logo(IS_PRIM, nd);
         break;
         }
      setprocnode__caseobj(nd, UNDEFINED);
      proclst = cdr(proclst);
      }

   while (varlst != NIL && NOT_THROWING)
      {
      if (is_aggregate(car(varlst)))
         {
         err_logo(BAD_DATA_UNREC, car(varlst));
         break;
         }
      setvalnode__caseobj(intern(car(varlst)), Unbound);
      varlst = cdr(varlst);
      }

   while (plistlst != NIL && NOT_THROWING)
      {
      if (is_aggregate(car(plistlst)))
         {
         err_logo(BAD_DATA_UNREC, car(plistlst));
         break;
         }
      setplist__caseobj(intern(car(plistlst)), NIL);
      plistlst = cdr(plistlst);
      }

   gcref(proclst);
   gcref(varlst);
   gcref(plistlst);
   return Unbound;
   }

// Sets or clears a flag on each interned object in the list.
// The flag must be one of PROC_BURIED, PROC_STEPPED, or PROC_TRACED.
// If setflag is true, the flag is set.  Otherwise the flag is cleared.
static
void bury_or_unbury_list(NODE * list, int flag, bool setflag)
   {
   while (list != NIL && NOT_THROWING)
      {
      if (is_aggregate(car(list)))
         {
         err_logo(BAD_DATA_UNREC, car(list));
         break;
         }

      // set or clear the flag, depending on setflag
      NODE * caseobject = intern(car(list));
      if (setflag)
         {
         setflag__caseobj(caseobject, flag);
         }
      else
         {
         clearflag__caseobj(caseobject, flag);
         }

      list = cdr(list);
      if (check_throwing) break;
      }
   }

static
NODE *bury_helper(NODE *arg, int flag, bool setflag)
   {
   NODE *proclst;
   NODE *varlst;
   NODE *plistlst;
   three_lists(arg, &proclst, &varlst, &plistlst);

   if (NOT_THROWING)
      {
      bury_or_unbury_list(proclst, flag, setflag);

      flag <<= 1;
      bury_or_unbury_list(varlst, flag, setflag);

      flag <<= 1;
      bury_or_unbury_list(plistlst, flag, setflag);
      }

   gcref(proclst);
   gcref(varlst);
   gcref(plistlst);
   return Unbound;
   }

NODE *lbury(NODE *arg)
   {
   return bury_helper(arg, PROC_BURIED, true);
   }

NODE *ltrace(NODE *arg)
   {
   return bury_helper(arg, PROC_TRACED, true);
   }

NODE *lstep(NODE *arg)
   {
   return bury_helper(arg, PROC_STEPPED, true);
   }

NODE *lunbury(NODE *arg)
   {
   return bury_helper(arg, PROC_BURIED, false);
   }

NODE *luntrace(NODE *arg)
   {
   return bury_helper(arg, PROC_TRACED, false);
   }

NODE *lunstep(NODE *arg)
   {
   return bury_helper(arg, PROC_STEPPED, false);
   }

NODE *ledit(NODE *args)
   {
   
   if (!bExpert)
      {
      // if an editor is already open, just give it focus
      HWND editorWindow = ::FindWindow(NULL, "Editor");
      if (editorWindow)
         {
         ::ShowWindow(editorWindow, SW_SHOWNORMAL);
         ::SetWindowPos(editorWindow, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
         return Unbound;
         }
      }

   int save_yield_flag = yield_flag;
   yield_flag = 0;
   lsetcursorwait(NIL);

   if (args != NIL)
      {
      FILE * holdstrm = writestream;
      writestream = fopen(TempPathName, "w");
      if (writestream != NULL)
         {
         po_helper(args, -1);
         fclose(writestream);
         writestream = holdstrm;
         }
      else
         {
         err_logo(
            FILE_ERROR,
            make_static_strnode("Could not create editor file"));
         writestream = holdstrm;
         return Unbound;
         }
      }

   //if (in_graphics_mode)
   //   {
   //   text_screen;
   //   }

   NODE * args_list = reref(NIL, args);
   if (TMainFrame::PopupEditorForFile(TempPathName, args_list))
      {
      err_logo(FILE_ERROR, make_static_strnode("Could not launch the editor"));
      }
   else
      {
      unlink(TempPathName);
      IsDirty = true;
      }

   lsetcursorarrow(NIL);
   yield_flag = save_yield_flag;

   return Unbound;
   }

bool endedit(void)
   {
   bool realsave = false;

   FILE * holdstrm = loadstream;
   NODE * tmp_line = reref(NIL, current_line);
   int save_yield_flag = yield_flag;
   yield_flag = 0;
   lsetcursorwait(NIL);

   LinesLoadedOnEdit = 0;

   loadstream = fopen(TempPathName, "r");
   if (loadstream != NULL)
      {
      int sv_val_status = val_status;

      realsave = true;
      while (!feof(loadstream) && NOT_THROWING)
         {
         fgetpos(loadstream, &LinesLoadedOnEdit);
         current_line = reref(current_line, reader(loadstream, ""));
         
         val_status = 0;
         NODE * exec_list = parser(current_line, true);
         eval_driver(exec_list);
         }
      fclose(loadstream);
      val_status = sv_val_status;
      }
   else
      {
      // err_logo(
      //    FILE_ERROR,
      //    make_static_strnode("Could not read editor file"));
      }

   lsetcursorarrow(NIL);
   yield_flag = save_yield_flag;
   loadstream = holdstrm;
   current_line = reref(current_line, tmp_line);

   return realsave;
   }

NODE *lthing(NODE *args)
   {
   NODE *val = Unbound;

   NODE * arg = name_arg(args);
   if (NOT_THROWING)
      {
      val = valnode__caseobj(intern(arg));
      }

   while (val == Unbound && NOT_THROWING)
      {
      val = err_logo(NO_VALUE, car(args));
      }

   return val;
   }

NODE *lnamep(NODE *args)
   {
   NODE *arg = name_arg(args);
   if (NOT_THROWING)
      {
      return true_or_false(valnode__caseobj(intern(arg)) != Unbound);
      }
   return Unbound;
   }

NODE *lprocedurep(NODE *args)
   {
   NODE *arg = name_arg(args);
   if (NOT_THROWING)
      {
      return true_or_false(procnode__caseobj(intern(arg)) != UNDEFINED);
      }
   return Unbound;
   }

NODE *lproplistp(NODE *args)
   {
   NODE *arg = name_arg(args);
   if (NOT_THROWING)
      {
      return true_or_false(plist__caseobj(intern(arg)) != NIL);
      }
   return Unbound;
   }

// wanted:
//   0 = defined
//   1 = primative
//   2 = macro
static
NODE *check_proctype(NODE *args, int wanted)
   {
   NODE * arg = name_arg(args);

   NODE * cell;
   if (NOT_THROWING && (cell = procnode__caseobj(intern(arg))) == UNDEFINED)
      {
      return Falsex;
      }

   if (wanted == 2)
      {
      return true_or_false(is_macro(intern(arg)));
      }

   int isprim = is_prim(cell);
   if (NOT_THROWING)
      {
      return true_or_false((isprim != 0) == wanted);
      }

   return Unbound;
   }

NODE *lprimitivep(NODE *args)
   {
   return check_proctype(args, 1);
   }

NODE *ldefinedp(NODE *args)
   {
   return check_proctype(args, 0);
   }

NODE *lmacrop(NODE *args)
   {
   return check_proctype(args, 2);
   }

NODE *lcopydef(NODE *args)
   {
   NODE * arg1 = name_arg(args);
   NODE * arg2 = name_arg(cdr(args));
   if (numberp(arg2)) 
      {
      err_logo(BAD_DATA_UNREC, arg2);
      }
   if (numberp(arg1))
      {
      err_logo(BAD_DATA_UNREC, arg1);
      }

   if (NOT_THROWING)
      {
      arg1 = intern(arg1);
      arg2 = intern(arg2);
      }
   if (NOT_THROWING && procnode__caseobj(arg2) == UNDEFINED)
      {
      err_logo(DK_HOW, arg2);
      }

   bool redef = variableIsTrue(Redefp);
   if (NOT_THROWING && !redef && is_prim(procnode__caseobj(arg1)))
      {
      err_logo(IS_PRIM, arg1);
      }
   if (NOT_THROWING)
      {
      NODE *old_proc = procnode__caseobj(arg1);
      NODE *new_proc = procnode__caseobj(arg2);
      if (old_proc != UNDEFINED)
         {
         int old_default = get_default_args_for_procedure(old_proc);
         int new_default = get_default_args_for_procedure(new_proc);

         if (old_default != new_default)
            {
            set_new_generation();
            }
         }

      setprocnode__caseobj(arg1, new_proc);
      setflag__caseobj(arg1, PROC_BURIED);
      if (is_macro(arg2)) 
         {
         setflag__caseobj(arg1, PROC_MACRO);
         }
      else 
         {
         clearflag__caseobj(arg1, PROC_MACRO);
         }
      }
   return Unbound;
   }

