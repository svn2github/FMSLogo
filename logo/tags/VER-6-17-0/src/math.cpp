/*
 *      math.cpp          logo math functions module              dvb
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

#include "const.h"

const char MATHFUNC_Sum        = '+';
const char MATHFUNC_Difference = '-';
const char MATHFUNC_Product    = '*';
const char MATHFUNC_Quotient   = '/';
const char MATHFUNC_Remainder  = '%';
const char MATHFUNC_Modulo     = 'm';
const char MATHFUNC_BitAnd     = '&';
const char MATHFUNC_BitOr      = '|';
const char MATHFUNC_BitXor     = '^';
const char MATHFUNC_BitAShift  = 'a';
const char MATHFUNC_BitLShift  = 'l';
const char MATHFUNC_BitNot     = '~';
const char MATHFUNC_Sin        = 's';
const char MATHFUNC_Cos        = 'c';
const char MATHFUNC_Tan        = 't';
const char MATHFUNC_ArcSin     = 'v';
const char MATHFUNC_ArcCos     = 'w';
const char MATHFUNC_ArcTan     = 'x';
const char MATHFUNC_RadSin     = 'S';
const char MATHFUNC_RadCos     = 'C';
const char MATHFUNC_RadTan     = 'T';
const char MATHFUNC_RadArcSin  = 'V';
const char MATHFUNC_RadArcCos  = 'W';
const char MATHFUNC_RadArcTan  = 'X';
const char MATHFUNC_SquareRoot = 'q';
const char MATHFUNC_Integer    = 'i';
const char MATHFUNC_Round      = 'r';
const char MATHFUNC_Exp        = 'e';
const char MATHFUNC_Log10      = 'g';
const char MATHFUNC_Ln         = 'n';
const char MATHFUNC_Power      = 'p';

// returns 0  if snd is not a number
// returns 1  if snd is an integer
// returns >1 if snd is a floating point value
int numberp(NODE *snd)
{
    if (is_number(snd)) 
    {
        return 1;
    }

    NODE * stringnode = cnv_node_to_strnode(snd);
    if (stringnode == Unbound) 
    {
        return 0;
    }

    // HACK: only ref() and deref() stringnode if cnv_node_to_strnode()
    // creates a new node.
    // This hack is necessary because cnv_node_to_strnode() is so hard to use. 
    // Really, cnv_node_to_strnode() should be simplified.
    bool mustDerefStringnode = false;
    if (snd != stringnode)
    {
        ref(stringnode);
        mustDerefStringnode = true;
    }

    const char * p = getstrptr(stringnode);
    int plen = getstrlen(stringnode);
    if (plen >= MAX_NUMBER)
    {
        if (mustDerefStringnode)
        {
            deref(stringnode);
        }
        return 0;
    }

    int dl   = 0; // index of the end of the number before the decimal point
    int dr   = 0; // index to the end of the number after the decimal point
    int pcnt = 0; // index of the "current" character
    if (pcnt < plen && *p == '-')
    {
        p++, pcnt++;
    }

    while (pcnt < plen && isdigit(*p))
    {
        p++, pcnt++, dl++;
    }

    if (pcnt < plen && *p == '.')
    {
        p++, pcnt++;
        while (pcnt < plen && isdigit(*p))
        {
            p++, pcnt++, dr++;
        }
    }

    if (pcnt < plen && (dl || dr) && (*p == 'E' || *p == 'e'))
    {
        p++, pcnt++;

        if (pcnt < plen && *p == '+' || *p == '-')
        {
            p++, pcnt++;
        }

        while (pcnt < plen && isdigit(*p))
        {
            p++, pcnt++, dr++;
        }
    }

    int rval;
    if ((dl == 0 && dr == 0) || pcnt != plen)
    {
        rval = 0;
    }
    else
    {
        rval = dr + 1;
    }

    if (mustDerefStringnode)
    {
        deref(stringnode);
    }
    return rval;
}


NODE *lrandom(NODE *arg)
{
    NODE *val = pos_int_arg(arg);
    if (NOT_THROWING)
    {
        long r;
#ifdef bsd
        r = (getint(val) == 0 ? 0 : random() % getint(val));
#else
        // r = (getint(val) == 0 ? 0 : rand() % getint(val));
        r = (((long) rand()) << 15) | rand();
        r = (getint(val) == 0 ? 0 : r % getint(val));
#endif
        val = make_intnode((FIXNUM) r);
        return val;
    }
    else 
    {
        return Unbound;
    }
}

NODE *lrerandom(NODE *arg)
{
    int seed = 1;

    if (arg != NIL)
    {
        seed = int_arg(arg);
    }
    if (NOT_THROWING)
    {
#ifdef bsd
        srandom((int) seed);
#else
        srand((int) seed);
#endif
    }
    return Unbound;
}


static jmp_buf oflo_buf;

#define sig_arg 0
static
void handle_oflo(int /*sig*/)
{
    // _fpreset();  // commented out for bug #1397560 
    longjmp(oflo_buf, 1);
}

