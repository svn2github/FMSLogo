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


// class structures for the controls we support, for the most part they
// are the same as the original with just a key and callback string added

class TMxWindow : public TDialog
   {
   public:
   char caption[MAX_BUFFER_SIZE];
   char callback[MAX_BUFFER_SIZE];
   int x;
   int y;
   int h;
   int w;

   TMxWindow(TWindow *AParent, const char * AText) : TDialog(AParent, AText)
      {
      }

   protected:
   void SetupWindow();
   void CmCancel()
      {
      }

   void CmOk()
      {
      }

   DECLARE_RESPONSE_TABLE(TMxWindow);
   };

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
   char callback[MAX_BUFFER_SIZE];
   char caption[MAX_BUFFER_SIZE];
   int x;
   int y;
   int h;
   int w;

   TMxDialog(TWindow *AParent, const char * AText) 
      : TDialog(AParent, AText)
      {
      }

   protected:
   void SetupWindow();
   void CmCancel()
      {
      }

   void CmOk()
      {
      }

   DECLARE_RESPONSE_TABLE(TMxDialog);
   };


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

   TMyListBox(TWindow *Parent, int X, int Y, int W, int H) :
      TListBox(Parent, MYLISTBOX_ID, X, Y, W, H)
      {
      // disable automatic sorting
      Attr.Style ^= LBS_SORT;
      }
   };

class TMxComboBox : public TComboBox
   {
   public:
   TMxComboBox(
      TWindow *Parent, 
      int X, 
      int Y,
      int W, 
      int H
      ) : TComboBox(Parent, MYCOMBOBOX_ID, X, Y, W, H, CBS_SIMPLE, 0)
      {
      // set attributes
      Attr.Style |= CBS_DISABLENOSCROLL;
      Attr.Style ^= CBS_SORT;
      }
   };

class TMyStatic : public TStatic
   {
   public:
   TMyStatic(
      TWindow *AParent,
      int AnId, 
      const char * AText, 
      int X, 
      int Y,
      int W, 
      int H
      ) : TStatic(AParent, AnId, AText, X, Y, W, H)
      {
      };
   };

class TMyButton : public TButton
   {
   public:
   char callback[MAX_BUFFER_SIZE];

   TMyButton(
      TWindow *AParent, 
      int AnId, 
      const char * AText, 
      int X, 
      int Y,
      int W, 
      int H
      ) : TButton(AParent, AnId, AText, X, Y, W, H)
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
   char callback[MAX_BUFFER_SIZE];

   TMyScrollBar(
      TWindow *AParent, 
      int AnId, 
      int X, 
      int Y,
      int W, 
      int H, 
      BOOL IsHScrollBar
      ) : TScrollBar(AParent, AnId, X, Y, W, H, IsHScrollBar)
      {
      };

   void SetPosition(int, bool redraw = true);
   };

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
   TMyGroupBox(
      TWindow *AParent, 
      int AnId, 
      const char * AText, 
      int X, 
      int Y,
      int W, 
      int H
      ) : TGroupBox(AParent, AnId, AText, X, Y, W, H)
      {
      };
   };

class TMyRadioButton : public TRadioButton
   {
   public:

   TMyRadioButton(
      TWindow * Parent, 
      const char * Title, 
      int X, 
      int Y,
      int W, 
      int H, 
      TGroupBox *Group
      ) : TRadioButton(Parent, MYRADIOBUTTON_ID, Title, X, Y, W, H, Group)
      {
      }
   };

class TMyCheckBox : public TCheckBox
   {
   public:
   char callback[MAX_BUFFER_SIZE];

   TMyCheckBox(
      TWindow *AParent, 
      int AnId, 
      const char * ATitle, 
      int X, 
      int Y,
      int W, 
      int H, 
      TGroupBox *AGroup
      ) : TCheckBox(AParent, AnId, ATitle, X, Y, W, H, AGroup)
      {
      };
   };


// class structure for storing information about user windows.
// The implementation is an in-place circular doubly-linked list.
struct dialogthing
   {
   friend class dialoglist;

private:
   struct dialogthing *next;
   struct dialogthing *prev;

public:
   char key[MAX_BUFFER_SIZE];
   char *parent;

   int type;

   union
      {
      class TMxWindow      * TWmybox;
      class TMyStatic      * TSmybox;
      class TMyListBox     * TLmybox;
      class TMxComboBox    * TCmybox;
      class TMyButton      * TBmybox;
      class TMyScrollBar   * TSCmybox;
      class TMyGroupBox    * TGmybox;
      class TMyRadioButton * TRmybox;
      class TMyCheckBox    * TCBmybox;
      class TMxDialog      * TDmybox;
      };

   dialogthing(int t, const char * name)
     : next(NULL),
       prev(NULL),
       parent(NULL),
       type(t),
       TWmybox(NULL)
      {
      strcpy(key, name);
      }

   TWindow * GetWindow();
   };

