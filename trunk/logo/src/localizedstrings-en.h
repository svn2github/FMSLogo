//
// Copyright (C) 2006 by David Costanzo
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
//

/////////////////////////////////////////////////////////////////////////////
// This file contains localized strings for English
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Localization Instructions:
//
// This file a C++ header file, so if you are familiar with how C++ works, it
// will help.
//
// Each localized string is a line that takes the following form:
//
//      #define <TOKEN> "<quoted-string>" //<status>
//
//   #define         - is part of C++.  Do not change this.
//   <TOKEN>         - is how the FMSLogo source code refers to the string.
//                     This must not change, regardless of the locale.
//   <quoted-string> - is what fmslogo.exe will use whenever it refers 
//                     to <TOKEN>.  This is bit that must be translated.
//   <status>        - This is some information on whether or not the
//                     string has been localized yet.  For example, is 
//                     someone has localized FMSLogo into French, then I add
//                     a new string, I will append //NOT_YET_LOCALIZED as a
//                     reminder that we need to localized just this one string.
//
// To localize FMSLogo, you must to translate the phrases in <quoted-string>
// from English to your language.  Once you have localized a string, please
// remove the //<status> comment at the end of the line.
//
// If you think that a string should *NOT* be translated (for example "FMSLogo"),
// then just delete the //<status> comment to indicate that you have decided
// not to translate the string.  If you are not sure how to translate a string
// please leave the //<status> comment so that that someone else may investigate
// it.
//
// Please note that some of the quoted strings embed a <TOKEN> within them.
// For example, the phrase:
//
//   "I like FMSLogo, do you?"
//
// Might appear as:
//
//   "I like "LOCALIZED_GENERAL_PRODUCTNAME", do you?"
//
// When fmslogo.exe is built, the LOCALIZED_GENERAL_PRODUCTNAME will be 
// replaced with the localized form of FMSLogo and will look like the
// original phrase.  Please only translate the "I like " and ", do you?".
//
// Some of the quoted strings (the ones that appear in menus and buttons)
// have ampersands "&" characters in them.  For example the word "File" 
// may appear as "&File".  This tells Windows that ALT+F should take the
// user straight to this option.
// 
// Some of the quoted strings have a "%p" or a "%s" in them.  For example,
// the error message for when you give bad input looks like this:
//
//    "%p doesn't like %s as input"
//
// The "%p" and "%s" are replaced with the procedure name and the input
// that it doesn't like.  You must NOT add any "%" characters to any string, 
// nor can you change the order in which the %p and %s occur.
//
// There are some special characters that you can add to a string with a 
// special "escape sequence", which begins with a backslash "\".
//
//    Tab       - "\t"
//    Newline   - "\n"
//    Backslash - "\\"
//
// Due to a bug in Borland's resource compiler, two forward slashes cannot
// appear in a quoted string.  To work around this problem, I "escape" the
// first slash, as in:
// 
//    "http://fmslogo.org/" -> "http:\x2F/fmslogo.org/
//
/////////////////////////////////////////////////////////////////////////////

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      "&OK"
#define LOCALIZED_GENERAL_CANCELBUTTON  "&Cancel"

#define LOCALIZED_GENERAL_PRODUCTNAME   "FMSLogo"



//
// The menu options on the main window 
//
#define LOCALIZED_FILE        "&File"
#define LOCALIZED_FILE_NEW    "&New\t(erase workspace)"
#define LOCALIZED_FILE_LOAD   "&Load...\t(merge into workspace)"
#define LOCALIZED_FILE_OPEN   "&Open...\t(replace workspace)" 
#define LOCALIZED_FILE_SAVE   "&Save" 
#define LOCALIZED_FILE_SAVEAS "Save &As..."
#define LOCALIZED_FILE_EDIT   "&Edit..."
#define LOCALIZED_FILE_ERASE  "E&rase..."
#define LOCALIZED_FILE_EXIT   "E&xit"

#define LOCALIZED_BITMAP               "&Bitmap"
#define LOCALIZED_BITMAP_NEW           "&New"
#define LOCALIZED_BITMAP_LOAD          "&Load..."
#define LOCALIZED_BITMAP_SAVE          "&Save"
#define LOCALIZED_BITMAP_SAVEAS        "Save &As..."
#define LOCALIZED_BITMAP_PRINT         "&Print..."
#define LOCALIZED_BITMAP_PRINTERSETUP  "P&rinter Setup..."
#define LOCALIZED_BITMAP_ACTIVEAREA    "A&ctive Area..."

