/*
*      graphics.c          logo graphics module          mak
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

#define screen_left   (-BitMapWidth/2)
#define screen_right  ( BitMapWidth/2)
#define screen_bottom (-BitMapHeight/2)
#define screen_top    ( BitMapHeight/2)

#define turtle_left_max   (-BitMapWidth/2)
#define turtle_right_max  ( BitMapWidth/2)
#define turtle_bottom_max (-BitMapHeight/2)
#define turtle_top_max    ( BitMapHeight/2)

COLORREF colortable[16] =
   {
   0x00000000, // black
   0x00FF0000, // blue
   0x0000FF00, // green
   0x00FFFF00, // cyan
   0x000000FF, // red
   0x00FF00FF, // magenta
   0x0000FFFF, // yellow
   0x00FFFFFF, // white
   0x003B609B, // brown
   0x001288C5, // tan
   0x0040A264, // forest
   0x00BBBB78, // aqua
   0x007795FF, // salmon
   0x00D07190, // purple
   0x0000A3FF, // orange
   0x00B7B7B7, // grey
   };

bool bIndexMode = false;

bool        bPolyFlag  = false;
VERTEXLIST* ThePolygon = NULL;

mode_type current_mode = wrapmode;

Turtle g_Turtles[TURTLES] =
   {
      {
         {
         1.0, 0.0, 0.0,
         0.0, 1.0, 0.0,
         0.0, 0.0, 1.0,
         },

         {0.0, 0.0, 0.0},

         0.0,

         true,

         0,
      },
   }
;

int    turtle_which = 0;
int    turtle_max = 0;
VECTOR g_Scale = {1.0, 1.0, 1.0};
Point  g_Wanna = {0.0, 0.0, 0.0};
bool   out_of_bounds = false;

//char record[GR_SIZE];
static int record_index = 0;
static pen_info orig_pen; // DELETEME
static int forward_count = 0; // DELETEME

bool record_next_move = false;
bool refresh_p = true;

#define sq(z) ((z)*(z))

static void forward_helper(FLONUM d);

/************************************************************/

double pfmod(double x, double y)
   {
   double temp = fmod(x, y);

   if (temp < 0) return temp + y;
   return temp;
   }

FLONUM cut_error(FLONUM n)
   {
   if (!bExpert)
      {
      n *= 1000000.0;
      n = (n > 0.0 ? floor(n) : ceil(n));
      n /= 1000000.0;
      if (n == -0.0) n = 0.0;
      }

   return (n);
   }

FIXNUM g_round(FLONUM n)
   {
   n += (n < 0.0 ? -0.5 : 0.5);

   if (n > (FLONUM) LONG_MAX)
      return LONG_MAX;
   else if (n < (FLONUM) LONG_MIN)
      return LONG_MIN;
   else
      return (FIXNUM) n;
   }


static
FLONUM 
numeric_node_to_flonum(
   NODE * numeric_node // TODO: const
)
   {
   FLONUM number;

   if (nodetype(numeric_node) == INT)
      {
      number = (FLONUM) getint(numeric_node);
      }
   else
      {
      number = getfloat(numeric_node);
      }

   return number;
   }

static
FIXNUM 
numeric_node_to_fixnum(
   NODE * numeric_node // TODO: const
)
   {
   FIXNUM number;

   if (nodetype(numeric_node) == INT)
      {
      number = getint(numeric_node);
      }
   else
      {
      number = (FIXNUM) getfloat(numeric_node);
      }

   return number;
   }

/************************************************************/

void draw_turtles(bool erase)
   {
   int temp = turtle_which;

   for (turtle_which = 0; turtle_which <= turtle_max; turtle_which++)
      {
      draw_turtle(erase);
      }

   turtle_which = temp;
   }

void draw_turtle(bool erase)
   {
   if (turtle_which >= TURTLES - TURTLEN)
      {
      ThreeD.SetFrom();
      ThreeD.SetAt();
      ThreeD.SetUp();
      ThreeD.SetVolume();
      ThreeD.SetEye();
      ThreeD.SetLight();
//      if (ThreeD.Tree) ThreeD.View();
      }

   if (g_Turtles[turtle_which].IsShown) 
      {
      ibmturt(erase);
      }
   }

/************************************************************/

void uppitch(FLONUM a)
   {

// if (bPolyFlag)
//    {
//    bPolyFlag = false;
//    ThreeD.DisposeVertices(ThePolygon);
//    ThePolygon = NULL;
//    MainWindowx->CommandWindow->MessageBox("You cannot change pitch while defining a planar polygon", "Pitch Error");
//    err_logo(STOP_ERROR, NIL);
//    }
// else
      {
      draw_turtle(false);

      FLONUM Cx = cos(a * degrad);
      FLONUM Sx = sin(a * degrad);

      MATRIX pitch;
      pitch.e11 = 1.0; pitch.e12 = 0.0; pitch.e13 = 0.0;
      pitch.e21 = 0.0; pitch.e22 = Cx; pitch.e23 = -Sx;
      pitch.e31 = 0.0; pitch.e32 = Sx; pitch.e33 = Cx;

      g_Turtles[turtle_which].Matrix = MMMultiply(
         g_Turtles[turtle_which].Matrix,
         pitch);

      if (status_flag)
         {
         update_status_turtleheading();
         update_status_turtleroll();
         update_status_turtlepitch();
         }

      draw_turtle(true);
      }
   }

void rightroll(FLONUM a)
   {
// if (bPolyFlag)
//   {
//   bPolyFlag = false;
//   ThreeD.DisposeVertices(ThePolygon);
//   ThePolygon = NULL;
//   MainWindowx->CommandWindow->MessageBox("You cannot change roll while defining a planar polygon", "Roll Error");
//   err_logo(STOP_ERROR, NIL);
//   }
// else
      {
      draw_turtle(false);

      FLONUM Cy = cos(a * degrad);
      FLONUM Sy = sin(a * degrad);

      MATRIX roll;
      roll.e11 = Cy;  roll.e12 = 0.0; roll.e13 = Sy;
      roll.e21 = 0.0; roll.e22 = 1.0; roll.e23 = 0.0;
      roll.e31 = -Sy; roll.e32 = 0.0; roll.e33 = Cy;

      g_Turtles[turtle_which].Matrix = MMMultiply(
         g_Turtles[turtle_which].Matrix,
         roll);

      if (status_flag)
         {
         update_status_turtleheading();
         update_status_turtleroll();
         update_status_turtlepitch();
         }

      draw_turtle(true);
      }
   }

void right(FLONUM a)
   {
   draw_turtle(false);
   g_Turtles[turtle_which].Heading += a;
   g_Turtles[turtle_which].Heading = pfmod(g_Turtles[turtle_which].Heading, 360.0);

   if (current_mode == perspectivemode)
      {
      FLONUM Cz = cos(-a * degrad);
      FLONUM Sz = sin(-a * degrad);

      MATRIX turn;
      turn.e11 = Cz;  turn.e12 = -Sz; turn.e13 = 0.0;
      turn.e21 = Sz;  turn.e22 = Cz;  turn.e23 = 0.0;
      turn.e31 = 0.0; turn.e32 = 0.0; turn.e33 = 1.0;

      g_Turtles[turtle_which].Matrix = MMMultiply(
         g_Turtles[turtle_which].Matrix,
         turn);
      }

   if (status_flag)
      {
      update_status_turtleheading();
      update_status_turtleroll();
      update_status_turtlepitch();
      }

   draw_turtle(true);
   }

