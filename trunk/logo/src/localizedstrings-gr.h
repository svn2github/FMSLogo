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
//
// For quoted strings that refer to commands, please refer to the command
// in your language, then put the English form in parentheses.  For example:
//
//   "Can't use TO inside a procedure"
//
// is translated into French as:
//
//   "Impossible d'utiliser POUR (TO) dans une proc�dure"
//
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
#define LOCALIZED_GENERAL_CANCELBUTTON  "&�����"

#define LOCALIZED_GENERAL_PRODUCTNAME   "FMSLogo"



//
// The menu options on the main window 
//
#define LOCALIZED_FILE        "&������" // 
#define LOCALIZED_FILE_NEW    "&���\t(��������� ������� ��� ����������)" // I'm sure "workspace" can have a better translation.
#define LOCALIZED_FILE_LOAD   "&�������...\t(��������� ������� ��� ���������� ��� ������)" // 
#define LOCALIZED_FILE_OPEN   "��&�����...\t(��������� ������� ��� ���������� ��� ������� ��� ��� ������)" // 
#define LOCALIZED_FILE_SAVE   "&����������"  // 
#define LOCALIZED_FILE_SAVEAS "���������� &��..." // 
#define LOCALIZED_FILE_EDIT   "&�����������..." // 
#define LOCALIZED_FILE_ERASE  "&�������..." // 
#define LOCALIZED_FILE_EXIT   "�&�����" // 

#define LOCALIZED_BITMAP               "��&����" // 
#define LOCALIZED_BITMAP_NEW           "&���" // 
#define LOCALIZED_BITMAP_LOAD          "��&�����..." // 
#define LOCALIZED_BITMAP_SAVE          "&����������" // 
#define LOCALIZED_BITMAP_SAVEAS        "���������� &��..." // 
#define LOCALIZED_BITMAP_PRINT         "&��������..." // 
#define LOCALIZED_BITMAP_PRINTERSETUP  "�&������� ���������..." // 
#define LOCALIZED_BITMAP_ACTIVEAREA    "���&��� �������..." // 

#define LOCALIZED_SET                  "&�������" // 
#define LOCALIZED_SET_PENSIZE          "&������� �����..." // 
#define LOCALIZED_SET_LABELFONT        "������������� &�������..." // 
#define LOCALIZED_SET_COMMANDERFONT    "������������� ��������� &������� (commander)..." // 
#define LOCALIZED_SET_PENCOLOR         "����� &�����..." // 
#define LOCALIZED_SET_FLOODCOLOR       "����� &����������..." // 
#define LOCALIZED_SET_SCREENCOLOR      "����� &������..." // 

#define LOCALIZED_ZOOM                 "&����"  // 
#define LOCALIZED_ZOOM_IN              "&���������" // 
#define LOCALIZED_ZOOM_OUT             "&���������" // 
#define LOCALIZED_ZOOM_NORMAL          "&��������" // 

#define LOCALIZED_HELP                 "&�������"  // 
#define LOCALIZED_HELP_INDEX           "&������ ��� �������" // 
#define LOCALIZED_HELP_MCI             "������� ��� �� &MCI" // 
#define LOCALIZED_HELP_HELP            "&����� ��������" // 
#define LOCALIZED_HELP_TUTORIAL        "&������" // Perhaps not the best one for "tutorial"
#define LOCALIZED_HELP_DEMO            "&��������"  // 
#define LOCALIZED_HELP_EXAMPLE         "&������������" // 
#define LOCALIZED_HELP_RELEASENOTES    "&���������� �������" // 
#define LOCALIZED_HELP_ABOUTFMSLOGO    "&����������� ��� ��� "LOCALIZED_GENERAL_PRODUCTNAME"..." // I have assumed here that FMSLogo would be female grammatically, as are all the programming languages in Greek
#define LOCALIZED_HELP_MS              "&����������� ��� ��� MS..." // 

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              "������� ������� ��������" // 
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       "����� �� �������� ���������� ��� �������� ��� ���������� �������" // 
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        "���� ����" // 
#define LOCALIZED_SELECTACTIVEAREA_YLOW         "���� ����"  // 
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        "���� ����" // 
#define LOCALIZED_SELECTACTIVEAREA_XLOW         "�������� ����" // 
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "������ ������� ��� ����� ��� ������������:" // 
#define LOCALIZED_SELECTACTIVEAREA_RESET        "&���������"  // 
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON // Localized above
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON // 


//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     "����&�����" // 
#define LOCALIZED_POPUP_CUT                      "��&�����" // 
#define LOCALIZED_POPUP_PASTE                    "&����������" // 
#define LOCALIZED_POPUP_DELETE                   "&��������" // 
#define LOCALIZED_POPUP_UNDO                     "�&�������" // 
#define LOCALIZED_POPUP_SELECTALL                "�&������ ����" // 
#define LOCALIZED_POPUP_HELP                     "���&������ ��� �������" // 

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   "������������" // 