TWindow * dialogthing::GetWindow()
   {
   switch (type)
      {
      case TWindow_type:      return TWmybox;
      case TStatic_type:      return TSmybox;
      case TListBox_type:     return TLmybox;
      case TComboBox_type:    return TCmybox;
      case TButton_type:      return TBmybox;
      case TScrollBar_type:   return TSCmybox;
      case TGroupBox_type:    return TGmybox;
      case TRadioButton_type: return TRmybox;
      case TCheckBox_type:    return TCBmybox;
      case TDialog_type:      return TDmybox;
      }

   assert(!"can't happen");
   return NULL;
   }


class dialoglist
   {
   dialogthing * last;

   public:
   void insert(dialogthing * a);
   dialogthing * get(const char *k);
   dialogthing * get2(const char *k, int t);
   char *getrootkey();
   const char *getfirstchild(const char *par);
   void zap(const char *k);
   void list(const char *k, int lev);
   void listall();
   void clear();
   bool OnScreenControlsExist();

   dialoglist()
      {
      last = NULL;
      }

   ~dialoglist()
      {
      clear();
      }

   };


// inserts an element into the list.
void dialoglist::insert(dialogthing * newnode)
   {
   if (last != NULL)
      {
      // the list was not empty.
      // insert the new node just after "last"
      newnode->next = last->next;
      newnode->prev = last;

      last->next->prev = newnode;
      last->next       = newnode;

      last = newnode;
      }
   else
      {
      // the list was empty.
      // make the newnode the "last" node.
      last = newnode;
      last->next = last;
      last->prev = last;
      }
   }

// returns the element whose key is k and whose type is t
dialogthing * dialoglist::get2(const char *k, int t)
   {
   if (last == NULL) 
      {
      return NULL;
      }

   dialogthing * f = last;

   do
      {
      if (strcmp(f->key, k) == 0)
         {
         if (f->type == t) 
            {
            return f;
            }
         else 
            {
            // the window is not of type t.
            return NULL;
            }
         }
      f = f->next;
      }
   while (f != last);

   return NULL;
   }

// returns the element whose key is k
dialogthing * dialoglist::get(const char *k)
   {
   if (last == NULL) 
      {
      return NULL;
      }

   dialogthing * f = last;

   do
      {
      if (strcmp(f->key, k) == 0)
         {
         return f;
         }
      f = f->next;
      }
   while (f != last);

   return NULL;
   }

// returns the key of the first link whose parent is "k"
// In the words, returns the first child of "k"
const char *dialoglist::getfirstchild(const char *k)
   {
   if (last == NULL) 
      {
      return NULL;
      }

   dialogthing * f = last;

   do
      {
      if (strcmp(f->parent, k) == 0)
         {
         return f->key;
         }
      f = f->next;
      }
   while (f != last);

   return NULL;
   }

// deletes the link whose key is "k" and any children of that link.
void dialoglist::zap(const char *k)
   {

   if (last == NULL) 
      {
      return;
      }

   dialogthing * f = last;
   dialogthing * p = NULL;

   // find the link whose key is "k"
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
   const char *t;
   while ((t = getfirstchild(k)) != NULL)
      {
      zap(t);
      }

   // remove the link from the list
   if (p != NULL)
      {
      f = p->next;

      if (f == p)
         {
         // this was the only element in the list
         last = NULL;
         }
      else
         {
         if (p == last) 
            {
            last = p->prev;
            }

         p->prev->next = p->next;
         f->prev = p->prev;
         }

      delete p;
      }
   }

// prints the heirarchy of all children of the node whose "k".
void dialoglist::list(const char *k, int level)
   {
   if (last == NULL) 
      {
      return;
      }

   dialogthing * f = last;
   dialogthing * p = NULL;

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
      char indent[128];

      indent[0] = '\0';
      for (int i = 0; i < level; i++) 
         {
         strcat(indent, " ");
         }

      if (level == 0)
         {
         char temp[128];
         sprintf(temp, "%s %s", Windowname[p->type], p->key);
         putcombobox(temp);
         }

      dialogthing *ff = last;
      do
         {
         if (strcmp(ff->parent, k) == 0)
            {
            char temp[128];
            sprintf(temp, "  %s%s %s", indent, Windowname[ff->type], ff->key);
            putcombobox(temp);
            list(ff->key, level + 1);
            }
         ff = ff->next;
         }
      while (ff != last);
      }
   }

// deletes all elements in the list
void dialoglist::clear()
   {
   dialogthing *l = last;

   if (l == NULL) 
      {
      return;
      }

   do
      {
      dialogthing *ll = l;
      l = l->next;
      delete ll;
      }
   while (l != last);

   }