#define LOCALIZED_SET                  "&Set"
#define LOCALIZED_SET_PENSIZE          "Pen Si&ze..."
#define LOCALIZED_SET_LABELFONT        "&Label Font..."
#define LOCALIZED_SET_COMMANDERFONT    "&Commander Font..."
#define LOCALIZED_SET_PENCOLOR         "&Pen Color..."
#define LOCALIZED_SET_FLOODCOLOR       "F&lood Color..."
#define LOCALIZED_SET_SCREENCOLOR      "&Screen Color..."

#define LOCALIZED_ZOOM                 "&Zoom" 
#define LOCALIZED_ZOOM_IN              "&In"
#define LOCALIZED_ZOOM_OUT             "&Out"
#define LOCALIZED_ZOOM_NORMAL          "&Normal"

#define LOCALIZED_HELP                 "&Help" 
#define LOCALIZED_HELP_INDEX           "&Index"
#define LOCALIZED_HELP_MCI             "&MCI"
#define LOCALIZED_HELP_HELP            "&Using Help"
#define LOCALIZED_HELP_TUTORIAL        "&Tutorial"
#define LOCALIZED_HELP_DEMO            "&Demo" 
#define LOCALIZED_HELP_EXAMPLE         "&Examples"
#define LOCALIZED_HELP_RELEASENOTES    "&Release Notes"
#define LOCALIZED_HELP_ABOUTFMSLOGO    "&About "LOCALIZED_GENERAL_PRODUCTNAME"..."
#define LOCALIZED_HELP_MS              "&About MS..."

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              "Select Active Area"
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       "These affect Printing and Saving Bitmaps"
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        "Y-High"
#define LOCALIZED_SELECTACTIVEAREA_YLOW         "Y-Low" 
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        "X-High"
#define LOCALIZED_SELECTACTIVEAREA_XLOW         "X-Low"
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "Turtle steps per inch printed:"
#define LOCALIZED_SELECTACTIVEAREA_RESET        "&Reset" 
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON


//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     "Copy"
#define LOCALIZED_POPUP_CUT                      "Cut"
#define LOCALIZED_POPUP_PASTE                    "Paste"
#define LOCALIZED_POPUP_DELETE                   "Delete"
#define LOCALIZED_POPUP_UNDO                     "Undo"
#define LOCALIZED_POPUP_SELECTALL                "Select All"
#define LOCALIZED_POPUP_HELP                     "Topic Search"

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   "Editor"

#define LOCALIZED_EDITOR_FILE                    "&File"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        "&Save and Exit\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    "Save to &Workspace"
#define LOCALIZED_EDITOR_FILE_PRINT              "&Print..." 
#define LOCALIZED_EDITOR_FILE_EXIT               "E&xit" 

#define LOCALIZED_EDITOR_EDIT                    "&Edit"
#define LOCALIZED_EDITOR_EDIT_UNDO               "&Undo\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_CUT                "&Cut\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               "C&opy\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              "&Paste\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_PASTE              "&Paste\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             "&Delete\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           "C&lear All\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          "S&elect All\tCtrl+A"

#define LOCALIZED_EDITOR_SEARCH                  "&Search"
#define LOCALIZED_EDITOR_SEARCH_FIND             "&Find...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          "&Replace...\tCtrl+H" 
#define LOCALIZED_EDITOR_SEARCH_NEXT             "&Next\tF3" 

#define LOCALIZED_EDITOR_SET                     "Se&t" 
#define LOCALIZED_EDITOR_SET_FONT                "&Font..." 

#define LOCALIZED_EDITOR_TEST                    "Test!"

