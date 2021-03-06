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

enum WINDOWTYPE 
   {
      WINDOWTYPE_None,
      WINDOWTYPE_Window,
      WINDOWTYPE_Static,
      WINDOWTYPE_ListBox,
      WINDOWTYPE_ComboBox,
      WINDOWTYPE_Button,
      WINDOWTYPE_ScrollBar,
      WINDOWTYPE_GroupBox,
      WINDOWTYPE_RadioButton,
      WINDOWTYPE_CheckBox,
      WINDOWTYPE_Dialog,
   };

static HICON hCursorSave = 0; // handle for saved cursor


class TClientRectangle
   {
public:
   TClientRectangle();

   void InitializeFromInput(NODE * & Args);

   int GetX() const {return x;}
   int GetY() const {return y;}
   int GetWidth() const {return width;}
   int GetHeight() const {return height;}

   void ConvertToDialogCoordinates();
   void ConvertToScreenCoordinates();

private:
   int x;
   int y;
   int width;
   int height;
   };

TClientRectangle::TClientRectangle() : 
   x(0),
   y(0),
   width(0), 
   height(0)
   {
   }

void TClientRectangle::InitializeFromInput(NODE * & Args)
   {
   NODE * nextinput = Args;

   x = int_arg(nextinput);
   nextinput = cdr(nextinput);

   y = int_arg(nextinput);
   nextinput = cdr(nextinput);

   width = getint(pos_int_arg(nextinput));
   nextinput = cdr(nextinput);

   height = getint(pos_int_arg(nextinput));
   nextinput = cdr(nextinput);
   
   Args = nextinput;
   }

void TClientRectangle::ConvertToDialogCoordinates()
   {
   x = (x * BaseUnitsx) / 4;
   y = (y * BaseUnitsy) / 8;

   width  = (width  * BaseUnitsx) / 4;
   height = (height * BaseUnitsy) / 8;
   }

void TClientRectangle::ConvertToScreenCoordinates()
   {
   x =  x - MainWindowx->ScreenWindow->Scroller->XPos + xoffset;
   y = -y - MainWindowx->ScreenWindow->Scroller->YPos + yoffset;
   }

// class structures for the controls we support, for the most part they
// are the same as the original with just a callback string added

class TMxDialog : public TDialog
   {
public:
   char callback[MAX_BUFFER_SIZE];
   char caption[MAX_BUFFER_SIZE];

   TClientRectangle clientrect;

   TMxDialog(
      TWindow * Parent
      ) : TDialog(Parent, "DIALOGSTUB")
      {
      }

protected:
   void SetupWindow();

   void CmCancel()
      {
      // no cancel
      }

   void CmOk()
      {
      // no close
      }

   DECLARE_RESPONSE_TABLE(TMxDialog);
   };


void TMxDialog::SetupWindow()
   {
   SetWindowPos(
      NULL, 
      clientrect.GetX(), 
      clientrect.GetY(),
      clientrect.GetWidth(), 
      clientrect.GetHeight(), 
      0);

   SetCaption(caption);

   do_execution(callback);

   TDialog::SetupWindow();
   }

DEFINE_RESPONSE_TABLE1(TMxDialog, TDialog)
   EV_COMMAND(IDCANCEL, CmCancel),
   EV_COMMAND(IDOK, CmOk),
END_RESPONSE_TABLE;


class TMyListBox : public TListBox
   {
public:

   TMyListBox(
      TWindow                * Parent, 
      const TClientRectangle & ClientRect
      ) : TListBox(
         Parent, 
         MYLISTBOX_ID, 
         ClientRect.GetX(), 
         ClientRect.GetY(), 
         ClientRect.GetWidth(), 
         ClientRect.GetHeight())
      {
      // disable automatic sorting
      Attr.Style ^= LBS_SORT;
      }
   };

class TMxComboBox : public TComboBox
   {
public:
   TMxComboBox(
      TWindow                * Parent, 
      const TClientRectangle & ClientRect
      ) : TComboBox(
         Parent, 
         MYCOMBOBOX_ID, 
         ClientRect.GetX(), 
         ClientRect.GetY(), 
         ClientRect.GetWidth(), 
         ClientRect.GetHeight(),
         CBS_SIMPLE, 
         0)
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
      TWindow                * Parent,
      const char             * Text, 
      const TClientRectangle & ClientRect
      ) : TStatic(
         Parent, 
         MYSTATIC_ID, 
         Text, 
         ClientRect.GetX(), 
         ClientRect.GetY(), 
         ClientRect.GetWidth(), 
         ClientRect.GetHeight())
      {
      }
   };