// returns the key of the first element whose parent is the root window.
// returns NULL, if no element's parent is the root window.
char *dialoglist::getrootkey()
   {
   dialogthing *l = last;

   if (l == NULL) 
      {
      return NULL;
      }

   do
      {
      if (l->parent == (char *)MainWindowx->ScreenWindow)
         {
         return l->key;
         }
      l = l->next;
      }
   while (l != last);

   return NULL;
   }

// prints the heirarchy of all windows starting at the screen window
void dialoglist::listall()
   {
   dialogthing *l = last;

   if (l == NULL) 
      {
      return;
      }

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

bool dialoglist::OnScreenControlsExist()
   {
   dialogthing *l = last;

   if (l == NULL) 
      {
      return false;
      }

   do
      {
      if (l->parent == (char *)MainWindowx->ScreenWindow)
         {
         if ((l->type != TWindow_type) && (l->type != TDialog_type))
            {
            return true;
            }
         }
      l = l->next;
      }
   while (l != last);

   return false;
   }

dialoglist dialogboxes;

/* User function to create a modeless window */

NODE *lwindowcreate(NODE *args)
   {
   /* get all the args */
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args = cdr(args));

   char titlename[MAX_BUFFER_SIZE];
   cnv_strnode_string(titlename, args = cdr(args));

   int x =            int_arg(args = cdr(args)) ;
   int y =            int_arg(args = cdr(args)) ;
   int w = getint(pos_int_arg(args = cdr(args)));
   int h = getint(pos_int_arg(args = cdr(args)));

   char callback[MAX_BUFFER_SIZE];
   if (cdr(args) != NIL) 
      {
      cnv_strnode_string(callback, cdr(args));
      }
   else 
      {
      callback[0] = '\0';
      }


   // convert them to "DIALOG" units this is the key to making
   // all Graphics Modes work correctly.

   x = (x * BaseUnitsx) / 4;
   y = (y * BaseUnitsy) / 8;
   w = (w * BaseUnitsx) / 4;
   h = (h * BaseUnitsy) / 8;

   // if not already exist continue

   if (dialogboxes.get(childname) == NULL)
      {
      dialogthing *child = new dialogthing(TWindow_type, childname);

      // if parent exists use it else use main window
      dialogthing *parent;
      if ((parent = dialogboxes.get2(parentname, TWindow_type)) != NULL)
         {
         child->TWmybox = new TMxWindow(
            parent->TWmybox,
            "DIALOGSTUB");
         child->parent = (char *)parent->TWmybox;
         }
      else
         {
         child->TWmybox = new TMxWindow(
            MainWindowx->ScreenWindow,
            "DIALOGSTUB");
         child->parent = (char *)MainWindowx->ScreenWindow;
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

      dialogboxes.insert(child);

      child->TWmybox->Create();
      child->TWmybox->ShowWindow(SW_SHOW);

      // Make sure the window is up before we try to add controls?

      MyMessageScan();
      }
   else
      {     
      ShowMessageAndStop("Already exists", childname);
      }

   return Unbound;
   }


void windowdelete_helper()
   {
   char *tempkey;
   while (tempkey = dialogboxes.getrootkey())
      {
      dialogthing *temp = dialogboxes.get(tempkey);
      if (temp != NULL)
         {
         temp->GetWindow()->CloseWindow();
         dialogboxes.zap(tempkey);
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

   dialogthing *window = dialogboxes.get2(childname, WindowType);
   if (window != NULL)
      {
      window->GetWindow()->EnableWindow(bEnable);
      }
   else
      {
      ShowMessageAndStop("Does not exist", childname);
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
   char windowkey[MAX_BUFFER_SIZE];
   cnv_strnode_string(windowkey, args);

   // if it exists kill it
   dialogthing *window = dialogboxes.get2(windowkey, WindowType);
   if (window != NULL)
      {
      window->GetWindow()->CloseWindow();

      dialogboxes.zap(windowkey);
      UpdateZoomControlFlag();
      }
   else
      {
      ShowMessageAndStop("Does not exist", windowkey);
      }

   return Unbound;
   }


NODE *lwindowenable(NODE *args)
   {
   return WindowEnableHelper(args, TWindow_type);
   }

NODE *lwindowdelete(NODE *arg)
   {
   char windowname[MAX_BUFFER_SIZE];
   cnv_strnode_string(windowname, arg);

   if (NOT_THROWING)
      {
      dialogthing *window;
      if ((window = dialogboxes.get2(windowname, TWindow_type)) != NULL)
         {
         // The exact name and type exists matches.
         // kill this window and all of its children.
         window->TWmybox->CloseWindow();

         dialogboxes.zap(windowname);
         }
      else
         {
         // No window exists that matches this name and type.
         // Close all windows.
         windowdelete_helper();
         }
      }
   
   return Unbound;
   }

NODE *ldialogcreate(NODE *args)
   {
   // get args
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args = cdr(args));

   char titlename[MAX_BUFFER_SIZE];
   cnv_strnode_string(titlename, args = cdr(args));

   int x =            int_arg(args = cdr(args)) ;
   int y =            int_arg(args = cdr(args)) ;
   int w = getint(pos_int_arg(args = cdr(args)));
   int h = getint(pos_int_arg(args = cdr(args)));

   char callback[MAX_BUFFER_SIZE];
   if (cdr(args) != NIL)
      {
      cnv_strnode_string(callback, cdr(args));
      }
   else
      {
      callback[0] = '\0';
      }

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
      dialogthing * child = new dialogthing(TDialog_type, childname);

      // if parent of corect type exists use it
      dialogthing *parent;
      if ((parent = dialogboxes.get2(parentname, TWindow_type)) != NULL)
         {
         child->TDmybox = new TMxDialog(parent->TWmybox, "DIALOGSTUB");
         child->parent = (char *)parent->TWmybox;
         }
      else
         {
         // else use main window
         child->TDmybox = new TMxDialog(
            MainWindowx->ScreenWindow,
            "DIALOGSTUB");
         child->parent = (char *)MainWindowx->ScreenWindow;
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

      dialogboxes.insert(child);

      // Note will not return until the Window closes
      // But the LOGO program still has some control through
      // the callback which is done through OWLs "SetupWindow".
      child->TDmybox->Execute();
      }
   else
      {
      ShowMessageAndStop("Already exists", childname);
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
   // get args
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
      // if unique continue

      if (dialogboxes.get(childname) == NULL)
         {
         dialogthing * child = new dialogthing(TListBox_type, childname);

         bool updateZoomControl = false;

         dialogthing *parent;
         if ((parent = dialogboxes.get2(parentname, TWindow_type)) != NULL)
            {
            // If modeless parent then continue

            // convert to "DIALOG" units.
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;
            
            child->parent = parent->key;

            child->TLmybox = new TMyListBox(parent->TWmybox, x, y, w, h);
            }
         else if ((parent = dialogboxes.get2(parentname, TDialog_type)) != NULL)
            {
            // else if modal window continue

            // convert to "DIALOG" units.
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;

            child->parent = parent->key;

            child->TLmybox = new TMyListBox(parent->TDmybox, x, y, w, h);
            }
         else
            {
            // else the parent does not exist -- put the control on the screen
            child->parent = (char *)MainWindowx->ScreenWindow;

            child->TLmybox = new TMyListBox(
               MainWindowx->ScreenWindow,
               +x - MainWindowx->ScreenWindow->Scroller->XPos+xoffset,
               -y - MainWindowx->ScreenWindow->Scroller->YPos+yoffset,
               w,
               h);
            }

         child->TLmybox->Create();
            
         MyMessageScan();
            
         dialogboxes.insert(child);

         if (updateZoomControl)
            {
            UpdateZoomControlFlag();
            }
         }
      else
         {
         ShowMessageAndStop("Already exists", childname);
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
         NODE * val = parser(make_strnode(stringname), false);
         return val;
         }
      }
   else
      {
      ShowMessageAndStop("Does not exist", parentname);
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
      ShowMessageAndStop("Does not exist", parentname);
      }

   return Unbound;
   }

NODE *llistboxdeletestring(NODE *args)
   {
   // get args
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   int index = getint(pos_int_arg(cdr(args)));

   // if exists continue
   dialogthing *parent = dialogboxes.get2(parentname, TListBox_type);
   if (parent != NULL)
      {
      // kill entry based on index
      parent->TLmybox->DeleteString(index);
      parent->TLmybox->SetSelIndex(0);
      }
   else
      {
      ShowMessageAndStop("Does not exist", parentname);
      }

   return Unbound;
   }

NODE *lcomboboxcreate(NODE *args)
   {
   // get args
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
      // if unique continue
      if (dialogboxes.get(childname) == NULL)
         {
         dialogthing * child = new dialogthing(TComboBox_type, childname);

         bool updateZoomControl = false;
         
         dialogthing *parent = dialogboxes.get2(parentname, TWindow_type);
         if (parent != NULL)
            {
            // if modeless window enter here

            // convert to "DIALOG" units
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;

            child->parent = parent->key;

            child->TCmybox = new TMxComboBox(parent->TWmybox, x, y, w, h);
            }
         else if ((parent = dialogboxes.get2(parentname, TDialog_type)) != NULL)
            {
            // if modal window enter here (same as above except names change)
            
            // convert to "DIALOG" units
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;
            
            child->parent = parent->key;

            child->TCmybox = new TMxComboBox(parent->TDmybox, x, y, w, h);
            }
         else
            {
            // else the parent does not exist -- put the control on the screen
            child->parent = (char *) MainWindowx->ScreenWindow;

            child->TCmybox = new TMxComboBox(
               MainWindowx->ScreenWindow,
               +x - MainWindowx->ScreenWindow->Scroller->XPos+xoffset,
               -y - MainWindowx->ScreenWindow->Scroller->YPos+yoffset,
               w,
               h);

            updateZoomControl = true;
            }

         child->TCmybox->Create();

         MyMessageScan();

         dialogboxes.insert(child);

         if (updateZoomControl)
            {
            UpdateZoomControlFlag();
            }
         }
      else
         {
         ShowMessageAndStop("Already exists", childname);
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
   dialogthing *parent = dialogboxes.get2(parentname, TComboBox_type);
   if (parent != NULL)
      {
      // if successful getting string return it
      char stringname[MAX_BUFFER_SIZE];
      if (((TComboBox *) parent->TCmybox)->GetText(stringname, MAX_BUFFER_SIZE) >= 0)
         {
         // parsing it turns it into a list
         NODE * val = parser(make_strnode(stringname), false);
         return val;
         }
      }
   else
      {
      ShowMessageAndStop("Does not exist", parentname);
      }

   return Unbound;
   }

NODE *lcomboboxsettext(NODE *args)
   {
   // get args
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   char stringname[MAX_BUFFER_SIZE];
   cnv_strnode_string(stringname, cdr(args));

   // if exists continue
   dialogthing *parent = dialogboxes.get2(parentname, TComboBox_type);
   if (parent != NULL)
      {
      // set the editcontrol portion to the user specified text
      ((TComboBox *) parent->TCmybox)->SetText(stringname);
      }
   else
      {
      ShowMessageAndStop("Does not exist", parentname);
      }

   return Unbound;
   }

NODE *lcomboboxaddstring(NODE *args)
   {
   // get args
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   char stringname[MAX_BUFFER_SIZE];
   cnv_strnode_string(stringname, cdr(args));

   // if exists continue
   dialogthing *parent = dialogboxes.get2(parentname, TComboBox_type);
   if (parent != NULL)
      {
      // add string and reset selection
      ((TComboBox *) parent->TCmybox)->AddString(stringname);
      ((TComboBox *) parent->TCmybox)->SetSelIndex(0);
      }
   else
      {
      ShowMessageAndStop("Does not exist", parentname);
      }

   return Unbound;
   }

NODE *lcomboboxdeletestring(NODE *args)
   {
   // get args
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   int index = getint(pos_int_arg(cdr(args)));

   // if exists continue
   dialogthing *parent = dialogboxes.get2(parentname, TComboBox_type);
   if (parent != NULL)
      {
      // kill entry and reset index
      ((TComboBox *) parent->TCmybox)->DeleteString(index);
      ((TComboBox *) parent->TCmybox)->SetSelIndex(0);
      }
   else
      {
      ShowMessageAndStop("Does not exist", parentname);
      }

   return Unbound;
   }

NODE *lscrollbarcreate(NODE *args)
   {
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
         dialogthing * child = new dialogthing(TScrollBar_type, childname);
         
         dialogthing *parent;
         if ((parent = dialogboxes.get2(parentname, TWindow_type)) != NULL)
            {
            
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;

            child->parent = parent->key;

            if (w > h)
               {
               child->TSCmybox = new TMyScrollBar(parent->TWmybox, MYSCROLLBAR_ID, x, y, w, 0, TRUE);
               }
            else
               {
               child->TSCmybox = new TMyScrollBar(parent->TWmybox, MYSCROLLBAR_ID, x, y, 0, h, FALSE);
               }
            
            strcpy(child->TSCmybox->callback, callback);
            
            child->TSCmybox->Create();
            
            MyMessageScan();
            
            dialogboxes.insert(child);
            }
         else if ((parent = dialogboxes.get2(parentname, TDialog_type)) != NULL)
            {
            
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;
            
            child->parent = parent->key;
            
            if (w > h)
               {
               child->TSCmybox = new TMyScrollBar(parent->TDmybox, MYSCROLLBAR_ID, x, y, w, 0, TRUE);
               }
            else
               {
               child->TSCmybox = new TMyScrollBar(parent->TDmybox, MYSCROLLBAR_ID, x, y, 0, h, FALSE);
               }
            
            strcpy(child->TSCmybox->callback, callback);
            
            child->TSCmybox->Create();
            
            MyMessageScan();
            
            dialogboxes.insert(child);
            }
         else
            {
            child->parent = (char*) MainWindowx->ScreenWindow;
            
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
            
            child->TSCmybox->Create();
            
            MyMessageScan();
            
            dialogboxes.insert(child);

            UpdateZoomControlFlag();
            }
         }
      else
         {
         ShowMessageAndStop("Already exists", childname);
         }
      }

   return Unbound;
   }

NODE *lscrollbarset(NODE *args)
   {
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   int lo = getint(pos_int_arg(args = cdr(args)));
   int hi = getint(pos_int_arg(args = cdr(args)));
   int pos = getint(pos_int_arg(cdr(args)));

   dialogthing *parent;
   if ((parent = dialogboxes.get2(parentname, TScrollBar_type)) != NULL)
      {
      ((TScrollBar *) parent->TSCmybox)->SetRange(lo, hi);
      ((TScrollBar *) parent->TSCmybox)->SetPosition(pos);
      }
   else
      {
      ShowMessageAndStop("Does not exist", parentname);
      }

   return Unbound;
   }

NODE *lscrollbarget(NODE *args)
   {
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   dialogthing *parent;
   if ((parent = dialogboxes.get2(parentname, TScrollBar_type)) != NULL)
      {
      int pos = ((TScrollBar *) parent->TSCmybox)->GetPosition();
      return make_intnode(pos);
      }
   else
      {
      ShowMessageAndStop("Does not exist", parentname);
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
         dialogthing * child = new dialogthing(TStatic_type, childname);

         dialogthing *parent;
         if ((parent = dialogboxes.get2(parentname, TWindow_type)) != NULL)
            {
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;

            child->parent = parent->key;

            child->TSmybox = new TMyStatic(parent->TWmybox, MYSTATIC_ID, titlename, x, y, w, h);
            
            child->TSmybox->Create();
            
            MyMessageScan();
            
            dialogboxes.insert(child);
            }
         else if ((parent = dialogboxes.get2(parentname, TDialog_type)) != NULL)
            {
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;
            
            child->parent = parent->key;

            child->TSmybox = new TMyStatic(parent->TDmybox, MYSTATIC_ID, titlename, x, y, w, h);
            
            child->TSmybox->Create();

            MyMessageScan();
            
            dialogboxes.insert(child);
            }
         else
            {
            child->parent = (char *) MainWindowx->ScreenWindow;
            
            child->TSmybox = new TMyStatic(
               MainWindowx->ScreenWindow,
               MYSTATIC_ID,
               titlename,
               +x - MainWindowx->ScreenWindow->Scroller->XPos+xoffset,
               -y - MainWindowx->ScreenWindow->Scroller->YPos+yoffset,
               w,
               h);
            
            child->TSmybox->Create();
            
            MyMessageScan();
            
            dialogboxes.insert(child);

            UpdateZoomControlFlag();
            }
         }
      else
         {
         ShowMessageAndStop("Already exists", childname);
         }
      }
   
   return Unbound;
   }

NODE *lstaticupdate(NODE *args)
   {
   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args);

   char titlename[MAX_BUFFER_SIZE];
   cnv_strnode_string(titlename, cdr(args));

   dialogthing *temp;
   if ((temp = dialogboxes.get2(childname, TStatic_type)) != NULL)
      {
      temp->TSmybox->SetText(titlename);
      }
   else
      {
      ShowMessageAndStop("Does not exist", childname);
      }

   return Unbound;
   }

