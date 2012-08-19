// Copyright (C) 1995 by the Regents of the University of California
// Copyright (C) 1995 by George Mills
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "dlgwind.h"

#include <wx/app.h>
#include <wx/choicdlg.h>
#include <wx/textdlg.h>
#include <wx/button.h>
#include <wx/listbox.h>

#include "fmslogo.h"
#include "mainframe.h"
#include "mainwind.h"
#include "screen.h"
#include "coms.h"
#include "parse.h"
#include "logodata.h"
#include "logomath.h"
#include "main.h"
#include "localizedstrings.h"
#include "init.h"
#include "argumentutils.h"
#include "graphwin.h"
#include "error.h"
#include "eval.h"
#include "logocore.h"
#include "lists.h"
#include "screenwindow.h"
#include "debugheap.h"

enum WINDOWTYPE 
{
    WINDOWTYPE_None,
    WINDOWTYPE_Window,
    //WINDOWTYPE_Static,
    WINDOWTYPE_ListBox,
    //WINDOWTYPE_ComboBox,
    WINDOWTYPE_Button,
    //WINDOWTYPE_ScrollBar,
    //WINDOWTYPE_GroupBox,
    //WINDOWTYPE_RadioButton,
    //WINDOWTYPE_CheckBox,
    WINDOWTYPE_Dialog,
};

// TODO: Derive from wxRect
class CClientRectangle
{
public:
    CClientRectangle();

    void InitializeFromInput(NODE * & Args);

    int GetX() const {return m_X;}
    int GetY() const {return m_Y;}
    int GetWidth() const {return m_Width;}
    int GetHeight() const {return m_Height;}

    void ConvertToDialogCoordinates();
    void ConvertToScreenCoordinates();

private:
    int m_X;
    int m_Y;
    int m_Width;
    int m_Height;
};

CClientRectangle::CClientRectangle() : 
    m_X(0),
    m_Y(0),
    m_Width(0), 
    m_Height(0)
{
}

void CClientRectangle::InitializeFromInput(NODE * & Args)
{
    NODE * nextinput = Args;

    m_X = int_arg(nextinput);
    nextinput = cdr(nextinput);

    m_Y = int_arg(nextinput);
    nextinput = cdr(nextinput);

    m_Width = getint(nonnegative_int_arg(nextinput));
    nextinput = cdr(nextinput);

    m_Height = getint(nonnegative_int_arg(nextinput));
    nextinput = cdr(nextinput);
   
    Args = nextinput;
}

void CClientRectangle::ConvertToDialogCoordinates()
{
    m_X = (m_X * BaseUnitsx) / 4;
    m_Y = (m_Y * BaseUnitsy) / 8;

    m_Width  = (m_Width  * BaseUnitsx) / 4;
    m_Height = (m_Height * BaseUnitsy) / 8;
}

void CClientRectangle::ConvertToScreenCoordinates()
{
    m_X =  m_X - GetScreenHorizontalScrollPosition() + xoffset;
    m_Y = -m_Y - GetScreenVerticalScrollPosition()   + yoffset;
}

static void SetMswLogoCompatibleFont(wxWindow * Window)
{
    // Sets the font to look like it did in MSWLogo.
    wxFont font = Window->GetFont();
    font.SetFaceName("System");
    Window->SetFont(font);
}

// class structures for the controls we support, for the most part they
// are the same as the original with just a callback string added

class CLogoDialog : public wxDialog
{
public:
    CLogoDialog(
        wxWindow               * Parent,
        const wxString         & Caption,
        const CClientRectangle & ClientRectangle
        ) : wxDialog(
            Parent,
            wxID_ANY,
            Caption,
            wxPoint(ClientRectangle.GetX(), ClientRectangle.GetY()),
            wxSize(ClientRectangle.GetWidth(), ClientRectangle.GetHeight()),
            wxCAPTION) //DS_MODALFRAME | WS_POPUP
    {
    }

private:

    // Event handlers
    void OnOkButton(wxCommandEvent& Event);
    void OnCancelButton(wxCommandEvent& Event);

    DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CLogoDialog);
};

void CLogoDialog::OnOkButton(wxCommandEvent& Event)
{
}

void CLogoDialog::OnCancelButton(wxCommandEvent& Event)
{
}

// REVISIT: This was really supposed to prevent closing the window
// from normal UI events, like pressing the "X" on the system menu.
// However, since the system menu doesn't show up, I'm not sure how
// useful this is.  Also, in the OWL implementation, Alt+F4 would close
// the window and I'm not sure if that's a good thing or not.
BEGIN_EVENT_TABLE(CLogoDialog, wxDialog)
    EVT_BUTTON(wxID_OK,     CLogoDialog::OnOkButton)
    EVT_BUTTON(wxID_CANCEL, CLogoDialog::OnCancelButton)
END_EVENT_TABLE()

class CLogoListBox : public wxListBox
{
public:

    CLogoListBox(
        wxWindow               * Parent,
        const CClientRectangle & ClientRectangle
        ) : wxListBox(
            Parent,
            wxID_ANY,
            wxPoint(ClientRectangle.GetX(), ClientRectangle.GetY()),
            wxSize(ClientRectangle.GetWidth(), ClientRectangle.GetHeight()))
    {
        SetMswLogoCompatibleFont(this);
    }

private:

    DECLARE_NO_COPY_CLASS(CLogoListBox);
};

#ifdef FMSLOGO_OWL

class TMxComboBox : public TComboBox
{
public:
    TMxComboBox(
        TWindow                * Parent, 
        const CClientRectangle & ClientRect
        ) : 
        TComboBox(
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
        const CClientRectangle & ClientRect
        ) : 
        TStatic(
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

#endif

class CLogoButton : public wxButton
{
public:

    CLogoButton(
        wxWindow               * Parent,
        const wxString         & Caption,
        const CClientRectangle & ClientRectangle,
        const char             * Callback
        ) : wxButton(
            Parent,
            wxID_ANY,
            Caption,
            wxPoint(ClientRectangle.GetX(), ClientRectangle.GetY()),
            wxSize(ClientRectangle.GetWidth(), ClientRectangle.GetHeight()))
    {
        strcpy(m_Callback, Callback);
        SetMswLogoCompatibleFont(this);
    }

private:
    // Event handlers
    void OnClick(wxCommandEvent& Event);

    // private member variables
    char m_Callback[MAX_BUFFER_SIZE];

    DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CLogoButton);
};

BEGIN_EVENT_TABLE(CLogoButton, wxButton)
    EVT_BUTTON(wxID_ANY, CLogoButton::OnClick)
END_EVENT_TABLE()

// if the button gets clicked we end up here and queue the event 
void CLogoButton::OnClick(wxCommandEvent& Event)
{
    callthing *callevent = callthing::CreateFunctionEvent(m_Callback);
    calllists.insert(callevent);
    checkqueue();
}

#if 0 // TODO

class TMyScrollBar : public TScrollBar
{
public:
    char callback[MAX_BUFFER_SIZE];