class TMyButton : public TButton
   {
public:
   char callback[MAX_BUFFER_SIZE];

   TMyButton(
      TWindow                * Parent, 
      const char             * Text, 
      const TClientRectangle & ClientRect
      ) : TButton(
         Parent, 
         MYBUTTON_ID, 
         Text, 
         ClientRect.GetX(), 
         ClientRect.GetY(), 
         ClientRect.GetWidth(), 
         ClientRect.GetHeight())
      {
      }

   void EvLButtonUp(UINT modKeys, TPoint &point);
   DECLARE_RESPONSE_TABLE(TMyButton);
   };

DEFINE_RESPONSE_TABLE1(TMyButton, TButton)
   EV_WM_LBUTTONUP,
END_RESPONSE_TABLE;


// if the button gets clicked we end up here and queue the event 
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
      TWindow                * Parent, 
      const TClientRectangle & ClientRect,
      bool                     IsHScrollBar
      ) : TScrollBar(
         Parent, 
         MYSCROLLBAR_ID,
         ClientRect.GetX(),
         ClientRect.GetY(),
         IsHScrollBar  ? ClientRect.GetWidth()  : 0,
         !IsHScrollBar ? ClientRect.GetHeight() : 0,
         IsHScrollBar),
        rangeoffset(0)
      {
      }

   int  Get();
   void Set(int low, int high, int position);

   protected:
   void SetPosition(int, bool redraw = true);

   private:
   int  rangeoffset;
   };

void TMyScrollBar::SetPosition(int thumbpos, bool redraw)
   {
   TScrollBar::SetPosition(thumbpos, redraw);

   callthing *callevent = callthing::CreateNoYieldFunctionEvent(callback);
   calllists.insert(callevent);
   checkqueue();
   }

void TMyScrollBar::Set(int low, int high, int position)
   {
   if (low < 0)
      {
      // if the low value is negative, then shift the 
      // range so that we keep it positive.
      // The OWL class cannot handle a negative low position.
      rangeoffset = low;

      low       = 0;
      high     -= rangeoffset;
      position -= rangeoffset;
      }
   else
      {
      rangeoffset = 0;
      }

   SetRange(low, high);
   SetPosition(position);
   }

int TMyScrollBar::Get()
   {
   return GetPosition() + rangeoffset;
   }

class TMyGroupBox : public TGroupBox
   {
   public:
   TMyGroupBox(
      TWindow                * Parent, 
      const TClientRectangle & ClientRect
      ) : TGroupBox(
         Parent, 
         MYGROUPBOX_ID, 
         NULL, 
         ClientRect.GetX(), 
         ClientRect.GetY(), 
         ClientRect.GetWidth(), 
         ClientRect.GetHeight())
      {
      }
   };

class TMyRadioButton : public TRadioButton
   {
   public:

   TMyRadioButton(
      TWindow                * Parent, 
      const char             * Title, 
      const TClientRectangle & ClientRect,
      TGroupBox              * Group
      ) : TRadioButton(
         Parent, 
         MYRADIOBUTTON_ID, 
         Title, 
         ClientRect.GetX(), 
         ClientRect.GetY(), 
         ClientRect.GetWidth(), 
         ClientRect.GetHeight(),
         Group)
      {
      }
   };

class TMyCheckBox : public TCheckBox
   {
   public:
   TMyCheckBox(
      TWindow                * Parent, 
      const char             * Title, 
      const TClientRectangle & ClientRect,
      TGroupBox              * Group
      ) : TCheckBox(
         Parent, 
         MYCHECKBOX_ID, 
         Title,
         ClientRect.GetX(), 
         ClientRect.GetY(), 
         ClientRect.GetWidth(), 
         ClientRect.GetHeight(),
         Group)
      {
      }
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

   WINDOWTYPE type;

   union
      {
      class TMxDialog      * TDmybox;
      class TMyStatic      * TSmybox;
      class TMyListBox     * TLmybox;
      class TMxComboBox    * TCmybox;
      class TMyButton      * TBmybox;
      class TMyScrollBar   * TSCmybox;
      class TMyGroupBox    * TGmybox;
      class TMyRadioButton * TRmybox;
      class TMyCheckBox    * TCBmybox;
      };

   dialogthing(WINDOWTYPE t, const char * name)
     : next(NULL),
       prev(NULL),
       parent(NULL),
       type(t),
       TDmybox(NULL)
      {
      strcpy(key, name);
      }

   TWindow * GetWindow();
   };

