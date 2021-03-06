/*
 *      logocore.h          logo header file                dvb
 *
 *	Copyright (C) 1993 by the Regents of the University of California
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

#define ARRAYSIZE(ARRAY)            (sizeof(ARRAY) / sizeof(*(ARRAY)))
#define STRINGLENGTH(STRINGLITERAL) (sizeof(STRINGLITERAL) - 1)

#ifdef DEBUG

extern struct NODE * tracked_node;

void set_tracked_node(struct NODE * node);
void trace_node_change(struct NODE * Node);

#define TRACE_NODE_CHANGE(NODE) trace_node_change(NODE)
#define SET_TRACKED_NODE(NODE)  set_tracked_node(NODE)

#else

#define TRACE_NODE_CHANGE(NODE)
#define SET_TRACKED_NODE(NODE)

#endif // DEBUG


#define check_throwing (check_stop(false) || stopping_flag == THROWING)

enum mode_type
{
    wrapmode, 
    fencemode, 
    windowmode, 
    perspectivemode,
};

typedef struct NODE * (*logofunc) (struct NODE *);

#define WORDSIZE        32             /* bits per int                        */

#define NIL             ((NODE *) 0)
#define UNDEFINED       Unbound
#define HASH_LEN        1021           /* a prime number                      */
#define SEG_SIZE        1000           /* 1 for debugging internal leaks      */
//#define GCMAX         8192
#define MAX_NUMBER      50             /* max number of digits in a float     */
#define MAX_BUFFER_SIZE 256
#define MAX_PACKET_SIZE 1024

#define STOP_PRIORITY	0
#define OUTPUT_PRIORITY	1
#define MAYBE_PRIORITY	2
#define TAIL_PRIORITY	2	/* largest tailcall priority */
#define MACRO_PRIORITY	3
#define PREFIX_PRIORITY 4

const int TOTAL_SPECIAL_TURTLES = 3; // number of special turtles
const int SPECIAL_TURTLE_EYE_LOCATION   = 0;
const int SPECIAL_TURTLE_EYE_FIXATION   = 1;
const int SPECIAL_TURTLE_LIGHT_LOCATION = 2;

typedef unsigned short NODETYPES;

/* Note that some of these values are used twice; they must be
* distinguishable by the other bits used with them. */

const NODETYPES NT_TREE     = 0x8000;
const NODETYPES NT_EMPTY    = 0x4000;
const NODETYPES NT_AGGR     = 0x2000;
const NODETYPES NT_LIST     = 0x1000;
const NODETYPES NT_RUNP     = 0x0800;
const NODETYPES NT_ARRAY    = 0x0400;
const NODETYPES NT_WORD     = 0x0200;
const NODETYPES NT_NUMBER   = 0x0100;
const NODETYPES NT_FLOAT    = 0x0080;
const NODETYPES NT_CONT     = 0x0080;
const NODETYPES NT_PRIM     = 0x0040;
const NODETYPES NT_INFIX    = 0x0020;
const NODETYPES NT_LINE     = 0x0020;
const NODETYPES NT_VBAR     = 0x0020;
const NODETYPES NT_STRING   = 0x0010;
const NODETYPES NT_BACKSL   = 0x0008;
const NODETYPES NT_PUNCT    = 0x0004;
const NODETYPES NT_TAILFORM = 0x0004;
const NODETYPES NT_COLON    = 0x0002;
const NODETYPES NT_MACRO    = 0x0002;
const NODETYPES NT_CASEOBJ  = 0x0001;

const NODETYPES PNIL             = NT_EMPTY|NT_AGGR|NT_LIST;
const NODETYPES PUNBOUND         = 0;
const NODETYPES CONS             = NT_AGGR|NT_LIST;
const NODETYPES STRING           = NT_WORD|NT_STRING;
const NODETYPES INTEGER          = NT_WORD|NT_NUMBER;
const NODETYPES FLOATINGPOINT    = NT_WORD|NT_NUMBER|NT_FLOAT;
const NODETYPES PRIM             = NT_PRIM;
const NODETYPES MACRO            = NT_PRIM|NT_MACRO;
const NODETYPES TAILFORM         = NT_PRIM|NT_TAILFORM;
const NODETYPES CASEOBJ          = NT_WORD|NT_CASEOBJ;
const NODETYPES INFIX            = NT_PRIM|NT_INFIX;
const NODETYPES TREE             = NT_AGGR|NT_LIST|NT_TREE;
const NODETYPES RUN_PARSE        = NT_AGGR|NT_LIST|NT_RUNP;
const NODETYPES QUOTE            = NT_WORD|NT_PUNCT;
const NODETYPES COLON            = NT_WORD|NT_PUNCT|NT_COLON;
const NODETYPES BACKSLASH_STRING = NT_WORD|NT_STRING|NT_BACKSL;
const NODETYPES VBAR_STRING      = NT_WORD|NT_STRING|NT_BACKSL|NT_VBAR;
const NODETYPES ARRAY            = NT_AGGR|NT_ARRAY;
const NODETYPES LINE             = NT_LINE|NT_LIST|NT_AGGR;
const NODETYPES CONT             = NT_CONT|NT_LIST;
const NODETYPES NT_FREE          = 0xFFFF;