#define LOCALIZED_EDITOR_FILE                    "&������" // 
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        "���������� ��� �&�����\tCtrl+D" // 
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    "���&�������" // 
#define LOCALIZED_EDITOR_FILE_PRINT              "&��������..."  // 
#define LOCALIZED_EDITOR_FILE_EXIT               "�&�����"  // 

#define LOCALIZED_EDITOR_EDIT                    "&�����������" // 
#define LOCALIZED_EDITOR_EDIT_UNDO               "�������&�\tCtrl+Z" // 
#define LOCALIZED_EDITOR_EDIT_CUT                "��&�����\tCtrl+X" // 
#define LOCALIZED_EDITOR_EDIT_COPY               "����&�����\tCtrl+C" // 
#define LOCALIZED_EDITOR_EDIT_PASTE              "&����������\tCtrl+V" // 
#define LOCALIZED_EDITOR_EDIT_DELETE             "&��������\tDel" // 
#define LOCALIZED_EDITOR_EDIT_CLEARALL           "��&�������� ����\tCtrl+Del" // 
#define LOCALIZED_EDITOR_EDIT_SELECTALL          "�&������ ����\tCtrl+A" // 

#define LOCALIZED_EDITOR_SEARCH                  "���&������" // 
#define LOCALIZED_EDITOR_SEARCH_FIND             "��&����...\tCtrl+F" // 
#define LOCALIZED_EDITOR_SEARCH_REPLACE          "����&���������...\tCtrl+H"  // 
#define LOCALIZED_EDITOR_SEARCH_NEXT             "�&������\tF3"  // 

#define LOCALIZED_EDITOR_SET                     "&�������"  // 
#define LOCALIZED_EDITOR_SET_FONT                "&�������������..."  // 

#define LOCALIZED_EDITOR_TEST                    "������!" // 

#define LOCALIZED_EDITOR_HELP                    "&�������"  // 
#define LOCALIZED_EDITOR_HELP_INDEX              "&������ ��� �������" // 
#define LOCALIZED_EDITOR_HELP_EDITOR             "���&���������" // 
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        "���&������ �������\tF1" // 


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES //
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    "���&������� ��� ������" // 
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       "����� ����������" // 
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON // 
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       "�������� ������� ��� ��� ����� �����������.  �� ��� ��� ������������, ����� �� ������� �� ������.  " // 
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       "������ �� ������������ ��� ������� ��� ���� ��� �����;"  // 


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     "�������� �������" // 
#define LOCALIZED_COMMANDER_HALT                "���������" // 
#define LOCALIZED_COMMANDER_TRACE               "���������" // 
#define LOCALIZED_COMMANDER_NOTRACE             "�����" // 
#define LOCALIZED_COMMANDER_PAUSE               "�����" // 
#define LOCALIZED_COMMANDER_STATUS              "���������" // 
#define LOCALIZED_COMMANDER_NOSTATUS            "�����" // 
#define LOCALIZED_COMMANDER_STEP                "����" // 
#define LOCALIZED_COMMANDER_UNSTEP              "�����" // 
#define LOCALIZED_COMMANDER_RESET               "���������" // 
#define LOCALIZED_COMMANDER_EXECUTE             "��������" // 
#define LOCALIZED_COMMANDER_EDALL               "�����������" // If that's too long, please replace it again with EDALL

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        "���������" // 
#define LOCALIZED_STATUS_PEN                    "����" // 
#define LOCALIZED_STATUS_CONTACT                "�����:" // 
#define LOCALIZED_STATUS_WIDTH                  "������:" // 
#define LOCALIZED_STATUS_STYLE                  "����:" // 
#define LOCALIZED_STATUS_ORIENTATION            "���������������" // 
#define LOCALIZED_STATUS_PITCH                  "�����:" // 
#define LOCALIZED_STATUS_HEADING                "����������:" // 
#define LOCALIZED_STATUS_ROLL                   "������:" // 
#define LOCALIZED_STATUS_TURTLE                 "������" // 
#define LOCALIZED_STATUS_POSITION               "���� (XYZ):" // XYZ is fine :P
#define LOCALIZED_STATUS_WHICH                  "������:" // 
#define LOCALIZED_STATUS_VISIBILITY             "���������:" // 
#define LOCALIZED_STATUS_COLOR                  "�����" // 
#define LOCALIZED_STATUS_PENCOLOR               "���� (���):" // Maybe a teacher would recognize RGB more easily than the Greek equivalent, but I've translated it anyway.
#define LOCALIZED_STATUS_FLOODCOLOR             "������� (���):" // 
#define LOCALIZED_STATUS_SCREENCOLOR            "����� (���):" // 
#define LOCALIZED_STATUS_PALETTE                "������:" // 
#define LOCALIZED_STATUS_KERNEL                 "�������" // 
#define LOCALIZED_STATUS_CALLS                  "�������:" // 
#define LOCALIZED_STATUS_PEAKMEMORY             "�����:" // 

