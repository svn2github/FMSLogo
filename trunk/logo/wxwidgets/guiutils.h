// -*- c++ -*-
#include <stddef.h>

class wxMenu;
class wxMenuBar;
class wxTopLevelWindow;

struct MENUITEM 
{
    const char *  MenuText;
    int           MenuId;
};

void
SetFmsLogoIcon(
    wxTopLevelWindow & TopLevelWindow
    );

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
