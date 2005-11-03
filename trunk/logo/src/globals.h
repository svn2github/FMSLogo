
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
extern BOOL bExpert;
extern BOOL bFixed;
extern BOOL bWidth;
extern BOOL bHeight;
//extern BOOL bSilent;
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
extern int traceflag;
extern bool IsDirty;
extern bool error_happen;
extern long eval_count;
extern long vector_count;
extern int memory_count;
extern int status_flag;
extern int keyboard_on;
extern int keyboard_value;
extern int mouse_on;
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
extern SOCKET sendPort;
extern SOCKET receivePort;
extern BOOL bSendConnected;
extern BOOL bSendBusy;
extern BOOL bReceiveConnected;
extern BOOL bReceiveBusy;
extern PHOSTENT phes;
extern PHOSTENT pher;
extern char *network_receive_receive;
extern char *network_receive_send;
extern char *network_send_receive;
extern char *network_send_send;
extern char *network_receive_value;
extern char *network_send_value;
extern int network_send_on;
extern int network_receive_on;

/* logodata.c */
#ifdef ecma
extern char ecma_array[];
extern char special_chars[];
extern int ecma_size;
#endif

/* mem.c */
extern NODE *free_list;
extern struct segment *segment_list;

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
extern NODE *Truex, *Falsex, *Left_Paren, *Right_Paren, *Null_Word, *Toplevel, *System, *Error;
extern NODE *End, *Redefp, *Caseignoredp, *Erract, *Printdepthlimit, *Printwidthlimit, *Pause;
extern NODE *If, *Ifelse, *To, *Macro, *Unbound, *Not_Enough_Node;
extern NODE *Minus_Sign, *Minus_Tight, *Startup, *Query, *Output, *Op, *Stop, *Goto, *Tag;

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

/* print.c */
extern bool print_backslashes;

/* lists.c */

/* files.c */

/* coms.c */
extern FIXNUM ift_iff_flag;

/* term.c */
extern int x_coord, y_coord, x_max, y_max;
extern int interactive;

/* paren.c */
extern NODE *the_generation;

/* graphics.c */
extern mode_type current_mode;
extern BOOL bPolyFlag;
extern VERTEXLIST* ThePolygon;

typedef struct _Turtle
   {
   MATRIX   Matrix;
   VECTOR   Position;
   FLONUM   Heading;
   bool     IsShown;
   long     Bitmap;
   } Turtle;

extern Turtle g_Turtles[];
extern FLONUM x_scale;
extern FLONUM y_scale;
extern FLONUM z_scale;
extern int turtle_which;
extern int turtle_max;
extern TThreeDSolid ThreeD;

#ifdef mac

#define SIGQUIT SIGABRT

/* macterm.c */
extern WindowPtr graphics_window, listener_window;
#endif

#ifdef ibm
/* ibmterm.c/ztcterm.c */
extern bool in_graphics_mode;
extern int MaxX, MaxY;
#ifdef __ZTC__
extern int ibm_screen_bottom, turtle_color;
extern bool in_splitscreen;
#else
extern int ibm_screen_top;
#define SIGQUIT 15
#endif
#endif

#ifdef x_window
/* xgraphics.c */
#endif

