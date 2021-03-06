/*
 *      logodata.cpp    logo data management module             dvb
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

#ifndef WX_PURE
#include <windows.h>
#endif

#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>

#include "logodata.h"
#include "version.h"
#include "init.h"
#include "error.h"
#include "mem.h"
#include "parse.h"
#include "logomath.h"
#include "lists.h"
#include "eval.h"
#include "intern.h"
#include "print.h"
#include "files.h"
#include "appendablelist.h"
#include "debugheap.h"

#include "localizedstrings.h"

#if WX_PURE
// wxTODO: The original, non-internationalized code is used when not on Windows.
// This should be rewritten to use the Unicode-aware C routines.
#define upper_p(c) (c >= 'A' && c <= 'Z')
#endif

// g_SpecialCharacters[] is an array of characters that must be escaped
// with a backslash when put in a string.
//
// The series of "+" characters from 0x7 to 0xD (but not 0xB) represent 
// a hole in the set of backslahed representations.
//
// REVISIT: why do "?" and the infix operators need to be backslashed?
//
//                                            1         2           3
//                                   3 4 56789012345678901234 5 678901
static char g_SpecialCharacters[] = " \t\n(?????+++~)[]-*/=<>\"\\:;|{}";

bool
is_special_character(char ch)
{
    return strchr(g_SpecialCharacters, ch) != NULL;
}

const int ecma_begin = 3; // first char used for quoteds

static char ecma_array[128];

char ecma_set(int ch)
{
    // Return the backslashed form of "ch".
    ch &= 0xFF;
    if (ch >= 0x80)
    {
        return ch;
    }
    return ecma_array[ch];
}

char ecma_clear(int ch)
{
    // Return the unbackslashed form of "ch".
    ch &= 0xFF;
    if (ch < ecma_begin || ch >= ecma_begin + sizeof(g_SpecialCharacters) - 1) 
    {
        // ch is not backslashed
        return ch;
    }
    if (ch >= 0x7 && ch <= 0xD && ch != 0xB) 
    {
        // ch is not backslashed
        return ch;
    }

    // ch is backslashed
    return g_SpecialCharacters[ch - ecma_begin];
}

bool ecma_get(int ch)
{
    // return true if "ch" is backslashed.
    // return false, otherwise.

    ch &= 0xFF;
    return 
        ((ch >= ecma_begin && ch < ecma_begin + sizeof(g_SpecialCharacters) - 1) && 
         (ch < 0x7 || ch > 0xD || ch == 0xB));
}

void init_ecma_array()
{
    // Initialize ecma_array to map all characters to themselves.
    for (int i = 0; i < sizeof(ecma_array); i++)
    {
        ecma_array[i] = i;
    }

    // Override the special characters to map to ecma_begin+index.
    // Characters a "backslashed" by replacing them with very small 
    // values that are usually used for control characters.
    for (int i = 0; i < sizeof(g_SpecialCharacters) - 1; i++)
    {
        ecma_array[g_SpecialCharacters[i]] = ecma_begin+i;
    }
}

char *strnzcpy(char *dst, const char *src, int len)
{
    strncpy(dst, src, len);
    dst[len] = '\0';
    return dst;
}

char *word_strnzcpy(char *dst, NODE *wordlist, int len)
{
    char *temp = dst;

    while (wordlist != NIL)
    {
        strncpy(dst, getstrptr(car(wordlist)), getstrlen(car(wordlist)));
        dst += getstrlen(car(wordlist));
        wordlist = cdr(wordlist);
    }
    temp[len] = '\0';
    return temp;
}

char *noparity_strnzcpy(char *dst, const char * src, int len)
{
    for (int i = 0; i < len; i++)
    {
        dst[i] = ecma_clear(src[i]);
    }
    dst[len] = '\0';

    return dst;
}

char *mend_strnzcpy(char *dst, const char * src, int len)
{
    bool vbar = false;

    for (int i = 0; i < len;)
    {
        while (*src == '|')
        {
            vbar = !vbar;
            src++;
        }
        if (vbar)
        {
            if (is_special_character(*src))
            {
                dst[i++] = ecma_set(*src++);
            }
            else
            {
                dst[i++] = *src++;
            }
        }
        else
        {
            while (*src == ';' || (*src == '~' && *(src + 1) == '\n'))
            {
                while (*src == '~' && *(src + 1) == '\n') 
                {
                    src += 2;
                }
                if (*src == ';')
                    do
                    {
                        src++;
                    } while (*src != '\0' && *src != '~' && *(src + 1) != '\n');
            }

            if (*src != '|') 
            {
                dst[i++] = *src++;
            }
        }
    }
    dst[len] = '\0';
    return dst;
}