// Override the default Borland math error handling, which
// displays a dialog box whenever a trig function is given
// bad input.  This is not Logo-like--it should throw a Logo
// error instead of halting the program.
// By doing a long jump, the calling code will handle it
// equivalent to how they handle floating point exceptions,
// which is exactly what we want.
int _RTLENTRY _matherr (struct exception *e)
{
    longjmp(oflo_buf, 1);
    return 1;
}

//#define errchk(x) x
#define errchk(x) { errno = 0; x; if (errno) err_logo(BAD_DATA_UNREC,arg); }/*ignore*/

static
NODE * get_arg_for_function(NODE * args, char fcn)
{
    NODE * arg;

    switch (fcn)
    {
    case MATHFUNC_Remainder:
    case MATHFUNC_Modulo:
    case MATHFUNC_BitAnd:
    case MATHFUNC_BitOr:
    case MATHFUNC_BitXor:
    case MATHFUNC_BitAShift:
    case MATHFUNC_BitLShift:
        // changes 1.0 to 1.
        arg = integer_arg(args);
        break;

    default:
        // any number is good input
        arg = numeric_arg(args);
    }

    return arg;
}

static
NODE *binary(NODE *args, char fcn)
{
    NODE * arg = get_arg_for_function(args, fcn);

    args = cdr(args);
    if (stopping_flag == THROWING) 
    {
        return Unbound;
    }

    bool imode;
    FIXNUM ival;
    FLONUM fval;
    if (nodetype(arg) == INTEGER)
    {
        imode = true;
        ival = getint(arg);
    }
    else
    {
        imode = false;
        fval = getfloat(arg);
    }

    if (args == NIL)
    {
        // one argument supplied
        if (imode)
        {
            switch (fcn)
            {
            case MATHFUNC_Difference: 
                ival = -ival; 
                break;

            case MATHFUNC_BitNot: 
                ival = ~ival; 
                break;

            case MATHFUNC_ArcSin:
            case MATHFUNC_ArcCos:
            case MATHFUNC_ArcTan:
            case MATHFUNC_RadArcSin:
            case MATHFUNC_RadArcCos:
            case MATHFUNC_RadArcTan:
            case MATHFUNC_Sin:
            case MATHFUNC_Cos:
            case MATHFUNC_Tan:
            case MATHFUNC_RadSin:
            case MATHFUNC_RadCos:
            case MATHFUNC_RadTan:
            case MATHFUNC_SquareRoot:
            case MATHFUNC_Exp:
            case MATHFUNC_Log10:
            case MATHFUNC_Ln:
            case MATHFUNC_Quotient:
                imode = false;
                fval = (FLONUM) ival;
                break;
            }
        }

        if (!imode)
        {
            if (!setjmp(oflo_buf))
            {
                switch (fcn)
                {
                case MATHFUNC_Difference: 
                    fval = -fval; 
                    break;

                case MATHFUNC_Quotient:
                    if (fval == 0.0)
                    {
                        err_logo(BAD_DATA_UNREC, arg);
                    }
                    else
                    {
                        fval = 1 / fval;
                    }
                    break;

                case MATHFUNC_BitNot: 
                    err_logo(BAD_DATA_UNREC, arg); 
                    break;

                case MATHFUNC_Cos: 
                    fval = cos(fval * rads_per_degree); 
                    break;

                case MATHFUNC_Sin: 
                    fval = sin(fval * rads_per_degree); 
                    break;

                case MATHFUNC_Tan: 
                    fval = tan(fval * rads_per_degree); 
                    break;

                case MATHFUNC_ArcSin: 
                    fval = asin(fval) * degrees_per_rad; 
                    break;

                case MATHFUNC_ArcCos: 
                    fval = acos(fval) * degrees_per_rad; 
                    break;

                case MATHFUNC_ArcTan: 
                    fval = atan(fval) * degrees_per_rad; 
                    break;

                case MATHFUNC_RadSin: 
                    fval = sin(fval); 
                    break;

                case MATHFUNC_RadCos: 
                    fval = cos(fval); 
                    break;

                case MATHFUNC_RadTan: 
                    fval = tan(fval); 
                    break;

                case MATHFUNC_RadArcSin: 
                    fval = asin(fval); 
                    break;

                case MATHFUNC_RadArcCos: 
                    fval = acos(fval); 
                    break;

                case MATHFUNC_RadArcTan: 
                    fval = atan(fval); 
                    break;

                case MATHFUNC_SquareRoot: 
                    errchk(fval = sqrt(fval)); 
                    break;

                case MATHFUNC_Exp: 
                    errchk(fval = exp(fval)); 
                    break;

                case MATHFUNC_Log10: 
                    errchk(fval = log10(fval)); 
                    break;

                case MATHFUNC_Ln: 
                    errchk(fval = log(fval));
                    break;

                case MATHFUNC_Round:
                    fval += (fval < 0 ? -0.5 : 0.5);
                    // FALLTHROUGH
                case MATHFUNC_Integer:
                    if (fval > (FLONUM) MAXINT || fval < -(FLONUM) MAXINT)
                    {
                        handle_oflo(sig_arg);
                    }

                    signal(SIGFPE, handle_oflo);
                    ival = (FIXNUM) fval;
                    imode = true;
                    signal(SIGFPE, SIG_DFL);
                    break;

                default: 
                    // NOTE: several functions are missing because
                    // they just output whatever the first input is
                    // when there is only one input.
                    break;
                }
            }
            else
            {
                /* overflow */
                if (fcn == MATHFUNC_Round || fcn == MATHFUNC_Integer)
                {
                    if (fval < 0.0)
                    {
                        fval = ceil(fval);
                    }
                    else
                    {
                        fval = floor(fval);
                    }
                }
                else
                {
                    err_logo(BAD_DATA_UNREC, arg);
                }
            }
        }
        // end float case
    }
    else
    {
        // more than one input was given
        bool wantint = false;
        while (args != NIL && NOT_THROWING)
        {
            arg = get_arg_for_function(args, fcn);

            args = cdr(args);
            if (stopping_flag == THROWING) 
            {
                return Unbound;
            }

            FIXNUM iarg;
            FLONUM farg;
            if (nodetype(arg) == INTEGER)
            {
                if (imode)
                {
                    iarg = getint(arg);
                }
                else 
                {
                    farg = (FLONUM) getint(arg);
                }
            }
            else
            {
                if (imode)
                {
                    fval = (FLONUM) ival;
                    imode = false;
                }
                farg = getfloat(arg);
            }

            if (imode)
            {
                FIXNUM oval = ival;

                signal(SIGFPE, handle_oflo);
                if (setjmp(oflo_buf) == 0)
                {
                    switch (fcn)
                    {
                    case MATHFUNC_Difference: 
                        iarg = -iarg;
                        // FALLTHROUGH
                    case MATHFUNC_Sum:
                        if (iarg < 0)
                        {
                            FIXNUM nval = ival + iarg;
                            if (nval >= ival)
                            {
                                imode = false;
                                fcn   = MATHFUNC_Sum;
                                fval  = (FLONUM) ival;
                                farg  = (FLONUM) iarg;
                                // handle_oflo(sig_arg);
                            }
                            else
                            {
                                ival = nval;
                            }
                        }
                        else
                        {
                            FIXNUM nval = ival + iarg;
                            if (nval < ival)
                            {
                                imode = false;
                                fcn   = MATHFUNC_Sum;
                                fval  = (FLONUM) ival;
                                farg  = (FLONUM) iarg;
                                // handle_oflo(sig_arg);
                            }
                            else
                            {
                                ival = nval;
                            }
                        }
                        break;

                    case MATHFUNC_Quotient:
                        if (iarg == 0)
                        {
                            err_logo(BAD_DATA_UNREC, arg);
                        }
                        else
                        {
                            if (ival % iarg != 0)
                            {
                                imode = false;
                                fval = (FLONUM) ival;
                                farg = (FLONUM) iarg;
                            }
                            else
                            {
                                ival /= iarg;
                            }
                        }
                        break;

                    case MATHFUNC_Remainder:
                        if (iarg == 0)
                        {
                            err_logo(BAD_DATA_UNREC, arg);
                        }
                        else
                        {
                            ival %= iarg;
                        }
                        break;

                    case MATHFUNC_Modulo:
                        if (iarg == 0)
                        {
                            err_logo(BAD_DATA_UNREC, arg);
                        }
                        else
                        {
                            ival %= iarg;
                            if ((ival < 0) != (iarg < 0))
                            {
                                ival += iarg;
                            }
                        }
                        break;

                    case MATHFUNC_BitAnd: 
                        ival &= iarg; 
                        break;

                    case MATHFUNC_BitOr:
                        ival |= iarg; 
                        break;

                    case MATHFUNC_BitXor: 
                        ival ^= iarg; 
                        break;

                    case MATHFUNC_BitAShift:
                    case MATHFUNC_BitLShift:
                        if (iarg < 0)
                        {
                            if (fcn == MATHFUNC_BitAShift)
                            {
                                ival >>= -iarg;
                            }
                            else
                            {
                                ival = (unsigned) ival >> -iarg;
                            }
                        }
                        else
                        {
                            ival <<= iarg;
                        }
                        break;

                    case MATHFUNC_Product:
                        if (ival < SAFEINT && ival > -SAFEINT &&
                            iarg < SAFEINT && iarg > -SAFEINT)
                        {
                            ival *= iarg;
                            break;
                        }
                        wantint = true;

                    default:                // math library
                        imode = false;
                        fval = (FLONUM) ival;
                        farg = (FLONUM) iarg;
                    }
                }
                else
                {
                    // integer overflow detected
                    imode = false;
                    fval = (FLONUM) oval;
                    farg = (FLONUM) iarg;
                }
                signal(SIGFPE, SIG_DFL);
            }

            if (!imode)
            {
                signal(SIGFPE, handle_oflo);
                if (setjmp(oflo_buf) == 0)
                {
                    switch (fcn)
                    {
                    case MATHFUNC_Sum: 
                        fval += farg; 
                        break;

                    case MATHFUNC_Difference: 
                        fval -= farg; 
                        break;

                    case MATHFUNC_Product:
                        fval *= farg;

                        if (wantint)
                        {
                            wantint = false;
                            if (fval <= MAXINT && fval >= -MAXINT)
                            {
                                imode = true;
                                ival = fval;
                            }
                        }
                        break;

                    case MATHFUNC_Quotient:
                        if (farg == 0.0)
                        {
                            err_logo(BAD_DATA_UNREC, arg);
                        }
                        else
                        {
                            fval /= farg;
                        }
                        break;

                    case MATHFUNC_ArcTan:
                        errchk(fval = atan2(farg, fval) * degrees_per_rad);
                        break;

                    case MATHFUNC_RadArcTan:
                        errchk(fval = atan2(farg, fval));
                        break;

                    case MATHFUNC_Power:
                        errchk(fval = pow(fval, farg));
                        break;

                    default:  // logical op
                        if (nodetype(arg) == INTEGER)
                        {
                            err_logo(BAD_DATA_UNREC, make_floatnode(fval));
                        }
                        else
                        {
                            err_logo(BAD_DATA_UNREC, arg);
                        }
                        break;
                    }
                }
                else
                {
                    /* floating overflow detected */
                    err_logo(BAD_DATA_UNREC, arg);
                }
                signal(SIGFPE, SIG_DFL);
            }
            // end floating point
        }
        // end dyadic
    }

    if (NOT_THROWING)
    {
        NODE * val;

        if (imode)
        {
            val = make_intnode(ival);
        }
        else
        {
            if (_isnan(fval))
            {
                val = make_floatnode(0.0);
            }
            else
            {
                val = make_floatnode(fval);
            }
        }
        return val;
    }
    return Unbound;
}