#define is_aggregate(nd) ((nodetype(nd) & NT_AGGR))
#define is_cont(nd)      ((nodetype(nd) == CONT))
#define is_list(nd)      ((nodetype(nd) & NT_LIST))
#define is_tree(nd)      ((nodetype(nd) & NT_TREE))
#define is_string(nd)    ((nodetype(nd) & NT_STRING))
#define is_number(nd)    ((nodetype(nd) & NT_NUMBER))
#define is_prim(nd)      ((nodetype(nd) & NT_PRIM))
#define is_word(nd)      ((nodetype(nd) & NT_WORD))
#define is_caseobject(nd)((nodetype(nd) == CASEOBJ))
#define runparsed(nd)    ((nodetype(nd) & NT_RUNP))
#define backslashed(nd)  ((nodetype(nd) & NT_BACKSL))
#define is_tailform(nd)  ((nodetype(nd) == TAILFORM))


// IMPORTANT: Logo programs depend on the value of these
// enumerated types, so any new values must be added to the
// end of the list.
enum ERR_TYPES
{
    SUCCESS              = 0, 

    OUT_OF_MEM           = 1, 
    STACK_OVERFLOW       = 2, 
    TURTLE_OUT_OF_BOUNDS = 3,
    BAD_DATA_UNREC       = 4,
    DIDNT_OUTPUT         = 5,
    NOT_ENOUGH           = 6,
    BAD_DATA             = 7,
    TOO_MUCH             = 8,
    DK_WHAT              = 9,
    PAREN_MISMATCH       = 10,
    NO_VALUE             = 11,
    UNEXPECTED_PAREN     = 12,
    DK_HOW               = 13,
    NO_CATCH_TAG         = 14,
    ALREADY_DEFINED      = 15,
    STOP_ERROR           = 16,
    ALREADY_DRIBBLING    = 17,
    FILE_ERROR           = 18,
    IF_WARNING           = 19,
    SHADOW_WARN          = 20,
    USER_ERR             = 21,
    IS_PRIM              = 22,
    NOT_INSIDE           = 23,
    DK_HOW_UNREC         = 24,
    NO_TEST              = 25,
    UNEXPECTED_BRACKET   = 26,
    UNEXPECTED_BRACE     = 27,
    BAD_GRAPH_INIT       = 28,
    ERR_MACRO            = 29,
    DK_WHAT_UP           = 30,
    AT_TOPLEVEL          = 31,
    APPLY_BAD_DATA       = 32,
    DEEPEND              = 33,
    OUT_OF_MEM_UNREC     = 34,

    // FMSLogo-specific error codes start at 1000
    WINDOW_GENERAL               = 1000,
    WINDOW_ALREADY_EXISTS        = 1001,
    WINDOW_DOES_NOT_EXIST        = 1002,

    DLL_GENERAL                  = 1100,
    DLL_LOAD_FAILED              = 1101,
    DLL_NOT_LOADED               = 1102,
    DLL_TYPE_DATA_NOT_PAIRED     = 1103,
    DLL_INVALID_DATA_TYPE        = 1104,
    DLL_INVALID_OUTPUT_TYPE      = 1105,
    DLL_FUNCTION_NOT_FOUND       = 1106,

    IMAGE_GENERAL                = 1200,
    IMAGE_GIF_LOAD_FAILED        = 1201,
    IMAGE_GIF_SAVE_FAILED        = 1202,
    IMAGE_BMP_OPEN_FAILED        = 1211,
    IMAGE_BMP_CREATE_FAILED      = 1212,
    IMAGE_BMP_WRITE_FAILED       = 1213,
    IMAGE_BMP_INVALID            = 1214,

