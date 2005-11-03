/*
*       term.c          terminal cursor control                 dvb
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

int x_coord;
int y_coord;
int x_max;
int y_max;

/*
char bp[1024];
char cl_arr[40];
char cm_arr[40];
char so_arr[40];
char se_arr[40];
*/

#ifdef unix
#ifdef SYSV
struct termio tty_cooked, tty_cbreak;
#else
struct sgttyb tty_cooked, tty_cbreak;
#endif
#endif

bool interactive;
int tty_charmode;

static char *termcap_ptr;

void termcap_putter(char /*ch*/)
   {
   /*
    *termcap_ptr++ = ch;
    */
   }

#ifdef unix
void termcap_getter(char *cap, char *buf)
   {
   char temp[40];
   char *temp_ptr = temp;

   termcap_ptr = buf;
   tgetstr(cap, &temp_ptr);
   tputs(temp, 1, termcap_putter);
   }
#endif

void term_init()
   {
   //    int term_sg;
   interactive = true;  //isatty(0);
   ift_iff_flag = -1;
   term_init_ibm();
   /*
#ifdef mac
   term_init_mac();
   return;
#else
#ifdef ibm
   term_init_ibm();
#else
   if (interactive)
      {
#ifdef SYSV
      ioctl(0,TCGETA,(char *)(&tty_cooked));
      tty_cbreak = tty_cooked;
      tty_cbreak.c_cc[VMIN] = '\01';
      tty_cbreak.c_cc[VTIME] = '\0';
      tty_cbreak.c_lflag &= ~ECHO;
#else
      ioctl(0,TIOCGETP,(char *)(&tty_cooked));
      tty_cbreak = tty_cooked;
      tty_cbreak.sg_flags |= CBREAK;
      tty_cbreak.sg_flags &= ~ECHO;
#endif
      }
   tty_charmode = 0;
   tgetent(bp, getenv("TERM"));
   x_max = tgetnum("co");
   y_max = tgetnum("li");
   term_sg = tgetnum("sg");

   x_coord = y_coord = 0;
   termcap_getter("cm", cm_arr);
   termcap_getter("cl", cl_arr);

   if (term_sg <= 0)
      {
      termcap_getter("so", so_arr);
      termcap_getter("se", se_arr);
      }
   else / * don't mess with stupid standout modes * /
   so_arr[0] = se_arr[0] = '\0';
#endif
#endif
   */
   }

void charmode_on()
   {
#ifdef unix
   if ((readstream == stdin) && interactive && !tty_charmode)
      {
#ifdef SYSV
      ioctl(0, TCSETA, (char *) (&tty_cbreak));
#else
      ioctl(0, TIOCSETP, (char *) (&tty_cbreak));
#endif
      tty_charmode++;
      }
#endif
   }

void charmode_off()
   {
   /*
#ifdef unix
   if (tty_charmode)
      {
#ifdef SYSV
      ioctl(0,TCSETA,(char *)(&tty_cooked));
#else
      ioctl(0,TIOCSETP,(char *)(&tty_cooked));
#endif
      tty_charmode = 0;
      }
#endif
   */
   }

NODE *lcleartext(NODE *)
   {
   ibm_clear_text();
   /*
#ifdef mac
   cgotoxy(x_margin + 1, y_margin + 1, stdout);
   ccleos(stdout);
#else
#ifdef ibm
   ibm_clear_text();
   ibm_gotoxy(x_margin, y_margin);
#else
   printf("%s", cl_arr);
   printf("%s", tgoto(cm_arr, x_margin, y_margin));
#endif
#endif
   x_coord = x_margin;
   y_coord = y_margin;
   */
   return (UNBOUND);
   }

NODE *lcursor(NODE *)
   {
   /*
      return(cons(make_intnode((FIXNUM)(x_coord-x_margin)),
      cons(make_intnode((FIXNUM)(y_coord-y_margin)), NIL)));
    */
   return (cons(make_intnode((FIXNUM) (0)),
         cons(make_intnode((FIXNUM) (0)), NIL)));
   }

NODE *lsetcursor(NODE *  /*args*/)
   {
   /*
      NODE *arg;

      arg = pos_int_vector_arg(args); // can now return floats
      if (NOT_THROWING)
      {
      x_coord = x_margin + getint(car(arg));
      y_coord = y_margin + getint(cadr(arg));
#ifdef mac
      mac_gotoxy(x_coord, y_coord);
#else
#ifdef ibm
      ibm_gotoxy(x_coord, y_coord);
#else
      printf("%s", tgoto(cm_arr, x_coord, y_coord));
#endif
#endif
      fflush(stdout);
#ifdef __ZTC__
      zflush();
#endif
      }
   */
   return (UNBOUND);
   }

NODE *lsetmargins(NODE *  /*args*/)
   {
   /*
      NODE *arg;

      arg = pos_int_vector_arg(args); // can now return floats
      if (NOT_THROWING)
      {
      x_margin = getint(car(arg));
      y_margin = getint(cadr(arg));
      lcleartext(NIL);
      }
    */
   return (UNBOUND);
   }

NODE *lstandout(NODE *args)
   {
   char textbuf[300];
   char fmtbuf[100];

   sprintf(fmtbuf, "%%p");
   print_stringptr = textbuf;
   print_stringlen = 300;
   ndprintf((FILE *) NULL, fmtbuf, car(args));
   *print_stringptr = '\0';
   return (make_strnode(textbuf, NULL, (int) strlen(textbuf), STRING, strnzcpy));
   }

