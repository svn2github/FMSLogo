#include <wx/menu.h>

#include "guiutils.h"

void
FillMenu(
    wxMenu *          Menu,
    const MENUITEM *  MenuItems,
    size_t            MenuItemsLength
    )
{
    for (size_t i = 0; i < MenuItemsLength; i++)
    {
        if (MenuItems[i].MenuText != NULL)
        {
            Menu->Append(
                MenuItems[i].MenuId,
                MenuItems[i].MenuText);
        }
        else
        {
            Menu->AppendSeparator();
        }
    }
}

void
AppendChildMenu(
    wxMenuBar *       MainMenu,
    const char *      ChildMenuText,
    const MENUITEM *  ChildMenuItems,
    size_t            ChildMenuItemsLength
    )
{
    // create the popup menu
    wxMenu * childMenu = new wxMenu;

    // fill the child menu with its items
    FillMenu(childMenu, ChildMenuItems, ChildMenuItemsLength);

    // append the child menu to the main menu
    MainMenu->Append(childMenu, ChildMenuText);
}
