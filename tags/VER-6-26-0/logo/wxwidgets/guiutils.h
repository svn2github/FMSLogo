// -*- c++ -*-

class wxMenuBar;

struct MENUITEM 
{
    const char *  MenuText;
    int           MenuId;
};


void
FillMenu(
    wxMenu *          Menu,
    const MENUITEM *  MenuItems,
    size_t            MenuItemsLength
    );

void
AppendChildMenu(
    wxMenuBar *       MainMenu,
    const char *      ChildMenuText,
    const MENUITEM *  ChildMenuItems,
    size_t            ChildMenuItemsLength
    );
