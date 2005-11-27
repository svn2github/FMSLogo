/*
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

#define TWindow_type 1
#define TStatic_type 2
#define TListBox_type 3
#define TComboBox_type 4
#define TButton_type 5
#define TScrollBar_type 6
#define TGroupBox_type 7
#define TRadioButton_type 8
#define TCheckBox_type 9
#define TDialog_type 10


static HICON hCursorSave = 0; // handle for saved cursor

static const char *Windowname[] =
   {
       "?",
       "Window",
       "Static",
       "ListBox",
       "ComboBox",
       "Button",
       "ScrollBar",
       "GroupBox",
       "RadioButton",
       "CheckButton",
       "Dialog",
   };

/* class structure for storing information about users windows */

class slink
   {
   friend class slist;

   slink *next;
   slink *prev;
   char *key;
   char *parent;
   int type;
   void * e;

   slink (void * a, slink *n, slink *p, char *k, char *par, int t)
      {
      e = a;
      next = n;
      prev = p;
      key = k;
      parent = par;
      type = t;
      }
   }
;

class slist
   {
   slink *last;
   public:
   void insert(void * a, char *k, char *par, int t);
   void * get(char *k);
   void * get2(char *k, int t);
   char *getrootkey();
   int gettype(char *k);
   char *getparent(char *par);
   void zap(char *k);
   void * zapall();
   void list(char *k, int lev);
   void listall();
   void clear();
   BOOL OnScreenControlsExist();

   slist()
      {
      last = NULL;
      }

   slist (void * a, char *k, char *par, int t)
      {
      last = new slink (a, NULL, NULL, k, par, t);
      last->next = last;
      last->prev = last;
      }

   ~slist()
      {
      clear();
      }
   }
;

void slist::insert(void * a, char *k, char *par, int t)
   {
   if (last)
      {
      last->next = new slink (a, last->next, last, k, par, t);
      last->next->next->prev = last->next;
      }
   else
      {
      last = new slink (a, NULL, NULL, k, par, t);
      last->next = last;
      last->prev = last;
      }
   }

void * slist::get2(char *k, int t)
   {
   slink *f;

   if (last == NULL) return NULL;

   f = last;

   do
      {
      if (strcmp(f->key, k) == 0)
         {
         if (f->type == t) return (f->e); else return (NULL);
         }
      f = f->next;
      }
   while (f != last);

   return NULL;
   }

void * slist::get(char *k)
   {
   slink *f;

   if (last == NULL) return NULL;

   f = last;

   do
      {
      if (strcmp(f->key, k) == 0)
         {
         return (f->e);
         }
      f = f->next;
      }
   while (f != last);

   return NULL;
   }

int slist::gettype(char *k)
   {
   slink *f;

   if (last == NULL) return NULL;

   f = last;

   do
      {
      if (strcmp(f->key, k) == 0)
         {
         return (f->type);
         }
      f = f->next;
      }
   while (f != last);

   return NULL;
   }

char *slist::getparent(char *k)
   {
   slink *f;

   if (last == NULL) return NULL;

   f = last;

   do
      {
      if (strcmp(f->parent, k) == 0)
         {
         return (f->key);
         }
      f = f->next;
      }
   while (f != last);

   return NULL;
   }

void slist::zap(char *k)
   {
   slink *f;
   slink *p;
   char *t;

   if (last == NULL) return;

   f = last;
   p = NULL;

   do
      {
      if (strcmp(f->key, k) == 0)
         {
         p = f;
         break;
         }
      f = f->next;
      }
   while (f != last);

   // delete any children first

   while ((t = getparent(k)) != NULL)
      {
      zap(t);
      }

   if (p != NULL)
      {
      f = p->next;

      if (f == p)
         {
         last = NULL;
         }
      else
         {
         if (p == last) last = p->prev;

         p->prev->next = p->next;
         f->prev = p->prev;
         }

      delete p;
      }

   }

void slist::list(char *k, int level)
   {
   slink *f;
   slink *ff;
   slink *p;
   char temp[128];
   char indent[128];
   int i;

   if (last == NULL) return;

   f = last;
   p = NULL;

   do
      {
      if (strcmp(f->key, k) == 0)
         {
         p = f;
         break;
         }
      f = f->next;
      }
   while (f != last);

   if (p != NULL)
      {

      indent[0] = '\0';
      for (i = 0; i < level; i++) strcat(indent, " ");

      if (level == 0)
         {
         sprintf(temp, "%s %s", Windowname[p->type], p->key);
         putcombobox(temp);
         }

      ff = last;

      do
         {
         if (strcmp(ff->parent, k) == 0)
            {
            sprintf(temp, "  %s%s %s", indent, Windowname[ff->type], ff->key);
            putcombobox(temp);
            list(ff->key, level + 1);
            }
         ff = ff->next;
         }
      while (ff != last);

      }
   }

void slist::clear()
   {
   slink *l = last;

   if (l == NULL) return;

   do
      {
      slink *ll = l;
      l = l->next;
      delete ll;
      }
   while (l != last);

   }

void * slist::zapall()
   {
   slink *l = last;

   if (l == NULL) return NULL;

   do
      {
      if (l->parent == (char *)MainWindowx->ScreenWindow)
         {
         return(l->e);
         }
      l = l->next;
      }
   while (l != last);

   return NULL;
   }

char *slist::getrootkey()
   {
   slink *l = last;

   if (l == NULL) return NULL;

   do
      {
      if (l->parent == (char *)MainWindowx->ScreenWindow)
         {
         return(l->key);
         }
      l = l->next;
      }
   while (l != last);

   return NULL;
   }

void slist::listall()
   {
   slink *l = last;

   if (l == NULL) return;

   do
      {
      if (l->parent == (char *)MainWindowx->ScreenWindow)
         {
         list(l->key, 0);
         }
      l = l->next;
      }
   while (l != last);
   }

BOOL slist::OnScreenControlsExist()
   {
   slink *l = last;

   if (l == NULL) return FALSE;

   do
      {
      if (l->parent == (char *)MainWindowx->ScreenWindow)
         {
         if ((l->type != TWindow_type) && (l->type != TDialog_type))
         return TRUE;
         }
      l = l->next;
      }
   while (l != last);

   return FALSE;
   }

// class structures for the controls we support, for the most part they
// are the same as the original with just a key and callback string added

class TMxWindow : public TDialog
   {
   public:
   char key[MAX_BUFFER_SIZE];
   char caption[MAX_BUFFER_SIZE];
   char callback[MAX_BUFFER_SIZE];
   int x, y, h, w;
   TMxWindow(TWindow *AParent, LPSTR AText) : TDialog(AParent, AText)
      {
      }
   ;
   void SetupWindow();
   void CmCancel()
      {
      }
   ;
   void CmOk()
      {
      }
   ;
   DECLARE_RESPONSE_TABLE(TMxWindow);
   }
;

void TMxWindow::SetupWindow()
   {
   ::SetWindowPos(HWindow, NULL, x, y, w, h, 0);
   SetCaption(caption);

   do_execution(callback);

   TDialog::SetupWindow();
   }

class TMxDialog : public TDialog
   {
   public:
   char key[MAX_BUFFER_SIZE];
   char callback[MAX_BUFFER_SIZE];
   char caption[MAX_BUFFER_SIZE];
   int x, y, h, w;
   TMxDialog(TWindow *AParent, LPSTR AText) : TDialog(AParent, AText)
      {
      }
   ;
   void SetupWindow();
   void CmCancel()
      {
      }
   ;
   void CmOk()
      {
      }
   ;
   DECLARE_RESPONSE_TABLE(TMxDialog);
   }
;

void TMxDialog::SetupWindow()
   {
   SetWindowPos(NULL, x, y, w, h, 0);
   SetCaption(caption);

   do_execution(callback);

   TDialog::SetupWindow();
   }

class TMyListBox : public TListBox
   {
   public:
   char key[MAX_BUFFER_SIZE];
   TMyListBox(TWindow *AParent, int AnId, int X, int Y,
      int W, int H, TModule _FAR *AModule = NULL) :
   TListBox(AParent, AnId, X, Y, W, H, AModule)
      {
      }
   ;
   }
;

class TMxComboBox : public TComboBox
   {
   public:
   char key[MAX_BUFFER_SIZE];
   TMxComboBox(TWindow *AParent, int AnId, int X, int Y,
      int W, int H, DWORD AStyle, WORD ATextLen, TModule _FAR *AModule = NULL) :
   TComboBox(AParent, AnId, X, Y, W, H, AStyle, ATextLen, AModule)
      {
      }
   ;
   }
