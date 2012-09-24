/*
*      print.cpp         logo printing module                    dvb
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

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

#include "unix.h"
#include "parse.h"
#include "print.h"
#include "logocore.h"
#include "logodata.h"
#include "ibmterm.h"
#include "init.h"
#include "eval.h"
#include "files.h"
#include "debugheap.h"

#include "localizedstrings.h"

// structures
struct STRING_PRINT_INFORMATION
{
    size_t  TotalBytesNeeded;
    size_t  BufferLength;
    char  * Buffer;
};

// global variable
static STRING_PRINT_INFORMATION g_StringPrintInformation;

bool print_backslashes = false;


void update_coords(char /*ch*/)
{
}

void print_char(FILE *strm, char ch)
{
    if (strm != NULL)
    {
        // printing to a file stream
        if (strm == stdout)
        {
            putcombochar(ch);
            if (dribblestream != NULL)
            {
                putc(ch, dribblestream);
            }
            update_coords(ch);
        }
        else
        {
            putc(ch, strm);
        }
    }
    else
    {
        // printing to string
        if (g_StringPrintInformation.TotalBytesNeeded + 1 < g_StringPrintInformation.BufferLength)
        {
            g_StringPrintInformation.Buffer[g_StringPrintInformation.TotalBytesNeeded] = ch;
        }
        g_StringPrintInformation.TotalBytesNeeded++;
    }
}

void print_space(FILE *strm)
{
    print_char(strm, ' ');
}

/*VARARGS2*/
void ndprintf(FILE *strm, const char *fmt, ...)
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
                {
                    print_node(strm, nd);
                }
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
        else 
        {
            print_char(strm, ch);
        }
    }
    va_end(ap);
}

