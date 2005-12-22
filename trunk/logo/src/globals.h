
/*
*      globals.h       logo global references module           dvb
*
*       Copyright (C) 1989 The Regents of the University of California
*       This Software may be copied and distributed for educational,
*       research, and not for profit purposes provided that this
*       copyright and statement are included in all such copies.
*
*/

/* extern double atof();

/* main.c */
extern int yield_flag;
extern int GCMAX;
extern int MAX_PHYS_LINE;
// extern int ROUNDPOS;
// extern int BUFFERTYPE;
extern bool bExpert;
extern bool bFixed;
extern bool bWidth;
extern bool bHeight;
extern char *combo_buff;
extern char *p_line;
extern NODE **hash_table;
extern NODE **gcstack;
extern NODE **gctop;
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

/* mem.c */
#ifdef MEM_DEBUG
extern long int mem_allocated;
extern long int mem_freed;
#endif

/* parse.c */
extern FILE *loadstream, *writestream, *readstream, *dribblestream;
extern int input_blocking;
extern NODE *current_line;
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
extern NODE *Op;
extern NODE *Stop;
extern NODE *Goto;
extern NODE *Tag;

/* wrksp.c */
extern int to_pending;
extern fpos_t LinesLoadedOnEdit;

/* error.c */
extern NODE *throw_node;
extern NODE *err_mesg;
extern ERR_TYPES erract_errtype;

/* eval.c */
//extern FIXNUM global_repcount[];
//extern FIXNUM global_repcount_index;
extern FIXNUM repcountup;

extern NODE *fun, *ufun, *last_ufun, *this_line, *last_line, *didnt_get_output;
extern NODE *var, *var_stack, *output_node, *last_call, *didnt_output_name;
extern CTRLTYPE stopping_flag;
extern char *logolib;
extern FIXNUM tailcall, val_status, dont_fix_ift;

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
extern int tty_charmode;
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
extern VECTOR g_Scale;     // used to scale a picture in scrunch mode.
extern Point  g_Wanna;     // a point where the turtle wants to go
extern int turtle_which;
extern int turtle_max;
extern TThreeDSolid ThreeD;

/* ibmterm.cpp */
extern bool in_graphics_mode;
extern int MaxX, MaxY;
extern int ibm_screen_top;
const int SIGQUIT = 15;

/* unix.cpp */
extern jmp_buf iblk_buf;