char *mend_nosemi(char *dst, const char * src, int len)
{
    bool vbar = false;

    for (int i = 0; i < len;)
    {
        while (*src == '|')
        {
            vbar = !vbar;
            src++;
        }
        if (vbar)
        {
            if (is_special_character(*src))
            {
                dst[i++] = ecma_set(*src++);
            }
            else
            {
                dst[i++] = *src++;
            }
        }
        else
        {
            while ((*src == '~' && *(src + 1) == '\n'))
            {
                while (*src == '~' && *(src + 1) == '\n') 
                {
                    src += 2;
                }
            }
            if (*src != '|') 
            {
                dst[i++] = *src++;
            }
        }
    }
    dst[len] = '\0';
    return dst;
}

char *quote_strnzcpy(char *dst, const char *src, int len)
{
    dst[0] = '"';
    strncpy(dst + 1, src, len - 1);
    dst[len] = '\0';
    return dst;
}

char *colon_strnzcpy(char *dst, const char * src, int len)
{
    dst[0] = ':';
    strncpy(dst + 1, src, len - 1);
    dst[len] = '\0';
    return dst;
}

char
uncapital(
    char Capital
    )
{
    char lowercase;

#ifdef WX_PURE
    lowercase = tolower(Capital);
#else
    LCMapString(
        MAKELCID(LANG_USER_DEFAULT, SORT_DEFAULT),
        LCMAP_LOWERCASE,
        &Capital,
        sizeof(Capital),
        &lowercase,
        sizeof(lowercase));
#endif

    return lowercase;
}

static
bool
islowercase(
    char Character
    )
{
    return uncapital(Character) == Character;
}

char *low_strnzcpy(char *dst, const char * src, int len)
{
#ifdef WX_PURE
    for (int i = 0; i < len; i++)
    {
        dst[i] = uncapital(src[i]);
    }
#else
    LCMapString(
        MAKELCID(LANG_USER_DEFAULT, SORT_DEFAULT),
        LCMAP_LOWERCASE,
        src,
        len,
        dst,
        len);
#endif

    dst[len] = '\0';
    return dst;
}

char
capital(
    char LowerCase
    )
{
    char capital;

#ifdef WX_PURE
    capital = toupper(LowerCase);
#else
    LCMapString(
        MAKELCID(LANG_USER_DEFAULT, SORT_DEFAULT),
        LCMAP_UPPERCASE,
        &LowerCase,
        sizeof(LowerCase),
        &capital,
        sizeof(capital));
#endif

    return capital;
}

char *cap_strnzcpy(char *dst, const char * src, int len)
{
#ifdef WX_PURE
    for (size_t i = 0; i < len; i++)
    {
        dst[i] = capital(src[i]);
    }
#else
    LCMapString(
        MAKELCID(LANG_USER_DEFAULT, SORT_DEFAULT),
        LCMAP_UPPERCASE,
        src,
        len,
        dst,
        len);
#endif

    dst[len] = '\0';
    return dst;
}

char * NormalizeCaseForDisplay(char *dst, const char * src, int len)
{
    return cap_strnzcpy(dst, src, len);
}

char *noparitylow_strnzcpy(char *dst, const char *src, int len)
{
    char *temp = dst;

    for (int i = 0; i < len; i++)
    {
        char c = ecma_clear(*src++);

        *dst++ = uncapital(c);
    }
    *dst = '\0';
    return temp;
}

int low_strncmp(const char *string1, const char * string2, int length)
{
#ifdef WX_PURE
    for (size_t i = 0; i < length; i++)
    {
        if (*string1 != *string2)
        {
            if (upper_p(*string2))
            {
                if (upper_p(*string1))
                {
                    if (uncapital(*string1) != uncapital(*string2))
                        return (uncapital(*string1) - uncapital(*string2));
                }
                else
                {
                    if (*string1 != uncapital(*string2))
                    {
                        return (*string1 - uncapital(*string2));
                    }
                }
            }
            else if (upper_p(*string1))
            {
                if (uncapital(*string1) != *string2)
                {
                    return (uncapital(*string1) - *string2);
                }
            }
            else
            {
                return (*string1 - *string2);
            }
        }
        string1++;
        string2++;
    }

    return 0;

#else
    int rval = CompareString(
        MAKELCID(LANG_USER_DEFAULT, SORT_DEFAULT),
        NORM_IGNORECASE,
        string1,
        length,
        string2,
        length);

    // convert from CompareString() to C return value
    rval -= 2;

    return rval;
#endif
}