;

class TMyStatic : public TStatic
   {
   public:
   char key[MAX_BUFFER_SIZE];
   TMyStatic(TWindow *AParent, int AnId, LPSTR AText, int X, int Y,
      int W, int H, WORD ATextLen, TModule _FAR *AModule = NULL) :
   TStatic(AParent, AnId, AText, X, Y, W, H, ATextLen, AModule)
      {
      }
   ;
   }
;

class TMyButton : public TButton
   {
   public:
   char key[MAX_BUFFER_SIZE];
   char callback[MAX_BUFFER_SIZE];

   int critical;
   TMyButton(TWindow *AParent, int AnId, LPSTR AText, int X, int Y,
      int W, int H, BOOL IsDefault, TModule _FAR *AModule = NULL) :
   TButton(AParent, AnId, AText, X, Y, W, H, IsDefault, AModule)
      {
      }
   ;
   void EvLButtonUp(UINT modKeys, TPoint &point);
   DECLARE_RESPONSE_TABLE(TMyButton);
   }
;

NODE *leventcheck(NODE *)
   {
   MSG msg;

   //   checkqueue();

   while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
      }

   return Unbound;
   }

/* function that processes our own queued events */

void checkqueue()
   {
   callthing *thing;

   while (thing = calllists.get())
      {
      int save_yield_flag;
      int sv_val_status;

      sv_val_status = val_status;

      calllists.zap();
      switch (thing->kind)
         {
         // mouse event must not yield while processing
         case EVENTTYPE_Mouse:
            {
            save_yield_flag = yield_flag;
            yield_flag = 0;
            mouse_posx = thing->arg1;
            mouse_posy = thing->arg2;
            do_execution(thing->func);
            yield_flag = save_yield_flag;
            break;
            }

          // keyboard event must not yield while processing
          case EVENTTYPE_Keyboard:
             {
             save_yield_flag = yield_flag;
             yield_flag = 0;
             keyboard_value = thing->arg1;
             do_execution(thing->func);
             yield_flag = save_yield_flag;
             break;
             }

          // Button, timer or other event ok to yield while processing
          case EVENTTYPE_YieldFunction:
             {
             do_execution(thing->func);
             break;
             }

          // Scrollbar, MCI, Net, timer or other event must not yield while processing
          case EVENTTYPE_NoYieldFunction:
             {
             save_yield_flag = yield_flag;
             yield_flag = 0;
             do_execution(thing->func);
             yield_flag = save_yield_flag;
             break;
             }

          // Network events must not yield while processing
          case EVENTTYPE_NetworkReceive:
             {
             save_yield_flag = yield_flag;
             yield_flag = 0;
             if (thing->networkpacket != NULL)
                {
                strcpy(network_receive_value, thing->networkpacket);
                free(thing->networkpacket);
                thing->networkpacket = NULL;
                }
             do_execution(thing->func);
             yield_flag = save_yield_flag;
             break;
             }

          // Network events must not yield while processing
          case EVENTTYPE_NetworkSend:
             {
             save_yield_flag = yield_flag;
             yield_flag = 0;
             if (thing->networkpacket != NULL)
                {
                strcpy(network_send_value, thing->networkpacket);
                free(thing->networkpacket);
                thing->networkpacket = NULL;
                }
             do_execution(thing->func);
             yield_flag = save_yield_flag;
             break;
             }
         }

      delete thing;

      val_status = sv_val_status;
      }
   }

/* function to dump the queue */

void emptyqueue()
   {
   callthing *thing;

   while (thing = calllists.get())
      {
      calllists.zap();
      switch (thing->kind)
         {
         // TODO: move this logic into callthing's destructor
         case EVENTTYPE_NetworkReceive:
         case EVENTTYPE_NetworkSend:
            {
            free(thing->networkpacket);
            break;
            }
         }

      delete thing;
      }
   }

/* if the button gets clicked we end up here and queue the event */

void TMyButton::EvLButtonUp(UINT /* modKeys */, TPoint & /* point */)
   {
   DefaultProcessing();

   callthing *callevent = callthing::CreateFunctionEvent(callback);
   calllists.insert(callevent);
   checkqueue();
   }

class TMyScrollBar : public TScrollBar
   {
   public:
   char key[MAX_BUFFER_SIZE];
   char callback[MAX_BUFFER_SIZE];
   int critical;
   TMyScrollBar(TWindow *AParent, int AnId, int X, int Y,
      int W, int H, BOOL IsHScrollBar, TModule _FAR *AModule = NULL) :
   TScrollBar(AParent, AnId, X, Y, W, H, IsHScrollBar, AModule)
      {
      }
   ;

   void SetPosition(int, bool redraw = true);
   }
;

void TMyScrollBar::SetPosition(int thumbpos, bool redraw)
   {
   TScrollBar::SetPosition(thumbpos, redraw);

   callthing *callevent = callthing::CreateNoYieldFunctionEvent(callback);
   calllists.insert(callevent);
   checkqueue();
   }

class TMyGroupBox : public TGroupBox
   {
   public:
   char key[MAX_BUFFER_SIZE];
   TMyGroupBox(TWindow *AParent, int AnId, LPSTR AText, int X, int Y,
      int W, int H, TModule _FAR *AModule = NULL) :
   TGroupBox(AParent, AnId, AText, X, Y, W, H, AModule)
      {
      }
   ;
   }
;

class TMyRadioButton : public TRadioButton
   {
   public:
   char key[MAX_BUFFER_SIZE];
   int critical;
   char callback[MAX_BUFFER_SIZE];
   TMyRadioButton(TWindow *AParent, int AnId, LPSTR ATitle, int X, int Y,
      int W, int H, TGroupBox _FAR *AGroup, TModule _FAR *AModule = NULL) :
   TRadioButton(AParent, AnId, ATitle, X, Y, W, H, AGroup, AModule)
      {
      }
   ;
   }
;

class TMyCheckBox : public TCheckBox
   {
   public:
   char key[MAX_BUFFER_SIZE];
   int critical;
   char callback[MAX_BUFFER_SIZE];
   TMyCheckBox(TWindow *AParent, int AnId, LPSTR ATitle, int X, int Y,
      int W, int H, TGroupBox _FAR *AGroup, TModule _FAR *AModule = NULL) :
   TCheckBox(AParent, AnId, ATitle, X, Y, W, H, AGroup, AModule)
      {
      }
   ;
   }
;

struct dialogthing
   {
   union
      {
      TMxWindow      * TWmybox;
      TMyStatic      * TSmybox;
      TMyListBox     * TLmybox;
      TMxComboBox    * TCmybox;
      TMyButton      * TBmybox;
      TMyScrollBar   * TSCmybox;
      TMyGroupBox    * TGmybox;
      TMyRadioButton * TRmybox;
      TMyCheckBox    * TCBmybox;
      TMxDialog      * TDmybox;
      };
   };

struct dialoglist : slist
   {
   void insert(dialogthing *a, char *k, char *par, int t)
      {
      slist::insert(a, k, par, t);
      }
   dialogthing *get(char *k)
      {
      return (dialogthing *) slist::get(k);
      }
   dialogthing *get2(char *k, int t)
      {
      return (dialogthing *) slist::get2(k, t);
      }
   dialogthing *zapall()
      {
      return (dialogthing *) slist::zapall();
      }
   dialoglist()
      {
      }
   dialoglist(dialogthing *a, char *k, char *par, int t) : slist (a, k, par, t)
      {
      }
   }
;

dialoglist dialogboxes;

/* User function to create a modeless window */

