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

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include "dlgwind.h"

   #include <windows.h>
   #include <windowsx.h> // for combobox macros
   #include <commctrl.h> // for combobox style manifest constants

   #include <wx/app.h>
   #include <wx/button.h>
   #include <wx/listbox.h>
   #include <wx/combobox.h>
   #include <wx/stattext.h>
   #include <wx/statbox.h>
   #include <wx/checkbox.h>
   #include <wx/radiobut.h>
   #include <wx/scrolbar.h>

   #include <wx/filename.h>
   #include <wx/filedlg.h> 
   #include <wx/msgdlg.h> 

   #include "fmslogo.h"
   #include "logoeventqueue.h"
   #include "screen.h"
   #include "coms.h"
   #include "parse.h"
   #include "logodata.h"
   #include "logomath.h"
   #include "localizedstrings.h"
   #include "commander.h"
   #include "init.h"
   #include "argumentutils.h"
   #include "graphwin.h"
   #include "error.h"
   #include "eval.h"
   #include "logocore.h"
   #include "lists.h"
   #include "print.h"
   #include "stringprintednode.h"
   #include "screenwindow.h"
   #include "questionbox.h"
   #include "selectbox.h"
   #include "stringadapter.h"
   #include "debugheap.h"
#endif

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

class CClientRectangle : public wxRect
{
public:
    CClientRectangle();

    void InitializeFromInput(NODE * & Args);

    void ConvertToDialogCoordinates();
    void ConvertToScreenCoordinates();
};

CClientRectangle::CClientRectangle()
{
}

void CClientRectangle::InitializeFromInput(NODE * & Args)
{
    NODE * nextinput = Args;

    SetX(int_arg(nextinput));
    nextinput = cdr(nextinput);

    SetY(int_arg(nextinput));
    nextinput = cdr(nextinput);

    SetWidth(getint(nonnegative_int_arg(nextinput)));
    nextinput = cdr(nextinput);

    SetHeight(getint(nonnegative_int_arg(nextinput)));
    nextinput = cdr(nextinput);
   
    Args = nextinput;
}

void CClientRectangle::ConvertToDialogCoordinates()
{
    SetX((GetX() * BaseUnitsx) / 4);
    SetY((GetY() * BaseUnitsy) / 8);

    SetWidth((GetWidth() * BaseUnitsx) / 4);
    SetHeight((GetHeight() * BaseUnitsy) / 8);
}

// Converts from logo coordinates (where 0,0 is the center of the logical screen
// and may be scrolled off-center) to coordinates within the client area of the
// screen.
void CClientRectangle::ConvertToScreenCoordinates()
{
    SetX( GetX() - GetScreenHorizontalScrollPosition() + xoffset);
    SetY(-GetY() - GetScreenVerticalScrollPosition()   + yoffset);
}

static void SetMswLogoCompatibleFont(wxWindow * Window)
{
    // Sets the font to look like it did in MSWLogo.
    wxFont font = Window->GetFont();
    font.SetFaceName(WXSTRING("System"));
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
        ) :
        wxDialog(
            Parent,
            wxID_ANY,
            Caption,
            wxPoint(ClientRectangle.GetX(), ClientRectangle.GetY()),
            wxSize(ClientRectangle.GetWidth(), ClientRectangle.GetHeight()),
            wxCLIP_CHILDREN | wxCAPTION)
    {
    }

private:
    DECLARE_NO_COPY_CLASS(CLogoDialog);
};

class CLogoListBox : public wxListBox
{
public:

    // In MSWLogo, the list boxes rounded down the height so that
    // they would never show a partial item in the list.  I wasn't
    // able to figure out to change the style of a wxListBox so that
    // it didn't include LBS_NOINTEGRALHEIGHT, so instead I create
    // the window using CreateWindowEx().
    CLogoListBox(
        wxWindow               * Parent,
        const CClientRectangle & ClientRectangle
        )
    {
#ifdef __WXMSW__
        HWND hwnd = ::CreateWindowEx(
            WS_EX_CLIENTEDGE | WS_EX_LEFT, // extended style
            WC_LISTBOX,                    // window class
            "",                            // caption
            LBS_HASSTRINGS |
                LBS_NOTIFY |
                WS_GROUP |
                WS_TABSTOP |
                WS_BORDER |
                WS_CHILD |
                WS_VSCROLL |
                WS_OVERLAPPED |
                WS_VISIBLE,
            ClientRectangle.GetX(),
            ClientRectangle.GetY(),
            ClientRectangle.GetWidth(),
            ClientRectangle.GetHeight(),
            Parent != NULL ? static_cast<HWND>(Parent->GetHandle()) : NULL,
            NULL,  // menu
            NULL,  // module instance
            NULL); // additional parameters
        if (hwnd == NULL)
        {
            // TODO: raise a wxWidgets error
        }

        Reparent(Parent);
        SetHWND(hwnd);
        SubclassWin(hwnd);
        AdoptAttributesFromHWND();
#endif
    }

private:

    DECLARE_NO_COPY_CLASS(CLogoListBox);
};

// Unfortunately, wxComboBox does not handle CBS_SIMPLE Windows comboboxes well.
// In particular, there is no way to set CBS_DISABLENOSCROLL, which means that
// its height would vary with the number of elements within it, which makes it
// incompatable with the MSWLogo behavior.
//
// To work around this, the CLogoComboBox is written as a thin wrapper around
// a native COMBOBOX window, with only the member functions from wxComboBox that
// are necessary to support the MSWLogo commands.
class CLogoComboBox : public wxWindow
{
public:
    CLogoComboBox(
        wxWindow               * Parent, 
        const CClientRectangle & ClientRectangle
        )
    {
#ifdef __WXMSW__
        HWND hwnd = CreateWindow(
            WC_COMBOBOX, // window class
            "",           // caption
            CBS_SIMPLE |
                CBS_AUTOHSCROLL |
                CBS_DISABLENOSCROLL |
                CBS_HASSTRINGS |
                WS_GROUP |
                WS_TABSTOP |
                WS_VSCROLL |
                WS_CHILD |
                WS_OVERLAPPED |
                WS_VISIBLE,
            ClientRectangle.GetX(),
            ClientRectangle.GetY(),
            ClientRectangle.GetWidth(),
            ClientRectangle.GetHeight(),
            Parent != NULL ? static_cast<HWND>(Parent->GetHandle()) : NULL,
            NULL,  // menu
            NULL,  // module instance
            NULL); // additional parameters
        if (hwnd == NULL)
        {
            // TODO: raise a wxWidgets error
        }

        Reparent(Parent);
        SetHWND(hwnd);
        AdoptAttributesFromHWND();

        //
        // For the default COMBOBOX style, Microsoft Windows shrinks the
        // listbox portion so that its height is a multiple of the height
        // of its items (so it never shows a partial item).
        // MSWLogo used this style, which means that FMSLogo must also, or
        // else progams wouldn't lay out dialog boxes correctly.
        //
        // For some reason, under wxWidgets, the portion between the bottom
        // of the listbox and the bottom of the overall COMBOBOX control does
        // not get repainted, which has an undesireable effect.  This can be
        // mostly accounted for by overriding EVT_ERASE_BACKGROUND and setting
        // the brush to the parent's background color, but this doesn't behave
        // correctly when the COMBOBOX is put on the FMSLogo screen window and
        // the turtle draws into that area.
        //
        // So, instead, there is the following block of code shrinks the overall
        // COMBOBOX control box to just be large enough to hold the listbox,
        // which Windows shrunk.  MSWLogo didn't need to do this, so there is
        // probably a way to get the parent to repaint this portion of the
        // COMBOBOX, but I wasn't able to figure it out.
        //

        // Find the listbox child.
        HWND childListBox = FindWindowEx(hwnd, NULL, "ComboLBox", NULL);
        if (childListBox != NULL)
        {
            // Get the extents of the listbox.
            RECT listboxRectangle;
            BOOL isOk = ::GetWindowRect(childListBox, &listboxRectangle);
            if (isOk)
            {
                // The bottom-right corner of the listbox is the
                // height and width that we desire.
                int x = listboxRectangle.right;
                int y = listboxRectangle.bottom;

                // Resize the combobox to exactly fit the listbox.
                ScreenToClient(&x, &y);
                SetSize(x, y);
            }
        }
#endif // __WXMSW__
    }