    MIDI_GENERAL                 = 1300,
    MIDI_DEVICE_ALREADY_OPEN     = 1301,
    MIDI_INVALID_DEVICE          = 1302,
    MIDI_NOT_OPEN                = 1303,

    TIMER_GENERAL                = 1400,
    TIMER_NOT_FOUND              = 1401,

    FATAL                        = 0xFFFF,
};

#define FALSE   0
#define TRUE    1

#define even_p(x)  ((x % 2) == 0)
#define odd_p(x)   ((x % 2) != 0)

typedef long    FIXNUM;
// typedef __int64 FIXNUM  
#define MAXINT  0x7fffffffL
#define SAFEINT 0x00003fff   // safe to multiply w/o overflow

typedef double FLONUM;
#define FLONUM_MAX     DBL_MAX
#define FLONUM_EPSILON 1.0e-12 // don't use DLB_EPSILON (see bug #1624729)

struct NODE
{
#ifdef MEM_DEBUG
    int magic; // set to 'NODE'
#endif

    NODETYPES type;

    long ref_count;
    union
    {
        struct
        {
            NODE * ncar;
            NODE * ncdr;
            NODE * nobj;    // used only for oblist
        }
            ncons;
        struct
        {
            const char * ptr;
            char       * head;
            int          len;
        }
            nstring;
        struct
        {
            logofunc fun;
            short    npriority;
            short    nmin_args;
            short    ndef_args;
            short    nmax_args;
        }
            nprim;
        FIXNUM nint;
        FLONUM nfloat;
        struct
        {
            int     dim;
            int     origin;
            NODE ** data;
        }
            narray;
    }
        nunion;
};

extern void      gc(NODE* node);
extern NODETYPES nodetype(const NODE *nd);

inline
void
settype(NODE * Node, NODETYPES Type)
{
    Node->type = Type;
}

inline
long
getrefcnt(const NODE * Node)
{
    return Node->ref_count;
}

inline
void increfcnt(NODE * Node)
{
    TRACE_NODE_CHANGE(Node);
    Node->ref_count++;
}

inline
long
decrefcnt(NODE * Node)
{
    TRACE_NODE_CHANGE(Node);
    return --Node->ref_count;
}

inline
bool
is_freed(const NODE * node)
{
    return node->type == 0xCCCC || node->type == NT_FREE;
}

inline
NODE*
car(const NODE * node)
{
    assert(node != NULL);
    assert(!is_freed(node));
    assert(node->type != STRING);
    assert(node->type != INTEGER);
    assert(node->type != FLOATINGPOINT);

    return node->nunion.ncons.ncar;
}

inline
NODE*
cdr(const NODE * node)
{
    assert(node != NULL);
    assert(!is_freed(node));
    assert(node->type != STRING);
    assert(node->type != INTEGER);
    assert(node->type != FLOATINGPOINT);

    return node->nunion.ncons.ncdr;
}

inline
NODE*
getobject(const NODE * node)
{
    assert(node != NULL);
    assert(!is_freed(node));
    assert(node->type != STRING);
    assert(node->type != INTEGER);
    assert(node->type != FLOATINGPOINT);

    return node->nunion.ncons.nobj;
}

#define caar(node)              car(car(node))
#define cadr(node)              car(cdr(node))
#define cdar(node)              cdr(car(node))
#define cddr(node)              cdr(cdr(node))

#define getstrptr(node)         ((node)->nunion.nstring.ptr)
#define getstrlen(node)         ((node)->nunion.nstring.len)
#define getstrhead(node)        ((node)->nunion.nstring.head)
#define setstrptr(node,str)     ((node)->nunion.nstring.ptr = (str))
#define setstrlen(node,length)  ((node)->nunion.nstring.len = (length))
#define setstrhead(node,ptr)    ((node)->nunion.nstring.head = (ptr))

inline 
unsigned short
getstrrefcnt(const unsigned short * refcnt)
{
    return *refcnt;
}

inline 
void
setstrrefcnt(unsigned short * refcnt, unsigned short value)
{
    *refcnt = value;
}

inline 
unsigned short
incstrrefcnt(unsigned short * refcnt)
{
    return (*refcnt)++;
}

inline 
unsigned short
decstrrefcnt(unsigned short * refcnt)
{
    return --(*refcnt);
}

inline FIXNUM 
getint(const NODE * Node) 
{
    assert(Node != NULL);
    //assert(Node->type == INTEGER);
    return Node->nunion.nint;
}

