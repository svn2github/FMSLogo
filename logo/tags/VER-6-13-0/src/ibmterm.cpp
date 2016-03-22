/*
*      ibmterm.c           IBM screen module             mak
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

//fake defs
#define COPY_PUT 12
//

/************************************************************/

bool in_erase_mode = false;

int current_write_mode = COPY_PUT;
int turtle_color;

extern int *TopOfStack;

bool check_stop(bool scan_for_messages)
   {
   // int key;

   //#define MAXREALSTACK 0x00080000

   // if ((TopOfStack - &key) > MAXREALSTACK)
   //    {
   //    err_logo(STACK_OVERFLOW, NIL);
   //    return 1;
   //    }

   // long base, top;

   // IsTimeToPause = false;
   // IsTimeToHalt = false;

   if (scan_for_messages)
      {
      MyMessageScan();
      }

   if (IsTimeToHalt)
      {
      IsTimeToHalt = false;
      emptyqueue();
      err_logo(STOP_ERROR, NIL);
      return true;
      }

   if (IsTimeToPause)
      {
      IsTimeToPause = false;
      to_pending = false;
      lpause(NIL);
      }

   return false;
   }


void pen_down()
   {
   current_write_mode = COPY_PUT;
   in_erase_mode = false;
   }

void pen_reverse()
   {
   current_write_mode = XOR_PUT;
   in_erase_mode = false;
   }

void pen_erase()
   {
   if (!in_erase_mode)
      {
      current_write_mode = COPY_PUT;
      in_erase_mode = true;
      }
   }

void set_list_pen_pattern(NODE *arg)
   {
   unsigned char pat[8];

   NODE * cur_num = arg;
   for (int count = 0; count < 8; count++)
      {
      NODE * temp = cnv_node_to_numnode(car(cur_num));
      pat[count] = (char) getint(temp);
      if (cdr(cur_num) != NIL)
         {
         cur_num = cdr(cur_num);
         }
      gcref(temp);
      }
   //    setfillpattern(pat, getcolor());
   }

void get_pen_pattern(char * /* pat */)
   {
   //    getfillpattern(pat);
   }

NODE *get_node_pen_pattern()
   {
   /*
      unsigned char pat[8];

      getfillpattern(pat);
      return(cons(make_intnode((FIXNUM)(pat[0])),
      cons(make_intnode((FIXNUM)(pat[1])),
      cons(make_intnode((FIXNUM)(pat[2])),
      cons(make_intnode((FIXNUM)(pat[3])),
      cons(make_intnode((FIXNUM)(pat[4])),
      cons(make_intnode((FIXNUM)(pat[5])),
      cons(make_intnode((FIXNUM)(pat[6])),
      cons(make_intnode((FIXNUM)(pat[7])),
      NIL)))))))));
    */
   return NIL;
   }

NODE *get_node_pen_mode()
   {
   const char * mode;

   if (in_erase_mode)
      {
      mode = LOCALIZED_PENMODE_ERASE;
      }
   else if (current_write_mode == XOR_PUT)
      {
      mode = LOCALIZED_PENMODE_REVERSE;
      }
   else
      {
      mode = LOCALIZED_PENMODE_PAINT;
      }

   return make_static_strnode(mode);
   }

void erase_screen()
   {
   ibm_clear_screen();
   }

bool button()
   {
   return false;
   }

void tone(FIXNUM frequency, FIXNUM duration)
   {
   if (frequency < 37)
      {
      frequency = 37;
      }

   MyBeep(frequency, duration);
   }

