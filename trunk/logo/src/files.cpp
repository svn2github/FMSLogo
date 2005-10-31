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

#ifndef TIOCSTI
extern jmp_buf iblk_buf;
#endif

NODE *file_list = NULL;
NODE *reader_name = NIL, *writer_name = NIL;

FILE *open_file(NODE *arg, char *access)
   {
   char *fnstr;
   FILE *tstrm;

   ref(arg);
   arg = reref(arg, cnv_node_to_strnode(arg));
   if (arg == UNBOUND) return (NULL);
   fnstr = (char *) malloc((size_t) getstrlen(arg) + 1);
   strnzcpy(fnstr, getstrptr(arg), getstrlen(arg));

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

   if (strcmp(access, "r+") == 0)
      {
      fseek(tstrm, 0, 2);// a+ does not work so r+ and seek to end
      }

   deref(arg);
   free(fnstr);
   return (tstrm);
   }

NODE *ldribble(NODE *arg)
   {
   if (dribblestream != NULL)
      err_logo(ALREADY_DRIBBLING, NIL);
   else
      {
      dribblestream = open_file(car(arg), "w+");
      if (dribblestream == NULL) err_logo(FILE_ERROR, NIL);
      }
   return (UNBOUND);
   }

NODE *lnodribble(NODE *)
   {
   if (dribblestream != NULL)
      {
      fclose(dribblestream);
      dribblestream = NULL;
      }
   return (UNBOUND);
   }

FILE *find_file(NODE *arg, bool remove)
   {
   NODE *t, *prev = NIL;
   FILE *fp = NULL;

   t = file_list;
   while (t != NIL)
      {
      if (compare_node(arg, car(t), FALSE) == 0)
         {
         fp = (FILE *) t->n_obj;
         if (remove)
            {
            t->n_obj = NIL;
            if (prev == NIL)
               file_list = reref(file_list, cdr(t));
            else
               setcdr(prev, cdr(t));
            }
         break;
         }
      prev = t;
      t = cdr(t);
      }
   return fp;
   }

static
NODE *lopen(NODE *arg, char *mode)
   {
   FILE *tmp;

   arg = car(arg);
   if (find_file(arg, FALSE) != NULL)
      err_logo(FILE_ERROR, make_static_strnode("File already open"));
   else if ((tmp = open_file(arg, mode)) != NULL)
      {
      push(arg, file_list);
      file_list->n_obj = (NODE *) tmp;
      }
   else
      err_logo(FILE_ERROR, make_static_strnode("I can't open that file"));
   return (UNBOUND);
   }

NODE *lopenread(NODE *args)
   {
   BOOL bBinary = FALSE;

   if (cdr(args) != NIL)
      bBinary = torf_arg(cdr(args));

   if (NOT_THROWING)
      {
      if (bBinary)
         return (lopen(args, "rb"));
      else
         return (lopen(args, "r"));
      }

   return(UNBOUND);
   }

NODE *lopenwrite(NODE *args)
   {
   BOOL bBinary = FALSE;

	if (cdr(args) != NIL)
		bBinary = torf_arg(cdr(args));

	if (NOT_THROWING)
		{
		if (bBinary)
			return (lopen(args, "wb"));
		else
			return (lopen(args, "w"));
		}

   return(UNBOUND);
   }

NODE *lopenappend(NODE *args)
   {
   BOOL bBinary = FALSE;

	if (cdr(args) != NIL)
		bBinary = torf_arg(cdr(args));

	if (NOT_THROWING)
		{
		if (bBinary)
			return (lopen(args, "ab"));
		else
			return (lopen(args, "a"));
		}

   return(UNBOUND);
   }

NODE *lopenupdate(NODE *args)
   {
   BOOL bBinary = FALSE;

   if (cdr(args) != NIL)
      bBinary = torf_arg(cdr(args));

   if (NOT_THROWING)
      {
      if (bBinary)
         return (lopen(args, "r+b"));
      else
         return (lopen(args, "r+"));
      }

   return(UNBOUND);
   }

NODE *lallopen(NODE *)
   {
   return (file_list);
   }

