/*
 *      files.cpp         logo file management module             dvb
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
#include <windows.h>
#include <setjmp.h>

#include "files.h"
#include "fileswnd.h"
#include "logocore.h"
#include "mem.h"
#include "init.h"
#include "main.h"
#include "parse.h"
#include "error.h"
#include "logomath.h"
#include "eval.h"
#include "coms.h"
#include "lists.h"
#include "wrksp.h"
#include "print.h"
#include "unix.h"
#include "graphics.h"
#include "startup.h"
#include "screenwindow.h"
#include "cursor.h"
#include "debugheap.h"

#include "localizedstrings.h"

class CFileListNode
{
public:
    CFileListNode * m_Next;
    NODE          * m_FileNameNode;
    bool            m_IsBinaryStream;
    FILE *          m_FilePtr;

    CFileListNode(NODE * FileNameNode, FILE * FilePtr, bool IsBinaryStream);
    ~CFileListNode();

private:
    CFileListNode();
};

NODE *current_line = NIL;       // current line to be parsed

static CFileListNode * g_OpenFiles;

CFileStream g_Reader(stdin);
CFileStream g_Writer(stdout);

CFileListNode::CFileListNode(
    NODE * FileNameNode,
    FILE * FilePtr,
    bool   IsBinaryStream
    ) :
    m_Next(NULL),
    m_FileNameNode(vref(FileNameNode)),
    m_IsBinaryStream(IsBinaryStream),
    m_FilePtr(FilePtr)
{
}

CFileListNode::~CFileListNode()
{
    // close the file, if it's still open
    if (m_FilePtr != NULL)
    {
        fclose(m_FilePtr);
    }

    // release the filename
    deref(m_FileNameNode);
}

static
FILE *open_file(NODE *arg, const char *access)
{
    assert(arg == NIL || getrefcnt(arg) != 0);

    NODE * filenameNode = cnv_node_to_strnode(arg);
    if (filenameNode == Unbound) 
    {
        return NULL;
    }

    char * fnstr = (char *) malloc((size_t) getstrlen(filenameNode) + 1);
    strnzcpy(fnstr, getstrptr(filenameNode), getstrlen(filenameNode));

    FILE *tstrm;
    if (stricmp(fnstr, "clipboard") == 0)
    {
        if (stricmp(access, "r") == 0)
        {
            ::OpenClipboard(GetMainWindow());

            HANDLE HText = ::GetClipboardData(CF_TEXT);

            if (HText)
            {
                LPSTR lpText = (LPSTR) GlobalLock(HText);

                FILE *clipstrm = fopen(TempClipName, "w");
                if (clipstrm != NULL)
                {
                    fwrite(lpText, sizeof(char), GlobalSize(HText), clipstrm);
                    fclose(clipstrm);
                }

                GlobalUnlock(HText);
            }
            else
            {
                FILE *clipstrm = fopen(TempClipName, "w");
                if (clipstrm != NULL)
                {
                    fputs(LOCALIZED_ERROR_CLIPBOARDISEMPTY, clipstrm);
                    fclose(clipstrm);
                }
            }

            ::CloseClipboard();

            tstrm = fopen(TempClipName, access);
        }
        else if (stricmp(access, "w") == 0)
        {
            tstrm = fopen(TempClipName, access);
        }
    }
    else
    {
        tstrm = fopen(fnstr, access);
    }

    if (tstrm != NULL)
    {
        if (strncmp(access, "r+", 2) == 0)
        {
            // When we open in "r+", we want to read/write from the
            // end of the file until the user seeks somewhere else.
            // This mode is only used from OPENUPDATE.
            fseek(tstrm, 0, SEEK_END);
        }
    }

    gcref(filenameNode);
    free(fnstr);
    return tstrm;
}

NODE *ldribble(NODE *arg)
{
    if (dribblestream != NULL)
    {
        err_logo(ALREADY_DRIBBLING, NIL);
    }
    else
    {
        dribblestream = open_file(car(arg), "w");
        if (dribblestream == NULL) 
        {
            err_logo(FILE_ERROR, NIL);
        }
    }

    return Unbound;
}

NODE *lnodribble(NODE *)
{
    if (dribblestream != NULL)
    {
        fclose(dribblestream);
        dribblestream = NULL;
    }
    return Unbound;
}

// Searches the list of open files for the node that matches
// the given filename.
// FileNameNode - The name of the file stream to look for.
// Remove       - true, if the file should be removed from the
//                list of open files.  false, otherwise.
// IsBinary     - If not NULL and a file is found, this is set to whether
//                or not the file was opened as a binary stream.
static
FILE *
FindOrRemoveFile(
    NODE * FileNameNode,
    bool   Remove,
    bool * IsBinary
    )
{
    FILE *fp = NULL;

    for (CFileListNode ** nodePtr = &g_OpenFiles;
         (*nodePtr) != NULL;
         nodePtr = &(*nodePtr)->m_Next)
    {
        CFileListNode * node = *nodePtr;
        if (compare_node(FileNameNode, node->m_FileNameNode, false) == 0)
        {
            // found it.
            // Return the FILE* and whether or not it's a binary stream.
            fp = node->m_FilePtr;
            if (IsBinary != NULL)
            {
                *IsBinary = node->m_IsBinaryStream;
            }

            if (Remove)
            {
                node->m_FilePtr = NULL;
                *nodePtr = node->m_Next;
                delete node;
            }
            break;
        }
    }

    return fp;
}

static
FILE *
FindFile(
    NODE * FileNameNode,
    bool * IsBinary
    )
{
    return FindOrRemoveFile(FileNameNode, false, IsBinary);
}

static
FILE *
FindFile(
    NODE * FileNameNode
    )
{
    return FindOrRemoveFile(FileNameNode, false, NULL);
}

static
FILE *
RemoveFile(
    NODE * FileNameNode
    )
{
    return FindOrRemoveFile(FileNameNode, true, NULL);
}

// Arguments   - The Logo arguments passed into the file operation.
//               The first argument is the filename.
//               The first argument is the optional "BinaryMode" argument.
// DefaultMode - The mode to use if Arguments does not indicate to use a binary mode
// BinaryMode  - The mode to use if Arguments does indicates to use a binary mode
static
NODE *
open_helper(
    NODE       *Arguments, 
    const char *DefaultMode,
    const char *BinaryMode
    )
{
    bool useBinaryMode = false;

    if (cdr(Arguments) != NIL)
    {
        useBinaryMode = boolean_arg(cdr(Arguments));
    }

    if (NOT_THROWING)
    {
        const char * mode = DefaultMode;
        if (useBinaryMode)
        {
            mode = BinaryMode;
        }

        FILE * newFileStream;
        NODE * fileNameNode = car(Arguments);
        if (FindFile(fileNameNode) != NULL)
        {
            err_logo(
                FILE_ERROR, 
                make_static_strnode(LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN));
        }
        else if ((newFileStream = open_file(fileNameNode, mode)) != NULL)
        {
            // create a new node for this file
            CFileListNode * newNode = new CFileListNode(
                fileNameNode,
                newFileStream,
                useBinaryMode);

            // add this to the front of the list
            newNode->m_Next = g_OpenFiles;
            g_OpenFiles     = newNode;
        }
        else
        {
            err_logo(
                FILE_ERROR, 
                make_static_strnode(LOCALIZED_ERROR_FILESYSTEM_CANTOPEN));
        }
    }
    return Unbound;
}

NODE *lopenread(NODE *args)
{
    return open_helper(args, "r", "rb");
}

NODE *lopenwrite(NODE *args)
{
    return open_helper(args, "w", "wb");
}

NODE *lopenappend(NODE *args)
{
    return open_helper(args, "a", "ab");
}

NODE *lopenupdate(NODE *args)
{
    return open_helper(args, "r+", "r+b");
}

NODE *lallopen(NODE *)
{
    NODE * allopen = NIL;
    for (CFileListNode * node = g_OpenFiles; node != NULL; node = node->m_Next)
    {
        allopen = cons(node->m_FileNameNode, allopen);
    }

    return allopen;
}

NODE *lclose(NODE *arg)
{
    NODE * filename = string_arg(arg);
    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    FILE *filePtr = RemoveFile(filename);
    if (filePtr == NULL)
    {
        err_logo(
            FILE_ERROR, 
            make_static_strnode(LOCALIZED_ERROR_FILESYSTEM_NOTOPEN));

        return Unbound;
    }

    // close the file stream
    fclose(filePtr);

    char * fnstr = (char *) malloc((size_t) getstrlen(filename) + 1);
    strnzcpy(fnstr, getstrptr(filename), getstrlen(filename));

    if (stricmp(fnstr, "clipboard") == 0)
    {
        ::OpenClipboard(GetMainWindow());

        ::EmptyClipboard();

        FILE *clipstrm = fopen(TempClipName, "rb");
        if (clipstrm != NULL)
        {
            fseek(clipstrm, 0, SEEK_END);
            LONG iSize = ftell(clipstrm);
            fseek(clipstrm, 0, SEEK_SET);

            HGLOBAL HText = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, iSize);
            LPSTR lpText = (LPSTR) GlobalLock(HText);

            fread( lpText, sizeof(char), GlobalSize(HText), clipstrm);
            fclose(clipstrm);
            
            GlobalUnlock(HText);
            
            ::SetClipboardData(CF_TEXT, HText);

            ::CloseClipboard();
        }

        remove(TempClipName);
    }

    free(fnstr);

    // If we closed the active reader or write stream,
    // then we should reset the stream to the default
    // (either stdin or stdout) to so that future
    // reads/writes won't crash.
    if (g_Writer.IsNamed(filename))
    {
        g_Writer.ResetToDefaultStream();
    }

    if (g_Reader.IsNamed(filename))
    {
        g_Reader.ResetToDefaultStream();
    }

    return Unbound;
}

CFileStream::CFileStream(
    FILE * DefaultFileStream
    ) :
    m_Name(NIL),
    m_Stream(DefaultFileStream),
    m_DefaultStream(DefaultFileStream),
    m_StreamIsBinary(false)
{
}

void
CFileStream::ResetToDefaultStream()
{
    deref(m_Name);
    m_Name = NIL;

    m_Stream = m_DefaultStream;
    m_StreamIsBinary = false;
}

void
CFileStream::SetStreamToOpenFile(
    NODE * FileName
    )
{
    bool   filePtrIsBinaryStream;
    FILE * filePtr;

    if (FileName == NIL)
    {
        // reset to the default stream
        ResetToDefaultStream();
    }
    else if ((filePtr = FindFile(FileName, &filePtrIsBinaryStream)) != NULL)
    {
        m_Stream         = filePtr;
        m_StreamIsBinary = filePtrIsBinaryStream;
        m_Name           = reref(m_Name, FileName);
    }
    else
    {
        err_logo(
            FILE_ERROR, 
            make_static_strnode(LOCALIZED_ERROR_FILESYSTEM_NOTOPEN));
    }
}

bool
CFileStream::IsNamed(
    NODE * FileName
    ) const
{
    return compare_node(FileName, m_Name, false) == 0;
}

bool
CFileStream::IsBinary() const
{
    return m_StreamIsBinary;
}

NODE *
CFileStream::GetName() const
{
    return m_Name;
}

NODE *
CFileStream::GetPosition() const
{
    return make_intnode(ftell(m_Stream));
}

void
CFileStream::SetPosition(
    NODE * Arguments
    )
{
    NODE *val = nonnegative_int_arg(Arguments);

    if (NOT_THROWING)
    {
        fseek(m_Stream, getint(val), SEEK_SET);
    }
}


NODE *lsetwrite(NODE *arg)
{
    g_Writer.SetStreamToOpenFile(car(arg));
    return Unbound;
}

NODE *lsetread(NODE *arg)
{
    g_Reader.SetStreamToOpenFile(car(arg));
    return Unbound;
}

NODE *lreader(NODE *)
{
    return g_Reader.GetName();
}

NODE *lwriter(NODE *)
{
    return g_Writer.GetName();
}

NODE *lerasefile(NODE *arg)
{
    arg = cnv_node_to_strnode(car(arg));
    if (arg == Unbound) 
    {
        return Unbound;
    }

    char * fnstr = (char *) malloc((size_t) getstrlen(arg) + 1);
    strnzcpy(fnstr, getstrptr(arg), getstrlen(arg));
    remove(fnstr);
    free(fnstr);
    gcref(arg);
    return Unbound;
}


void
PrintWorkspaceToFileStream(
    FILE * FileStream
    )
{
    if (FileStream != NULL)
    {
        // HACK: change g_Writer to use the new stream
        FILE * savedWriterStream = g_Writer.GetStream();
        g_Writer.SetStream(FileStream);

        bool save_yield_flag = yield_flag;
        yield_flag = false;
        lsetcursorwait(NIL);

        NODE * entire_workspace = vref(cons_list(lcontents(NIL)));
        lpo(entire_workspace);
        deref(entire_workspace);

        fclose(g_Writer.GetStream());
        IsDirty = false;

        lsetcursorarrow(NIL);
        yield_flag = save_yield_flag;

        // restore g_Writer
        g_Writer.SetStream(savedWriterStream);
    }
    else
    {
        err_logo(
            FILE_ERROR, 
            make_static_strnode(LOCALIZED_ERROR_FILESYSTEM_CANTOPEN));
    }
}


NODE *lsave(NODE *arg)
{
    if (IsEditorOpen())
    {
        // Notify the user that the editor is open and that 
        // the changes made in that editor won't be saved.
        ::MessageBox(
            GetCommanderWindow(),
            LOCALIZED_EDITORISOPEN,
            LOCALIZED_INFORMATION,
            MB_OK | MB_ICONQUESTION);
    }

    lprint(arg);

    PrintWorkspaceToFileStream(open_file(car(arg), "w+"));

    return Unbound;
}

void runstartup(NODE *oldst)
{
    NODE* st = Startup.GetValue();
    if (st != oldst && st != NIL && is_list(st))
    {
        start_execution();

        g_ValueStatus = VALUE_STATUS_NotOk;
        eval_driver(st);

        // process special conditions
        process_special_conditions();

        stop_execution();
    }
}

void silent_load(NODE *arg, const char *prefix)
{

    /* This procedure is called three ways:
     *    silent_load(NIL,*argv)    loads *argv
     *    silent_load(proc,logolib) loads logolib/proc
     *    silent_load(proc,NULL)    loads proc.lgo
     * The "/" or ".lgo" is supplied by this procedure as needed.
     */
    if (prefix == NULL && arg == NIL)
    {
        return;
    }

    // construct the filename
    char   filename[MAX_PATH];
    char * filenamePtr   = filename;
    char * filenameLimit = filename + MAX_PATH - 1;  // leave room for NUL

    *filenamePtr = '\0';
    if (prefix != NULL)
    {
        size_t prefixLength = strlen(prefix);
        if (filenameLimit <= filenamePtr + prefixLength)
        {
            // prefix is too long
            return;
        }

        // copy the prefix to the filename
        memcpy(filenamePtr, prefix, prefixLength);
        filenamePtr += prefixLength;
    }

    if (arg != NIL)
    {
        arg = cnv_node_to_strnode(arg);
        if (arg == Unbound)
        {
            return;
        }

        const char * argString       = getstrptr(arg);
        int          argStringLength = getstrlen(arg);

        if (filenameLimit <= filenamePtr + argStringLength)
        {
            // prefix is too long
            return;
        }
        noparitylow_strnzcpy(filenamePtr, argString, argStringLength);

        // Replace characters that are illegal in filename (such as '?')
        // characters that are illegal in procedure names (such as '+')
        // This permits us to load "?REST" as a Logolib routine.
        for (const char * limit = filenamePtr + argStringLength;
             filenamePtr < limit;
             filenamePtr++)
        {
            if (*filenamePtr == '?')
            {
                *filenamePtr = '+';
            }
        }

        if (prefix == NULL)
        {
            const size_t EXTENSION_LENGTH = sizeof(".lgo") - 1;
            // this is not coming from Logolib, so append a ".lgo"
            if (filenameLimit <= filenamePtr + EXTENSION_LENGTH)
            {
                // prefix is too long
                return;
            }
            memcpy(filenamePtr, ".lgo", EXTENSION_LENGTH);
            filenamePtr += EXTENSION_LENGTH;
        }
        gcref(arg);
    }

    // NUL-terminate filename
    *filenamePtr = '\0';

    bool isOk = fileload(filename);
    if (isOk)
    {
        if (stopping_flag == THROWING)
        {
            // There was an error parsing this file.
            // Open it in the editor so that it can be debugged.
            stopping_flag = RUN;
            OpenEditorToLocationOfFirstError(filename);
        }
    }
    else 
    {
        if (arg == NIL)
        {
            // we're loading argv (not from Logolib or current directory)
            // so we should display an error
            ndprintf(stdout, LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2"\n", prefix);
        }
    }
}