NODE *ladd(NODE *args)
{
    if (args == NIL) 
    {
        return make_intnode(0);
    }
    return binary(args, MATHFUNC_Sum);
}

NODE *lsub(NODE *args)
{
    return binary(args, MATHFUNC_Difference);
}

NODE *lmul(NODE *args)
{
    if (args == NIL) 
    {
        return make_intnode(1);
    }
    return binary(args, MATHFUNC_Product);
}

NODE *ldivide(NODE *args)
{
    return binary(args, MATHFUNC_Quotient);
}

NODE *lremainder(NODE *args)
{
    return binary(args, MATHFUNC_Remainder);
}

NODE *lmodulo(NODE *args)
{
    return binary(args, MATHFUNC_Modulo);
}

NODE *lbitand(NODE *args)
{
    if (args == NIL) 
    {
        return make_intnode(-1);
    }
    return binary(args, MATHFUNC_BitAnd);
}

NODE *lbitor(NODE *args)
{
    if (args == NIL) 
    {
        return make_intnode(0);
    }
    return binary(args, MATHFUNC_BitOr);
}

NODE *lbitxor(NODE *args)
{
    if (args == NIL) 
    {
        return make_intnode(0);
    }
    return binary(args, MATHFUNC_BitXor);
}

NODE *lashift(NODE *args)
{
    return binary(args, MATHFUNC_BitAShift);
}