TWindow * dialogthing::GetWindow()
   {
   switch (type)
      {
      case WINDOWTYPE_Window:      return TDmybox;
      case WINDOWTYPE_Static:      return TSmybox;
      case WINDOWTYPE_ListBox:     return TLmybox;
      case WINDOWTYPE_ComboBox:    return TCmybox;
      case WINDOWTYPE_Button:      return TBmybox;
      case WINDOWTYPE_ScrollBar:   return TSCmybox;
      case WINDOWTYPE_GroupBox:    return TGmybox;
      case WINDOWTYPE_RadioButton: return TRmybox;
      case WINDOWTYPE_CheckBox:    return TCBmybox;
      case WINDOWTYPE_Dialog:      return TDmybox;
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
   dialogthing * get(const char *k, WINDOWTYPE type);
   dialogthing * get(const char *k, WINDOWTYPE type1, WINDOWTYPE type2);
   const char *getrootkey();
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

// returns the element whose key is "key"
dialogthing * dialoglist::get(const char *key)
   {
   if (last == NULL) 
      {
      return NULL;
      }

   dialogthing * f = last;

   do
      {
      if (strcmp(f->key, key) == 0)
         {
         return f;
         }
      f = f->next;
      }
   while (f != last);

   return NULL;
   }

// returns the element whose key is k and whose type is t
dialogthing * dialoglist::get(const char *key, WINDOWTYPE type)
   {
   dialogthing * item = get(key);
   if (item != NULL)
      {
      // the window exists
      if (item->type == type) 
         {
         // the window has the correct type
         return item;
         }
      }

   return NULL;
   }

// returns the element whose key is "key" and whose type is either type1 or type2
dialogthing * dialoglist::get(const char *key, WINDOWTYPE type1, WINDOWTYPE type2)
   {
   dialogthing * item = get(key);
   if (item != NULL)
      {
      // the window exists
      if (item->type == type1 || item->type == type2) 
         {
         // the window exists and has the correct type
         return item;
         }
      }

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

   // find the link whose key is "k"
   dialogthing * p = get(k);

   // delete any children first
   const char *t;
   while ((t = getfirstchild(k)) != NULL)
      {
      zap(t);
      }

   // remove the link from the list
   if (p != NULL)
      {
      dialogthing * f = p->next;

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
   dialogthing * p = get(k);
   if (p != NULL)
      {
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
            "CheckBox",
            "Dialog",
         };

      const size_t MAX_WINDOWNAME_LENGTH = sizeof("radiobutton");

      if (level == 0)
         {
         char temp[MAX_WINDOWNAME_LENGTH + 1 + MAX_BUFFER_SIZE + 1];
         sprintf(temp, "%s %s", Windowname[(int)p->type], p->key);
         putcombobox(temp);
         }

      dialogthing *ff = last;
      do
         {
         if (strcmp(ff->parent, k) == 0)
            {
            char temp[2 + 1 + MAX_WINDOWNAME_LENGTH + 1 + MAX_BUFFER_SIZE + 1];
            sprintf(temp, "  %*s%s %s", level, "", Windowname[(int)ff->type], ff->key);
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

   last = NULL;
   }

// returns the key of the first element whose parent is the root window.
// returns NULL, if no element's parent is the root window.
const char *dialoglist::getrootkey()
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
         if ((l->type != WINDOWTYPE_Window) && (l->type != WINDOWTYPE_Dialog))
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


NODE *leventcheck(NODE *)
   {
   // checkqueue();

   MSG msg;
   while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
      }

   return Unbound;
   }

// function that processes our own queued events 
void checkqueue()
   {
   while (callthing * thing = calllists.get())
      {
      bool save_yield_flag = yield_flag;
      int  sv_val_status = val_status;;

      calllists.zap();
      switch (thing->kind)
         {
         // mouse event must not yield while processing
         case EVENTTYPE_Mouse:
            yield_flag = false;
            mouse_posx = thing->arg1;
            mouse_posy = thing->arg2;
            do_execution(thing->func);
            break;

          // keyboard event must not yield while processing
          case EVENTTYPE_Keyboard:
             yield_flag = false;
             keyboard_value = thing->arg1;
             do_execution(thing->func);
             break;

          // Button, timer or other event ok to yield while processing
          case EVENTTYPE_YieldFunction:
             do_execution(thing->func);
             break;

          // Scrollbar, MCI, Net, timer or other event must not yield while processing
          case EVENTTYPE_NoYieldFunction:
             yield_flag = false;
             do_execution(thing->func);
             break;

          // Network events must not yield while processing
          case EVENTTYPE_NetworkReceiveReady:
             yield_flag = false;

             // use the new value
             thing->networkconnection->SetLastPacketReceived(thing->networkpacket);
             thing->networkpacket = NULL;

             do_execution(thing->func);
             break;

         default:
            assert(0 && "bad callthing type");
            break;
         }

      delete thing;

      yield_flag = save_yield_flag;
      val_status = sv_val_status;
      }
   }

/* function to dump the queue */

void emptyqueue()
   {
   while (callthing * thing = calllists.get())
      {
      calllists.zap();

      delete thing;
      }
   }

/* User function to create a modeless window */

NODE *lwindowcreate(NODE *args)
   {
   /* get all the args */
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);
   args = cdr(args);

   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args);
   args = cdr(args);

   char titlename[MAX_BUFFER_SIZE];
   cnv_strnode_string(titlename, args);
   args = cdr(args);

   TClientRectangle clientrect;
   clientrect.InitializeFromInput(args);

   char callback[MAX_BUFFER_SIZE];
   if (args != NIL) 
      {
      cnv_strnode_string(callback, args);
      }
   else 
      {
      callback[0] = '\0';
      }


   if (NOT_THROWING)
      {
      // convert them to "DIALOG" units.
      // this is the key to making all Graphics Modes work correctly.

      clientrect.ConvertToDialogCoordinates();

      // if not already exist continue
      if (dialogboxes.get(childname) == NULL)
         {
         dialogthing *child = new dialogthing(WINDOWTYPE_Window, childname);

         // if parent exists use it else use main window
         dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_Window);
         if (parent != NULL)
            {
            child->TDmybox = new TMxDialog(parent->TDmybox);
            child->parent = (char *)parent->TDmybox;
            }
         else
            {
            child->TDmybox = new TMxDialog(MainWindowx->ScreenWindow);
            child->parent = (char *)MainWindowx->ScreenWindow;
            }

         // Modeless windows can have to have a callback to set them up
         // since it will return
         strcpy(child->TDmybox->callback, callback);
         strcpy(child->TDmybox->caption, titlename);

         // Most attributes are set in DIALOGSTUB
         child->TDmybox->clientrect = clientrect;

         dialogboxes.insert(child);

         child->TDmybox->Create();
         child->TDmybox->ShowWindow(SW_SHOW);

         // Make sure the window is up before we try to add controls
         MyMessageScan();
         }
      else
         {     
         ShowMessageAndStop("Already exists", childname);
         }
      }

   return Unbound;
   }


static
NODE *
WindowEnableHelper(
   NODE       * args,
   WINDOWTYPE   WindowType
)
   {
   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args);

   bool bEnable = boolean_arg(cdr(args));

   if (NOT_THROWING)
      {
      dialogthing *window = dialogboxes.get(childname, WindowType);
      if (window != NULL)
         {
         window->GetWindow()->EnableWindow(bEnable);
         }
      else
         {
         ShowMessageAndStop("Does not exist", childname);
         }
      }

   return Unbound;
   }


