#include "owlrc.h"

#define ID_STATIC               -1

#define IDC_BASE 1000
#define CMD_BASE 32771
#define IDD_BASE 100

#define ID_XLOW                 IDC_BASE + 0
#define ID_XHIGH                IDC_BASE + 1
#define ID_YLOW                 IDC_BASE + 2
#define ID_YHIGH                IDC_BASE + 3
#define ID_RESETEXTENT          IDC_BASE + 4
#define ID_PIXELS               IDC_BASE + 5

#define ID_MEMORY               IDC_BASE + 6
#define ID_EVALS                IDC_BASE + 7
#define ID_FILEEDITOK           IDC_BASE + 8
#define ID_FILEEDITALL          IDC_BASE + 9
#define ID_FILEEDITCANCEL       IDC_BASE + 10
#define ID_FILEEDITCOMBO        IDC_BASE + 11
#define ID_PALETTEUSE           IDC_BASE + 12
#define ID_TURTLEROLL           IDC_BASE + 13
#define ID_FLOODCOLOR           IDC_BASE + 14
#define ID_SCREENCOLOR          IDC_BASE + 15
#define ID_TURTLEWHICH          IDC_BASE + 16
#define ID_TURTLEPITCH          IDC_BASE + 17
#define ID_TURTLEPOSITION       IDC_BASE + 18
#define ID_TURTLEHEADING        IDC_BASE + 19
#define ID_TURTLEVISABILITY     IDC_BASE + 20
#define ID_PENCONTACT           IDC_BASE + 21
#define ID_PENCOLOR             IDC_BASE + 22
#define ID_PENWIDTH             IDC_BASE + 23
#define ID_PENSTYLE             IDC_BASE + 24
#define ID_VECTORS              IDC_BASE + 25
#define ID_THINGS               IDC_BASE + 26

#define ID_TRACE                IDC_BASE + 27
#define ID_STATUS               IDC_BASE + 28
#define ID_RESET                IDC_BASE + 29
#define ID_EXECUTE              IDC_BASE + 30
#define ID_EDITINPUT            IDC_BASE + 31
#define ID_HALT                 IDC_BASE + 32
#define ID_YIELD                IDC_BASE + 33
#define ID_PAUSE                IDC_BASE + 34
#define ID_LISTBOX              IDC_BASE + 35
#define ID_EDALL                IDC_BASE + 36

#define ID_COLORBAR1            IDC_BASE + 37
#define ID_COLORBAR2            IDC_BASE + 38
#define ID_COLORBAR3            IDC_BASE + 39
#define ID_SELCOLOR             IDC_BASE + 40
#define ID_COLOR1               IDC_BASE + 41
#define ID_COLOR2               IDC_BASE + 42
#define ID_COLOR3               IDC_BASE + 43
#define ID_COLOR4               IDC_BASE + 44
#define ID_COLOR5               IDC_BASE + 45
#define ID_COLOR6               IDC_BASE + 46
#define ID_COLOR7               IDC_BASE + 47
#define ID_COLOR8               IDC_BASE + 48
#define ID_COLORGROUP           IDC_BASE + 49

#define ID_SIZEBAR              IDC_BASE + 50
#define ID_SELSIZE              IDC_BASE + 51
#define ID_SIZE1                IDC_BASE + 52
#define ID_SIZE2                IDC_BASE + 53
#define ID_SIZE3                IDC_BASE + 54
#define ID_SIZE4                IDC_BASE + 55
#define ID_SIZE5                IDC_BASE + 56
#define ID_SIZE6                IDC_BASE + 57
#define ID_SIZE7                IDC_BASE + 58
#define ID_SIZE8                IDC_BASE + 59
#define ID_SIZEGROUP            IDC_BASE + 60

#define MYWINDOW_ID             IDC_BASE + 61
#define MYSTATIC_ID             IDC_BASE + 62
#define MYLISTBOX_ID            IDC_BASE + 63
#define MYCOMBOBOX_ID           IDC_BASE + 64
#define MYBUTTON_ID             IDC_BASE + 65
#define MYSCROLLBAR_ID          IDC_BASE + 66
#define MYGROUPBOX_ID           IDC_BASE + 67
#define MYRADIOBUTTON_ID        IDC_BASE + 68
#define MYCHECKBOX_ID           IDC_BASE + 69
#define MYDIALOG_ID             IDC_BASE + 70

#define CM_CONTROLHALT          CMD_BASE + 0
#define CM_CONTROLEXECUTE       CMD_BASE + 1

#define CM_FILEEDIT             CMD_BASE + 2
#define CM_FILEERASE            CMD_BASE + 3

#define CM_HELPEDIT             CMD_BASE + 4
#define CM_HELPEDIT_TOPIC       CMD_BASE + 5

#define CM_HELP                 CMD_BASE + 6
#define CM_HELPABOUT            CMD_BASE + 7
#define CM_HELPABOUTMS          CMD_BASE + 8
#define CM_HELPINDEX            CMD_BASE + 9
#define CM_HELPHELP             CMD_BASE + 10
#define CM_HELPMCI              CMD_BASE + 11
#define CM_HELPTUTORIAL         CMD_BASE + 12
#define CM_HELPDEMO             CMD_BASE + 13
#define CM_HELPEXAMPLES         CMD_BASE + 14
#define CM_HELPRELEASENOTES     CMD_BASE + 15

#define CM_BITMAPNEW            CMD_BASE + 16
#define CM_BITMAPSAVE           CMD_BASE + 17
#define CM_BITMAPSAVEAS         CMD_BASE + 18
#define CM_BITMAPOPEN           CMD_BASE + 19
#define CM_BITMAPPRINT          CMD_BASE + 20
#define CM_BITMAPPRINTERSETUP   CMD_BASE + 21
#define CM_BITMAPPRINTERAREA    CMD_BASE + 22

#define CM_SETFONT              CMD_BASE + 23
#define CM_SETCOMMANDERFONT     CMD_BASE + 24
#define CM_SETPENCOLOR          CMD_BASE + 25
#define CM_SETFLOODCOLOR        CMD_BASE + 26
#define CM_SETSCREENCOLOR       CMD_BASE + 27
#define CM_SETPENSIZE           CMD_BASE + 28

#define CM_ZOOMIN               CMD_BASE + 29
#define CM_ZOOMOUT              CMD_BASE + 30
#define CM_ZOOMNORMAL           CMD_BASE + 31

#define CM_TEST                 CMD_BASE + 32
#define CM_EDITSETFONT          CMD_BASE + 33
#define CM_FILESAVETOWORKSPACE  CMD_BASE + 34
#define CM_FILESAVEANDEXIT      CMD_BASE + 35
#define CM_EDALLEXIT		CMD_BASE + 36

#define WM_MYSCROLLBARCALLBACK         WM_USER + 0
#define WM_CHECKQUEUE                  WM_USER + 1

#define WM_NETWORK_CONNECTSENDACK      WM_USER + 2
#define WM_NETWORK_CONNECTSENDFINISH   WM_USER + 3
#define WM_NETWORK_LISTENRECEIVEACK    WM_USER + 4
#define WM_NETWORK_LISTENRECEIVEFINISH WM_USER + 5

#define PRINTERSETUP_DIALOG     IDD_BASE + 0
#define ABORTPRINT_DIALOG       IDD_BASE + 1
#define COMMANDERSETUP_DIALOG   IDD_BASE + 2

#define EXE_NAME_MAX_SIZE 128

