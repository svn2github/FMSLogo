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

#include "wrksp.h"
#include "logodata.h"
#include "appendablelist.h"
#include "intern.h"
#include "init.h"
#include "mem.h"
#include "parse.h"
#include "eval.h"
#include "error.h"
#include "logomath.h"
#include "paren.h"
#include "ibmterm.h"
#include "startup.h"
#include "print.h"
#include "files.h"
#include "unix.h"
#include "debugheap.h"

#include "localizedstrings.h"
#include "cursor.h"
#include "mainwind.h"
#include "screenwindow.h"

bool bExpert    = false;               // Expert mode
bool yield_flag = true;                // Flag to signal yield state
bool IsDirty    = false;               // Flag to signal to query user ok to quit
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
    toline.AppendElement(is_macro(name) ? Macro : To.GetNode());
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
    bodywordslist.AppendElement(cons_list(End.GetNode()));

    // we're done making the bodywords list
    bodywords = bodywordslist.GetList();

    // cache the value of the bodywords so we won't have to
    // create it the next time.
    setbodywords__procnode(proc, bodywords);

    // return the bodywords
    return bodywords;
}


// Gets the first argument in the args list as a name of a variable or plist.
// Throws recoverable bad input errors until it gets one.
static
NODE *name_arg(NODE *args)
{
    while (is_aggregate(car(args)) && NOT_THROWING)
    {
        setcar(args, err_logo(BAD_DATA, car(args)));
    }
    return car(args);
}


// Gets the first argument in the args list as a name of a procedure.
// Throws recoverable bad input errors until it gets one.
static
NODE *proc_name_arg(NODE *args)
{
    while ((is_aggregate(car(args)) || numberp(car(args))) && NOT_THROWING)
    {
        setcar(args, err_logo(BAD_DATA, car(args)));
    }
    return car(args);
}

void untreeify_procnode(NODE * procnode)
{
    if (procnode != NIL && procnode != UNDEFINED)
    {
        // untreeify the body
        if (!is_prim(procnode) && is_tree(bodylist__procnode(procnode)))
        {
            untreeify_body(bodylist__procnode(procnode));
        }
    }
}