static
NODE *
WindowDeleteHelper(
   NODE       * args,
   WINDOWTYPE   WindowType
)
   {
   // get args
   char windowkey[MAX_BUFFER_SIZE];
   cnv_strnode_string(windowkey, args);

   if (NOT_THROWING)
      {
      // if it exists kill it
      dialogthing *window = dialogboxes.get(windowkey, WindowType);
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
      }

   return Unbound;
   }


NODE *lwindowenable(NODE *args)
   {
   return WindowEnableHelper(args, WINDOWTYPE_Window);
   }

NODE *lwindowdelete(NODE *arg)
   {
   char windowname[MAX_BUFFER_SIZE];
   cnv_strnode_string(windowname, arg);

   if (NOT_THROWING)
      {
      dialogthing *window = dialogboxes.get(windowname, WINDOWTYPE_Window);
      if (window != NULL)
         {
         // The exact name and type exists matches.
         // kill this window and all of its children.
         window->TDmybox->CloseWindow();
         dialogboxes.zap(windowname);
         }
      else
         {
         // No window exists that matches this name and type.
         // Close all windows.
         const char *tempkey;
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
      }

   return Unbound;
   }

NODE *ldialogcreate(NODE *args)
   {
   // get args
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);
   args = cdr(args);

   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args);
   args = cdr(args);

   char titlename[MAX_BUFFER_SIZE];
   cnv_strnode_string(titlename, args);
   args = cdr(args);

   TClientRectangle clientrect;
   clientrect.InitializeFromInput(args);

   char callback[MAX_BUFFER_SIZE];
   if (args != NIL) 
      {
      cnv_strnode_string(callback, args);
      }
   else 
      {
      callback[0] = '\0';
      }


   if (NOT_THROWING)
      {
      // convert to "DIALOG" units. 
      // This is the key to getting consistent results in all graphics MODEs.
      clientrect.ConvertToDialogCoordinates();

      // if it does not exist continue
      if (dialogboxes.get(childname) == NULL)
         {
         // make one
         dialogthing * child = new dialogthing(WINDOWTYPE_Dialog, childname);

         // if parent of corect type exists use it
         dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_Window);
         if (parent != NULL)
            {
            child->TDmybox = new TMxDialog(parent->TDmybox);
            child->parent = (char *)parent->TDmybox;
            }
         else
            {
            // else use main window
            child->TDmybox = new TMxDialog(MainWindowx->ScreenWindow);
            child->parent = (char *)MainWindowx->ScreenWindow;
            }

         // Modal windows have to have a callback to set them up
         // since it will not return until closed
         strcpy(child->TDmybox->callback, callback);
         strcpy(child->TDmybox->caption, titlename);

         // Most attributes are set in DIALOGSTUB
         child->TDmybox->clientrect = clientrect;

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
      }

   return Unbound;
   }

NODE *ldialogenable(NODE *args)
   {
   return WindowEnableHelper(args, WINDOWTYPE_Dialog);
   }
   