NODE *numeric_arg(NODE *args)
   {
   NODE *arg = car(args);

   NODE * val = cnv_node_to_numnode(arg);
   while (val == Unbound && NOT_THROWING)
      {
      gcref(val);
      setcar(args, err_logo(BAD_DATA, arg));
      arg = car(args);
      val = cnv_node_to_numnode(arg);
      }
   setcar(args, val);
   return (val);
   }

NODE *luppitch(NODE *arg)
   {
   NODE* val = numeric_arg(arg);
   if (NOT_THROWING)
      {
      FLONUM a = numeric_node_to_flonum(val);
      uppitch(a);
      }
   return Unbound;
   }

NODE *ldownpitch(NODE *arg)
   {
   NODE* val = numeric_arg(arg);
   if (NOT_THROWING)
      {
      FLONUM a = numeric_node_to_flonum(val);
      uppitch(-a);
      }

   return Unbound;
   }

NODE *lrightroll(NODE *arg)
   {
   NODE* val = numeric_arg(arg);
   if (NOT_THROWING)
      {
      FLONUM a = numeric_node_to_flonum(val);
      rightroll(a);
      }

   return Unbound;
   }

NODE *lleftroll(NODE *arg)
   {
   NODE* val = numeric_arg(arg);
   if (NOT_THROWING)
      {
      FLONUM a = numeric_node_to_flonum(val);
      rightroll(-a);
      }
   return Unbound;
   }

NODE *lright(NODE *arg)
   {
   NODE* val = numeric_arg(arg);
   if (NOT_THROWING)
      {
      FLONUM a = numeric_node_to_flonum(val);
      right(a);
      }

   return Unbound;
   }

NODE *lleft(NODE *arg)
   {
   NODE* val = numeric_arg(arg);
   if (NOT_THROWING)
      {
      FLONUM a = numeric_node_to_flonum(val);
      right(-a);
      }

   return Unbound;
   }

static
FLONUM towards_helper(FLONUM x, FLONUM y, FLONUM from_x, FLONUM from_y)
   {
   FLONUM tx = from_x / g_Scale.x;
   FLONUM ty = from_y / g_Scale.y;

   if (x != tx || y != ty)
      {
      FLONUM m, a;
      if (x == tx)
         {
         a = (y < ty) ? -90 : 90;
         }
      else
         {
         m = (y - ty) / (x - tx);
         a = atan(m) / degrad;
         if (x < tx) a = fmod(a + 180.0, 360.0);
         }
      a = -(a - 90.0);
      return (a < 0 ? 360.0 + a : a);
      }

   return 0.0;
   }

static
void 
setpos_helper(
   NODE *xnode, 
   NODE *ynode, 
   NODE *znode, 
   bool bEraseTurtle = true
)
   {

   if (NOT_THROWING)
      {
      if (bEraseTurtle) 
         { 
         draw_turtle(false);
         }

      if (current_mode == perspectivemode)
         {
         move_to_3d(
            g_Turtles[turtle_which].Position.x,
            g_Turtles[turtle_which].Position.y,
            g_Turtles[turtle_which].Position.z);
         }
      else
         {
         move_to(
            g_Turtles[turtle_which].Position.x,
            g_Turtles[turtle_which].Position.y);
         }

      Point target;
      target.x = (xnode == NIL) ?
            g_Turtles[turtle_which].Position.x :
            numeric_node_to_flonum(xnode);

      target.y = (ynode == NIL) ?
            g_Turtles[turtle_which].Position.y :
            numeric_node_to_flonum(ynode);

      target.z = (znode == NIL) ?
            g_Turtles[turtle_which].Position.z :
            numeric_node_to_flonum(znode);

      if (current_mode == perspectivemode)
         {
         g_Wanna = g_Turtles[turtle_which].Position = target;
         out_of_bounds = false;
         line_to_3d(g_Turtles[turtle_which].Position);
         save_line();
         }
      else
         {
         Point scaled;
         scaled.x = target.x * g_Scale.x;
         scaled.y = target.y * g_Scale.y;

         bool wrapping =
            scaled.x > turtle_right_max ||
            scaled.x < turtle_left_max ||
            scaled.y > turtle_top_max ||
            scaled.y < turtle_bottom_max;

         if ((current_mode == fencemode) && wrapping)
            {
            err_logo(TURTLE_OUT_OF_BOUNDS, NIL);
            }
         else if ((current_mode == wrapmode) && (wrapping || out_of_bounds))
            {
            FLONUM save_heading = g_Turtles[turtle_which].Heading;

            g_Turtles[turtle_which].Heading = towards_helper(
               target.x,
               target.y, 
               g_Wanna.x, 
               g_Wanna.y);

            FLONUM tx = g_Wanna.x / g_Scale.x;
            FLONUM ty = g_Wanna.y / g_Scale.y;
            forward_helper(sqrt(sq(target.x - tx) + sq(target.y - ty)));

            g_Turtles[turtle_which].Heading = save_heading;
            g_Wanna.x = scaled.x;
            g_Wanna.y = scaled.y;
            out_of_bounds = wrapping;
            }
         else
            {
            g_Wanna.x = g_Turtles[turtle_which].Position.x = scaled.x;
            g_Wanna.y = g_Turtles[turtle_which].Position.y = scaled.y;
            out_of_bounds = false;
            line_to(
               g_Turtles[turtle_which].Position.x, 
               g_Turtles[turtle_which].Position.y);
            save_line();
            }
         }

      if (bEraseTurtle) 
         {
         draw_turtle(true);
         }
      }
   }

