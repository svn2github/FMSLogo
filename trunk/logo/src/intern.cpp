/*
*      intern.c        logo data interning module              dvb
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

NODE **hash_table;

static
FIXNUM hash(const char *s, int len)
/* Map S to an integer in the range 0 .. HASH_LEN-1. */
/* Method attributed to Peter Weinberger, adapted from Aho, Sethi, */
/* and Ullman's book, Compilers: Principles, Techniques, and */
/* Tools; figure 7.35. */
   {
   unsigned long h = 0, g;

   while (--len >= 0)
      {
      h = (h << 4) + *s++;
      g = h & (0xf << (WORDSIZE - 4));
      if (g != 0)
         {
         h ^= g ^ (g >> (WORDSIZE - 8));
         }
      }
   return h % HASH_LEN;
   }

NODE *make_case(NODE *casestrnd, NODE *obj)
   {
   NODE * clistptr = caselistptr__object(obj);
   NODE * new_caseobj = make_caseobj(casestrnd, obj);
   setcdr(clistptr, cons(new_caseobj, cdr(clistptr)));
   return new_caseobj;
   }

static
NODE *
make_object(
   NODE *canonical, 
   NODE *proc, 
   NODE *val,
   NODE *plist,
   NODE *casestrnd
)
   {
   NODE * temp = cons_list(
      canonical, 
      proc, 
      val, 
      plist, 
      make_intnode(0));

   make_case(casestrnd, temp);
   return temp;
   }

NODE *make_instance(NODE *casend, NODE *lownd)
   {
   /* Called only if arg isn't already in hash table */
   NODE * obj = make_object(lownd, UNDEFINED, Unbound, NIL, casend);
   FIXNUM hashind = hash(getstrptr(lownd), getstrlen(lownd));
   push(obj, (hash_table[hashind]));
   return car(caselist__object(obj));
   }

static
NODE *find_instance(NODE *lownd)
   {
   NODE * hash_entry = hash_table[hash(getstrptr(lownd), getstrlen(lownd))];
   while (hash_entry != NIL)
      {
      NODE * thisobj = car(hash_entry);
      int cmpresult = compare_node(lownd, canonical__object(thisobj), FALSE);
      if (cmpresult == 0)
         {
         // found it
         return thisobj;
         }
      else
         {
         hash_entry = cdr(hash_entry);
         }
      }

   return NIL;
   }

static
int case_compare(NODE *nd1, NODE *nd2)
   {
   if (backslashed(nd1) && backslashed(nd2))
      {
      if (getstrlen(nd1) != getstrlen(nd2)) 
         {
         return 1;
         }

      return strncmp(getstrptr(nd1), getstrptr(nd2), getstrlen(nd1));
      }

   if (backslashed(nd1) || backslashed(nd2))
      {
      return 1;
      }

   return compare_node(nd1, nd2, FALSE);
   }

static
NODE *find_case(NODE *strnd, NODE *obj)
   {
   NODE * clist = caselist__object(obj);
   while (clist != NIL &&
          case_compare(strnd, strnode__caseobj(car(clist))))
      {
      clist = cdr(clist);
      }

   if (clist == NIL) 
      {
      return NIL;
      }
   else 
      {
      return car(clist);
      }
   }

NODE *intern(NODE *nd)
   {
   if (nodetype(nd) == CASEOBJ) 
      {
      return nd;
      }

   nd = vref(cnv_node_to_strnode(nd));
   NODE * lownd = make_strnode(getstrptr(nd), getstrlen(nd), STRING, noparitylow_strnzcpy);

   NODE * obj;
   NODE * casedes;
   if ((obj = find_instance(lownd)) != NIL)
      {
      if ((casedes = find_case(nd, obj)) == NIL)
         {
         casedes = make_case(nd, obj);
         }
      }
   else
      {
      casedes = make_instance(nd, lownd);
      }
   deref(nd);
   gcref(lownd);
   return casedes;
   }