NODE *ldialogdelete(NODE *args)
   {
   return WindowDeleteHelper(args, WINDOWTYPE_Dialog);
   }

NODE *llistboxcreate(NODE *args)
   {
   // get args
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);
   args = cdr(args);

   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args);
   args = cdr(args);

   TClientRectangle clientrect;
   clientrect.InitializeFromInput(args);

   if (NOT_THROWING)
      {
      // if unique continue

      if (dialogboxes.get(childname) == NULL)
         {
         dialogthing * child = new dialogthing(WINDOWTYPE_ListBox, childname);

         dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_Window, WINDOWTYPE_Dialog);
         if (parent != NULL)
            {
            // The parent is a user-created window
            clientrect.ConvertToDialogCoordinates();
            
            child->parent = parent->key;

            child->TLmybox = new TMyListBox(parent->TDmybox, clientrect);
            }
         else
            {
            // else the parent does not exist -- put the control on the screen
            clientrect.ConvertToScreenCoordinates();

            child->parent = (char *)MainWindowx->ScreenWindow;

            child->TLmybox = new TMyListBox(MainWindowx->ScreenWindow, clientrect);
            }

         child->TLmybox->Create();
            
         MyMessageScan();
            
         dialogboxes.insert(child);

         if (parent == NULL)
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
   return WindowEnableHelper(args, WINDOWTYPE_ListBox);
   }

NODE *llistboxdelete(NODE *args)
   {
   return WindowDeleteHelper(args, WINDOWTYPE_ListBox);
   }

NODE *llistboxgetselect(NODE *args)
   {
   // get args
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   if (NOT_THROWING)
      {
      // If it exists continue
      dialogthing *parent;
      if ((parent = dialogboxes.get(parentname, WINDOWTYPE_ListBox)) != NULL)
         {
         // if success on fetching string return it
         char stringname[MAX_BUFFER_SIZE];
         if (parent->TLmybox->GetSelString(stringname, MAX_BUFFER_SIZE) >= 0)
            {
            // parsing it basically turns it into a list for us
            NODE * val = parser(make_strnode(stringname), false);
            return val;
            }
         else
            {
            // nothing is selected
            return NIL;
            }
         }
      else
         {
         ShowMessageAndStop("Does not exist", parentname);
         }
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

   if (NOT_THROWING)
      {
      // if exists continue
      dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_ListBox);
      if (parent != NULL)
         {
         // add entry and reset Index for consistency
         parent->TLmybox->AddString(stringname);
         parent->TLmybox->SetSelIndex(0);
         }
      else
         {
         ShowMessageAndStop("Does not exist", parentname);
         }
      }

   return Unbound;
   }

NODE *llistboxdeletestring(NODE *args)
   {
   // get args
   char listboxname[MAX_BUFFER_SIZE];
   cnv_strnode_string(listboxname, args);

   int index = getint(pos_int_arg(cdr(args)));

   if (NOT_THROWING)
      {
      // if exists continue
      dialogthing *listbox = dialogboxes.get(listboxname, WINDOWTYPE_ListBox);
      if (listbox != NULL)
         {
         // kill entry based on index
         listbox->TLmybox->DeleteString(index);
         listbox->TLmybox->SetSelIndex(0);
         }
      else
         {
         ShowMessageAndStop("Does not exist", listboxname);
         }
      }

   return Unbound;
   }

NODE *lcomboboxcreate(NODE *args)
   {
   // get args
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);
   args = cdr(args);

   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args);
   args = cdr(args);

   TClientRectangle clientrect;
   clientrect.InitializeFromInput(args);

   if (NOT_THROWING)
      {
      // if unique continue
      if (dialogboxes.get(childname) == NULL)
         {
         dialogthing * child = new dialogthing(WINDOWTYPE_ComboBox, childname);

         dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_Window, WINDOWTYPE_Dialog);
         if (parent != NULL)
            {
            // convert to "DIALOG" units
            clientrect.ConvertToDialogCoordinates();

            child->parent = parent->key;

            child->TCmybox = new TMxComboBox(parent->TDmybox, clientrect);
            }
         else
            {
            // else the parent does not exist -- put the control on the screen
            clientrect.ConvertToScreenCoordinates();

            child->parent = (char *) MainWindowx->ScreenWindow;

            child->TCmybox = new TMxComboBox(
               MainWindowx->ScreenWindow,
               clientrect);
            }

         child->TCmybox->Create();

         MyMessageScan();

         dialogboxes.insert(child);

         if (parent == NULL)
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
   return WindowEnableHelper(args, WINDOWTYPE_ComboBox);
   }

NODE *lcomboboxdelete(NODE *args)
   {
   return WindowDeleteHelper(args, WINDOWTYPE_ComboBox);
   }

