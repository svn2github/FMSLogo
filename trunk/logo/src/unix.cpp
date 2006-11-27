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

jmp_buf iblk_buf;

static CDynamicBuffer g_ComboBuffer;
static
void
mputcombobox(
   const char *str
   )
   {
   // Append the string to the buffer
   g_ComboBuffer.AppendString(str);

   // process lines
   char * next_line = g_ComboBuffer.m_Buffer;
   for (size_t i = 0; i < g_ComboBuffer.m_BufferLength; i++)
      {
      if (g_ComboBuffer.m_Buffer[i] == '\n')
         {
         // if <lf> pump it out
         g_ComboBuffer.m_Buffer[i] = '\0';
         putcombobox(next_line);
         g_ComboBuffer.m_Buffer[i] = '\n';
         next_line = &g_ComboBuffer.m_Buffer[i + 1];
         }
      }

   // flush the last line (which doesn't end in \n)
   if (next_line[0] != '\0') 
      {
      putcombobox(next_line);
      }

   // clear the contents of the buffer, since we wrote the entire thing
   g_ComboBuffer.Empty();
   }

void putcombochar(char ch)
   {
   if (ch == '\n')
      {
      // if <lf> pump it out
      putcombobox(g_ComboBuffer.m_Buffer);
      g_ComboBuffer.Empty();
      }
   else
      {
      g_ComboBuffer.AppendChar(ch);
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

NODE *lchdir(NODE *arg)
   {
   char fname[MAX_BUFFER_SIZE + 1];
   cnv_strnode_string(fname, arg);

   if (chdir(fname))
      {
      printfx(LOCALIZED_FILE_CHDIRFAILED, fname);
      }
   else
      {
      getcwd(fname, sizeof fname);
      printfx(LOCALIZED_FILE_CHDIRSUCCEEDED, fname);
      }

   return Unbound;
   }

NODE *lpopdir(NODE *)
   {
   chdir("..");

   char fname[MAX_BUFFER_SIZE + 1];
   getcwd(fname, sizeof fname);

   printfx(LOCALIZED_FILE_POPPEDTO, fname);

   return Unbound;
   }

NODE *lmkdir(NODE *arg)
   {
   char fname[MAX_BUFFER_SIZE + 1];
   cnv_strnode_string(fname, arg);

   if (mkdir(fname))
      {
      printfx(LOCALIZED_FILE_MKDIRFAILED, fname);
      }
   else
      {
      chdir(fname);
      printfx(LOCALIZED_FILE_MKDIRSUCCEEDED, fname);
      }

   return Unbound;
   }

NODE *lrmdir(NODE *arg)
   {
   char fname[MAX_BUFFER_SIZE + 1];
   cnv_strnode_string(fname, arg);

   if (rmdir(fname))
      {
      printfx(LOCALIZED_FILE_RMDIRFAILED, fname);
      if (errno == EEXIST)
         {
         printfx(LOCALIZED_FILE_RMDIRFAILEDNOEXIST);
         }
      else if (errno == EEXIST || errno == EPERM)
         {
         printfx(LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY);
         }
      else
         {
         printfx("%s", strerror(errno));
         }
      }
   else
      {
      printfx(LOCALIZED_FILE_RMDIRSUCCEEDED, fname);
      }

   return Unbound;
   }

static
NODE *directory_helper(bool OnlyListDirectories)
   {
   NODE *directory = NIL;

   WIN32_FIND_DATA findFileData;

   HANDLE searchHandle = FindFirstFile(
      "*.*",
      &findFileData); 
   if (searchHandle != INVALID_HANDLE_VALUE)
      {
      BOOL moreToCome = TRUE;
      while (moreToCome)
         {
         bool isADirectory = findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? 
            true : 
            false;
         if ((OnlyListDirectories && isADirectory) ||
             (!OnlyListDirectories && !isADirectory))
            {
            // found what we're looking for
            NODE* file = make_strnode(findFileData.cFileName);
            if (directory == NIL)
               {
               directory = cons_list(file);
               }
            else
               {
               directory = cons(file,directory);
               }
            }
         
         // iterate to the next file
         moreToCome = FindNextFile(searchHandle, &findFileData);
         }

      FindClose(searchHandle);
      }

   return directory;
   }

NODE *lfiles(NODE *)
   {
   return directory_helper(false);
   }

NODE *ldirectories(NODE *)
   {
   return directory_helper(true);
   }

void unblock_input()
   {
   if (input_blocking)
      {
      input_blocking = false;
      longjmp(iblk_buf, 1);
      }
   }

void uninitialize_combobox()
   {
   g_ComboBuffer.Dispose();
   }