NODE *lclose(NODE *arg)
   {
   FILE *tmp;
   char *fnstr;
   
   arg = car(arg);
   
   ref(arg);
   arg = reref(arg, cnv_node_to_strnode(arg));
   if (arg == UNBOUND) return (NULL);
   fnstr = (char *) malloc((size_t) getstrlen(arg) + 1);
   strnzcpy(fnstr, getstrptr(arg), getstrlen(arg));

   if ((tmp = find_file(arg, TRUE)) == NULL)
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

   deref(arg);
   free(fnstr);

   return (UNBOUND);
   }

NODE *lsetwrite(NODE *arg)
   {
   FILE *tmp;

   if (car(arg) == NIL)
      {
      writestream = stdout;
      deref(writer_name);
      writer_name = NIL;
      }
   else if ((tmp = find_file(car(arg), FALSE)) != NULL)
      {
      writestream = tmp;
      writer_name = reref(writer_name, car(arg));
      }
   else
      err_logo(FILE_ERROR, make_static_strnode("File not open"));
   return (UNBOUND);
   }

NODE *lsetread(NODE *arg)
   {
   FILE *tmp;

   if (car(arg) == NIL)
      {
      readstream = stdin;
      deref(reader_name);
      reader_name = NIL;
      }
   else if ((tmp = find_file(car(arg), FALSE)) != NULL)
      {
      readstream = tmp;
      reader_name = reref(reader_name, car(arg));
      }
   else
      err_logo(FILE_ERROR, make_static_strnode("File not open"));
   return (UNBOUND);
   }

NODE *lreader(NODE *)
   {
   return (reader_name);
   }

NODE *lwriter(NODE *)
   {
   return (writer_name);
   }

NODE *lerasefile(NODE *arg)
   {
   char *fnstr;

   arg = cnv_node_to_strnode(car(arg));
   if (arg == UNBOUND) return (UNBOUND);
   fnstr = (char *) malloc((size_t) getstrlen(arg) + 1);
   strnzcpy(fnstr, getstrptr(arg), getstrlen(arg));
   unlink(fnstr);
   free(fnstr);
   return (UNBOUND);
   }

NODE *lsave(NODE *arg)
   {
   FILE *tmp;
   int save_yield_flag;

   if (::FindWindow(NULL, "Editor"))
      {
      MainWindowx->CommandWindow->MessageBox("Did you know you have an edit session running?\n\nAny changes in this edit session are not being saved.", "Information", MB_OK | MB_ICONQUESTION);
      }

   lprint(arg);

   tmp = writestream;
   writestream = open_file(car(arg), "w+");
   if (writestream != NULL)
      {

      save_yield_flag = yield_flag;
      yield_flag = 0;
      lsetcursorwait(NIL);

      setcar(arg, cons(lcontents(NIL), NIL));
      lpo(car(arg));
      fclose(writestream);
      IsDirty = false;

      lsetcursorarrow(NIL);
      yield_flag = save_yield_flag;
      }
   else
      {
      err_logo(FILE_ERROR, make_static_strnode("Could not open file"));
      }

   writestream = tmp;
   return (UNBOUND);
   }

void runstartup(NODE *oldst)
   {
   NODE *st;

   st = valnode__caseobj(Startup);
   if (st != oldst && st != NIL && is_list(st))
      {
      val_status = 0;
      halt_flag++;
      if (halt_flag < 1) halt_flag = 1;
      eval_driver(st);
         {
         /* process special conditions */

         for (int i = 0; i < 1; i++)
            {
            if (stopping_flag == THROWING)
               {
               if (compare_node(throw_node, Error, TRUE) == 0)
                  {
                  err_print();
                  }
               else if (compare_node(throw_node, System, TRUE) == 0)
                  {
                  break;
                  }
               else if (compare_node(throw_node, Toplevel, TRUE) != 0)
                  {
                  err_logo(NO_CATCH_TAG, throw_node);
                  err_print();
                  }
               stopping_flag = RUN;
               }

            if (stopping_flag == STOP || stopping_flag == OUTPUT)
               {
               print_node(
                  stdout,
                  make_static_strnode(
                     "You must be in a procedure to use OUTPUT or STOP.\n"));
               stopping_flag = RUN;
               }
            }
         }
         halt_flag--;
      }
   }