int noparity_strncmp(const char * s1, const char * s2, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (ecma_clear(*s1) != ecma_clear(*s2))
        {
            return (ecma_clear(*s1) - ecma_clear(*s2));
        }
        s1++, s2++;
    }
    return 0;
}

int noparitylow_strncmp(const char * s1, const char * s2, int len)
{
    for (int i = 0; i < len; i++)
    {
        char c1 = ecma_clear(*s1);
        char c2 = ecma_clear(*s2);
        if (c1 != c2)
        {
            int rval = low_strncmp(&c1, &c2, 1);
            if (rval != 0)
            {
                return rval;
            }
        }
        s1++;
        s2++;
    }

    return 0;
}



// Makes a string node by copying a NUL-terminated string
// into a NODE structure.
NODE * 
make_strnode(
    const char *string, 
    int         len,
    NODETYPES   typ,  
    char *    (*copy_routine) (char *, const char *, int)
    )
{
    assert(typ & NT_STRING);

    if (len == 0 && Null_Word != NIL)
    {
        return Null_Word;
    }

    // allocate enough to hold the header, the string, and NUL.
    char * strhead = (char *) malloc(sizeof(short) + len + 1);
    if (strhead == NULL)
    {
        err_logo(OUT_OF_MEM, NIL);
        return Unbound;
    }

    // set the "string pointer" to just after the header
    char * strptr = strhead + sizeof(short);
    copy_routine(strptr, string, len);

    // set the reference count to 1.
    unsigned short *header = (unsigned short *) strhead;
    setstrrefcnt(header, 1);

    NODE * strnode = newnode(typ);
    setstrlen(strnode, len);
    setstrptr(strnode, strptr);
    setstrhead(strnode, strhead);
    return strnode;
}

// Makes a STRING node by copying a NUL-terminated string
// into a NODE structure.  
// It uses strnzcpy as its copy routine.
NODE * 
make_strnode(
    const char *string
    )
{
    return make_strnode(string, strlen(string), STRING, strnzcpy);
}


// Makes a string node by copying from a list of word nodes.
NODE * 
make_strnode_from_wordlist(
    NODE *      wordlist, 
    int         len,
    NODETYPES   typ
    )
{
    if (len == 0 && Null_Word != NIL)
    {
        return Null_Word;
    }

    // allocate enough to hold the header, the string, and NUL.
    char * strhead = (char *) malloc(sizeof(short) + len + 1);
    if (strhead == NULL)
    {
        err_logo(OUT_OF_MEM, NIL);
        return Unbound;
    }

    // set the "string pointer" to just after the header
    char * strptr = strhead + sizeof(short);
    word_strnzcpy(strptr, wordlist, len);

    // set the reference count to 1.
    unsigned short *header = (unsigned short *) strhead;
    setstrrefcnt(header, 1);

    NODE * strnode = newnode(typ);
    setstrlen(strnode, len);
    setstrptr(strnode, strptr);
    setstrhead(strnode, strhead);
    return strnode;
}


// Makes a string node by referencing an existing NUL-terminated string.
// This string is modified and must not be in static memory.
NODE *
make_strnode_no_copy(
    const char *strptr, 
    char       *strhead, 
    int         len,
    NODETYPES   typ
    )
{
    // increment the reference count
    unsigned short * header = (unsigned short *) strhead;
    assert(header != NULL);       // string is in static memory
    assert(*header != USHRT_MAX); // ref count would overflow
    incstrrefcnt(header);

    if (len == 0 && Null_Word != NIL)
    {
        // we will not take this reference, so we must free it.
        if (decstrrefcnt(header) == 0) 
        {
            free(header);
        }
        return Null_Word;
    }

    NODE * strnode = newnode(typ);
    setstrlen(strnode, len);
    setstrptr(strnode, strptr);
    setstrhead(strnode, strhead);
    return strnode;
}