NODE *lstaticdelete(NODE *args)
   {
   return WindowDeleteHelper(args, TStatic_type);
   }

NODE *lbuttoncreate(NODE *args)
   {
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
         dialogthing * child = new dialogthing(TButton_type, childname);

         dialogthing *parent;
         if ((parent = dialogboxes.get2(parentname, TWindow_type)) != NULL)
            {
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;

            child->parent = parent->key;

            child->TBmybox = new TMyButton(
               parent->TWmybox,
               MYBUTTON_ID,
               titlename,
               x,
               y,
               w,
               h);

            strcpy(child->TBmybox->callback, callback);

            child->TBmybox->Create();

            MyMessageScan();

            dialogboxes.insert(child);
            }
         else if ((parent = dialogboxes.get2(parentname, TDialog_type)) != NULL)
            {
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;

            child->parent = parent->key;

            child->TBmybox = new TMyButton(
               parent->TDmybox,
               MYBUTTON_ID,
               titlename,
               x,
               y,
               w,
               h);

            strcpy(child->TBmybox->callback, callback);

            child->TBmybox->Create();

            MyMessageScan();

            dialogboxes.insert(child);
            }
         else
            {
            child->parent = (char *) MainWindowx->ScreenWindow;

            child->TBmybox = new TMyButton(
               MainWindowx->ScreenWindow,
               MYBUTTON_ID,
               titlename,
               +x - MainWindowx->ScreenWindow->Scroller->XPos+xoffset,
               -y - MainWindowx->ScreenWindow->Scroller->YPos+yoffset,
               w,
               h);

            strcpy(child->TBmybox->callback, callback);

            child->TBmybox->Create();

            MyMessageScan();

            dialogboxes.insert(child);

            UpdateZoomControlFlag();
            }
         }
      else
         {
         ShowMessageAndStop("Already exists", childname);
         }
      }
      
   return Unbound;
   }

