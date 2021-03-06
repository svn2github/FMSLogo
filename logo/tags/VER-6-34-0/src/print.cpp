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

void print_char(FILE *strm, MESSAGETYPE type, char ch)
{
    if (strm != NULL)
    {
        // printing to a file stream
        if (strm == stdout)
        {
            // FMSLogo isn't a command-line application, so printing
            // to "stdout" really goes to the commander history.
            putcombochar(type, ch);
            if (dribblestream != NULL)
            {
                putc(ch, dribblestream);
            }
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

void print_space(FILE *strm, MESSAGETYPE type)
{
    print_char(strm, type, ' ');
}

void ndprintf(FILE *strm, MESSAGETYPE type, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    char ch;
    while ((ch = *fmt++) != '\0')
    {
        if (ch == '%')
        {
            ch = *fmt++;
            if (ch == 's') // show
            {
                print_node(strm, type, va_arg(ap, NODE *));
            }
            else if (ch == 'p')  // print
            {
                /* print */
                NODE * nd = va_arg(ap, NODE *);
                if (is_list(nd))
                {
                    print_helper(strm, type, nd);
                }
                else
                {
                    print_node(strm, type, nd);
                }
            }
            else if (ch == 't') // text
            {
                char *cp = va_arg(ap, char *);
                while (ch = *cp++)
                {
                    print_char(strm, type, ch);
                }
            }
            else
            {
                print_char(strm, type, '%');
                print_char(strm, type, ch);
            }
        }
        else
        {
            print_char(strm, type, ch);
        }
    }

    va_end(ap);
}

static
void
real_print_node(
    FILE       * strm,
    MESSAGETYPE  type,
    const NODE * nd,
    int          depth,
    int          width
    );

static
void real_print_helper(FILE *strm, MESSAGETYPE type, const NODE *ndlist, int depth, int width)
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
        real_print_node(strm, type, arg, depth, width);
        if (ndlist != NIL)
        {
            print_space(strm, type);
            if (--wid == 0)
            {
                ndprintf(strm, type, "...");
                break;
            }
        }
    }
}


// Prints a node to a file stream in a way that is consistent
// with how FMSLogo parses nodes.
//
//   strm - the file stream.
//   type - the type of message that is being printed
//   nd - the node to print
//   depth - how "deep" to go (how many elements of a list)
//   width - how many bytes to print at most ???
static
void
real_print_node(
    FILE       * strm,
    MESSAGETYPE  type,
    const NODE * nd,
    int          depth,
    int          width
    )
{
    NODETYPES ndty;

    if (depth == 0)
    {
        ndprintf(strm, type, "...");
    }
    else if (nd == NIL)
    {
        print_char(strm, type, '[');
        print_char(strm, type, ']');
    }
    else if (nd == Unbound)
    {
        ndprintf(strm, type, LOCALIZED_UNBOUND);
    }
    else if ((ndty = nodetype(nd)) & NT_PRIM)
    {
        ndprintf(strm, type, "PRIM");
    }
    else if (ndty & NT_LIST)
    {
        print_char(strm, type, '[');
        real_print_helper(strm, type, nd, depth - 1, width);
        print_char(strm, type, ']');
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

        print_char(strm, type, '{');

        // print each item in the array
        NODE **pp = getarrptr(nd);
        int i = 0;
        while (i < wid)
        {
            real_print_node(strm, type, *pp++, depth - 1, width);
            if (++i < dim) 
            {
                print_space(strm, type);
            }
        }
        if (wid < dim) 
        {
            ndprintf(strm, type, "...");
        }
        print_char(strm, type, '}');

        // print the origin
        if (print_backslashes && (getarrorg(nd) != 1))
        {
            char origin[32];
            sprintf(origin, "@%d", getarrorg(nd));
            ndprintf(strm, type, origin);
        }
    }
    else if (ndty == QUOTE)
    {
        print_char(strm, type, '\"');
        real_print_node(strm, type, car(nd), width - 1, depth);
    }
    else if (ndty == COLON)
    {
        print_char(strm, type, ':');
        real_print_node(strm, type, car(nd), width - 1, depth);
    }
    else if (ndty == FLOATINGPOINT)
    {
        char buffer[MAX_NUMBER];
        sprintf(buffer, "%0.15g", getfloat(nd));

        // REVISIT: is it okay to ignore the width parameter?
        for (const char *cp = buffer; *cp != '\0'; cp++)
        {
            print_char(strm, type, *cp);
        }
    }
    else if (ndty == INTEGER)
    {
        char buffer[MAX_NUMBER];
        sprintf(buffer, "%ld", getint(nd));

        // REVISIT: is it okay to ignore the width parameter?
        for (const char *cp = buffer; *cp != '\0'; cp++)
        {
            print_char(strm, type, *cp);
        }
    }
    else if (ndty == CASEOBJ)
    {
        real_print_node(strm, type, strnode__caseobj(nd), depth, width);
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
                print_char(strm, type, *cp++);
            }
        }
        else if (!print_backslashes)
        {
            for (int i = 0; i < totalCharsToPrint; i++)
            {
                print_char(strm, type, ecma_clear(*cp++));
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
                    print_char(strm, type, *cp++);
                    totalCharsToPrint--;
                }
                print_char(strm, type, '|');
                for (i = 0; i < totalCharsToPrint; i++)
                {
                    char ch = ecma_clear(*cp++);

                    // Even in vbars, there are some characters
                    // that must be escaped.
                    if (ch == '|' || ch == '\\')
                    {
                        print_char(strm, type, '\\');
                    }
                    print_char(strm, type, ch);
                }
                print_char(strm, type, '|');
            }
            else 
            {
                // word was not in vbars
                for (i = 0; i < totalCharsToPrint; i++)
                {
                    if (is_special_character(*cp))
                    {
                        // *cp must be escaped with a backslash
                        print_char(strm, type, '\\');
                    }
                    print_char(strm, type, *cp++);
                }
            }
        }

        if (dots)
        {
            ndprintf(strm, type, "...");
        }
    }
}

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

