/*
*      mem.c           logo memory management module           dvb 6/28/88
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

// a segment is a pool of nodes that is allocated in a single malloc.
struct segment
   {
   struct segment * next;
   struct logo_node nodes[SEG_SIZE];
   };

NODE **gcstack;
NODE **gctop;

static NODE    *free_list    = NIL;    // global ptr to free node list
static segment *segment_list = NULL;   // global ptr to segment list

static long int mem_nodes = 0;
static long int mem_max = 0;

static NODE *reserve_tank;

NODETYPES nodetype(const NODE *nd)
   {
   if (nd == NIL) 
      {
      return PNIL;
      }

   return nd->node_type;
   }

void setobject(NODE *nd, NODE *newobj)
   {
   NODE *oldobj = getobject(nd);
   
   ref(newobj);
   deref(oldobj);

   nd->n_obj = newobj;
   }

void setcar(NODE *nd, NODE *newcar)
   {
   NODE *oldcar = car(nd);

   ref(newcar);
   deref(oldcar);

   nd->n_car = newcar;
   }

void setcdr(NODE *nd, NODE *newcdr)
   {
   NODE *oldcdr = cdr(nd);

   ref(newcdr);
   deref(oldcdr);

   nd->n_cdr = newcdr;
   }

NODE *reref(NODE *oldval, NODE *newval)
   {
   // reference newval
   ref(newval);

   // dereference proc_var
   deref(oldval);

   return newval;
   }

NODE *unref(NODE *ret_var)
   {
   if (ret_var != NIL) 
      {
      decrefcnt(ret_var);
      }
   return ret_var;
   }

static
void addseg()
   {
#ifdef MEM_DEBUG
   // allocate the nodes one at a time
   NODE* new_node = (NODE*) malloc(sizeof(*new_node));
   if (new_node != NULL)
      {
      memcpy(&new_node->magic, "NODE", 4);
      settype(new_node, NT_FREE);
      new_node->n_cdr = free_list;
      free_list = new_node;
      }
#else

   // Allocate a large block of nodes at one time
   // and link them into the free_list.
   memory_count++;
   if (status_flag) update_status_memory();

   struct segment *newseg;
   if ((newseg = (segment *) malloc(sizeof(*newseg))) != NULL)
      {
      newseg->next = segment_list;
      segment_list = newseg;
      for (int p = 0; p < SEG_SIZE; p++)
         {
         newseg->nodes[p].n_cdr = free_list;
         free_list = &newseg->nodes[p];
         }
      }
#endif
   }

NODE *newnode(NODETYPES type)
   {
   NODE *newnd;

   // include for debugging leaks
   //    memory_count++;
   //    if (status_flag) update_status_memory();

   if ((newnd = free_list) == NIL)
      {
      addseg();
      if ((newnd = free_list) == NIL)
         {
         err_logo(OUT_OF_MEM, NIL);
         if ((newnd = free_list) == NIL)
            {
            err_logo(OUT_OF_MEM_UNREC, NIL);
            }
         }
      }
   free_list = newnd->n_cdr;
   settype(newnd, type);
   setrefcnt(newnd, 0);
   newnd->n_car = NIL;
   newnd->n_cdr = NIL;
   newnd->n_obj = NIL;
   mem_nodes++;
   if (mem_nodes > mem_max) 
      {
      mem_max = mem_nodes;
      }
   return newnd;
   }

NODE *cons(NODE *x, NODE *y)
   {
   NODE *val = newnode(CONS);

   setcar(val, x);
   setcdr(val, y);
   return val;
   }

void gc(NODE *nd)
   {
   for (;;)
      {
      NODE *tcar;
      NODE *tcdr;
      NODE *tobj;

      int i;
      NODE **pp;

      switch (nodetype(nd))
         {
         case PUNBOUND:
            setrefcnt(nd, 10000);  // save some time
         case PNIL:
            if (gctop == gcstack) 
               {
               // no more nodes to garbage collect
               return;
               }
            // get ready to garbage collect the next node
            nd = *--gctop;
            continue;

         case LINE:
         case CONS:
         case CASEOBJ:
         case RUN_PARSE:
         case QUOTE:
         case COLON:
         case TREE:
         case CONT:
            tcdr = cdr(nd);
            tcar = car(nd);
            tobj = getobject(nd);
            break;

         case ARRAY:
            pp = getarrptr(nd);
            i = getarrdim(nd);
            while (--i >= 0)
               {
               tobj = *pp++;
               deref(tobj);
               }
            free(getarrptr(nd));
            tcar = tcdr = tobj = NIL;
            break;

         case STRING:
         case BACKSLASH_STRING:
         case VBAR_STRING:
            if (getstrhead(nd) != NULL)
               {
               // The string was allocated on the heap 
               // (it's not a string literal).
               // Decrement the reference count and free it, if necessary.
               unsigned short *temp = (unsigned short *) getstrhead(nd);

               assert(*temp != 0); // BUG: the string was already freed
               if (decstrrefcnt(temp) == 0) 
                  {
                  free(getstrhead(nd));
                  }
               }
         default:
            tcar = tcdr = tobj = NIL;
         }

#ifdef MEM_DEBUG
      // The easiest way to debug leaks is to just free the node.
      free(nd);
#else
      // "free" this node by adding it to the free list
      nd->n_cdr = free_list;
      free_list = nd;
#endif

      mem_nodes--;
      if (tcdr != NIL && decrefcnt(tcdr) == 0)
         {
         // push tcdr onto the stack of nodes to
         // be garbage collected.
         if (gctop < &gcstack[GCMAX])
            {
            *gctop++ = tcdr;
            }
         }

      if (tcar != NIL && decrefcnt(tcar) == 0)
         {
         // push tcar onto the stack of nodes to
         // be garbage collected.
         if (gctop < &gcstack[GCMAX])
            {
            *gctop++ = tcar;
            }
         }

      if (tobj != NIL && decrefcnt(tobj) == 0)
         {
         // push tobj onto the garbage-collection stack
         // to be garbage collected in due time
         if (gctop < &gcstack[GCMAX])
            {
            *gctop++ = tobj;
            }
         }

      if (gctop == gcstack) 
         {
         // no more nodes to garbage collect
         return;
         }

      // garbage-collect whatever node is at the top of the stack
      nd = *--gctop;
      }
   }

NODE *lnodes(NODE *  /* args */)
   {
   // snapshot of total nodes when this was called
   long int temp_max   = mem_max;
   long int temp_nodes = mem_nodes;

   mem_max = mem_nodes;

   return cons_list(
      make_intnode(temp_nodes),
      make_intnode(temp_max));
   }

void fill_reserve_tank()
   {
   // grow the reserve tank by 50 nodes
   for (int i = 0; i < 50; i++)
      {
      reserve_tank = cons(NIL, reserve_tank);
      }
   }

void use_reserve_tank()
   {
   // release all nodes in the reserve tank
   gcref(reserve_tank);
   reserve_tank = NIL;
   }

void check_reserve_tank()
   {
   if (reserve_tank == NIL) 
      {
      fill_reserve_tank();
      }
   }

void free_segment_list()
   {
   while (segment_list != NULL)
      {
      segment *next_segment = segment_list->next;
      free(segment_list);
      segment_list = next_segment;
      }
   }