void silent_load(NODE *arg, char *prefix)
   {
   FILE *tmp_stream;
   NODE *tmp_line, *exec_list;
   char load_path[200];
   NODE *st = valnode__caseobj(Startup);
   int sv_val_status = val_status;
   int save_yield_flag;

   /* This procedure is called three ways:
    *    silent_load(NIL,*argv)  loads *argv
    *    silent_load(proc,logolib)     loads logolib/proc
    *    silent_load(proc,NULL)  loads proc.lg
    * The "/" or ".lg" is supplied by this procedure as needed.
    */

   bool IsDirtySave = IsDirty;
   if (prefix == NULL && arg == NIL) return;
   strcpy(load_path, (prefix == NULL ? "" : prefix));
   if (arg != NIL)
      {
      arg = cnv_node_to_strnode(arg);
      if (arg == UNBOUND) return;
#ifdef unix
      if (prefix != NULL) strcat(load_path, "/");
#endif
      noparitylow_strnzcpy(load_path + (int) strlen(load_path),
         getstrptr(arg), getstrlen(arg));
      if (prefix == NULL) strcat(load_path, ".lgo");
      gcref(arg);
      }
   tmp_stream = loadstream;
   tmp_line = vref(current_line);
   loadstream = fopen(load_path, "r");
   if (loadstream != NULL)
      {

      save_yield_flag = yield_flag;
      yield_flag = 0; // Why?
      lsetcursorwait(NIL);

      while (!feof(loadstream) && NOT_THROWING)
         {
         current_line = reref(current_line, reader(loadstream, ""));
         exec_list = parser(current_line, TRUE);
         val_status = 0;
         if (exec_list != NIL) eval_driver(exec_list);
         }

      lsetcursorarrow(NIL);
      yield_flag = save_yield_flag;

      fclose(loadstream);

      runstartup(st);
      val_status = sv_val_status;
      }
   else if (arg == NIL)
      {
      ndprintf(stdout, "File not found: %t\n", prefix);
      }
   loadstream = tmp_stream;
   deref(current_line);
   current_line = tmp_line;
   IsDirty = IsDirtySave;
   }