NODE *lcomboboxgettext(NODE *args)
   {
   // get args
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   // if exists continue
   dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_ComboBox);
   if (parent != NULL)
      {
      // if successful getting string return it
      char stringname[MAX_BUFFER_SIZE];
      if (parent->TCmybox->GetText(stringname, MAX_BUFFER_SIZE) >= 0)
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
   dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_ComboBox);
   if (parent != NULL)
      {
      // set the editcontrol portion to the user specified text
      parent->TCmybox->SetText(stringname);
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
   dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_ComboBox);
   if (parent != NULL)
      {
      // add string and reset selection
      parent->TCmybox->AddString(stringname);
      parent->TCmybox->SetSelIndex(0);
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
   dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_ComboBox);
   if (parent != NULL)
      {
      // kill entry and reset index
      parent->TCmybox->DeleteString(index);
      parent->TCmybox->SetSelIndex(0);
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
   args = cdr(args);

   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args);
   args = cdr(args);

   TClientRectangle clientrect;
   clientrect.InitializeFromInput(args);

   char callback[MAX_BUFFER_SIZE];
   cnv_strnode_string(callback, args);
   if (NOT_THROWING)
      {
      if (dialogboxes.get(childname) == NULL)
         {
         dialogthing * child = new dialogthing(WINDOWTYPE_ScrollBar, childname);
         
         const bool isHorizontalScrollbar = clientrect.GetWidth() > clientrect.GetHeight();

         dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_Window, WINDOWTYPE_Dialog);
         if (parent != NULL)
            {
            clientrect.ConvertToDialogCoordinates();

            child->parent = parent->key;

            child->TSCmybox = new TMyScrollBar(
               parent->TDmybox, 
               clientrect,
               isHorizontalScrollbar);
            }
         else
            {
            clientrect.ConvertToScreenCoordinates();

            child->parent = (char*) MainWindowx->ScreenWindow;

            child->TSCmybox = new TMyScrollBar(
               MainWindowx->ScreenWindow,
               clientrect,
               isHorizontalScrollbar);
            }

         strcpy(child->TSCmybox->callback, callback);
            
         child->TSCmybox->Create();
            
         MyMessageScan();
            
         dialogboxes.insert(child);

         if (parent == NULL)
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

NODE *lscrollbarset(NODE *args)
   {
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);
   args = cdr(args);

   int lo  = int_arg(args);
   args = cdr(args);

   int hi  = int_arg(args);
   if (hi < lo)
      {
      // the low value must be less than the high value
      NODE * node = err_logo(BAD_DATA, car(args));
      gcref(node);
      }
   args = cdr(args);

   int pos = int_arg(args);

   if (NOT_THROWING)
      {
      dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_ScrollBar);
      if (parent != NULL)
         {
         parent->TSCmybox->Set(lo, hi, pos);
         }
      else
         {
         ShowMessageAndStop("Does not exist", parentname);
         }
      }

   return Unbound;
   }

NODE *lscrollbarget(NODE *args)
   {
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   if (NOT_THROWING)
      {
      dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_ScrollBar);
      if (parent != NULL)
         {
         int pos = parent->TSCmybox->Get();
         return make_intnode(pos);
         }
      else
         {
         ShowMessageAndStop("Does not exist", parentname);
         }
      }

   return Unbound;
   }

NODE *lscrollbarenable(NODE *args)
   {
   return WindowEnableHelper(args, WINDOWTYPE_ScrollBar);
   }

NODE *lscrollbardelete(NODE *args)
   {
   return WindowDeleteHelper(args, WINDOWTYPE_ScrollBar);
   }

NODE *lstaticcreate(NODE *args)
   {
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);
   args = cdr(args);

   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args);
   args = cdr(args);

   char titlename[MAX_BUFFER_SIZE];
   cnv_strnode_string(titlename, args);
   args = cdr(args);

   TClientRectangle clientrect;
   clientrect.InitializeFromInput(args);

   if (NOT_THROWING)
      {
      if (dialogboxes.get(childname) == NULL)
         {
         dialogthing * child = new dialogthing(WINDOWTYPE_Static, childname);

         dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_Window, WINDOWTYPE_Dialog);
         if (parent != NULL)
            {
            clientrect.ConvertToDialogCoordinates();

            child->parent = parent->key;

            child->TSmybox = new TMyStatic(
               parent->TDmybox, 
               titlename, 
               clientrect);
            }
         else
            {
            clientrect.ConvertToScreenCoordinates();

            child->parent = (char *) MainWindowx->ScreenWindow;
            
            child->TSmybox = new TMyStatic(
               MainWindowx->ScreenWindow,
               titlename,
               clientrect);
            }

         child->TSmybox->Create();
            
         MyMessageScan();
            
         dialogboxes.insert(child);

         if (parent == NULL)
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

NODE *lstaticupdate(NODE *args)
   {
   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args);

   char titlename[MAX_BUFFER_SIZE];
   cnv_strnode_string(titlename, cdr(args));

   dialogthing *temp = dialogboxes.get(childname, WINDOWTYPE_Static);
   if (temp != NULL)
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
   return WindowDeleteHelper(args, WINDOWTYPE_Static);
   }