#define LOCALIZED_EDITOR_HELP                    "&Help" 
#define LOCALIZED_EDITOR_HELP_INDEX              "&Index"
#define LOCALIZED_EDITOR_HELP_EDITOR             "&Editor"
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        "&Topic Search\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    "&Save and Exit"
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       "&Don't Save"
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       "There are unsaved changes in the workspace.  If you exit without saving, these changes will be lost.  "
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       "Would you like to save your changes before exiting?" 


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     "Commander"
#define LOCALIZED_COMMANDER_HALT                "Halt"
#define LOCALIZED_COMMANDER_TRACE               "Trace"
#define LOCALIZED_COMMANDER_NOTRACE             "NoTrace"
#define LOCALIZED_COMMANDER_PAUSE               "Pause"
#define LOCALIZED_COMMANDER_STATUS              "Status"
#define LOCALIZED_COMMANDER_NOSTATUS            "NoStatus"
#define LOCALIZED_COMMANDER_STEP                "Step"
#define LOCALIZED_COMMANDER_UNSTEP              "UnStep"
#define LOCALIZED_COMMANDER_RESET               "Reset"
#define LOCALIZED_COMMANDER_EXECUTE             "Execute"
#define LOCALIZED_COMMANDER_EDALL               "Edall"

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        "Status"
#define LOCALIZED_STATUS_CONTACT                "Contact:"
#define LOCALIZED_STATUS_PENCOLOR               "Pen(RGB):"
#define LOCALIZED_STATUS_FLOODCOLOR             "Flood(RGB):"
#define LOCALIZED_STATUS_SCREENCOLOR            "Screen(RGB):"
#define LOCALIZED_STATUS_PALETTE                "Palette use:"
#define LOCALIZED_STATUS_WIDTH                  "Width:"
#define LOCALIZED_STATUS_POSITION               "Position(XYZ):"
#define LOCALIZED_STATUS_WHICH                  "Which:"
#define LOCALIZED_STATUS_VISIBILITY             "Visibility:"
#define LOCALIZED_STATUS_STYLE                  "Style:"
#define LOCALIZED_STATUS_HEADING                "Heading:"
#define LOCALIZED_STATUS_PITCH                  "Pitch:"
#define LOCALIZED_STATUS_ROLL                   "Roll:"
#define LOCALIZED_STATUS_PEN                    "Pen"
#define LOCALIZED_STATUS_ORIENTATION            "Orientation"
#define LOCALIZED_STATUS_TURTLE                 "Turtle"
#define LOCALIZED_STATUS_COLOR                  "Color"
#define LOCALIZED_STATUS_KERNEL                 "Kernel"
#define LOCALIZED_STATUS_CALLS                  "Calls:"
#define LOCALIZED_STATUS_PEAKMEMORY             "Peak Memory:"

#define LOCALIZED_STATUS_PENREVERSE  "Reverse"
#define LOCALIZED_STATUS_PENNORMAL   "Normal"
#define LOCALIZED_STATUS_PENERASE    "Erase"
#define LOCALIZED_STATUS_PENUP       "Up"
#define LOCALIZED_STATUS_PENDOWN     "Down"
#define LOCALIZED_STATUS_PENSHOWN    "Shown"
#define LOCALIZED_STATUS_PENHIDDEN   "Hidden"
#define LOCALIZED_STATUS_POLYGONS    "Polygons"
#define LOCALIZED_STATUS_VECTORS     "Vectors"
#define LOCALIZED_STATUS_NODES       "Nodes"

//
// Strings on the Erase Procedure dialog box window
//
#define LOCALIZED_ERASEPROCEDURE                "Erase Procedure"
#define LOCALIZED_ERASEPROCEDURE_OK             LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_ERASEPROCEDURE_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_ERASEPROCEDURE_ALL            "&All"

//
// Strings on the Edit Procedure dialog box window
//
#define LOCALIZED_EDITPROCEDURE                "Edit Procedure"
#define LOCALIZED_EDITPROCEDURE_OK             LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_EDITPROCEDURE_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_EDITPROCEDURE_ALL            "&All"

