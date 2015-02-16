/*
 *      sort.cpp       sorting utilities module                dvb
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
#include <stdlib.h>
#include <string.h>

#include "sort.h"
#include "logocore.h"
#include "logodata.h"
#include "logomath.h"

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
NODE *merge(NODE *a, NODE *b, bool ignorecase)
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
    if (compare_node(car(a), car(b), ignorecase) < 0)
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
        if (compare_node(car(a), car(b), ignorecase) < 0)
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
void mergepairs(NODE *nd, bool ignorecase)
{
    NODE *temp;

    while (nd != NIL && cdr(nd) != NIL)
    {
        nd->nunion.ncons.ncar = merge(car(nd), cadr(nd), ignorecase);
        temp = cdr(nd);
        nd->nunion.ncons.ncdr = cddr(nd);
        temp->nunion.ncons.ncar = temp->nunion.ncons.ncdr = NIL;
        gc(temp);
        nd = cdr(nd);
    }
}

/* Destructively sorts a list and returns the head of the new list */
NODE * mergesort(NODE * list, bool ignorecase)
{
    // The empty list is already sorted.
    if (list == NIL)
    {
        return NIL;
    }

    // A single element list is already sorted.
    if (cdr(list) == NIL) 
    {
        return list;
    }

    ms_listlist(list);
    while (cdr(list) != NIL)
    {
        mergepairs(list, ignorecase);
    }
    NODE * newHead = car(list);
    list->nunion.ncons.ncar = NIL;
    gc(list);
    return newHead;
}