#define LOCALIZED_STATUS_PENREVERSE  "����������" // 
#define LOCALIZED_STATUS_PENNORMAL   "��������" // 
#define LOCALIZED_STATUS_PENERASE    "�������" // 
#define LOCALIZED_STATUS_PENUP       "����" // 
#define LOCALIZED_STATUS_PENDOWN     "����" // 
#define LOCALIZED_STATUS_PENSHOWN    "�����" //  
#define LOCALIZED_STATUS_PENHIDDEN   "������" // 
#define LOCALIZED_STATUS_POLYGONS    "��������" // 
#define LOCALIZED_STATUS_VECTORS     "����������" // 
#define LOCALIZED_STATUS_NODES       "������" // 

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           "&����"
#define LOCALIZED_ERASEPROCEDURE                "������� �������"
#define LOCALIZED_EDITPROCEDURE                 "����������� �������"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     "������� ��������" // 
#define LOCALIZED_SETCOLOR_RED                 "�������" // 
#define LOCALIZED_SETCOLOR_GREEN               "�������" // 
#define LOCALIZED_SETCOLOR_BLUE                "�������" // 
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON // 
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON // 

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   "������� �����" // 
#define LOCALIZED_SETPENSIZE_SIZE              "�������" // 
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     "����������� ��� ��� "LOCALIZED_GENERAL_PRODUCTNAME // 
#define LOCALIZED_ABOUTFMS_VERSION             LOCALIZED_GENERAL_PRODUCTNAME", ������ "FMSLOGO_VERSION // 
#define LOCALIZED_ABOUTFMS_GUI                 "GUI ��� ��� George Mills (mills@softronix.com)\nSoftronics, Inc.\nhttp:\x2F/www.softronix.com/" // 
#define LOCALIZED_ABOUTFMS_CORE                "������� ��� ��� Brian Harvey (bh@cs.berkeley.edu)\nUniversity of California Berkeley" // 
#define LOCALIZED_ABOUTFMS_INSTALLER           "������������ ���������� ��� Nullsoft Scriptable Install System\nhttp:\x2F/nsis.sourceforge.net" // 
#define LOCALIZED_ABOUTFMS_ADVENTURE           "The Great Logo Adventure (ISBN 0-9651934-6-2)\n�������� ��� ��������� ��� ��� Jim Muller\n��������� ��� http:\x2F/www.softronix.com/" // 
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "������������ ���� Yehuda Katz (yehuka@softhome.net)\n��� Erich Neuwirth (erich.neuwirth@univie.ac.at)" // 
#define LOCALIZED_ABOUTFMS_GPL                 "� "LOCALIZED_GENERAL_PRODUCTNAME" ����� �������� ���������\n����� �� GNU Public License" // I dared to add a string ("H ") before the PRODUCTNAME constant :P
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "News Group ��� ���������: comp.lang.logo\n������������ �� Logo-Forum ���\nhttp:\x2F/groups.yahoo.com/group/LogoForum/" // 
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "��������� ��� ��������:\n������� �������������� (teo64x@yahoo.gr)" // 
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON // 


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "����������� ��� �� FMS" // 
#define LOCALIZED_ABOUTMS_FMS                  "FMS �������� Fight Multiple Sclerosis." // Maybe someone should give an accurate translation of Multiple Sclerosis
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "Please consider donating to the\nNational Multiple Sclerosis Society.\nhttp:\x2F/www.nmss.org\n1-800-FIGHT-MS" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTMS_OK                   LOCALIZED_GENERAL_OKBUTTON // 


// 
// Strings in various other dialog boxes
// 

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "������� �� ���� ��� ������� ����������� ���� ������.\n\n������ ���������� �� �������� ��� "LOCALIZED_GENERAL_PRODUCTNAME";" // 
#define LOCALIZED_EDITSESSIONISRUNNING      "� ������������ ������ ����� ��� ��������" // 

#define LOCALIZED_NOTHALTEDREALLYEXIT        "���� "LOCALIZED_GENERAL_PRODUCTNAME" ��� ������ �� ������� ���� ����������.\n\n������ ���������� �� ������� � "LOCALIZED_GENERAL_PRODUCTNAME"?" // 
#define LOCALIZED_NOTHALTEDREALLYHALT        "���� "LOCALIZED_GENERAL_PRODUCTNAME" ��� ������ �� ������� ���� ����������.\n\n������ ���������� �� ���������� � "LOCALIZED_GENERAL_PRODUCTNAME"?" // 
#define LOCALIZED_LOGOISNOTHALTED            "� "LOCALIZED_GENERAL_PRODUCTNAME" �� ���������" // 