//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     "Set Color"
#define LOCALIZED_SETCOLOR_RED                 "Red"
#define LOCALIZED_SETCOLOR_GREEN               "Green"
#define LOCALIZED_SETCOLOR_BLUE                "Blue"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   "Pen Size"
#define LOCALIZED_SIZE                         "Size"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     "About "LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             LOCALIZED_GENERAL_PRODUCTNAME" Version "FMSLOGO_VERSION
#define LOCALIZED_ABOUTFMS_GUI                 "GUI by George Mills (mills@softronix.com)\nSoftronics, Inc.\nhttp:\x2F/www.softronix.com/"
#define LOCALIZED_ABOUTFMS_INSTALLER           "Installer based on Nullsoft Scriptable Install System\nhttp:\x2F/nsis.sourceforge.net"
#define LOCALIZED_ABOUTFMS_ADVENTURE           "The Great Logo Adventure (ISBN 0-9651934-6-2)\nWritten and donated by Jim Muller\nAvailable at http:\x2F/www.softronix.com/"
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "Thanks to Yehuda Katz (yehuka@softhome.net)\nand Erich Neuwirth (erich.neuwirth@univie.ac.at)"
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME" is free software\nSee GNU Public License"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "Internet News Group: comp.lang.logo\nVisit the Logo-Forum at\nhttp:\x2F/groups.yahoo.com/group/LogoForum/"
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "To learn the internals of computers,\ntry MultiMedia Logic from Softronics, Inc."
#define LOCALIZED_ABOUTFMS_CORE                "Core by Brian Harvey (bh@cs.berkeley.edu)\nUniversity of California Berkeley"
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "About FMS"
#define LOCALIZED_ABOUTMS_FMS                  "FMS stands for Fight Multiple Sclerosis."
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "Please consider donating to the\nNational Multiple Sclerosis Society.\nhttp:\x2F/www.nmss.org\n1-800-FIGHT-MS"
#define LOCALIZED_ABOUTMS_OK                   LOCALIZED_GENERAL_OKBUTTON


// 
// Strings in various other dialog boxes
// 

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "Changes in this edit session may be lost.\n\nDo you really want to exit "LOCALIZED_GENERAL_PRODUCTNAME"?"
#define LOCALIZED_EDITSESSIONISRUNNING      "An Edit session is running"

#define LOCALIZED_NOTHALTEDREALLYEXIT        LOCALIZED_GENERAL_PRODUCTNAME" does not like exiting while not halted.\n\nDo you really want to exit "LOCALIZED_GENERAL_PRODUCTNAME"?"
#define LOCALIZED_NOTHALTEDREALLYHALT        LOCALIZED_GENERAL_PRODUCTNAME" does not like exiting while not halted.\n\nDo you really want to Halt "LOCALIZED_GENERAL_PRODUCTNAME"?"
#define LOCALIZED_LOGOISNOTHALTED            LOCALIZED_GENERAL_PRODUCTNAME" is not Halted"

#define LOCALIZED_WRITEFAILEDNOMEMORY         "Write failed, Possibly no Memory"
#define LOCALIZED_COULDNOTWRITEBMP            "Could not write .bmp"
#define LOCALIZED_COULDNOTOPENBMP             "Could not open .bmp"
#define LOCALIZED_COULDNOTCREATEBMP           "Unable to create Windows 3.0 bitmap"
#define LOCALIZED_NOTVALIDBMP                 "Not a Windows 3.0 bitmap"

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "You have not saved to disk"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "Executing a new will erase all definitions.\n\nContinue with New?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "The file being loaded will be merged into your workspace\nand may overwrite your unsaved changes.\n\nContinue with Load?"
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "This will erase all of your unsaved changes.\n\nContinue with Open?"

#define LOCALIZED_EDITORISOPEN                  "Did you know you have an edit session running?\n\nAny changes in this edit session are not being saved."

#define LOCALIZED_ERROR_CANTREADFILE            "Unable to read file \"%s\" from disk"
#define LOCALIZED_ERROR_CANTWRITEFILE           "Unable to write file \"%s\" to disk"

#define LOCALIZED_SAVEISFOREXPERTSONLY          "This feature is for expert mode only (use "LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT")"
#define LOCALIZED_SAVETOWORKSPACE                "Save to Workspace"
#define LOCALIZED_CONTENTSCHANGED                "Contents Changed"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "The contents have changed.\nWould you like to save the changes to the workspace?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "The cursor will be positioned just after last successful definition.\nCheck the Commander window for possible error message."
#define LOCALIZED_RETURNTOEDIT                  "Return to edit?"

#define LOCALIZED_EDITFAILEDTOLOAD              "Your Edit has FAILED to load"



// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILEFILTER_ALLFILES "All Files (*.*)|*.*|"
#define LOCALIZED_FILEFILTER_LOGO     "Logo Files (*.lgo)|*.lgo|"LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    "Bitmap Files (*.bmp)|*.bmp|GIF Files (*.gif)|*.gif|"LOCALIZED_FILEFILTER_ALLFILES



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             " stops\n"
#define LOCALIZED_TRACING_OUTPUTS           " outputs %s\n"
#define LOCALIZED_TRACING_MAKE              "Make %s %s" 
#define LOCALIZED_TRACING_PPROP             "Pprop %s %s %s"
#define LOCALIZED_TRACING_LOCATION          " in %s\n%s"

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  "Single Step"

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "%s defined\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "erase"
#define LOCALIZED_PENMODE_REVERSE  "reverse"
#define LOCALIZED_PENMODE_PAINT    "paint"

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED      "Input is not paired"
#define LOCALIZED_ERROR_FATALINTERNAL          "Logo: Fatal Internal Error"
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       "Logo: Out of memory"
#define LOCALIZED_ERROR_OUTOFMEMORY            "Out of memory"
#define LOCALIZED_ERROR_STACKOVERFLOW          "stack overflow"
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      "turtle out of bounds"
#define LOCALIZED_ERROR_BADGRAPHINIT           "couldn't initialize graphics"
#define LOCALIZED_ERROR_BADDATA                "%p doesn't like %s as input"
#define LOCALIZED_ERROR_DIDNTOUTPUT            "%p didn't output to %p"
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        "not enough inputs to %p"
#define LOCALIZED_ERROR_TOOMUCH                "too much inside ()'s"
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    "You don't say what to do with %s"
#define LOCALIZED_ERROR_PARENMISMATCH          "too many ('s"
#define LOCALIZED_ERROR_NOVALUE                "%s has no value"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        "unexpected ')'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      "unexpected ']'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        "unexpected '}'"
#define LOCALIZED_ERROR_DONTKNOWHOWTO          "I don't know how to %p"
#define LOCALIZED_ERROR_NOCATCHTAG             "Can't find catch tag for %p"
#define LOCALIZED_ERROR_ALREADYDEFINED         "%p is already defined"
#define LOCALIZED_ERROR_STOPPING               "Stopping..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "Already dribbling"
#define LOCALIZED_ERROR_FILESYSTEM                   "File system error: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "Could not open file"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "Unable to open file: %t"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "File already open"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "File not open"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "Could not create editor file"
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "Could not launch the editor" 
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "Could not read editor file" 
#define LOCALIZED_ERROR_IFWARNING              "Assuming you mean IFELSE, not IF"
#define LOCALIZED_ERROR_SHADOWWARNING          "%p shadowed by local in procedure call"
#define LOCALIZED_ERROR_USER                   "Throw \"Error"
#define LOCALIZED_ERROR_ISPRIMITIVE            "%p is a primitive"
#define LOCALIZED_ERROR_TONOTINSIDE            "Can't use TO inside a procedure"
#define LOCALIZED_ERROR_ATTOPLEVEL             "Can only use %p inside a procedure"
#define LOCALIZED_ERROR_ATTOPLEVEL2            "You must be in a procedure to use OUTPUT or STOP"
#define LOCALIZED_ERROR_NOTEST                 "%p without TEST"
#define LOCALIZED_ERROR_BADMACROOUTPUT         "Macro output %s instead of a list"
#define LOCALIZED_ERROR_DEEPEND                "END inside multi-line instruction"
#define LOCALIZED_ERROR_DEEPENDIN              "END inside multi-line instruction in %p"
#define LOCALIZED_ERROR_UNKNOWN                "Unknown error condition - internal error."

#define LOCALIZED_PAUSING                      "Pausing..."


//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "Error"
#define LOCALIZED_ERROR_BADINPUT             "Bad input"

#define LOCALIZED_ERROR_CANTOPENPORT         "Could not open port"
#define LOCALIZED_ERROR_CANTCLOSEPORT        "Could not close port"
#define LOCALIZED_ERROR_CANTFLUSHPORT        "Could not flush port"
#define LOCALIZED_ERROR_CANTDCBONPORT        "Could not build dcb on port"
#define LOCALIZED_ERROR_CANTSETPORT          "Could not set port"
#define LOCALIZED_ERROR_PORTALREADYOPEN      "Port is already open"
#define LOCALIZED_ERROR_PORTNOTOPEN          "Port is not open"
#define LOCALIZED_ERROR_FIRSTINPUTNOTANARRY  "First input must be an array"

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "Already exists"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "Does not exist"