inline FLONUM
getfloat(const NODE * Node)
{
    assert(Node != NULL);
    //assert(Node->type == FLOATINGPOINT);
    return Node->nunion.nfloat;
}

inline
logofunc 
getprimfun(const NODE * Node)
{
    assert(Node != NULL);
    assert(is_prim(Node));
    return Node->nunion.nprim.fun;
}

inline 
void
setprimfun(NODE * Node, logofunc Func)
{
    assert(Node != NULL);
    assert(is_prim(Node));
    Node->nunion.nprim.fun = Func;
}

inline
short 
getprimmin(const NODE * Node)
{
    assert(Node != NULL);
    assert(is_prim(Node));
    return Node->nunion.nprim.nmin_args;
}

inline
void 
setprimmin(NODE * Node, short Min)
{
    assert(Node != NULL);
    assert(is_prim(Node));
    Node->nunion.nprim.nmin_args = Min;
}


inline
short 
getprimmax(const NODE * Node)
{
    assert(Node != NULL);
    assert(is_prim(Node));
    return Node->nunion.nprim.nmax_args;
}

inline
void 
setprimmax(NODE * Node, short Max)
{
    assert(Node != NULL);
    assert(is_prim(Node));
    Node->nunion.nprim.nmax_args = Max;
}

inline
short 
getprimdflt(const NODE * Node)
{
    assert(Node != NULL);
    assert(is_prim(Node));
    return Node->nunion.nprim.ndef_args;
}

inline
void 
setprimdflt(NODE * Node, short Default)
{
    assert(Node != NULL);
    assert(is_prim(Node));
    Node->nunion.nprim.ndef_args = Default;
}

inline
short 
getprimpri(const NODE * Node)
{
    assert(Node != NULL);
    assert(is_prim(Node));
    return Node->nunion.nprim.npriority;
}

inline
void
setprimpri(NODE * Node, short Priority)
{
    assert(Node != NULL);
    assert(is_prim(Node));
    Node->nunion.nprim.npriority = Priority;
}

// Special value for pmin, means that it's
// OK if primitive name on line by itself even though defltargs=1 (ED, CO)
#define OK_NO_ARG       01000

inline
int 
getarrdim(const NODE * Node)
{
    assert(Node != NULL);
    assert(Node->type == ARRAY);
    return Node->nunion.narray.dim;
}

inline
int
getarrorg(const NODE * Node)
{
    assert(Node != NULL);
    assert(Node->type == ARRAY);
    return Node->nunion.narray.origin;
}

inline
NODE **
getarrptr(const NODE * Node)
{
    assert(Node != NULL);
    assert(Node->type == ARRAY);
    return Node->nunion.narray.data;
}

inline
void
setarrdim(NODE * Node, int Length)
{
    assert(Node != NULL);
    assert(Node->type == ARRAY);
    Node->nunion.narray.dim = Length;
}

inline
void
setarrorg(NODE * Node, int Origin)
{
    assert(Node != NULL);
    assert(Node->type == ARRAY);
    Node->nunion.narray.origin = Origin;
}

inline
void
setarrptr(NODE * Node, NODE ** Ptr)
{
    assert(Node != NULL);
    assert(Node->type == ARRAY);
    Node->nunion.narray.data = Ptr;
}

enum CTRLTYPE
{
    RUN, 
    STOP, 
    OUTPUT, 
    THROWING, 
    MACRO_RETURN,
};

#define NOT_THROWING            (stopping_flag != THROWING)
#define RUNNING                 (stopping_flag == RUN)
#define STOPPING                (stopping_flag == STOP)

#define canonical__object(o)    car(o)
#define procnode__object(o)     cadr(o)
#define setprocnode__object(o,v) setcar(cdr(o), v)
#define valnode__object(o)      cadr(cdr(o))
#define setvalnode__object(o,v) setcar(cddr(o), v)
#define plist__object(o)        cadr(cddr(o))
#define setplist__object(o,v)   setcar(cdr(cddr(o)), v)
#define obflags__object(o)      car(cddr(cddr(o)))
#define caselistptr__object(o)  cddr(cddr(o))
#define caselist__object(o)     cdr(cddr(cddr(o)))

#define strnode__caseobj(co)    car(co)
#define object__caseobj(c)      cdr(c)
#define procnode__caseobj(c)    procnode__object(object__caseobj(c))
#define setprocnode__caseobj(c,v) setprocnode__object(object__caseobj(c),v)
#define valnode__caseobj(c)     valnode__object(object__caseobj(c))
#define setvalnode__caseobj(c,v) setvalnode__object(object__caseobj(c),v)
#define plist__caseobj(c)       plist__object(object__caseobj(c))
#define setplist__caseobj(c,v)  setplist__object(object__caseobj(c),v)
#define obflags__caseobj(c)     obflags__object(object__caseobj(c))