#define LOCALIZED_WRITEFAILEDNOMEMORY         "� ������� �������. ���� ��� ������� ������ �������� �����." // 
#define LOCALIZED_COULDNOTWRITEBMP            "������� � ������� ��� .bmp" // 
#define LOCALIZED_COULDNOTOPENBMP             "������� � �������� ��� �� .bmp" // 
#define LOCALIZED_COULDNOTCREATEBMP           "������� �� ������������ � ������ Windows 3.0 bitmap" // 
#define LOCALIZED_NOTVALIDBMP                 "� ����� ��� ����� Windows 3.0 bitmap" // 

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "��� ������������ ��� �����" // 
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "� �������� ���� ���� ������� �� ������ ��� ���������� ������� ��� ����������.\n\n��������;" // 
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "�� ������ ��� ���������� �� ��������� ���� ���������� ������� ��� ����������\n��� ���� ������ ������ ������� ��� ����� �����������.\n\n��������;" // 
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "���� �� ������ ���� ��� ������� ��� ��� ����� �����������.\n\n��������;" // 

#define LOCALIZED_EDITORISOPEN                  "������ ��� ��� ����� ��� ������� ������������ �������;\n\n����������� ������ �� ���� ��� ������� �� �� �����������." // 

#define LOCALIZED_ERROR_CANTREADFILE            "�������� ��������� ��� ������� \"%s\" ��� �� �����" // 
#define LOCALIZED_ERROR_CANTWRITEFILE           "�������� �������� ��� ������� \"%s\" ��� �����" // 

#define LOCALIZED_SAVEISFOREXPERTSONLY          "���� � ���������� ����� ���� ��� �� expert mode (�������������� �� "LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT")" // 
#define LOCALIZED_SAVETOWORKSPACE                "����������" // 
#define LOCALIZED_CONTENTSCHANGED                "�� ����������� �������" // 
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "�� ����������� ����� �������.\n������ �� �� ������������;" // 



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "� ������� �� ����������� ���� ��� ��������� ����������� ������.\n������� �� �������� ������� ��� ������ ������ ������." // 
#define LOCALIZED_RETURNTOEDIT                  "��������� ���� �����������;" // 

#define LOCALIZED_EDITFAILEDTOLOAD              "� ����������� ��� ������� �� ��������" // Isn't the use of capitals like shouting to the programmer for making a mistake? ;P



// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILEFILTER_ALLFILES "��� �� ������ (*.*)|*.*|" // 
#define LOCALIZED_FILEFILTER_LOGO     "������ Logo (*.lgo)|*.lgo|"LOCALIZED_FILEFILTER_ALLFILES // 
#define LOCALIZED_FILEFILTER_IMAGE    "������ ������� Bitmap (*.bmp)|*.bmp|������ ������� GIF (*.gif)|*.gif|"LOCALIZED_FILEFILTER_ALLFILES // 



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             " ���������\n" // 
#define LOCALIZED_TRACING_OUTPUTS           " ���������� %s\n" // 
#define LOCALIZED_TRACING_MAKE              "��������� %s %s"  // 
#define LOCALIZED_TRACING_PPROP             "�������� %s %s %s" // 
#define LOCALIZED_TRACING_LOCATION          " ��� %s\n%s" // 

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  "����-����" // NOT_YET_LOCALIZED

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "%s ��������\n" // 


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "�������" // 
#define LOCALIZED_PENMODE_REVERSE  "����������" // 
#define LOCALIZED_PENMODE_PAINT    "����������" // 

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          "Logo: ��������� ������" // 
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       "Logo: ���������� ������" // 
#define LOCALIZED_ERROR_OUTOFMEMORY            "���������� ������" // 
#define LOCALIZED_ERROR_STACKOVERFLOW          "����������� �������" // 
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      "������ ����� �����" // 
#define LOCALIZED_ERROR_BADGRAPHINIT           "�������� ��������� ��������" // 
#define LOCALIZED_ERROR_BADDATA                "��� %p ��� ������ �� %s �� ����������" // 
#define LOCALIZED_ERROR_DIDNTOUTPUT            "�� %p ��������� ���� ��� �� %p" // 
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        "���������� ���������� ��� �� %p" // 
#define LOCALIZED_ERROR_TOOMUCH                "���������� ������ ��������� ������� ��� ()" // 
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    "��� ����� �� �� ���� �� �� %s" // 
#define LOCALIZED_ERROR_PARENMISMATCH          "���������� ����� ('s" // 
#define LOCALIZED_ERROR_NOVALUE                "�� %s ��� ���� ����" // 
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        "�� ������������ ')'" // 
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      "�� ������������ ']'" // 
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        "�� ������������ '}'" // 
#define LOCALIZED_ERROR_DONTKNOWHOWTO          "��� ���� �� %p" // 
#define LOCALIZED_ERROR_NOCATCHTAG             "�� ����� �� ��� ������� ��������� ��� �� %p" // 
#define LOCALIZED_ERROR_ALREADYDEFINED         "�� %p ���� ��� �������" // 
#define LOCALIZED_ERROR_STOPPING               "���������..." // 
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "������� ��� ���������" // 
#define LOCALIZED_ERROR_FILESYSTEM                   "������ ���������� �������: %p" // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "�������� ����������" // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "�������� ���������� ��� %t" // 
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "�� ������ ����� ��� �������" // 
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "�� ������ ��� ����� �������" // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "�������� ���������� ��� ������� ����������� ������"// 
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "�������� ���������� ��� ����������� ������"  // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "�������� ��������� ��� ������� ����������� ������"  // 
#define LOCALIZED_ERROR_IFWARNING              "����� ��� ��������� IFELSE, ��� IF" // This should change a little when primitives are localized
#define LOCALIZED_ERROR_SHADOWWARNING          "�� %p ������������ ��� ������ ���� ����� ��� �������" // I could make it a little more accurate if I knew whether it refers to a variable or something else
#define LOCALIZED_ERROR_USER                   "Throw \"Error" // 
#define LOCALIZED_ERROR_ISPRIMITIVE            "�� %p ����� ����������� ������" // 
#define LOCALIZED_ERROR_TONOTINSIDE            "������� � ����� ��� TO ���� �� ������" // But why? :D
#define LOCALIZED_ERROR_ATTOPLEVEL             "�� %p ��������������� ���� ���� �� �������" // 
#define LOCALIZED_ERROR_ATTOPLEVEL2            "�������� �� ��������������� OUTPUT � STOP ���� ���� �� ������" // 
#define LOCALIZED_ERROR_NOTEST                 "%p ����� TEST" // 
#define LOCALIZED_ERROR_BADMACROOUTPUT         "� ����������� ��������� %s ���� ��� �����" // 
#define LOCALIZED_ERROR_DEEPEND                "�� END ��������� ���� �� ������ ��������� �������" // 
#define LOCALIZED_ERROR_DEEPENDIN              "�� END ��������� ���� �� ������ ��������� ������� ��� %p" // 
#define LOCALIZED_ERROR_UNKNOWN                "������� ��������� ��������� - ��������� ������." // 