    const wxString GetValue() const
    {
#ifdef __WXMSW__
        // Determine how long the value is.
        int valueLength = ComboBox_GetTextLength(static_cast<HWND>(GetHandle()));

        // Allocate space for the value.
        wxChar * buffer = new wxChar[valueLength + 1];

        // Read the value into the allocated space
        ComboBox_GetText(
            static_cast<HWND>(GetHandle()),
            buffer,
            valueLength + 1);

        // Convert the buffer into a wxString
        wxString value(buffer);
        delete buffer;

        // Return the value
        return value;
#else
	return wxString("TODO");
#endif
	
    }

    void SetValue(const wxString & NewValue)
    {
#ifdef __WXMSW__
        // For compatibility with MSWLogo, make a best
        // effort to change the selected item to match the
        // new text.
        ComboBox_SelectString(
            static_cast<HWND>(GetHandle()),
            -1,  // search the entire list
            NewValue.c_str());

        int isOk = ComboBox_SetText(
            static_cast<HWND>(GetHandle()),
            NewValue.c_str());
        if (!isOk)
        {
            // TODO: raise a wxWidgets error
        }
#endif
    }

    void Delete(int IndexToDelete)
    {
#ifdef __WXMSW__
        int totalItems = ComboBox_DeleteString(
            static_cast<HWND>(GetHandle()),
            IndexToDelete);
        if (totalItems == CB_ERR)
        {
            // TODO: raise a wxWidgets error
        }
#endif
    }

    void Append(const wxString & NewValue)
    {
#ifdef __WXMSW__
        int newIndex = ComboBox_AddString(
            static_cast<HWND>(GetHandle()),
            NewValue.c_str());
        if (newIndex == CB_ERR || newIndex == CB_ERRSPACE)
        {
            // TODO: raise a wxWidgets error
        }
#endif
    }

    void SetSelection(int IndexToSelect)
    {
#ifdef __WXMSW__
        int status = ComboBox_SetCurSel(
            static_cast<HWND>(GetHandle()),
            IndexToSelect);
        if (status == CB_ERR && IndexToSelect != -1)
        {
            // TODO: raise a wxWidgets error
        }
#endif
    }

private:
    DECLARE_NO_COPY_CLASS(CLogoComboBox);
};

// CLogoStaticText cannot be derived from wxStaticText because that
// class does not support word-wrapping in the same manner that 
// the static text control in MSWLogo does.
class CLogoStaticText : public wxStaticTextBase
{
public:
    CLogoStaticText(
        wxWindow               * Parent,
        const char             * Text, 
        const CClientRectangle & ClientRectangle
        )
    {
#ifdef __WXMSW__
        HWND hwnd = CreateWindow(
            WC_STATIC, // window class
            Text,       // caption
            WS_CHILD |
                WS_OVERLAPPED |
                WS_CLIPCHILDREN |
                WS_VISIBLE,
            ClientRectangle.GetX(),
            ClientRectangle.GetY(),
            ClientRectangle.GetWidth(),
            ClientRectangle.GetHeight(),
            Parent != NULL ? static_cast<HWND>(Parent->GetHandle()) : NULL,
            NULL,  // menu
            NULL,  // module instance
            NULL); // additional parameters
        if (hwnd == NULL)
        {
            // TODO: raise a wxWidgets error
        }

        Reparent(Parent);
        SetHWND(hwnd);
        SubclassWin(hwnd);
        AdoptAttributesFromHWND();
#endif
    }

private:
    DECLARE_NO_COPY_CLASS(CLogoStaticText);
};