NODE *lbuttoncreate(NODE *args)
   {
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);
   args = cdr(args);

   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args);
   args = cdr(args);

   char titlename[MAX_BUFFER_SIZE];
   cnv_strnode_string(titlename, args);
   args = cdr(args);

   TClientRectangle clientrect;
   clientrect.InitializeFromInput(args);

   char callback[MAX_BUFFER_SIZE];
   if (args != NIL)
      {
      cnv_strnode_string(callback, args);
      }
   else
      {
      callback[0] = '\0';
      }

   if (NOT_THROWING)
      {
      if (dialogboxes.get(childname) == NULL)
         {
         dialogthing * child = new dialogthing(WINDOWTYPE_Button, childname);

         dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_Window, WINDOWTYPE_Dialog);
         if (parent != NULL)
            {
            clientrect.ConvertToDialogCoordinates();

            child->parent = parent->key;

            child->TBmybox = new TMyButton(
               parent->TDmybox,
               titlename,
               clientrect);
            }
         else
            {
            clientrect.ConvertToScreenCoordinates();

            child->parent = (char *) MainWindowx->ScreenWindow;

            child->TBmybox = new TMyButton(
               MainWindowx->ScreenWindow,
               titlename,
               clientrect);
            }

         strcpy(child->TBmybox->callback, callback);

         child->TBmybox->Create();

         MyMessageScan();

         dialogboxes.insert(child);

         if (parent == NULL)
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

NODE *lbuttonupdate(NODE *args)
   {
   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args);

   char titlename[MAX_BUFFER_SIZE];
   cnv_strnode_string(titlename, cdr(args));

   if (NOT_THROWING)
      {
      dialogthing *temp = dialogboxes.get(childname, WINDOWTYPE_Button);
      if (temp != NULL)
         {
         temp->TBmybox->SetWindowText(titlename);
         }
      else
         {
         ShowMessageAndStop("Does not exist", childname);
         }
      }

   return Unbound;
   }

NODE *lbuttonenable(NODE *args)
   {
   return WindowEnableHelper(args, WINDOWTYPE_Button);
   }

NODE *lbuttondelete(NODE *args)
   {
   return WindowDeleteHelper(args, WINDOWTYPE_Button);
   }

NODE *lgroupboxcreate(NODE *args)
   {
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);
   args = cdr(args);

   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args);
   args = cdr(args);

   TClientRectangle clientrect;
   clientrect.InitializeFromInput(args);

   if (NOT_THROWING)
      {
      if (dialogboxes.get(childname) == NULL)
         {
         dialogthing * child = new dialogthing(WINDOWTYPE_GroupBox, childname);

         dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_Window, WINDOWTYPE_Dialog);
         if (parent != NULL)
            {
            clientrect.ConvertToDialogCoordinates();

            child->parent = parent->key;

            child->TGmybox = new TMyGroupBox(
               parent->TDmybox, 
               clientrect);
            }
         else
            {
            clientrect.ConvertToScreenCoordinates();

            child->parent = (char *) MainWindowx->ScreenWindow;
            
            child->TGmybox = new TMyGroupBox(
               MainWindowx->ScreenWindow, 
               clientrect);
            }

         child->TGmybox->Create();

         MyMessageScan();

         dialogboxes.insert(child);

         if (parent == NULL)
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

NODE *lgroupboxdelete(NODE *args)
   {
   return WindowDeleteHelper(args, WINDOWTYPE_GroupBox);
   }

NODE *lradiobuttoncreate(NODE *args)
   {
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);
   args = cdr(args);

   char groupname[MAX_BUFFER_SIZE];
   cnv_strnode_string(groupname, args);
   args = cdr(args);

   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args);
   args = cdr(args);

   char titlename[MAX_BUFFER_SIZE];
   cnv_strnode_string(titlename, args);
   args = cdr(args);

   TClientRectangle clientrect;
   clientrect.InitializeFromInput(args);

   if (NOT_THROWING)
      {
      dialogthing *group = dialogboxes.get(groupname, WINDOWTYPE_GroupBox);
      if (group != NULL)
         {
         if (dialogboxes.get(childname) == NULL)
            {
            dialogthing * child = new dialogthing(WINDOWTYPE_RadioButton, childname);

            dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_Window, WINDOWTYPE_Dialog);
            if (parent != NULL)
               {
               clientrect.ConvertToDialogCoordinates();

               child->parent = parent->key;

               child->TRmybox = new TMyRadioButton(
                  parent->TDmybox, 
                  titlename, 
                  clientrect,
                  group->TGmybox);
               }
            else
               {
               clientrect.ConvertToScreenCoordinates();

               child->parent = (char *) MainWindowx->ScreenWindow;

               child->TRmybox = new TMyRadioButton(
                  MainWindowx->ScreenWindow,
                  titlename,
                  clientrect,
                  group->TGmybox);
               }

            child->TRmybox->Create();
               
            MyMessageScan();

            dialogboxes.insert(child);

            if (parent == NULL)
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
   return WindowEnableHelper(args, WINDOWTYPE_RadioButton);
   }

NODE *lradiobuttondelete(NODE *args)
   {
   return WindowDeleteHelper(args, WINDOWTYPE_RadioButton);
   }

NODE *lradiobuttonget(NODE *args)
   {
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   if (NOT_THROWING)
      {
      dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_RadioButton);
      if (parent != NULL)
         {
         uint check = parent->TRmybox->GetCheck();
         return true_or_false(BF_CHECKED == check);
         }
      else
         {
         ShowMessageAndStop("Does not exist", parentname);
         }
      }

   return Unbound;
   }