NODE *lellipsearc(NODE *arg)
   {
   NODE *tmp1;
   NODE *tmp2;
   NODE *tmp3;

   FLONUM ang;
   FLONUM rx;
   FLONUM ry;
   FLONUM i;

   VECTOR r;
   VECTOR rp;

   int pen_state = pen_vis;

   /* get args */

   NODE * val1 = numeric_arg(arg);
   NODE * val2 = numeric_arg(cdr(arg));
   NODE * val3 = numeric_arg(cdr(cdr(arg)));
   NODE * val4 = numeric_arg(cdr(cdr(cdr(arg))));

   if (NOT_THROWING)
      {

      FLONUM angle      = numeric_node_to_flonum(val1);
      FLONUM radius_x   = numeric_node_to_flonum(val2);
      FLONUM radius_y   = numeric_node_to_flonum(val3);
      FLONUM startangle = numeric_node_to_flonum(val4);

      draw_turtle(false);

      /* save and force turtle state */
      bool turtle_state = g_Turtles[turtle_which].IsShown;
      g_Turtles[turtle_which].IsShown = false;

      /* grab things before they change and use for restore */

      FLONUM th = g_Turtles[turtle_which].Heading;
      FLONUM tx = g_Turtles[turtle_which].Position.x;
      FLONUM ty = g_Turtles[turtle_which].Position.y;
      FLONUM tz = g_Turtles[turtle_which].Position.z;

      /* calculate resolution parameters */
      FLONUM count = abs(angle * max(radius_x, radius_y) / 200.0);
      if (count == 0.0)
         {
         count = 1.0;
         }
      FLONUM delta = angle / count;

      /* draw each line segment of arc (will do wrap) */

      ang = startangle;
      for (i = 0.0; i <= count - 1.0; i = i + 1.0)
         {

         /* calc x y */
         FLONUM x = -sin(ang * degrad) * radius_x;
         FLONUM y = -cos(ang * degrad) * radius_y;

         /* jump to begin of first line segment without drawing */
         if (i == 0.0) pen_vis = 1;

         /* rotate delta point according to roll around y axis */
         if (current_mode == perspectivemode)
            {
            r.x = x;
            r.y = y;
            r.z = 0.0;

            rp = MVxyMultiply(g_Turtles[turtle_which].Matrix, r);

            setpos_helper(
               tmp1 = make_floatnode(tx + rp.x),
               tmp2 = make_floatnode(ty + rp.y),
               tmp3 = make_floatnode(tz + rp.z),
               false);
            gcref(tmp3);
            }
         else
            {
            /* now rotate about position */

            rx = cos((th - 90.0) * degrad) * y - sin((th - 90.0) * degrad) * x;
            ry = cos((th + 90.0) * degrad) * x + sin((th + 90.0) * degrad) * y;

            setpos_helper(
               tmp1 = make_floatnode(tx + rx),
               tmp2 = make_floatnode(ty + ry),
               NIL,
               false);
            }

         gcref(tmp1);
         gcref(tmp2);

         // restore pen (in case saved)
         pen_vis = pen_state;

         ang = ang + delta;
         }

      /* assure we draw something and end in the exact right place */

//      if (ang != angle + startangle)
         {
         FLONUM x = -sin((angle + startangle) * degrad) * radius_x;
         FLONUM y = -cos((angle + startangle) * degrad) * radius_y;

         if (current_mode == perspectivemode)
            {
            r.x = x;
            r.y = y;
            r.z = 0.0;

            rp = MVxyMultiply(g_Turtles[turtle_which].Matrix, r);

            setpos_helper(
               tmp1 = make_floatnode(tx + rp.x),
               tmp2 = make_floatnode(ty + rp.y),
               tmp3 = make_floatnode(tz + rp.z),
               FALSE);

            gcref(tmp3);
            }
         else
            {
            /* now rotate about position */

            rx = cos((th - 90.0) * degrad) * y - sin((th - 90.0) * degrad) * x;
            ry = cos((th + 90.0) * degrad) * x + sin((th + 90.0) * degrad) * y;

            setpos_helper(
               tmp1 = make_floatnode(tx + rx),
               tmp2 = make_floatnode(ty + ry),
               NIL,
               FALSE);
            }

         gcref(tmp1);
         gcref(tmp2);
         }

      /* restore state */
      g_Turtles[turtle_which].IsShown = turtle_state;

      g_Turtles[turtle_which].Position.x = tx;
      g_Turtles[turtle_which].Position.y = ty;
      g_Turtles[turtle_which].Position.z = tz;

      if (status_flag) update_status_turtleposition();

      draw_turtle(true);
      g_Wanna = g_Turtles[turtle_which].Position;
      out_of_bounds = false;

      }
   return Unbound;
   }


static
bool wrap_right(FLONUM d, FLONUM x1, FLONUM y1, FLONUM x2, FLONUM y2)
   {
   if (x2 > screen_right)
      {
      FLONUM yi = ((y2 - y1) / (x2 - x1)) * (screen_right - x1) + y1;
      if (yi >= screen_bottom && yi <= screen_top)
         {
         line_to(screen_right, yi);
         save_line();
         record_next_move = TRUE;
         g_Turtles[turtle_which].Position.x = turtle_left_max;
         g_Turtles[turtle_which].Position.y = yi;
         if (current_mode == wrapmode)
            {
            forward_helper(d * ((x2 - screen_right) / (x2 - x1)));
            return true;
            }
         g_Turtles[turtle_which].Position.x = turtle_right_max;
         err_logo(TURTLE_OUT_OF_BOUNDS, NIL);
         }
      }
   return false;
   }

static
bool wrap_up(FLONUM d, FLONUM x1, FLONUM y1, FLONUM x2, FLONUM y2)
   {
   if (y2 > screen_top)
      {
      FLONUM xi = ((x2 - x1) / (y2 - y1)) * (screen_top - y1) + x1;
      if (xi >= screen_left && xi <= screen_right)
         {
         line_to(xi, screen_top);
         save_line();
         record_next_move = TRUE;
         g_Turtles[turtle_which].Position.x = xi;
         g_Turtles[turtle_which].Position.y = turtle_bottom_max;
         if (current_mode == wrapmode)
            {
            forward_helper(d * ((y2 - screen_top) / (y2 - y1)));
            return true;
            }
         g_Turtles[turtle_which].Position.y = turtle_top_max;
         err_logo(TURTLE_OUT_OF_BOUNDS, NIL);
         }
      }
   return false;
   }

static
bool wrap_left(FLONUM d, FLONUM x1, FLONUM y1, FLONUM x2, FLONUM y2)
   {
   if (x2 < screen_left)
      {
      FLONUM yi = ((y2 - y1) / (x1 - x2)) * (x1 - screen_left) + y1;
      if (yi >= screen_bottom && yi <= screen_top)
         {
         line_to(screen_left, yi);
         save_line();
         record_next_move = TRUE;
         g_Turtles[turtle_which].Position.x = turtle_right_max;
         g_Turtles[turtle_which].Position.y = yi;
         if (current_mode == wrapmode)
            {
            forward_helper(d * ((screen_left - x2) / (x1 - x2)));
            return true;
            }
         g_Turtles[turtle_which].Position.x = turtle_left_max;
         err_logo(TURTLE_OUT_OF_BOUNDS, NIL);
         }
      }
   return false;
   }

static
bool wrap_down(FLONUM d, FLONUM x1, FLONUM y1, FLONUM x2, FLONUM y2)
   {
   if (y2 < screen_bottom)
      {
      FLONUM xi = ((x2 - x1) / (y1 - y2)) * (y1 - screen_bottom) + x1;
      if (xi >= screen_left && xi <= screen_right)
         {
         line_to(xi, screen_bottom);
         save_line();
         record_next_move = TRUE;
         g_Turtles[turtle_which].Position.x = xi;
         g_Turtles[turtle_which].Position.y = turtle_top_max;
         if (current_mode == wrapmode)
            {
            forward_helper(d * ((screen_bottom - y2) / (y1 - y2)));
            return true;
            }
         g_Turtles[turtle_which].Position.y = turtle_bottom_max;
         err_logo(TURTLE_OUT_OF_BOUNDS, NIL);
         }
      }
   return false;
   }

void forward_helper(FLONUM d)
   {
   if ((forward_count > 32) || !_finite(d))
      {
      return;
      }

   forward_count++;

   FLONUM real_heading = -g_Turtles[turtle_which].Heading + 90.0;
   FLONUM x1 = g_Turtles[turtle_which].Position.x;
   FLONUM y1 = g_Turtles[turtle_which].Position.y;
   FLONUM dx = (FLONUM) (cos((FLONUM) (real_heading * degrad)) * d * g_Scale.x);
   FLONUM dy = (FLONUM) (sin((FLONUM) (real_heading * degrad)) * d * g_Scale.y);
   FLONUM x2 = x1 + dx;
   FLONUM y2 = y1 + dy;

   move_to(x1, y1);
   if (record_next_move)
      {
      save_move();
      record_next_move = FALSE;
      }

   //    if (check_throwing) return;
   //    if (stopping_flag == THROWING) return;

   if (current_mode == windowmode ||
         (
            x2 >= screen_left &&
            x2 <= screen_right &&
            y2 >= screen_bottom &&
            y2 <= screen_top
         ))
      {
      g_Turtles[turtle_which].Position.x = g_Turtles[turtle_which].Position.x + dx;
      g_Turtles[turtle_which].Position.y = g_Turtles[turtle_which].Position.y + dy;
      line_to(x2, y2);
      save_line();
      }
   else
      {
      if (!wrap_right(d, x1, y1, x2, y2))
         if (!wrap_left(d, x1, y1, x2, y2))
            if (!wrap_up(d, x1, y1, x2, y2))
               wrap_down(d, x1, y1, x2, y2);
      }

   forward_count--;
   }