class CLogoButton : public wxButton
{
public:
    CLogoButton(
        wxWindow               * Parent,
        const char             * Caption,
        const CClientRectangle & ClientRectangle,
        const char             * Callback
        )
    {
#ifdef __WXMSW__     
      // Initializing the native window using the wxButton ctor
      // caused some painting problems.  The problems seemed
      // related to changing the font to the MSWLogo-compatible
      // one.  Since this is not necessary when using the raw
      // win32 BUTTON class, we create the child window using
      // CreateWindow.
        HWND hwnd = CreateWindow(
            WC_BUTTON, // window class
            Caption,    // caption
            BS_PUSHBUTTON |
                BS_TEXT |
                WS_CHILD |
                WS_GROUP |
                WS_TABSTOP |
                WS_VISIBLE,
            ClientRectangle.GetX(),
            ClientRectangle.GetY(),
            ClientRectangle.GetWidth(),
            ClientRectangle.GetHeight(),
            Parent != NULL ? static_cast<HWND>(Parent->GetHandle()) : NULL,
            NULL,  // menu
            NULL,  // module instance
            NULL); // additional parameters
        if (hwnd == NULL)
        {
            // TODO: raise a wxWidgets error
        }

        Reparent(Parent);
        SetHWND(hwnd);
        SubclassWin(hwnd);
        AdoptAttributesFromHWND();

        strcpy(m_Callback, Callback);
#endif
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

class CLogoScrollBar : public wxScrollBar
{
public:
    CLogoScrollBar(
        wxWindow               * Parent,
        const CClientRectangle & ClientRectangle,
        bool                     IsHScrollBar,
        const char             * Callback
        ) :
        wxScrollBar(
            Parent, 
            wxID_ANY,
            wxPoint(ClientRectangle.GetX(), ClientRectangle.GetY()),
            wxSize(
                 IsHScrollBar  ? ClientRectangle.GetWidth()  : GetSystemScrollBarWidth(),
                 !IsHScrollBar ? ClientRectangle.GetHeight() : GetSystemScrollBarHeight()),
            IsHScrollBar ? wxSB_HORIZONTAL : wxSB_VERTICAL),
        m_IsHorizontal(IsHScrollBar),
        m_RangeOffset(0)
    {
        strcpy(m_Callback, Callback);
        SetMswLogoCompatibleFont(this);
    }

    int  Get();
    void Set(int Low, int High, int Position);

    void SetPosition(int ThumbPosition);

private:
    // Event handlers
    void OnScroll(wxScrollEvent& Event);

    // Private helper functions
    void RunCallback();

    static int GetSystemMetric(int MetricId, int DefaultValue);
    static int GetSystemScrollBarWidth();
    static int GetSystemScrollBarHeight();
    static int GetSystemScrollThumbWidth();
    static int GetSystemScrollThumbHeight();

    // private member variables
    const int m_IsHorizontal;
    int       m_RangeOffset;
    char      m_Callback[MAX_BUFFER_SIZE];

    DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CLogoScrollBar);
};

int CLogoScrollBar::GetSystemMetric(int MetricId, int DefaultValue)
{
#ifdef __WXMSW__
    int value = GetSystemMetrics(MetricId);
    if (value == 0)
    {
        // GetSystemMetrics failed.  Use a reasonable default.
        value = DefaultValue;
    }

    return value;
#else
    return DefaultValue;
#endif
}

int CLogoScrollBar::GetSystemScrollBarHeight()
{
#ifdef __WXMSW__
    return GetSystemMetric(SM_CYVSCROLL, 16);
#else
    return 16;
#endif
}

int CLogoScrollBar::GetSystemScrollBarWidth()
{
#ifdef __WXMSW__
    return GetSystemMetric(SM_CYHSCROLL, 16);
#else
    return 16;
#endif   
}

int CLogoScrollBar::GetSystemScrollThumbHeight()
{
#ifdef __WXMSW__
    return GetSystemMetric(SM_CYVTHUMB, 16);
#else
    return 16;
#endif   
    
}

int CLogoScrollBar::GetSystemScrollThumbWidth()
{
#ifdef __WXMSW__
    return GetSystemMetric(SM_CXHTHUMB, 16);
#else
    return 16;
#endif   
}

void CLogoScrollBar::RunCallback()
{
    callthing *callevent = callthing::CreateNoYieldFunctionEvent(m_Callback);
    calllists.insert(callevent);
    checkqueue();
}

void CLogoScrollBar::SetPosition(int ThumbPosition)
{
    SetThumbPosition(ThumbPosition);

    RunCallback();
}

void CLogoScrollBar::Set(int Low, int High, int Position)
{
    // Update the scrollbar
    m_RangeOffset = Low;

    int scrollThumbWidth = m_IsHorizontal ?
        GetSystemScrollThumbWidth() :
        GetSystemScrollThumbHeight();

    SetScrollbar(
        Position - Low,                // position
        scrollThumbWidth,              // width of the thumb
        High - Low + scrollThumbWidth, // range
        1);                            // granularity of thumb position

    // Notify Logo of the update
    RunCallback();
}

int CLogoScrollBar::Get()
{
    return GetThumbPosition() + m_RangeOffset;
}

void CLogoScrollBar::OnScroll(wxScrollEvent& Event)
{
    // Notify Logo of the update
    RunCallback();

    // continue with the default processing
    Event.Skip();
}

BEGIN_EVENT_TABLE(CLogoScrollBar, wxScrollBar)
    EVT_COMMAND_SCROLL(wxID_ANY, CLogoScrollBar::OnScroll)
END_EVENT_TABLE()


class CLogoGroupBox : public wxStaticBox
{
public:
    CLogoGroupBox(
        wxWindow                * Parent, 
        const CClientRectangle  & ClientRectangle
        ) :
        wxStaticBox(
            Parent,
            wxID_ANY,
            wxEmptyString,
            wxPoint(ClientRectangle.GetX(), ClientRectangle.GetY()),
            wxSize(ClientRectangle.GetWidth(), ClientRectangle.GetHeight())),
        m_FirstChild(NULL)
    {
        // Even though we don't show any text, the font size affects
        // the location of the lines which surround the groupbox,
        // so we must match the font used by MSWLogo.
        SetMswLogoCompatibleFont(this);
    }