NODE *llshift(NODE *args)
{
    return binary(args, MATHFUNC_BitLShift);
}

NODE *lbitnot(NODE *args)
{
    return binary(args, MATHFUNC_BitNot);
}

NODE *lsin(NODE *args)
{
    return binary(args, MATHFUNC_Sin);
}

NODE *lcos(NODE *args)
{
    return binary(args, MATHFUNC_Cos);
}

NODE *ltan(NODE *args)
{
    return binary(args, MATHFUNC_Tan);
}

NODE *lasin(NODE *args)
{
    return binary(args, MATHFUNC_ArcSin);
}

NODE *lacos(NODE *args)
{
    return binary(args, MATHFUNC_ArcCos);
}

NODE *latan(NODE *args)
{
    return binary(args, MATHFUNC_ArcTan);
}

NODE *lradsin(NODE *args)
{
    return binary(args, MATHFUNC_RadSin);
}

NODE *lradcos(NODE *args)
{
    return binary(args, MATHFUNC_RadCos);
}

NODE *lradtan(NODE *args)
{
    return binary(args, MATHFUNC_RadTan);
}

NODE *lradasin(NODE *args)
{
    return binary(args, MATHFUNC_RadArcSin);
}

NODE *lradacos(NODE *args)
{
    return binary(args, MATHFUNC_RadArcCos);
}