void print_helper(FILE *strm, MESSAGETYPE type, NODE *nd)
{
    real_print_helper(
        strm,
        type,
        nd,
        find_limit(Printdepthlimit),
        find_limit(Printwidthlimit));
}

void print_node(FILE *strm, MESSAGETYPE type, NODE *nd)
{
    real_print_node(
        strm,
        type,
        nd,
        find_limit(Printdepthlimit),
        find_limit(Printwidthlimit));
}

void print_nobrak(FILE *strm, MESSAGETYPE type, NODE *nd)
{
    if (is_list(nd))
    {
        print_helper(strm, type, nd);
    }
    else 
    {
        print_node(strm, type, nd);
    }
}

void new_line(FILE *strm, MESSAGETYPE type)
{
    print_char(strm, type, '\n');
}

NODE *lshow(NODE *args)
{
    print_helper(g_Writer.GetStream(), MESSAGETYPE_Normal, args);
    new_line(g_Writer.GetStream(), MESSAGETYPE_Normal);
    return Unbound;
}

static
void type_helper(NODE *args, bool print_space_between_arguments)
{
    while (args != NIL)
    {
        NODE * arg = car(args);

        print_nobrak(g_Writer.GetStream(), MESSAGETYPE_Normal, arg);

        args = cdr(args);
        if (print_space_between_arguments && (args != NIL))
        {
            print_space(g_Writer.GetStream(), MESSAGETYPE_Normal);
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
    new_line(g_Writer.GetStream(), MESSAGETYPE_Normal);
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


// Prints a node to a string, as would happen with PRINT, using
// the given limits on width and depth.
// Returns the number of bytes needed to print the entire string for Node,
// including the NUL-terminator.
size_t
PrintNodeToString(
    const NODE * Node,
    char *       Buffer,
    size_t       BufferLength,
    int          PrintDepthLimit,
    int          PrintWidthLimit
    )
{
    // Initialize the printing engine to print to Buffer
    InitializeStringPrintInformation(Buffer, BufferLength);

    // Print the node
    if (is_list(Node))
    {
        real_print_helper(
            NULL,
            MESSAGETYPE_Normal,
            Node,
            PrintDepthLimit,
            PrintWidthLimit);
    }
    else
    {
        real_print_node(
            NULL,
            MESSAGETYPE_Normal,
            Node,
            PrintDepthLimit,
            PrintWidthLimit);
    }

    // NUL-terminate the string and return the total bytes needed.
    return FinalizeStringPrintInformation();
}


// Prints a node to a string, as would happen with PRINT if no limits
// were placed on its width or depth.
// Returns the number of bytes needed to print the entire string for Node,
// including the NUL-terminator.
size_t
PrintNodeToString(
    const NODE * Node,
    char *       Buffer,
    size_t       BufferLength
    )
{
    return PrintNodeToString(Node, Buffer, BufferLength, -1, -1);
}

