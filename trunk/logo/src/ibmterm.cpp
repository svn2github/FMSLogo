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

bool in_graphics_mode = false;
bool in_erase_mode = false;

int ibm_screen_top;
int current_write_mode = COPY_PUT;
int turtle_color;
int prev_color;

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

void term_init_ibm()
   {
   x_max = 80;
   y_max = 24;
   x_coord = y_coord = 0;
   }

void ibm_gotoxy(int x, int y)
   {
   gotoxy(x + 1, y + 1);
   }

void ibm_clear_text()
   {
   clearcombobox();
   }

void ibm_plain_mode()
   {
   // textattr(oldattr); /* white on black */
   }

/************************************************************/
/* These are the machine-specific graphics definitions.  All versions must
provide a set of functions analogous to these. */

void save_pen(pen_info *p)
   {
   // p->h = getx();
   // p->v = gety();
   p->penup = g_Turtles[turtle_which].IsPenUp;
   p->width = get_pen_width();
   // p->color = getcolor();
   p->prev_color = prev_color;
   get_pen_pattern(p->pattern);
   p->mode = get_pen_mode();
   }

void restore_pen(const pen_info *p)
   {
   // moveto(p->h, p->v);
   g_Turtles[turtle_which].IsPenUp = p->penup;
   set_pen_width(p->width);
   set_pen_mode(p->mode);    // must restore mode before color
   // setcolor(p->color);
   prev_color = p->prev_color;
   set_pen_pattern(p->pattern);
   }

void plain_xor_pen()
   {
   set_pen_width(1);
   // setcolor(turtle_color);
   // setwritemode(XOR_PUT);
   current_write_mode = XOR_PUT;
   in_erase_mode = false;
   }

void pen_down()
   {
   // setwritemode(COPY_PUT);
   current_write_mode = COPY_PUT;
   if (in_erase_mode)
      {
      // setcolor(prev_color);
      in_erase_mode = false;
      }
   }

void pen_reverse()
   {
   // setwritemode(XOR_PUT);
   current_write_mode = XOR_PUT;
   if (in_erase_mode)
      {
      // setcolor(prev_color);
      in_erase_mode = false;
      }
   }

void pen_erase()
   {
   if (!in_erase_mode)
      {
      //        setwritemode(COPY_PUT);
      current_write_mode = COPY_PUT;
      //        prev_color = getcolor();
      //        setcolor(0);
      in_erase_mode = true;
      }
   }

int get_pen_mode()
   {
   if (in_erase_mode)
      {
      return 2;
      }
   else
      {
      return current_write_mode;
      }
   }

void set_pen_mode(int m)
   {
   switch (m)
      {
       case 2: pen_erase(); break;
       case COPY_PUT: pen_down(); break;
       case XOR_PUT: pen_reverse(); break;
      }
   }

//int get_pen_width()
//{
//    struct linesettingstype ls;
//
//    getlinesettings(&ls);
//    return ls.thickness;
//return (0);
//}

void set_pen_pattern(const char * /* pat */)
   {
   //    setfillpattern(pat, getcolor());
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
      mode = "erase";
      }
   else if (current_write_mode == XOR_PUT)
      {
      mode = "reverse";
      }
   else
      {
      mode = "paint";
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