NODE *lbuttonupdate(NODE *args)
   {
   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args);

   char titlename[MAX_BUFFER_SIZE];
   cnv_strnode_string(titlename, cdr(args));

   dialogthing *temp;
   if ((temp = dialogboxes.get2(childname, TButton_type)) != NULL)
      {
      temp->TBmybox->SetWindowText(titlename);
      }
   else
      {
      ShowMessageAndStop("Does not exist", childname);
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
         dialogthing * child = new dialogthing(TGroupBox_type, childname);

         dialogthing *parent;
         if ((parent = dialogboxes.get2(parentname, TWindow_type)) != NULL)
            {
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;

            child->parent = parent->key;

            child->TGmybox = new TMyGroupBox(parent->TWmybox, MYGROUPBOX_ID, NULL, x, y, w, h);

            child->TGmybox->Create();

            MyMessageScan();

            dialogboxes.insert(child);
            }
         else if ((parent = dialogboxes.get2(parentname, TDialog_type)) != NULL)
            {
            x = (x * BaseUnitsx) / 4;
            y = (y * BaseUnitsy) / 8;
            w = (w * BaseUnitsx) / 4;
            h = (h * BaseUnitsy) / 8;

            child->parent = parent->key;

            child->TGmybox = new TMyGroupBox(parent->TDmybox, MYGROUPBOX_ID, NULL, x, y, w, h);

            child->TGmybox->Create();
            
            MyMessageScan();
            
            dialogboxes.insert(child);
            }
         else
            {
            child->parent = (char *) MainWindowx->ScreenWindow;
            
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
            
            dialogboxes.insert(child);

            UpdateZoomControlFlag();
            }
         }
      else
         {
         ShowMessageAndStop("Already exists", childname);
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
      dialogthing *group;
      if ((group = dialogboxes.get2(groupname, TGroupBox_type)) != NULL)
         {
         if (dialogboxes.get(childname) == NULL)
            {
            dialogthing * child = new dialogthing(TRadioButton_type, childname);

            bool updateZoomControl = false;

            dialogthing *parent;
            if ((parent = dialogboxes.get2(parentname, TWindow_type)) != NULL)
               {
               x = (x * BaseUnitsx) / 4;
               y = (y * BaseUnitsy) / 8;
               w = (w * BaseUnitsx) / 4;
               h = (h * BaseUnitsy) / 8;

               child->parent = parent->key;

               child->TRmybox = new TMyRadioButton(
                  parent->TWmybox, 
                  titlename, 
                  x, 
                  y, 
                  w, 
                  h, 
                  group->TGmybox);
               }
            else if ((parent = dialogboxes.get2(parentname, TDialog_type)) != NULL)
               {
               x = (x * BaseUnitsx) / 4;
               y = (y * BaseUnitsy) / 8;
               w = (w * BaseUnitsx) / 4;
               h = (h * BaseUnitsy) / 8;

               child->parent = parent->key;
            
               child->TRmybox = new TMyRadioButton(
                  parent->TDmybox, 
                  titlename, 
                  x, 
                  y,
                  w, 
                  h,
                  group->TGmybox);
               }
            else
               {
               child->parent = (char *) MainWindowx->ScreenWindow;

               child->TRmybox = new TMyRadioButton(
                  MainWindowx->ScreenWindow,
                  titlename,
                  +x - MainWindowx->ScreenWindow->Scroller->XPos+xoffset,
                  -y - MainWindowx->ScreenWindow->Scroller->YPos+yoffset,
                  w,
                  h,
                  group->TGmybox);
               
               updateZoomControl = true;
               }

            child->TRmybox->Create();
               
            MyMessageScan();

            dialogboxes.insert(child);

            if (updateZoomControl)
               {
               UpdateZoomControlFlag();
               }
            }
         else
            {
            ShowMessageAndStop("Already exists", childname);
            }
         }
      else
         {
         ShowMessageAndStop("Does not exist", groupname);
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
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   dialogthing *parent;
   if ((parent = dialogboxes.get2(parentname, TRadioButton_type)) != NULL)
      {
      if (BF_CHECKED == parent->TRmybox->GetCheck())
         {
         return Truex;
         }
      else
         {
         return Falsex;
         }
      }
   else
      {
      ShowMessageAndStop("Does not exist", parentname);
      }

   return Unbound;
   }

NODE *lradiobuttonset(NODE *args)
   {
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   bool pos = boolean_arg(args = cdr(args));

   dialogthing *parent;
   if ((parent = dialogboxes.get2(parentname, TRadioButton_type)) != NULL)
      {
      if (pos)
         {
         ((TCheckBox *) parent->TRmybox)->Check();
         }
      else
         {
         ((TCheckBox *) parent->TRmybox)->Uncheck();
         }
      }
   else
      {
      ShowMessageAndStop("Does not exist", parentname);
      }

   return Unbound;
   }

NODE *lcheckboxcreate(NODE *args)
   {
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
      dialogthing *group;
      if ((group = dialogboxes.get2(groupname, TGroupBox_type)) != NULL)
         {

         if (dialogboxes.get(childname) == NULL)
            {
            dialogthing * child = new dialogthing(TCheckBox_type, childname);

            dialogthing *parent;
            if ((parent = dialogboxes.get2(parentname, TWindow_type)) != NULL)
               {
               x = (x * BaseUnitsx) / 4;
               y = (y * BaseUnitsy) / 8;
               w = (w * BaseUnitsx) / 4;
               h = (h * BaseUnitsy) / 8;

               child->parent = parent->key;
               
               child->TCBmybox = new TMyCheckBox(
                  parent->TWmybox, 
                  MYCHECKBOX_ID, 
                  titlename, 
                  x, 
                  y, 
                  w, 
                  h, 
                  group->TGmybox);
               
               child->TCBmybox->Create();
               
               MyMessageScan();
               
               dialogboxes.insert(child);
               }
            else if ((parent = dialogboxes.get2(parentname, TDialog_type)) != NULL)
               {
               x = (x * BaseUnitsx) / 4;
               y = (y * BaseUnitsy) / 8;
               w = (w * BaseUnitsx) / 4;
               h = (h * BaseUnitsy) / 8;
            
               child->parent = parent->key;
               
               child->TCBmybox = new TMyCheckBox(
                  parent->TDmybox, 
                  MYCHECKBOX_ID, 
                  titlename, 
                  x, 
                  y, 
                  w, 
                  h, 
                  group->TGmybox);
               
               child->TCBmybox->Create();
               
               MyMessageScan();
               
               dialogboxes.insert(child);
               }
            else
               {
               child->parent = (char *) MainWindowx->ScreenWindow;

               child->TCBmybox = new TMyCheckBox(
                  MainWindowx->ScreenWindow,
                  MYCHECKBOX_ID,
                  titlename,
                  +x - MainWindowx->ScreenWindow->Scroller->XPos+xoffset,
                  -y - MainWindowx->ScreenWindow->Scroller->YPos+yoffset,
                  w,
                  h,
                  group->TGmybox);
               
               child->TCBmybox->Create();
               
               MyMessageScan();
               
               dialogboxes.insert(child);

               UpdateZoomControlFlag();
               }
            }
         else
            {
            ShowMessageAndStop("Already exists", childname);
            }
         }
      else
         {
         ShowMessageAndStop("Does not exist", groupname);
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
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   dialogthing *parent;
   if ((parent = dialogboxes.get2(parentname, TCheckBox_type)) != NULL)
      {
      if (BF_CHECKED == parent->TCBmybox->GetCheck())
         {
         return Truex;
         }
      else
         {
         return Falsex;
         }
      }
   else
      {
      ShowMessageAndStop("Does not exist", parentname);
      }

   return Unbound;
   }

NODE *lcheckboxset(NODE *args)
   {
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   // int pos = getint(pos_int_arg(args = cdr(args)));
   int pos = boolean_arg(args = cdr(args));

   dialogthing *parent;
   if ((parent = dialogboxes.get2(parentname, TCheckBox_type)) != NULL)
      {
      if (pos)
         {
         parent->TCBmybox->Check();
         }
      else
         {
         parent->TCBmybox->Uncheck();
         }
      }
   else
      {
      ShowMessageAndStop("Does not exist", parentname);
      }

   return Unbound;
   }

BOOL CheckOnScreenControls()
   {
   return dialogboxes.OnScreenControlsExist();
   }

NODE *ldebugwindows(NODE *arg)
   {
   if (arg != NIL)
      {
      char childname[MAX_BUFFER_SIZE];
      cnv_strnode_string(childname, arg);
      
      if (dialogboxes.get(childname) != NULL)
         {
         dialogboxes.list(childname, 0);
         }
      else
         {
         ShowMessageAndStop("Does not exist", childname);
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

   NODE * targ = make_strnode(str);
   NODE * val = parser(targ, false);
   return val;
   }

NODE *lselectbox(NODE *args)
   {
   char banner[MAX_BUFFER_SIZE];
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
         char textbuf[MAX_BUFFER_SIZE];
         cnv_strnode_string(textbuf, args);

         dlg.AddString(textbuf);

         args = cdr(args);
         }
      }

   int iStatus = dlg.Execute();

   if (iStatus >= 0)
      {
      return make_intnode(iStatus + 1);
      }
   else
      {
      err_logo(STOP_ERROR, NIL);
      return make_intnode(0);
      }
   }

NODE *lyesnobox(NODE *args)
   {
   char banner[MAX_BUFFER_SIZE];
   cnv_strnode_string(banner, args);

   char body[MAX_BUFFER_SIZE];
   cnv_strnode_string(body, args = cdr(args));

   int iStatus = MainWindowx->CommandWindow->MessageBox(
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
   hCursorSave = ::SetCursor(hCursorWait);

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
      NODE * arg = make_strnode(filename);
      NODE * val = arg; // parser(arg, false);
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

   // Get file name from user and then save the file
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
   cnv_strnode_string(filename, args);

   char editexit[MAX_BUFFER_SIZE];
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