void forward_helper3d(FLONUM d)
   {
   VECTOR direction;

   move_to_3d(g_Turtles[turtle_which].Position.x, g_Turtles[turtle_which].Position.y, g_Turtles[turtle_which].Position.z);

   if (record_next_move)
      {
      save_move();
      record_next_move = FALSE;
      }

   direction.x = 0.0;
   direction.y = d;
   direction.z = 0.0;

   direction = MVyMultiply(g_Turtles[turtle_which].Matrix, direction);

   g_Turtles[turtle_which].Position.x += direction.x;
   g_Turtles[turtle_which].Position.y += direction.y;
   g_Turtles[turtle_which].Position.z += direction.z;

   line_to_3d(g_Turtles[turtle_which].Position);
   save_line();
   }

void forward(FLONUM d)
   {
   draw_turtle(false);
   if (current_mode == perspectivemode)
      forward_helper3d(d);
   else
      forward_helper(d);

   draw_turtle(true);
   g_Wanna = g_Turtles[turtle_which].Position;
   out_of_bounds = false;
   }

NODE *lforward(NODE *arg)
   {
   NODE * val = numeric_arg(arg);
   if (NOT_THROWING)
      {
      FLONUM d = numeric_node_to_flonum(val);
      forward(d);
      }
   return Unbound;
   }

NODE *lback(NODE *arg)
   {
   NODE* val = numeric_arg(arg);
   if (NOT_THROWING)
      {
      FLONUM d = numeric_node_to_flonum(val);
      forward(-d);
      }
   return Unbound;
   }

NODE *lbitmapturtle(NODE *)
   {
   draw_turtle(false);
   g_Turtles[turtle_which].Bitmap = SRCCOPY;
   draw_turtle(true);
   return Unbound;
   }

NODE *lnobitmapturtle(NODE *)
   {
   draw_turtle(false);
   g_Turtles[turtle_which].Bitmap = 0;
   draw_turtle(true);
   return Unbound;
   }

NODE *lshowturtle(NODE *)
   {
   if (!g_Turtles[turtle_which].IsShown)
      {
      g_Turtles[turtle_which].IsShown = true;
      if (status_flag) update_status_turtlevisability();
      draw_turtle(true);
      }
   return Unbound;
   }

NODE *lhideturtle(NODE *)
   {
   if (g_Turtles[turtle_which].IsShown)
      {
      draw_turtle(false);
      g_Turtles[turtle_which].IsShown = false;
      if (status_flag) update_status_turtlevisability();
      }
   return Unbound;
   }

NODE *lshownp(NODE *)
   {
   return g_Turtles[turtle_which].IsShown ? Truex : Falsex;
   }

NODE *lsetheading(NODE *arg)
   {
   NODE *val = numeric_arg(arg);
   if (NOT_THROWING)
      {
      draw_turtle(false);

      FLONUM a = numeric_node_to_flonum(val);
      a = pfmod(a, 360.0);

      if (current_mode == perspectivemode)
         right(a - rotation_z());
      else
         g_Turtles[turtle_which].Heading = a;

      if (status_flag)
         {
         update_status_turtleheading();
         update_status_turtleroll();
         update_status_turtlepitch();
         }

      draw_turtle(true);
      }
   return Unbound;
   }

NODE *lsetroll(NODE *arg)
   {
   NODE* val = numeric_arg(arg);
   if (NOT_THROWING)
      {
      draw_turtle(false);

      FLONUM a = numeric_node_to_flonum(val);
      a = pfmod(a, 360.0);

      rightroll(a - rotation_y());

      if (status_flag)
         {
         update_status_turtleheading();
         update_status_turtleroll();
         update_status_turtlepitch();
         }

      draw_turtle(true);
      }
   return Unbound;
   }

NODE *lsetpitch(NODE *arg)
   {
   NODE * val = numeric_arg(arg);
   if (NOT_THROWING)
      {
      draw_turtle(false);

      FLONUM a = numeric_node_to_flonum(val);
      a = pfmod(a, 360.0);
      uppitch(a - rotation_x());

      if (status_flag)
         {
         update_status_turtleheading();
         update_status_turtleroll();
         update_status_turtlepitch();
         }

      draw_turtle(true);
      }
   return Unbound;
   }

NODE *lsetclip(NODE *args)
   {
   NODE* angle = numeric_arg(args);
   NODE* zmin = numeric_arg(cdr(args));
   NODE* zmax = numeric_arg(cdr(cdr(args)));

   if (NOT_THROWING)
      {
      draw_turtle(false);

      FLONUM _Angle = numeric_node_to_flonum(angle);
      FLONUM _Zmin  = numeric_node_to_flonum(zmin);
      FLONUM _Zmax  = numeric_node_to_flonum(zmax);

      ThreeD.SetClip(_Angle, _Zmin, _Zmax);

      draw_turtle(true);
      }
   return Unbound;
   }

const double epsilon=1.0e-12;

/* rotations such that heading has no dependedncies */

FLONUM rotation_z()
   {
   FLONUM m11 = g_Turtles[turtle_which].Matrix.e11;
   FLONUM m12 = g_Turtles[turtle_which].Matrix.e12;
   FLONUM m21 = g_Turtles[turtle_which].Matrix.e21;
   FLONUM m22 = g_Turtles[turtle_which].Matrix.e22;
   FLONUM m23 = g_Turtles[turtle_which].Matrix.e23;

   FLONUM result;

   if ((1.0 - fabs(m23)) < epsilon)
      {
      result = atan2(m12, m11) / degrad;
      }
   else
      {
      result = atan2(-m21, m22) / degrad;
      }

   if (result < 0.0) return result + 360.0; else return result;
   }

FLONUM rotation_y()
   {
   FLONUM m13 = g_Turtles[turtle_which].Matrix.e13;
   FLONUM m23 = g_Turtles[turtle_which].Matrix.e23;
   FLONUM m33 = g_Turtles[turtle_which].Matrix.e33;

   FLONUM result;

   if ((1.0 - fabs(m23)) < epsilon)
      {
      return 0.0;
      }
   else
      {
      result = atan2(m13, m33) / degrad;
      }

   if (result < 0.0) return result + 360.0; else return result;
   }

FLONUM rotation_x()
   {
   FLONUM m13 = g_Turtles[turtle_which].Matrix.e13;
   FLONUM m23 = g_Turtles[turtle_which].Matrix.e23;
   FLONUM m33 = g_Turtles[turtle_which].Matrix.e33;

   FLONUM result;

   if ((1.0 - fabs(m23)) < epsilon)
      {
      return (m23 < 0.0) ? 90.0 : 270.0;
      }
   else
      {
      FLONUM ry = atan2(-m13, m33);

      FLONUM a;
      if (fabs(fabs(ry) - 90.0 * degrad) < epsilon)
         a = m13 / sin(-ry);
      else
         a = m33 / cos(ry);

      result = atan2(-m23, a) / degrad;
      }

   if (result < 0.0) return result + 360.0; else return result;
   }

NODE *lheading(NODE *)
   {
   if (current_mode == perspectivemode)
      return (make_floatnode(rotation_z()));
   else
      return (make_floatnode(g_Turtles[turtle_which].Heading));
   }

