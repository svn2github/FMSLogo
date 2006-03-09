/*
*      paren.c              logo parenthesizing module          dko
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

#define assign(to, from)    to = reref(to, from)

NODE *the_generation;
bool tree_dk_how;

static NODE *gather_args(NODE *proc, NODE **args, bool inparen, NODE **ifnode);
static NODE *paren_infix(NODE *left_arg, NODE **rest, int old_pri, bool inparen);

// Set the line pointer for a tree.
static
void make_line(NODE *tree, NODE *line)
   {
   setobject(tree, line); //BH
   //setobject(tree, NIL);
   //tree->n_obj = line;
   settype(tree, LINE);
   }

static
void untreeify(NODE *node)
   {
   settreepair__tree(node, NIL);
   settype(node, CONS);
   }

static
void untreeify_line(NODE *line)
   {
   if (line != NIL && is_list(line))
      {
      untreeify_line(car(line));
      untreeify_line(cdr(line));
      untreeify(line);
      }
   }

void untreeify_proc(NODE *procname)
   {

   NODE *body = bodylist__procnode(procnode__caseobj(procname));

   for (NODE * body_ptr = body; body_ptr != NIL; body_ptr = cdr(body_ptr))
      {
      untreeify_line(car(body_ptr));
      }
   untreeify(body);
   }

// Treeify a body by appending the trees of the lines.
void make_tree_from_body(NODE *body)
   {
   if (body == NIL ||
         (is_tree(body) && generation__tree(body) == the_generation))
      {
      return;
      }

   NODE *end_ptr = NIL;
   for (NODE * body_ptr = body; body_ptr != NIL; body_ptr = cdr(body_ptr))
      {
      NODE * tree = car(body_ptr);
      assign(this_line, tree);
      make_tree(tree);
      if (is_tree(tree))
         {
         tree = tree__tree(tree);
         make_line(tree, car(body_ptr));
         if (end_ptr == NIL)
            {
            settree__tree(body, tree);
            }
         else
            {
            setcdr(end_ptr, tree);
            }
         if (generation__tree(car(body_ptr)) == Unbound)
            {
            setgeneration__tree(body, Unbound);
            }
         untreeify(car(body_ptr));
         while (cdr(tree) != NIL)
            {
            tree = cdr(tree);
            }
         end_ptr = tree;
         }
      else
         {
         /* error while treeifying */
         untreeify(body);
         return;
         }
      }
   settype(body, TREE);
   }


// Parenthesize an expression. 
// Set expr to the node after the first full expression.
static
NODE *paren_expr(NODE **expr, bool inparen)
   {

   if (*expr == NIL)
      {
      if (inparen) 
         {
         err_logo(PAREN_MISMATCH, NIL);
         }
      return *expr;
      }

   NODE *tree = NIL;
   NODE *proc;
   NODE *retval;
   NODE **ifnode = (NODE **) NIL;

   NODE * first = vref(car(*expr));
   pop(*expr);
   if (nodetype(first) == CASEOBJ && !numberp(first))
      {
      if (first == Left_Paren)
         {
         deref(first);
         tree = paren_expr(expr, TRUE);
         tree = paren_infix(tree, expr, -1, TRUE);
         if (*expr == NIL)
            {
            err_logo(PAREN_MISMATCH, NIL);
            }
         else if (car(*expr) != Right_Paren)
            {
            // throw the rest away
            err_logo(TOO_MUCH, NIL);
            for (int parens = 0; *expr; pop(*expr))
               {
               if (car(*expr) == Left_Paren)
                  {
                  parens++;
                  }
               else if (car(*expr) == Right_Paren)
                  {
                  if (parens-- == 0) 
                     {
                     break;
                     }
                  }
               }
            }
         else
            {
            pop(*expr);
            }
         retval = tree;
         }
      else if (first == Right_Paren)
         {
         deref(first);
         err_logo(UNEXPECTED_PAREN, NIL);
         if (inparen) 
            {
            push(first, *expr);
            }
         retval = NIL;
         }
      else if (first == Minus_Sign)
         {
         deref(first);
         push(Minus_Tight, *expr);
         retval = paren_infix(make_intnode(0), expr, -1, inparen);
         }
      else
         {
         /* it must be a procedure */
         if (procnode__caseobj(first) == UNDEFINED && 
             NOT_THROWING &&
             first != Null_Word)
            {
            silent_load(first, NULL);  // try ./<first>.lgo
            }
         if (procnode__caseobj(first) == UNDEFINED && 
             NOT_THROWING &&
             first != Null_Word)
            {
            silent_load(first, logolib); // try <logolib>/<first>
            }
         proc = procnode__caseobj(first);
         if (proc == UNDEFINED && NOT_THROWING)
            {
            retval = cons(first, NIL);
            tree_dk_how = TRUE;
            }
         else
            {
            if (first == If)
               {
               // Kludge: turn IF to IFELSE sometimes.
               ifnode = &first;
               }
            retval = gather_args(proc, expr, inparen, ifnode);
            if (retval != Unbound)
               {
               retval = cons(first, retval);
               }
            }
         deref(first);
         }
      }
   else if (is_list(first))
      {
      /* quoted list */
      retval = make_quote(first);
      deref(first);
      }
   else
      {
      unref(first);
      return first;
      }
   return retval;
   }

