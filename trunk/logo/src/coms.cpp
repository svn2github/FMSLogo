/*
*      coms.cpp     program execution control module      dvb
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
#include <math.h>
#include <time.h>
#include <string.h>

#include "coms.h"
#include "logocore.h"
#include "mem.h"
#include "eval.h"
#include "init.h"
#include "error.h"
#include "logomath.h"
#include "parse.h"
#include "lists.h"
#include "graphwin.h"
#include "graphics.h"
#include "stringprintednode.h"
#include "debugheap.h"

// ift_iff_flag: flag for if TEST has been called within the scope
// -1 : TEST has not been called.
//  0 : TEST "FALSE has been called.
//  1 : TEST "TRUE has been called.
FIXNUM ift_iff_flag = -1;

NODE *make_cont(enum labels cont, NODE *val)
{
    NODE *retval = cons(NIL, val);
    retval->nunion.ncons.ncar = reinterpret_cast<NODE *>(cont);
    settype(retval, CONT);
    return retval;
}

NODE *loutput(NODE *arg)
{
    if (NOT_THROWING)
    {
        stopping_flag = OUTPUT;
        assign(output_node, car(arg));
    }
    return Unbound;
}

NODE *lstop(NODE *)
{
    if (NOT_THROWING)
    {
        stopping_flag = STOP;
    }
    return Unbound;
}

NODE *lthrow(NODE *arg)
{
    if (NOT_THROWING)
    {
        if (Error.Equals(car(arg)))
        {
            // this a THROW "ERROR
            if (cdr(arg) != NIL)
            {
                NODE * secondInput = cadr(arg);

                // A third input was specified.
                // If it's a number, then we may have a special case 
                // to throw an error as if it were an internal error.
                NODE * number = cnv_node_to_numnode(secondInput);

                // convert floating point numbers to integers
                FIXNUM value = -1;
                FLONUM f;
                if (nodetype(number) == INTEGER)
                {
                    value = getint(number);
                }
                else if (nodetype(number) == FLOATINGPOINT &&
                         fmod((f = getfloat(number)), 1.0) == 0.0 && 
                         f >= -(FLONUM) FIXNUM_MAX && 
                         f < (FLONUM) FIXNUM_MAX)
                {
                    value = f;
                }

                gcref(number);

                if (value == BAD_DATA_UNREC)
                {
                    if (cddr(arg))
                    {
                        NODE * thirdInput = car(cddr(arg));
                        err_logo(BAD_DATA_UNREC, thirdInput, true);
                    }
                    else
                    {
                        // the second input is a simple error text
                        err_logo(USER_ERR, secondInput);
                    }
                }
                else
                {
                    // the second input is a simple error text
                    err_logo(USER_ERR, secondInput);
                }
            }
            else
            {
                err_logo(USER_ERR, Unbound);
            }
        }
        else
        {
            stopping_flag = THROWING;
            assign(throw_node, car(arg));
            if (cdr(arg) != NIL)
            {
                assign(output_node, cadr(arg));
            }
            else
            {
                assign(output_node, Unbound);
            }
        }
    }
    return Unbound;
}

NODE *lcatch(NODE *args)
{
    return make_cont(catch_continuation, cons(car(args), lrun(cdr(args))));
}

bool boolean_arg(NODE *args)
{
    NODE *arg = car(args);

    while (NOT_THROWING)
    {
        if (Truex.Equals(arg)) 
        {
            return true;
        }
        if (Falsex.Equals(arg))
        {
            return false;
        }
        setcar(args, err_logo(BAD_DATA, arg));
        arg = car(args);
    }

    // default to "true" for backward compatability.
    // (This used to return to -1, which is more likely to behave like "true" than "false").
    return true;
}

NODE *lgoto(NODE *args)
{
    return make_cont(goto_continuation, car(args));
}

NODE *ltag(NODE * /* args */)
{
    return Unbound;
}

NODE *lnot(NODE *args)
{
    bool arg = boolean_arg(args);

    if (NOT_THROWING)
    {
        return true_or_false(!arg);
    }

    return Unbound;
}

NODE *land(NODE *args)
{
    // if there are no false inputs, then the entire expression is true
    NODE * rval = Truex.GetNode();
   
    for (NODE* current_arg = args;
         current_arg != NIL;
         current_arg = cdr(current_arg))
    {
        bool arg = boolean_arg(current_arg);
        if (stopping_flag == THROWING)
        {
            return Unbound;
        }

        if (!arg)
        {
            // found a false input, so entire expression is false
            rval = Falsex.GetNode();

            // Don't break because we want to validate 
            // the rest of the inputs.
        }
    }

    return rval;
}

NODE *lor(NODE *args)
{
    // if there are no true inputs, then the entire expression is false
    NODE * rval = Falsex.GetNode();
   
    for (NODE* current_arg = args;
         current_arg != NIL;
         current_arg = cdr(current_arg))
    {
        bool arg = boolean_arg(current_arg);
        if (stopping_flag == THROWING)
        {
            return Unbound;
        }

        if (arg)
        {
            // found a true input, so entire expression is true
            rval = Truex.GetNode();

            // Don't break because we want to validate 
            // the rest of the inputs.
        }
    }

    return rval;
}

NODE *runnable_arg(NODE *args)
{
    NODE *arg = car(args);

    if (!is_aggregate(arg))
    {
        setcar(args, parser(arg, TRUE));
        arg = car(args);
    }
    while (!is_list(arg) && NOT_THROWING)
    {
        setcar(args, err_logo(BAD_DATA, arg));
        arg = car(args);
    }
    return arg;
}