NODE *
make_lowercase_strnode_from_strnode(
    NODE * OriginalNode
    )
{
    assert(is_string(OriginalNode));

    // Check to see if this is already a lower-case node.
    // There's no need to allocate a new node if the current 
    // one will do.

    const char * originalString       = getstrptr(OriginalNode);
    size_t       originalStringLength = getstrlen(OriginalNode);
    for (size_t i = 0; i < originalStringLength; i++)
    {
        if (!islowercase(originalString[i]))
        {
            // OriginalNode is not already lowercase.
            return make_strnode(
                originalString,
                originalStringLength,
                nodetype(OriginalNode), 
                low_strnzcpy);
        }
    }

    // OriginalNode is already a lower-case string
    return OriginalNode;
}

void make_runparse(NODE *ndi)
{
    NODE * rp_list = runparse(ndi);
    setobject(ndi, rp_list);
    settype(ndi, RUN_PARSE);
}

NODE *make_quote(NODE *qnd)
{
    NODE * nd = cons_list(qnd);

    settype(nd, QUOTE);
    return nd;
}

NODE *maybe_quote(NODE *nd)
{
    if (nd == Unbound || is_aggregate(nd) || numberp(nd)) return (nd);
    return make_quote(nd);
}

NODE *make_caseobj(NODE *cstrnd, NODE *obj)
{
    NODE *nd = cons(cstrnd, obj);

    settype(nd, CASEOBJ);
    return nd;
}

NODE *make_colon(NODE *cnd)
{
    NODE *nd = cons_list(cnd);

    settype(nd, COLON);
    return nd;
}

NODE *make_intnode(FIXNUM i)
{
    NODE *nd = newnode(INTEGER);

    nd->nunion.nint = i;
    return nd;
}

NODE *make_floatnode(FLONUM f)
{
    NODE *nd = newnode(FLOATINGPOINT);

    nd->nunion.nfloat = f;
    return nd;
}

// Caller must call gcref() on the returned value
NODE *cnv_node_to_numnode(NODE *ndi)
{
    if (is_number(ndi))
    {
        return ndi;
    }

    ndi = cnv_node_to_strnode(ndi);
    if (ndi == Unbound) 
    {
        return Unbound;
    }

    int dr;
    if (((getstrlen(ndi)) < MAX_NUMBER) && (dr = numberp(ndi)))
    {
        char buffer[MAX_NUMBER];
        char *s = buffer;

        // Copy the contents of the string node into buffer
        if (backslashed(ndi))
        {
            noparity_strnzcpy(s, getstrptr(ndi), getstrlen(ndi));
        }
        else
        {
            strnzcpy(s, getstrptr(ndi), getstrlen(ndi));
        }

        // If the string was an explicit positive number,
        // as in "+123" instead of "123", then we skip past the "+".
        if (*s == '+') 
        {
            ++s;
        }

        // If the string ends in a decimal point, as in "123.", then
        // remove the decimal point.
        if (buffer[getstrlen(ndi) - 1] == '.') 
        {
            buffer[getstrlen(ndi) - 1] = '\0';
        }

        // Convert the string to a number node.
        NODE *val;
        if (dr - 1 || getstrlen(ndi) > 9)
        {
            val = make_floatnode(atof(s));
        }
        else
        {
            val = make_intnode(atol(s));
        }
        gcref(ndi);
        return val;
    }
    else
    {
        gcref(ndi);
        return Unbound;
    }
}

// Returns a string node that has the stringized form of "nd".
//
// If nd is already a string node, then it is returned.
//
// If nd is not already a string, but can be converted to one, then new node is
// created with a reference count of 0.
//
// Returns Unbound if nd cannot be converted to a word node.
//
// If "nd" can be guaranteed by the caller to have a non-zero reference count,
// such as if it's an argument in an argument list, then the returned node
// can safely freed with gcref().  This handles all cases listed above.
NODE *cnv_node_to_strnode(NODE *nd)
{
    if (nd == Unbound || is_aggregate(nd))
    {
        return Unbound;
    }

    char s[MAX_NUMBER];
    switch (nodetype(nd))
    {
    case STRING:
    case BACKSLASH_STRING:
    case VBAR_STRING:
        // the node is already a string
        return nd;

    case CASEOBJ:
        return strnode__caseobj(nd);

    case QUOTE:
        nd = vref(cnv_node_to_strnode(node__quote(nd)));
        assign(
            nd, 
            make_strnode(getstrptr(nd), getstrlen(nd) + 1, nodetype(nd), quote_strnzcpy));
        unref(nd);
        return nd;
         
    case COLON:
        nd = vref(cnv_node_to_strnode(node__colon(nd)));
        assign(
            nd, 
            make_strnode(getstrptr(nd), getstrlen(nd) + 1, nodetype(nd), colon_strnzcpy));
        unref(nd);
        return nd;

    case INTEGER:
        sprintf(s, "%ld", getint(nd));
        return make_strnode(s);

    case FLOATINGPOINT:
        sprintf(s, "%0.15g", getfloat(nd));
        return make_strnode(s);
    }

    /*NOTREACHED*/
    assert(0);
    return NIL;
}

