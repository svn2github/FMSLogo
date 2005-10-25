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

extern x_margin, y_margin;
/************************************************************/

//extern unsigned _stklen = 8000; /* 5000 for debugging, 65000 for real */

BOOLEANx in_graphics_mode = FALSE;
BOOLEANx have_been_in_graphics_mode = FALSE;
BOOLEANx in_erase_mode = FALSE;

int ibm_screen_top, ibm_turtle_top_max;
int current_write_mode = COPY_PUT;
int current_vis[TURTLES]=
      {
      0
      }
;
int turtle_color;
int prev_color;
int texth;
extern int MaxX, MaxY;
void *window_image;

void nop()
   {
   }

extern int *TopOfStack;

BOOLEANx check_ibm_stop(int scan)
   {
   //   int key;

   //#define MAXREALSTACK 0x00080000

   //   if ((TopOfStack - &key) > MAXREALSTACK)
   //      {
   //      err_logo(STACK_OVERFLOW, NIL);
   //      return(1);
   //      }

   //    long base, top;

   //    Time_To_Pause = 0;
   //    Time_To_Halt = 0;

   if (scan) MyMessageScan();

   if (Time_To_Halt)
      {
      Time_To_Halt = 0;
      emptyqueue();
      err_logo(STOP_ERROR, NIL);
      return (1);
      }

   if (Time_To_Pause)
      {
      Time_To_Pause = 0;
      to_pending = 0;
      lpause();
      }

   return (0);
   }

void term_init_ibm()
   {
   tty_charmode = 0;
   x_max = 80;
   y_max = 24;
   x_coord = y_coord = 0;
   /*
      so_arr[0] = '\1'; so_arr[1] = '\0';
      se_arr[0] = '\2'; se_arr[1] = '\0';
    */
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
   //    textattr(oldattr); /* white on black */
   }

/************************************************************/
/* These are the machine-specific graphics definitions.  All versions must
provide a set of functions analogous to these. */

void save_pen(pen_info *p)
   {
   //    p->h = getx();
   //    p->v = gety();
   p->vis = current_vis[turtle_which];
   p->width = get_ibm_pen_width();
   //    p->color = getcolor();
   p->prev_color = prev_color;
   get_pen_pattern(p->pattern);
   p->mode = get_ibm_pen_mode();
   }

void restore_pen(pen_info *p)
   {
   //    moveto(p->h, p->v);
   current_vis[turtle_which] = p->vis;
   set_ibm_pen_width(p->width);
   set_ibm_pen_mode(p->mode);          /* must restore mode before color      */
   //    setcolor(p->color);
   prev_color = p->prev_color;
   set_pen_pattern(p->pattern);
   }

void plain_xor_pen()
   {
   set_ibm_pen_width(1);
   //    setcolor(turtle_color);
   //    setwritemode(XOR_PUT);
   current_write_mode = XOR_PUT;
   in_erase_mode = FALSE;
   }

void ibm_pen_down()
   {
   //    setwritemode(COPY_PUT);
   current_write_mode = COPY_PUT;
   if (in_erase_mode)
      {
      //        setcolor(prev_color);
      in_erase_mode = FALSE;
      }
   }

void ibm_pen_xor()
   {
   //    setwritemode(XOR_PUT);
   current_write_mode = XOR_PUT;
   if (in_erase_mode)
      {
      //        setcolor(prev_color);
      in_erase_mode = FALSE;
      }
   }

void ibm_pen_erase()
   {
   if (!in_erase_mode)
      {
      //        setwritemode(COPY_PUT);
      current_write_mode = COPY_PUT;
      //        prev_color = getcolor();
      //        setcolor(0);
      in_erase_mode = TRUE;
      }
   }

int get_ibm_pen_mode()
   {
   if (in_erase_mode)
      return 2;
   else
      return current_write_mode;
   }

void set_ibm_pen_mode(int m)
   {
   switch (m)
      {
       case 2: ibm_pen_erase(); break;
       case COPY_PUT: ibm_pen_down(); break;
       case XOR_PUT: ibm_pen_xor(); break;
      }
   }

//int get_ibm_pen_width()
//{
//    struct linesettingstype ls;
//
//    getlinesettings(&ls);
//    return ls.thickness;
//return (0);
//}

void set_pen_pattern(char * /* pat */)
   {
   //    setfillpattern(pat, getcolor());
   }

void set_list_pen_pattern(NODE *arg)
   {
   unsigned char pat[8];
   NODE *cur_num, *temp;
   int count;

   cur_num = arg;
   for (count = 0; count <= 7; count++)
      {
      temp = cnv_node_to_numnode(car(cur_num));
      pat[count] = (char) getint(temp);
      if (cdr(cur_num) != NIL)
         cur_num = cdr(cur_num);
      gcref(temp);
      }
   //    setfillpattern(pat, getcolor());
   }

void get_pen_pattern(char * /* pat */)
   {
   //    getfillpattern(pat);
   }

NODE *Get_node_pen_pattern()
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
   return (NIL);
   }

NODE *Get_node_pen_mode()
   {
   if (in_erase_mode)
      return (make_static_strnode("erase"));
   if (current_write_mode == XOR_PUT)
      return (make_static_strnode("reverse"));
   return (make_static_strnode("paint"));
   }

void erase_screen()
   {
   ibm_clear_screen();
   }

FIXNUM mickey_x()
   {
   return 0;
   }

FIXNUM mickey_y()
   {
   return 0;
   }

BOOLEANx Button()
   {
   return FALSE;
   }

void tone(FIXNUM frequency, FIXNUM duration)
   {
   if (frequency < 37)
      {
      frequency = 37;
      }

   MyBeep(frequency, duration);
   }

FIXNUM t_height()
   {
   return 18;
   }

FLONUM t_half_bottom()
   {
   return 6.0;
   }

FLONUM t_side()
   {
   return 19.0;
   }