NODE *lwindowcreate(NODE *args)
   {
   dialogthing *child;
   dialogthing *parent;
   int x;
   int y;
   int w;
   int h;
   char parentname[MAX_BUFFER_SIZE];
   char childname[MAX_BUFFER_SIZE];
   char titlename[MAX_BUFFER_SIZE];
   char callback[MAX_BUFFER_SIZE];
   char *ptr;

   /* get all the args */

   cnv_strnode_string(parentname, args);
   cnv_strnode_string(childname, args = cdr(args));
   cnv_strnode_string(titlename, args = cdr(args));
   x =            int_arg(args = cdr(args)) ;
   y =            int_arg(args = cdr(args)) ;
   w = getint(pos_int_arg(args = cdr(args)));
   h = getint(pos_int_arg(args = cdr(args)));
   if (cdr(args) != NIL) cnv_strnode_string(callback, cdr(args));
   else callback[0] = '\0';


   // convert them to "DIALOG" units this is the key to making
   // all Graphics Modes work correctly.

   x = (x * BaseUnitsx) / 4;
   y = (y * BaseUnitsy) / 8;
   w = (w * BaseUnitsx) / 4;
   h = (h * BaseUnitsy) / 8;

   // if not already exist continue

   if (dialogboxes.get(childname) == NULL)
      {

      child = new dialogthing;

      // if parent exists use it else use main window

      if ((parent = dialogboxes.get2(parentname, TWindow_type)) != NULL)
         {
         child->TWmybox = new TMxWindow(
            parent->TWmybox,
            "DIALOGSTUB");
         ptr = (char *)parent->TWmybox;
         }
      else
         {
         child->TWmybox = new TMxWindow(
            MainWindowx->ScreenWindow,
            "DIALOGSTUB");
         ptr = (char *)MainWindowx->ScreenWindow;
         }

      // Modeless windows can have to have a callback to set them up
      // since it will return

      strcpy(child->TWmybox->callback, callback);
      strcpy(child->TWmybox->caption, titlename);

      // Most attributes are set in DIALOGSTUB

      child->TWmybox->x = x;
      child->TWmybox->y = y;
      child->TWmybox->w = w;
      child->TWmybox->h = h;

      strcpy(child->TWmybox->key, childname);
      dialogboxes.insert(child, child->TWmybox->key, ptr, TWindow_type);

      child->TWmybox->Create();
      child->TWmybox->ShowWindow(SW_SHOW);

      // Make sure the window is up before we try to add controls?

      MyMessageScan();
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox(childname, "Already exists");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }


void windowdelete_helper()
   {
   char *tempkey;
   int temptype;
   dialogthing *temp;

   while (tempkey = dialogboxes.getrootkey())
      {
      if (temptype = dialogboxes.gettype(tempkey))
         {
         if (temp = dialogboxes.get(tempkey))
            {
            switch (temptype)
               {
               case TWindow_type:      temp->TWmybox->CloseWindow(); break;
               case TStatic_type:      temp->TSmybox->CloseWindow(); break;
               case TListBox_type:     temp->TLmybox->CloseWindow(); break;
               case TComboBox_type:    temp->TCmybox->CloseWindow(); break;
               case TButton_type:      temp->TBmybox->CloseWindow(); break;
               case TScrollBar_type:   temp->TSCmybox->CloseWindow(); break;
               case TGroupBox_type:    temp->TGmybox->CloseWindow(); break;
               case TRadioButton_type: temp->TRmybox->CloseWindow(); break;
               case TCheckBox_type:    temp->TCBmybox->CloseWindow(); break;
               case TDialog_type:      temp->TDmybox->CloseWindow(); break;
               }

            dialogboxes.zap(tempkey);
            }
         else
            {
            break;
            }
         }
      else
         {
         break;
         }
      }
   }

static
NODE *
WindowEnableHelper(
   NODE *args,
   int   WindowType
)
   {
   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args);
   bool bEnable = boolean_arg(cdr(args));

   dialogthing *temp;
   if ((temp = dialogboxes.get2(childname, WindowType)) != NULL)
      {
      switch (WindowType)
         {
         case TWindow_type:
            temp->TWmybox->EnableWindow(bEnable);
            break;

         case TDialog_type:
            temp->TDmybox->EnableWindow(bEnable);
            break;

         case TListBox_type:
            temp->TLmybox->EnableWindow(bEnable);
            break;

         case TComboBox_type:
            temp->TCmybox->EnableWindow(bEnable);
            break;

         case TScrollBar_type:
            temp->TSCmybox->EnableWindow(bEnable);
            break;

         case TButton_type:
            temp->TBmybox->EnableWindow(bEnable);
            break;

         case TRadioButton_type:
            temp->TRmybox->EnableWindow(bEnable);
            break;

         case TCheckBox_type:
            temp->TCBmybox->EnableWindow(bEnable);
            break;
         }
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox(childname, "Does not exist");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }


static
NODE *
WindowDeleteHelper(
   NODE *args,
   int   WindowType
)
   {
   // get args
   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args);

   // if it exists kill it
   dialogthing *temp;
   if ((temp = dialogboxes.get2(childname, WindowType)) != NULL)
      {
      switch (WindowType)
         {
         case TWindow_type:
            temp->TWmybox->CloseWindow();
            break;

         case TDialog_type:
            temp->TDmybox->CloseWindow();
            break;

         case TListBox_type:
            temp->TLmybox->CloseWindow();
            break;

         case TComboBox_type:
            temp->TCmybox->CloseWindow();
            break;

         case TScrollBar_type:
            temp->TSCmybox->CloseWindow();
            break;

         case TButton_type:
            temp->TBmybox->CloseWindow();
            break;

         case TRadioButton_type:
            temp->TRmybox->CloseWindow();
            break;

         case TCheckBox_type:
            temp->TCBmybox->CloseWindow();
            break;
         }

      dialogboxes.zap(childname);
      UpdateZoomControlFlag();
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox(childname, "Does not exist");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }


NODE *lwindowenable(NODE *args)
   {
   return WindowEnableHelper(args, TWindow_type);
   }

NODE *lwindowdelete(NODE *arg)
   {
   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, arg);

   if (NOT_THROWING)
      {
      // Check if exact name and type exists and if does kill it
      // and all of its children, too
      dialogthing *temp;
      if ((temp = dialogboxes.get2(childname, TWindow_type)) != NULL)
         {
         temp->TWmybox->CloseWindow();

         dialogboxes.zap(childname);
         }
      else
         {
         windowdelete_helper();
         }
      }
   
   return Unbound;
   }

