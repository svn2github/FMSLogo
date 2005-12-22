/*
*      wrksp.c         logo workspace management module                dvb
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

int to_pending = 0;
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
   NODE *val = bodywords__procnode(proc);

   if (val != NIL) 
      {
      return val;
      }
   name = intern(name);
   NODE * head = cons_list((is_macro(name) ? Macro : To), name);
   NODE * tail = cdr(head);
   val = formals__procnode(proc);
   while (val != NIL)
      {
      if (is_list(car(val)))
         {
         setcdr(tail, cons_list(cons(make_colon(caar(val)), cdar(val))));
         }
      else if (nodetype(car(val)) == INT)
         {
         setcdr(tail, cons_list(car(val)));
         }
      else
         {
         setcdr(tail, cons_list(make_colon(car(val))));
         }
      tail = cdr(tail);
      val = cdr(val);
      }
   head = cons_list(head);
   tail = head;
   val = bodylist__procnode(proc);
   while (val != NIL)
      {
      setcdr(tail, cons_list(runparse(car(val))));
      tail = cdr(tail);
      val = cdr(val);
      }
   setcdr(tail, cons_list(cons_list(End)));
   setbodywords__procnode(proc, head);
   return head;
   }

static
NODE *name_arg(NODE *args)
   {
   while (aggregate(car(args)) && NOT_THROWING)
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
         return text__procnode(val);
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
         return get_bodywords(val, name);
      }
   return Unbound;
   }

static
NODE *define_helper(NODE *args, int macro_flag)
   {
   NODE *name, *val;
   int minimum = 0, deflt = 0, maximum = 0, old_default = -1;
   int redef = (compare_node(valnode__caseobj(Redefp), Truex, TRUE) == 0);

   if (macro_flag >= 0)
      {
      name = name_arg(args);
      if (NOT_THROWING)
         {
         name = intern(name);
         val = procnode__caseobj(name);
         if (!redef && is_prim(val))
            {
            err_logo(IS_PRIM, name);
            return Unbound;
            }
         else if (val != UNDEFINED)
            {
            old_default = (is_prim(val) ? getprimdflt(val) :
                  getint(dfltargs__procnode(val)));
            }
         }
      if (NOT_THROWING)
         {
         val = cadr(args);
         while ((val == NIL || !is_list(val) || !is_list(car(val))) &&
               NOT_THROWING)
            {
            setcar(cdr(args), err_logo(BAD_DATA, val));
            val = cadr(args);
            }
         }
      }
   else
      {
      /* lambda */
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
               maximum = -1;
            }
         else if (nodetype(arg) == INT &&
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
         if (check_throwing) break;
         }
      }
   if (macro_flag < 0)
      {
      return make_procnode(val, NIL, minimum, deflt, maximum);
      }
   else if (NOT_THROWING)
      {
      setprocnode__caseobj(name,
         make_procnode(val, NIL, minimum, deflt, maximum));
      if (macro_flag)
         setflag__caseobj(name, PROC_MACRO);
      else
         clearflag__caseobj(name, PROC_MACRO);
      if (deflt != old_default && old_default >= 0)
         {
         the_generation = reref(the_generation, cons_list(NIL));
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
NODE *to_helper(NODE *args, bool macro_flag)
   {
   NODE *proc_name;
   NODE *formals = NIL;
   NODE *lastnode = NIL;
   NODE *body_words;
   NODE *lastnode2;
   NODE *body_list;

   int minimum = 0;
   int deflt = 0;
   int maximum = 0;
   int old_default = -1;
   char ttemp[16];

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

   proc_name = car(args);
   args = cdr(args);

   if (nodetype(proc_name) != CASEOBJ)
      err_logo(BAD_DATA_UNREC, proc_name);
   else if ((procnode__caseobj(proc_name) != UNDEFINED && loadstream == stdin)
         || is_prim(procnode__caseobj(proc_name)))
      err_logo(ALREADY_DEFINED, proc_name);
   else
      {
      NODE *old_proc = procnode__caseobj(proc_name);
      if (old_proc != UNDEFINED)
         {
         old_default = getint(dfltargs__procnode(old_proc));
         }
      while (args != NIL)
         {
         NODE * arg = car(args);
         args = cdr(args);
         if (nodetype(arg) == CONS && maximum != -1)
            {
            make_runparse(arg);
            arg = parsed__runparse(arg);
            maximum++;
            if (nodetype(car(arg)) != COLON)
               {
               err_logo(BAD_DATA_UNREC, arg);
               break;
               }
            else
               setcar(arg, node__colon(car(arg)));
            if (cdr(arg) == NIL)
               maximum = -1;
            }
         else if (nodetype(arg) == COLON && maximum == minimum)
            {
            arg = node__colon(arg);
            minimum++;
            maximum++;
            deflt++;
            }
         else if (nodetype(arg) == INT &&
               getint(arg) <= (unsigned) maximum &&
               getint(arg) >= minimum)
            {
            deflt = getint(arg);
            }
         else
            {
            err_logo(BAD_DATA_UNREC, arg);
            break;
            }

         NODE *tnode = cons_list(arg);
         if (formals == NIL) formals = tnode;
         else setcdr(lastnode, tnode);
         lastnode = tnode;
         }
      }

   if (NOT_THROWING)
      {
      body_words = cons_list(current_line);
      lastnode2 = body_words;
      body_list = cons_list(formals);
      lastnode = body_list;
      to_pending++;                    /* for int or quit signal              */
      while (NOT_THROWING && to_pending && (!feof(loadstream)))
         {
         strcpy(ttemp, "> ");
         NODE * ttnode = reader(loadstream, ttemp);
         NODE * tnode = cons_list(ttnode);
         setcdr(lastnode2, tnode);
         lastnode2 = tnode;
         tnode = cons_list(parser(car(tnode), TRUE));
         if (car(tnode) != NIL && compare_node(caar(tnode), End, TRUE) == 0)
            {
            break;
            }
         else if (car(tnode) != NIL)
            {
            setcdr(lastnode, tnode);
            lastnode = tnode;
            }
         }
      if (to_pending && NOT_THROWING)
         {
         setprocnode__caseobj(proc_name,
            make_procnode(body_list, body_words, minimum,
               deflt, maximum));
         if (macro_flag)
            setflag__caseobj(proc_name, PROC_MACRO);
         else
            clearflag__caseobj(proc_name, PROC_MACRO);
         if (deflt != old_default && old_default >= 0)
            {
            the_generation = reref(the_generation, cons_list(NIL));
            }
         if (loadstream == stdin)
            {
            ndprintf(stdout, "%s defined\n", proc_name);
            }
         }
      to_pending = 0;
      }
   return Unbound;
   }

NODE *lto(NODE *args)
   {
   IsDirty = true;
   input_mode = TO_MODE;
   to_helper(args, FALSE);
   input_mode = NO_MODE;
   return Unbound;
   }

NODE *lmacro(NODE *args)
   {
   IsDirty = true;
   input_mode = TO_MODE;
   to_helper(args, TRUE);
   input_mode = NO_MODE;
   return Unbound;
   }

NODE *lmake(NODE *args)
   {
   NODE *what;

   what = name_arg(args);
   if (NOT_THROWING)
      {
      what = intern(what);
      setvalnode__caseobj(what, cadr(args));
      if (flag__caseobj(what, VAL_TRACED))
         {
         NODE *tvar = maybe_quote(cadr(args));
         ndprintf(writestream, "Make %s %s", make_quote(what), tvar);
         if (ufun != NIL)
            {
            ndprintf(writestream, " in %s\n%s", ufun, this_line);
            }
         new_line(writestream);
         }
      }
   return Unbound;
   }

NODE *llocal(NODE *args)
   {
   NODE *vsp = var_stack;

   if (tailcall != 0) 
     {
     return Unbound;
     }

   if (args == NIL) 
     {
     return Unbound;
     }

   while (is_list(car(args)) && cdr(args) != NIL && NOT_THROWING)
      {
      setcar(args, err_logo(BAD_DATA, car(args)));
      }

   if (is_list(car(args)))
      {
      args = car(args);
      }

   while (args != NIL && NOT_THROWING)
      {
      NODE * arg = car(args);
      while (!is_word(arg) && NOT_THROWING)
         {
         arg = err_logo(BAD_DATA, arg);
         setcar(args, arg);            // prevent crash in lapply
         }
      if (NOT_THROWING)
         {
         arg = intern(arg);
         setcar(args, arg);            // local [a b] faster next time
         if (not_local(arg, vsp))
            {
            push(arg, var_stack);
            setobject(var_stack, valnode__caseobj(arg));
            }
         setvalnode__caseobj(arg, Unbound);
         tell_shadow(arg);
         args = cdr(args);
         }
      if (check_throwing) break;
      }
   var = reref(var, var_stack);        // so eval won't undo our work
   return Unbound;
   }

static NODE *cnt_list = NIL;
static NODE *cnt_last = NIL;
static int want_buried = 0;

typedef enum
   {
   c_PROCS, 
   c_VARS, 
   c_PLISTS,
   }
CNTLSTTYP;


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
	
   if (want_buried) flag_check = want_buried;
	
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

static
void ms_listlist(NODE *nd)
   {
   while (nd != NIL)
      {
      NODE* temp = newnode(CONS);
      car(temp) = car(nd);
      car(nd) = temp;
      increfcnt(temp);
      nd = cdr(nd);
      }
   }

static
NODE *merge(NODE *a, NODE *b)
   {
   NODE *ret, *tail;

   if (a == NIL) return (b);
   if (b == NIL) return (a);
   if (compare_node(car(a), car(b), FALSE) < 0)
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
      if (compare_node(car(a), car(b), FALSE) < 0)
         {
         cdr(tail) = a;
         a = cdr(a);
         }
      else
         {
         cdr(tail) = b;
         b = cdr(b);
         }
      tail = cdr(tail);
      }

   if (b == NIL) cdr(tail) = a;
   else cdr(tail) = b;

   return ret;
   }

static
void mergepairs(NODE *nd)
   {
   NODE *temp;

   while (nd != NIL && cdr(nd) != NIL)
      {
      car(nd) = merge(car(nd), cadr(nd));
      temp = cdr(nd);
      cdr(nd) = cddr(nd);
      car(temp) = cdr(temp) = NIL;
      gc(temp);
      nd = cdr(nd);
      }
   }

static
NODE *mergesort(NODE *nd)
   {
   NODE *ret;

   if (nd == NIL) return (NIL);
   if (cdr(nd) == NIL) return (nd);
   ms_listlist(nd);
   while (cdr(nd) != NIL)
      mergepairs(nd);
   ret = car(nd);
   car(nd) = NIL;
   gc(nd);
   return (ret);
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

NODE *lcontents(NODE *)
   {
   NODE *ret;

   want_buried = 0;

   ret = cons_list(get_contents(c_PLISTS));
   ref(ret);

   push(get_contents(c_VARS), ret);

   push(get_contents(c_PROCS), ret);

   deref(cnt_list);
   cnt_list = NIL;
   return (unref(ret));
   }

NODE *ltraced(NODE *)
   {
   NODE *ret;

   want_buried = PROC_TRACED;

   ret = cons_list(get_contents(c_PLISTS));
   ref(ret);

   push(get_contents(c_VARS), ret);

   push(get_contents(c_PROCS), ret);
	
   deref(cnt_list);
   cnt_list = NIL;
   return(ret);
   }

NODE *lstepped(NODE *)
   {
   NODE *ret;

   want_buried = PROC_STEPPED;

   ret = cons_list(get_contents(c_PLISTS));
   ref(ret);

   push(get_contents(c_VARS), ret);

   push(get_contents(c_PROCS), ret);

   deref(cnt_list);
   cnt_list = NIL;
   return(ret);
   }

NODE *lburied(NODE *)
   {
   NODE *ret;

   want_buried = PROC_BURIED;

   ret = cons_list(get_contents(c_PLISTS));
   ref(ret);

   push(get_contents(c_VARS), ret);

   push(get_contents(c_PROCS), ret);

   deref(cnt_list);
   cnt_list = NIL;
   return (unref(ret));
   }

NODE *lprocedures(NODE *)
   {
   NODE *ret;

   want_buried = 0;

   ret = get_contents(c_PROCS);
   ref(ret);
   deref(cnt_list);
   cnt_list = NIL;
   return (unref(ret));
   }

NODE *lnames(NODE *)
   {
   NODE *ret;

   want_buried = 0;

   ret = cons_list(NIL, get_contents(c_VARS));
   ref(ret);
   deref(cnt_list);
   cnt_list = NIL;
   return (unref(ret));
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
      return cons_list(nd);
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
      arg = car(arg);
      }

   if (!is_list(car(arg)))
      {
      *proclst = arg;
      }
   else
      {
      *proclst = car(arg);
      if (cdr(arg) != NIL)
         {
         *varlst = one_list(cadr(arg));
         if (cddr(arg) != NIL)
            {
            *plistlst = one_list(car(cddr(arg)));
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
char *expand_slash(NODE *wd)
   {
   char *result;
   const char *cp;
   char *cp2;
   int i, len = getstrlen(wd), j;

   for (cp = getstrptr(wd), i = 0, j = len; --j >= 0;)
      if (getparity(*cp++)) i++;
   result = (char *) malloc(len + i + 1);
   if (result == NULL)
      {
      err_logo(OUT_OF_MEM, NIL);
      return 0;
      }
   for (cp = getstrptr(wd), cp2 = result, j = len; --j >= 0;)
      {
      if (getparity(*cp)) *cp2++ = '\\';
      *cp2++ = clearparity(*cp++);
      }
   *cp2 = '\0';
   return result;
   }

static
NODE *po_helper(NODE *arg, int just_titles)  /* >0 for POT, <0 for EDIT       */
   {
   print_backslashes = TRUE;

   NODE *proclst;
   NODE *varlst;
   NODE *plistlst;
   three_lists(arg, &proclst, &varlst, &plistlst);

   while (proclst != NIL)
      {
      if (aggregate(car(proclst)))
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
      else if (nodetype(tvar) & NT_PRIM)
         {
         err_logo(IS_PRIM, car(proclst));
         break;
         }
      else
         {
         tvar = get_bodywords(tvar, car(proclst));
         if (just_titles > 0)
            print_nobrak(writestream, car(tvar));
         else while (tvar != NIL)
            {
            if (is_list(car(tvar)))
               print_nobrak(writestream, car(tvar));
            else
               {
               char *str = expand_slash(car(tvar));
               if (writestream == stdout)
                  {
                  printfx(str);
                  if (dribblestream != NULL)
                     fprintf(dribblestream, "%s\n", str);
                  }
               else
                  {
                  fprintf(writestream, "%s", str);
                  }
               free(str);
               }
            if (writestream != stdout) new_line(writestream);
            tvar = cdr(tvar);
            }
         new_line(writestream);
         }
      proclst = cdr(proclst);
      if (check_throwing) break;
      }

   while (varlst != NIL && NOT_THROWING)
      {
      if (aggregate(car(varlst)))
         {
         err_logo(BAD_DATA_UNREC, car(varlst));
         break;
         }

      NODE * tvar = maybe_quote(valnode__caseobj(intern(car(varlst))));

      if (tvar == Unbound)
         {
         if (just_titles >= 0)
            {
            err_logo(NO_VALUE, car(varlst));
            break;
            }
         }
      else
         {
         ndprintf(writestream, "Make %s %s\n",
            make_quote(car(varlst)), tvar);
         }
      varlst = cdr(varlst);
      if (check_throwing) break;
      }

   while (plistlst != NIL && NOT_THROWING)
      {
      if (aggregate(car(plistlst)))
         {
         err_logo(BAD_DATA_UNREC, car(plistlst));
         break;
         }

      NODE * plist = plist__caseobj(intern(car(plistlst)));
      if (plist != NIL && just_titles > 0)
         {
         ndprintf(
            writestream, 
            "Plist %s = %s\n",
            maybe_quote(car(plistlst)), plist);
         }
      else 
         {
         while (plist != NIL)
            {
            ndprintf(
               writestream, "Pprop %s %s %s\n",
               maybe_quote(car(plistlst)),
               maybe_quote(car(plist)),
               maybe_quote(cadr(plist)));
            plist = cddr(plist);
            }
         }

      plistlst = cdr(plistlst);
      if (check_throwing) break;
      }

   print_backslashes = FALSE;
   return Unbound;
   }

NODE *lpo(NODE *arg)
   {
   lsetcursorwait(NIL);

   NODE * temp = po_helper(arg, 0);

   lsetcursorarrow(NIL);

   return temp;
   }

NODE *lpot(NODE *arg)
   {
   return po_helper(arg, 1);
   }

NODE *lerase(NODE *arg)
   {
   int redef = (compare_node(valnode__caseobj(Redefp), Truex, TRUE) == 0);

   NODE *proclst;
   NODE *varlst;
   NODE *plistlst;
   three_lists(arg, &proclst, &varlst, &plistlst);

   if (proclst != NIL)
      {
      the_generation = reref(the_generation, cons_list(NIL));
      }

   while (proclst != NIL)
      {
      if (aggregate(car(proclst)))
         {
         err_logo(BAD_DATA_UNREC, car(proclst));
         break;
         }
      NODE * nd = intern(car(proclst));
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
      if (aggregate(car(varlst)))
         {
         err_logo(BAD_DATA_UNREC, car(varlst));
         break;
         }
      setvalnode__caseobj(intern(car(varlst)), Unbound);
      varlst = cdr(varlst);
      }

   while (plistlst != NIL && NOT_THROWING)
      {
      if (aggregate(car(plistlst)))
         {
         err_logo(BAD_DATA_UNREC, car(plistlst));
         break;
         }
      setplist__caseobj(intern(car(plistlst)), NIL);
      plistlst = cdr(plistlst);
      }
   return Unbound;
   }

static
void bury_list(NODE * list, int flag)
   {
   while (list != NIL && NOT_THROWING)
      {
      if (aggregate(car(list)))
         {
         err_logo(BAD_DATA_UNREC, car(list));
         break;
         }
      setflag__caseobj(intern(car(list)), flag);
      list = cdr(list);
      if (check_throwing) break;
      }
   }

static
NODE *bury_helper(NODE *arg, int flag)
   {
   NODE *proclst;
   NODE *varlst;
   NODE *plistlst;
   three_lists(arg, &proclst, &varlst, &plistlst);

   bury_list(proclst, flag);

   flag <<= 1;
   bury_list(varlst, flag);

   flag <<= 1;
   bury_list(plistlst, flag);

   return Unbound;
   }

NODE *lbury(NODE *arg)
   {
   return bury_helper(arg, PROC_BURIED);
   }

NODE *ltrace(NODE *arg)
   {
   return bury_helper(arg, PROC_TRACED);
   }

NODE *lstep(NODE *arg)
   {
   return bury_helper(arg, PROC_STEPPED);
   }

static
void unbury_list(NODE * list, int flag)
   {
   while (list != NIL && NOT_THROWING)
      {
      if (aggregate(car(list)))
         {
         err_logo(BAD_DATA_UNREC, car(list));
         break;
         }
      clearflag__caseobj(intern(car(list)), flag);
      list = cdr(list);
      if (check_throwing) break;
      }
   }

static
NODE *unbury_helper(NODE *arg, int flag)
   {
   NODE *proclst;
   NODE *varlst;
   NODE *plistlst;
   three_lists(arg, &proclst, &varlst, &plistlst);

   unbury_list(proclst, flag);

   flag <<= 1;
   unbury_list(varlst, flag);

   flag <<= 1;
   unbury_list(plistlst, flag);

   return Unbound;
   }

NODE *lunbury(NODE *arg)
   {
   return unbury_helper(arg, PROC_BURIED);
   }

NODE *luntrace(NODE *arg)
   {
   return unbury_helper(arg, PROC_TRACED);
   }

NODE *lunstep(NODE *arg)
   {
   return unbury_helper(arg, PROC_STEPPED);
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
         JustDidEdit = true;
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
         NODE * exec_list = parser(current_line, TRUE);
         if (exec_list != NIL)
            {
            eval_driver(exec_list);
            }
         }
      fclose(loadstream);
      val_status = sv_val_status;
      }
   else
      {
      //        err_logo(FILE_ERROR,
      //              make_static_strnode("Could not read editor file"));
      }

   lsetcursorarrow(NIL);
   yield_flag = save_yield_flag;
   loadstream = holdstrm;
   current_line = reref(current_line, tmp_line);

   return realsave;
   }

NODE *lthing(NODE *args)
   {
   NODE *val = Unbound, *arg;

   arg = name_arg(args);
   if (NOT_THROWING) val = valnode__caseobj(intern(arg));
   while (val == Unbound && NOT_THROWING)
      val = err_logo(NO_VALUE, car(args));
   return (val);
   }

NODE *lnamep(NODE *args)
   {
   NODE *arg;

   arg = name_arg(args);
   if (NOT_THROWING)
      return torf(valnode__caseobj(intern(arg)) != Unbound);
   return Unbound;
   }

NODE *lprocedurep(NODE *args)
   {
   NODE *arg;

   arg = name_arg(args);
   if (NOT_THROWING)
      return torf(procnode__caseobj(intern(arg)) != UNDEFINED);
   return Unbound;
   }

NODE *lproplistp(NODE *args)
   {
   NODE *arg;

   arg = name_arg(args);
   if (NOT_THROWING)
      return torf(plist__caseobj(intern(arg)) != NIL);
   return Unbound;
   }

// wanted:
//   0 = defined
//   1 = primative
//   2 = macro
static
NODE *check_proctype(NODE *args, int wanted)
   {
   NODE * cell;
   NODE * arg = name_arg(args);
   if (NOT_THROWING && (cell = procnode__caseobj(intern(arg))) == UNDEFINED)
      {
      return (Falsex);
      }

   if (wanted == 2)
      {
      return torf(is_macro(intern(arg)));
      }

   int isprim = is_prim(cell);
   if (NOT_THROWING)
      {
      return torf((isprim != 0) == wanted);
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
   int old_default, new_default;
   int redef = (compare_node(valnode__caseobj(Redefp), Truex, TRUE) == 0);

   NODE * arg1 = name_arg(args);
   NODE * arg2 = name_arg(cdr(args));
   if (numberp(arg2)) err_logo(BAD_DATA_UNREC, arg2);
   if (numberp(arg1)) err_logo(BAD_DATA_UNREC, arg1);
   if (NOT_THROWING)
      {
      arg1 = intern(arg1);
      arg2 = intern(arg2);
      }
   if (NOT_THROWING && procnode__caseobj(arg2) == UNDEFINED)
      err_logo(DK_HOW, arg2);
   if (NOT_THROWING && !redef && is_prim(procnode__caseobj(arg1)))
      err_logo(IS_PRIM, arg1);
   if (NOT_THROWING)
      {
      NODE *old_proc = procnode__caseobj(arg1);
      NODE *new_proc = procnode__caseobj(arg2);
      if (old_proc != UNDEFINED)
         {
         old_default = (is_prim(old_proc) ? getprimdflt(old_proc) :
               getint(dfltargs__procnode(old_proc)));
         new_default = (is_prim(new_proc) ? getprimdflt(new_proc) :
               getint(dfltargs__procnode(new_proc)));
         if (old_default != new_default)
            {
            the_generation = reref(the_generation, cons_list(NIL));
            }
         }
      //      if (old_proc != UNDEFINED)
      //         {
      //         if (getint(dfltargs__procnode(old_proc)) !=
      //         getint(dfltargs__procnode(new_proc)))
      //            {
      //            the_generation = reref(the_generation, cons_list(NIL));
      //            }
      //         }
      setprocnode__caseobj(arg1, new_proc);
      setflag__caseobj(arg1, PROC_BURIED);
      if (is_macro(arg2)) setflag__caseobj(arg1, PROC_MACRO);
      else clearflag__caseobj(arg1, PROC_MACRO);
      }
   return Unbound;
   }