NODE *lroll(NODE *)
   {
   if (current_mode == perspectivemode)
      return (make_floatnode(rotation_y()));
   else
      return (make_floatnode(0.0));
   }

NODE *lpitch(NODE *)
   {
   if (current_mode == perspectivemode)
      return (make_floatnode(rotation_x()));
   else
      return (make_floatnode(0.0));
   }

NODE *vec_arg_helper(NODE *args, bool floatok)
   {
   NODE *arg = car(args);

   while (NOT_THROWING)
      {
      if (arg != NIL &&
            is_list(arg) &&
            cdr(arg) != NIL &&
            cddr(arg) == NIL)
         {
         NODE * val1 = cnv_node_to_numnode(car(arg));
         NODE * val2 = cnv_node_to_numnode(cadr(arg));
         if (val1 != Unbound && val2 != Unbound &&
            (
            floatok ||
            (
            (nodetype(val1) == INT && getint(val1) >= 0 || nodetype(val1) == FLOAT && getfloat(val1) >= 0.0)&&
            (nodetype(val2) == INT && getint(val2) >= 0 || nodetype(val2) == FLOAT && getfloat(val2) >= 0.0)
            )
            )
            )
            {
            setcar(arg, val1);
            setcar(cdr(arg), val2);
            return (arg);
            }
         gcref(val1);
         gcref(val2);
         }
      setcar(args, err_logo(BAD_DATA, arg));
      arg = car(args);
      }
   return Unbound;
   }

NODE *vec_3_arg_helper(NODE *args, bool floatok)
   {
   NODE *arg = car(args);

   while (NOT_THROWING)
      {
      if (arg != NIL &&
            is_list(arg) &&
            cdr(arg) != NIL &&
            cddr(arg) != NIL &&
            cddr(cdr(arg)) == NIL)
         {
         NODE * val1 = cnv_node_to_numnode(car(arg));
         NODE * val2 = cnv_node_to_numnode(cadr(arg));
         NODE * val3 = cnv_node_to_numnode(cadr(cdr(arg)));
         if (
            val1 != Unbound &&
            val2 != Unbound &&
            val3 != Unbound &&
            (
            floatok ||
            (
            (nodetype(val1) == INT && getint(val1) >= 0 || nodetype(val1) == FLOAT && getfloat(val1) >= 0.0)&&
            (nodetype(val2) == INT && getint(val2) >= 0 || nodetype(val2) == FLOAT && getfloat(val2) >= 0.0)&&
            (nodetype(val3) == INT && getint(val3) >= 0 || nodetype(val3) == FLOAT && getfloat(val3) >= 0.0)
            )
            )
            )
            {
            setcar(arg, val1);
            setcar(cdr(arg), val2);
            setcar(cddr(arg), val3);
            return (arg);
            }
         gcref(val1);
         gcref(val2);
         gcref(val3);
         }
      setcar(args, err_logo(BAD_DATA, arg));
      arg = car(args);
      }
   return Unbound;
   }

NODE *vec_4_arg_helper(NODE *args, bool floatok)
   {
   NODE *arg = car(args);

   while (NOT_THROWING)
      {
      if (arg != NIL &&
            is_list(arg) &&
            cdr(arg) != NIL &&
            cdr(cdr(arg)) != NIL &&
            cdr(cdr(cdr(arg))) != NIL &&
            cdr(cdr(cdr(cdr(arg)))) == NIL)
         {
         NODE* val1 = cnv_node_to_numnode(car(arg));
         NODE* val2 = cnv_node_to_numnode(car(cdr(arg)));
         NODE* val3 = cnv_node_to_numnode(car(cdr(cdr(arg))));
         NODE* val4 = cnv_node_to_numnode(car(cdr(cdr(cdr(arg)))));
         if (
               val1 != Unbound &&
               val2 != Unbound &&
               val3 != Unbound &&
               val4 != Unbound &&
               (floatok || (
                     nodetype(val1) == INT && getint(val1) >= 0 &&
                     nodetype(val2) == INT && getint(val2) >= 0 &&
                     nodetype(val3) == INT && getint(val3) >= 0 &&
                     nodetype(val4) == INT && getint(val4) >= 0)))
            {
            setcar(arg, val1);
            setcar(cdr(arg), val2);
            setcar(cdr(cdr(arg)), val3);
            setcar(cdr(cdr(cdr(arg))), val4);
            return (arg);
            }
         gcref(val1);
         gcref(val2);
         gcref(val3);
         gcref(val4);
         }
      setcar(args, err_logo(BAD_DATA, arg));
      arg = car(args);
      }
   return Unbound;
   }

NODE *vector_arg(NODE *args)
   {
   return vec_arg_helper(args, TRUE);
   }

NODE *vector_3_arg(NODE *args)
   {
   return vec_3_arg_helper(args, TRUE);
   }

NODE *vector_4_arg(NODE *args)
   {
   return vec_4_arg_helper(args, TRUE);
   }

NODE *pos_int_vector_arg(NODE *args)
   {
   return vec_arg_helper(args, FALSE);
   }

NODE *pos_int_vector_3_arg(NODE *args)
   {
   return vec_3_arg_helper(args, FALSE);
   }

NODE *pos_int_vector_4_arg(NODE *args)
   {
   return vec_4_arg_helper(args, FALSE);
   }


NODE *ltowards(NODE *args)
   {
   NODE * arg = vector_arg(args);
   if (NOT_THROWING)
      {
      NODE * xnode = car(arg);
      NODE * ynode = cadr(arg);

      FLONUM x = numeric_node_to_flonum(xnode);
      FLONUM y = numeric_node_to_flonum(ynode);

      return make_floatnode(towards_helper(x, y, g_Turtles[turtle_which].Position.x, g_Turtles[turtle_which].Position.y));
      }
   return Unbound;
   }

NODE *ltowardsxyz(NODE *args)
   {
   NODE * arg = vector_3_arg(args);
   if (NOT_THROWING)
      {
      NODE * xnode = car(arg);
      NODE * ynode = cadr(arg);
      NODE * znode = cadr(cdr(arg));

      VECTOR to;
      to.x = numeric_node_to_flonum(xnode);
      to.y = numeric_node_to_flonum(ynode);
      to.z = numeric_node_to_flonum(znode);

      // Generate a Vector to represent direction we need to head
      VECTOR diff = Subtract(to, g_Turtles[turtle_which].Position);
      Normalize(diff);

      // Compute angle between Y Axis and Vector [DOT] (Rotation about Z)
      FLONUM Rz = acos(diff.y) / degrad;

      // Project point onto X-Z plane and renormalize to measure roll
      diff.y = 0.0;
      Normalize(diff);

      // Compute angle between X Axis and Projection [DOT] (Rotation about Y)
      FLONUM Ry = acos(diff.x) / degrad;

      // Heading was limited to 0 to 180 but we must be able to roll -180 to 180
      // if point is in positive Z hemisphere then "roll" left to it.
      if (diff.z > 0.0) Ry = -Ry;

      // No Pitch needed
      FLONUM Rx = 0.0;

      return cons_list(
         make_floatnode(Ry),
         make_floatnode(Rx),
         make_floatnode(Rz));
      }

   return Unbound;
   }

NODE *lpos(NODE *)
   {
   return cons_list(
      make_floatnode(cut_error(g_Turtles[turtle_which].Position.x / g_Scale.x)),
      make_floatnode(cut_error(g_Turtles[turtle_which].Position.y / g_Scale.y)));
   }