NODE *make_static_strnode(const char *strptr)
{
    NODE *strnode = newnode(STRING);

    setstrptr(strnode, strptr);
    setstrhead(strnode, NULL);
    setstrlen(strnode, (int) strlen(strptr));
    return (strnode);
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

NODE *cons_list()
{
    return NIL;
}

NODE *cons_list(NODE * node1)
{
    return cons(node1, NIL);
}

NODE *cons_list(NODE * node1, NODE * node2)
{
    return cons(
        node1, 
        cons_list(node2));
}

NODE *cons_list(NODE * node1, NODE * node2, NODE * node3)
{
    return cons(
        node1, 
        cons_list(node2, node3));
}

NODE *cons_list(NODE * node1, NODE * node2, NODE * node3, NODE * node4)
{
    return cons(
        node1, 
        cons_list(node2, node3, node4));
}

NODE *cons_list(NODE * node1, NODE * node2, NODE * node3, NODE * node4, NODE * node5)
{
    return cons(
        node1, 
        cons_list(node2, node3, node4, node5));
}

int list_length(const NODE * List)
{
    int length = 0;

    for (const NODE * current_node = List;
         current_node != NIL;
         current_node = cdr(current_node))
    {
        length++;
    }

    return length;
}

// Constructs an array node with "len" elements, all of which are NIL.
// Returns Unbound when out of memory.
NODE *make_array(int len)
{
    assert(0 <= len);  // can't have a negative length array

#ifdef BORLAND
        // Borland's calloc() doesn't handle overflow,
        // so we must do it ourselves.
        if (sizeof(NODE*) * len + 100 < len)
        {
            // There would be an integer overflow when
            // calculating the size of the internal array.
            err_logo(OUT_OF_MEM, NIL);
            return Unbound;
        }
#endif


    NODE ** data;
    if (len != 0)
    {
        // calloc() handles both integer overflow and
        // initializing each of the members to NIL.
        data = (NODE **) calloc(sizeof *data, len);
        if (data == NULL)
        {
            // The array is too large to allocate.
            err_logo(OUT_OF_MEM, NIL);
            return Unbound;
        }
    }
    else
    {
        data = NULL;
    }

    NODE* node = newnode(ARRAY);
    setarrptr(node, data);
    setarrorg(node, 1);
    setarrdim(node, len);
    return node;
}

NODE *llowercase(NODE *args)
{
    NODE * arg = string_arg(args);
    if (NOT_THROWING)
    {
        return make_strnode(getstrptr(arg), getstrlen(arg), nodetype(arg), low_strnzcpy);
    }
    return Unbound;
}

NODE *luppercase(NODE *args)
{
    NODE * arg = string_arg(args);
    if (NOT_THROWING)
    {
        return make_strnode(getstrptr(arg), getstrlen(arg), nodetype(arg), cap_strnzcpy);
    }
    return Unbound;
}

/* property list stuff */
NODE *getprop(NODE *plist, NODE *name, bool before)
{
    bool caseig = isCaseIgnored();

    NODE *prev = NIL;
    while (plist != NIL)
    {
        if (compare_node(name, car(plist), caseig) == 0)
        {
            return (before ? prev : plist);
        }
        prev = plist;
        plist = cddr(plist);
    }
    return NIL;
}

NODE *lgprop(NODE *args)
{
    NODE *val = NIL;

    NODE * plname = string_arg(args);
    NODE * pname = string_arg(cdr(args));
    if (NOT_THROWING)
    {
        plname = intern(plname);

        NODE * plist = plist__caseobj(plname);
        if (plist != NIL)
        {
            val = getprop(plist, pname, FALSE);
        }
        if (val != NIL)
        {
            return cadr(val);
        }
    }
    return NIL;
}

NODE *lpprop(NODE *args)
{
    NODE *val = NIL;

    NODE * plname = string_arg(args);
    NODE * pname = string_arg(cdr(args));
    NODE * newval = car(cddr(args));
    if (NOT_THROWING)
    {
        plname = intern(plname);
        if (flag__caseobj(plname, PLIST_TRACED))
        {
            // This property list is being traced.
            // Trace the pprop to the write stream.
            NODE * propertylist  = vref(maybe_quote(plname));
            NODE * propertyname  = vref(maybe_quote(pname));
            NODE * propertyvalue = vref(maybe_quote(newval));

            ndprintf(
                g_Writer.GetStream(), 
                LOCALIZED_TRACING_PPROP, 
                propertylist,
                propertyname,
                propertyvalue);

            deref(propertylist);
            deref(propertyname);
            deref(propertyvalue);
            
            // trace the name of the function where the pprop was run.
            if (ufun != NIL)
            {
                ndprintf(
                    g_Writer.GetStream(), 
                    LOCALIZED_TRACING_LOCATION,
                    ufun, 
                    this_line);
            }
            new_line(g_Writer.GetStream());
        }

        NODE * plist = plist__caseobj(plname);
        if (plist != NIL)
        {
            val = getprop(plist, pname, FALSE);
        }
        if (val != NIL)
        {
            setcar(cdr(val), newval);
        }
        else
        {
            setplist__caseobj(plname, cons(pname, cons(newval, plist)));
        }
    }
    return Unbound;
}

NODE *lremprop(NODE *args)
{
    NODE * plname = string_arg(args);
    NODE * pname = string_arg(cdr(args));
    if (NOT_THROWING)
    {
        plname = intern(plname);
        NODE * plist = plist__caseobj(plname);
        if (plist != NIL)
        {
            bool caseig = isCaseIgnored();
            if (compare_node(car(plist), pname, caseig) == 0)
            {
                setplist__caseobj(plname, cddr(plist));
            }
            else
            {
                NODE * val = getprop(plist, pname, true);
                if (val != NIL)
                {
                    setcdr(cdr(val), cddr(cddr(val)));
                }
            }
        }
    }
    return Unbound;
}

static
NODE *copy_list(NODE *arg)
{
    CAppendableList copy;

    while (arg != NIL)
    {
        copy.AppendElement(car(arg));
        arg = cdr(arg);
    }

    return copy.GetList();
}

NODE *lplist(NODE *args)
{
    NODE *val = NIL;

    NODE * plname = string_arg(args);
    if (NOT_THROWING)
    {
        plname = intern(plname);
        NODE * plist = plist__caseobj(plname);
        val = copy_list(plist);
    }
    return val;
}


NODE * llogoversion(NODE * args)
{
    NODE * application_name    = make_static_strnode(LOCALIZED_GENERAL_PRODUCTNAME);
    NODE * application_version = make_static_strnode(FMSLOGO_VERSION);
    NODE * os_name             = make_static_strnode("Windows");
    NODE * locale              = make_intnode(LOCALE);

    return cons_list(
        application_name,
        application_version,
        os_name,
        locale);
}

bool variableIsTrue(NODE *variable) 
{
    return Truex.Equals(valnode__caseobj(variable));
}

// Returns the value of :CASEIGNOREDP, according to the following rules
// If CASEIGNOREDP is defined, then its value is used.
// Otherwise, if this is a non-English build and the non-English version
// is defined, then its value is used.
// Otherwise, it returns true.
bool isCaseIgnored()
{
    // Get the value of the English version or the localized version,
    // depending on which is defined.
    NODE * value = Caseignoredp.GetValue();
    if (value != Unbound)
    {
        // CASEIGNOREDP is defined.  Return if it's true.
        return Truex.Equals(value);
    }

    // Neither the English nor the alternate is defined,
    // so we use the default value of true.
    return true;
}

// Returns the value of :REDEFP, according to the following rules:
// If REDEFP is defined to be "true, then its value is used.
// Otherwise, if this is a non-English build and the non-English version
// is defined, then its value is used.
// Otherwise, it returns false.
bool canRedefinePrimitives()
{
    // Get the value of the English version or the localized version,
    // depending on which is defined.
    NODE * value = Redefp.GetValue();
    if (value != Unbound)
    {
        // REDEFP is defined.  Return if it's true.
        return Truex.Equals(value);
    }

    // Neither the English nor the alternate is defined,
    // so we use the default value of false.
    return false;
}
