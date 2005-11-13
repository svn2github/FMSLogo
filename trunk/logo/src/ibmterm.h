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

#define clear_screen erase_screen()

#define line_to(x,y) ibmto(x,y)
#define move_to(x,y) ibmfrom(x,y)
#define move_to_3d(x,y,z) ibmfrom3d(x,y,z)
#define draw_string(s)                 //outtext((char far *)s)
#define set_pen_vis(v) current_vis[turtle_which] = v

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

#define pen_vis current_vis[turtle_which]