// Fully parenthesize a complete line.
// i.e. transform it from a flat list to a tree.
static
NODE *paren_line(NODE *line)
   {
   if (line == NIL) 
      {
      return NIL;
      }

   NODE * retval = paren_expr(&line, FALSE);
   if (NOT_THROWING && retval != Unbound)
      {
      retval = paren_infix(retval, &line, -1, FALSE);
      retval = cons(retval, paren_line(line));
      }
   return retval;
   }


// Make a list of the next n expressions, where n is between min and max.
// Set args to immediately after the last expression.
NODE *gather_some_args(int min, int max, NODE **args, bool inparen, NODE **ifnode)
   {
   if (*args == NIL || car(*args) == Right_Paren ||
       (nodetype(car(*args)) == CASEOBJ &&
        nodetype(procnode__caseobj(car(*args))) == INFIX))
      {
      if (min > 0)
         {
         return cons_list(Not_Enough_Node);
         }
      }
   else if (max == 0)
      {
      if (ifnode != (NODE **) NIL && is_list(car(*args)))
         {
         /* if -> ifelse kludge */
         NODE *retval;
         err_logo(IF_WARNING, NIL);
         assign(*ifnode, Ifelse);
         retval = paren_expr(args, FALSE);
         retval = paren_infix(retval, args, -1, inparen);
         return cons(
            retval, 
            gather_some_args(min, max, args, inparen, NULL));
         }
      }
   else
      {
      if (max < 0) 
         { 
         // negative max means unlimited 
         max = 0;
         }

      if (car(*args) != Right_Paren &&
            (nodetype(car(*args)) != CASEOBJ ||
               nodetype(procnode__caseobj(car(*args))) != INFIX))
         {
         NODE *retval = paren_expr(args, FALSE);
         retval = paren_infix(retval, args, -1, inparen);
         return cons(
            retval, 
            gather_some_args(min - 1, max - 1, args, inparen, ifnode));
         }
      }
   return NIL;
   }

// Gather the correct number of arguments to proc into a list.
// Set args to immediately after the last arg.
static
NODE *gather_args(NODE *proc, NODE **args, bool inparen, NODE **ifnode)
   {
   int min, max;

   if (nodetype(proc) == CONS)
      {
      min = (inparen ? getint(minargs__procnode(proc))
            : getint(dfltargs__procnode(proc)));
      max = (inparen ? getint(maxargs__procnode(proc))
            : getint(dfltargs__procnode(proc)));
      }
   else
      {
      /* primitive */
      min = (inparen ? getprimmin(proc) : getprimdflt(proc));
      if (min < 0)
         {
         /* special form */
         return ((logofunc) *getprimfun(proc)) (*args);
         }

      if (getprimmin(proc) == OK_NO_ARG) 
         {
         // Kludge: allow EDIT and CO without input without paren 
         min = 0;
         }

      max = (inparen ? getprimmax(proc) : getprimdflt(proc));
      }
      
   return gather_some_args(min, max, args, inparen, ifnode);
   }

// Treeify a list of tokens (runparsed or not).
void make_tree(NODE *newtree)
   {

   if (newtree == NIL ||
       (is_tree(newtree) && generation__tree(newtree) == the_generation))
      {
      // already a tree
      return;
      }

   // make sure the tree-to-be is runparsed
   if (!runparsed(newtree)) 
      {
      make_runparse(newtree);
      }

   tree_dk_how = false;
   NODE * childtree = paren_line(parsed__runparse(newtree));
   if (childtree != NIL && childtree != Unbound)
      {
      settype(newtree, TREE);
      settree__tree(newtree, childtree);
      if (tree_dk_how || stopping_flag == THROWING)
         {
         setgeneration__tree(newtree, Unbound);
         }
      }
   }


/* Calculate the priority of a procedure.
*/
int priority(NODE *proc_obj)
   {
   if (proc_obj == Minus_Tight)
      {
      return PREFIX_PRIORITY + 4;
      }

   NODE *proc;
   if (nodetype(proc_obj) != CASEOBJ ||
       (proc = procnode__caseobj(proc_obj)) == UNDEFINED ||
       nodetype(proc) != INFIX)
      {
      return 0;
      }

   return is_prim(proc) ? getprimpri(proc) : PREFIX_PRIORITY;
   }

/* Parenthesize an infix expression.  left_arg is the expression on the left
* (already parenthesized), and rest is a pointer to the list starting with the
* infix procedure, if it's there.  Set rest to after the right end of the
* infix expression.
*/
static 
NODE *paren_infix(NODE *left_arg, NODE **rest, int old_pri, bool inparen)
   {

   NODE *infix_proc;
   int pri;
   if (*rest == NIL || !(pri = priority(infix_proc = car(*rest))) || pri <= old_pri)
      {
      return left_arg;
      }
   ref(infix_proc);
   pop(*rest);

   NODE * retval = paren_expr(rest, inparen);
   retval = paren_infix(retval, rest, pri, inparen);
   retval = cons_list(infix_proc, left_arg, retval);
   deref(infix_proc);

   return paren_infix(retval, rest, old_pri, inparen);
   }