#define LOCALIZED_PAUSING                      "�����..." // 


//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "������" // 
#define LOCALIZED_ERROR_BADINPUT             "���� ����������" // 
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    "� ���������� ��� ���������" // 

#define LOCALIZED_ERROR_CANTOPENPORT         "������� �� ������� ��� �����" // 
#define LOCALIZED_ERROR_CANTCLOSEPORT        "������� �� �������� ��� �����" // 
#define LOCALIZED_ERROR_CANTFLUSHPORT        "������� �� �������� ��� �����" // 
#define LOCALIZED_ERROR_CANTDCBONPORT        "������� � ���������� dcb ��� ����" // 
#define LOCALIZED_ERROR_CANTSETPORT          "������� � ������� ��� �����" // 
#define LOCALIZED_ERROR_PORTALREADYOPEN      "� ���� ����� ��� �������" // 
#define LOCALIZED_ERROR_PORTNOTOPEN          "� ���� ��� ����� �������" // 
#define LOCALIZED_ERROR_FIRSTINPUTNOTANARRY  "� ����� ���������� ������ �� ����� ������� (array)" // 

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "������� ���" // 
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "��� �������" // 

#define LOCALIZED_ERROR_DLL                   "������ DLL" // 
#define LOCALIZED_ERROR_DLLNOTLOADED          "�� DLL ��� ���� ��������" // 
#define LOCALIZED_ERROR_DLLALREADYLOADED      "�� DLL ���� ��� ��������" // 
#define LOCALIZED_ERROR_DLLLOADFAILED         "� ������� ��� DLL �������" // 
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "������ ����� ���������" // 
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "������ ����� ����������" // 
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "� ��������� �� �������" // 
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "��� ����������� ���� �� ���������� �����/���������" // 

#define LOCALIZED_ERROR_NETWORK                    "������ �������" // 
#define LOCALIZED_ERROR_NETWORKRECEIVE             "������ �������� ��� �� ������" // 
#define LOCALIZED_ERROR_NETWORKSEND                "������ ��������� ��� ������" // 
#define LOCALIZED_ERROR_NETWORKSHUTDOWN            "�� ������������ ������, ���� �� ������ �� �������" // 
#define LOCALIZED_ERROR_NETWORKNOTSTARTED          "��� ������" // 
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED      "���� ��� �������" // 
#define LOCALIZED_ERROR_NETWORKALREADYON           "��� �������" // 
#define LOCALIZED_ERROR_NETWORKALREADYOFF          "��� �������" // 

