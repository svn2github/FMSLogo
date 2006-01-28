/*
*      math.c          logo math functions module              dvb
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

/* CONSIDER for SIMPLICITY:
  Either document the return value, or return a bool type.
*/
int numberp(NODE *snd)
   {
   int dl, dr;

   if (is_number(snd)) 
      {
      return 1;
      }

   snd = cnv_node_to_strnode(snd);
   if (snd == Unbound) 
      {
      return 0;
      }

   const char * p = getstrptr(snd); 
   int plen = getstrlen(snd); 
   int pcnt = dl = dr = 0;
   if (plen >= MAX_NUMBER)
      {
      return 0;
      }

   if (pcnt < plen && *p == '-')
      p++, pcnt++;

   while (pcnt < plen && isdigit(*p))
      p++, pcnt++, dl++;

   if (pcnt < plen && *p == '.')
      {
      p++, pcnt++;
      while (pcnt < plen && isdigit(*p))
         p++, pcnt++, dr++;
      }

   if (pcnt < plen && (dl || dr) && (*p == 'E' || *p == 'e'))
      {
      p++, pcnt++;

      if (pcnt < plen && *p == '+' || *p == '-')
         p++, pcnt++;

      while (pcnt < plen && isdigit(*p))
         p++, pcnt++, dr++;
      }

   if ((dl == 0 && dr == 0) || pcnt != plen)
      return 0;
   else
      return dr + 1;
   }

