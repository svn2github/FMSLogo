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

// hash_table is an array of NODE*.
// Each of the NODE* in the array is a list of "objects" that hashes 
// to that bucket.
// Hashing is always done on the "canonical" version of the node, which is 
// all lowercase.
//
// An "object" is represented as a list.   The format for an object is:
//
// [canonical proc  val  plist  case_node1 case_node2 ... ]
//   canonical        - The canonical representation of the node.
//                      This is an all lower-case form of it.
//                      This is what is printed if you SHOW the node.
//   proc             - For objects that are procedures, this is the
//                      node that represents the procedure definition.
//   val              - For objects that represent variables,
//                      the value of the variable.
//   plist            - A list of properties.
//                      This is used for property lists.
//   case list        - A list of "case objects" for this node.
//                      This list always begins with int:0.
//
// A "case object" is a cons cell
//   car - a case-sensitive string representation of the object.
//   cdr - a reference to the object (see above).
// DC: what are case objects for?
NODE **hash_table;



// Map S to an integer in the range 0 .. HASH_LEN-1.
// Method attributed to Peter Weinberger, adapted from Aho, Sethi,
// and Ullman's book, Compilers: Principles, Techniques, and
// Tools; figure 7.35.
static
FIXNUM hash(const char *s, int len)
   {
   unsigned long h = 0;

   while (--len >= 0)
      {
      h = (h << 4) + *s++;
      unsigned long g = h & (0xf << (WORDSIZE - 4));
      if (g != 0)
         {
         h ^= g ^ (g >> (WORDSIZE - 8));
         }
      }
   return h % HASH_LEN;
   }


// Makes a "case object" and adds it to the "case list" for the interned object.
// adds this "case object" to this hash table entry's case list
static
NODE *make_case(NODE *casestrnd, NODE *object)
   {
   // get a pointer to the "case-list" of the five-tuple list
   NODE * clistptr = caselistptr__object(object);

   // create a new case object for this node
   NODE * new_caseobj = make_caseobj(casestrnd, object);

   // add this case object to the "case-list"
   setcdr(clistptr, cons(new_caseobj, cdr(clistptr)));

   // return the new case object
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

// Adds a node to hash_table based on case_node/lowercase_node.
// This is only called if arg isn't already in hash table 
NODE *make_instance(NODE *case_node, NODE *lowercase_node)
   {
   // create the five-tuple that represents this object
   NODE * obj = make_object(lowercase_node, UNDEFINED, Unbound, NIL, case_node);

   // figure out the hash value for the object
   FIXNUM hashind = hash(getstrptr(lowercase_node), getstrlen(lowercase_node));

   // append the object to the bucket
   push(obj, (hash_table[hashind]));

   // return the first element of the case list
   return car(caselist__object(obj));
   }

// Searches for a new in the hash_table based on lowercase_node value.
// All hashing happens on the lowercase form of a node.
// If found, find_instance() returns the "canonical" object from hash_table.
// Otherwise, returns NIL.
static
NODE *find_instance(NODE *lowercase_node)
   {
   // find the bucket that this node hashes to.
   NODE * hash_entry = hash_table[hash(getstrptr(lowercase_node), getstrlen(lowercase_node))];
   while (hash_entry != NIL)
      {
      // search all entries in this "bucket" using a case-sensitive comparison against
      // the canonical representation (lowercase representation) of the node.
      NODE * thisobj = car(hash_entry);
      int cmpresult = compare_node(lowercase_node, canonical__object(thisobj), false);
      if (cmpresult == 0)
         {
         // found it
         return thisobj;
         }

      // keep looking
      hash_entry = cdr(hash_entry);
      }

   return NIL;
   }

// Compares two nodes in a case-sensitive manner.
// Returns 0 if nd1 == nd2.
// Returns non-zero, otherwise.
static
int case_compare(NODE *nd1, NODE *nd2)
   {
   if (backslashed(nd1) && backslashed(nd2))
      {
      // both are blackslashed.
      if (getstrlen(nd1) != getstrlen(nd2)) 
         {
         // different lengths, so they are different.
         return 1;
         }

      // Do a regular string comparison
      return strncmp(getstrptr(nd1), getstrptr(nd2), getstrlen(nd1));
      }

   if (backslashed(nd1) || backslashed(nd2))
      {
      // one is backslashed and the other isn't.
      // They are definately different.
      return 1;
      }

   // Do a case-sensitive node comparison
   return compare_node(nd1, nd2, false);
   }

// Finds the NODE* from obj's case list that matches strnd 
// with a case-sensitive comparsion.
//
// The return value is not referenced.
static
NODE *find_case(NODE *strnd, NODE *obj)
   {
   // iterate over each element in the case list
   for (NODE * clist = caselist__object(obj);
        clist != NIL;
        clist = cdr(clist))
      {
      NODE* this_case = car(clist);
      if (0 == case_compare(strnd, strnode__caseobj(this_case)))
         {
         // found it
         return this_case;
         }
      }

   // didn't find one
   return NIL;
   }

// Returns a "case node" that matches the input node from the 
// "object" represented by the input node.
// If no "object" existed for the node, then one is created.
// If no "case node" matching the input node existed, then one is created.
//
// The returned object is NOT referenced.
NODE *intern(NODE *nd)
   {
   if (nodetype(nd) == CASEOBJ) 
      {
      return nd;
      }

   nd = vref(cnv_node_to_strnode(nd));

   // CONSIDER for SPEED/SPACE: we can just use nd if it is
   // already a lower-case node.
   NODE * lowercase_node = make_strnode(
      getstrptr(nd), 
      getstrlen(nd), 
      STRING, 
      noparitylow_strnzcpy);

   NODE * obj;
   NODE * casedes;
   if ((obj = find_instance(lowercase_node)) != NIL)
      {
      // This object has already been interned.

      // look for a node in the case list that matches
      if ((casedes = find_case(nd, obj)) == NIL)
         {
         // none exists, so add one
         casedes = make_case(nd, obj);
         }
      }
   else
      {
      // This node was not found in the hash table.
      // Add it.
      casedes = make_instance(nd, lowercase_node);
      }

   deref(nd);
   gcref(lowercase_node);
   return casedes;
   }


void release_all_objects()
   {
   for (int i = 0; i < HASH_LEN; i++)
      {
      for (NODE * hash_entry = hash_table[i];
           hash_entry != NIL;
           hash_entry = cdr(hash_entry))
         {
         NODE * object = car(hash_entry);

         // overwrite the "canonical" node with NIL to 
         // force garbage collection
         setcar(object, NIL);

         // overwrite the "proc node" with NIL to 
         // force garbage collection
         setprocnode__object(object, NIL);

         // overwrite the "value" with NIL to 
         // force garbage collection
         setvalnode__object(object, NIL);

         // overwrite the "propery list" with NIL to
         // force garbage collection
         setplist__object(object, NIL);

         // overwrite the "case-list" with NIL to
         // force garbage collection
         setcdr(caselistptr__object(object), NIL);

         // overwrite the "object" node with NIL to 
         // force garbage collection.
         setcar(hash_entry, NIL);
         }
      deref(hash_table[i]);
      hash_table[i] = NIL;
      }
   }