NODE *lradiobuttonset(NODE *args)
   {
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   bool pos = boolean_arg(args = cdr(args));

   if (NOT_THROWING)
      {
      dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_RadioButton);
      if (parent != NULL)
         {
         if (pos)
            {
            parent->TRmybox->Check();
            }
         else
            {
            parent->TRmybox->Uncheck();
            }
         }
      else
         {
         ShowMessageAndStop("Does not exist", parentname);
         }
      }

   return Unbound;
   }

NODE *lcheckboxcreate(NODE *args)
   {
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);
   args = cdr(args);

   char groupname[MAX_BUFFER_SIZE];
   cnv_strnode_string(groupname, args);
   args = cdr(args);

   char childname[MAX_BUFFER_SIZE];
   cnv_strnode_string(childname, args);
   args = cdr(args);

   char titlename[MAX_BUFFER_SIZE];
   cnv_strnode_string(titlename, args);
   args = cdr(args);

   TClientRectangle clientrect;
   clientrect.InitializeFromInput(args);

   if (NOT_THROWING)
      {
      dialogthing *group = dialogboxes.get(groupname, WINDOWTYPE_GroupBox);
      if (group != NULL)
         {

         if (dialogboxes.get(childname) == NULL)
            {
            dialogthing * child = new dialogthing(WINDOWTYPE_CheckBox, childname);

            dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_Window, WINDOWTYPE_Dialog);
            if (parent != NULL)
               {
               clientrect.ConvertToDialogCoordinates();
            
               child->parent = parent->key;
               
               child->TCBmybox = new TMyCheckBox(
                  parent->TDmybox, 
                  titlename, 
                  clientrect,
                  group->TGmybox);
               }
            else
               {
               clientrect.ConvertToScreenCoordinates();

               child->parent = (char *) MainWindowx->ScreenWindow;

               child->TCBmybox = new TMyCheckBox(
                  MainWindowx->ScreenWindow,
                  titlename,
                  clientrect,
                  group->TGmybox);
               }

               child->TCBmybox->Create();
               
               MyMessageScan();
               
               dialogboxes.insert(child);

               if (parent == NULL)
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

NODE *lcheckboxenable(NODE *args)
   {
   return WindowEnableHelper(args, WINDOWTYPE_CheckBox);
   }

NODE *lcheckboxdelete(NODE *args)
   {
   return WindowDeleteHelper(args, WINDOWTYPE_CheckBox);
   }

NODE *lcheckboxget(NODE *args)
   {
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   if (NOT_THROWING)
      {
      dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_CheckBox);
      if (parent != NULL)
         {
         uint check = parent->TCBmybox->GetCheck();
         return true_or_false(BF_CHECKED == check);
         }
      else
         {
         ShowMessageAndStop("Does not exist", parentname);
         }
      }

   return Unbound;
   }

NODE *lcheckboxset(NODE *args)
   {
   char parentname[MAX_BUFFER_SIZE];
   cnv_strnode_string(parentname, args);

   int pos = boolean_arg(args = cdr(args));

   if (NOT_THROWING)
      {
      dialogthing *parent = dialogboxes.get(parentname, WINDOWTYPE_CheckBox);
      if (parent != NULL)
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
      }

   return Unbound;
   }

bool CheckOnScreenControls()
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

   if (NOT_THROWING)
      {
      if (MainWindowx->CommandWindow->MessageBox(body, banner, MB_OKCANCEL) == IDCANCEL)
         {
         err_logo(STOP_ERROR, NIL);
         }
      }

   return Unbound;
   }

NODE *lquestionbox(NODE *args)
   {
   char banner[MAX_BUFFER_SIZE];
   cnv_strnode_string(banner, args);

   char body[MAX_BUFFER_SIZE];
   cnv_strnode_string(body, args = cdr(args));

   if (NOT_THROWING)
      {
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

   return Unbound;
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

   // must be a list that contains something
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

   if (NOT_THROWING)
      {
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

   // if user found a file then try to load it
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

void uninitialize_windows()
   {
   dialogboxes.clear();
   }