NODE *lradatan(NODE *args)
{
    return binary(args, MATHFUNC_RadArcTan);
}

NODE *lsqrt(NODE *args)
{
    return binary(args, MATHFUNC_SquareRoot);
}

NODE *linteg(NODE *args)
{
    return binary(args, MATHFUNC_Integer);
}

NODE *lround(NODE *args)
{
    return binary(args, MATHFUNC_Round);
}

NODE *lexp(NODE *args)
{
    return binary(args, MATHFUNC_Exp);
}

NODE *llog10(NODE *args)
{
    return binary(args, MATHFUNC_Log10);
}

NODE *lln(NODE *args)
{
    return binary(args, MATHFUNC_Ln);
}

NODE *lpower(NODE *args)
{
    return binary(args, MATHFUNC_Power);
}

static
int compare_flonums(FLONUM n1, FLONUM n2)
{
    // we can't use "fabs(n1 - n2) < DBL_EPSILON" to determine
    // equality because DBL_EPSILON is too large and doing so
    // would make statements like 1-e16 > 0 false.
    // Instead we shift the burden of proper floating point
    // comparisons to the Logo programmer.
    if (n1 == n2)
    {
        return 0;
    }
    else if (n1 < n2)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}


static
int compare_numnodes(NODE *n1, NODE *n2)
{
    if (nodetype(n1) == INTEGER)
    {
        if (nodetype(n2) == INTEGER)
        {
            return getint(n1) - getint(n2);
        }
        else
        {
            return compare_flonums(getint(n1), getfloat(n2));
        }
    }
    else
    {
        if (nodetype(n2) == INTEGER)
        {
            return compare_flonums(getfloat(n1), getint(n2));
        }
        else
        {
            return compare_flonums(getfloat(n1), getfloat(n2));
        }
    }
}