NODE *lposxyz(NODE *)
   {
   return cons_list(
      make_floatnode(cut_error(g_Turtles[turtle_which].Position.x / g_Scale.x)),
      make_floatnode(cut_error(g_Turtles[turtle_which].Position.y / g_Scale.y)),
      make_floatnode(cut_error(g_Turtles[turtle_which].Position.z / g_Scale.z)));
   }

NODE *lscrunch(NODE *)
   {
   return cons_list(
      make_floatnode(g_Scale.x),
      make_floatnode(g_Scale.y));
   }

NODE *lhome(NODE *)
   {
   NODE *tmp1;
   NODE *tmp2;
   NODE *tmp3;

   out_of_bounds = false;
   setpos_helper(tmp1 = make_intnode((FIXNUM) 0), tmp2 = make_intnode((FIXNUM) 0), tmp3 = make_intnode((FIXNUM) 0));
   gcref(tmp1);
   gcref(tmp2);
   gcref(tmp3);

   draw_turtle(false);
   g_Turtles[turtle_which].Heading = 0.0;
   g_Turtles[turtle_which].Matrix.e11 = 1.0;
   g_Turtles[turtle_which].Matrix.e12 = 0.0;
   g_Turtles[turtle_which].Matrix.e13 = 0.0;
   g_Turtles[turtle_which].Matrix.e21 = 0.0;
   g_Turtles[turtle_which].Matrix.e22 = 1.0;
   g_Turtles[turtle_which].Matrix.e23 = 0.0;
   g_Turtles[turtle_which].Matrix.e31 = 0.0;
   g_Turtles[turtle_which].Matrix.e32 = 0.0;
   g_Turtles[turtle_which].Matrix.e33 = 1.0;
   draw_turtle(true);
   return Unbound;
   }

static
void cs_helper(bool centerp, bool clearp)
   {
   bPolyFlag = false;
   ThreeD.DisposeVertices(ThePolygon);
   ThePolygon = NULL;
   ThreeD.DisposeTree();
   if (status_flag) update_status_vectors();

   if (clearp) 
      {
      erase_screen();
      }

   if (centerp)
      {
      turtle_max = 0;
      turtle_which = 0;
      g_Turtles[turtle_which].Bitmap = 0;
      g_Wanna.x = 0.0;
      g_Wanna.y = 0.0;
      g_Wanna.z = 0.0;
      g_Turtles[turtle_which].Position.x = 0.0;
      g_Turtles[turtle_which].Position.y = 0.0;
      g_Turtles[turtle_which].Position.z = 0.0;
      g_Turtles[turtle_which].Heading = 0.0;
      g_Turtles[turtle_which].Matrix.e11 = 1.0;
      g_Turtles[turtle_which].Matrix.e12 = 0.0;
      g_Turtles[turtle_which].Matrix.e13 = 0.0;
      g_Turtles[turtle_which].Matrix.e21 = 0.0;
      g_Turtles[turtle_which].Matrix.e22 = 1.0;
      g_Turtles[turtle_which].Matrix.e23 = 0.0;
      g_Turtles[turtle_which].Matrix.e31 = 0.0;
      g_Turtles[turtle_which].Matrix.e32 = 0.0;
      g_Turtles[turtle_which].Matrix.e33 = 1.0;

      if (status_flag)
         {
         update_status_turtleheading();
         update_status_turtleroll();
         update_status_turtlepitch();
         update_status_turtleposition();
         update_status_turtlewhich();
         }

      out_of_bounds = false;
      }
   draw_turtle(true);
   save_pen(&orig_pen);
   //   p_info_x(orig_pen) = g_round(screen_x_coord);
   //   p_info_y(orig_pen) = g_round(screen_y_coord);
   record_index = 0;
   }

NODE *lclearscreen(NODE *)
   {
   cs_helper(TRUE, TRUE);
//   InvalidateControls();
   return Unbound;
   }

NODE *lclean(NODE *)
   {
   cs_helper(FALSE, TRUE);
   return Unbound;
   }

NODE *lsetpos(NODE *args)
   {
   NODE *arg = vector_arg(args);

   if (NOT_THROWING)
      {
      setpos_helper(car(arg), cadr(arg), NIL);
      }
   return Unbound;
   }

NODE *lsetposxyz(NODE *args)
   {
   NODE *arg = vector_3_arg(args);

   if (NOT_THROWING)
      {
      setpos_helper(car(arg), cadr(arg), cadr(cdr(arg)));
      }
   return Unbound;
   }

NODE *lsetxy(NODE *args)
   {
   NODE *xnode, *ynode;

   xnode = numeric_arg(args);
   ynode = numeric_arg(cdr(args));
   if (NOT_THROWING)
      {
      setpos_helper(xnode, ynode, NIL);
      }
   return Unbound;
   }

NODE *lsetxyz(NODE *args)
   {
   NODE *xnode, *ynode, *znode;

   xnode = numeric_arg(args);
   ynode = numeric_arg(cdr(args));
   znode = numeric_arg(cdr(cdr(args)));
   if (NOT_THROWING)
      {
      setpos_helper(xnode, ynode, znode);
      }
   return Unbound;
   }

NODE *lsetx(NODE *args)
   {
   NODE *xnode;

   xnode = numeric_arg(args);
   if (NOT_THROWING)
      {
      setpos_helper(xnode, NIL, NIL);
      }
   return Unbound;
   }

NODE *lsety(NODE *args)
   {
   NODE *ynode;

   ynode = numeric_arg(args);
   if (NOT_THROWING)
      {
      setpos_helper(NIL, ynode, NIL);
      }
   return Unbound;
   }

NODE *lsetz(NODE *args)
   {
   NODE *znode;

   znode = numeric_arg(args);
   if (NOT_THROWING)
      {
      setpos_helper(NIL, NIL, znode);
      }
   return Unbound;
   }

NODE *lwrap(NODE *)
   {
   draw_turtle(false);
   cs_helper(TRUE, FALSE);
   current_mode = wrapmode;
   draw_turtle(true);
   return Unbound;
   }

NODE *lfence(NODE *)
   {
   draw_turtle(false);
   current_mode = fencemode;
   draw_turtle(true);
   return Unbound;
   }

NODE *lwindow(NODE *)
   {
   draw_turtle(false);
   current_mode = windowmode;
   draw_turtle(true);

   return Unbound;
   }

NODE *lsetlight(NODE *args)
   {
   NODE * arg = vector_arg(args);
   if (NOT_THROWING)
      {
      NODE * ambient = car(arg);
      NODE * diffuse = cadr(arg);

      ThreeD.Ambient = numeric_node_to_flonum(ambient);
      ThreeD.Diffuse = numeric_node_to_flonum(diffuse);

      if (ThreeD.Tree) 
         {
         ThreeD.View();
         }
      }

   return Unbound;
   }

NODE *llight(NODE *)
   {
   return cons_list(
      make_floatnode(ThreeD.Ambient),
      make_floatnode(ThreeD.Diffuse));
   }

NODE *lpolystart(NODE *)
   {

   if (bPolyFlag)
      {
      bPolyFlag = false;
      ThreeD.DisposeVertices(ThePolygon);
      ThePolygon = NULL;
      MainWindowx->CommandWindow->MessageBox("You already have a Polygon started", "PolyStart Error");
      err_logo(STOP_ERROR, NIL);
      }
   else
      {
      bPolyFlag = true;
      }

   return Unbound;
   }

NODE *lpolyview(NODE *)
   {
   if (ThreeD.Tree) ThreeD.View();

   return Unbound;
   }