    bool IsEmpty() const;
    void Add(wxWindow * Window);

private:

    // member variables
    wxWindow * m_FirstChild;

    DECLARE_NO_COPY_CLASS(CLogoGroupBox);
};

bool CLogoGroupBox::IsEmpty() const
{
    return m_FirstChild == NULL;
}

void CLogoGroupBox::Add(wxWindow * Window)
{
    if (m_FirstChild == NULL)
    {
        m_FirstChild = Window;
    }
}

class CLogoRadioButton : public wxRadioButton
{
public:

    CLogoRadioButton(
        wxWindow               * Parent, 
        const char             * Title, 
        const CClientRectangle & ClientRectangle,
        CLogoGroupBox          * Group
        ) :
        wxRadioButton(
            Parent,
            wxID_ANY,
            WXSTRING(Title),
            wxPoint(ClientRectangle.GetX(), ClientRectangle.GetY()),
            wxSize(ClientRectangle.GetWidth(), ClientRectangle.GetHeight()),
            Group->IsEmpty() ? wxRB_GROUP : 0)
    {
        Group->Add(this);
        SetMswLogoCompatibleFont(this);
    }

private:
    DECLARE_NO_COPY_CLASS(CLogoRadioButton);
};

class CLogoCheckBox : public wxCheckBox
{
public:
    CLogoCheckBox(
        wxWindow               * Parent,
        const wxString         & Title,
        const CClientRectangle & ClientRectangle,
        CLogoGroupBox          * Group
        ) :
        wxCheckBox(
            Parent,
            wxID_ANY,
            Title,
            wxPoint(ClientRectangle.GetX(), ClientRectangle.GetY()),
            wxSize(ClientRectangle.GetWidth(), ClientRectangle.GetHeight()))
    {
        // TODO: Figure out how to use Group
        SetMswLogoCompatibleFont(this);
    }

private:
    DECLARE_NO_COPY_CLASS(CLogoCheckBox);
};



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
        CLogoDialog      * Dialog;
        CLogoStaticText  * StaticText;
        CLogoListBox     * ListBox;
        CLogoComboBox    * ComboBox;
        CLogoButton      * Button;
        CLogoScrollBar   * ScrollBar;
        CLogoGroupBox    * GroupBox;
        CLogoRadioButton * RadioButton;
        CLogoCheckBox    * CheckBox;
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