NODE *lrandom(NODE *arg)
   {
   NODE *val;
   long r;

   val = pos_int_arg(arg);
   if (NOT_THROWING)
      {
#ifdef bsd
      r = (getint(val) == 0 ? 0 : random() % getint(val));
#else
      //      r = (getint(val) == 0 ? 0 : rand() % getint(val));
      r = (((long) rand()) << 15) | rand();
      r = (getint(val) == 0 ? 0 : r % getint(val));
#endif
      val = newnode(INT);
      setint(val, (FIXNUM) r);
      return (val);
      }
   else return Unbound;
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

jmp_buf oflo_buf;

#define sig_arg 0
static
void handle_oflo(int /*sig*/)
   {
   _fpreset();
   longjmp(oflo_buf, 1);
   }

//#define errchk(x) x
#define errchk(x) { errno = 0; x; if (errno) err_logo(BAD_DATA_UNREC,arg); }/*ignore*/

static
NODE *binary(NODE *args, char fcn)
   {
   NODE *arg, *val;
   bool imode;
   FIXNUM iarg, ival, oval, nval;
   FLONUM farg, fval;
   int wantint = 0;

   if (fcn == '%' || fcn == 'm')
      arg = integer_arg(args);
   else
      arg = numeric_arg(args);

   //   arg = numeric_arg(args);
   args = cdr(args);
   if (stopping_flag == THROWING) return Unbound;
   if (nodetype(arg) == INT)
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
      /* one argument supplied */
      if (imode)
         switch (fcn)
            {
            case '-': ival = -ival; break;
            case '~': ival = ~ival; break;
            case 'v':
            case 'w':
            case 'x':
            case 'V':
            case 'W':
            case 'X':
            case 's':
            case 'c':
            case 't':
            case 'S':
            case 'C':
            case 'T':
            case 'q':
            case 'e':
            case 'g':
            case 'n':
            case '/':
               imode = false;
               fval = (FLONUM) ival;
               break;
            }
      if (!imode)
         {
         if (!setjmp(oflo_buf))
            {
            switch (fcn)
               {
               case '-': fval = -fval; break;
               case '/':
                  if (fval == 0.0)
                     err_logo(BAD_DATA_UNREC, arg);
                  else
                     fval = 1 / fval;
                  break;
               case '~': err_logo(BAD_DATA_UNREC, arg); break;
               case 'c': fval = cos(fval * rads_per_degree); break;
               case 's': fval = sin(fval * rads_per_degree); break;
               case 't': fval = tan(fval * rads_per_degree); break;
               case 'v': fval = asin(fval) * degrees_per_rad; break;
               case 'w': fval = acos(fval) * degrees_per_rad; break;
               case 'x': fval = atan(fval) * degrees_per_rad; break;
               case 'S': fval = sin(fval); break;
               case 'C': fval = cos(fval); break;
               case 'T': fval = tan(fval); break;
               case 'V': fval = asin(fval); break;
               case 'W': fval = acos(fval); break;
               case 'X': fval = atan(fval); break;
               case 'q': errchk(fval = sqrt(fval)); break;
               case 'e': errchk(fval = exp(fval)); break;
               case 'g': errchk(fval = log10(fval)); break;
               case 'n': errchk(fval = log(fval)); break;
               case 'r':
                  fval += (fval < 0 ? -0.5 : 0.5);
               case 'i':
                  if (fval > (FLONUM) MAXINT || fval < -(FLONUM) MAXINT)
                     handle_oflo(sig_arg);
                  signal(SIGFPE, handle_oflo);
                  ival = (FIXNUM) fval;
                  imode = true;
                  signal(SIGFPE, SIG_DFL);
                  break;
               }
            }
         else
            {
            /* overflow */
            if (fcn == 'r' || fcn == 'i')
               {
               if (fval < 0.0)
                  fval = ceil(fval);
               else
                  fval = floor(fval);
               }
            else
               err_logo(BAD_DATA_UNREC, arg);
            }
         }
      /* end float case */
      }
   /* end monadic */
   while (args != NIL && NOT_THROWING)
      {
      if (fcn == '%' || fcn == 'm')
         arg = integer_arg(args);
      else
         arg = numeric_arg(args);

      //    arg = numeric_arg(args);

      args = cdr(args);
      if (stopping_flag == THROWING) return Unbound;

      if (nodetype(arg) == INT)
         {
         if (imode) iarg = getint(arg);
         else farg = (FLONUM) getint(arg);
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
         oval = ival;

         signal(SIGFPE, handle_oflo);
         if (setjmp(oflo_buf) == 0)
            {
            switch (fcn)
               {
               case '-': iarg = -iarg;
               case '+':
                  if (iarg < 0)
                     {
                     nval = ival + iarg;
                     if (nval >= ival)
                        {
                        imode = false;
                        fcn   = '+';
                        fval  = (FLONUM) ival;
                        farg  = (FLONUM) iarg;
                        //                        handle_oflo(sig_arg);
                        }
                     else ival = nval;
                     }
                  else
                     {
                     nval = ival + iarg;
                     if (nval < ival)
                        {
                        imode = false;
                        fcn   = '+';
                        fval  = (FLONUM) ival;
                        farg  = (FLONUM) iarg;
                        // handle_oflo(sig_arg);
                        }
                     else ival = nval;
                     }
                  break;

               case '/':
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

               case '%':
                  if (iarg == 0)
                     {
                     err_logo(BAD_DATA_UNREC, arg);
                     }
                  else
                     {
                     ival %= iarg;
                     }
                  break;

               case 'm':
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

               case '&': ival &= iarg; break;
               case '|': ival |= iarg; break;
               case '^': ival ^= iarg; break;
               case 'a':
               case 'l':
                  if (iarg < 0)
                     {
                     if (fcn == 'a')
                        ival >>= -iarg;
                     else
                        ival = (unsigned) ival
                           >> -iarg;
                     }
                  else
                     ival <<= iarg;
                  break;

               case '*':
                  if (ival < SAFEINT && ival > -SAFEINT &&
                      iarg < SAFEINT && iarg > -SAFEINT)
                     {
                     ival *= iarg;
                     break;
                     }
                  wantint++;

               default:                /* math library */
                  imode = false;
                  fval = (FLONUM) ival;
                  farg = (FLONUM) iarg;
               }
            }
         else
            {
            /* integer overflow detected */
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
               case '+': fval += farg; break;
               case '-': fval -= farg; break;
               case '*':
                  fval *= farg;

                  if (wantint)
                     {
                     wantint = 0;
                     if (fval <= MAXINT && fval >= -MAXINT)
                        {
                        imode = true;
                        ival = fval;
                        }
                     }

                    break;
               case '/':
                  if (farg == 0.0)
                       err_logo(BAD_DATA_UNREC, arg);
                  else
                     fval /= farg;
                    break;
                case 'x':
                    errchk(fval = atan2(farg, fval) * degrees_per_rad);
                    break;
                case 'X':
                    errchk(fval = atan2(farg, fval));
                    break;
                case 'p':
                    errchk(fval = pow(fval, farg));
                    break;
               default:  // logical op
                  if (nodetype(arg) == INT)
                     err_logo(BAD_DATA_UNREC, make_floatnode(fval));
                  else
                     err_logo(BAD_DATA_UNREC, arg);
               }
            }
         else
            {
            /* floating overflow detected */
            err_logo(BAD_DATA_UNREC, arg);
            }
         signal(SIGFPE, SIG_DFL);
         }
      /* end floating point */
      }
   /* end dyadic */
   if (NOT_THROWING)
      {
      if (imode)
         {
         val = newnode(INT);
         setint(val, ival);
         }
      else
         {
         val = newnode(FLOAT);
         if (_isnan(fval))
            setfloat(val, 0.0);
         else
            setfloat(val, fval);
         }
      return (val);
      }
   return Unbound;
   }

NODE *ladd(NODE *args)
   {
   if (args == NIL) return make_intnode(0);
   return (binary(args, '+'));
   }

NODE *lsub(NODE *args)
   {
   return (binary(args, '-'));
   }