NODE *true_or_false(bool tf)
{
    return tf ? Truex.GetNode() : Falsex.GetNode();
}

NODE *llessp(NODE *args)
{
    NODE * n1 = numeric_arg(args);
    NODE * n2 = numeric_arg(cdr(args));

    if (NOT_THROWING)
    {
        return true_or_false(compare_numnodes(n1, n2) < 0);
    }
    return Unbound;
}

NODE *llessequalp(NODE *args)
{

    NODE * n1 = numeric_arg(args);
    NODE * n2 = numeric_arg(cdr(args));

    if (NOT_THROWING) 
    {
        return true_or_false(compare_numnodes(n1, n2) <= 0);
    }
    return Unbound;
}

NODE *lgreaterp(NODE *args)
{
    NODE * n1 = numeric_arg(args);
    NODE * n2 = numeric_arg(cdr(args));

    if (NOT_THROWING)
    {
        return true_or_false(compare_numnodes(n1, n2) > 0);
    }
    return Unbound;
}

NODE *lgreaterequalp(NODE *args)
{
    NODE * n1 = numeric_arg(args);
    NODE * n2 = numeric_arg(cdr(args));

    if (NOT_THROWING)
    {
        return true_or_false(compare_numnodes(n1, n2) >= 0);
    }
    return Unbound;
}