NODE *lif(NODE *args)  // macroized
{
    if (cddr(args) != NIL)
    {
        return lifelse(args);
    }

    bool pred = boolean_arg(args);
    NODE * yes = runnable_arg(cdr(args));
    if (NOT_THROWING)
    {
        if (pred) 
        {
            return yes;
        }
        return NIL;
    }

    return Unbound;
}

NODE *lifelse(NODE *args)              // macroized
{
    bool pred = boolean_arg(args);
    NODE* yes = runnable_arg(cdr(args));
    NODE* no = runnable_arg(cddr(args));
    if (NOT_THROWING)
    {
        if (pred) 
        {
            return yes;
        }
        return no;
    }
    return Unbound;
}

NODE *lrun(NODE *args)                 // macroized
{
    NODE *arg = runnable_arg(args);

    if (NOT_THROWING)
    {
        return arg;
    }
    return Unbound;
}

NODE *lrunresult(NODE *args)
{
    return make_cont(runresult_continuation, lrun(args));
}

NODE *lrepeat(NODE *args)
{
    NODE * cnt       = nonnegative_int_arg(args);
    NODE * to_repeat = lrun(cdr(args));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    return make_cont(repeat_continuation, cons(cnt, to_repeat));
}

NODE *lrepcount(NODE *)
{
    return make_intnode((FIXNUM) repcountup);
}

NODE *lforever(NODE *args)
{
    NODE *to_repeat = lrun(args);

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    return make_cont(repeat_continuation, cons(make_intnode(-1), to_repeat));
}

NODE *ltest(NODE *args)
{
    bool arg = boolean_arg(args);

    if (tailcall != 0)
    {
        return Unbound;
    }

    if (NOT_THROWING)
    {
        ift_iff_flag = arg ? 1 : 0;
        dont_fix_ift = 1;
    }
    return Unbound;
}

NODE *liftrue(NODE *args)
{
    if (ift_iff_flag < 0)
    {
        // TEST has not been run in this scope
        return err_logo(NO_TEST, NIL);
    }
    else if (ift_iff_flag > 0)
    {
        // TEST "TRUE has been run in this scope
        return lrun(args);
    }
    else
    {
        // TEST "FALSE has been run in this scope
        return NIL;
    }
}

NODE *liffalse(NODE *args)
{
    if (ift_iff_flag < 0)
    {
        // TEST has not been run in this scope
        return err_logo(NO_TEST, NIL);
    }
    else if (ift_iff_flag == 0)
    {
        // TEST "FALSE has been run in this scope
        return lrun(args);
    }
    else
    {
        // TEST "TRUE has been run in this scope
        return NIL;
    }
}

void prepare_to_exit(bool /* okay */)
{
    exit_program();
}

NODE *lbye(NODE *)
{
    prepare_to_exit(TRUE);
    //    if (ufun != NIL || loadstream != stdin) exit(0);
    //    if (isatty(0) && isatty(1)) lcleartext();
    //    printf("Thank you for using Logo.\n");
    //    printf("Have a nice day.\n");
    return Unbound;
}

/* LOGO time */
NODE *ltime(NODE *)
{
    time_t tvec;
    time(&tvec);
    const char * Xtim = ctime(&tvec);

    NODE * arg = make_strnode(Xtim, strlen(Xtim) - 1, STRING, strnzcpy);
    NODE * val = parser(arg, false);
    return val;
}

/* LOGO time */
NODE *ltimemilli(NODE *)
{
#ifdef WX_PURE
    return NIL;
#else
    return make_intnode((FIXNUM) GetTickCount());
#endif
}

NODE *lwait(NODE *args)
{
#ifndef WX_PURE
    NODE * num = nonnegative_numeric_arg(args);
    if (NOT_THROWING)
    {
        FLONUM input = numeric_node_to_flonum(num);

        // The input is in 60ths of a second.  To convert to milliseconds:  
        //   (input / 60) * 1000 = input * 50 / 3 
        DWORD totalTicksToWait = g_round(input * 50.0 / 3.0);


        // Do a busy sleep so that a long WAIT can be interrupted by a HALT
        DWORD endTime = GetTickCount() + totalTicksToWait;
        while (GetTickCount() < endTime && !IsTimeToHalt) 
        {
            MyMessageScan();

            if (GetTickCount() + 10 < endTime)
            {
                // We're more than 10 ms away from the target time,
                // so we don't risk missing our target time by yielding.
                Sleep(1);  // yield
            }
        }
    }
#endif
    return Unbound;
}

NODE *lshell(NODE *args)
{
#ifdef WX_PURE
    bool isOk = false;
#else
    CStringPrintedNode shellCommand(car(args));

    bool waitForChildProcess;
    if (cdr(args) != NIL)
    {
        // a second input was given
        waitForChildProcess = boolean_arg(cdr(args));
    }
    else
    {
        // no second input was given
        waitForChildProcess = false;
    }

    if (stopping_flag == THROWING)
    {
        // we were passed invalid arguments
        return Unbound;
    }

    STARTUPINFO         startupInfo = {0};
    PROCESS_INFORMATION processInfo;

    BOOL isOk = CreateProcess(
        NULL,
        shellCommand,
        NULL,  // process security attribute
        NULL,  // thread security attributes
        FALSE, // don't inherit handles
        0,     // creation flags
        NULL,  // use FMSLogo's environment
        NULL,  // use FMSLogo's current working directory
        &startupInfo,
        &processInfo);
    if (isOk)
    {
        if (waitForChildProcess)
        {
            // Wait for the child process to exit.
            // Do a busy wait so that it can be interrupted by a HALT
            DWORD waitStatus = WAIT_TIMEOUT;
            while (waitStatus == WAIT_TIMEOUT && !IsTimeToHalt)
            {
                MyMessageScan();
                waitStatus = ::WaitForSingleObject(processInfo.hProcess, 10);
            }
        }

        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
    }

#endif
    return true_or_false(isOk);
}