// CONSIDER for MAINTAINABILITY:
// CONSIDER for SIZE:
// Refactor the common parts of lload() and fileload() into a helper.
NODE *lload(NODE *arg)
{
    NODE *st = Startup.GetValue();
    FIXNUM saved_value_status = g_ValueStatus;

    bool isDirtySave = IsDirty;
    FILE * tmp = loadstream;
    NODE * tmp_line = vref(current_line);
    loadstream = open_file(car(arg), "r");
    if (loadstream != NULL)
    {
        bool save_yield_flag = yield_flag;
        yield_flag = false;
        lsetcursorwait(NIL);

        while (!feof(loadstream) && NOT_THROWING)
        {
            current_line = reref(current_line, reader(loadstream, ""));
            NODE * exec_list = parser(current_line, true);
            g_ValueStatus = VALUE_STATUS_NotOk;
            eval_driver(exec_list);
        }
        fclose(loadstream);

        lsetcursorarrow(NIL);
        yield_flag = save_yield_flag;

        runstartup(st);
        g_ValueStatus = saved_value_status;
    }
    else
    {
        err_logo(
            FILE_ERROR, 
            make_static_strnode(LOCALIZED_ERROR_FILESYSTEM_CANTOPEN));
    }

    loadstream = tmp;
    deref(current_line);
    current_line = tmp_line;
    IsDirty = isDirtySave;
    return Unbound;
}

