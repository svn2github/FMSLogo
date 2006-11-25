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
// This file contains localized strings for Greek
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
#define LOCALIZED_GENERAL_OKBUTTON      "&OK" // NOT_YET_LOCALIZED
#define LOCALIZED_GENERAL_CANCELBUTTON  "&Cancel" // NOT_YET_LOCALIZED

#define LOCALIZED_GENERAL_PRODUCTNAME   "FMSLogo" // NOT_YET_LOCALIZED



//
// The menu options on the main window 
//
#define LOCALIZED_FILE        "&File" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_NEW    "&New\t(erase workspace)" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_LOAD   "&Load...\t(merge into workspace)" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_OPEN   "&Open...\t(replace workspace)"  // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_SAVE   "&Save"  // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_SAVEAS "Save &As..." // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_EDIT   "&Edit..." // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_ERASE  "E&rase..." // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_EXIT   "E&xit" // NOT_YET_LOCALIZED

#define LOCALIZED_BITMAP               "&Bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_BITMAP_NEW           "&New" // NOT_YET_LOCALIZED
#define LOCALIZED_BITMAP_LOAD          "&Load..." // NOT_YET_LOCALIZED
#define LOCALIZED_BITMAP_SAVE          "&Save" // NOT_YET_LOCALIZED
#define LOCALIZED_BITMAP_SAVEAS        "Save &As..." // NOT_YET_LOCALIZED
#define LOCALIZED_BITMAP_PRINT         "&Print..." // NOT_YET_LOCALIZED
#define LOCALIZED_BITMAP_PRINTERSETUP  "P&rinter Setup..." // NOT_YET_LOCALIZED
#define LOCALIZED_BITMAP_ACTIVEAREA    "A&ctive Area..." // NOT_YET_LOCALIZED

#define LOCALIZED_SET                  "&Set" // NOT_YET_LOCALIZED
#define LOCALIZED_SET_PENSIZE          "Pen Si&ze..." // NOT_YET_LOCALIZED
#define LOCALIZED_SET_LABELFONT        "&Label Font..." // NOT_YET_LOCALIZED
#define LOCALIZED_SET_COMMANDERFONT    "&Commander Font..." // NOT_YET_LOCALIZED
#define LOCALIZED_SET_PENCOLOR         "&Pen Color..." // NOT_YET_LOCALIZED
#define LOCALIZED_SET_FLOODCOLOR       "F&lood Color..." // NOT_YET_LOCALIZED
#define LOCALIZED_SET_SCREENCOLOR      "&Screen Color..." // NOT_YET_LOCALIZED

#define LOCALIZED_ZOOM                 "&Zoom"  // NOT_YET_LOCALIZED
#define LOCALIZED_ZOOM_IN              "&In" // NOT_YET_LOCALIZED
#define LOCALIZED_ZOOM_OUT             "&Out" // NOT_YET_LOCALIZED
#define LOCALIZED_ZOOM_NORMAL          "&Normal" // NOT_YET_LOCALIZED

#define LOCALIZED_HELP                 "&Help"  // NOT_YET_LOCALIZED
#define LOCALIZED_HELP_INDEX           "&Index" // NOT_YET_LOCALIZED
#define LOCALIZED_HELP_MCI             "&MCI" // NOT_YET_LOCALIZED
#define LOCALIZED_HELP_HELP            "&Using Help" // NOT_YET_LOCALIZED
#define LOCALIZED_HELP_TUTORIAL        "&Tutorial" // NOT_YET_LOCALIZED
#define LOCALIZED_HELP_DEMO            "&Demo"  // NOT_YET_LOCALIZED
#define LOCALIZED_HELP_EXAMPLE         "&Examples" // NOT_YET_LOCALIZED
#define LOCALIZED_HELP_RELEASENOTES    "&Release Notes" // NOT_YET_LOCALIZED
#define LOCALIZED_HELP_ABOUTFMSLOGO    "&About "LOCALIZED_GENERAL_PRODUCTNAME"..." // NOT_YET_LOCALIZED
#define LOCALIZED_HELP_MS              "&About MS..." // NOT_YET_LOCALIZED

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              "Select Active Area" // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       "These affect Printing and Saving Bitmaps" // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        "Y-High" // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTACTIVEAREA_YLOW         "Y-Low"  // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        "X-High" // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTACTIVEAREA_XLOW         "X-Low" // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "Turtle steps per inch printed:" // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTACTIVEAREA_RESET        "&Reset"  // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED


//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     "Copy" // NOT_YET_LOCALIZED
#define LOCALIZED_POPUP_CUT                      "Cut" // NOT_YET_LOCALIZED
#define LOCALIZED_POPUP_PASTE                    "Paste" // NOT_YET_LOCALIZED
#define LOCALIZED_POPUP_DELETE                   "Delete" // NOT_YET_LOCALIZED
#define LOCALIZED_POPUP_UNDO                     "Undo" // NOT_YET_LOCALIZED
#define LOCALIZED_POPUP_SELECTALL                "Select All" // NOT_YET_LOCALIZED
#define LOCALIZED_POPUP_HELP                     "Topic Search" // NOT_YET_LOCALIZED

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   "Editor" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_FILE                    "&File" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        "&Save and Exit\tCtrl+D" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    "Save to &Workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_FILE_PRINT              "&Print..."  // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_FILE_EXIT               "E&xit"  // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_EDIT                    "&Edit" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_EDIT_UNDO               "&Undo\tCtrl+Z" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_EDIT_CUT                "&Cut\tCtrl+X" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_EDIT_COPY               "C&opy\tCtrl+C" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_EDIT_PASTE              "&Paste\tCtrl+V" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_EDIT_PASTE              "&Paste\tCtrl+V" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_EDIT_DELETE             "&Delete\tDel" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_EDIT_CLEARALL           "C&lear All\tCtrl+Del" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_EDIT_SELECTALL          "S&elect All\tCtrl+A" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_SEARCH                  "&Search" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_SEARCH_FIND             "&Find...\tCtrl+F" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_SEARCH_REPLACE          "&Replace...\tCtrl+H"  // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_SEARCH_NEXT             "&Next\tF3"  // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_SET                     "Se&t"  // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_SET_FONT                "&Font..."  // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_TEST                    "Test!" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_HELP                    "&Help"  // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_HELP_INDEX              "&Index" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_HELP_EDITOR             "&Editor" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        "&Topic Search\tF1" // NOT_YET_LOCALIZED


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_GENERAL_PRODUCTNAME // NOT_YET_LOCALIZED
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    "&Save and Exit" // NOT_YET_LOCALIZED
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       "&Don't Save" // NOT_YET_LOCALIZED
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       "There are unsaved changes in the workspace.  If you exit without saving, these changes will be lost.  " // NOT_YET_LOCALIZED
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       "Would you like to save your changes before exiting?"  // NOT_YET_LOCALIZED


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     "Commander" // NOT_YET_LOCALIZED
#define LOCALIZED_COMMANDER_HALT                "Halt" // NOT_YET_LOCALIZED
#define LOCALIZED_COMMANDER_TRACE               "Trace" // NOT_YET_LOCALIZED
#define LOCALIZED_COMMANDER_NOTRACE             "NoTrace" // NOT_YET_LOCALIZED
#define LOCALIZED_COMMANDER_PAUSE               "Pause" // NOT_YET_LOCALIZED
#define LOCALIZED_COMMANDER_STATUS              "Status" // NOT_YET_LOCALIZED
#define LOCALIZED_COMMANDER_NOSTATUS            "NoStatus" // NOT_YET_LOCALIZED
#define LOCALIZED_COMMANDER_STEP                "Step" // NOT_YET_LOCALIZED
#define LOCALIZED_COMMANDER_UNSTEP              "UnStep" // NOT_YET_LOCALIZED
#define LOCALIZED_COMMANDER_RESET               "Reset" // NOT_YET_LOCALIZED
#define LOCALIZED_COMMANDER_EXECUTE             "Execute" // NOT_YET_LOCALIZED
#define LOCALIZED_COMMANDER_EDALL               "Edall" // NOT_YET_LOCALIZED

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        "Status" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_CONTACT                "Contact:" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_PENCOLOR               "Pen(RGB):" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_FLOODCOLOR             "Flood(RGB):" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_SCREENCOLOR            "Screen(RGB):" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_PALETTE                "Palette use:" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_WIDTH                  "Width:" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_POSITION               "Position(XYZ):" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_WHICH                  "Which:" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_VISIBILITY             "Visibility:" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_STYLE                  "Style:" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_HEADING                "Heading:" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_PITCH                  "Pitch:" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_ROLL                   "Roll:" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_PEN                    "Pen" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_ORIENTATION            "Orientation" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_TURTLE                 "Turtle" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_COLOR                  "Color" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_KERNEL                 "Kernel" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_CALLS                  "Calls:" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_PEAKMEMORY             "Peak Memory:" // NOT_YET_LOCALIZED

