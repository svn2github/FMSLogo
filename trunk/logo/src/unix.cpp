/*
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
jmp_buf iblk_buf;
#endif

char *combo_buff = NULL;
size_t combo_buff_size = 0;

static
void
prepare_combo_buff(
   const char * str
)
   {
   // if combo_buff has never been allocated, do so now.
   if (combo_buff == NULL)
      {
      combo_buff = (char *) calloc(MAX_BUFFER_SIZE, sizeof(char));
      combo_buff_size = MAX_BUFFER_SIZE;
      }

   // if it won't fit extend it
   size_t length = strlen(combo_buff) + strlen(str) + 1;
   if (combo_buff_size < length)
      {
      combo_buff = (char *) realloc(combo_buff, length);
      combo_buff_size = length;
      }
   }

static
void
mputcombobox(
   const char *str
)
   {
   // resize combo_buff to be large enough to hold str
   prepare_combo_buff(str);

   // append str
   strcat(combo_buff, str);

   // process lines
   char * tempbuff = combo_buff;
   size_t i = strlen(combo_buff);

   for (size_t j = 0; j < i; j++)
      {

      // if <cr> pump it out
      if (combo_buff[j] == '\n')
         {
         combo_buff[j] = '\0';
         putcombobox(tempbuff);
         combo_buff[j] = '\n';
         tempbuff = &combo_buff[j + 1];
         //         MyMessageScan(); // didn't help
         }
      }

   if (tempbuff != '\0') 
      {
      putcombobox(tempbuff);
      }

   combo_buff[0] = '\0';
   }

void putcombochar(char c)
   {
   // resize combo_buff to be large enough to one more character
   prepare_combo_buff("x");

   // if <cr> pump it out
   if (c == '\n')
      {
      putcombobox(combo_buff);
      combo_buff[0] = '\0';
      }
   else
      {
      // else append it
      size_t i = strlen(combo_buff);
      combo_buff[i] = c;
      combo_buff[i + 1] = '\0';
      }
   }

int printfx(const char *fmt)
   {
   mputcombobox(fmt);

   return strlen(fmt);
   }

int printfx(const char *fmt, const char *str)
   {
   // BUG: this should use snprintf(), but it does
   // not exist in Borland's compiler.
   char buff[MAX_BUFFER_SIZE * 2];
   int cnt = sprintf(buff, fmt, str);

   mputcombobox(buff);

   return cnt;
   }

NODE *lpushdir(NODE *arg)
   {
   char fname[MAX_BUFFER_SIZE + 1];
   cnv_strnode_string(fname, arg);

   if (chdir(fname))
      {
      printfx("Could not chdir to directory \"%s\"", fname);
      }
   else
      {
      getcwd(fname, sizeof fname);
      printfx("Changed to \"%s\"", fname);
      }

   return Unbound;
   }

NODE *lpopdir(NODE *)
   {
   chdir("..");

   char fname[MAX_BUFFER_SIZE + 1];
   getcwd(fname, sizeof fname);

   printfx("Popped to \"%s\"", fname);

   return Unbound;
   }

NODE *lmkdir(NODE *arg)
   {
   char fname[MAX_BUFFER_SIZE + 1];
   cnv_strnode_string(fname, arg);

   if (mkdir(fname))
      {
      printfx("Failed to create directory \"%s\"", fname);
      }
   else
      {
      chdir(fname);
      printfx("Now in newly created directory \"%s\"", fname);
      }

   return Unbound;
   }

NODE *lrmdir(NODE *arg)
   {
   char fname[MAX_BUFFER_SIZE + 1];
   cnv_strnode_string(fname, arg);

   if (rmdir(fname))
      {
      printfx("Failed to remove directory \"%s\"", fname);
      if (errno == EEXIST)
         {
         printfx("The directory does not exist.");
         }
      else if (errno == EEXIST || errno==EPERM)
         {
         printfx("Make sure the directory is empty before trying to remove it.");
         }
      else
         {
         printfx("%s", strerror(errno));
         }
      }
   else
      {
      printfx("Removed directory \"%s\"", fname);
      }

   return Unbound;
   }

NODE *lfiles(NODE *)
   {
   struct find_t ffblk;

   NODE *directory = NIL;

   int done = _dos_findfirst("*.*", 0, &ffblk);
   while (!done)
      {
      if (ffblk.attrib != FA_DIREC)
         {
         NODE* file = make_strnode(ffblk.name, strlen(ffblk.name), STRING, strnzcpy);
         if (directory == NIL)
            {
            directory = cons_list(file);
            }
         else
            {
            directory = cons(file,directory);
            }
         }
      done = _dos_findnext(&ffblk);
      }

   return (directory);
   }

NODE *ldirectories(NODE *)
   {
   struct find_t ffblk;

   NODE *directory = NIL;

   int done = _dos_findfirst("*.*", FA_DIREC, &ffblk);
   while (!done)
      {
      if (ffblk.attrib == FA_DIREC)
         {
         NODE* file = make_strnode(ffblk.name, strlen(ffblk.name), STRING, strnzcpy);
         if (directory == NIL)
            {
            directory = cons_list(file);
            }
         else
            {
            directory = cons(file,directory);
            }
         }
      done = _dos_findnext(&ffblk);
      }

   return directory;
   }

void unblock_input()
   {
   if (input_blocking)
      {
      input_blocking = 0;
#ifdef TIOCSTI
      ioctl(0, TIOCSTI, "\n");
#else
      longjmp(iblk_buf, 1);
#endif
      }
   }

#ifdef __ZTC__
void logo_stop(int /*sig*/)
#else
void logo_stop(int /*sig*/)
#endif
   {
   to_pending = 0;
#ifndef unix
   err_logo(STOP_ERROR, NIL);
#else
   if (ufun != NIL)
      {
      err_logo(STOP_ERROR, NIL);
      }
   else
      {
      new_line(stdout);
      }
#endif
#ifndef bsd
   signal(SIGINT, logo_stop);
#endif
   unblock_input();
   }

#ifdef __ZTC__
void logo_pause(int /*sig*/)
#else
void logo_pause(int /*sig*/)
#endif
   {
   to_pending = 0;
#ifdef bsd
   sigsetmask(0);
#else
   signal(SIGQUIT, logo_pause);
#endif
#ifndef unix
   lpause(NIL);
#else
   if (ufun != NIL)
      {
      lpause(NIL);
      }
   else
      {
      new_line(stdout);
      unblock_input();
      }
#endif
   }