#define text__procnode(p)       car(p)
#define formals__procnode(p)    caar(p)
#define bodylist__procnode(p)   cdar(p)
#define dfltargs__procnode(p)   cadr(cddr(p))
#define minargs__procnode(p)    car(cddr(p))
#define maxargs__procnode(p)    car(cddr(cddr(p)))
#define bodywords__procnode(p)  cadr(p)
#define setbodywords__procnode(p,v) setcar(cdr(p),v)

inline
NODE*
parsed__runparse(
    const NODE * runparsed_node
    )
{
    assert(runparsed_node->type == RUN_PARSE);
    return getobject(runparsed_node);
}

#define node__quote(q)          car(q)
#define node__colon(c)          car(c)
#define valnode__colon(c)       valnode__caseobj(node__colon(c))

#define treepair__tree(t)       getobject(t)
#define settreepair__tree(t, v) setobject(t, v)
#define generation__tree(t)     car(treepair__tree(t))
#define setgeneration__tree(t, g) setcar(treepair__tree(t), g)
#define tree__tree(t)           cdr(treepair__tree(t))
#define settree__tree(t, v)     settreepair__tree(t, cons(the_generation, v))

#define unparsed__line(l)       getobject(l)
#define generation__line(l)     (generation__tree(unparsed__line(l)))

#define cont__cont(c)           (int)car(c)
#define val__cont(c)            cdr(c)

/* Object flags.  Ones settable by users via bury_helper must come in threes
* for proc, val, plist even if meaningless for some of those. */
#define PROC_BURIED     01
#define VAL_BURIED      02
#define PLIST_BURIED    04
#define PROC_TRACED     010
#define VAL_TRACED      020
#define PLIST_TRACED    040
#define PROC_STEPPED    0100
#define VAL_STEPPED     0200
#define PLIST_STEPPED   0400
#define PROC_MACRO      01000

#define setflag__caseobj(c,f) ((obflags__caseobj(c))->nunion.nint |= (f))
#define clearflag__caseobj(c,f) ((obflags__caseobj(c))->nunion.nint &= ~(f))
#define flag__caseobj(c,f) (int)((obflags__caseobj(c))->nunion.nint & (f))
#define flag__object(o,f) (int)((obflags__object(o))->nunion.nint & (f))
#define is_macro(c) (flag__caseobj(c, PROC_MACRO))

inline
void
ref(NODE * object)
{
    if (object != NIL)
    {
        assert(!is_freed(object));
        increfcnt(object);
    }
}

inline
NODE*
vref(NODE * object)
{
    if (object != NIL)
    {
        assert(!is_freed(object));
        increfcnt(object);
    }
    return object;
}


inline 
void
deref(NODE * object)
{
    if (object == NIL)
    {
        return;
    }

    assert(!is_freed(object));
    assert(getrefcnt(object) != 0); // memleak

    if (decrefcnt(object) == 0)
    {
        gc(object);
    }
}

inline 
void
gcref(NODE * object)
{
    if (object == NIL)
    {
        return;
    }

    assert(!is_freed(object));

    if (getrefcnt(object) == 0)
    {
        TRACE_NODE_CHANGE(object);
        gc(object);
    }
}

#define push(obj, stack)    spush(obj, &stack)
#define pop(stack)          spop(&stack)

/* evaluator labels, needed by macros in other files */

#define do_list(x) \
   x(all_done) \
   x(begin_line) \
   x(end_line) \
   x(begin_seq) \
   x(begin_apply) \
   x(eval_sequence_continue) \
   x(accumulate_arg) \
   x(compound_apply_continue) \
   x(set_args_continue) \
   x(macro_return) \
   x(after_lambda) \
   x(runresult_continuation) \
   x(runresult_followup) \
   x(repeat_continuation) \
   x(repeat_followup) \
   x(catch_continuation) \
   x(catch_followup) \
   x(goto_continuation) \


#define do_enum(x) x,

enum labels
{
    do_list(do_enum)
    NUM_TOKENS
};

// write modes (not sure what these numbers mean)
const int COPY_PUT = 12;
const int XOR_PUT  = 199;

#define ScreenSz 0.70      // Default proportion of screen size
#define MAX_TIMERS 32