    case WINDOWTYPE_Static:
        return StaticText;

    case WINDOWTYPE_ListBox:
        return ListBox;

    case WINDOWTYPE_ComboBox:
        return ComboBox;

    case WINDOWTYPE_Button:
        return Button;

    case WINDOWTYPE_ScrollBar:
        return ScrollBar;

    case WINDOWTYPE_GroupBox:
        return GroupBox;

    case WINDOWTYPE_RadioButton:
        return RadioButton;

    case WINDOWTYPE_CheckBox:
        return CheckBox;

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
        // This is a top-level WINDOW or DIALOG or
        // a widget that was placed on the screen window.
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
            putcombobox(WXSTRING_TO_STRING(temp), MESSAGETYPE_Normal);
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

                putcombobox(WXSTRING_TO_STRING(temp), MESSAGETYPE_Normal);
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
        if (l->m_Parent == NULL)
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

    CStringPrintedNode titlename(car(nextArg));
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
        child->m_Parent = reinterpret_cast<char*>(parent->Dialog);
    }
    else
    {
        // The parent doesn't exist.  Use the top-level window as the parent.
        wxParent = GetMainWxWindow();
        child->m_Parent = NULL;
    }

    child->Dialog = new CLogoDialog(
        wxParent,
        WXSTRING(titlename.GetString()),
        clientrect);

    g_LogoWidgets.insert(child);

    // Invoke the user-supplied instruction list that adds controls
    // to this window before it is shown.
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
            // Kill this window and all of its children.
            //
            // Note that because wxWidgets doesn't destroy the window until
            // the application is idle, some tests may think that the window
            // is still open.  To signal to the tests that the window
            // is scheduled to be destroyed, we change its name in a way that
            // the tests will see, but the user won't.
            window->Dialog->SetTitle(window->Dialog->GetTitle() + WXSTRING(" "));
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

    CStringPrintedNode titlename(car(nextArg));
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
        WXSTRING(titlename.GetString()),
        clientrect);
    child->m_Parent = (char *)wxParent;
    g_LogoWidgets.insert(child);

    // Modal windows must have a callback to set them up
    // since it will not return until closed.
    do_execution(callback);

    // Since executing "callback" can delete the new dialog box,
    // we must check that it still exists before we try to show it.
    child = g_LogoWidgets.get(childname, WINDOWTYPE_Dialog);
    if (child != NULL)
    {
        child->Dialog->ShowModal();
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

        child->m_Parent = NULL;

        child->ListBox = new CLogoListBox(
            GetScreenWxWindow(),
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
    return parser(make_strnode(WXSTRING_TO_STRING(selection)), false);
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
    listbox->ListBox->Append(WXSTRING(stringname));
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

    if (listbox->ListBox->GetCount() <= (unsigned int) index)
    {
        // The index is out of range.
        // This is not an error in FMSLogo, but it is in wxWidgets,
        // so we ignore the request.
        return Unbound;
    }

    // kill entry based on index
    listbox->ListBox->Delete(index);

    // Set the selection back to 0, if such an entry exists
    if (!listbox->ListBox->IsEmpty())
    {
        listbox->ListBox->SetSelection(0);
    }

    return Unbound;
}

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

        child->ComboBox = new CLogoComboBox(
            parent->Dialog,
            clientrect);
    }
    else
    {
        // else the parent does not exist -- put the control on the screen
        clientrect.ConvertToScreenCoordinates();

        child->m_Parent = NULL;

        child->ComboBox = new CLogoComboBox(
            GetScreenWxWindow(),
            clientrect);
    }

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
    const wxString & selection = combobox->ComboBox->GetValue();

    // parsing it turns it into a list
    return parser(make_strnode(WXSTRING_TO_STRING(selection)), false);
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
    combobox->ComboBox->SetValue(WXSTRING(stringname));
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
    combobox->ComboBox->Append(WXSTRING(stringname));
    combobox->ComboBox->SetSelection(0);
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
    combobox->ComboBox->Delete(index);
    combobox->ComboBox->SetSelection(0);
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

        child->ScrollBar = new CLogoScrollBar(
            parent->Dialog, 
            clientrect,
            isHorizontalScrollbar,
            callback);
    }
    else
    {
        clientrect.ConvertToScreenCoordinates();

        child->m_Parent = NULL;

        child->ScrollBar = new CLogoScrollBar(
            GetScreenWxWindow(),
            clientrect,
            isHorizontalScrollbar,
            callback);
    }

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

    scrollbar->ScrollBar->Set(lo, hi, pos);
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

    int pos = scrollbar->ScrollBar->Get();
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

    CStringPrintedNode titlename(car(nextArg));
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

        child->StaticText = new CLogoStaticText(
            parent->Dialog, 
            titlename, 
            clientrect);
    }
    else
    {
        clientrect.ConvertToScreenCoordinates();

        child->m_Parent = NULL;
            
        child->StaticText = new CLogoStaticText(
            GetScreenWxWindow(),
            titlename,
            clientrect);
    }

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

    CStringPrintedNode titlename(car(cdr(args)));

    CLogoWidget *temp = g_LogoWidgets.get(childname, WINDOWTYPE_Static);
    if (temp == NULL)
    {
        err_logo(WINDOW_DOES_NOT_EXIST, car(args));
        return Unbound;
    }

    temp->StaticText->SetLabel(WXSTRING(titlename.GetString()));
    return Unbound;
}