NODE *lload(NODE *arg)
   {
   FILE *tmp;
   NODE *tmp_line, *exec_list;
   NODE *st = valnode__caseobj(Startup);
   int sv_val_status = val_status;
   int save_yield_flag;

   if (IsDirty)
      {
      if (MainWindowx->CommandWindow->MessageBox(
         "The file being loaded may over write your changes.\n"
            "\n"
            "Continue Loading?", 
         "You have not saved to disk", 
         MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL) 
         {
         return (UNBOUND);
         }
      }

   bool IsDirtySave = IsDirty;
   tmp = loadstream;
   tmp_line = vref(current_line);
   loadstream = open_file(car(arg), "r");
   if (loadstream != NULL)
      {

      save_yield_flag = yield_flag;
      yield_flag = 0;
      lsetcursorwait(NIL);

      while (!feof(loadstream) && NOT_THROWING)
         {
         current_line = reref(current_line, reader(loadstream, ""));
         exec_list = parser(current_line, TRUE);
         val_status = 0;
         if (exec_list != NIL) eval_driver(exec_list);
         }
      fclose(loadstream);

      lsetcursorarrow(NIL);
      yield_flag = save_yield_flag;

      runstartup(st);
      val_status = sv_val_status;
      }
   else
      err_logo(FILE_ERROR, make_static_strnode("Could not open file"));
   loadstream = tmp;
   deref(current_line);
   current_line = tmp_line;
   IsDirty = IsDirtySave;
   return (UNBOUND);
   }

NODE *lreadlist(NODE *)
   {
   NODE *val;

   input_mode = LIST_MODE;
   val = parser(reader(readstream, ""), FALSE);
   input_mode = NO_MODE;
   if (feof(readstream))
      {
      gcref(val);
      return (Null_Word);
      }
   return (val);
   }

NODE *lreadword(NODE *)
   {
   NODE *val;

   val = reader(readstream, "RW");     /* fake prompt flags no auto-continue  */
   if (feof(readstream))
      {
      gcref(val);
      return (NIL);
      }
   return (val);
   }

NODE *lreadchar(NODE *)
   {
   char c;

   charmode_on();
   input_blocking++;
#ifndef TIOCSTI
   if (!setjmp(iblk_buf))
#endif
      {
#ifdef mac
      csetmode(C_RAW, stdin);
      while ((c = (char) getc(readstream)) == EOF && readstream == stdin);
      csetmode(C_ECHO, stdin);
#else
#ifdef ibm
      if (interactive && readstream == stdin)
         c = (char) rd_getc(stdin);
      else
         c = (char) getc(readstream);

//      if (c == 17)
//         {
//         /* control-q */
//         to_pending = 0;
//         err_logo(STOP_ERROR, NIL);
//         }
//      if (c == 23)
//         {
//         /* control-w */
//         logo_pause(0);
//         return (lreadchar());
//         }

#else
      c = (char) getc(readstream);
#endif
#endif
      }
   input_blocking = 0;
   if (feof(readstream))
      {
      return (NIL);
      }

   if (readstream->flags & _F_BIN)
      return (make_intnode(((unsigned char) c)));
   else
      return make_strnode(
        &c,
        (char *) NULL,
        1,
        (getparity(c) ? STRING : BACKSLASH_STRING),
        strnzcpy);
   }

NODE *lreadchars(NODE *args)
   {
   unsigned int c, i;
   char *strhead, *strptr;
   NODETYPES type = STRING;
   unsigned short *temp;

   c = (unsigned int) getint(pos_int_arg(args));
   if (stopping_flag == THROWING) return UNBOUND;
   charmode_on();
   input_blocking++;
#ifndef TIOCSTI
   if (!setjmp(iblk_buf))
#endif
      {
      strhead = (char *) malloc((size_t) (c + sizeof(short) + 1));
      strptr = strhead + sizeof(short);
      fread(strptr, 1, (int) c, readstream);
      temp = (unsigned short *) strhead;
      setstrrefcnt(temp, 0);
      }
   input_blocking = 0;
#ifndef TIOCSTI
   if (stopping_flag == THROWING) return (UNBOUND);
#endif
   if (feof(readstream))
      {
      free(strhead);
      return (NIL);
      }
   for (i = 0; i < c; i++)
      if (getparity(strptr[i])) type = BACKSLASH_STRING;
   return (make_strnode(strptr, strhead, (int) c, type, strnzcpy));
   }

NODE *leofp(NODE *)
   {
   ungetc(getc(readstream), readstream);
   if (feof(readstream))
      return (Truex);
   else
      return (Falsex);
   }

NODE *lkeyp(NODE *)
   {
   //    long nc;
#ifdef mac
   int c;
#endif

   if (readstream == stdin && interactive)
      {
      charmode_on();
      //        fflush(stdout);
#ifdef __ZTC__
      zflush();
#endif
#if defined(mac)
      csetmode(C_RAW, stdin);
      c = ungetc(getc(readstream), readstream);
      csetmode(C_ECHO, stdin);
      return (c == EOF ? Falsex : Truex);
#elif defined(ibm)
      return (Truex
       //kbhit() ? Truex : Falsex
       );
#else
#ifdef FIONREAD
      ioctl(0, FIONREAD, (char *) (&nc));
#else
      ndprintf(stdout, "Can't KEYP, no FIONREAD on this system\n");
      nc = 1;                 /* pretend there's a char so we don't loop*/
#endif
      if (nc > 0)
         return (Truex);
      else
         return (Falsex);
#endif
      }
   ungetc(getc(readstream), readstream);
   if (feof(readstream))
      return (Truex);
   else
      return (Falsex);
   }

NODE *lreadpos(NODE *)
   {
   return (make_intnode(ftell(readstream)));
   }

NODE *lsetreadpos(NODE *arg)
   {
   NODE *val = pos_int_arg(arg);

   if (NOT_THROWING)
      {
      fseek(readstream, getint(val), 0);
      }
   return (UNBOUND);
   }

NODE *lwritepos(NODE *)
   {
   return (make_intnode(ftell(writestream)));
   }

NODE *lsetwritepos(NODE *arg)
   {
   NODE *val = pos_int_arg(arg);

   if (NOT_THROWING)
      {
      fseek(writestream, getint(val), 0);
      }
   return (UNBOUND);
   }