NODE *ltext(NODE *args)
{
    NODE* name = proc_name_arg(args);
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
    NODE* name = proc_name_arg(args);
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
        name = proc_name_arg(args);
        if (NOT_THROWING)
        {
            name = intern(name);
            val = procnode__caseobj(name);
            bool redef = canRedefinePrimitives();
            if (!redef && is_prim(val))
            {
                err_logo(IS_PRIM, name);
                return Unbound;
            }
            else if (val != UNDEFINED)
            {
                untreeify_procnode(val);
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

    deepend_proc_name = vref(proc_name);  // for error reporting

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
            untreeify_procnode(old_proc);
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
                if (nodetype(car(arg)) != COLON)
                {
                    // input names must begin with a colon
                    err_logo(BAD_DATA_UNREC, arg);
                    break;
                }

                setcar(arg, node__colon(car(arg)));
                if (cdr(arg) == NIL)
                {
                    // this is a "rest" input
                    maximum = -1;
                }
                else
                {
                    // this is an input with a default value
                    maximum++;
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

        g_ToLine    = reref(g_ToLine, body_words);
        to_pending = true;      // for int or quit signal
        while (NOT_THROWING && to_pending && !feof(loadstream))
        {
            NODE * ttnode = reader(loadstream, "> ");

            // append ttnode to body_words
            NODE * tnode = cons_list(ttnode);
            setcdr(body_words_lastnode, tnode);
            body_words_lastnode = tnode;

            NODE * next_line = parser(car(body_words_lastnode), true);
            if (next_line != NIL && End.Equals(car(next_line)))
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
                ndprintf(stdout, LOCALIZED_PROCEDUREDEFINED, proc_name);
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

        rd_clearbuffer(loadstream);
        g_ToLine   = reref(g_ToLine, NIL);
        to_pending = false;
    }
    else
    {
        gcref(formals);
    }

    deepend_proc_name = reref(deepend_proc_name, NIL);
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
                g_Writer.GetStream(),
                LOCALIZED_TRACING_MAKE,
                quoted_variable_name,
                new_value);

            deref(quoted_variable_name);
            deref(new_value);

            // trace the name of the procedure where the assignment happened.
            if (ufun != NIL)
            {
                ndprintf(
                    g_Writer.GetStream(),
                    LOCALIZED_TRACING_LOCATION,
                    ufun,
                    this_line);
            }
            new_line(g_Writer.GetStream());
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
        if (ecma_get(*cp++)) 
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
        if (ecma_get(*cp))
        {
            // backslash this character
            *cp2++ = '\\';
        }
        *cp2++ = ecma_clear(*cp++);
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

    // print all of the requested procedures
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
            // the procedure hasn't been defined.

            if (just_titles < 0)
            {
                // We're doing an EDIT, so it's okay that the
                // procedure hasn't been defined.
                // Print the following boilerplate for the user:
                //   TO <proc>\n
                //   END\n
                //   \n
                ndprintf(
                    g_Writer.GetStream(), 
                    "%t %p\n%t\n\n", 
                    To.GetName(),
                    car(proclst),
                    End.GetName());
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
            NODE * bodywords = get_bodywords(tvar, car(proclst));
            if (just_titles > 0)
            {
                // only print the title line 
                NODE * titleline = car(bodywords);
                if (is_list(titleline))
                {
                    print_helper(g_Writer.GetStream(), titleline);
                }
                else
                {
                    char *str = expand_slash(titleline);
                    ndprintf(g_Writer.GetStream(), "%t", str);
                    free(str);
                }
            }
            else 
            {
                // Print the entire procedure definition one line at a time.
                while (bodywords != NIL)
                {
                    NODE * currentline = car(bodywords);
                    if (is_list(currentline))
                    {
                        print_helper(g_Writer.GetStream(), currentline);
                    }
                    else
                    {
                        char *str = expand_slash(currentline);
                        if (g_Writer.GetStream() == stdout)
                        {
                            if (str[0] == '\0')
                            {
                                // str doesn't end in a newline.  
                                // printfx() always writes a newline to the
                                // commander history, regardless of if the 
                                // string ends in a newline (in essence, the 
                                // newline is optional).  However, it doesn't
                                // write anything when given the empty
                                // string, which is what happens when there's a
                                // blank line in the procedure definition.
                                // To ensure that blank lines are preserved, we
                                // write a newline.
                                // Note that we can't just call 
                                //   printfx("%s\n", str);
                                // because that could overflow the buffer in
                                // printfx()
                                printfx("\n");
                            }
                            else
                            {
                                printfx(str);
                            }

                            if (dribblestream != NULL)
                            {
                                fprintf(dribblestream, "%s\n", str);
                            }
                        }
                        else
                        {
                            fprintf(g_Writer.GetStream(), "%s", str);
                        }
                        free(str);
                    }

                    if (g_Writer.GetStream() != stdout) 
                    {
                        new_line(g_Writer.GetStream());
                    }

                    bodywords = cdr(bodywords);
                }
            }
            new_line(g_Writer.GetStream());
        }
        proclst = cdr(proclst);
        if (check_throwing) break;
    }

    // print all of the requested variables
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

            // MAKE "name "value
            ndprintf(
                g_Writer.GetStream(),
                "%t %s %s\n",
                LOCALIZED_ALTERNATE_MAKE,
                quoted_variable_name,
                quoted_value);

            gcref(quoted_variable_name);
        }
        gcref(quoted_value);
    }

    // print all of the requested property lists
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
            // PLIST "name = [name1 value1 name2 value2]
            ndprintf(
                g_Writer.GetStream(), 
                "%t %s = %s\n",
                LOCALIZED_ALTERNATE_PLIST,
                quoted_plist_name, 
                plist);
        }
        else 
        {
            while (plist != NIL)
            {
                NODE * quoted_property_name  = maybe_quote(car(plist));
                NODE * quoted_property_value = maybe_quote(cadr(plist));

                // PPROP "list "name "value
                ndprintf(
                    g_Writer.GetStream(), 
                    "%t %s %s %s\n",
                    LOCALIZED_ALTERNATE_PPROP,
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
        bool redef = canRedefinePrimitives();
        if (!redef && is_prim(procnode__caseobj(nd)))
        {
            err_logo(IS_PRIM, nd);
            break;
        }

        untreeify_procnode(procnode__caseobj(nd));

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
        // non-experts shouldn't have to understand the complexities of 
        // having multiple editors open.  So if an editor is open, give
        // it focus instead of opening a new one.
        if (GetMainWindow() != NULL)
        {
            HWND editor = GetEditorWindow();
            if (editor != NULL)
            {
                ShowWindow(editor, SW_SHOWNORMAL);
                SetWindowPos(editor, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                SetFocus(editor);
                return Unbound;
            }
        }
    }

    bool save_yield_flag = yield_flag;
    yield_flag = false;
    lsetcursorwait(NIL);

    // Write the requested contents to a file
    if (args != NIL)
    {
        FILE * fileStream = fopen(TempPathName, "w");
        if (fileStream != NULL)
        {
            // HACK: change g_Writer to use the new stream
            FILE * savedWriterStream = g_Writer.GetStream();
            g_Writer.SetStream(fileStream);

            po_helper(args, -1);

            // restore g_Writer
            g_Writer.SetStream(savedWriterStream);

            fclose(fileStream);
        }
        else
        {
            err_logo(
                FILE_ERROR,
                make_static_strnode(LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR));
        }
    }

    // open the file inside an editor
    if (NOT_THROWING)
    {
        NODE * args_list = vref(args);
        if (ShowEditorForFile(TempPathName, args_list))
        {
            err_logo(
                FILE_ERROR, 
                make_static_strnode(LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR));
        }
        else
        {
            remove(TempPathName);
            IsDirty = true;
        }
    }

    lsetcursorarrow(NIL);
    yield_flag = save_yield_flag;

    return Unbound;
}

bool endedit(void)
{
    bool realsave = false;

    FILE * holdstrm = loadstream;
    NODE * tmp_line = vref(current_line);
    bool save_yield_flag = yield_flag;
    yield_flag = false;
    lsetcursorwait(NIL);

    LinesLoadedOnEdit = 0;

    loadstream = fopen(TempPathName, "r");
    if (loadstream != NULL)
    {
        FIXNUM saved_value_status = g_ValueStatus;

        realsave = true;
        while (!feof(loadstream) && NOT_THROWING)
        {
            fgetpos(loadstream, &LinesLoadedOnEdit);
            current_line = reref(current_line, reader(loadstream, ""));
         
            NODE * exec_list = parser(current_line, true);

            g_ValueStatus = VALUE_STATUS_NotOk;
            eval_driver(exec_list);
        }
        fclose(loadstream);
        g_ValueStatus = saved_value_status;
    }
    else
    {
        // err_logo(
        //    FILE_ERROR,
        //    make_static_strnode(LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR));
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
    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    NODE * procnode = load_procedure_if_necessary(intern(arg));
    return true_or_false(procnode != UNDEFINED);
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


enum PROCTYPE
{
    PROCTYPE_UserDefined,
    PROCTYPE_Primitive,
    PROCTYPE_Macro,
};

static
NODE *check_proctype(NODE *args, PROCTYPE wanted)
{
    NODE * arg = proc_name_arg(args);
    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    NODE * interned_arg = intern(arg);

    NODE * procnode;
    if (wanted == PROCTYPE_Primitive)
    {
        procnode = procnode__caseobj(interned_arg);
    }
    else
    {
        // macros and user-defined functions may be implemented 
        // as a library routine, so we try to load it if it's not
        // already loaded.
        procnode = load_procedure_if_necessary(interned_arg);
    }

    if (procnode == UNDEFINED)
    {
        // this isn't even a procedure
        return Falsex.GetNode();
    }

    bool istype = false;

    switch (wanted)
    {
    case PROCTYPE_UserDefined:
        istype = is_prim(procnode) ? false : true;
        break;

    case PROCTYPE_Primitive:
        istype = is_prim(procnode) ? true : false;
        break;

    case PROCTYPE_Macro:
        istype = is_macro(interned_arg);
        break;

    default:
        assert(!"Internal Error: Bad Argument");
    }

    return true_or_false(istype);
}

NODE *lprimitivep(NODE *args)
{
    return check_proctype(args, PROCTYPE_Primitive);
}

NODE *ldefinedp(NODE *args)
{
    return check_proctype(args, PROCTYPE_UserDefined);
}

NODE *lmacrop(NODE *args)
{
    return check_proctype(args, PROCTYPE_Macro);
}

// Copies the title line from a procedure definition
// while replacing the name of the function.
static
NODE *cpdf_newname(NODE * Name, NODE * TitleLine)
{
    // Get the string from Name
    NODE *nname = cnv_node_to_strnode(Name);
    const char * namestr = getstrptr(nname);

    // For the purpose of this function, the title line
    // consists of three parts:
    // (TO|.MACRO) (procname) (args)*
    const char * titlestr = getstrptr(TitleLine);

    // Set p1 to just before the procedure name
    // Either "TO" or ".MACRO" comes before it.
    const char * p1 = titlestr + strcspn(titlestr, " \t");
    p1 = p1 + strspn(p1, " \t");

    // Set p2 to just after the procedure name.
    const char * p2 = p1 + strcspn(p1, " \t");

    // Contruct the new title line by replacing only
    // the name part of the original title line.
    char newTitleLine[2000];
    sprintf(
        newTitleLine,
        "%.*s%.*s%s",
        p1-titlestr, titlestr,
        getstrlen(nname), namestr,
        p2);

    return make_strnode(newTitleLine);
}

NODE *lcopydef(NODE *args)
{
    NODE * arg1 = proc_name_arg(args);
    NODE * arg2 = proc_name_arg(cdr(args));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    arg1 = intern(arg1);
    arg2 = intern(arg2);

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    // load the procedure, in case we're copydef'ing a library routine
    NODE * new_proc = load_procedure_if_necessary(arg2);
    if (new_proc == UNDEFINED)
    {
        // the second input isn't the name of a procedure
        err_logo(DK_HOW, arg2);
        return Unbound;
    }

    bool redef = canRedefinePrimitives();
    if (!redef && is_prim(procnode__caseobj(arg1)))
    {
        // attempted to redefine a primitive
        err_logo(IS_PRIM, arg1);
        return Unbound;
    }

    NODE *old_proc = procnode__caseobj(arg1);
    if (old_proc != UNDEFINED)
    {
        // The first input was already defined as something,
        // so we must redefine it.
        untreeify_procnode(old_proc);

        int old_default = get_default_args_for_procedure(old_proc);
        int new_default = get_default_args_for_procedure(new_proc);

        if (old_default != new_default)
        {
            set_new_generation();
        }
    }

    if (!is_prim(new_proc))
    {
        // We are copying a user-defined function.
        // We must copy the body of the procedure, but change
        // the name of the procedure in the TO line,
        // or else the new procedure will have the same name
        // as the old procudure, which is confusing if the
        // function is ever printed out.
        NODE *bwds = get_bodywords(new_proc, arg1);
        new_proc = make_procnode(
            text__procnode(new_proc),
            cons(cpdf_newname(arg1,car(bwds)), cdr(bwds)),
            getint(minargs__procnode(new_proc)),
            getint(dfltargs__procnode(new_proc)),
            getint(maxargs__procnode(new_proc)));
    }

    // set the first input to have the same procedure as the second input
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

    return Unbound;
}