#define LOCALIZED_STATUS_PENREVERSE  "Reverse" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_PENNORMAL   "Normal" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_PENERASE    "Erase" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_PENUP       "Up" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_PENDOWN     "Down" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_PENSHOWN    "Shown" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_PENHIDDEN   "Hidden" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_POLYGONS    "Polygons" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_VECTORS     "Vectors" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_NODES       "Nodes" // NOT_YET_LOCALIZED

//
// Strings on the Erase Procedure dialog box window
//
#define LOCALIZED_ERASEPROCEDURE                "Erase Procedure" // NOT_YET_LOCALIZED
#define LOCALIZED_ERASEPROCEDURE_OK             LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_ERASEPROCEDURE_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_ERASEPROCEDURE_ALL            "&All" // NOT_YET_LOCALIZED

//
// Strings on the Edit Procedure dialog box window
//
#define LOCALIZED_EDITPROCEDURE                "Edit Procedure" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITPROCEDURE_OK             LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_EDITPROCEDURE_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_EDITPROCEDURE_ALL            "&All" // NOT_YET_LOCALIZED

//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     "Set Color" // NOT_YET_LOCALIZED
#define LOCALIZED_SETCOLOR_RED                 "Red" // NOT_YET_LOCALIZED
#define LOCALIZED_SETCOLOR_GREEN               "Green" // NOT_YET_LOCALIZED
#define LOCALIZED_SETCOLOR_BLUE                "Blue" // NOT_YET_LOCALIZED
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   "Pen Size" // NOT_YET_LOCALIZED
#define LOCALIZED_SIZE                         "Size" // NOT_YET_LOCALIZED
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     "About "LOCALIZED_GENERAL_PRODUCTNAME // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_VERSION             LOCALIZED_GENERAL_PRODUCTNAME" Version "FMSLOGO_VERSION // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_GUI                 "GUI by George Mills (mills@softronix.com)\nSoftronics, Inc.\nhttp:\x2F/www.softronix.com/" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_INSTALLER           "Installer based on Nullsoft Scriptable Install System\nhttp:\x2F/nsis.sourceforge.net" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_ADVENTURE           "The Great Logo Adventure (ISBN 0-9651934-6-2)\nWritten and donated by Jim Muller\nAvailable at http:\x2F/www.softronix.com/" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "Thanks to Yehuda Katz (yehuka@softhome.net)\nand Erich Neuwirth (erich.neuwirth@univie.ac.at)" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME" is free software\nSee GNU Public License" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "Internet News Group: comp.lang.logo\nVisit the Logo-Forum at\nhttp:\x2F/groups.yahoo.com/group/LogoForum/" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "To learn the internals of computers,\ntry MultiMedia Logic from Softronics, Inc." // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_CORE                "Core by Brian Harvey (bh@cs.berkeley.edu)\nUniversity of California Berkeley" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "About FMS" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTMS_FMS                  "FMS stands for Fight Multiple Sclerosis." // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "Please consider donating to the\nNational Multiple Sclerosis Society.\nhttp:\x2F/www.nmss.org\n1-800-FIGHT-MS" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTMS_OK                   LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED


// 
// Strings in various other dialog boxes
// 

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "Changes in this edit session may be lost.\n\nDo you really want to exit "LOCALIZED_GENERAL_PRODUCTNAME"?" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITSESSIONISRUNNING      "An Edit session is running" // NOT_YET_LOCALIZED

#define LOCALIZED_NOTHALTEDREALLYEXIT        LOCALIZED_GENERAL_PRODUCTNAME" does not like exiting while not halted.\n\nDo you really want to exit "LOCALIZED_GENERAL_PRODUCTNAME"?" // NOT_YET_LOCALIZED
#define LOCALIZED_NOTHALTEDREALLYHALT        LOCALIZED_GENERAL_PRODUCTNAME" does not like exiting while not halted.\n\nDo you really want to Halt "LOCALIZED_GENERAL_PRODUCTNAME"?" // NOT_YET_LOCALIZED
#define LOCALIZED_LOGOISNOTHALTED            LOCALIZED_GENERAL_PRODUCTNAME" is not Halted" // NOT_YET_LOCALIZED

#define LOCALIZED_WRITEFAILEDNOMEMORY         "Write failed, Possibly no Memory" // NOT_YET_LOCALIZED
#define LOCALIZED_COULDNOTWRITEBMP            "Could not write .bmp" // NOT_YET_LOCALIZED
#define LOCALIZED_COULDNOTOPENBMP             "Could not open .bmp" // NOT_YET_LOCALIZED
#define LOCALIZED_COULDNOTCREATEBMP           "Unable to create Windows 3.0 bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_NOTVALIDBMP                 "Not a Windows 3.0 bitmap" // NOT_YET_LOCALIZED

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "You have not saved to disk" // NOT_YET_LOCALIZED
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "Executing a new will erase all definitions.\n\nContinue with New?" // NOT_YET_LOCALIZED
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "The file being loaded will be merged into your workspace\nand may overwrite your unsaved changes.\n\nContinue with Load?" // NOT_YET_LOCALIZED
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "This will erase all of your unsaved changes.\n\nContinue with Open?" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITORISOPEN                  "Did you know you have an edit session running?\n\nAny changes in this edit session are not being saved." // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_CANTREADFILE            "Unable to read file \"%s\" from disk" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTWRITEFILE           "Unable to write file \"%s\" to disk" // NOT_YET_LOCALIZED

#define LOCALIZED_SAVEISFOREXPERTSONLY          "This feature is for expert mode only (use "LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT")" // NOT_YET_LOCALIZED
#define LOCALIZED_SAVETOWORKSPACE                "Save to Workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_CONTENTSCHANGED                "Contents Changed" // NOT_YET_LOCALIZED
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "The contents have changed.\nWould you like to save the changes to the workspace?" // NOT_YET_LOCALIZED



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "The cursor will be positioned just after last successful definition.\nCheck the Commander window for possible error message." // NOT_YET_LOCALIZED
#define LOCALIZED_RETURNTOEDIT                  "Return to edit?" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITFAILEDTOLOAD              "Your Edit has FAILED to load" // NOT_YET_LOCALIZED



// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILEFILTER_ALLFILES "All Files (*.*)|*.*|" // NOT_YET_LOCALIZED
#define LOCALIZED_FILEFILTER_LOGO     "Logo Files (*.lgo)|*.lgo|"LOCALIZED_FILEFILTER_ALLFILES // NOT_YET_LOCALIZED
#define LOCALIZED_FILEFILTER_IMAGE    "Bitmap Files (*.bmp)|*.bmp|GIF Files (*.gif)|*.gif|"LOCALIZED_FILEFILTER_ALLFILES // NOT_YET_LOCALIZED



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             " stops\n" // NOT_YET_LOCALIZED
#define LOCALIZED_TRACING_OUTPUTS           " outputs %s\n" // NOT_YET_LOCALIZED
#define LOCALIZED_TRACING_MAKE              "Make %s %s"  // NOT_YET_LOCALIZED
#define LOCALIZED_TRACING_PPROP             "Pprop %s %s %s" // NOT_YET_LOCALIZED
#define LOCALIZED_TRACING_LOCATION          " in %s\n%s" // NOT_YET_LOCALIZED

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  "Single Step" // NOT_YET_LOCALIZED

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "%s defined\n" // NOT_YET_LOCALIZED


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "erase" // NOT_YET_LOCALIZED
#define LOCALIZED_PENMODE_REVERSE  "reverse" // NOT_YET_LOCALIZED
#define LOCALIZED_PENMODE_PAINT    "paint" // NOT_YET_LOCALIZED

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED      "Input is not paired" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FATALINTERNAL          "Logo: Fatal Internal Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       "Logo: Out of memory" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_OUTOFMEMORY            "Out of memory" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_STACKOVERFLOW          "stack overflow" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      "turtle out of bounds" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BADGRAPHINIT           "couldn't initialize graphics" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BADDATA                "%p doesn't like %s as input" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DIDNTOUTPUT            "%p didn't output to %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        "not enough inputs to %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_TOOMUCH                "too much inside ()'s" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    "You don't say what to do with %s" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_PARENMISMATCH          "too many ('s" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NOVALUE                "%s has no value" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        "unexpected ')'" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      "unexpected ']'" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        "unexpected '}'" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DONTKNOWHOWTO          "I don't know how to %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NOCATCHTAG             "Can't find catch tag for %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ALREADYDEFINED         "%p is already defined" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_STOPPING               "Stopping..." // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "Already dribbling" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM                   "File system error: %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "Could not open file" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "Unable to open file: %t" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "File already open" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "File not open" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "Could not create editor file" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "Could not launch the editor"  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "Could not read editor file"  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_IFWARNING              "Assuming you mean IFELSE, not IF" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SHADOWWARNING          "%p shadowed by local in procedure call" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_USER                   "Throw \"Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ISPRIMITIVE            "%p is a primitive" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_TONOTINSIDE            "Can't use TO inside a procedure" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ATTOPLEVEL             "Can only use %p inside a procedure" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ATTOPLEVEL2            "You must be in a procedure to use OUTPUT or STOP" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NOTEST                 "%p without TEST" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BADMACROOUTPUT         "Macro output %s instead of a list" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DEEPEND                "END inside multi-line instruction" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DEEPENDIN              "END inside multi-line instruction in %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_UNKNOWN                "Unknown error condition - internal error." // NOT_YET_LOCALIZED

#define LOCALIZED_PAUSING                      "Pausing..." // NOT_YET_LOCALIZED


//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BADINPUT             "Bad input" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_CANTOPENPORT         "Could not open port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTCLOSEPORT        "Could not close port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTFLUSHPORT        "Could not flush port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTDCBONPORT        "Could not build dcb on port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTSETPORT          "Could not set port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_PORTALREADYOPEN      "Port is already open" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_PORTNOTOPEN          "Port is not open" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FIRSTINPUTNOTANARRY  "First input must be an array" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "Already exists" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "Does not exist" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_DLL                   "DLL Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLNOTLOADED          "DLL is not loaded" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLALREADYLOADED      "DLL is already loaded" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLLOADFAILED         "DLL load failed" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "Invalid data type input" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "Invalid output type" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "Function not found" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "Not all Type/Data inputs are paired" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_NETWORK                    "Network Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKRECEIVE             "Network Receive Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKSEND                "Network Send Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKSHUTDOWN            "Unexpected Error, Network may be shutdown" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOTSTARTED          "Not started" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED      "Already started" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYON           "Already on" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYOFF          "Already off" // NOT_YET_LOCALIZED