NODE *lstaticdelete(NODE *args)
{
    return WindowDeleteHelper(args, WINDOWTYPE_Static);
}


NODE *lbuttoncreate(NODE *args)
{
    NODE * nextArg = args;

    char parentname[MAX_BUFFER_SIZE];
    cnv_strnode_string(parentname, nextArg);
    nextArg = cdr(nextArg);

    char childname[MAX_BUFFER_SIZE];
    cnv_strnode_string(childname, nextArg);
    nextArg = cdr(nextArg);

    CStringPrintedNode titlename(car(nextArg));
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

        child->m_Parent = NULL;

        child->Button = new CLogoButton(
            GetScreenWxWindow(),
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

    CStringPrintedNode titlename(car(cdr(args)));

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

    button->Button->SetLabel(WXSTRING(titlename.GetString()));
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

        child->GroupBox = new CLogoGroupBox(
            parent->Dialog, 
            clientrect);
    }
    else
    {
        clientrect.ConvertToScreenCoordinates();

        child->m_Parent = NULL;
            
        child->GroupBox = new CLogoGroupBox(
            GetScreenWxWindow(),
            clientrect);
    }

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

    CStringPrintedNode titlename(car(nextArg));
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

        child->RadioButton = new CLogoRadioButton(
            parent->Dialog, 
            titlename, 
            clientrect,
            group->GroupBox);
    }
    else
    {
        clientrect.ConvertToScreenCoordinates();

        child->m_Parent = NULL;

        child->RadioButton = new CLogoRadioButton(
            GetScreenWxWindow(),
            titlename,
            clientrect,
            group->GroupBox);
    }

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

    bool isPressed = radiobutton->RadioButton->GetValue();
    return true_or_false(isPressed);
}

NODE *lradiobuttonset(NODE *args)
{
    char radiobuttonname[MAX_BUFFER_SIZE];
    cnv_strnode_string(radiobuttonname, args);

    bool isPressed = boolean_arg(cdr(args));

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

    radiobutton->RadioButton->SetValue(isPressed);

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

    CStringPrintedNode titlename(car(nextArg));
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

        child->CheckBox = new CLogoCheckBox(
            parent->Dialog, 
            WXSTRING(titlename.GetString()), 
            clientrect,
            group->GroupBox);
    }
    else
    {
        clientrect.ConvertToScreenCoordinates();

        child->m_Parent = NULL;

        child->CheckBox = new CLogoCheckBox(
            GetScreenWxWindow(),
            WXSTRING(titlename.GetString()),
            clientrect,
            group->GroupBox);
    }

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

    bool isChecked = checkbox->CheckBox->IsChecked();
    return true_or_false(isChecked);
}