NODE *lmul(NODE *args)
   {
   if (args == NIL) return make_intnode(1);
   return (binary(args, '*'));
   }

NODE *ldivide(NODE *args)
   {
   return (binary(args, '/'));
   }

NODE *lremainder(NODE *args)
   {
   return (binary(args, '%'));
   }

NODE *lmodulo(NODE *args)
   {
   return (binary(args, 'm'));
   }

NODE *lbitand(NODE *args)
   {
   if (args == NIL) return make_intnode(-1);
   return (binary(args, '&'));
   }

NODE *lbitor(NODE *args)
   {
   if (args == NIL) return make_intnode(0);
   return (binary(args, '|'));
   }

NODE *lbitxor(NODE *args)
   {
   if (args == NIL) return make_intnode(0);
   return (binary(args, '^'));
   }

NODE *lashift(NODE *args)
   {
   return (binary(args, 'a'));
   }

NODE *llshift(NODE *args)
   {
   return (binary(args, 'l'));
   }

NODE *lbitnot(NODE *args)
   {
   return (binary(args, '~'));
   }

NODE *lsin(NODE *args)
   {
   return (binary(args, 's'));
   }

NODE *lcos(NODE *args)
   {
   return (binary(args, 'c'));
   }

NODE *ltan(NODE *args)
   {
   return (binary(args, 't'));
   }

NODE *lasin(NODE *args)
   {
   return (binary(args, 'v'));
   }

NODE *lacos(NODE *args)
   {
   return (binary(args, 'w'));
   }

NODE *latan(NODE *args)
   {
   return (binary(args, 'x'));
   }

NODE *lradsin(NODE *args)
   {
   return (binary(args, 'S'));
   }

NODE *lradcos(NODE *args)
   {
   return (binary(args, 'C'));
   }

NODE *lradtan(NODE *args)
   {
   return (binary(args, 'T'));
   }

NODE *lradasin(NODE *args)
   {
   return (binary(args, 'V'));
   }

NODE *lradacos(NODE *args)
   {
   return (binary(args, 'W'));
   }

NODE *lradatan(NODE *args)
   {
   return (binary(args, 'X'));
   }

NODE *lsqrt(NODE *args)
   {
   return (binary(args, 'q'));
   }

NODE *linteg(NODE *args)
   {
   return (binary(args, 'i'));
   }

NODE *lround(NODE *args)
   {
   return (binary(args, 'r'));
   }

NODE *lexp(NODE *args)
   {
   return (binary(args, 'e'));
   }

NODE *llog10(NODE *args)
   {
   return (binary(args, 'g'));
   }

NODE *lln(NODE *args)
   {
   return (binary(args, 'n'));
   }

NODE *lpower(NODE *args)
   {
   return (binary(args, 'p'));
   }

static
int compare_flonums(FLONUM n1, FLONUM n2)
   {
   if (fabs(n1 - n2) < DBL_EPSILON)
      {
      // floats are equal (or close enough to be considered equal)
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
   if (nodetype(n1) == INT)
      {
      if (nodetype(n2) == INT)
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
      if (nodetype(n2) == INT)
         {
         return compare_flonums(getfloat(n1), getint(n2));
         }
      else
         {
         return compare_flonums(getfloat(n1), getfloat(n2));
         }
      }
   }

NODE *torf(bool tf)
   {
   return (tf ? Truex : Falsex);
   }

NODE *llessp(NODE *args)
   {
   NODE * n1 = numeric_arg(args);
   NODE * n2 = numeric_arg(cdr(args));

   if (NOT_THROWING)
      {
      return torf(compare_numnodes(n1, n2) < 0);
      }
   return Unbound;
   }

NODE *lgreaterp(NODE *args)
   {
   NODE * n1 = numeric_arg(args);
   NODE * n2 = numeric_arg(cdr(args));

   if (NOT_THROWING)
      {
      return torf(compare_numnodes(n1, n2) > 0);
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
   NODE *arg1, *arg2;
   bool val;

   arg1 = car(args);
   arg2 = cadr(args);

   if (compare_node(valnode__caseobj(Caseignoredp), Truex, TRUE) == 0)
      val = equalp_help(arg1, arg2, TRUE);
   else
      val = equalp_help(arg1, arg2, FALSE);

   return (torf(val));
   }

NODE *l_eq(NODE *args)
   {
   return torf(car(args) == cadr(args));
   }

NODE *lbeforep(NODE *args)
   {
   NODE *arg1, *arg2;
   int val;

   arg1 = string_arg(args);
   arg2 = string_arg(cdr(args));

   if (compare_node(valnode__caseobj(Caseignoredp), Truex, TRUE) == 0)
      val = compare_node(arg1, arg2, TRUE);
   else
      val = compare_node(arg1, arg2, FALSE);

   return (val < 0 ? Truex : Falsex);
   }