// The rest of the network errors shouldn't really see -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         "���� ������ �����" // 
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      "��� ������" // 
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      "�� ������� ��� ����� ������" // 
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED "� ������ ��� �������������" // 
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   "������� � �������� ���� �� �������� ��� ��������" // 
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         "� ����� ���������� ���������" // 
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    "������� ��������: �� ������� � ��������� �����������" // 
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH "���������: �� ������� � ��������� �����������. ����� �� NETSTARTUP" // 
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      "�� ��������� ������" // 
#define LOCALIZED_ERROR_NETWORKNODATA              "��� ������� ������� ���������" // 
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       "����� ������� �������" // 
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          "� ���������� �� ��������" // 
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       "� ���������� ���������� ����" // 
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   "� ���������� ���������� ���" // 
#define LOCALIZED_ERROR_NETWORKBADADDRESS          "���� ���������" // 
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     "���������� ��������� ����������" // 
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      "�� ������ ����� ���� ������" // 
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      "� ���������� ����������� ��� �������������" // 
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         "� ��������� ��� ����� ������" // 
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     "���� ���������" // 
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           "� �������� ������ �����������" // 
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT // 
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        "����� ������� ������" // 
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        "� �������� ������������" // 
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          "���������� �������� �� �� �������" // 
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    "������� � �������� ��� ���������� �����������" // 
#define LOCALIZED_ERROR_NETWORKADDRINUSE           "� ��������� ��������������� ���" // 
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      "� ���������� ����������� ��� ������������� ��� ��� ���������� �����������" // 
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            "� ������ �������� �����" // 
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    "� ����� �������� ��� �������������" // 
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   "� ����� ����������� ��� �������������" // 
#define LOCALIZED_ERROR_NETWORKNOBUFFER            "��� ������� ����� ���� ��������� ����� (buffer)" // 
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    "� ������� ����� ��� �����������" // 
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        "� ������� ��� ����� �����������" // 
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         "���� ������� ��� ����������" // 
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     "� ������� ��������" // 
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     "�� ��������� ��������� �������� ��� ��������" // 
#define LOCALIZED_ERROR_NETWORKISDOWN              "�� ������ �� ����������" // 
#define LOCALIZED_ERROR_NETWORKRESET               "�� ������ ��������" // 
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   "� ������� ��� ����� �����" // 
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          "� ��������� ����������� �� ����������" // 
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   "������� � ����� �� ��� �������� ����������" // 
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        "�� ���������� ����� ����� ����� ��� ��� �������" // 
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   "� ���������� ��� ������������� ���� �������" // 
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         "�� ������� �������� ���� ������������� �������� ����������" // 
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         "���������� ������ ��������" // 

#define LOCALIZED_ERROR_POLYSTART               "������ PolyStart" // 
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "����� ��� ��������� ��� ��������" // 

#define LOCALIZED_ERROR_POLYEND                 "������ PolyEnd" // 
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "��� ����� ��������� ��������" // 
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "���������� ����������� 3 ���������� ��� �� ������� ��� ��������" // 

#define LOCALIZED_ERROR_SOUND                 "������ ����" // 

#define LOCALIZED_ERROR_MIDI                  "������ MIDI" // 
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "����� ������� MIDI" // 
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "����� ��� �������" // 
#define LOCALIZED_ERROR_MIDINOTOPEN           "��� ����� �������" // 

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "��� ������� ������� ��� ��������" // 

#define LOCALIZED_ERROR_MCI                   "������ MCI" // 

#define LOCALIZED_ERROR_TIMERTOOMANY          "���������� ������ ��������������" // 
#define LOCALIZED_ERROR_TIMERBADID            "����� ������� �������������" // 
#define LOCALIZED_ERROR_TIMERNOTFOUND         "� �������������� �� �������" // 

#define LOCALIZED_ERROR_BITMODEBADBITMODE     "����� BitMode" // 

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       "� online ������� ��� ����� ��������� ����� �� hhctrl.ocx �� ���������."  // 
#define LOCALIZED_ERROR_HHCTRLATOMNOTFOUND    "� online ������� ��� ����� ��������� ����� �� hhctrl.ocx ��� �������� ATOM_HTMLHELP_API_ANSI."  // 

#define LOCALIZED_ERROR_BADCOMMANDLINE        "����� ������ ������� �������"  // 

#define LOCALIZED_ERROR_TMPNOTDEFINED         "� ��������� ������������� TMP ��� ���� ������� � ����� �����.\n� "LOCALIZED_GENERAL_PRODUCTNAME" �� ����������� �� �������������� �� C:\\ ��� ��� ���������� ���������� �������" // 