NODE *ldialogcreate(NODE *args)
   {
   dialogthing *child;
   dialogthing *parent;
   int x;
   int y;
   int w;
   int h;
   char parentname[MAX_BUFFER_SIZE];
   char childname[MAX_BUFFER_SIZE];
   char titlename[MAX_BUFFER_SIZE];
   char callback[MAX_BUFFER_SIZE];
   char *ptr;

   // get args

   cnv_strnode_string(parentname, args);
   cnv_strnode_string(childname, args = cdr(args));
   cnv_strnode_string(titlename, args = cdr(args));
   x =            int_arg(args = cdr(args)) ;
   y =            int_arg(args = cdr(args)) ;
   w = getint(pos_int_arg(args = cdr(args)));
   h = getint(pos_int_arg(args = cdr(args)));
   if (cdr(args) != NIL) cnv_strnode_string(callback, cdr(args));
   else callback[0] = '\0';

   // convert to "DIALOG" units. This is the key to getting consistent
   // results in all graphics MODEs.

   x = (x * BaseUnitsx) / 4;
   y = (y * BaseUnitsy) / 8;
   w = (w * BaseUnitsx) / 4;
   h = (h * BaseUnitsy) / 8;

   // if it does not exist continue

   if (dialogboxes.get(childname) == NULL)
      {

      // make one

      child = new dialogthing;

      // if parent of corect type exists use it

      if ((parent = dialogboxes.get2(parentname, TWindow_type)) != NULL)
         {
         child->TDmybox = new TMxDialog(parent->TWmybox, "DIALOGSTUB");
         ptr = (char *)parent->TWmybox;
         }
      else
         {
         // else use main window
         child->TDmybox = new TMxDialog(
            MainWindowx->ScreenWindow,
            "DIALOGSTUB");
         ptr = (char *)MainWindowx->ScreenWindow;
         }

      // Modal windows have to have a callback to set them up
      // since it will not return until closed

      strcpy(child->TDmybox->callback, callback);
      strcpy(child->TDmybox->caption, titlename);

      // Most attributes are set in DIALOGSTUB

      child->TDmybox->x = x;
      child->TDmybox->y = y;
      child->TDmybox->w = w;
      child->TDmybox->h = h;

      strcpy(child->TDmybox->key, childname);
      dialogboxes.insert(child, child->TDmybox->key, ptr, TDialog_type);

      // Note will not return until the Window closes
      // But the LOGO program still has some control through
      // the callback which is done through OWLs "SetupWindow".

      child->TDmybox->Execute();
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox(
         childname,
         "Already exists");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *ldialogenable(NODE *args)
   {
   return WindowEnableHelper(args, TDialog_type);
   }
   
NODE *ldialogdelete(NODE *args)
   {
   return WindowDeleteHelper(args, TDialog_type);
   }

NODE *llistboxcreate(NODE *args)
   {
   dialogthing *child;
   dialogthing *parent;
   int x;
   int y;
   int w;
   int h;
   char parentname[MAX_BUFFER_SIZE];
   char childname[MAX_BUFFER_SIZE];

   // get args

   cnv_strnode_string(parentname, args);
   cnv_strnode_string(childname, args = cdr(args));
   x = int_arg(args = cdr(args));
   y = int_arg(args = cdr(args));
   w = int_arg(args = cdr(args));
   h = int_arg(cdr(args));

   if (NOT_THROWING)
      {
      // if unique continue

      if (dialogboxes.get(childname) == NULL)
         {
         // If modeless parent then continue
         
         if ((parent = dialogboxes.get2(parentname, TWindow_type)) != NULL)
            {
            
            // convert to "DIALOG" units.
            
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;
            
            child = new dialogthing;
            
            child->TLmybox = new TMyListBox(parent->TWmybox, MYLISTBOX_ID, x, y, w, h);
            child->TLmybox->Attr.Style ^= LBS_SORT;
            
            child->TLmybox->Create();
            
            MyMessageScan();
            
            strcpy(child->TLmybox->key, childname);
            dialogboxes.insert(child, child->TLmybox->key, parent->TWmybox->key, TListBox_type);
            }
         
         // else if modal window continue
         
         else if ((parent = dialogboxes.get2(parentname, TDialog_type)) != NULL)
            {
            
            // convert to "DIALOG" units.
            
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;

            child = new dialogthing;
            
            child->TLmybox = new TMyListBox(parent->TDmybox, MYLISTBOX_ID, x, y, w, h);
            
            child->TLmybox->Attr.Style ^= LBS_SORT;
            
            child->TLmybox->Create();
            
            MyMessageScan();
            
            strcpy(child->TLmybox->key, childname);
            dialogboxes.insert(child, child->TLmybox->key, parent->TDmybox->key, TListBox_type);
            }
         else
            {
            
            child = new dialogthing;
            
            child->TLmybox = new TMyListBox(
               MainWindowx->ScreenWindow,
               MYLISTBOX_ID,
               +x - MainWindowx->ScreenWindow->Scroller->XPos+xoffset,
               -y - MainWindowx->ScreenWindow->Scroller->YPos+yoffset,
               w,
               h);

            child->TLmybox->Attr.Style ^= LBS_SORT;

            child->TLmybox->Create();

            MyMessageScan();

            strcpy(child->TLmybox->key, childname);
            dialogboxes.insert(
               child,
               child->TLmybox->key,
               (char *)MainWindowx->ScreenWindow,
               TListBox_type);

            UpdateZoomControlFlag();
            //       MainWindowx->CommandWindow->MessageBox(parentname, "Does not exist");
            //       err_logo(STOP_ERROR, NIL);
            }
         }
      else
         {
         MainWindowx->CommandWindow->MessageBox(childname, "Already exists");
         err_logo(STOP_ERROR, NIL);
         }
      }
   
   return Unbound;
   }

NODE *llistboxenable(NODE *args)
   {
   return WindowEnableHelper(args, TListBox_type);
   }

NODE *llistboxdelete(NODE *args)
   {
   return WindowDeleteHelper(args, TListBox_type);
   }

NODE *llistboxgetselect(NODE *args)
   {
   // get args
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   // If it exists continue
   dialogthing *parent;
   if ((parent = dialogboxes.get2(parentname, TListBox_type)) != NULL)
      {
      // if success on fetching string return it
      char stringname[MAX_BUFFER_SIZE];
      if (parent->TLmybox->GetSelString(stringname, MAX_BUFFER_SIZE) >= 0)
         {
         // parsing it basically turns it into a list for us
         NODE * val = parser(
            make_strnode(stringname, strlen(stringname), STRING, strnzcpy), 
            FALSE);
         return (val);
         }
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox(parentname, "Does not exist");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *llistboxaddstring(NODE *args)
   {

   // get args
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   char stringname[MAX_BUFFER_SIZE];
   cnv_strnode_string(stringname, cdr(args));

   // if exists continue
   dialogthing *parent;
   if ((parent = dialogboxes.get2(parentname, TListBox_type)) != NULL)
      {
      // add entry and reset Index for consistency
      parent->TLmybox->AddString(stringname);
      parent->TLmybox->SetSelIndex(0);
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox(parentname, "Does not exist");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *llistboxdeletestring(NODE *args)
   {
   dialogthing *parent;
   int index;
   char parentname[MAX_BUFFER_SIZE];

   // get args

   cnv_strnode_string(parentname, args);
   index = getint(pos_int_arg(cdr(args)));

   // if exists continue

   if ((parent = dialogboxes.get2(parentname, TListBox_type)) != NULL)
      {
      // kill entry based on index
      parent->TLmybox->DeleteString(index);
      parent->TLmybox->SetSelIndex(0);
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox(parentname, "Does not exist");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *lcomboboxcreate(NODE *args)
   {
   dialogthing *child;
   dialogthing *parent;
   int x;
   int y;
   int w;
   int h;
   char parentname[MAX_BUFFER_SIZE];
   char childname[MAX_BUFFER_SIZE];

   // get args

   cnv_strnode_string(parentname, args);
   cnv_strnode_string(childname, args = cdr(args));
   x = int_arg(args = cdr(args));
   y = int_arg(args = cdr(args));
   w = int_arg(args = cdr(args));
   h = int_arg(cdr(args));

   if (NOT_THROWING)
      {
      // if unique continue

      if (dialogboxes.get(childname) == NULL)
         {
         // if modeless window enter here

         if ((parent = dialogboxes.get2(parentname, TWindow_type)) != NULL)
            {
            // convert to "DIALOG" units
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;
            
            // create thingy
            
            child = new dialogthing;
            
            child->TCmybox = new TMxComboBox(parent->TWmybox, MYCOMBOBOX_ID, x, y, w, h, CBS_SIMPLE, 0);

            // set attributes
            
            child->TCmybox->Attr.Style |= CBS_DISABLENOSCROLL;
            child->TLmybox->Attr.Style ^= CBS_SORT;
            
            // Display the control
            
            child->TCmybox->Create();
            
            MyMessageScan();
            
            strcpy(child->TCmybox->key, childname);
            dialogboxes.insert(child, child->TCmybox->key, parent->TWmybox->key, TComboBox_type);
            }
         
         // if modal window enter here (same as above except names change)

         else if ((parent = dialogboxes.get2(parentname, TDialog_type)) != NULL)
            {
            
            // convert to "DIALOG" units
            
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;
            
            child = new dialogthing;
            
            child->TCmybox = new TMxComboBox(parent->TDmybox, MYCOMBOBOX_ID, x, y, w, h, CBS_SIMPLE, 0);
            
            child->TCmybox->Attr.Style |= CBS_DISABLENOSCROLL;
            child->TCmybox->Attr.Style ^= CBS_SORT;
            
            child->TCmybox->Create();
            
            MyMessageScan();
            
            strcpy(child->TCmybox->key, childname);
            dialogboxes.insert(child, child->TCmybox->key, parent->TDmybox->key, TComboBox_type);
            }
         else
            {
            child = new dialogthing;
            
            child->TCmybox = new TMxComboBox(
               MainWindowx->ScreenWindow,
               MYCOMBOBOX_ID,
               +x - MainWindowx->ScreenWindow->Scroller->XPos+xoffset,
               -y - MainWindowx->ScreenWindow->Scroller->YPos+yoffset,
               w,
               h,
               CBS_SIMPLE,
               0);

            child->TCmybox->Attr.Style |= CBS_DISABLENOSCROLL;
            child->TCmybox->Attr.Style ^= CBS_SORT;

            child->TCmybox->Create();

            MyMessageScan();

            strcpy(child->TCmybox->key, childname);
            dialogboxes.insert(
               child,
               child->TCmybox->key,
               (char *)MainWindowx->ScreenWindow,
               TComboBox_type);

            UpdateZoomControlFlag();

            // MainWindowx->CommandWindow->MessageBox(parentname, "Does not exist");
            // err_logo(STOP_ERROR, NIL);
            }
         }
      else
         {
         MainWindowx->CommandWindow->MessageBox(childname, "Already exists");
         err_logo(STOP_ERROR, NIL);
         }
      }

   return Unbound;
   }

NODE *lcomboboxenable(NODE *args)
   {
   return WindowEnableHelper(args, TComboBox_type);
   }

NODE *lcomboboxdelete(NODE *args)
   {
   return WindowDeleteHelper(args, TComboBox_type);
   }

NODE *lcomboboxgettext(NODE *args)
   {
   // get args
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   // if exists continue
   dialogthing *parent;
   if ((parent = dialogboxes.get2(parentname, TComboBox_type)) != NULL)
      {
      // if successful getting string return it
      char stringname[MAX_BUFFER_SIZE];
      if (((TComboBox *) parent->TCmybox)->GetText(stringname, MAX_BUFFER_SIZE) >= 0)
         {
         // parsing it turns it into a list
         NODE * val = parser(
            make_strnode(stringname, strlen(stringname), STRING, strnzcpy),
            FALSE);
         return val;
         }
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox(parentname, "Does not exist");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *lcomboboxsettext(NODE *args)
   {
   dialogthing *parent;
   char parentname[MAX_BUFFER_SIZE];
   char stringname[MAX_BUFFER_SIZE];

   // get args

   cnv_strnode_string(parentname, args);
   cnv_strnode_string(stringname, cdr(args));

   // if exists continue

   if ((parent = dialogboxes.get2(parentname, TComboBox_type)) != NULL)
      {

      // set the editcontrol portion to the user specified text

      ((TComboBox *) parent->TCmybox)->SetText(stringname);
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox(parentname, "Does not exist");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *lcomboboxaddstring(NODE *args)
   {
   dialogthing *parent;
   char parentname[MAX_BUFFER_SIZE];
   char stringname[MAX_BUFFER_SIZE];

   // get args

   cnv_strnode_string(parentname, args);
   cnv_strnode_string(stringname, cdr(args));

   // if exists continue

   if ((parent = dialogboxes.get2(parentname, TComboBox_type)) != NULL)
      {

      // add string and reset selection

      ((TComboBox *) parent->TCmybox)->AddString(stringname);
      ((TComboBox *) parent->TCmybox)->SetSelIndex(0);
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox(parentname, "Does not exist");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *lcomboboxdeletestring(NODE *args)
   {
   dialogthing *parent;
   int index;
   char parentname[MAX_BUFFER_SIZE];

   // get args

   cnv_strnode_string(parentname, args);
   index = getint(pos_int_arg(cdr(args)));

   // if exists continue

   if ((parent = dialogboxes.get2(parentname, TComboBox_type)) != NULL)
      {

      // kill entrt and reset Index

      ((TComboBox *) parent->TCmybox)->DeleteString(index);
      ((TComboBox *) parent->TCmybox)->SetSelIndex(0);
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox(parentname, "Does not exist");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *lscrollbarcreate(NODE *args)
   {
   dialogthing *child;
   dialogthing *parent;

   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args = cdr(args));

   int x = int_arg(args = cdr(args));
   int y = int_arg(args = cdr(args));
   int w = int_arg(args = cdr(args));
   int h = int_arg(args = cdr(args));

   char callback[MAX_BUFFER_SIZE];
   cnv_strnode_string(callback, cdr(args));

   if (NOT_THROWING)
      {
      if (dialogboxes.get(childname) == NULL)
         {
         
         if ((parent = dialogboxes.get2(parentname, TWindow_type)) != NULL)
            {
            
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;

            child = new dialogthing;
            
            if (w > h)
               {
               child->TSCmybox = new TMyScrollBar(parent->TWmybox, MYSCROLLBAR_ID, x, y, w, 0, TRUE);
               }
            else
               {
               child->TSCmybox = new TMyScrollBar(parent->TWmybox, MYSCROLLBAR_ID, x, y, 0, h, FALSE);
               }
            
            strcpy(child->TSCmybox->callback, callback);
            child->TSCmybox->critical = 0;
            
            child->TSCmybox->Create();
            
            MyMessageScan();
            
            strcpy(child->TSCmybox->key, childname);
            dialogboxes.insert(child, child->TSCmybox->key, parent->TWmybox->key, TScrollBar_type);
            }
         else if ((parent = dialogboxes.get2(parentname, TDialog_type)) != NULL)
            {
            
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;
            
            child = new dialogthing;
            
            if (w > h)
               {
               child->TSCmybox = new TMyScrollBar(parent->TDmybox, MYSCROLLBAR_ID, x, y, w, 0, TRUE);
               }
            else
               {
               child->TSCmybox = new TMyScrollBar(parent->TDmybox, MYSCROLLBAR_ID, x, y, 0, h, FALSE);
               }
            
            strcpy(child->TSCmybox->callback, callback);
            child->TSCmybox->critical = 0;
            
            child->TSCmybox->Create();
            
            MyMessageScan();
            
            strcpy(child->TSCmybox->key, childname);
            dialogboxes.insert(child, child->TSCmybox->key, parent->TDmybox->key, TScrollBar_type);
            }
         else
            {
            child = new dialogthing;
            
            if (w > h)
               {
               child->TSCmybox = new TMyScrollBar(
                  MainWindowx->ScreenWindow,
                  MYSCROLLBAR_ID,
                  +x - MainWindowx->ScreenWindow->Scroller->XPos+xoffset,
                  -y - MainWindowx->ScreenWindow->Scroller->YPos+yoffset,
                  w,
                  0,
                  TRUE);
               }
            else
               {
               child->TSCmybox = new TMyScrollBar(
                  MainWindowx->ScreenWindow,
                  MYSCROLLBAR_ID,
                  +x - MainWindowx->ScreenWindow->Scroller->XPos+xoffset,
                  -y - MainWindowx->ScreenWindow->Scroller->YPos+yoffset,
                  0,
                  h,
                  FALSE);
               }
            
            strcpy(child->TSCmybox->callback, callback);
            child->TSCmybox->critical = 0;
            
            child->TSCmybox->Create();
            
            MyMessageScan();
            
            strcpy(child->TSCmybox->key, childname);
            dialogboxes.insert(
               child,
               child->TSCmybox->key,
               (char *)MainWindowx->ScreenWindow,
               TScrollBar_type);

            UpdateZoomControlFlag();

            // MainWindowx->CommandWindow->MessageBox(parentname, "Does not exist");
            // err_logo(STOP_ERROR, NIL);
            }
         }
      else
         {
         MainWindowx->CommandWindow->MessageBox(childname, "Already exists");
         err_logo(STOP_ERROR, NIL);
         }
      }

   return Unbound;
   }

NODE *lscrollbarset(NODE *args)
   {
   dialogthing *parent;
   char parentname[MAX_BUFFER_SIZE];
   int lo;
   int hi;
   int pos;

   cnv_strnode_string(parentname, args);
   lo = getint(pos_int_arg(args = cdr(args)));
   hi = getint(pos_int_arg(args = cdr(args)));
   pos = getint(pos_int_arg(cdr(args)));

   if ((parent = dialogboxes.get2(parentname, TScrollBar_type)) != NULL)
      {
      ((TScrollBar *) parent->TSCmybox)->SetRange(lo, hi);
      ((TScrollBar *) parent->TSCmybox)->SetPosition(pos);
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox(parentname, "Does not exist");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *lscrollbarget(NODE *args)
   {
   dialogthing *parent;
   char parentname[MAX_BUFFER_SIZE];
   int pos;

   cnv_strnode_string(parentname, args);

   if ((parent = dialogboxes.get2(parentname, TScrollBar_type)) != NULL)
      {
      pos = ((TScrollBar *) parent->TSCmybox)->GetPosition();
      return (make_intnode(pos));
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox(parentname, "Does not exist");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *lscrollbarenable(NODE *args)
   {
   return WindowEnableHelper(args, TScrollBar_type);
   }

NODE *lscrollbardelete(NODE *args)
   {
   return WindowDeleteHelper(args, TScrollBar_type);
   }

NODE *lstaticcreate(NODE *args)
   {
   dialogthing *child;
   dialogthing *parent;

   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args = cdr(args));

   char titlename[MAX_BUFFER_SIZE];
   cnv_strnode_string(titlename, args = cdr(args));

   int x = int_arg(args = cdr(args));
   int y = int_arg(args = cdr(args));
   int w = int_arg(args = cdr(args));
   int h = int_arg(cdr(args));

   if (NOT_THROWING)
      {
      if (dialogboxes.get(childname) == NULL)
         {
         if ((parent = dialogboxes.get2(parentname, TWindow_type)) != NULL)
            {
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;
            
            child = new dialogthing;

            child->TSmybox = new TMyStatic(parent->TWmybox, MYSTATIC_ID, titlename, x, y, w, h, 0);
            
            child->TSmybox->Create();
            
            MyMessageScan();
            
            strcpy(child->TSmybox->key, childname);
            dialogboxes.insert(child, child->TSmybox->key, parent->TWmybox->key, TStatic_type);
            }
         else if ((parent = dialogboxes.get2(parentname, TDialog_type)) != NULL)
            {
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;
            
            child = new dialogthing;

            child->TSmybox = new TMyStatic(parent->TDmybox, MYSTATIC_ID, titlename, x, y, w, h, 0);
            
            child->TSmybox->Create();

            MyMessageScan();
            
            strcpy(child->TSmybox->key, childname);
            dialogboxes.insert(child, child->TSmybox->key, parent->TDmybox->key, TStatic_type);
            }
         else
            {
            child = new dialogthing;
            
            child->TSmybox = new TMyStatic(
               MainWindowx->ScreenWindow,
               MYSTATIC_ID,
               titlename,
               +x - MainWindowx->ScreenWindow->Scroller->XPos+xoffset,
               -y - MainWindowx->ScreenWindow->Scroller->YPos+yoffset,
               w,
               h,
               0);
            
            child->TSmybox->Create();
            
            MyMessageScan();
            
            strcpy(child->TSmybox->key, childname);
            dialogboxes.insert(
               child,
               child->TSmybox->key,
               (char *)MainWindowx->ScreenWindow,
               TStatic_type);

            UpdateZoomControlFlag();
            
            // MainWindowx->CommandWindow->MessageBox(parentname, "Does not exist");
            // err_logo(STOP_ERROR, NIL);
            }
         }
      else
         {
         MainWindowx->CommandWindow->MessageBox(childname, "Already exists");
         err_logo(STOP_ERROR, NIL);
         }
      }
   
   return Unbound;
   }

NODE *lstaticupdate(NODE *args)
   {
   dialogthing *temp;
   char childname[MAX_BUFFER_SIZE];
   char titlename[MAX_BUFFER_SIZE];

   cnv_strnode_string(childname, args);
   cnv_strnode_string(titlename, cdr(args));

   if ((temp = dialogboxes.get2(childname, TStatic_type)) != NULL)
      {
      temp->TSmybox->SetText(titlename);
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox(childname, "Does not exist");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *lstaticdelete(NODE *args)
   {
   return WindowDeleteHelper(args, TStatic_type);
   }

NODE *lbuttoncreate(NODE *args)
   {
   dialogthing *child;
   dialogthing *parent;

   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args = cdr(args));

   char titlename[MAX_BUFFER_SIZE];
   cnv_strnode_string(titlename, args = cdr(args));

   int x = int_arg(args = cdr(args));
   int y = int_arg(args = cdr(args));
   int w = int_arg(args = cdr(args));
   int h = int_arg(args = cdr(args));

   char callback[MAX_BUFFER_SIZE];
   if (cdr(args) != NIL)
      {
      cnv_strnode_string(callback, cdr(args));
      }
   else
      {
      callback[0] = '\0';
      }

   if (NOT_THROWING)
      {
      if (dialogboxes.get(childname) == NULL)
         {

         if ((parent = dialogboxes.get2(parentname, TWindow_type)) != NULL)
            {
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;

            child = new dialogthing;

            child->TBmybox = new TMyButton(
               parent->TWmybox,
               MYBUTTON_ID,
               titlename,
               x,
               y,
               w,
               h,
               0);

            strcpy(child->TBmybox->callback, callback);
            child->TBmybox->critical = 0;

            child->TBmybox->Create();

            MyMessageScan();

            strcpy(child->TBmybox->key, childname);
            dialogboxes.insert(
               child,
               child->TBmybox->key,
               parent->TWmybox->key,
               TButton_type);
            }
         else if ((parent = dialogboxes.get2(parentname, TDialog_type)) != NULL)
            {
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;

            child = new dialogthing;

            child->TBmybox = new TMyButton(
               parent->TDmybox,
               MYBUTTON_ID,
               titlename,
               x,
               y,
               w,
               h,
               0);

            strcpy(child->TBmybox->callback, callback);
            child->TBmybox->critical = 0;

            child->TBmybox->Create();

            MyMessageScan();

            strcpy(child->TBmybox->key, childname);
            dialogboxes.insert(
               child,
               child->TBmybox->key,
               parent->TDmybox->key,
               TButton_type);
            }
         else
            {
            child = new dialogthing;

            child->TBmybox = new TMyButton(
               MainWindowx->ScreenWindow,
               MYBUTTON_ID,
               titlename,
               +x - MainWindowx->ScreenWindow->Scroller->XPos+xoffset,
               -y - MainWindowx->ScreenWindow->Scroller->YPos+yoffset,
               w,
               h,
               0);

            strcpy(child->TBmybox->callback, callback);
            child->TBmybox->critical = 0;

            child->TBmybox->Create();

            MyMessageScan();

            strcpy(child->TBmybox->key, childname);
            dialogboxes.insert(
               child,
               child->TBmybox->key,
               (char *)MainWindowx->ScreenWindow,
               TButton_type);

            UpdateZoomControlFlag();

            // MainWindowx->CommandWindow->MessageBox(parentname, "Does not exist");
            // err_logo(STOP_ERROR, NIL);
            }
         }
      else
         {
         MainWindowx->CommandWindow->MessageBox(childname, "Already exists");
         err_logo(STOP_ERROR, NIL);
         }
      }
      
   return Unbound;
   }

NODE *lbuttonupdate(NODE *args)
   {
   dialogthing *temp;
   char childname[MAX_BUFFER_SIZE];
   char titlename[MAX_BUFFER_SIZE];

   cnv_strnode_string(childname, args);
   cnv_strnode_string(titlename, cdr(args));

   if ((temp = dialogboxes.get2(childname, TButton_type)) != NULL)
      {
      temp->TBmybox->SetWindowText(titlename);
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox(childname, "Does not exist");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *lbuttonenable(NODE *args)
   {
   return WindowEnableHelper(args, TButton_type);
   }

NODE *lbuttondelete(NODE *args)
   {
   return WindowDeleteHelper(args, TButton_type);
   }

NODE *lgroupboxcreate(NODE *args)
   {
   dialogthing *child;
   dialogthing *parent;

   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args = cdr(args));

   int x = int_arg(args = cdr(args));
   int y = int_arg(args = cdr(args));
   int w = int_arg(args = cdr(args));
   int h = int_arg(cdr(args));

   if (NOT_THROWING)
      {
      if (dialogboxes.get(childname) == NULL)
         {
         if ((parent = dialogboxes.get2(parentname, TWindow_type)) != NULL)
            {
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;

            child = new dialogthing;

            child->TGmybox = new TMyGroupBox(parent->TWmybox, MYGROUPBOX_ID, NULL, x, y, w, h);

            child->TGmybox->Create();

            MyMessageScan();

            strcpy(child->TGmybox->key, childname);
            dialogboxes.insert(child, child->TGmybox->key, parent->TWmybox->key, TGroupBox_type);
            }
         else if ((parent = dialogboxes.get2(parentname, TDialog_type)) != NULL)
            {
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;

            child = new dialogthing;

            child->TGmybox = new TMyGroupBox(parent->TDmybox, MYGROUPBOX_ID, NULL, x, y, w, h);
            
            child->TGmybox->Create();
            
            MyMessageScan();
            
            strcpy(child->TGmybox->key, childname);
            dialogboxes.insert(child, child->TGmybox->key, parent->TDmybox->key, TGroupBox_type);
            }
         else
            {
            child = new dialogthing;
            
            child->TGmybox = new TMyGroupBox(
               MainWindowx->ScreenWindow,
               MYGROUPBOX_ID,
               NULL,
               +x - MainWindowx->ScreenWindow->Scroller->XPos+xoffset,
               -y - MainWindowx->ScreenWindow->Scroller->YPos+yoffset,
               w,
               h);
            
            child->TGmybox->Create();
            
            MyMessageScan();
            
            strcpy(child->TGmybox->key, childname);
            dialogboxes.insert(
               child,
               child->TGmybox->key,
               (char *)MainWindowx->ScreenWindow,
               TGroupBox_type);

            UpdateZoomControlFlag();
            // MainWindowx->CommandWindow->MessageBox(parentname, "Does not exist");
            // err_logo(STOP_ERROR, NIL);
            }
         }
      else
         {
         MainWindowx->CommandWindow->MessageBox(childname, "Already exists");
         err_logo(STOP_ERROR, NIL);
         }
      }

   return Unbound;
   }

NODE *lgroupboxdelete(NODE *args)
   {
   return WindowEnableHelper(args, TGroupBox_type);
   }

NODE *lradiobuttoncreate(NODE *args)
   {
   dialogthing *child;
   dialogthing *parent;
   dialogthing *group;

   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   char groupname[MAX_BUFFER_SIZE];
   cnv_strnode_string(groupname, args = cdr(args));

   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args = cdr(args));

   char titlename[MAX_BUFFER_SIZE];
   cnv_strnode_string(titlename, args = cdr(args));
   int x = int_arg(args = cdr(args));
   int y = int_arg(args = cdr(args));
   int w = int_arg(args = cdr(args));
   int h = int_arg(args = cdr(args));

   if (NOT_THROWING)
      {
      if (dialogboxes.get(childname) == NULL)
         {
         if ((parent = dialogboxes.get2(parentname, TWindow_type)) != NULL)
            {
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;
            
            if ((group = dialogboxes.get2(groupname, TGroupBox_type)) != NULL)
               {
               child = new dialogthing;
               
               child->TRmybox = new TMyRadioButton(parent->TWmybox, MYRADIOBUTTON_ID, titlename, x, y, w, h, group->TGmybox);
               
               //         strcpy(child->TRmybox->callback,callback);
               //         child->TRmybox->critical = 0;
               
               child->TRmybox->Create();
               
               MyMessageScan();
               
               strcpy(child->TRmybox->key, childname);
               dialogboxes.insert(child, child->TRmybox->key, parent->TWmybox->key, TRadioButton_type);
               }
            else
               {
               MainWindowx->CommandWindow->MessageBox(groupname, "Does not exist");
               err_logo(STOP_ERROR, NIL);
               }
            }
         else if ((parent = dialogboxes.get2(parentname, TDialog_type)) != NULL)
            {
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;
            
            if ((group = dialogboxes.get2(groupname, TGroupBox_type)) != NULL)
               {
               child = new dialogthing;
               
               child->TRmybox = new TMyRadioButton(parent->TDmybox, MYRADIOBUTTON_ID, titlename, x, y, w, h, group->TGmybox);
               
               //         strcpy(child->TRmybox->callback,callback);
               //         child->TRmybox->critical = 0;
               
               child->TRmybox->Create();
               
               MyMessageScan();
               
               strcpy(child->TRmybox->key, childname);
               dialogboxes.insert(child, child->TRmybox->key, parent->TDmybox->key, TRadioButton_type);
               }
            else
               {
               MainWindowx->CommandWindow->MessageBox(groupname, "Does not exist");
               err_logo(STOP_ERROR, NIL);
               }
            }
         else
            {
            if ((group = dialogboxes.get2(groupname, TGroupBox_type)) != NULL)
               {
               child = new dialogthing;
               
               child->TRmybox = new TMyRadioButton(
                  MainWindowx->ScreenWindow,
                  MYRADIOBUTTON_ID,
                  titlename,
                  +x - MainWindowx->ScreenWindow->Scroller->XPos+xoffset,
                  -y - MainWindowx->ScreenWindow->Scroller->YPos+yoffset,
                  w,
                  h,
                  group->TGmybox);

               //         strcpy(child->TRmybox->callback,callback);
               //         child->TRmybox->critical = 0;

               child->TRmybox->Create();

               MyMessageScan();

               strcpy(child->TRmybox->key, childname);
               dialogboxes.insert(
                  child,
                  child->TRmybox->key,
                  (char *)MainWindowx->ScreenWindow,
                  TRadioButton_type);

               UpdateZoomControlFlag();
               }
            else
               {
               MainWindowx->CommandWindow->MessageBox(groupname, "Does not exist");
               err_logo(STOP_ERROR, NIL);
               }
            }
         }
      else
         {
         MainWindowx->CommandWindow->MessageBox(childname, "Already exists");
         err_logo(STOP_ERROR, NIL);
         }
      }
   
   return Unbound;
   }

NODE *lradiobuttonenable(NODE *args)
   {
   return WindowEnableHelper(args, TRadioButton_type);
   }

NODE *lradiobuttondelete(NODE *args)
   {
   return WindowDeleteHelper(args, TRadioButton_type);
   }

NODE *lradiobuttonget(NODE *args)
   {
   dialogthing *parent;
   char parentname[MAX_BUFFER_SIZE];

   cnv_strnode_string(parentname, args);

   if ((parent = dialogboxes.get2(parentname, TRadioButton_type)) != NULL)
      {
      if (BF_CHECKED == parent->TRmybox->GetCheck())
         return (Truex);
      else
         return (Falsex);
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox(parentname, "Does not exist");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *lradiobuttonset(NODE *args)
   {
   dialogthing *parent;

   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   bool pos = boolean_arg(args = cdr(args));

   if ((parent = dialogboxes.get2(parentname, TRadioButton_type)) != NULL)
      {
      if (pos)
         ((TCheckBox *) parent->TRmybox)->Check();
      else
         ((TCheckBox *) parent->TRmybox)->Uncheck();
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox(parentname, "Does not exist");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *lcheckboxcreate(NODE *args)
   {
   dialogthing *child;
   dialogthing *parent;
   dialogthing *group;

   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   char groupname[MAX_BUFFER_SIZE];
   cnv_strnode_string(groupname, args = cdr(args));

   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args = cdr(args));

   char titlename[MAX_BUFFER_SIZE];
   cnv_strnode_string(titlename, args = cdr(args));

   int x = int_arg(args = cdr(args));
   int y = int_arg(args = cdr(args));
   int w = int_arg(args = cdr(args));
   int h = int_arg(args = cdr(args));

   if (NOT_THROWING)
      {
      if (dialogboxes.get(childname) == NULL)
         {
         if ((parent = dialogboxes.get2(parentname, TWindow_type)) != NULL)
            {
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;
            
            if ((group = dialogboxes.get2(groupname, TGroupBox_type)) != NULL)
               {
               child = new dialogthing;
               
               child->TCBmybox = new TMyCheckBox(parent->TWmybox, MYCHECKBOX_ID, titlename, x, y, w, h, group->TGmybox);
               
               //         strcpy(child->TCBmybox->callback,callback);
               //         child->TCBmybox->critical = 0;
               
               child->TCBmybox->Create();
               
               MyMessageScan();
               
               strcpy(child->TCBmybox->key, childname);
               dialogboxes.insert(child, child->TCBmybox->key, parent->TWmybox->key, TCheckBox_type);
               }
            else
               {
               MainWindowx->CommandWindow->MessageBox(groupname, "Does not exist");
               err_logo(STOP_ERROR, NIL);
               }
            }
         else if ((parent = dialogboxes.get2(parentname, TDialog_type)) != NULL)
            {
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;
            
            if ((group = dialogboxes.get2(groupname, TGroupBox_type)) != NULL)
               {
               child = new dialogthing;
               
               child->TCBmybox = new TMyCheckBox(parent->TDmybox, MYCHECKBOX_ID, titlename, x, y, w, h, group->TGmybox);
               
               //         strcpy(child->TCBmybox->callback,callback);
               //         child->TCBmybox->critical = 0;
               
               child->TCBmybox->Create();
               
               MyMessageScan();
               
               strcpy(child->TCBmybox->key, childname);
               dialogboxes.insert(child, child->TCBmybox->key, parent->TDmybox->key, TCheckBox_type);
               }
            else
               {
               MainWindowx->CommandWindow->MessageBox(groupname, "Does not exist");
               err_logo(STOP_ERROR, NIL);
               }
            }
         else
            {
            if ((group = dialogboxes.get2(groupname, TGroupBox_type)) != NULL)
               {
               child = new dialogthing;

               child->TCBmybox = new TMyCheckBox(
                  MainWindowx->ScreenWindow,
                  MYCHECKBOX_ID,
                  titlename,
                  +x - MainWindowx->ScreenWindow->Scroller->XPos+xoffset,
                  -y - MainWindowx->ScreenWindow->Scroller->YPos+yoffset,
                  w,
                  h,
                  group->TGmybox);
               
               //         strcpy(child->TCBmybox->callback,callback);
               //         child->TCBmybox->critical = 0;
               
               child->TCBmybox->Create();
               
               MyMessageScan();
               
               strcpy(child->TCBmybox->key, childname);
               dialogboxes.insert(
                  child,
                  child->TCBmybox->key,
                  (char *)MainWindowx->ScreenWindow,
                  TCheckBox_type);

               UpdateZoomControlFlag();
               }
            else
               {
               MainWindowx->CommandWindow->MessageBox(groupname, "Does not exist");
               err_logo(STOP_ERROR, NIL);
               }
            }
         }
      else
         {
         MainWindowx->CommandWindow->MessageBox(childname, "Already exists");
         err_logo(STOP_ERROR, NIL);
         }
      }
   
   return Unbound;
   }

NODE *lcheckboxenable(NODE *args)
   {
   return WindowEnableHelper(args, TCheckBox_type);
   }

NODE *lcheckboxdelete(NODE *args)
   {
   return WindowDeleteHelper(args, TCheckBox_type);
   }

NODE *lcheckboxget(NODE *args)
   {
   dialogthing *parent;
   char parentname[MAX_BUFFER_SIZE];

   cnv_strnode_string(parentname, args);

   if ((parent = dialogboxes.get2(parentname, TCheckBox_type)) != NULL)
      {
      if (BF_CHECKED == parent->TCBmybox->GetCheck())
         return Truex;
      else
         return Falsex;
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox(parentname, "Does not exist");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *lcheckboxset(NODE *args)
   {
   dialogthing *parent;
   char parentname[MAX_BUFFER_SIZE];
   int pos;

   cnv_strnode_string(parentname, args);
//   pos = getint(pos_int_arg(args = cdr(args)));
   pos = boolean_arg(args = cdr(args));

   if ((parent = dialogboxes.get2(parentname, TCheckBox_type)) != NULL)
      {
      if (pos)
         parent->TCBmybox->Check();
      else
         parent->TCBmybox->Uncheck();
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox(parentname, "Does not exist");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

BOOL CheckOnScreenControls()
   {
   return dialogboxes.OnScreenControlsExist();
   }

NODE *ldebugwindows(NODE *arg)
   {
   char childname[MAX_BUFFER_SIZE];

   if (arg != NIL)
      {
      cnv_strnode_string(childname, arg);
      
      if (dialogboxes.get(childname) != NULL)
         {
         dialogboxes.list(childname, 0);
         }
      else
         {
         MainWindowx->CommandWindow->MessageBox(childname, "Does not exist");
         err_logo(STOP_ERROR, NIL);
         }
      }
   else
      {
      dialogboxes.listall();
      }

   return Unbound;
   }

NODE *lmessagebox(NODE *args)
   {
   char banner[MAX_BUFFER_SIZE];
   cnv_strnode_string(banner, args);

   char body[MAX_BUFFER_SIZE];
   cnv_strnode_string(body, args = cdr(args));

   if (MainWindowx->CommandWindow->MessageBox(body, banner, MB_OKCANCEL) == IDCANCEL)
      {
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *lquestionbox(NODE *args)
   {
   char banner[MAX_BUFFER_SIZE];
   cnv_strnode_string(banner, args);

   char body[MAX_BUFFER_SIZE];
   cnv_strnode_string(body, args = cdr(args));

   char str[MAX_BUFFER_SIZE];
   memset(str, 0, MAX_BUFFER_SIZE);

   TInputDialog dlg(
      MainWindowx->ScreenWindow,
      banner,
      body,
      str,
      MAX_BUFFER_SIZE);

   if (dlg.Execute() == IDCANCEL)
      {
      memset(str, 0, MAX_BUFFER_SIZE);
      err_logo(STOP_ERROR, NIL);
      }

   NODE * targ = make_strnode(str, strlen(str), STRING, strnzcpy);
   NODE * val = parser(targ, FALSE);
   return val;
   }

NODE *lselectbox(NODE *args)
   {
   int iStatus;

   char banner[MAX_BUFFER_SIZE];
   char textbuf[MAX_BUFFER_SIZE];

   cnv_strnode_string(banner, args);

   TPickListDialog dlg(
      MainWindowx->ScreenWindow,
      0,
      0,
      0,
      banner);

   args = car(cdr(args));

   /* must be a list that contains something */

   if (is_list(args) && (args != NIL))
      {
      while (args != NIL)
         {
         cnv_strnode_string(textbuf, args);
         dlg.AddString(textbuf);

         args = cdr(args);
         }
      }

   iStatus = dlg.Execute();

   if (iStatus >= 0)
      {
      return (make_intnode(iStatus + 1));
      }
   else
      {
      err_logo(STOP_ERROR, NIL);
      return (make_intnode(0));
      }
   }

NODE *lyesnobox(NODE *args)
   {
   char banner[MAX_BUFFER_SIZE];
   char body[MAX_BUFFER_SIZE];
   int iStatus;

   cnv_strnode_string(banner, args);
   cnv_strnode_string(body, args = cdr(args));

   iStatus = MainWindowx->CommandWindow->MessageBox(
      body,
      banner,
      MB_YESNOCANCEL | MB_ICONQUESTION);

   switch (iStatus)
      {
      case IDYES:
         {
         return Truex;
         }
      case IDNO:
         {
         return Falsex;
         }
      case IDCANCEL:
         {
         err_logo(STOP_ERROR, NIL);
         return Falsex;
         }
      }

   return Unbound;
   }

NODE *lsetcursorwait(NODE *)
   {
   hCursorSave =::SetCursor(hCursorWait);

   return Unbound;
   }

NODE *lsetcursorarrow(NODE *)
   {

   if (hCursorSave)
      {
      ::SetCursor(hCursorSave);
      hCursorSave = 0;
      }
   else
      {
      ::SetCursor(hCursorArrow);
      }

   return Unbound;
   }

NODE *ldialogfileopen(NODE *args)
   {
   char filename[MAX_BUFFER_SIZE];
   cnv_strnode_string(filename, args);

   TOpenSaveDialog::TData FileData;
   FileData.Flags = OFN_HIDEREADONLY | OFN_EXPLORER;
   FileData.SetFilter("All Files (*.*)|*.*|");
   strcpy(FileData.FileName, filename);

   /* if user found a file then try to load it  */

   if (TFileOpenDialog(MainWindowx, FileData).Execute() == IDOK)
      {
      strcpy(filename, FileData.FileName);
      NODE * arg = make_strnode(filename, strlen(filename), STRING, strnzcpy);
      NODE * val = arg; // parser(arg, FALSE);
      return val;
      }
   else
      {
      return NIL;
      }
   }

NODE *ldialogfilesave(NODE *args)
   {
   char filename[MAX_BUFFER_SIZE];
   cnv_strnode_string(filename, args);


   /* Get file name from user and then save the file */
   TOpenSaveDialog::TData FileData;
   FileData.SetFilter("All Files (*.*)|*.*|");
   strcpy(FileData.FileName, filename);

   if (TFileSaveDialog(MainWindowx, FileData).Execute() == IDOK)
      {
      strcpy(filename, FileData.FileName);
      NODE * arg = make_strnode(filename, strlen(filename), STRING, strnzcpy);
      NODE * val = arg; // parser(arg, FALSE);
      return val;
      }
   else
      {
      return NIL;
      }
   }

NODE *lwindowfileedit(NODE *args)
   {
   char filename[MAX_BUFFER_SIZE];
   char editexit[MAX_BUFFER_SIZE];

   cnv_strnode_string(filename, args);
   cnv_strnode_string(editexit, args = cdr(args));

   strcpy(edit_editexit, editexit);

   TMainFrame::PopupEditorForFile(filename, NULL);
   return Unbound;
   }

DEFINE_RESPONSE_TABLE1(TMyButton, TButton)
  EV_WM_LBUTTONUP,
END_RESPONSE_TABLE;

DEFINE_RESPONSE_TABLE1(TMxWindow, TDialog)
  EV_COMMAND(IDCANCEL, CmCancel),
  EV_COMMAND(IDOK, CmOk),
END_RESPONSE_TABLE;

DEFINE_RESPONSE_TABLE1(TMxDialog, TDialog)
  EV_COMMAND(IDCANCEL, CmCancel),
  EV_COMMAND(IDOK, CmOk),
END_RESPONSE_TABLE;