#define LOCALIZED_ERROR_DLL                   "DLL Error"
#define LOCALIZED_ERROR_DLLNOTLOADED          "DLL is not loaded"
#define LOCALIZED_ERROR_DLLALREADYLOADED      "DLL is already loaded"
#define LOCALIZED_ERROR_DLLLOADFAILED         "DLL load failed"
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "Invalid data type input"
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "Invalid output type"
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "Function not found"
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "Not all Type/Data inputs are paired"

#define LOCALIZED_ERROR_NETWORK                    "Network Error"
#define LOCALIZED_ERROR_NETWORKRECEIVE             "Network Receive Error"
#define LOCALIZED_ERROR_NETWORKSEND                "Network Send Error"
#define LOCALIZED_ERROR_NETWORKSHUTDOWN            "Unexpected Error, Network may be shutdown"
#define LOCALIZED_ERROR_NETWORKNOTSTARTED          "Not started"
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED      "Already started"
#define LOCALIZED_ERROR_NETWORKALREADYON           "Already on"
#define LOCALIZED_ERROR_NETWORKALREADYOFF          "Already off"

// The rest of the network errors shouldn't really see -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         "Name too long"
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      "Not initialized"
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      "System not ready"
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED "Version is not supported"
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   "Can't send after socket shutdown"
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         "Interrupted system call"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    "Authoritative Answer: Host not found"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH "Non-Authoritative: Host not found. See NETSTARTUP"
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      "Non-recoverable error"
#define LOCALIZED_ERROR_NETWORKNODATA              "No data record available"
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       "Bad file number"
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          "Operation would block"
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       "Operation now in progress"
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   "Operation already in progress"
#define LOCALIZED_ERROR_NETWORKBADADDRESS          "Bad address"
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     "Destination address required"
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      "Message too long"
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      "Protocol family not supported"
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         "Directory not empty"
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     "Application limit has been reached"
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           "Disk quota exceeded"
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        "Too many open files"
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        "Access denied"
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          "Socket operation on non-socket"
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    "Can't assign requested address"
#define LOCALIZED_ERROR_NETWORKADDRINUSE           "Address already in use"
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      "Address family not supported by protocol family"
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            "Connection timed out"
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    "Socket type not supported"
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   "Protocol not supported"
#define LOCALIZED_ERROR_NETWORKNOBUFFER            "No space in buffer"
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    "Socket is already connected"
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        "Socket is not connected"
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         "Bad protocol option"
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     "Connection reset by peer"
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     "Software caused connection abort"
#define LOCALIZED_ERROR_NETWORKISDOWN              "Network is down"
#define LOCALIZED_ERROR_NETWORKRESET               "Network was reset"
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   "Connection refused"
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          "Host is down"
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   "Host is unreachable"
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        "Protocol is wrong type for socket"
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   "Operation not supported on socket"
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         "No path to remote host was found"
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         "Too many references"

#define LOCALIZED_ERROR_POLYSTART               "PolyStart Error"
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "You already have a Polygon started"

#define LOCALIZED_ERROR_POLYEND                 "PolyEnd Error"
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "You have not started a Polygon"
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "You must have at least 3 vectors to define a polygon" 

#define LOCALIZED_ERROR_SOUND                 "Sound Error"

#define LOCALIZED_ERROR_MIDI                  "MIDI Error"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "Invalid MIDI device"
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "Already open"
#define LOCALIZED_ERROR_MIDINOTOPEN           "Not open"

#define LOCALIZED_ERROR_MCI                   "MCI Error"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "No Text in Clipboard"

#define LOCALIZED_ERROR_MCI                   "MCI Error"

#define LOCALIZED_ERROR_TIMERTOOMANY          "Too Many Timers"
#define LOCALIZED_ERROR_TIMERBADID            "Bad Timer Id"
#define LOCALIZED_ERROR_TIMERNOTFOUND         "Timer not found"