#define LOCALIZED_ERROR_GIFSAVEFAILED         "������� � ���������� ��� GIF, ������� �� ����� ��� �� ���� ��� �����" // 
#define LOCALIZED_ERROR_GIFREADFAILED         "������� � �������� ��� GIF, ������� �� ����� ��� �� ���� ��� �����" // 

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  "� ������� BitMap ����� ����� �����" // 
#define LOCALIZED_ERROR_BITMAPCUTFAILED        "� ������� (cut) �������, ���� ��� ������� ������ �����" // 
#define LOCALIZED_ERROR_BITMAPFITFAILED        "� ���������� (fit) �������, ���� ��� ������� ������ �����" // 

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    "��� ������� ������ ��� ����������"  // 
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  "�� BitMap ���� �������� ������ �� ���� ��������� �� ��� ������"  // 

#define LOCALIZED_ERROR_BADTURTLEID             "����� ������� �������" // 
#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      "� ������ %d ��� ���� ������, �� ����������" // 

#define LOCALIZED_ERROR_FONTNOTFOUND            "� ������������� %s �� �������.  �������� ��� ��� ��� ��������:\n" // 

#define LOCALIZED_ERROR_PRINTERCANTSCALE        "� ������ ��� �������� ��� ����������� ���� �� ����������."  // 
#define LOCALIZED_ERROR_CANTDRAWIMAGE           "� ������ �� ������ �� ����������" // 
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        "� ������ �� ������ �� �������" // 
#define LOCALIZED_ERROR_SUBCODE                 "����������" // 

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         "����������:" // 
#define LOCALIZED_PROMPT_TO     "������� To (������� ��� End)" // 
#define LOCALIZED_PROMPT_LIST   "������� List (������� ��� ���������)" // 
#define LOCALIZED_PROMPT_PAUSE  "������� Pause (������� ��� ��������)" // 
#define LOCALIZED_PROMPT_INPUT  "������� Input (������� ��� ���������)" // 

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      "������� ���� �������� \"%s\"" // 
#define LOCALIZED_FILE_CHDIRFAILED         "������� � ������� ��� �������� \"%s\"" // 
#define LOCALIZED_FILE_POPPEDTO            "������ ���� �������� \"%s\"" // 
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "������� ��� ��� �������� \"%s\""  // 
#define LOCALIZED_FILE_MKDIRFAILED         "�������� ����������� ��� ��������� \"%s\""  // 
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "���������� ��������� \"%s\""  // 
#define LOCALIZED_FILE_RMDIRFAILED         "�������� ��������� ��� ��������� \"%s\""  // 
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "� ��������� ��� �������" // 
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "������������� ��� � ��������� ����� ������ ���� ������������ �� ��� ����������." // 


//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "������ �������" // 
#define LOCALIZED_INFORMATION   "�����������" // 
#define LOCALIZED_WARNING       "�������" // 
#define LOCALIZED_UNTITLED      "����� �����" // 
#define LOCALIZED_UNKNOWN       "�������" // 

#define LOCALIZED_UNBOUND       "(����� �����)" // 