NODE *lreadlist(NODE *)
{
    input_mode = INPUTMODE_List;
    NODE * val = parser(reader(g_Reader.GetStream(), ""), false);
    input_mode = INPUTMODE_None;
    if (feof(g_Reader.GetStream()))
    {
        gcref(val);
        return Null_Word;
    }
    return val;
}

NODE *lreadword(NODE *)
{
    NODE * val = reader(g_Reader.GetStream(), "RW");  // fake prompt flags no auto-continue
    if (feof(g_Reader.GetStream()))
    {
        gcref(val);
        return NIL;
    }
    return val;
}

NODE *lreadrawline(NODE *)
{
    NODE *val = reader(g_Reader.GetStream(), "RAW"); // fake prompt flags no specials
    if (feof(g_Reader.GetStream()))
    {
        gcref(val);
        return NIL;
    }

    return val;
}

NODE *lreadchar(NODE *)
{
    input_blocking = true;

    char c;
    if (!setjmp(iblk_buf))
    {
        if (g_Reader.GetStream() == stdin)
        {
            c = (char) rd_getc(stdin);
        }
        else
        {
            c = (char) getc(g_Reader.GetStream());
        }
    }
    input_blocking = false;

    if (feof(g_Reader.GetStream()))
    {
        return NIL;
    }

    if (g_Reader.IsBinary())
    {
        return make_intnode(((unsigned char) c));
    }
    else
    {
        return make_strnode(
            &c,
            1,
            ecma_get(c) ? STRING : BACKSLASH_STRING,
            strnzcpy);
    }
}