NODE *lcheckboxset(NODE *args)
{
    char checkboxname[MAX_BUFFER_SIZE];
    cnv_strnode_string(checkboxname, args);

    bool check = boolean_arg(cdr(args));

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

    checkbox->CheckBox->SetValue(check);

    return Unbound;
}

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
    CStringPrintedNode banner(car(args));
    CStringPrintedNode body(car(cdr(args)), CStringPrintedNode::WithPrintLimits);

    if (NOT_THROWING)
    {
        if (wxMessageBox(
                WXSTRING(body),
                WXSTRING(banner),
                wxOK | wxCANCEL | wxCENTER,
                GetParentWindowForDialog()) == wxCANCEL)
        {
            err_logo(STOP_ERROR, NIL);
        }
    }

    return Unbound;
}

NODE *lquestionbox(NODE *args)
{
    // read/validate inputs
    CStringPrintedNode banner(car(args));
    CStringPrintedNode body(car(cdr(args)), CStringPrintedNode::WithPrintLimits);

    if (stopping_flag == THROWING)
    {
        // bad input
        return Unbound;
    }

    CQuestionBox questionBox(
        GetMainWxWindow(),
        WXSTRING(banner.GetString()),
        WXSTRING(body.GetString()));

    int exitCode = questionBox.ShowModal();
    if (exitCode == wxID_CANCEL)
    {
        // The user pressed cancel.
        err_logo(STOP_ERROR, NIL);
        return Unbound;
    }

    NODE * targ = make_strnode(WXSTRING_TO_STRING(questionBox.GetAnswer()));
    NODE * val = parser(targ, false);
    return val;
}


NODE *lselectbox(NODE *args)
{
    // read/validate inputs
    CStringPrintedNode banner(car(args));

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
        CStringPrintedNode choice(car(currentChoice));
        choices.Add(WXSTRING(choice.GetString()));
    }

    CSelectBox selectBox(
        GetMainWxWindow(),
        WXSTRING(banner.GetString()),
        choices);

    int status = selectBox.DoDialog();
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
    CStringPrintedNode banner(car(args));
    CStringPrintedNode body(car(cdr(args)), CStringPrintedNode::WithPrintLimits);

    if (NOT_THROWING)
    {
        int status = wxMessageBox(
            WXSTRING(body),
            WXSTRING(banner),
            wxYES_NO | wxCANCEL | wxCENTER,
            GetParentWindowForDialog());
        switch (status)
        {
        case wxYES:
            return Truex.GetNode();

        case wxNO:
            return Falsex.GetNode();

        case wxCANCEL:
            err_logo(STOP_ERROR, NIL);
            return Falsex.GetNode();
        }
    }

    return Unbound;
}

static
NODE * dialogfile_helper(NODE * args, long fileDialogFlags)
{
    char filenameBuffer[MAX_PATH];
    PrintNodeToString(car(args), filenameBuffer, ARRAYSIZE(filenameBuffer));

    wxFileName filename(filenameBuffer);

    const wxString selectedFilename = wxFileSelector(
        wxEmptyString,                             // title/message
        filename.GetPath(),                        // default path
        filename.GetFullName(),                    // default file name
        filename.GetExt(),                         // default file extension
        WXSTRING(LOCALIZED_FILEFILTER_ALLFILES),   // file filters
        fileDialogFlags,                           // flags
        GetParentWindowForDialog());               // parent window
    if (!selectedFilename.empty())
    {
        return make_strnode(WXSTRING_TO_STRING(selectedFilename));
    }
    else
    {
        return NIL;
    }
}

NODE *ldialogfileopen(NODE *args)
{
    return dialogfile_helper(args, wxFD_OPEN | wxFD_FILE_MUST_EXIST);
}

NODE *ldialogfilesave(NODE *args)
{
    return dialogfile_helper(args, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
}

NODE *lwindowfileedit(NODE *args)
{
    char filename[MAX_PATH];
    PrintNodeToString(car(args), filename, ARRAYSIZE(filename));

    cnv_strnode_string(edit_editexit, cdr(args));

    ShowEditorForFile(filename, NULL);
    return Unbound;
}

void uninitialize_windows()
{
    g_LogoWidgets.clear();
}