// The rest of the network errors shouldn't really see -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         "Name too long" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      "Not initialized" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      "System not ready" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED "Version is not supported" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   "Can't send after socket shutdown" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         "Interrupted system call" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    "Authoritative Answer: Host not found" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH "Non-Authoritative: Host not found. See NETSTARTUP" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      "Non-recoverable error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNODATA              "No data record available" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       "Bad file number" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          "Operation would block" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       "Operation now in progress" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   "Operation already in progress" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKBADADDRESS          "Bad address" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     "Destination address required" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      "Message too long" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      "Protocol family not supported" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         "Directory not empty" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     "Application limit has been reached" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           "Disk quota exceeded" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        "Too many open files" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        "Access denied" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          "Socket operation on non-socket" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    "Can't assign requested address" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKADDRINUSE           "Address already in use" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      "Address family not supported by protocol family" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            "Connection timed out" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    "Socket type not supported" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   "Protocol not supported" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOBUFFER            "No space in buffer" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    "Socket is already connected" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        "Socket is not connected" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         "Bad protocol option" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     "Connection reset by peer" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     "Software caused connection abort" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKISDOWN              "Network is down" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKRESET               "Network was reset" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   "Connection refused" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          "Host is down" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   "Host is unreachable" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        "Protocol is wrong type for socket" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   "Operation not supported on socket" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         "No path to remote host was found" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         "Too many references" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_POLYSTART               "PolyStart Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "You already have a Polygon started" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_POLYEND                 "PolyEnd Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "You have not started a Polygon" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "You must have at least 3 vectors to define a polygon"  // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_SOUND                 "Sound Error" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_MIDI                  "MIDI Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "Invalid MIDI device" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "Already open" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MIDINOTOPEN           "Not open" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_MCI                   "MCI Error" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "No Text in Clipboard" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_MCI                   "MCI Error" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_TIMERTOOMANY          "Too Many Timers" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_TIMERBADID            "Bad Timer Id" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_TIMERNOTFOUND         "Timer not found" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_BITMODEBADBITMODE     "Illegal Bitmode" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       "Online help is unavailable because hhctrl.ocx could not be loaded."  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_HHCTRLATOMNOTFOUND    "Online help is unavailable because hhctrl.ocx does not contain ATOM_HTMLHELP_API_ANSI."  // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_BADCOMMANDLINE        "Invalid Command Line"  // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_TMPNOTDEFINED         "The environment variable TMP is not defined or invalid.\n"LOCALIZED_GENERAL_PRODUCTNAME" will attempt to use C:\\ for storing temporary files" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_GIFSAVEFAILED         "Problem Generating GIF, check memory and diskspace" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_GIFREADFAILED         "Problem Reading GIF, check memory and diskspace" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  "BitMap Index out of range" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPCUTFAILED        "Cut failed, Possibly not enough Memory" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPFITFAILED        "Fit failed, Possibly not enough Memory" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    "Nothing to Paste"  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  "BitMap at Index must be initialized with a bitmap"  // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_BADTURTLEID             "Bad Turtle Id" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      "Turtle %d has no picture, will Halt" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_FONTNOTFOUND            "Sorry, no font named %s was found.  Choose one of the following:\n" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_PRINTERCANTSCALE        "Print driver does not support this function"  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTDRAWIMAGE           "Cannot draw image" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        "Cannot extract image" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SUBCODE                 "Sub Code" // NOT_YET_LOCALIZED

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         "Input:" // NOT_YET_LOCALIZED
#define LOCALIZED_PROMPT_TO     "To Mode (Cancel to End)" // NOT_YET_LOCALIZED
#define LOCALIZED_PROMPT_LIST   "List Mode (Cancel to Halt)" // NOT_YET_LOCALIZED
#define LOCALIZED_PROMPT_PAUSE  "Pause Mode (Cancel to Continue)" // NOT_YET_LOCALIZED
#define LOCALIZED_PROMPT_INPUT  "Input Mode (Cancel to Halt)" // NOT_YET_LOCALIZED

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      "Changed to \"%s\"" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_CHDIRFAILED         "Could not chdir to directory \"%s\"" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_POPPEDTO            "Popped to \"%s\"" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "Now in newly created directory \"%s\""  // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_MKDIRFAILED         "Failed to create directory \"%s\""  // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "Removed directory \"%s\""  // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_RMDIRFAILED         "Failed to remove directory \"%s\""  // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "The directory does not exist." // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "Make sure the directory is empty before trying to remove it." // NOT_YET_LOCALIZED


