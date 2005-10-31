/*
*      ibmterm.h          IBM-specific graphics macros         mak
*
*       Copyright (C) 1989 The Regents of the University of California
*       This Software may be copied and distributed for educational,
*       research, and not for profit purposes provided that this
*       copyright and statement are included in all such copies.
*
*/

#define GR_SIZE 10000

#define prepare_to_draw nop()
#define done_drawing nop()

#define prepare_to_draw_turtle nop()
#define done_drawing_turtle nop()

#define screen_height (screen_bottom - screen_top)
#define screen_width (screen_right - screen_left)

#define screen_left   (-BitMapWidth/2)
#define screen_right  ( BitMapWidth/2)
#define screen_bottom (-BitMapHeight/2)
#define screen_top    ( BitMapHeight/2)

#define turtle_left_max   (-BitMapWidth/2)
#define turtle_right_max  ( BitMapWidth/2)
#define turtle_bottom_max (-BitMapHeight/2)
#define turtle_top_max    ( BitMapHeight/2)

#define turtle_height t_height()
#define turtle_half_bottom t_half_bottom()
#define turtle_side t_side()

//#define screen_x_coord turtle_p[turtle_which].x
//#define screen_y_coord turtle_p[turtle_which].y
//#define screen_z_coord turtle_p[turtle_which].z

#define clear_screen erase_screen()

#define line_to(x,y) ibmto(x,y)
#define move_to(x,y) ibmfrom(x,y)
#define line_to_3d(x,y,z) ibmto3d(x,y,z)
#define move_to_3d(x,y,z) ibmfrom3d(x,y,z)
#define draw_string(s)                 //outtext((char far *)s)
#define set_pen_vis(v) current_vis[turtle_which] = v
#define set_pen_mode(m) set_ibm_pen_mode(m)
#define set_pen_color(r,g,b) {if (!in_erase_mode) thepencolor(r,g,b);}//ignore//
#define set_flood_color(r,g,b) {if (!in_erase_mode) thefloodcolor(r,g,b);}//ignore//
#define set_screen_color(r,g,b) {if (!in_erase_mode) thescreencolor(r,g,b);}//ignore//
#define set_pen_width(w) set_ibm_pen_width(w)
#define set_pen_height(h) set_ibm_pen_width(h)
#define set_pen_x(x) ibmto((int)x, -gety())
#define set_pen_y(y) ibmto(getx(), -(int)y)

/* pen_info is a stucture type with fields for the various
pen characteristics including the location, size, color,
mode (e.g. XOR or COPY), pattern, visibility (0 = visible) */

typedef struct
   {
   //   int     h;
   //   int       v;
   int vis;
   int width;
   int color, prev_color;
   unsigned char pattern[8];
   int mode;
   }
pen_info;

//#define p_info_x(p) p.h
//#define p_info_y(p) p.v

#define pen_width get_ibm_pen_width()
#define pen_height get_ibm_pen_width()
#define pen_color                      //getcolor()
#define pen_mode get_ibm_pen_mode()
#define pen_vis current_vis[turtle_which]
#define pen_x                          //getx()
#define pen_y                          //gety()
#define get_node_pen_pattern Get_node_pen_pattern()
#define get_node_pen_mode Get_node_pen_mode()

#define pen_reverse ibm_pen_xor()
#define pen_erase ibm_pen_erase()
#define pen_down ibm_pen_down()

#define button Button()
#define mouse_x mickey_x()
#define mouse_y mickey_y()

#define full_screen nop()
#define split_screen nop()
#define text_screen nop()

/* definitions from term.c and math.c for ibmterm.c */
extern int x_coord, y_coord, x_max, y_max, tty_charmode;
/*
extern char so_arr[], se_arr[];
*/
extern FLONUM degrad;

/* definitions from ibmterm.c for graphics.c */
extern int current_vis[], ibm_screen_top, ibm_turtle_top_max;
extern bool in_erase_mode;