/* CONSIDER for SPEED:
   Many calls to this function are just to see if a node is "True.
   We could write a special-case function for this.
*/
int compare_node(NODE *n1, NODE *n2, bool ignorecase)
{
    int icmp;

    if (n1 == n2)
    {
        return 0; // equal
    }

    NODETYPES nt1 = nodetype(n1);
    NODETYPES nt2 = nodetype(n2);

    if (!(nt1 & NT_WORD) || !(nt2 & NT_WORD)) 
    {
        return -9999;
    }

    if (nt1 == CASEOBJ && 
        nt2 == CASEOBJ && 
        ignorecase &&
        (object__caseobj(n1) == object__caseobj(n2)))
    {
        return 0;
    }

    if ((nt1 & NT_NUMBER) && (nt2 & NT_NUMBER))
    {
        return compare_numnodes(n1, n2);
    }

    if (nt1 & NT_NUMBER)
    {
        NODE * nn2 = cnv_node_to_numnode(n2);
        if (nn2 != Unbound)
        {
            icmp = compare_numnodes(n1, nn2);
            gcref(nn2);
            return icmp;
        }
    }

    if (nt2 & NT_NUMBER)
    {
        NODE * nn1 = cnv_node_to_numnode(n1);
        if (nn1 != Unbound)
        {
            icmp = compare_numnodes(nn1, n2);
            gcref(nn1);
            return icmp;
        }
    }

    NODE * a1 = cnv_node_to_strnode(n1);
    NODE * a2 = cnv_node_to_strnode(n2);
    nt1 = nodetype(a1);
    nt2 = nodetype(a2);
    if (nt1 == STRING && nt2 == STRING)
    {
        if ((getstrlen(a1) == getstrlen(a2)) &&
            (getstrptr(a1) == getstrptr(a2)))
        {
            icmp = 0;
        }
        else
        {
            int cmp_len = (getstrlen(a1) > getstrlen(a2)) ?
                getstrlen(a2) : getstrlen(a1);

            if (ignorecase)
            {
                icmp = low_strncmp(getstrptr(a1), getstrptr(a2), cmp_len);
            }
            else
            {
                icmp = strncmp(getstrptr(a1), getstrptr(a2), cmp_len);
            }

            if ((getstrlen(a1) != getstrlen(a2)) && icmp == 0)
            {
                icmp = getstrlen(a1) - getstrlen(a2);
            }
        }
    }
    else if (nt1 & NT_BACKSL || nt2 & NT_BACKSL)
    {
        if ((getstrlen(a1) == getstrlen(a2)) &&
            (getstrptr(a1) == getstrptr(a2)))
        {
            icmp = 0;
        }
        else
        {
            int cmp_len = (getstrlen(a1) > getstrlen(a2)) ?
                getstrlen(a2) : getstrlen(a1);

            if (ignorecase)
            {
                icmp = noparitylow_strncmp(getstrptr(a1), getstrptr(a2), cmp_len);
            }
            else
            {
                icmp = noparity_strncmp(getstrptr(a1), getstrptr(a2), cmp_len);
            }

            if ((getstrlen(a1) != getstrlen(a2)) && icmp == 0)
            {
                icmp = getstrlen(a1) - getstrlen(a2);
            }
        }
    }
    else
    {
        err_logo(FATAL, NIL);
    }

    if (a1 != n1) 
    {
        gcref(a1);
    }

    if (a2 != n2) 
    {
        gcref(a2);
    }

    return icmp;
}

bool equalp_help(NODE *arg1, NODE *arg2, bool ignorecase)
{
    if (is_list(arg1))
    {
        if (!is_list(arg2)) 
        {
            return false;
        }

        while (arg1 != NIL && arg2 != NIL)
        {
            if (!equalp_help(car(arg1), car(arg2), ignorecase))
            {
                return false;
            }
            arg1 = cdr(arg1);
            arg2 = cdr(arg2);
            if (check_throwing)
            {
                break;
            }
        }
        return arg1 == NIL && arg2 == NIL;
    }
    else if (is_list(arg2))
    {
        return false;
    }
    else if (nodetype(arg1) == ARRAY)
    {
        if (nodetype(arg2) != ARRAY)
        {
            return false;
        }
        return arg1 == arg2;
    }
    else if (nodetype(arg2) == ARRAY)
    {
        return false;
    }
    else
    {
        return 0 == compare_node(arg1, arg2, ignorecase);
    }
}

NODE *lequalp(NODE *args)
{
    NODE * arg1 = car(args);
    NODE * arg2 = cadr(args);

    bool caseig = variableIsTrue(Caseignoredp);
    bool val = equalp_help(arg1, arg2, caseig);

    return true_or_false(val);
}

NODE *lnotequalp(NODE *args)
{
    NODE * arg1 = car(args);
    NODE * arg2 = cadr(args);

    bool caseig = variableIsTrue(Caseignoredp);
    bool val = equalp_help(arg1, arg2, caseig);

    return true_or_false(!val);
}

NODE *l_eq(NODE *args)
{
    return true_or_false(car(args) == cadr(args));
}

NODE *lbeforep(NODE *args)
{
    NODE * arg1 = string_arg(args);
    NODE * arg2 = string_arg(cdr(args));

    bool caseig = variableIsTrue(Caseignoredp);
    int  val    = compare_node(arg1, arg2, caseig);

    return true_or_false(val < 0);
}
