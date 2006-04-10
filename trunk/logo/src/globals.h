/*
 *      globals.h       logo global references module           dvb
 *
 *	Copyright (C) 1993 by the Regents of the University of California
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

/* main.c */
extern int yield_flag;
extern int GCMAX;
extern int MAX_PHYS_LINE;
extern bool bExpert;
extern bool bFixed;
extern bool bWidth;
extern bool bHeight;
extern NODE **hash_table;
extern NODE *current_line;
extern NODE *exec_list;
extern char TempPathName[];
extern bool IsTimeToExit;
extern bool IsTimeToPause;
extern bool IsTimeToHalt;
extern int halt_flag;
extern bool traceflag;
extern bool IsDirty;
extern bool error_happen;
extern long eval_count;
extern long vector_count;
extern int memory_count;
extern bool status_flag;
extern enum KEYBOARDCAPTURE KeyboardCapture;
extern int keyboard_value;
extern bool MouseCaptureIsEnabled;
extern int mouse_posx;
extern int mouse_posy;
extern int xoffset;
extern int yoffset;
extern char *keyboard_status;
extern char *keyboard_keydown;
extern char *keyboard_keyup;
extern char *mouse_lbuttondown;
extern char *mouse_lbuttonup;
extern char *mouse_rbuttondown;
extern char *mouse_rbuttonup;
extern char *mouse_mousemove;
extern char edit_editexit[];
extern char mci_callback[];
extern char *timer_callback[];

extern SOCKET sendSock;
extern SOCKET receiveSock;
extern unsigned int sendPort;
extern unsigned int receivePort;
extern bool bSendConnected;
extern bool bSendBusy;
extern bool bReceiveConnected;
extern bool bReceiveBusy;
extern PHOSTENT phes;
extern PHOSTENT pher;
extern char *network_receive_receive;
extern char *network_receive_send;
extern char *network_send_receive;
extern char *network_send_send;
extern char *network_receive_value;
extern char *network_send_value;
extern bool network_send_on;
extern bool network_receive_on;

/* logodata.c */
#ifdef ecma
extern char ecma_array[];
extern char special_chars[];
extern int ecma_size;
#endif

/* mem.cpp */
extern NODE **gcstack;
extern NODE **gctop;

/* parse.c */
extern FILE *loadstream, *writestream, *readstream, *dribblestream;
extern int input_blocking;
extern int input_mode;

/* math.c */

/* intern.c */

/* debug.c */

/* print.c */
extern int print_stringlen;
extern char *print_stringptr;

/* init.c */
extern NODE *Truex;
extern NODE *Falsex;
extern NODE *Left_Paren;
extern NODE *Right_Paren;
extern NODE *Null_Word;
extern NODE *Toplevel;
extern NODE *System;
extern NODE *Error;
extern NODE *End;
extern NODE *Redefp;
extern NODE *Caseignoredp;
extern NODE *Erract;
extern NODE *Printdepthlimit;
extern NODE *Printwidthlimit;
extern NODE *Pause;
extern NODE *If;
extern NODE *Ifelse;
extern NODE *To;
extern NODE *Macro;
extern NODE *Unbound;
extern NODE *Not_Enough_Node;
extern NODE *Minus_Sign;
extern NODE *Minus_Tight;
extern NODE *Startup;
extern NODE *Query;
extern NODE *Output;
extern NODE *Stop;
extern NODE *Goto;
extern NODE *Tag;

// wrksp.cpp
extern bool   to_pending;
extern fpos_t LinesLoadedOnEdit;

// error.cpp
extern NODE *throw_node;
extern ERR_TYPES erract_errtype;

// eval.cpp
extern FIXNUM repcountup;

extern NODE *fun;
extern NODE *ufun;
extern NODE *last_ufun;
extern NODE *this_line;
extern NODE *last_line;
extern NODE *didnt_get_output;
extern NODE *var;
extern NODE *var_stack;
extern NODE *output_node;
extern NODE *last_call;
extern NODE *didnt_output_name;
extern CTRLTYPE stopping_flag;
extern char *logolib;
extern FIXNUM tailcall;
extern FIXNUM val_status;
extern FIXNUM dont_fix_ift;

/* print.cpp */
extern bool print_backslashes;

/* math.cpp */

/* lists.cpp */

/* files.cpp */

/* coms.cpp */
extern FIXNUM ift_iff_flag;

/* term.cpp */
extern int x_coord;
extern int y_coord;
extern int x_max;
extern int y_max;
extern bool interactive;
extern bool in_erase_mode;

/* paren.cpp */
extern NODE *the_generation;

/* graphics.cpp */
extern mode_type   current_mode;
extern bool        bPolyFlag;
extern VERTEXLIST* ThePolygon;

struct Turtle
   {
   MATRIX   Matrix;
   VECTOR   Position;
   FLONUM   Heading;
   long     Bitmap;
   bool     IsShown;
   bool     IsPenUp;
   };

extern Turtle g_Turtles[];
extern VECTOR g_Scale;        // used to scale a picture in scrunch mode.
extern VECTOR g_OneOverScale; // 1 / g_Scale (replaces divides with multiplies)
extern Point  g_Wanna;        // a point where the turtle wants to go
extern int turtle_which;
extern int turtle_max;
extern TThreeDSolid ThreeD;

// graphwin.cpp
typedef HWND WINAPI (*HTMLHELPFUNC)(HWND, LPCSTR, UINT, DWORD);
extern HTMLHELPFUNC g_HtmlHelpFunc;
extern HMODULE      g_HtmlHelpLib;

/* ibmterm.cpp */
extern bool in_graphics_mode;
extern int MaxX;
extern int MaxY;
extern int ibm_screen_top;
const int SIGQUIT = 15;

/* unix.cpp */
extern jmp_buf iblk_buf;