NODE *lpolyend(NODE *)
   {

   if (bPolyFlag)
      {
      if (ThePolygon && (ThePolygon != ThePolygon->Next) && (ThePolygon->Next != ThePolygon->Next->Next))
         {
         ThreeD.AddPolygon(ThePolygon, pcolor);
         }
      else
         {
         ThreeD.DisposeVertices(ThePolygon);
         ThePolygon = NULL;
         MainWindowx->CommandWindow->MessageBox(
            "You must have at least 3 vectors to define a polygon",
            "PolyEnd Error");
         err_logo(STOP_ERROR, NIL);
         }
      }
   else
      {
      ThreeD.DisposeVertices(ThePolygon);
      MainWindowx->CommandWindow->MessageBox(
         "You have not started a Polygon",
         "PolyEnd Error");
      err_logo(STOP_ERROR, NIL);
      }

   ThePolygon = NULL;
   bPolyFlag = false;

   return Unbound;
   }

NODE *lperspective(NODE *)
   {
   draw_turtle(false);
   current_mode = perspectivemode;
   g_Turtles[TURTLES - 3].Position.x = 400.0;       // From
   g_Turtles[TURTLES - 3].Position.y = 400.0;
   g_Turtles[TURTLES - 3].Position.z = 600.0;
   g_Turtles[TURTLES - 3].Heading = 0.0;
   g_Turtles[TURTLES - 3].Matrix.e11 = 1.0;
   g_Turtles[TURTLES - 3].Matrix.e12 = 0.0;
   g_Turtles[TURTLES - 3].Matrix.e13 = 0.0;
   g_Turtles[TURTLES - 3].Matrix.e21 = 0.0;
   g_Turtles[TURTLES - 3].Matrix.e22 = 1.0;
   g_Turtles[TURTLES - 3].Matrix.e23 = 0.0;
   g_Turtles[TURTLES - 3].Matrix.e31 = 0.0;
   g_Turtles[TURTLES - 3].Matrix.e32 = 0.0;
   g_Turtles[TURTLES - 3].Matrix.e33 = 1.0;

   g_Turtles[TURTLES - 2].Position.x = 0.0;         // At
   g_Turtles[TURTLES - 2].Position.y = 0.0;
   g_Turtles[TURTLES - 2].Position.z = 0.0;
   g_Turtles[TURTLES - 2].Heading = 0.0;
   g_Turtles[TURTLES - 2].Matrix.e11 = 1.0;
   g_Turtles[TURTLES - 2].Matrix.e12 = 0.0;
   g_Turtles[TURTLES - 2].Matrix.e13 = 0.0;
   g_Turtles[TURTLES - 2].Matrix.e21 = 0.0;
   g_Turtles[TURTLES - 2].Matrix.e22 = 1.0;
   g_Turtles[TURTLES - 2].Matrix.e23 = 0.0;
   g_Turtles[TURTLES - 2].Matrix.e31 = 0.0;
   g_Turtles[TURTLES - 2].Matrix.e32 = 0.0;
   g_Turtles[TURTLES - 2].Matrix.e33 = 1.0;

   g_Turtles[TURTLES - 1].Position.x = 0.0;             // Light
   g_Turtles[TURTLES - 1].Position.y = 0.0;
   g_Turtles[TURTLES - 1].Position.z = 1000.0;
   g_Turtles[TURTLES - 1].Heading = 0.0;
   g_Turtles[TURTLES - 1].Matrix.e11 = 1.0;
   g_Turtles[TURTLES - 1].Matrix.e12 = 0.0;
   g_Turtles[TURTLES - 1].Matrix.e13 = 0.0;
   g_Turtles[TURTLES - 1].Matrix.e21 = 0.0;
   g_Turtles[TURTLES - 1].Matrix.e22 = 1.0;
   g_Turtles[TURTLES - 1].Matrix.e23 = 0.0;
   g_Turtles[TURTLES - 1].Matrix.e31 = 0.0;
   g_Turtles[TURTLES - 1].Matrix.e32 = 0.0;
   g_Turtles[TURTLES - 1].Matrix.e33 = 1.0;

   ThreeD.SetLight();
   ThreeD.SetFrom();
   ThreeD.SetAt();
   ThreeD.SetUp();
   ThreeD.SetVolume();
   ThreeD.SetEye();
   ThreeD.SetClip(60.0, 100000.0, -100000.0);
   if (ThreeD.Tree) 
     {
     ThreeD.View();
     }

   draw_turtle(true);
   return Unbound;
   }

NODE *lfill(NODE *arg)
   {
   bool bOld;

   draw_turtles(false);
   MainWindowx->ScreenWindow->UpdateWindow();
   if (arg != NIL)
      {
      bOld = boolean_arg(arg);
      }
   else
      {
      bOld = false;
      }

   logofill(bOld);
   MainWindowx->ScreenWindow->Invalidate(false);
   draw_turtles(true);
   return Unbound;
   }

NODE *llabelsize(NODE *arg)
   {
   char textbuf[MAX_BUFFER_SIZE];
   cnv_strnode_string(textbuf, arg);

   if (NOT_THROWING)
      {
      SIZE size;
      size = labelsize(textbuf);
      return cons_list(
         make_intnode((FIXNUM) size.cx),
         make_intnode((FIXNUM) size.cy));
      }
   return Unbound;
   }

NODE *llabel(NODE *arg)
   {
   char textbuf[MAX_BUFFER_SIZE];
   //    short theLength;

   print_stringptr = textbuf;
   print_stringlen = MAX_BUFFER_SIZE;
   ndprintf((FILE *) NULL, "%p", car(arg));
   *print_stringptr = '\0';

   if (NOT_THROWING)
      {
      draw_turtle(false);
      label(textbuf);
      save_string(textbuf);
      record_next_move = TRUE;
      draw_turtle(true);
      }
   return Unbound;
   }

NODE *ltextscreen(NODE *)
   {
   return Unbound;
   }

NODE *lsplitscreen(NODE *)
   {
   return Unbound;
   }

NODE *lfullscreen()
   {
   return Unbound;
   }

NODE *lpendownp(NODE *)
   {
   return (pen_vis == 0 ? Truex : Falsex);
   }

NODE *lpenmode(NODE *)
   {
   return get_node_pen_mode();
   }

NODE *lpensize(NODE *)
   {
   return cons_list(
      make_intnode((FIXNUM) get_pen_width()),
      make_intnode((FIXNUM) get_pen_height()));
   }

NODE *lpenpattern(NODE *)
   {
   return get_node_pen_pattern();
   }

NODE *lpendown(NODE *)
   {
   pen_vis = 0;
   save_vis();
   return Unbound;
   }

NODE *lpenup(NODE *)
   {
   if (pen_vis == 0)
      pen_vis--;
   save_vis();
   return Unbound;
   }

NODE *lpenpaint(NODE *)
   {
   pen_down();
   save_mode();
   return lpendown(NIL);
   }

NODE *lpenerase(NODE *)
   {
   pen_erase();
   save_mode();
   return lpendown(NIL);
   }

NODE *lpenreverse(NODE *)
   {
   pen_reverse();
   save_mode();
   return lpendown(NIL);
   }