#define LOCALIZED_ERROR_BITMODEBADBITMODE     "Illegal Bitmode"

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       "Online help is unavailable because hhctrl.ocx could not be loaded." 
#define LOCALIZED_ERROR_HHCTRLATOMNOTFOUND    "Online help is unavailable because hhctrl.ocx does not contain ATOM_HTMLHELP_API_ANSI." 

#define LOCALIZED_ERROR_BADCOMMANDLINE        "Invalid Command Line" 

#define LOCALIZED_ERROR_TMPNOTDEFINED         "The environment variable TMP is not defined or invalid.\n"LOCALIZED_GENERAL_PRODUCTNAME" will attempt to use C:\\ for storing temporary files"

#define LOCALIZED_ERROR_GIFSAVEFAILED         "Problem Generating GIF, check memory and diskspace"
#define LOCALIZED_ERROR_GIFREADFAILED         "Problem Reading GIF, check memory and diskspace"

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  "BitMap Index out of range"
#define LOCALIZED_ERROR_BITMAPCUTFAILED        "Cut failed, Possibly not enough Memory"
#define LOCALIZED_ERROR_BITMAPFITFAILED        "Fit failed, Possibly not enough Memory"

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    "Nothing to Paste" 
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  "BitMap at Index must be initialized with a bitmap" 

#define LOCALIZED_ERROR_BADTURTLEID             "Bad Turtle Id"
#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      "Turtle %d has no picture, will Halt"

#define LOCALIZED_ERROR_FONTNOTFOUND            "Sorry, no font named %s was found.  Choose one of the following:\n"

#define LOCALIZED_ERROR_PRINTERCANTSCALE        "Print driver does not support this function" 
#define LOCALIZED_ERROR_CANTDRAWIMAGE           "Cannot draw image"
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        "Cannot extract image"
#define LOCALIZED_ERROR_SUBCODE                 "Sub Code"

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         "Input:"
#define LOCALIZED_PROMPT_TO     "To Mode (Cancel to End)"
#define LOCALIZED_PROMPT_LIST   "List Mode (Cancel to Halt)"
#define LOCALIZED_PROMPT_PAUSE  "Pause Mode (Cancel to Continue)"
#define LOCALIZED_PROMPT_INPUT  "Input Mode (Cancel to Halt)"

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      "Changed to \"%s\""
#define LOCALIZED_FILE_CHDIRFAILED         "Could not chdir to directory \"%s\""
#define LOCALIZED_FILE_POPPEDTO            "Popped to \"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "Now in newly created directory \"%s\"" 
#define LOCALIZED_FILE_MKDIRFAILED         "Failed to create directory \"%s\"" 
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "Removed directory \"%s\"" 
#define LOCALIZED_FILE_RMDIRFAILED         "Failed to remove directory \"%s\"" 
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "The directory does not exist."
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "Make sure the directory is empty before trying to remove it."


//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "Active Area"
#define LOCALIZED_INFORMATION   "Information"
#define LOCALIZED_WARNING       "Warning"
#define LOCALIZED_UNTITLED      "Untitled"
#define LOCALIZED_UNKNOWN       "Unknown"

#define LOCALIZED_UNBOUND       "Unbound"

