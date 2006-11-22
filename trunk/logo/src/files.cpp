/*
*      files.c         logo file management module             dvb
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

static NODE *g_OpenFiles = NULL;

CFileStream g_Reader(stdin);
CFileStream g_Writer(stdout);

FILE *open_file(NODE *arg, const char *access)
   {
   ref(arg);
   arg = reref(arg, cnv_node_to_strnode(arg));
   if (arg == Unbound) 
      {
      return NULL;
      }

   char * fnstr = (char *) malloc((size_t) getstrlen(arg) + 1);
   strnzcpy(fnstr, getstrptr(arg), getstrlen(arg));

   FILE *tstrm;
   if (stricmp(fnstr, "clipboard") == 0)
      {
      if (stricmp(access, "r") == 0)
         {
         ::OpenClipboard(MainWindowx->HWindow);

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
               fputs( "No Text in Clipboard", clipstrm);
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

   deref(arg);
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

static
FILE *find_file(NODE *arg, bool remove)
   {
   NODE *prev = NIL;
   FILE *fp = NULL;

   for (NODE * t = g_OpenFiles; t != NIL; t = cdr(t))
      {
      if (compare_node(arg, car(t), false) == 0)
         {
         fp = (FILE *) t->nunion.ncons.nobj;
         if (remove)
            {
            t->nunion.ncons.nobj = NIL;
            if (prev == NIL)
               {
               g_OpenFiles = reref(g_OpenFiles, cdr(t));
               }
            else
               {
               setcdr(prev, cdr(t));
               }
            }
         break;
         }
      prev = t;
      }
   return fp;
   }

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

      FILE* tmp;
      Arguments = car(Arguments);
      if (find_file(Arguments, false) != NULL)
         {
         err_logo(FILE_ERROR, make_static_strnode("File already open"));
         }
      else if ((tmp = open_file(Arguments, mode)) != NULL)
         {
         push(Arguments, g_OpenFiles);
         g_OpenFiles->nunion.ncons.nobj = (NODE *) tmp;
         }
      else
         {
         err_logo(FILE_ERROR, make_static_strnode("I can't open that file"));
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
   return g_OpenFiles;
   }

NODE *lclose(NODE *arg)
   {
   arg = car(arg);
   
   ref(arg);
   arg = reref(arg, cnv_node_to_strnode(arg));
   if (arg == Unbound) 
      {
      return (NULL); // why not Unbound?
      }

   char * fnstr = (char *) malloc((size_t) getstrlen(arg) + 1);
   strnzcpy(fnstr, getstrptr(arg), getstrlen(arg));

   FILE *tmp;
   if ((tmp = find_file(arg, true)) == NULL)
      {
      err_logo(FILE_ERROR, make_static_strnode("File not open"));
      }
   else
      {
      fclose(tmp);

      if (stricmp(fnstr, "clipboard") == 0)
         {
         ::OpenClipboard(MainWindowx->HWindow);

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

         unlink(TempClipName);
         }
      }

   if (g_Writer.IsNamed(arg)) 
      {
      g_Writer.ResetToDefaultStream();
      }

   if (g_Reader.IsNamed(arg)) 
      {
      g_Reader.ResetToDefaultStream();
      }

   deref(arg);
   free(fnstr);

   return Unbound;
}

CFileStream::CFileStream(
   FILE * DefaultFileStream
   ) :
   m_Name(NIL),
   m_Stream(DefaultFileStream),
   m_DefaultStream(DefaultFileStream)
   {
   }

void
CFileStream::ResetToDefaultStream()
   {
   deref(m_Name);
   m_Name = NIL;

   m_Stream = m_DefaultStream;
   }

void
CFileStream::SetStreamToOpenFile(
   NODE * FileName
   )
   {
   FILE *tmp;

   if (FileName == NIL)
      {
      // reset to the default stream
      ResetToDefaultStream();
      }
   else if ((tmp = find_file(FileName, false)) != NULL)
      {
      m_Stream = tmp;
      m_Name = reref(m_Name, FileName);
      }
   else
      {
      err_logo(FILE_ERROR, make_static_strnode("File not open"));
      }
   }

bool
CFileStream::IsNamed(
   NODE * FileName
   ) const
   {
   return compare_node(FileName, m_Name, false) == 0;
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
   NODE *val = pos_int_arg(Arguments);

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
   unlink(fnstr);
   free(fnstr);
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
      err_logo(FILE_ERROR, make_static_strnode("Could not open file"));
      }
   }


NODE *lsave(NODE *arg)
   {
   if (::FindWindow(NULL, "Editor"))
      {
      MainWindowx->CommandWindow->MessageBox(
         "Did you know you have an edit session running?\n"
            "\n"
            "Any changes in this edit session are not being saved.", 
         "Information", 
         MB_OK | MB_ICONQUESTION);
      }

   lprint(arg);

   PrintWorkspaceToFileStream(open_file(car(arg), "w+"));

   return Unbound;
   }

void runstartup(NODE *oldst)
   {
   NODE* st = valnode__caseobj(Startup);
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
      filenamePtr += argStringLength;

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
         MainWindowx->MyPopupEditToError(filename);
         }
      }
   else 
      {
      if (arg == NIL)
         {
         // we're loading argv (not from Logolib or current directory)
         // so we should display an error
         ndprintf(stdout, "Unable to open file: %t\n", prefix);
         }
      }
   }

// CONSIDER for MAINTAINABILITY:
// CONSIDER for SIZE:
// Refactor the common parts of lload() and fileload() into a helper.
NODE *lload(NODE *arg)
   {
   NODE *st = valnode__caseobj(Startup);
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
      err_logo(FILE_ERROR, make_static_strnode("Could not open file"));
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

   if (g_Reader.GetStream()->flags & _F_BIN)
      {
      return make_intnode(((unsigned char) c));
      }
   else
      {
      return make_strnode(
        &c,
        1,
        getparity(c) ? STRING : BACKSLASH_STRING,
        strnzcpy);
      }
   }

NODE *lreadchars(NODE *args)
   {
   NODETYPES type = STRING;

   unsigned int c = (unsigned int) getint(pos_int_arg(args));
   if (stopping_flag == THROWING) 
      {
      return Unbound;
      }

   input_blocking = true;

   char *strhead, *strptr;
   if (!setjmp(iblk_buf))
      {
      strhead = (char *) malloc((size_t) (c + sizeof(short) + 1));
      strptr = strhead + sizeof(short);
      fread(strptr, 1, (int) c, g_Reader.GetStream());
      unsigned short * temp = (unsigned short *) strhead;
      setstrrefcnt(temp, 0);
      }

   input_blocking = false;

   if (stopping_flag == THROWING) 
      {
      return Unbound;
      }

   if (feof(g_Reader.GetStream()))
      {
      free(strhead);
      return NIL;
      }

   for (unsigned int i = 0; i < c; i++)
      {
      if (getparity(strptr[i])) 
         {
         type = BACKSLASH_STRING;
         }
      }

   return make_strnode_no_copy(strptr, strhead, (int) c, type);
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
      return Truex;
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
   for (NODE * current_file = g_OpenFiles;
        current_file != NIL;
        current_file = cdr(current_file))
      {
      FILE * fp = reinterpret_cast<FILE *>(current_file->nunion.ncons.nobj);
      fclose(fp);

      current_file->nunion.ncons.nobj = NIL;
      }

   // empty the file list
   deref(g_OpenFiles);
   g_OpenFiles = NIL;

   return Unbound;
   }

void uninitialize_files()
   {
   lcloseall(NIL);

   g_Reader.ResetToDefaultStream();
   g_Writer.ResetToDefaultStream();
   }