    TMyScrollBar(
        TWindow                * Parent, 
        const CClientRectangle & ClientRect,
        bool                     IsHScrollBar
        ) : 
        TScrollBar(
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
        const CClientRectangle & ClientRect
        ) : 
        TGroupBox(
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
        const CClientRectangle & ClientRect,
        TGroupBox              * Group
        ) : 
        TRadioButton(
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
        const CClientRectangle & ClientRect,
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

#endif


// class structure for storing information about user windows.
// The implementation is an in-place circular doubly-linked list.
class CLogoWidget
{
    friend class CLogoWidgetList;

private:
    class CLogoWidget * m_Next;
    class CLogoWidget * m_Prev;

public:
    char   m_Key[MAX_BUFFER_SIZE];
    char * m_Parent;

    WINDOWTYPE m_Type;

    union
    {
        class CLogoDialog    * Dialog;
        //class TMyStatic      * TSmybox;
        class CLogoListBox     * ListBox;
        //class TMxComboBox    * TCmybox;
        class CLogoButton    * Button;
        //class TMyScrollBar   * TSCmybox;
        //class TMyGroupBox    * TGmybox;
        //class TMyRadioButton * TRmybox;
        //class TMyCheckBox    * TCBmybox;
    };

   CLogoWidget(WINDOWTYPE Type, const char * Name)
       : m_Next(NULL),
         m_Prev(NULL),
         m_Parent(NULL),
         m_Type(Type),
         Dialog(NULL)
    {
        strcpy(m_Key, Name);
    }

    wxWindow * GetWindow() const;
    bool       IsRootWindow() const;
};

wxWindow * CLogoWidget::GetWindow() const
{
    switch (m_Type)
    {
    case WINDOWTYPE_Window:
    case WINDOWTYPE_Dialog:
        return Dialog;

    //case WINDOWTYPE_Static:      return TSmybox;

    case WINDOWTYPE_ListBox:
        return ListBox;

    //case WINDOWTYPE_ComboBox:    return TCmybox;

    case WINDOWTYPE_Button:
        return Button;

    //case WINDOWTYPE_ScrollBar:   return TSCmybox;
    //case WINDOWTYPE_GroupBox:    return TGmybox;
    //case WINDOWTYPE_RadioButton: return TRmybox;
    //case WINDOWTYPE_CheckBox:    return TCBmybox;

    case WINDOWTYPE_None:
        assert(!"can't happen");
        return NULL;
    }

    assert(!"can't happen");
    return NULL;
}

bool CLogoWidget::IsRootWindow() const
{
    if (m_Parent == NULL)
    {
        // This is a top-level WINDOW or DIALOG.
        return true;
    }

    if (m_Parent == (char *)CFmsLogo::GetMainFrame()->GetScreen())
    {
        // This is a widget that was placed on the screen window
        return true;
    }

    return false;
}

// TODO: Use std::list instead
class CLogoWidgetList
{
    CLogoWidget * last;

public:
    void insert(CLogoWidget * a);
    CLogoWidget * get(const char *k);
    CLogoWidget * get(const char *k, WINDOWTYPE type);
    CLogoWidget * get(const char *k, WINDOWTYPE type1, WINDOWTYPE type2);
    const char *getrootkey();
    const char *getfirstchild(const char *par);
    void zap(const char *k);
    void list(const char *k, int lev);
    void listall();
    void clear();
    bool OnScreenControlsExist();

    CLogoWidgetList()
    {
        last = NULL;
    }

    ~CLogoWidgetList()
    {
        clear();
    }

};


// inserts an element into the list.
void CLogoWidgetList::insert(CLogoWidget * NewNode)
{
    if (last != NULL)
    {
        // The list was not empty.
        // Insert the new node just after "last".
        NewNode->m_Next = last->m_Next;
        NewNode->m_Prev = last;

        last->m_Next->m_Prev = NewNode;
        last->m_Next         = NewNode;

        last = NewNode;
    }
    else
    {
        // The list was empty.
        // Make the newnode the "last" node.
        last = NewNode;
        last->m_Next = last;
        last->m_Prev = last;
    }
}

// returns the element whose key is "key"
CLogoWidget * CLogoWidgetList::get(const char *Key)
{
    if (last == NULL) 
    {
        return NULL;
    }

    CLogoWidget * f = last;

    do
    {
        if (strcmp(f->m_Key, Key) == 0)
        {
            return f;
        }
        f = f->m_Next;
    } while (f != last);

    return NULL;
}

// returns the element whose key is k and whose type is t
CLogoWidget * CLogoWidgetList::get(const char *Key, WINDOWTYPE Type)
{
    CLogoWidget * item = get(Key);
    if (item != NULL)
    {
        // the window exists
        if (item->m_Type == Type) 
        {
            // the window has the correct type
            return item;
        }
    }

    return NULL;
}

// returns the element whose key is "Key" and whose type is either Type1 or Type2
CLogoWidget * CLogoWidgetList::get(const char *Key, WINDOWTYPE Type1, WINDOWTYPE Type2)
{
    CLogoWidget * item = get(Key);
    if (item != NULL)
    {
        // the window exists
        if (item->m_Type == Type1 || item->m_Type == Type2) 
        {
            // the window exists and has the correct type
            return item;
        }
    }

    return NULL;
}

// returns the key of the first link whose parent is "Key"
// In the words, returns the first child of "Key"
const char *CLogoWidgetList::getfirstchild(const char * Key)
{
    if (last == NULL) 
    {
        return NULL;
    }

    CLogoWidget * f = last;

    do
    {
        if (f->m_Parent != NULL &&
            strcmp(f->m_Parent, Key) == 0)
        {
            return f->m_Key;
        }
        f = f->m_Next;
    } while (f != last);

    return NULL;
}

// deletes the link whose key is "Key" and any children of that link.
void CLogoWidgetList::zap(const char * Key)
{

    if (last == NULL) 
    {
        return;
    }

    // find the link whose key is "Key"
    CLogoWidget * p = get(Key);

    // delete any children first
    const char *t;
    while ((t = getfirstchild(Key)) != NULL)
    {
        zap(t);
    }

    // remove the link from the list
    if (p != NULL)
    {
        CLogoWidget * f = p->m_Next;

        if (f == p)
        {
            // this was the only element in the list
            last = NULL;
        }
        else
        {
            if (p == last) 
            {
                last = p->m_Prev;
            }

            p->m_Prev->m_Next = p->m_Next;
            f->m_Prev         = p->m_Prev;
        }

        delete p;
    }
}

// prints the heirarchy of all children of the node whose key is "k".
void CLogoWidgetList::list(const char *k, int level)
{
    CLogoWidget * p = get(k);
    if (p != NULL)
    {
        static const char *WindowName[] =
        {
            "?",
            LOCALIZED_WINDOWCLASSNAME_WINDOW,
            LOCALIZED_WINDOWCLASSNAME_STATIC,
            LOCALIZED_WINDOWCLASSNAME_LISTBOX,
            LOCALIZED_WINDOWCLASSNAME_COMBOBOX,
            LOCALIZED_WINDOWCLASSNAME_BUTTON,
            LOCALIZED_WINDOWCLASSNAME_SCROLLBAR,
            LOCALIZED_WINDOWCLASSNAME_GROUPBOX,
            LOCALIZED_WINDOWCLASSNAME_RADIOBUTTON,
            LOCALIZED_WINDOWCLASSNAME_CHECKBOX,
            LOCALIZED_WINDOWCLASSNAME_DIALOG,
        };

        if (level == 0)
        {
            const wxString & temp = wxString::Format(
                "%s %s",
                WindowName[(int)p->m_Type],
                p->m_Key);
            putcombobox(temp);
        }

        CLogoWidget *ff = last;
        do
        {
            if (ff->m_Parent != NULL &&
                strcmp(ff->m_Parent, k) == 0)
            {
                const wxString & temp = wxString::Format(
                    "  %*s%s %s",
                    level,
                    "",
                    WindowName[(int)ff->m_Type],
                    ff->m_Key);

                putcombobox(temp);
                list(ff->m_Key, level + 1);
            }
            ff = ff->m_Next;
        } while (ff != last);
    }
}

// deletes all elements in the list
void CLogoWidgetList::clear()
{
    CLogoWidget *l = last;

    if (l == NULL) 
    {
        return;
    }

    do
    {
        CLogoWidget *ll = l;
        l = l->m_Next;
        // REVISIT: is it okay to destroy every window, or does
        // this destroy some windows (like children windows) twice.
        ll->GetWindow()->Destroy();
        delete ll;
    } while (l != last);

    last = NULL;
}

// returns the key of the first element whose parent is the root window.
// returns NULL, if no element's parent is the root window.
const char *CLogoWidgetList::getrootkey()
{
    CLogoWidget *l = last;

    if (l == NULL) 
    {
        return NULL;
    }

    do
    {
        if (l->IsRootWindow())
        {
            return l->m_Key;
        }
        l = l->m_Next;
    } while (l != last);

    return NULL;
}

// prints the heirarchy of all windows starting at the screen window
void CLogoWidgetList::listall()
{
    CLogoWidget *l = last;

    if (l == NULL) 
    {
        return;
    }

    do
    {
        if (l->IsRootWindow())
        {
            list(l->m_Key, 0);
        }
        l = l->m_Next;
    } while (l != last);
}

bool CLogoWidgetList::OnScreenControlsExist()
{
    CLogoWidget *l = last;

    if (l == NULL) 
    {
        return false;
    }

    do
    {
        // Check if the control is on the screen window
        if (l->m_Parent == (char *)CFmsLogo::GetMainFrame()->GetScreen())
        {
            return true;
        }
        l = l->m_Next;
    } while (l != last);

    return false;
}

CLogoWidgetList g_LogoWidgets;


/* User function to create a modeless window */

NODE *lwindowcreate(NODE *args)
{
    NODE * nextArg = args;

    // get all the args
    char parentname[MAX_BUFFER_SIZE];
    cnv_strnode_string(parentname, nextArg);
    nextArg = cdr(nextArg);

    char childname[MAX_BUFFER_SIZE];
    cnv_strnode_string(childname, nextArg);
    nextArg = cdr(nextArg);

    char titlename[MAX_BUFFER_SIZE];
    cnv_strnode_string(titlename, nextArg);
    nextArg = cdr(nextArg);

    CClientRectangle clientrect;
    clientrect.InitializeFromInput(nextArg);

    char callback[MAX_BUFFER_SIZE];
    if (nextArg != NIL) 
    {
        cnv_strnode_string(callback, nextArg);
    }
    else 
    {
        callback[0] = '\0';
    }


    if (stopping_flag == THROWING)
    {
        return Unbound;
    }


    if (g_LogoWidgets.get(childname) != NULL)
    {
        // it's an error if this already exists
        err_logo(WINDOW_ALREADY_EXISTS, cadr(args));
        return Unbound;
    }

    // Convert the client rectangle to "DIALOG" units.
    // This is the key to making all Graphics Modes work correctly.
    clientrect.ConvertToDialogCoordinates();

    CLogoWidget *child = new CLogoWidget(WINDOWTYPE_Window, childname);

    // if parent exists use it, else use desktop
    CLogoWidget *parent = g_LogoWidgets.get(parentname, WINDOWTYPE_Window);
    wxWindow * wxParent;
    if (parent != NULL)
    {
        wxParent = parent->Dialog;
    }
    else
    {
        // The parent doesn't exist.  Use the desktop as the parent.
        // REVISIT: The OWL implementation uses the screen window as the parent.
        // This might be okay in wxWidgets as long as SetExtraStyle(wxWS_EX_BLOCK_EVENTS)
        // is called to block suprious events from being sent to the main window.
        // This would make eliminate the need to call uninitilaize_windows() from
        // CMainFrame::OnClose and would keep the wxWidgets implementation closer to
        // the OWL implementation.
        wxParent = NULL;
    }

    child->Dialog = new CLogoDialog(
        wxParent,
        titlename,
        clientrect);
    child->m_Parent = (char*) wxParent;

    g_LogoWidgets.insert(child);

    // Modeless windows have a callback to set them up due to
    // legacy with the Borland OWL implementation of MSWLogo.
    do_execution(callback);

    child->Dialog->Show();

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

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    CLogoWidget *window = g_LogoWidgets.get(childname, WindowType);
    if (window == NULL)
    {
        err_logo(WINDOW_DOES_NOT_EXIST, car(args));
        return Unbound;
    }

    window->GetWindow()->Enable(bEnable);
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
    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    CLogoWidget *window = g_LogoWidgets.get(windowkey, WindowType);
    if (window == NULL)
    {
        // The window does not exist.  Throw an error.
        err_logo(WINDOW_DOES_NOT_EXIST, car(args));
        return Unbound;
    }

    // The window exists.  Close it.
    window->GetWindow()->Destroy();

    g_LogoWidgets.zap(windowkey);

    UpdateZoomControlFlag();
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
        CLogoWidget *window = g_LogoWidgets.get(windowname, WINDOWTYPE_Window);
        if (window != NULL)
        {
            // The exact name and type exists matches.
            // kill this window and all of its children.
            window->Dialog->Destroy();
            g_LogoWidgets.zap(windowname);
        }
        else
        {
            // No window exists that matches this name and type.
            // Close all windows.
            const char *tempkey;
            while ((tempkey = g_LogoWidgets.getrootkey()))
            {
                CLogoWidget *temp = g_LogoWidgets.get(tempkey);
                if (temp != NULL)
                {
                    temp->GetWindow()->Destroy();
                    g_LogoWidgets.zap(tempkey);
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
    NODE * nextArg = args;

    // get args
    char parentname[MAX_BUFFER_SIZE];
    cnv_strnode_string(parentname, nextArg);
    nextArg = cdr(nextArg);

    char childname[MAX_BUFFER_SIZE];
    cnv_strnode_string(childname, nextArg);
    nextArg = cdr(nextArg);

    char titlename[MAX_BUFFER_SIZE];
    cnv_strnode_string(titlename, nextArg);
    nextArg = cdr(nextArg);

    CClientRectangle clientrect;
    clientrect.InitializeFromInput(nextArg);

    char callback[MAX_BUFFER_SIZE];
    if (nextArg != NIL) 
    {
        cnv_strnode_string(callback, nextArg);
    }
    else 
    {
        callback[0] = '\0';
    }

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    // if it does not exist continue
    if (g_LogoWidgets.get(childname) != NULL)
    {
        err_logo(WINDOW_ALREADY_EXISTS, cadr(args));
        return Unbound;
    }

    // convert to "DIALOG" units. 
    // This is the key to getting consistent results in all graphics MODEs.
    clientrect.ConvertToDialogCoordinates();

    // make one
    CLogoWidget * child = new CLogoWidget(WINDOWTYPE_Dialog, childname);

    // if parent of correct type exists use it
    CLogoWidget *parent = g_LogoWidgets.get(parentname, WINDOWTYPE_Window);
    wxWindow * wxParent;
    if (parent != NULL)
    {
        wxParent = parent->Dialog;
    }
    else
    {
        // The parent does not exist.  Use the desktop as the parent.
        wxParent = NULL;
    }

    child->Dialog = new CLogoDialog(
        wxParent,
        titlename,
        clientrect);
    child->m_Parent = (char *)wxParent;

    g_LogoWidgets.insert(child);

    // Modal windows must have a callback to set them up
    // since it will not return until closed.
    do_execution(callback);

    child->Dialog->ShowModal();
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
    NODE * nextArg = args;

    char parentname[MAX_BUFFER_SIZE];
    cnv_strnode_string(parentname, nextArg);
    nextArg = cdr(nextArg);

    char childname[MAX_BUFFER_SIZE];
    cnv_strnode_string(childname, nextArg);
    nextArg = cdr(nextArg);

    CClientRectangle clientrect;
    clientrect.InitializeFromInput(nextArg);

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    if (g_LogoWidgets.get(childname) != NULL)
    {
        err_logo(WINDOW_ALREADY_EXISTS, cadr(args));
        return Unbound;
    }
    
    CLogoWidget * child = new CLogoWidget(WINDOWTYPE_ListBox, childname);

    CLogoWidget *parent = g_LogoWidgets.get(parentname, WINDOWTYPE_Window, WINDOWTYPE_Dialog);
    if (parent != NULL)
    {
        // The parent is a user-created window
        clientrect.ConvertToDialogCoordinates();
            
        child->m_Parent = parent->m_Key;

        child->ListBox = new CLogoListBox(
            parent->Dialog,
            clientrect);
    }
    else
    {
        // else the parent does not exist -- put the control on the screen
        clientrect.ConvertToScreenCoordinates();

        child->m_Parent = (char *)CFmsLogo::GetMainFrame()->GetScreen();

        child->ListBox = new CLogoListBox(
            CFmsLogo::GetMainFrame()->GetScreen(),
            clientrect);
    }

    g_LogoWidgets.insert(child);

    if (parent == NULL)
    {
        UpdateZoomControlFlag();
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
    char listboxname[MAX_BUFFER_SIZE];
    cnv_strnode_string(listboxname, args);
    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    CLogoWidget * listbox = g_LogoWidgets.get(listboxname, WINDOWTYPE_ListBox);
    if (listbox == NULL)
    {
        // the listbox does not exist
        err_logo(WINDOW_DOES_NOT_EXIST, car(args));
        return Unbound;
    }

    // Fetch the selected string from the listbox
    const wxString & selection = listbox->ListBox->GetStringSelection();

    // Parsing the string turns it into a list for us
    return parser(make_strnode(selection.c_str()), false);
}

NODE *llistboxaddstring(NODE *args)
{
    // get args
    char listboxname[MAX_BUFFER_SIZE];
    cnv_strnode_string(listboxname, args);

    char stringname[MAX_BUFFER_SIZE];
    cnv_strnode_string(stringname, cdr(args));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    CLogoWidget *listbox = g_LogoWidgets.get(listboxname, WINDOWTYPE_ListBox);
    if (listbox == NULL)
    {
        // the list box does not exist.
        err_logo(WINDOW_DOES_NOT_EXIST, car(args));
        return Unbound;
    }

    // add entry and reset Index for consistency
    listbox->ListBox->Append(stringname);
    listbox->ListBox->SetSelection(0);
    return Unbound;
}

NODE *llistboxdeletestring(NODE *args)
{
    // get args
    char listboxname[MAX_BUFFER_SIZE];
    cnv_strnode_string(listboxname, args);
   
    int index = getint(nonnegative_int_arg(cdr(args)));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    // if exists continue
    CLogoWidget *listbox = g_LogoWidgets.get(listboxname, WINDOWTYPE_ListBox);
    if (listbox == NULL)
    {
        // the list box does not exist.
        err_logo(WINDOW_DOES_NOT_EXIST, car(args));
        return Unbound;
    }

    // kill entry based on index
    listbox->ListBox->Delete(index);
    listbox->ListBox->SetSelection(0);
    return Unbound;
}

#if 0 // TODO: implement the rest of the controls

NODE *lcomboboxcreate(NODE *args)
{
    // get args
    NODE * nextArg = args;

    char parentname[MAX_BUFFER_SIZE];
    cnv_strnode_string(parentname, nextArg);
    nextArg = cdr(nextArg);

    char childname[MAX_BUFFER_SIZE];
    cnv_strnode_string(childname, nextArg);
    nextArg = cdr(nextArg);

    CClientRectangle clientrect;
    clientrect.InitializeFromInput(nextArg);

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    // if unique continue
    if (g_LogoWidgets.get(childname) != NULL)
    {
        err_logo(WINDOW_ALREADY_EXISTS, cadr(args));
        return Unbound;
    }

    CLogoWidget * child = new CLogoWidget(WINDOWTYPE_ComboBox, childname);

    CLogoWidget *parent = g_LogoWidgets.get(parentname, WINDOWTYPE_Window, WINDOWTYPE_Dialog);
    if (parent != NULL)
    {
        // convert to "DIALOG" units
        clientrect.ConvertToDialogCoordinates();

        child->m_Parent = parent->m_Key;

        child->TCmybox = new TMxComboBox(parent->Dialog, clientrect);
    }
    else
    {
        // else the parent does not exist -- put the control on the screen
        clientrect.ConvertToScreenCoordinates();

        child->m_Parent = (char *) CFmsLogo::GetMainFrame()->GetScreen();

        child->TCmybox = new TMxComboBox(
            CFmsLogo::GetMainFrame()->GetScreen(),
            clientrect);
    }

    child->TCmybox->Create();

    MyMessageScan();

    g_LogoWidgets.insert(child);

    if (parent == NULL)
    {
        UpdateZoomControlFlag();
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
    char comboboxname[MAX_BUFFER_SIZE];
    cnv_strnode_string(comboboxname, args);

    // get the combobox
    CLogoWidget *combobox = g_LogoWidgets.get(comboboxname, WINDOWTYPE_ComboBox);
    if (combobox == NULL)
    {
        // the combobox does not exist
        err_logo(WINDOW_DOES_NOT_EXIST, car(args));
        return Unbound;
    }

    // Get the text from the combobox
    char stringname[MAX_BUFFER_SIZE];
    if (combobox->TCmybox->GetText(stringname, MAX_BUFFER_SIZE) < 0)
    {
        // there was an error
        return NIL;
    }

    // parsing it turns it into a list
    return parser(make_strnode(stringname), false);
}

NODE *lcomboboxsettext(NODE *args)
{
    // get args
    char comboboxname[MAX_BUFFER_SIZE];
    cnv_strnode_string(comboboxname, args);

    char stringname[MAX_BUFFER_SIZE];
    cnv_strnode_string(stringname, cdr(args));

    // if exists continue
    CLogoWidget *combobox = g_LogoWidgets.get(comboboxname, WINDOWTYPE_ComboBox);
    if (combobox == NULL)
    {
        err_logo(WINDOW_DOES_NOT_EXIST, car(args));
        return Unbound;
    }

    // set the editcontrol portion to the user specified text
    combobox->TCmybox->SetText(stringname);
    return Unbound;
}

NODE *lcomboboxaddstring(NODE *args)
{
    // get args
    char comboboxname[MAX_BUFFER_SIZE];
    cnv_strnode_string(comboboxname, args);

    char stringname[MAX_BUFFER_SIZE];
    cnv_strnode_string(stringname, cdr(args));

    // get the combobox
    CLogoWidget *combobox = g_LogoWidgets.get(comboboxname, WINDOWTYPE_ComboBox);
    if (combobox == NULL)
    {
        // the combobox does not exist
        err_logo(WINDOW_DOES_NOT_EXIST, car(args));
        return Unbound;
    }

    // add string and reset selection
    combobox->TCmybox->AddString(stringname);
    combobox->TCmybox->SetSelIndex(0);
    return Unbound;
}

NODE *lcomboboxdeletestring(NODE *args)
{
    // get args
    char comboboxname[MAX_BUFFER_SIZE];
    cnv_strnode_string(comboboxname, args);

    int index = getint(nonnegative_int_arg(cdr(args)));

    // get the combobox
    CLogoWidget *combobox = g_LogoWidgets.get(comboboxname, WINDOWTYPE_ComboBox);
    if (combobox == NULL)
    {
        err_logo(WINDOW_DOES_NOT_EXIST, car(args));
        return Unbound;
    }

    // kill entry and reset index
    combobox->TCmybox->DeleteString(index);
    combobox->TCmybox->SetSelIndex(0);
    return Unbound;
}

NODE *lscrollbarcreate(NODE *args)
{
    NODE * nextArg = args;

    char parentname[MAX_BUFFER_SIZE];
    cnv_strnode_string(parentname, nextArg);
    nextArg = cdr(nextArg);

    char childname[MAX_BUFFER_SIZE];
    cnv_strnode_string(childname, nextArg);
    nextArg = cdr(nextArg);

    CClientRectangle clientrect;
    clientrect.InitializeFromInput(nextArg);

    char callback[MAX_BUFFER_SIZE];
    cnv_strnode_string(callback, nextArg);

    if (stopping_flag == THROWING)
    {
        // an error occured
        return Unbound;
    }

    if (g_LogoWidgets.get(childname) != NULL)
    {
        err_logo(WINDOW_ALREADY_EXISTS, cadr(args));
        return Unbound;
    }

    CLogoWidget * child = new CLogoWidget(WINDOWTYPE_ScrollBar, childname);
         
    const bool isHorizontalScrollbar = clientrect.GetWidth() > clientrect.GetHeight();

    CLogoWidget *parent = g_LogoWidgets.get(parentname, WINDOWTYPE_Window, WINDOWTYPE_Dialog);
    if (parent != NULL)
    {
        clientrect.ConvertToDialogCoordinates();

        child->m_Parent = parent->m_Key;

        child->TSCmybox = new TMyScrollBar(
            parent->Dialog, 
            clientrect,
            isHorizontalScrollbar);
    }
    else
    {
        clientrect.ConvertToScreenCoordinates();

        child->m_Parent = (char*) CFmsLogo::GetMainFrame()->GetScreen();

        child->TSCmybox = new TMyScrollBar(
            CFmsLogo::GetMainFrame()->GetScreen(),
            clientrect,
            isHorizontalScrollbar);
    }

    strcpy(child->TSCmybox->callback, callback);

    child->TSCmybox->Create();

    MyMessageScan();

    g_LogoWidgets.insert(child);

    if (parent == NULL)
    {
        UpdateZoomControlFlag();
    }

    return Unbound;
}

NODE *lscrollbarset(NODE *args)
{
    NODE * nextArg = args;

    char scrollbarname[MAX_BUFFER_SIZE];
    cnv_strnode_string(scrollbarname, nextArg);
    nextArg = cdr(nextArg);

    int lo = int_arg(nextArg);
    nextArg = cdr(nextArg);

    int hi = int_arg(nextArg);
    if (hi < lo)
    {
        // the low value must be less than the high value
        NODE * node = err_logo(BAD_DATA, car(nextArg));
        gcref(node);
    }
    nextArg = cdr(nextArg);

    int pos = int_arg(nextArg);

    if (stopping_flag == THROWING)
    {
        // an error occured
        return Unbound;
    }

    CLogoWidget *scrollbar = g_LogoWidgets.get(scrollbarname, WINDOWTYPE_ScrollBar);
    if (scrollbar == NULL)
    {
        err_logo(WINDOW_DOES_NOT_EXIST, car(args));
        return Unbound;
    }

    scrollbar->TSCmybox->Set(lo, hi, pos);
    return Unbound;
}

NODE *lscrollbarget(NODE *args)
{
    char scrollbarname[MAX_BUFFER_SIZE];
    cnv_strnode_string(scrollbarname, args);

    if (stopping_flag == THROWING)
    {
        // an error occured
        return Unbound;
    }

    CLogoWidget *scrollbar = g_LogoWidgets.get(scrollbarname, WINDOWTYPE_ScrollBar);
    if (scrollbar == NULL)
    {
        // the scrollbar doesn't exist
        err_logo(WINDOW_DOES_NOT_EXIST, car(args));
        return Unbound;
    }

    int pos = scrollbar->TSCmybox->Get();
    return make_intnode(pos);
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
    NODE * nextArg = args;

    char parentname[MAX_BUFFER_SIZE];
    cnv_strnode_string(parentname, nextArg);
    nextArg = cdr(nextArg);

    char childname[MAX_BUFFER_SIZE];
    cnv_strnode_string(childname, nextArg);
    nextArg = cdr(nextArg);

    char titlename[MAX_BUFFER_SIZE];
    cnv_strnode_string(titlename, nextArg);
    nextArg = cdr(nextArg);

    CClientRectangle clientrect;
    clientrect.InitializeFromInput(nextArg);

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    if (g_LogoWidgets.get(childname) != NULL)
    {
        err_logo(WINDOW_ALREADY_EXISTS, cadr(args));
        return Unbound;
    }

    CLogoWidget * child = new CLogoWidget(WINDOWTYPE_Static, childname);

    CLogoWidget *parent = g_LogoWidgets.get(
        parentname, 
        WINDOWTYPE_Window, 
        WINDOWTYPE_Dialog);
    if (parent != NULL)
    {
        clientrect.ConvertToDialogCoordinates();

        child->m_Parent = parent->m_Key;

        child->TSmybox = new TMyStatic(
            parent->Dialog, 
            titlename, 
            clientrect);
    }
    else
    {
        clientrect.ConvertToScreenCoordinates();

        child->m_Parent = (char *) CFmsLogo::GetMainFrame()->GetScreen();
            
        child->TSmybox = new TMyStatic(
            CFmsLogo::GetMainFrame()->GetScreen(),
            titlename,
            clientrect);
    }

    child->TSmybox->Create();

    MyMessageScan();

    g_LogoWidgets.insert(child);

    if (parent == NULL)
    {
        UpdateZoomControlFlag();
    }
   
    return Unbound;
}

NODE *lstaticupdate(NODE *args)
{
    char childname[MAX_BUFFER_SIZE];
    cnv_strnode_string(childname, args);

    char titlename[MAX_BUFFER_SIZE];
    cnv_strnode_string(titlename, cdr(args));

    CLogoWidget *temp = g_LogoWidgets.get(childname, WINDOWTYPE_Static);
    if (temp == NULL)
    {
        err_logo(WINDOW_DOES_NOT_EXIST, car(args));
        return Unbound;
    }

    temp->TSmybox->SetText(titlename);
    return Unbound;
}

NODE *lstaticdelete(NODE *args)
{
    return WindowDeleteHelper(args, WINDOWTYPE_Static);
}

#endif

NODE *lbuttoncreate(NODE *args)
{
    NODE * nextArg = args;

    char parentname[MAX_BUFFER_SIZE];
    cnv_strnode_string(parentname, nextArg);
    nextArg = cdr(nextArg);

    char childname[MAX_BUFFER_SIZE];
    cnv_strnode_string(childname, nextArg);
    nextArg = cdr(nextArg);

    char titlename[MAX_BUFFER_SIZE];
    cnv_strnode_string(titlename, nextArg);
    nextArg = cdr(nextArg);

    CClientRectangle clientrect;
    clientrect.InitializeFromInput(nextArg);

    char callback[MAX_BUFFER_SIZE];
    if (nextArg != NIL)
    {
        cnv_strnode_string(callback, nextArg);
    }
    else
    {
        callback[0] = '\0';
    }

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    if (g_LogoWidgets.get(childname) != NULL)
    {
        // the button already exists
        err_logo(WINDOW_ALREADY_EXISTS, cadr(args));
        return Unbound;
    }

    CLogoWidget * child = new CLogoWidget(WINDOWTYPE_Button, childname);

    CLogoWidget *parent = g_LogoWidgets.get(
        parentname,
        WINDOWTYPE_Window,
        WINDOWTYPE_Dialog);

    if (parent != NULL)
    {
        clientrect.ConvertToDialogCoordinates();

        child->m_Parent = parent->m_Key;

        child->Button = new CLogoButton(
            parent->Dialog,
            titlename,
            clientrect,
            callback);
    }
    else
    {
        clientrect.ConvertToScreenCoordinates();

        child->m_Parent = (char *) CFmsLogo::GetMainFrame()->GetScreen();

        child->Button = new CLogoButton(
            CFmsLogo::GetMainFrame()->GetScreen(),
            titlename,
            clientrect,
            callback);
    }

    g_LogoWidgets.insert(child);

    if (parent == NULL)
    {
        UpdateZoomControlFlag();
    }
      
    return Unbound;
}

NODE *lbuttonupdate(NODE *args)
{
    char buttonname[MAX_BUFFER_SIZE];
    cnv_strnode_string(buttonname, args);

    char titlename[MAX_BUFFER_SIZE];
    cnv_strnode_string(titlename, cdr(args));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    CLogoWidget *button = g_LogoWidgets.get(buttonname, WINDOWTYPE_Button);
    if (button == NULL)
    {
        err_logo(WINDOW_DOES_NOT_EXIST, car(args));
        return Unbound;
    }

    button->Button->SetLabel(titlename);
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

#if 0

NODE *lgroupboxcreate(NODE *args)
{
    NODE * nextArg = args;

    char parentname[MAX_BUFFER_SIZE];
    cnv_strnode_string(parentname, nextArg);
    nextArg = cdr(nextArg);

    char childname[MAX_BUFFER_SIZE];
    cnv_strnode_string(childname, nextArg);
    nextArg = cdr(nextArg);

    CClientRectangle clientrect;
    clientrect.InitializeFromInput(nextArg);

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    if (g_LogoWidgets.get(childname) != NULL)
    {
        err_logo(WINDOW_ALREADY_EXISTS, cadr(args));
        return Unbound;
    }

    CLogoWidget * child = new CLogoWidget(WINDOWTYPE_GroupBox, childname);

    CLogoWidget *parent = g_LogoWidgets.get(
        parentname, 
        WINDOWTYPE_Window, 
        WINDOWTYPE_Dialog);
    if (parent != NULL)
    {
        clientrect.ConvertToDialogCoordinates();

        child->m_Parent = parent->m_Key;

        child->TGmybox = new TMyGroupBox(
            parent->Dialog, 
            clientrect);
    }
    else
    {
        clientrect.ConvertToScreenCoordinates();

        child->m_Parent = (char *) CFmsLogo::GetMainFrame()->GetScreen();
            
        child->TGmybox = new TMyGroupBox(
            CFmsLogo::GetMainFrame()->GetScreen(), 
            clientrect);
    }

    child->TGmybox->Create();

    MyMessageScan();

    g_LogoWidgets.insert(child);

    if (parent == NULL)
    {
        UpdateZoomControlFlag();
    }

    return Unbound;
}

NODE *lgroupboxdelete(NODE *args)
{
    return WindowDeleteHelper(args, WINDOWTYPE_GroupBox);
}

NODE *lradiobuttoncreate(NODE *args)
{
    NODE * nextArg = args;

    char parentname[MAX_BUFFER_SIZE];
    cnv_strnode_string(parentname, nextArg);
    nextArg = cdr(nextArg);

    char groupname[MAX_BUFFER_SIZE];
    cnv_strnode_string(groupname, nextArg);
    nextArg = cdr(nextArg);

    char childname[MAX_BUFFER_SIZE];
    cnv_strnode_string(childname, nextArg);
    nextArg = cdr(nextArg);

    char titlename[MAX_BUFFER_SIZE];
    cnv_strnode_string(titlename, nextArg);
    nextArg = cdr(nextArg);

    CClientRectangle clientrect;
    clientrect.InitializeFromInput(nextArg);

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    CLogoWidget *group = g_LogoWidgets.get(groupname, WINDOWTYPE_GroupBox);
    if (group == NULL)
    {
        // the group does not exist
        err_logo(WINDOW_DOES_NOT_EXIST, cadr(args));
        return Unbound;
    }

    if (g_LogoWidgets.get(childname) != NULL)
    {
        // a radio button by this name already exists
        err_logo(WINDOW_ALREADY_EXISTS, car(cdr(cdr(args))));
        return Unbound;
    }
     
    CLogoWidget * child = new CLogoWidget(WINDOWTYPE_RadioButton, childname);

    CLogoWidget *parent = g_LogoWidgets.get(
        parentname, 
        WINDOWTYPE_Window, 
        WINDOWTYPE_Dialog);
    if (parent != NULL)
    {
        clientrect.ConvertToDialogCoordinates();

        child->m_Parent = parent->m_Key;

        child->TRmybox = new TMyRadioButton(
            parent->Dialog, 
            titlename, 
            clientrect,
            group->TGmybox);
    }
    else
    {
        clientrect.ConvertToScreenCoordinates();

        child->m_Parent = (char *) CFmsLogo::GetMainFrame()->GetScreen();

        child->TRmybox = new TMyRadioButton(
            CFmsLogo::GetMainFrame()->GetScreen(),
            titlename,
            clientrect,
            group->TGmybox);
    }

    child->TRmybox->Create();

    MyMessageScan();

    g_LogoWidgets.insert(child);

    if (parent == NULL)
    {
        UpdateZoomControlFlag();
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
    char radiobuttonname[MAX_BUFFER_SIZE];
    cnv_strnode_string(radiobuttonname, args);

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    CLogoWidget *radiobutton = g_LogoWidgets.get(radiobuttonname, WINDOWTYPE_RadioButton);
    if (radiobutton == NULL)
    {
        // the radio button does not exist
        err_logo(WINDOW_DOES_NOT_EXIST, car(args));
        return Unbound;
    }

    uint check = radiobutton->TRmybox->GetCheck();
    return true_or_false(BF_CHECKED == check);
}

NODE *lradiobuttonset(NODE *args)
{
    char radiobuttonname[MAX_BUFFER_SIZE];
    cnv_strnode_string(radiobuttonname, args);

    bool pos = boolean_arg(cdr(args));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    CLogoWidget *radiobutton = g_LogoWidgets.get(radiobuttonname, WINDOWTYPE_RadioButton);
    if (radiobutton == NULL)
    {
        // the radio button does not exist
        err_logo(WINDOW_DOES_NOT_EXIST, car(args));
        return Unbound;
    }

    if (pos)
    {
        radiobutton->TRmybox->Check();
    }
    else
    {
        radiobutton->TRmybox->Uncheck();
    }

    return Unbound;
}

NODE *lcheckboxcreate(NODE *args)
{
    NODE * nextArg = args;

    char parentname[MAX_BUFFER_SIZE];
    cnv_strnode_string(parentname, nextArg);
    nextArg = cdr(nextArg);

    char groupname[MAX_BUFFER_SIZE];
    cnv_strnode_string(groupname, nextArg);
    nextArg = cdr(nextArg);

    char childname[MAX_BUFFER_SIZE];
    cnv_strnode_string(childname, nextArg);
    nextArg = cdr(nextArg);

    char titlename[MAX_BUFFER_SIZE];
    cnv_strnode_string(titlename, nextArg);
    nextArg = cdr(nextArg);

    CClientRectangle clientrect;
    clientrect.InitializeFromInput(nextArg);

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    CLogoWidget *group = g_LogoWidgets.get(groupname, WINDOWTYPE_GroupBox);
    if (group == NULL)
    {
        // the group does not exist
        err_logo(WINDOW_DOES_NOT_EXIST, cadr(args));
        return Unbound;
    }

    if (g_LogoWidgets.get(childname) != NULL)
    {
        // the checkbox already exists
        err_logo(WINDOW_ALREADY_EXISTS, car(cdr(cdr(args))));
        return Unbound;
    }

    CLogoWidget * child = new CLogoWidget(WINDOWTYPE_CheckBox, childname);

    CLogoWidget * parent = g_LogoWidgets.get(
        parentname, 
        WINDOWTYPE_Window, 
        WINDOWTYPE_Dialog);
    if (parent != NULL)
    {
        clientrect.ConvertToDialogCoordinates();

        child->m_Parent = parent->m_Key;

        child->TCBmybox = new TMyCheckBox(
            parent->Dialog, 
            titlename, 
            clientrect,
            group->TGmybox);
    }
    else
    {
        clientrect.ConvertToScreenCoordinates();

        child->m_Parent = (char *) CFmsLogo::GetMainFrame()->GetScreen();

        child->TCBmybox = new TMyCheckBox(
            CFmsLogo::GetMainFrame()->GetScreen(),
            titlename,
            clientrect,
            group->TGmybox);
    }

    child->TCBmybox->Create();

    MyMessageScan();

    g_LogoWidgets.insert(child);

    if (parent == NULL)
    {
        UpdateZoomControlFlag();
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
    char checkboxname[MAX_BUFFER_SIZE];
    cnv_strnode_string(checkboxname, args);

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    CLogoWidget *checkbox = g_LogoWidgets.get(checkboxname, WINDOWTYPE_CheckBox);
    if (checkbox == NULL)
    {
        // the checkbox doesn't exist
        err_logo(WINDOW_DOES_NOT_EXIST, car(args));
        return Unbound;
    }

    uint check = checkbox->TCBmybox->GetCheck();
    return true_or_false(BF_CHECKED == check);
}

NODE *lcheckboxset(NODE *args)
{
    char checkboxname[MAX_BUFFER_SIZE];
    cnv_strnode_string(checkboxname, args);

    int pos = boolean_arg(cdr(args));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    CLogoWidget *checkbox = g_LogoWidgets.get(checkboxname, WINDOWTYPE_CheckBox);
    if (checkbox == NULL)
    {
        // the checkbox doesn't exist
        err_logo(WINDOW_DOES_NOT_EXIST, car(args));
        return Unbound;
    }

    if (pos)
    {
        checkbox->TCBmybox->Check();
    }
    else
    {
        checkbox->TCBmybox->Uncheck();
    }

    return Unbound;
}

#endif 

bool CheckOnScreenControls()
{
    return g_LogoWidgets.OnScreenControlsExist();
}

NODE *ldebugwindows(NODE *arg)
{
    if (arg != NIL)
    {
        char windowname[MAX_BUFFER_SIZE];
        cnv_strnode_string(windowname, arg);
      
        if (g_LogoWidgets.get(windowname) == NULL)
        {
            err_logo(WINDOW_DOES_NOT_EXIST, car(arg));
            return Unbound;
        }

        g_LogoWidgets.list(windowname, 0);
    }
    else
    {
        g_LogoWidgets.listall();
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
        if (::MessageBox(
                GetParentWindowForDialog(),
                body, 
                banner, 
                MB_OKCANCEL) == IDCANCEL)
        {
            err_logo(STOP_ERROR, NIL);
        }
    }

    return Unbound;
}

NODE *lquestionbox(NODE *args)
{
    // read/validate inputs
    char banner[MAX_BUFFER_SIZE];
    cnv_strnode_string(banner, args);

    char body[MAX_BUFFER_SIZE];
    cnv_strnode_string(body, cdr(args));

    if (stopping_flag == THROWING)
    {
        // bad input
        return Unbound;
    }

    const wxString & str = ::wxGetTextFromUser(
        body,
        banner,
        "",
        CFmsLogo::GetMainFrame());

    if (str.IsEmpty())
    {
        // BUG: This doesn't distinguish between when the user
        // selects the empty string and when the user presses
        // cancel.

        // The user pressed cancel.
        err_logo(STOP_ERROR, NIL);
        return Unbound;
    }

    NODE * targ = make_strnode(str.c_str());
    NODE * val = parser(targ, false);
    return val;
}


NODE *lselectbox(NODE *args)
{
    // read/validate inputs
    char banner[MAX_BUFFER_SIZE];
    cnv_strnode_string(banner, args);

    NODE * choicesNode = list_arg(cdr(args));
    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    wxArrayString choices;
    for (NODE * currentChoice = choicesNode;
         currentChoice != NIL;
         currentChoice = cdr(currentChoice))
    {
        char choice[MAX_BUFFER_SIZE];
        cnv_strnode_string(choice, currentChoice);

        choices.Add(choice);
    }

    // TODO: Implement our own version of this
    // routine that doesn't leave a blank space
    // where the question should be placed.
    int status = ::wxGetSingleChoiceIndex(
        "",
        banner,
        choices,
        CFmsLogo::GetMainFrame());
    if (status < 0)
    {
        // the user pressed cancel
        err_logo(STOP_ERROR, NIL);
        return Unbound;
    }

    return make_intnode(status + 1);
}

NODE *lyesnobox(NODE *args)
{
    char banner[MAX_BUFFER_SIZE];
    cnv_strnode_string(banner, args);

    char body[MAX_BUFFER_SIZE];
    cnv_strnode_string(body, args = cdr(args));

    if (NOT_THROWING)
    {
        int status = ::MessageBox(
            GetParentWindowForDialog(),
            body,
            banner,
            MB_YESNOCANCEL | MB_ICONQUESTION);

        switch (status)
        {
        case IDYES:
            return Truex.GetNode();

        case IDNO:
            return Falsex.GetNode();

        case IDCANCEL:
            err_logo(STOP_ERROR, NIL);
            return Falsex.GetNode();
        }
    }

    return Unbound;
}

NODE *ldialogfileopen(NODE *args)
{
    char filename[MAX_BUFFER_SIZE];
    cnv_strnode_string(filename, args);

    OPENFILENAME openFileName;
    ZeroMemory(&openFileName, sizeof openFileName);
    openFileName.lStructSize       = sizeof openFileName;
    openFileName.hwndOwner         = GetParentWindowForDialog();
    openFileName.hInstance         = NULL;
    openFileName.lpstrFilter       = LOCALIZED_FILEFILTER_ALLFILES;
    openFileName.lpstrCustomFilter = NULL;
    openFileName.nMaxCustFilter    = 0;
    openFileName.nFilterIndex      = 0;
    openFileName.lpstrFile         = filename;
    openFileName.nMaxFile          = ARRAYSIZE(filename);
    openFileName.lpstrFileTitle    = NULL;
    openFileName.nMaxFileTitle     = 0;
    openFileName.lpstrInitialDir   = NULL;
    openFileName.lpstrTitle        = NULL;
    openFileName.Flags             = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER;
    openFileName.nFileOffset       = 0;
    openFileName.nFileExtension    = 0;
    openFileName.lpstrDefExt       = NULL;
    openFileName.lCustData         = 0;
    openFileName.lpfnHook          = NULL;
    openFileName.lpTemplateName    = NULL;

    // if user found a file then try to load it
    if (GetOpenFileName(&openFileName))
    {
        return make_strnode(filename);
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

    OPENFILENAME openFileName;
    ZeroMemory(&openFileName, sizeof openFileName);
    openFileName.lStructSize       = sizeof openFileName;
    openFileName.hwndOwner         = GetParentWindowForDialog();
    openFileName.hInstance         = NULL;
    openFileName.lpstrFilter       = LOCALIZED_FILEFILTER_ALLFILES;
    openFileName.lpstrCustomFilter = NULL;
    openFileName.nMaxCustFilter    = 0;
    openFileName.nFilterIndex      = 0;
    openFileName.lpstrFile         = filename;
    openFileName.nMaxFile          = ARRAYSIZE(filename);
    openFileName.lpstrFileTitle    = NULL;
    openFileName.nMaxFileTitle     = 0;
    openFileName.lpstrInitialDir   = NULL;
    openFileName.lpstrTitle        = NULL;
    openFileName.Flags             = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER;
    openFileName.nFileOffset       = 0;
    openFileName.nFileExtension    = 0;
    openFileName.lpstrDefExt       = NULL;
    openFileName.lCustData         = 0;
    openFileName.lpfnHook          = NULL;
    openFileName.lpTemplateName    = NULL;

    // if user found a file then try to load it
    if (GetSaveFileName(&openFileName))
    {
        return make_strnode(filename, strlen(filename), STRING, strnzcpy);
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

    ShowEditorForFile(filename, NULL);
    return Unbound;
}

void uninitialize_windows()
{
    g_LogoWidgets.clear();
}