static
void real_print_helper(FILE *strm, const NODE *ndlist, int depth, int width)
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
void real_print_node(FILE *strm, const NODE *nd, int depth, int width)
{
    NODETYPES ndty;

    if (depth == 0)
    {
        ndprintf(strm, "...");
    }
    else if (nd == NIL)
    {
        print_char(strm, '[');
        print_char(strm, ']');
    }
    else if (nd == Unbound)
    {
        ndprintf(strm, LOCALIZED_UNBOUND);
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
        int dim = getarrdim(nd);

        // figure out how many items to print
        int wid;
        if (width < 0) 
        {
            wid = dim;
        }
        else 
        {
            wid = (dim > width ? width : dim);
        }

        print_char(strm, '{');

        // print each item in the array
        NODE **pp = getarrptr(nd);
        int i = 0;
        while (i < wid)
        {
            real_print_node(strm, *pp++, depth - 1, width);
            if (++i < dim) 
            {
                print_space(strm);
            }
        }
        if (wid < dim) 
        {
            ndprintf(strm, "...");
        }
        print_char(strm, '}');

        // print the origin
        if (print_backslashes && (getarrorg(nd) != 1))
        {
            char origin[32];
            sprintf(origin, "@%d", getarrorg(nd));
            ndprintf(strm, origin);
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
    else if (ndty == FLOATINGPOINT)
    {
        char buffer[MAX_NUMBER];
        sprintf(buffer, "%0.15g", getfloat(nd));

        // REVISIT: is it okay to ignore the width parameter?
        for (const char *cp = buffer; *cp != '\0'; cp++)
        {
            print_char(strm, *cp);
        }
    }
    else if (ndty == INTEGER)
    {
        char buffer[MAX_NUMBER];
        sprintf(buffer, "%ld", getint(nd));

        // REVISIT: is it okay to ignore the width parameter?
        for (const char *cp = buffer; *cp != '\0'; cp++)
        {
            print_char(strm, *cp);
        }
    }
    else if (ndty == CASEOBJ)
    {
        real_print_node(strm, strnode__caseobj(nd), depth, width);
    }
    else
    {
        assert(is_string(nd));

        // figure out how many charaters to print
        int totalCharsToPrint;
        if (width < 0) 
        {
            totalCharsToPrint = getstrlen(nd);
        }
        else
        {
            totalCharsToPrint = max(width, 10);
            totalCharsToPrint = min(totalCharsToPrint, getstrlen(nd));
        }

        // should we print some elipses at the end?
        bool dots = false;
        if (totalCharsToPrint < getstrlen(nd))
        {
            dots = true;
        }

        // print totalCharsToPrint characters of nd
        const char *cp = getstrptr(nd);
        if (!backslashed(nd))
        {
            for (int i = 0; i < totalCharsToPrint; i++)
            {
                print_char(strm, *cp++);
            }
        }
        else if (!print_backslashes)
        {
            for (int i = 0; i < totalCharsToPrint; i++)
            {
                print_char(strm, ecma_clear(*cp++));
            }
        }
        else
        {
            // determine if the word was in vbars
            int i;
            for (i = 0; i < totalCharsToPrint; i++)
            {
                if (ecma_get(cp[i])) 
                {
                    break;
                }
            }

            if (i < totalCharsToPrint)
            {
                // word was in vbars
                if (strchr("\":", *cp))
                {
                    print_char(strm, *cp++);
                    totalCharsToPrint--;
                }
                print_char(strm, '|');
                for (i = 0; i < totalCharsToPrint; i++)
                {
                    char ch = ecma_clear(*cp++);

                    // Even in vbars, there are some characters
                    // that must be escaped.
                    if (ch == '|' || ch == '\\')
                    {
                        print_char(strm, '\\');
                    }
                    print_char(strm, ch);
                }
                print_char(strm, '|');
            }
            else 
            {
                // word was not in vbars
                for (i = 0; i < totalCharsToPrint; i++)
                {
                    if (is_special_character(*cp))
                    {
                        // *cp must be escaped with a backslash
                        print_char(strm, '\\');
                    }
                    print_char(strm, *cp++);
                }
            }
        }

        if (dots)
        {
            ndprintf(strm, "...");
        }
    }
}

static
int find_limit(const CLocalizedNode & Node)
{
    NODE * nd = cnv_node_to_numnode(Node.GetValue());

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
    if (is_list(nd))
    {
        print_helper(strm, nd);
    }
    else 
    {
        print_node(strm, nd);
    }
}

void new_line(FILE *strm)
{
    print_char(strm, '\n');
}

NODE *lshow(NODE *args)
{
    print_helper(g_Writer.GetStream(), args);
    new_line(g_Writer.GetStream());
    return Unbound;
}

static
void type_helper(NODE *args, bool print_space_between_arguments)
{
    while (args != NIL)
    {
        NODE * arg = car(args);

        print_nobrak(g_Writer.GetStream(), arg);

        args = cdr(args);
        if (print_space_between_arguments && (args != NIL))
        {
            print_space(g_Writer.GetStream());
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
    new_line(g_Writer.GetStream());
    return Unbound;
}

// Initializes the printing engine to print to Buffer.
void
InitializeStringPrintInformation(
    char * Buffer,
    size_t BufferLength
    )
{
    g_StringPrintInformation.TotalBytesNeeded = 0;
    g_StringPrintInformation.Buffer           = Buffer;
    g_StringPrintInformation.BufferLength     = BufferLength;
}

// NUL-terminate the string and return how many bytes would be
// required to hold the entire print job.
size_t FinalizeStringPrintInformation()
{
    // NUL-terminate the string
    if (g_StringPrintInformation.TotalBytesNeeded + 1 < g_StringPrintInformation.BufferLength)
    {
        // The string fit within the buffer.
        // NUL-terminate it at the end of what we wrote.
        g_StringPrintInformation.Buffer[g_StringPrintInformation.TotalBytesNeeded] = '\0';
    }
    else if (g_StringPrintInformation.BufferLength != 0)
    {
        // The string didn't fit within the buffer.
        // NUL-terminate it at the end of the buffer.
        g_StringPrintInformation.Buffer[g_StringPrintInformation.BufferLength - 1] = '\0';
    }
    else
    {
        // No buffer was given, so we can't NUL-terminate anything.
    }
    g_StringPrintInformation.TotalBytesNeeded++;

    // Return the total bytes needed.
    return g_StringPrintInformation.TotalBytesNeeded;
}


// Prints a node to a string, as would happen with PRINT if no limits
// were placed on its width or depth.
// Returns the number of bytes needed to entire string for of Node, including
// the NUL-terminator.
size_t
PrintNodeToString(
    const NODE * Node,
    char *       Buffer,
    size_t       BufferLength
    )
{
    // Initialize the printing engine to print to Buffer
    InitializeStringPrintInformation(Buffer, BufferLength);

    // Print the node
    if (is_list(Node))
    {
        real_print_helper(NULL, Node, -1, -1);
    }
    else
    {
        real_print_node(NULL, Node, -1, -1);
    }

    // NUL-terminate the string and return the total bytes needed.
    return FinalizeStringPrintInformation();
}
