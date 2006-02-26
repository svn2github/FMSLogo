/*
* Copyright (C) 2005 by David Costanzo
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "allwind.h"

#undef malloc
#undef calloc
#undef realloc
#undef free
#undef strdup

struct memory_header_t
{
   size_t                    blocksize;
   long                      id;
   struct memory_header_t *  prev;
   struct memory_header_t *  next;
};

// get a pointer to the header
static
memory_header_t *
debug_userptr_to_header(
   void *  userptr
   )
   {
   // cast the data to the block header
   char * headerptr = static_cast<char*>(userptr) - sizeof(memory_header_t);
   return reinterpret_cast<memory_header_t*>(headerptr);
   }


// return a pointer beyond the header
static
unsigned char *
debug_header_to_userptr(
   memory_header_t *  header
   )
   {
   return reinterpret_cast<unsigned char *>(header + 1);
   }

static struct memory_header_t g_allocated_blocks;
static long nextid = 0;

static
void 
debug_report_leaks(void)
   {
   if (g_allocated_blocks.next != &g_allocated_blocks)
      {
      // the list is not empty
      fprintf(stderr, "Memory Leaks detected!\n");

      // dump each memory block
      for (struct memory_header_t * current_block = g_allocated_blocks.next; 
           current_block != &g_allocated_blocks;
           current_block = current_block->next)
         {
         fprintf(
            stderr,
            "(id=%lu) %u bytes at 0x%X\n", 
            current_block->id,
            current_block->blocksize,
            debug_header_to_userptr(current_block));
         }
      }
   }

static
void
initialize_memory_tracking(
   void
)
   {
   static bool is_initialized = false;
   if (!is_initialized)
      {
      // make the list circular
      g_allocated_blocks.next = &g_allocated_blocks;
      g_allocated_blocks.prev = &g_allocated_blocks;

      g_allocated_blocks.blocksize = 0;

      atexit(debug_report_leaks);

      is_initialized = true;
      }
   }


void * debug_malloc(size_t blocksize)
   {
   void * realptr = malloc(sizeof(memory_header_t) + blocksize);
   if (realptr == NULL) 
      {
      return NULL;
      }

   // cast the data to the block header
   memory_header_t * header = static_cast<memory_header_t*>(realptr);
   header->blocksize = blocksize;

   header->id = nextid++;

   // link the new block into the head of the list
   initialize_memory_tracking();
   header->next = g_allocated_blocks.next;
   header->prev = &g_allocated_blocks;

   g_allocated_blocks.next->prev = header;
   g_allocated_blocks.next       = header;

   // get a pointer to the user's memory
   unsigned char * ptr = debug_header_to_userptr(header);

   // fill uninitialized memory with a recognizable bit pattern
   memset(ptr, 0xDD, blocksize);

   return ptr;
   }

void debug_free(void * userptr)
   {
   if (userptr == NULL)
      {
      // free(NULL) is defined to be a no-op
      return;
      }

   memory_header_t * header = debug_userptr_to_header(userptr);

   // unlink this block from the list
   header->next->prev = header->prev;
   header->prev->next = header->next;

   // fill the memory with a recognizable bit pattern
   memset(header, 0xCC, header->blocksize + sizeof(*header));
   free(header);
   }

void * debug_calloc(size_t arraylength, size_t elementsize)
   {
   size_t blocksize = arraylength * elementsize;

   void * ptr = debug_malloc(blocksize);
   if (ptr == NULL) 
      {
      return NULL;
      }

   // calloc requires that the memory is set to 0.
   memset(ptr, 0x00, blocksize);
   return ptr;
   }

void * debug_realloc(void * userptr, size_t newsize)
   {
   if (userptr == NULL) 
      {
      // realloc with a NULL first parameter means malloc()
      return debug_malloc(newsize);
      }

   if (newsize == 0)
      {
      // realloc with a size of 0 means free()
      debug_free(userptr);
      return NULL;
      }

   // this is a real realloc()
   memory_header_t * header = debug_userptr_to_header(userptr);
   if (header->blocksize < newsize)
      {
      // this is a realloc() to a larger size
      void * returnptr = debug_malloc(newsize);
      if (returnptr != NULL)
         {
         // copy the old memory block's contents to the new block
         memcpy(returnptr, userptr, header->blocksize);

         // release the old memory
         debug_free(userptr);
         }

      return returnptr;
      }

   // They are reallocating to a smaller size.
   // We can ignore this.
   header->blocksize = newsize;
   return userptr;
   }


char * debug_strdup(const char * string)
   {
   size_t length = strlen(string);
   void * newstring = debug_malloc(length + 1);
   if (newstring == NULL) 
      {
      return NULL;
      }

   memcpy(newstring, string, length + 1);
   return static_cast<char *>(newstring);
   }