//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "Active Area" // NOT_YET_LOCALIZED
#define LOCALIZED_INFORMATION   "Information" // NOT_YET_LOCALIZED
#define LOCALIZED_WARNING       "Warning" // NOT_YET_LOCALIZED
#define LOCALIZED_UNTITLED      "Untitled" // NOT_YET_LOCALIZED
#define LOCALIZED_UNKNOWN       "Unknown" // NOT_YET_LOCALIZED

#define LOCALIZED_UNBOUND       "Unbound" // NOT_YET_LOCALIZED

//
// Localized Strings that explain each accelerator
// I don't think that any of these strings can be seen by the user
//
#define LOCALIZED_STRINGTABLE_FILESAVEAS "Saves the contents of the EDALL window to a new file" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILEOPEN "Erases the current workspace and loads a Logo program as the new workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILELOAD "Locates and loads a Logo program into the current workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILENEW "Erases the contents of the EDALL session" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILESAVE "Saves the contents of the EDALL window" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILEEDIT "Selects a procedure to edit" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILEERASE "Selects a procedure to erase" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EXIT "Exits Logo" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPNEW "Clears the screen" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPOPEN "Loads a new screen from a Windows bitmap file" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPSAVE "Saves the contents of the screen to a bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPSAVEAS "Saves the contents of the screen to a different file" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPPRINT "Prints the contents of the screen" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPPRINTERSETUP "Configures your printer" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPPRINTERAREA "Sets the area of the screen that will be printed or saved to a bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_SETPENSIZE "Sets the thickness of the turtle's pen" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_SETFONT "Sets the font that is used by the LABEL command" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_SETCOMMANDERFONT "Sets the font used in the commander window" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_SETPENCOLOR "Sets the color of the turtle's pen" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_SETFLOODCOLOR "Sets the color used by the FILL command" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_SETSCREENCOLOR "Clears the screen and sets it to a new color" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_ZOOMIN "Zooms in on the screen" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_ZOOMOUT "Zooms out on the screen" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_ZOOMNORMAL "Restores the screen to its original size" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELP "Opens an index of help topics" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPMCI "Opens an index of help topics for the Media Control Interface" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPHELP "Opens help on using help" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPTUTORIAL "Opens a short tutorial on using "LOCALIZED_GENERAL_PRODUCTNAME // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPDEMO "Shows a demonstration of some things you can do in "LOCALIZED_GENERAL_PRODUCTNAME // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPEXAMPLES "Displays an index of the sample programs" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPRELEASENOTES "Displays the release notes for this version of "LOCALIZED_GENERAL_PRODUCTNAME // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPABOUT "Displays version and copyright information" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPABOUTMS "Displays a message about Multiple Sclerosis" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITDELETE "Deletes the current selection (and does not copy to the clipboard)" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITCLEAR "Deletes all text" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITUNDO "Undoes the previous action" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITCUT "Removes the selected text and puts it on the clipboard" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITCOPY "Copies the selected text to the clipboard" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITPASTE "Inserts the text from the clipboard at the current position" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITSELECTALL "Selects all text" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITFIND "Searches for text" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITREPLACE "Searches for text and replaces it with other text" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITFINDNEXT "Repeats the previous Find or Replace command" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITSETFONT "Sets the font for the EDALL window" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_TEST "Runs the selected Logo instructions" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPEDIT "Displays help on using the editor" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPEDIT_TOPIC "Displays help for Logo" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILESAVEANDEXIT "Saves and exits the current EDALL session" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILESAVETOWORKSPACE "Saves the current EDALL session" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILEPRINT "Prints the current EDALL session" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDALLEXIT "Closes the EDALL session" // NOT_YET_LOCALIZED

#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "Cannot find %s" // NOT_YET_LOCALIZED