NODE *lreadchars(NODE *args)
{
    NODETYPES type = STRING;

    size_t totalBytesRequested = (size_t) getint(nonnegative_int_arg(args));
    size_t totalBytesRead      = 0;

    if (stopping_flag == THROWING) 
    {
        return Unbound;
    }

    // READCHARS is documented to always return [] when the read
    // stream is set to the commander.
    if (g_Reader.GetStream() == stdin)
    {
        return NIL;
    }

    input_blocking = true;

    char *strhead, *strptr;
    if (!setjmp(iblk_buf))
    {
        // TODO: Don't allocate more bytes than the file contains.
        // This would allow for success when given a very large input.
        strhead = (char *) malloc(totalBytesRequested + sizeof(short) + 1);
        if (strhead == NULL)
        {
            err_logo(OUT_OF_MEM, NIL);
            return Unbound;
        }

        strptr = strhead + sizeof(short);
        totalBytesRead = fread(strptr, 1, totalBytesRequested, g_Reader.GetStream());
        unsigned short * temp = (unsigned short *) strhead;
        setstrrefcnt(temp, 0);
    }

    input_blocking = false;

    if (stopping_flag == THROWING) 
    {
        free(strhead);
        return Unbound;
    }

    if (totalBytesRead == 0)
    {
        // We read zero bytes.  This may be because we hit EOF or
        // because we requested zero bytes.  If both are true, we
        // want to return [] when we're at EOF.
        if (totalBytesRequested == 0)
        {
            // Probe to see if we're at the end of the file.
            // This will update feof().
            ungetc(getc(g_Reader.GetStream()), g_Reader.GetStream());
        }

        if (feof(g_Reader.GetStream()))
        {
            // We reached the end of the file.
            free(strhead);
            return NIL;
        }
    }

    // Check if this string has special characters in it
    for (size_t i = 0; i < totalBytesRead; i++)
    {
        if (ecma_get(strptr[i])) 
        {
            type = BACKSLASH_STRING;
            break;
        }
    }

    return make_strnode_no_copy(strptr, strhead, (int) totalBytesRead, type);
}

NODE *leofp(NODE *)
{
    ungetc(getc(g_Reader.GetStream()), g_Reader.GetStream());
    int isEof = feof(g_Reader.GetStream());
    return true_or_false(isEof);
}

NODE *lkeyp(NODE *)
{
    if (g_Reader.GetStream() == stdin)
    {
        return Truex.GetNode();
    }

    return leofp(NIL);
}

NODE *lreadpos(NODE *)
{
    return g_Reader.GetPosition();
}

NODE *lsetreadpos(NODE *arg)
{
    g_Reader.SetPosition(arg);
    return Unbound;
}

NODE *lwritepos(NODE *)
{
    return g_Writer.GetPosition();
}

NODE *lsetwritepos(NODE *arg)
{
    g_Writer.SetPosition(arg);
    return Unbound;
}

NODE *lcloseall(NODE *)
{
    // close all open file pointers
    while (g_OpenFiles != NULL)
    {
        CFileListNode * nextNode = g_OpenFiles->m_Next;
        delete g_OpenFiles;
        g_OpenFiles = nextNode;
    }

    return Unbound;
}

void uninitialize_files()
{
    lcloseall(NIL);

    g_Reader.ResetToDefaultStream();
    g_Writer.ResetToDefaultStream();
}
