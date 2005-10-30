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
mputcombobox(
   const char *str
)
   {
   char *tempbuff;

   int i;
   int j;
   int l;

   // if never called allocate it

   if (combo_buff == NULL)
      {
      combo_buff = (char *) malloc(MAX_BUFFER_SIZE);
      memset(combo_buff, 0, MAX_BUFFER_SIZE);
      combo_buff_size = MAX_BUFFER_SIZE;
      }

   // if it won't fit extend it

   l = strlen(combo_buff) + strlen(str) + 1;
   if (l > combo_buff_size)
      {
      combo_buff = (char *) realloc(combo_buff, l);
      combo_buff_size = l;
      }

   // append it

   strcat(combo_buff, str);

   // process lines

   tempbuff = combo_buff;
   i = strlen(combo_buff);

   for (j = 0; j < i; j++)
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

   if (tempbuff != '\0') putcombobox(tempbuff);

   combo_buff[0] = '\0';
   }

void putcombochar(char c)
   {
   int i;
   int l;

   // if never called allocate it

   if (combo_buff == NULL)
      {
      combo_buff = (char *) malloc(MAX_BUFFER_SIZE);
      memset(combo_buff, 0, MAX_BUFFER_SIZE);
      combo_buff_size = MAX_BUFFER_SIZE;
      }

   // if it won't fit extend it

   l = strlen(combo_buff) + 1 + 1;
   if (l > combo_buff_size)
      {
      combo_buff = (char *) realloc(combo_buff, l);
      combo_buff_size = l;
      }

   // if <cr> pump it out

   if (c == '\n')
      {
      putcombobox(combo_buff);
      combo_buff[0] = '\0';
      }

   // else append it

   else
      {
      i = strlen(combo_buff);
      combo_buff[i] = c;
      combo_buff[i + 1] = '\0';
      }
   }

void nputs(char *str)
   {
   char c;

   while ((c = *str++) != 0) putcombochar(c);
   }

int printfx(const char *fmt)
   {
   mputcombobox(fmt);

   return strlen(fmt);
   }

int printfx(const char *fmt, const char *str)
   {
   long cnt;                           /* Result of SPRINTF for return        */
   char buff[MAX_BUFFER_SIZE];

   cnt = sprintf(buff, fmt, str);

   mputcombobox(buff);

   return cnt;
   }

long putcharx(long ch)
   {
   putcombochar((char) ch);

   return ch;
   }

long putsx(const char *ch)
   {
   mputcombobox(ch);

   return 1;
   }

NODE *lpushdir(NODE *arg)
   {
   char fname[80];

   cnv_strnode_string(fname, arg);

   if (chdir(fname))
      {
      printfx("Could not Push to directory %s\n", fname);
      }
   else
      {
      getcwd(fname, 80);
      printfx("Pushed to %s\n", fname);
      }

   return (UNBOUND);
   }

NODE *lpopdir(NODE *)
   {
   char fname[80];

   chdir("..");
   getcwd(fname, 80);
   printfx("Popped to %s\n", fname);

   return (UNBOUND);
   }

NODE *lmkdir(NODE *arg)
   {
   char fname[80];

   cnv_strnode_string(fname, arg);

   if (mkdir(fname))
      {
      printfx("Failed to create directory %s\n", fname);
      }
   else
      {
      chdir(fname);
      printfx("Now in newly created directory %s\n", fname);
      }

   return (UNBOUND);
   }

NODE *lrmdir(NODE *arg)
   {
   char fname[80];

   cnv_strnode_string(fname, arg);

   if (rmdir(fname))
      {
      printfx("Failed to remove directory %s\n", fname);
      printfx("Make sure the directory is empty before trying to remove\n");
      }
   else
      {
      printfx("Logo directory %s removed\n", fname);
      }

   return (UNBOUND);
   }

NODE *lfiles(NODE *)
   {
   struct find_t ffblk;
   int done;

   NODE *directory = NULL;
   NODE *file;

   done = _dos_findfirst("*.*", 0, &ffblk);
   while (!done)
      {
      if (ffblk.attrib != FA_DIREC)
         {
         file = make_strnode(ffblk.name, NULL, strlen(ffblk.name), STRING, strnzcpy);
         if (directory == NULL)
            {
            directory = cons(file,NIL);
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

   NODE *directory = NULL;
   NODE *file;

   int done = _dos_findfirst("*.*", FA_DIREC, &ffblk);
   while (!done)
      {
      if (ffblk.attrib == FA_DIREC)
         {
         file = make_strnode(ffblk.name, NULL, strlen(ffblk.name), STRING, strnzcpy);
         if (directory == NULL)
            {
            directory = cons(file,NIL);
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


