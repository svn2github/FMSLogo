/*
*      print.c         logo printing module                    dvb
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
*/

#include "allwind.h"

int print_stringlen;
char *print_stringptr;

bool print_backslashes = false;

void update_coords(char /*ch*/)
   {
   }

void print_char(FILE *strm, char ch)
   {
   if (strm)
      {
      if (strm == stdout)
         {
         putcombochar(ch);
         if (dribblestream != NULL)
            putc(ch, dribblestream);
         update_coords(ch);
         }
      else
         {
         putc(ch, strm);
         }
      }
   else
      {
      /* printing to string */
      if (--print_stringlen > 0)
         *print_stringptr++ = ch;
      }
   }

void print_space(FILE *strm)
   {
   print_char(strm, ' ');
   }

/*VARARGS2*/
void ndprintf(FILE *strm, char *fmt, ...)
   {
   va_list ap;
   char ch;

   va_start(ap, fmt);
   while ((ch = *fmt++) != '\0')
      {
      if (ch == '%')
         {
         ch = *fmt++;
         if (ch == 's') // show
            {
            print_node(strm, va_arg(ap, NODE *));
            }
         else if (ch == 'p')  // print
            {
            /* print */
            NODE * nd = va_arg(ap, NODE *);
            if (is_list(nd))
               {
               print_helper(strm, nd);
               }
            else
               print_node(strm, nd);
            }
         else if (ch == 't') // text
            {
            char *cp = va_arg(ap, char *);
            while (ch = *cp++)
               {
               print_char(strm, ch);
               }
            }
         else
            {
            print_char(strm, '%');
            print_char(strm, ch);
            }
         }
      else print_char(strm, ch);
      }
   va_end(ap);
   }

static
void real_print_helper(FILE *strm, NODE *ndlist, int depth, int width)
   {
   int wid = width;

   while (ndlist != NIL)
      {
      if (!is_list(ndlist))
         {
         return;
         }
      NODE * arg = car(ndlist);
      ndlist = cdr(ndlist);
      if (check_throwing)
         {
         break;
         }
      real_print_node(strm, arg, depth, width);
      if (ndlist != NIL)
         {
         print_space(strm);
         if (--wid == 0)
            {
            ndprintf(strm, "...");
            break;
            }
         }
      }
   }


// prints a node to a file stream in a way that is consistent
// with how FMSLogo parses nodes.
//
//   strm - the file stream.
//   nd - the node to print.
//   depth - how "deep" to go (how many elements of a list)
//   width - how many bytes to print at most ???
void real_print_node(FILE *strm, NODE *nd, int depth, int width)
   {
   int i;
   const char *cp;
   NODETYPES ndty;

   if (depth == 0)
      {
      ndprintf(strm, "...");
      return;
      }
   if (nd == NIL)
      {
      print_char(strm, '[');
      print_char(strm, ']');
      }
   else if (nd == Unbound)
      {
      ndprintf(strm, "Unbound");
      }
   else if ((ndty = nodetype(nd)) & NT_PRIM)
      {
      ndprintf(strm, "PRIM");
      }
   else if (ndty & NT_LIST)
      {
      print_char(strm, '[');
      real_print_helper(strm, nd, depth - 1, width);
      print_char(strm, ']');
      }
   else if (ndty == ARRAY)
      {
      int i = 0, dim = getarrdim(nd), wid;
      NODE **pp = getarrptr(nd);

      if (width < 0) wid = dim;
      else wid = (dim > width ? width : dim);
      print_char(strm, '{');
      while (i < wid)
         {
         real_print_node(strm, *pp++, depth - 1, width);
         if (++i < dim) print_space(strm);
         }
      if (wid < dim) ndprintf(strm, "...");
      print_char(strm, '}');
      if (print_backslashes && (getarrorg(nd) != 1))
         {
         char org[] = "@        ";

         sprintf(&org[1], "%d", getarrorg(nd));
         ndprintf(strm, org);
         }
      }
   else if (ndty == QUOTE)
      {
      print_char(strm, '\"');
      real_print_node(strm, car(nd), width - 1, depth);
      }
   else if (ndty == COLON)
      {
      print_char(strm, ':');
      real_print_node(strm, car(nd), width - 1, depth);
      }
   else
      {
      int wid, dots = 0;

      nd = cnv_node_to_strnode(nd);
      cp = getstrptr(nd);
      if (width < 0) wid = getstrlen(nd);
      else
         {
         wid = (width < 10 ? 10 : width);
         wid = (wid < getstrlen(nd) ? wid : getstrlen(nd));
         }
      if (wid < getstrlen(nd)) dots++;

      if (!backslashed(nd))
         for (i = 0; i < wid; i++)
            {
            print_char(strm, *cp++);
            }
      else if (!print_backslashes)
         {
         for (i = 0; i < wid; i++)
            {
            print_char(strm, clearparity(*cp++));
            }
         }
      else
         {
         for (i = 0; i < wid; i++)
            {
            if (getparity(cp[i])) break;
            }
         if (i < wid)
            {
            /* word was in vbars */
            if (strchr("\":", *cp))
               {
               print_char(strm, *cp++);
               wid--;
               }
            print_char(strm, '|');
            for (i = 0; i < wid; i++)
               {
               print_char(strm, clearparity(*cp++));
               }
            print_char(strm, '|');
            }
         else for (i = 0; i < wid; i++)
            {
            if (strchr(special_chars, (int) * cp))
               {
               print_char(strm, '\\');
               }
            print_char(strm, *cp++);
            }
         }
      ;
      if (dots) ndprintf(strm, "...");
      gcref(nd);
      }
   }

static
int find_limit(NODE *nd)
   {
   if (nd == NIL) 
      {
      return -1;
      }

   nd = cnv_node_to_numnode(valnode__caseobj(nd));

   int val = -1;
   if (nodetype(nd) == INTEGER) 
      {
      val = getint(nd);
      }
   gcref(nd);
   return val;
   }

void print_helper(FILE *strm, NODE *nd)
   {
   real_print_helper(
      strm,
      nd,
      find_limit(Printdepthlimit),
      find_limit(Printwidthlimit));
   }

void print_node(FILE *strm, NODE *nd)
   {
   real_print_node(
      strm,
      nd,
      find_limit(Printdepthlimit),
      find_limit(Printwidthlimit));
   }

void print_nobrak(FILE *strm, NODE *nd)
   {
   if (is_list(nd)) print_helper(strm, nd);
   else print_node(strm, nd);
   }

void new_line(FILE *strm)
   {
   print_char(strm, '\n');
   }

NODE *lshow(NODE *args)
   {
   print_helper(writestream, args);
   new_line(writestream);
   return Unbound;
   }

static
void type_helper(NODE *args, bool sp)
   {
   NODE *arg /* = NIL */;

   while (args != NIL)
      {
      arg = car(args);
      args = cdr(args);
      if (is_list(arg))
         print_helper(writestream, arg);
      else
         print_node(writestream, arg);
      if (sp && (args != NIL))
         {
         print_space(writestream);
         }
      }
   }

NODE *ltype(NODE *args)
   {
   type_helper(args, false);
   return Unbound;
   }

NODE *lprint(NODE *args)
   {
   type_helper(args, true);
   new_line(writestream);
   return Unbound;
   }