//
// Localized Strings that explain each accelerator
// I don't think that any of these strings can be seen by the user
//
#define LOCALIZED_STRINGTABLE_FILESAVEAS "���������� ��� ������ ��� ��� ���������� �� ��� ������" // 
#define LOCALIZED_STRINGTABLE_FILEOPEN "������ ��� �������� ������ ��� �������� ��� ��� ������" // 
#define LOCALIZED_STRINGTABLE_FILELOAD "��������� ��� �������� ��� ��������� Logo, ������������ �� ���� ��������� ������" // 
#define LOCALIZED_STRINGTABLE_FILENEW "������ ��� ��� ������" // 
#define LOCALIZED_STRINGTABLE_FILESAVE "���������� ��� ��� ������" // 
#define LOCALIZED_STRINGTABLE_FILEEDIT "������� ���� ������� ���� �����������" // 
#define LOCALIZED_STRINGTABLE_FILEERASE "������� ���� ������� ���� ��������" // 
#define LOCALIZED_STRINGTABLE_EXIT "������� �� Logo" // 
#define LOCALIZED_STRINGTABLE_BITMAPNEW "��������� �� �����" // 
#define LOCALIZED_STRINGTABLE_BITMAPOPEN "�������� ��� ������ Windows bitmap" // 
#define LOCALIZED_STRINGTABLE_BITMAPSAVE "���������� �� ����������� ��� ������ �� ��� ������ bitmap" // 
#define LOCALIZED_STRINGTABLE_BITMAPSAVEAS "���������� �� ����������� ��� ������ �� ���� ������" // 
#define LOCALIZED_STRINGTABLE_BITMAPPRINT "��������� �� ����������� ��� ������" // 
#define LOCALIZED_STRINGTABLE_BITMAPPRINTERSETUP "�������� ��� �������� ���" // 
#define LOCALIZED_STRINGTABLE_BITMAPPRINTERAREA "�������� ��� ������� ��� ������ ��� �� ��������� � �� �����������" // 
#define LOCALIZED_STRINGTABLE_SETPENSIZE "�������� �� ����� ��� ����� ��� �������" // 
#define LOCALIZED_STRINGTABLE_SETFONT "�������� �� ������������� ��� ��������������� ��� ��� ������ LABEL" // 
#define LOCALIZED_STRINGTABLE_SETCOMMANDERFONT "�������� �� ������������� ��� ��������������� ��� �������� �������" // 
#define LOCALIZED_STRINGTABLE_SETPENCOLOR "�������� �� ����� ��� ����� ��� �������" // 
#define LOCALIZED_STRINGTABLE_SETFLOODCOLOR "�������� �� ����� ��� ��������������� ��� ��� ������ FILL" // 
#define LOCALIZED_STRINGTABLE_SETSCREENCOLOR "��������� ��� ����� ��� ��� ����� ��� ����������� �����" // 
#define LOCALIZED_STRINGTABLE_ZOOMIN "��������� ��� �����" // 
#define LOCALIZED_STRINGTABLE_ZOOMOUT "��������� ��� �����" // 
#define LOCALIZED_STRINGTABLE_ZOOMNORMAL "���������� ��� ����� ��� �������� ��� �������" // 
#define LOCALIZED_STRINGTABLE_HELP "������� ���� �������� �� ������ ��� �������" // 
#define LOCALIZED_STRINGTABLE_HELPMCI "������� ���� �������� �� ������ ��� ������� ��� �� Media Control Interface" // 
#define LOCALIZED_STRINGTABLE_HELPHELP "������� ������� ������� �� �� ����� ��� ��������" // 
#define LOCALIZED_STRINGTABLE_HELPTUTORIAL "������� ��� ����� ������ ������� �� �� ����� ��� "LOCALIZED_GENERAL_PRODUCTNAME // 
#define LOCALIZED_STRINGTABLE_HELPDEMO "����� ��� �������� ��� �� �������� �� ������ ���� "LOCALIZED_GENERAL_PRODUCTNAME // 
#define LOCALIZED_STRINGTABLE_HELPEXAMPLES "��������� ���� �������� �� �����������-��������" // 
#define LOCALIZED_STRINGTABLE_HELPRELEASENOTES "��������� ��� ���������� ����� ��� ������� ��� "LOCALIZED_GENERAL_PRODUCTNAME // 
#define LOCALIZED_STRINGTABLE_HELPABOUT "��������� ��� ������ ��� ����������� copyright" // 
#define LOCALIZED_STRINGTABLE_HELPABOUTMS "��������� ��� ������ ������� �� �� Multiple Sclerosis" // 
#define LOCALIZED_STRINGTABLE_EDITDELETE "��������� ��� �������� ������� (��� ��� ���������� ��� ��������)" // 
#define LOCALIZED_STRINGTABLE_EDITCLEAR "��������� ��� �� �������" // 
#define LOCALIZED_STRINGTABLE_EDITUNDO "������� ��� ����������� ��������" // 
#define LOCALIZED_STRINGTABLE_EDITCUT "������� �� ���������� ������� ��� �� ��������� ��� ��������" // 
#define LOCALIZED_STRINGTABLE_EDITCOPY "���������� �� ���������� ������� ��� ��������" // 
#define LOCALIZED_STRINGTABLE_EDITPASTE "������� �� ������� ��� �� �������� ���� �������� ����" // 
#define LOCALIZED_STRINGTABLE_EDITSELECTALL "�������� ��� �� �������" // 
#define LOCALIZED_STRINGTABLE_EDITFIND "������ ��� �������" // 
#define LOCALIZED_STRINGTABLE_EDITREPLACE "������ ��� ������� ��� �� ����������� �� ���� �������" // 
#define LOCALIZED_STRINGTABLE_EDITFINDNEXT "������������� ��� ��������� ������ ������� � ��������������" // 
#define LOCALIZED_STRINGTABLE_EDITSETFONT "�������� �� ������������� ��� ��� ����������� ������" // 
#define LOCALIZED_STRINGTABLE_TEST "������� ��� ����������� ������� Logo " // 
#define LOCALIZED_STRINGTABLE_HELPEDIT "��������� ������� ��� �� ����� ��� ����������� ������" // 
#define LOCALIZED_STRINGTABLE_HELPEDIT_TOPIC "��������� ������� ��� �� Logo" // 
#define LOCALIZED_STRINGTABLE_FILESAVEANDEXIT "���������� ��� ������ ��� ������� ��� ����������� ������" // 
#define LOCALIZED_STRINGTABLE_FILESAVETOWORKSPACE "���������� ��� ������" // 
#define LOCALIZED_STRINGTABLE_FILEPRINT "��������� ��� ������" // 
#define LOCALIZED_STRINGTABLE_EDALLEXIT "������� ��� ����������� ������" // 

#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "{ �� ������� �� %s }" // 