static
NODE *
setcolor_helper(
   NODE *args,
   void (*setcolorfunc)  (int, int, int),
   void (*savecolorfunc) (void)
)
   {
   if (is_list(car(args)))
      {
      NODE * arg = pos_int_vector_3_arg(args);

      if (NOT_THROWING)
         {
         if (!in_erase_mode)
            {
            setcolorfunc(
               numeric_node_to_fixnum(car(arg)),
               numeric_node_to_fixnum(cadr(arg)),
               numeric_node_to_fixnum(cadr(cdr(arg))));
            }
         savecolorfunc();
         }

      bIndexMode = false;
      }
   else
      {
      NODE * cnode = numeric_arg(args);

      if (NOT_THROWING)
         {
         int icolor = numeric_node_to_fixnum(cnode) % 16;
         if (!in_erase_mode)
            {
            setcolorfunc(
               GetRValue(colortable[icolor]), 
               GetGValue(colortable[icolor]), 
               GetBValue(colortable[icolor]));
            }
         savecolorfunc();
         }

      bIndexMode = true;
      }

   return Unbound;
   }


NODE *lsetpencolor(NODE *args)
   {
   return setcolor_helper(args, thepencolor, save_color_pen);
   }

NODE *lsetfloodcolor(NODE *args)
   {
   return setcolor_helper(args, thefloodcolor, save_color_flood);
   }

NODE *lsetscreencolor(NODE *args)
   {
   return setcolor_helper(args, thescreencolor, save_color_screen);
   }

NODE *lsetpensize(NODE *args)
   {
   NODE * arg = pos_int_vector_arg(args);

   if (NOT_THROWING)
      {
      set_pen_width(numeric_node_to_fixnum(car(arg)));
      set_pen_height(numeric_node_to_fixnum(cadr(arg)));
      save_size();
      }
   return Unbound;
   }

NODE *lsetpenpattern(NODE *args)
   {

   NODE * arg = car(args);
   ref(arg);
   while ((arg == NIL || !is_list(arg)) && NOT_THROWING)
      {
      arg = reref(arg, err_logo(BAD_DATA, arg));
      }

   if (NOT_THROWING)
      {
      set_list_pen_pattern(arg);
      save_pattern();
      }

   deref(arg);
   return Unbound;
   }

NODE *lsetscrunch(NODE *args)
   {
   NODE * xnode = numeric_arg(args);
   NODE * ynode = numeric_arg(cdr(args));

   if (NOT_THROWING)
      {
      draw_turtle(false);
      g_Scale.x = numeric_node_to_flonum(xnode);
      g_Scale.y = numeric_node_to_flonum(ynode);
      draw_turtle(true);
      }
   return Unbound;
   }

NODE *lbuttonp(NODE *)
   {
   if (button)
      return Truex;
   return Falsex;
   }

NODE *ltone(NODE *args) 
   {
   NODE * pitchnode    = numeric_arg(args);
   NODE * durationnode = numeric_arg(cdr(args));

   if (NOT_THROWING)
      { 
      FIXNUM pitch    = numeric_node_to_fixnum(pitchnode);
      FIXNUM duration = numeric_node_to_fixnum(durationnode);
      tone(pitch, duration);
      }
         
   return Unbound;
   }

/************************************************************/
/* The rest of this file implements the recording of moves in
the graphics window and the playing back of those moves.  It's
needed on machines like the Macintosh where the contents of the
graphics window can get erased and need to be redrawn.  On
machines where no graphics redrawing is necessary, set the size
of the recording buffer to 1 in logo.h. */

bool safe_to_save()
   {
   /*
      return(refresh_p && record_index < (GR_SIZE - 300));
    */
   return (1);
   }

void save_lm_helper()
   {
   /*
    *(int *)(record + record_index + 2) = pen_x;
    *(int *)(record + record_index + 4) = pen_y;
      record_index += 6;
    */
   }

void save_line()
   {
   if (status_flag) update_status_turtleposition();
   /*
      if (safe_to_save())
      {
      record[record_index] = LINEXY;
      save_lm_helper();
      }
    */
   }

void save_move()
   {
   if (status_flag) update_status_turtleposition();
   /*
      if (safe_to_save())
      {
      record[record_index] = MOVEXY;
      save_lm_helper();
      }
    */
   }

void save_vis()
   {
   if (status_flag) update_status_pencontact();
   /*
      if (safe_to_save())
      {
      record[record_index] = SETPENVIS;
      record[record_index + 1] = (char)pen_vis;
      record_index += 2;
      }
    */
   }

void save_mode()
   {
   if (status_flag) update_status_penstyle();
   /*
      if (safe_to_save())
      {
      record[record_index] = SETPENMODE;
#ifdef x_window
      *(GC *)(record + record_index + 2) = pen_mode;
#else
      *(int *)(record + record_index + 2) = pen_mode;
#endif
      record_index += 4;
      }
   */
   }

void save_color_pen()
   {
   if (status_flag) update_status_pencolor();
   /*
      if (safe_to_save())
      {
      record[record_index] = SETPENCOLOR;
    *(long *)(record + record_index + 2) = pen_color;
      record_index += 6;
      }
    */
   }

void save_color_screen()
   {
   if (status_flag) update_status_screencolor();
   /*
      if (safe_to_save())
      {
      record[record_index] = SETPENCOLOR;
    *(long *)(record + record_index + 2) = pen_color;
      record_index += 6;
      }
    */
   }

void save_color_flood()
   {
   if (status_flag) update_status_floodcolor();
   /*
      if (safe_to_save())
      {
      record[record_index] = SETPENCOLOR;
    *(long *)(record + record_index + 2) = pen_color;
      record_index += 6;
      }
    */
   }

void save_size()
   {
   if (status_flag) update_status_penwidth();
   /*
      if (safe_to_save())
      {
      record[record_index] = SETPENSIZE;
      *(int *)(record + record_index + 2) = get_pen_width();
      *(int *)(record + record_index + 4) = get_pen_height();
      record_index += 6;
      }
    */
   }

void save_pattern()
   {
   //    if (status_flag) update_status(SETPENPATTERN);
   /*
      int count;

      if (safe_to_save())
      {
      record[record_index] = SETPENPATTERN;
      get_pen_pattern(&record[record_index + 2]);
      record_index += 10;
      }
    */
   }

void save_string(char /* s */[])
   {
   /*
      int count;

      if (safe_to_save())
      {
      record[record_index] = LABEL;
      record[record_index + 2] = s[0];
      for (count = 0; count < s[0]; count++)
      record[record_index + 3 + count] = s[1 + count];
      record_index += 3 + s[0] + even_p(s[0]);
      }
    */
   }

NODE *lrefresh()
   {
   refresh_p = TRUE;
   return Unbound;
   }

NODE *lnorefresh()
   {
   refresh_p = FALSE;
   return Unbound;
   }

void redraw_graphics()
   {
   }

/* This is called when the graphics coordinate system has been shifted.
It adds a constant amount to each x and y coordinate in the record. */
void resize_record(int /* dh */, int /* dv */)
   {
   /*
      int r_index = 0;

   //   p_info_x(orig_pen) += dh;
   //   p_info_y(orig_pen) += dv;

      while (r_index < record_index)
      switch (record[r_index])
      {
      case (LINEXY) :
    *(int *)(record + r_index + 2) += dh;
    *(int *)(record + r_index + 4) += dv;
      r_index += 6;
      break;
      case (MOVEXY) :
    *(int *)(record + r_index + 2) += dh;
    *(int *)(record + r_index + 4) += dv;
      r_index += 6;
      break;
      case (LABEL) :
      r_index += 3 + record[r_index + 2] + even_p(record[r_index + 2]);
      break;
      case (SETPENVIS) :
      r_index += 2;
      break;
      case (SETPENMODE) :
      r_index += 4;
      break;
      case (SETPENCOLOR) :
      r_index += 6;
      break;
      case (SETPENSIZE) :
      r_index += 6;
      break;
      case (SETPENPATTERN) :
      r_index += 10;
      break;
      }
    */
   }