//
// Localized Strings that explain each accelerator
// I don't think that any of these strings can be seen by the user
//
#define LOCALIZED_STRINGTABLE_FILESAVEAS "Saves the contents of the EDALL window to a new file"
#define LOCALIZED_STRINGTABLE_FILEOPEN "Erases the current workspace and loads a Logo program as the new workspace"
#define LOCALIZED_STRINGTABLE_FILELOAD "Locates and loads a Logo program into the current workspace"
#define LOCALIZED_STRINGTABLE_FILENEW "Erases the contents of the EDALL session"
#define LOCALIZED_STRINGTABLE_FILESAVE "Saves the contents of the EDALL window"
#define LOCALIZED_STRINGTABLE_FILEEDIT "Selects a procedure to edit"
#define LOCALIZED_STRINGTABLE_FILEERASE "Selects a procedure to erase"
#define LOCALIZED_STRINGTABLE_EXIT "Exits Logo"
#define LOCALIZED_STRINGTABLE_BITMAPNEW "Clears the screen"
#define LOCALIZED_STRINGTABLE_BITMAPOPEN "Loads a new screen from a Windows bitmap file"
#define LOCALIZED_STRINGTABLE_BITMAPSAVE "Saves the contents of the screen to a bitmap"
#define LOCALIZED_STRINGTABLE_BITMAPSAVEAS "Saves the contents of the screen to a different file"
#define LOCALIZED_STRINGTABLE_BITMAPPRINT "Prints the contents of the screen"
#define LOCALIZED_STRINGTABLE_BITMAPPRINTERSETUP "Configures your printer"
#define LOCALIZED_STRINGTABLE_BITMAPPRINTERAREA "Sets the area of the screen that will be printed or saved to a bitmap"
#define LOCALIZED_STRINGTABLE_SETPENSIZE "Sets the thickness of the turtle's pen"
#define LOCALIZED_STRINGTABLE_SETFONT "Sets the font that is used by the LABEL command"
#define LOCALIZED_STRINGTABLE_SETCOMMANDERFONT "Sets the font used in the commander window"
#define LOCALIZED_STRINGTABLE_SETPENCOLOR "Sets the color of the turtle's pen"
#define LOCALIZED_STRINGTABLE_SETFLOODCOLOR "Sets the color used by the FILL command"
#define LOCALIZED_STRINGTABLE_SETSCREENCOLOR "Clears the screen and sets it to a new color"
#define LOCALIZED_STRINGTABLE_ZOOMIN "Zooms in on the screen"
#define LOCALIZED_STRINGTABLE_ZOOMOUT "Zooms out on the screen"
#define LOCALIZED_STRINGTABLE_ZOOMNORMAL "Restores the screen to its original size"
#define LOCALIZED_STRINGTABLE_HELP "Opens an index of help topics"
#define LOCALIZED_STRINGTABLE_HELPMCI "Opens an index of help topics for the Media Control Interface"
#define LOCALIZED_STRINGTABLE_HELPHELP "Opens help on using help"
#define LOCALIZED_STRINGTABLE_HELPTUTORIAL "Opens a short tutorial on using "LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_STRINGTABLE_HELPDEMO "Shows a demonstration of some things you can do in "LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_STRINGTABLE_HELPEXAMPLES "Displays an index of the sample programs"
#define LOCALIZED_STRINGTABLE_HELPRELEASENOTES "Displays the release notes for this version of "LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_STRINGTABLE_HELPABOUT "Displays version and copyright information"
#define LOCALIZED_STRINGTABLE_HELPABOUTMS "Displays a message about Multiple Sclerosis"
#define LOCALIZED_STRINGTABLE_EDITDELETE "Deletes the current selection (and does not copy to the clipboard)"
#define LOCALIZED_STRINGTABLE_EDITCLEAR "Deletes all text"
#define LOCALIZED_STRINGTABLE_EDITUNDO "Undoes the previous action"
#define LOCALIZED_STRINGTABLE_EDITCUT "Removes the selected text and puts it on the clipboard"
#define LOCALIZED_STRINGTABLE_EDITCOPY "Copies the selected text to the clipboard"
#define LOCALIZED_STRINGTABLE_EDITPASTE "Inserts the text from the clipboard at the current position"
#define LOCALIZED_STRINGTABLE_EDITSELECTALL "Selects all text"
#define LOCALIZED_STRINGTABLE_EDITFIND "Searches for text"
#define LOCALIZED_STRINGTABLE_EDITREPLACE "Searches for text and replaces it with other text"
#define LOCALIZED_STRINGTABLE_EDITFINDNEXT "Repeats the previous Find or Replace command"
#define LOCALIZED_STRINGTABLE_EDITSETFONT "Sets the font for the EDALL window"
#define LOCALIZED_STRINGTABLE_TEST "Runs the selected Logo instructions"
#define LOCALIZED_STRINGTABLE_HELPEDIT "Displays help on using the editor"
#define LOCALIZED_STRINGTABLE_HELPEDIT_TOPIC "Displays help for Logo"
#define LOCALIZED_STRINGTABLE_FILESAVEANDEXIT "Saves and exits the current EDALL session"
#define LOCALIZED_STRINGTABLE_FILESAVETOWORKSPACE "Saves the current EDALL session"
#define LOCALIZED_STRINGTABLE_FILEPRINT "Prints the current EDALL session"
#define LOCALIZED_STRINGTABLE_EDALLEXIT "Closes the EDALL session"

#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "Cannot find %s"
