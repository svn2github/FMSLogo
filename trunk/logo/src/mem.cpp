/*
 *      mem.cpp         logo memory management module           dvb 6/28/88
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

#include <stdio.h>

#include "logodata.h"
#include "main.h"
#include "error.h"
#include "status.h"
#include "debugheap.h"


// a segment is a pool of nodes that is allocated in a single malloc.
struct segment
{
    segment * next;
    NODE      nodes[SEG_SIZE];
};

int memory_count = 0;                  // Current amount of logo segments malloc'd

static NODE    *free_list    = NIL;    // global ptr to free node list
static segment *segment_list = NULL;   // global ptr to segment list

static long int mem_nodes = 0;
static long int mem_max = 0;

static NODE *reserve_tank;


#ifdef DEBUG

NODE * tracked_node = NIL;

void set_tracked_node(struct NODE * node)
{
    tracked_node = node;
}

void trace_node_change(struct NODE * Node)
{
    if (Node != NULL && Node == tracked_node)
    {
        DebugBreak();
    }
}

#endif // DEBUG


NODETYPES nodetype(const NODE *nd)
{
    if (nd == NIL) 
    {
        return PNIL;
    }

    return nd->type;
}

void setobject(NODE *nd, NODE *newobj)
{
    NODE *oldobj = getobject(nd);
   
    ref(newobj);
    deref(oldobj);

    nd->nunion.ncons.nobj = newobj;
}

void setcar(NODE *nd, NODE *newcar)
{
    NODE *oldcar = car(nd);

    ref(newcar);
    deref(oldcar);

    nd->nunion.ncons.ncar = newcar;
}

void setcdr(NODE *nd, NODE *newcdr)
{
    NODE *oldcdr = cdr(nd);

    ref(newcdr);
    deref(oldcdr);

    nd->nunion.ncons.ncdr = newcdr;
}

NODE *reref(NODE *oldval, NODE *newval)
{
    // reference newval
    ref(newval);

    // dereference proc_var
    deref(oldval);

    return newval;
}

// Decrements the reference count and returns the object, but will not free it.
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
        new_node->nunion.ncons.ncdr = free_list;
        free_list = new_node;
    }
#else

    // Allocate a large block of nodes at one time
    // and link them into the free_list.
    memory_count++;
    update_status_memory();

    struct segment *newseg;
    if ((newseg = (segment *) malloc(sizeof(*newseg))) != NULL)
    {
        newseg->next = segment_list;
        segment_list = newseg;
        for (int p = 0; p < SEG_SIZE; p++)
        {
            newseg->nodes[p].nunion.ncons.ncdr = free_list;
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
    //    update_status_memory();

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
    free_list = newnd->nunion.ncons.ncdr;
    settype(newnd, type);
    newnd->ref_count = 0;
    newnd->nunion.ncons.ncar = NIL;
    newnd->nunion.ncons.ncdr = NIL;
    newnd->nunion.ncons.nobj = NIL;
    mem_nodes++;
    if (mem_nodes > mem_max) 
    {
        mem_max = mem_nodes;
    }
    return newnd;
}

// Returns a NODE with refcount=0.
// Caller must free.
NODE *cons(NODE *x, NODE *y)
{
    NODE *val = newnode(CONS);

    setcar(val, x);
    setcdr(val, y);
    return val;
}

class CGarbageCollectionStack
{
    typedef struct _LIST_NODE
    {
        // Pointer to the next item in the list.
        struct _LIST_NODE * Next;
        
        // As many pointers as can fit into a NODE
        NODE * Nodes[3];
    } LIST_NODE;

public:
    void Initialize()
    {
        m_FreeList     = NULL;
        m_TopNode      = NULL;
        m_TopNodeIndex = ARRAYSIZE(m_TopNode->Nodes);
    }

    void AddMemory(NODE * UnusedLogoNode)
    {
        LIST_NODE * listNode = reinterpret_cast<LIST_NODE*>(UnusedLogoNode);

        // Assert that we can use an unused NODE as a LIST_NODE.
        assert(sizeof *listNode <= sizeof *UnusedLogoNode);

        // Add this node to the head of the free list.
        listNode->Next = m_FreeList;
        m_FreeList     = listNode;
    }

    void PushDeferredNode(NODE * DeferredNode)
    {
        if (m_TopNodeIndex == ARRAYSIZE(m_TopNode->Nodes))
        {
            // The current stack element is full.
            // Get another one from the FreeList.
            // The caller is responsible for ensuring that
            // there are enough elements in the free list.
            assert(m_FreeList != NULL);

            // Pop the node off the free list
            LIST_NODE * newNode = reinterpret_cast<LIST_NODE*>(m_FreeList);
            m_FreeList = m_FreeList->Next;

#ifdef MEM_DEBUG
            // Initialize the unused node slots to a recognizable value
            for (size_t i = 0; i < ARRAYSIZE(m_FreeList->Nodes); i++)
            {
                newNode->Nodes[i] = (NODE*)0xDCDCDCDC;
            }
#endif

            // Push this node onto the deferred stack
            newNode->Next  = m_TopNode;
            m_TopNode      = newNode;
            m_TopNodeIndex = 0;
        }

        // Now m_TopNode[m_TopNodeIndex] is an open slot.  Use it.
        m_TopNode->Nodes[m_TopNodeIndex] = DeferredNode;
        m_TopNodeIndex++;
    }

    void MaybeGarbageCollect(NODE * Node)
    {
        // REVISIT: Should this be reconciled with deref?
        if (Node != NIL)
        {
            if (decrefcnt(Node) == 0)
            {
                PushDeferredNode(Node);
            }
        }
    }

    bool DeferredStackIsEmpty()
    {
        return m_TopNode == NULL;
    }

    NODE * PopDeferredNode()
    {
        if (m_TopNode == NULL)
        {
            // There are no deferred nodes remaining.
            assert(m_TopNodeIndex == ARRAYSIZE(m_TopNode->Nodes));
            return NIL;
        }

        // Decrement m_TopNodeIndex to the next used slot.
        m_TopNodeIndex--;

        // Return the node in the m_TopNodeIndex slot.
        NODE * deferredNode = m_TopNode->Nodes[m_TopNodeIndex];

#ifdef MEM_DEBUG
        // Set the now freed slot to a recognizable value.
        m_TopNode->Nodes[m_TopNodeIndex] = (NODE*)0xABABABAB;
#endif

        if (m_TopNodeIndex == 0)
        {
            // That was the last node in this block.
            // Move it back to the free list.

            // Pop this node from the deferred GC list.
            LIST_NODE * node = m_TopNode;
            m_TopNode      = m_TopNode->Next;
            m_TopNodeIndex = ARRAYSIZE(m_TopNode->Nodes);

            // Push it node onto the free list.
            node->Next = m_FreeList;
            m_FreeList = node;
        }

        return deferredNode;
    }

    void Uninitialize()
    {
        // If the GC stack is going to be uninitialized, there shouldn't
        // be any nodes which are pending evaluation.
        assert(m_TopNode == NULL);
        assert(m_TopNodeIndex == ARRAYSIZE(m_TopNode->Nodes));

        LIST_NODE * nextNode;
        for (LIST_NODE * node = m_FreeList; node != NULL; node = nextNode)
        {
            // Remember what the next node is, before we free node.
            nextNode = node->Next;

#ifdef MEM_DEBUG
            // The easiest way to debug leaks is to just free the node.
            free(node);
#else
            // "free" this node by adding it to the free list
            NODE * logoNode = reinterpret_cast<NODE*>(node);
            logoNode->nunion.ncons.ncdr = free_list;
            free_list = logoNode;
#endif
        }

        m_FreeList = NULL;
    }

private:
    // A pointer to a list of GC deferred list nodes that
    // contains no NODEs.  This is a "free" list that can be
    // used when we need to expand the stack.
    // TODO: Merge this with the global "free list"
    LIST_NODE * m_FreeList;

    // This is the first node in the GC deferred list that has
    // NODE* in it that still need to be garbage collected.
    LIST_NODE * m_TopNode;
    int         m_TopNodeIndex;
};


void gc(NODE *nd)
{
    CGarbageCollectionStack gc_deferred_list;

    gc_deferred_list.Initialize();

    while (nd != NIL)
    {
        NODE *tcar;
        NODE *tcdr;
        NODE *tobj;

        int i;
        NODE **pp;

        switch (nodetype(nd))
        {
        case PUNBOUND:
            nd->ref_count = 10000;  // save some time

            // get ready to garbage collect the next node
            nd = gc_deferred_list.PopDeferredNode();
            continue;

        case LINE:
        case CONS:
        case CASEOBJ:
        case RUN_PARSE:
        case QUOTE:
        case COLON:
        case TREE:
            tcar = car(nd);
            tcdr = cdr(nd);
            tobj = getobject(nd);
            break;

        case CONT:
            // Continuation nodes only have a valid cdr.
            tcar = NIL;   // the car is a labels, not a NODE*
            tcdr = cdr(nd);
            tobj = NIL;   // the object shouldn't exist
            break;

        case ARRAY:
            pp = getarrptr(nd);
            i = getarrdim(nd);
            while (--i >= 0)
            {
                tobj = *pp++;

                // BUG: deref(tobj) can potentially call gc(),  which
                // means that it could cause a stack overflow.
                // The deref() should be reworked to use the gcstack.
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

                assert(*temp != 0); // the string was already freed
                if (decstrrefcnt(temp) == 0) 
                {
                    free(getstrhead(nd));
                }
            }

        case INTEGER:
        case FLOATINGPOINT:
        case PRIM:
        case MACRO:
        case TAILFORM:
        case INFIX:
            tcar = tcdr = tobj = NIL;
            break;

        default:
            assert(!"freeing unrecognized node type");
        }

        mem_nodes--;

        // At this point, we no longer need "nd", so we can
        // use its memory as bookkeeping space for the nodes
        // that we wish to free.
        gc_deferred_list.AddMemory(nd);

        // Check if any of the child noded can be garbage collected
        gc_deferred_list.MaybeGarbageCollect(tcar);
        gc_deferred_list.MaybeGarbageCollect(tcdr);
        gc_deferred_list.MaybeGarbageCollect(tobj);

        // get ready to garbage collect the next node
        nd = gc_deferred_list.PopDeferredNode();
    }

    // Free all of the nodes which were marked has having
    // no further references as a result of freeing nd.
    gc_deferred_list.Uninitialize();
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
