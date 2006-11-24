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

static char * combo_buff        = NULL;
static size_t combo_buff_size   = 0;    // size of the buffer
static size_t combo_buff_length = 0;    // bytes of string in buffer (not including NUL)


#ifdef NDEBUG
#  define ASSERT_COMBOBUFF_INVARIANT
#else
#  define ASSERT_COMBOBUFF_INVARIANT CBufferInvariant invariant;

class CBufferInvariant
   {
public:
   CBufferInvariant()
      {
      AssertInvariant();
      }

   ~CBufferInvariant()
      {
      AssertInvariant();
      }

   void AssertInvariant()
      {
      if (combo_buff == NULL)
         {
         assert(combo_buff_length == 0);
         assert(combo_buff_size   == 0);
         }
      else
         {
         assert(combo_buff_length <= combo_buff_size);
         assert(combo_buff[combo_buff_length] == '\0');

         // a good assert, but it takes too long
         //assert(strlen(combo_buff) == combo_buff_length);
         }
      }
   };

#endif // NDEBUG


// empty the combo_buff, but don't free it
static
void
reset_combo_buff()
   {
   combo_buff[0]     = '\0';
   combo_buff_length = 0;
   }

// resizes combo_buff to hold extra_length more bytes.
static
void
resize_combo_buff(
   size_t  extra_length
   )
   {
   ASSERT_COMBOBUFF_INVARIANT

   // if combo_buff has never been allocated, do so now.
   if (combo_buff == NULL)
      {
      combo_buff = (char *) calloc(MAX_BUFFER_SIZE, sizeof(char));
      combo_buff_size = MAX_BUFFER_SIZE;
      }

   // if it won't fit, then make the buffer bigger
   size_t required_length = combo_buff_length + extra_length + 1;
   if (combo_buff_size < required_length)
      {
      // Double the size of the buffer, instead of only requesting 
      // required_length bytes.  If we don't do this, then printing 
      // a long string takes a *very* long time because we repeatedly 
      // reallocate the buffer to be one byte larger.
      size_t newsize = max(combo_buff_size * 2, required_length);

      combo_buff = (char *) realloc(combo_buff, newsize);
      combo_buff_size = newsize;
      }
   }

static
void
mputcombobox(
   const char *str
   )
   {
   ASSERT_COMBOBUFF_INVARIANT

   // resize combo_buff to be large enough to hold str
   size_t str_length = strlen(str);

   resize_combo_buff(str_length);

   // append str
   strcpy(combo_buff + combo_buff_length, str);
   combo_buff_length += str_length;

   // process lines
   char * next_line = combo_buff;
   for (size_t j = 0; j < combo_buff_length; j++)
      {
      if (combo_buff[j] == '\n')
         {
         // if <cr> pump it out
         combo_buff[j] = '\0';
         putcombobox(next_line);
         combo_buff[j] = '\n';
         next_line = &combo_buff[j + 1];
         }
      }

   // flush the last line (which doesn't end in \n)
   if (next_line[0] != '\0') 
      {
      putcombobox(next_line);
      }

   reset_combo_buff();
   }

void putcombochar(char c)
   {
   ASSERT_COMBOBUFF_INVARIANT

   // resize combo_buff to be large enough to one more character
   resize_combo_buff(1);

   if (c == '\n')
      {
      // if <cr> pump it out
      putcombobox(combo_buff);
      reset_combo_buff();
      }
   else
      {
      // else append it
      size_t i = combo_buff_length;
      combo_buff[i] = c;
      combo_buff[i + 1] = '\0';
      combo_buff_length++;
      }
   }


void flushcombobox()
   {
   ASSERT_COMBOBUFF_INVARIANT

   // resize combo_buff to be large enough to one byte
   resize_combo_buff(1);

   putcombobox(combo_buff);
   reset_combo_buff();
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
   ASSERT_COMBOBUFF_INVARIANT

   free(combo_buff);
   combo_buff        = NULL;
   combo_buff_size   = 0;
   combo_buff_length = 0;
   }
