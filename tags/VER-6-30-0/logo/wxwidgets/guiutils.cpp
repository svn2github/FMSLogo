#include "guiutils.h"

#include <wx/menu.h>
#include <wx/icon.h>
#include <wx/toplevel.h>

#include "stringadapter.h"

#include "fmslogo-16x16.xpm"
#include "fmslogo-32x32.xpm"
#include "fmslogo-64x64.xpm"

void
SetFmsLogoIcon(
    wxTopLevelWindow & TopLevelWindow
    )
{
    wxIcon icon64x64(fmslogo_64x64_xpm);
    wxIcon icon32x32(fmslogo_32x32_xpm);
    wxIcon icon16x16(fmslogo_16x16_xpm);

    wxIconBundle icons;
    icons.AddIcon(icon16x16);
    icons.AddIcon(icon32x32);
    icons.AddIcon(icon64x64);

    TopLevelWindow.SetIcons(icons);
}

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
                WXSTRING(MenuItems[i].MenuText));
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
    MainMenu->Append(childMenu, WXSTRING(ChildMenuText));
}
