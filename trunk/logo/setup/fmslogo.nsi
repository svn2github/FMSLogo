;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Filename    : fmslogo.nsi
; Description : The NSIS installer script that builds the FMSLogo's installer.
;
; Localization Instructions: 
; 
;   1) If there are no place-holders for your language, then open a feature
;   request on the FMSLogo project asking someone to add the place-holders.
;
;   2) Once the place-holders exist, Search the file for the NOT_YET_LOCALIZED
;   markers, which will be next to the strings that should be localized.
;   Localize the bit within the double-quotes that corresponds to your language.
;
;   After you translate the string, delete the NOT_YET_LOCALIZED marker.
; 
;   Note that the some characters with the strings must be escaped with a 
;   dollar-sign ($).
;
;     dollar-sign      -> $$ 
;     carriage-return  -> $\r 
;     newline          -> $\n
;     tab              -> $\t
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

!include LogicLib.nsh
!include x64.nsh

; Compiler Flags
SetCompressor /SOLID lzma

; The name of the installer
Name "FMSLogo"

; The file to write
OutFile "fmslogo.exe"

; Use an XP manifest
XPStyle on

; Add a Vista manifest for UAC that requests admin rights, if available.
RequestExecutionLevel highest

; The default installation directory
InstallDir "$PROGRAMFILES\FMSLogo"

; Registry key to check for directory 
; (so if you install again, it will overwrite the old one automatically)
InstallDirRegKey HKLM "Software\FMSLogo" "Install_Dir"

!define /date COPYRIGHT_YEAR "%Y"
VIAddVersionKey "ProductName"     "FMSLogo"
VIAddVersionKey "ProductVersion"  "${FMSLOGO_VERSION}"
VIAddVersionKey "FileDescription" "FMSLogo installer"
VIAddVersionKey "LegalCopyright"  "Copyright (C) ${COPYRIGHT_YEAR} by David Costanzo"
VIAddVersionKey "CompanyName"     "David Costanzo"
VIAddVersionKey "FileVersion"     "${FMSLOGO_VERSION}"

VIProductVersion ${FMSLOGO_MAJOR_VERSION}.${FMSLOGO_MINOR_VERSION}.${FMSLOGO_MICRO_VERSION}.0

;--------------------------------

; Pages

Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

; variables
var previousinstalldir ; full path to the uninstaller

; Languages
LoadLanguageFile "${NSISDIR}\Contrib\Language files\English.nlf"  ; the default language
LoadLanguageFile "${NSISDIR}\Contrib\Language files\German.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Italian.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Spanish.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\French.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Greek.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Portuguese.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Russian.nlf"

LangString DesktopShortcut ${LANG_ENGLISH}    "Desktop Shortcut"
LangString DesktopShortcut ${LANG_GERMAN}     "Desktop Shortcut" ; NOT_YET_LOCALIZED
LangString DesktopShortcut ${LANG_SPANISH}    "Desktop Shortcut" ; NOT_YET_LOCALIZED
LangString DesktopShortcut ${LANG_ITALIAN}    "Collegamento sul Desktop"
LangString DesktopShortcut ${LANG_PORTUGUESE} "Atalho no Desktop"
LangString DesktopShortcut ${LANG_FRENCH}     "Raccourci Bureau" 
LangString DesktopShortcut ${LANG_GREEK}      "”хнфьмехуз ≈рйц№нейбт ≈сгбуябт"
LangString DesktopShortcut ${LANG_RUSSIAN}    "ярлык рабочего стола" 

LangString StartMenuShortcuts ${LANG_ENGLISH}    "Start Menu Shortcuts"
LangString StartMenuShortcuts ${LANG_GERMAN}     "Start Menu Shortcuts" ; NOT_YET_LOCALIZED
LangString StartMenuShortcuts ${LANG_SPANISH}    "Start Menu Shortcuts" ; NOT_YET_LOCALIZED
LangString StartMenuShortcuts ${LANG_ITALIAN}    "Collegamento nel Menu Start"
LangString StartMenuShortcuts ${LANG_PORTUGUESE} "Atalho no Menu Iniciar"
LangString StartMenuShortcuts ${LANG_FRENCH}     "Raccourcis Menu Dйmarrer" 
LangString StartMenuShortcuts ${LANG_GREEK}      "”хнфпмеэуейт ћенпэ Єнбсоз" 
LangString StartMenuShortcuts ${LANG_RUSSIAN}    "ярлык меню ѕуск" 

LangString ScreenSaver ${LANG_ENGLISH}    "Screen Saver"
LangString ScreenSaver ${LANG_GERMAN}     "Screen Saver" ; NOT_YET_LOCALIZED
LangString ScreenSaver ${LANG_SPANISH}    "Screen Saver" ; NOT_YET_LOCALIZED
LangString ScreenSaver ${LANG_ITALIAN}    "Screen Saver" ; NOT_YET_LOCALIZED
LangString ScreenSaver ${LANG_PORTUGUESE} "Screen Saver" ; NOT_YET_LOCALIZED
LangString ScreenSaver ${LANG_FRENCH}     "Screen Saver" ; NOT_YET_LOCALIZED 
LangString ScreenSaver ${LANG_GREEK}      "Screen Saver" ; NOT_YET_LOCALIZED 
LangString ScreenSaver ${LANG_RUSSIAN}    "Screen Saver" ; NOT_YET_LOCALIZED 

; uninstall must be able to remove all traces of any previous installation.
Function uninstall

  ; Remove registry keys
  DeleteRegKey SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo"

  ; Remove files and uninstaller
  Delete $previousinstalldir\fmslogo.exe
  Delete $previousinstalldir\fmslogo-${LANG_ENGLISH}.exe
  Delete $previousinstalldir\fmslogo-${LANG_GERMAN}.exe
  Delete $previousinstalldir\fmslogo-${LANG_SPANISH}.exe
  Delete $previousinstalldir\fmslogo-${LANG_ITALIAN}.exe
  Delete $previousinstalldir\fmslogo-${LANG_PORTUGUESE}.exe
  Delete $previousinstalldir\fmslogo-${LANG_GREEK}.exe
  Delete $previousinstalldir\fmslogo-${LANG_FRENCH}.exe
  Delete $previousinstalldir\fmslogo-${LANG_RUSSIAN}.exe

  Delete $previousinstalldir\startup.logoscript
  Delete $previousinstalldir\startup-${LANG_ENGLISH}.logoscript
  Delete $previousinstalldir\startup-${LANG_GERMAN}.logoscript
  Delete $previousinstalldir\startup-${LANG_SPANISH}.logoscript
  Delete $previousinstalldir\startup-${LANG_ITALIAN}.logoscript
  Delete $previousinstalldir\startup-${LANG_PORTUGUESE}.logoscript
  Delete $previousinstalldir\startup-${LANG_GREEK}.logoscript
  Delete $previousinstalldir\startup-${LANG_FRENCH}.logoscript
  Delete $previousinstalldir\startup-${LANG_RUSSIAN}.logoscript

  Delete $previousinstalldir\logohelp.chm
  Delete $previousinstalldir\logohelp-${LANG_ENGLISH}.chm
  Delete $previousinstalldir\logohelp-${LANG_GERMAN}.chm
  Delete $previousinstalldir\logohelp-${LANG_SPANISH}.chm
  Delete $previousinstalldir\logohelp-${LANG_ITALIAN}.chm
  Delete $previousinstalldir\logohelp-${LANG_PORTUGUESE}.chm
  Delete $previousinstalldir\logohelp-${LANG_GREEK}.chm
  Delete $previousinstalldir\logohelp-${LANG_FRENCH}.chm
  Delete $previousinstalldir\logohelp-${LANG_RUSSIAN}.chm

  Delete $SYSDIR\fmslogo.scr
  Delete $previousinstalldir\fmslogo-${LANG_ENGLISH}.scr
  Delete $previousinstalldir\fmslogo-${LANG_GERMAN}.scr
  Delete $previousinstalldir\fmslogo-${LANG_SPANISH}.scr
  Delete $previousinstalldir\fmslogo-${LANG_ITALIAN}.scr
  Delete $previousinstalldir\fmslogo-${LANG_PORTUGUESE}.scr
  Delete $previousinstalldir\fmslogo-${LANG_GREEK}.scr
  Delete $previousinstalldir\fmslogo-${LANG_FRENCH}.scr
  Delete $previousinstalldir\fmslogo-${LANG_RUSSIAN}.scr

  ; For FMSLogo 6.27.0, Windows applied a compatibility shim that disabled
  ; file system redirection, resulting in FMSLogo.scr, the screen saver
  ; binary, being written to the real system32 directory, instead of
  ; to syswow64, like most 32-bit programs.  In FMSLogo 6.28.0 or later,
  ; Windows no longer does this.  In order to be able to clean up for
  ; for 6.27.0, we must disable file system redirection, then re-delete
  ; the screensaver.
  ${If} ${RunningX64}
    ${DisableX64FSRedirection}
    Delete $SYSDIR\fmslogo.scr
    ${EnableX64FSRedirection}
  ${EndIf}

  Delete $previousinstalldir\logo.hlp
  Delete $previousinstalldir\logo.gid
  Delete $previousinstalldir\logo.fts

  Delete $previousinstalldir\mcistrwh.hlp
  Delete $previousinstalldir\mcistrwh.gid
  Delete $previousinstalldir\mcistrwh.fts

  Delete $previousinstalldir\README.TXT
  Delete $previousinstalldir\FMSLOGO.TXT
  Delete $previousinstalldir\license.txt
  Delete $previousinstalldir\turtle.bmp

  Delete $previousinstalldir\uninstall.exe

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\FMSLogo\*.*"
  Delete "$DESKTOP\FMSLogo.lnk"

  ; Remove directories used
  RMDir "$SMPROGRAMS\FMSLogo"
  RMDir /r "$previousinstalldir\logolib"
  RMDir /r "$previousinstalldir\examples"
  RMDir "$previousinstalldir"

  ; remove the file association for .LGO
  DeleteRegValue SHELL_CONTEXT "software\classes\.lgo" "Logo program"
  DeleteRegKey   SHELL_CONTEXT "software\classes\Logo program"

FunctionEnd


!include Sections.nsh
!include FileFunc.nsh
!insertmacro GetParameters
!insertmacro GetOptions

;
; InstallLanguageFile - build_path filename_stem filename_extension
;   Used to install a language-specific file to a well-known location.
;   The filename must be of the form:
;
;        <stem>-<LCID>.<extension>
;
;   and will be installed as:
;
;        <stem>.<extension>
;
;   All of the files with the LCID are packed into the installer, but
;   only the file that corresponds to the selected language is unpacked.
;
; Example Usage:
;  
;    !insertmacro InstallLanguageFile ..\src\ startup .logoscript
;
; This packs ..\src\startup-1031.logoscript, ..\src\startup-1033.logoscript, etc.
; into the installer, and unpacks the correct file as startup.logoscript.
;
!macro InstallLanguageFile.PerLanguage language_id build_path filename_stem filename_extension
  StrCmp $LANGUAGE ${language_id} 0 +2
     File /oname=${filename_stem}${filename_extension} ${build_path}${filename_stem}-${language_id}${filename_extension}
!macroend

!macro InstallLanguageFile build_path filename_stem filename_extension
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_ENGLISH}    ${build_path} ${filename_stem} ${filename_extension}
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_GERMAN}     ${build_path} ${filename_stem} ${filename_extension}
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_SPANISH}    ${build_path} ${filename_stem} ${filename_extension}
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_ITALIAN}    ${build_path} ${filename_stem} ${filename_extension}
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_PORTUGUESE} ${build_path} ${filename_stem} ${filename_extension}
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_FRENCH}     ${build_path} ${filename_stem} ${filename_extension}
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_GREEK}      ${build_path} ${filename_stem} ${filename_extension}
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_RUSSIAN}    ${build_path} ${filename_stem} ${filename_extension}
!macroend

;--------------------------------

; The stuff to install
Section "FMSLogo"

  SectionIn RO

  ;
  ; Set output path to the installation directory.
  ;
  SetOutPath $INSTDIR

  ;
  ; Put files there
  ;
  !insertmacro InstallLanguageFile ..\src\    startup   .logoscript
  !insertmacro InstallLanguageFile ..\src\    fmslogo   .exe
  !insertmacro InstallLanguageFile ..\manual\ logohelp  .chm

  File "..\src\README.TXT"
  File "..\src\LICENSE.TXT"
  File "..\src\turtle.bmp"
  File /r /x CVS "..\src\logolib"
  File /r /x CVS "..\src\examples"

  ;
  ; Write the uninstall keys for Windows
  ;

  ; Write the installation path into the registry
  WriteRegStr SHELL_CONTEXT "Software\FMSLogo" "Install_Dir" "$INSTDIR"

  WriteRegStr   SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "DisplayName" "FMSLogo"
  WriteRegStr   SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "NoModify" 1
  WriteRegDWORD SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "NoRepair" 1

  WriteUninstaller "uninstall.exe"

  ;
  ; create a file association for .lgo
  ;
  WriteRegStr SHELL_CONTEXT "software\classes\.lgo"      ""             "Logo program"
  WriteRegStr SHELL_CONTEXT "software\classes\.lgo"      "Logo program" "Logo program"
  WriteRegStr SHELL_CONTEXT "software\classes\Logo program\shell"              "" "open"
  WriteRegStr SHELL_CONTEXT "software\classes\Logo program\DefaultIcon"        "" '$INSTDIR\fmslogo.exe,0'
  WriteRegStr SHELL_CONTEXT "software\classes\Logo program\shell\open\command" "" '$INSTDIR\fmslogo.exe -L%1'

SectionEnd


Section $(StartMenuShortcuts)
  CreateDirectory "$SMPROGRAMS\FMSLogo"
  CreateShortCut "$SMPROGRAMS\FMSLogo\Uninstall.lnk"        "$INSTDIR\uninstall.exe"       "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\FMSLogo\FMSLogo.lnk"          "$INSTDIR\fmslogo.exe"         "" "$INSTDIR\fmslogo.exe" 0
  CreateShortCut "$SMPROGRAMS\FMSLogo\Examples.lnk"         "$INSTDIR\examples"            "" "$INSTDIR\examples" 0
  CreateShortCut "$SMPROGRAMS\FMSLogo\Examples (index).lnk" "$INSTDIR\examples\index.html" "" "$INSTDIR\examples\index.html" 0
SectionEnd


Section $(DesktopShortcut)
  CreateShortCut "$DESKTOP\FMSLogo.lnk" "$INSTDIR\fmslogo.exe" "" "$INSTDIR\fmslogo.exe" 0 
SectionEnd


Section /o $(ScreenSaver) sectionid_screensaver
  ; Install the screen saver to the system directory.
  SetOutPath $SYSDIR
  !insertmacro InstallLanguageFile ..\screensaver\ fmslogo .scr
SectionEnd


Function .onInit

  ${GetParameters} $R0
  ClearErrors
  ${GetOptions} $R0 /LCID= $LANGUAGE
  StrCmp $LANGUAGE ${LANG_ENGLISH}    SetupUser
  StrCmp $LANGUAGE ${LANG_FRENCH}     SetupUser
  StrCmp $LANGUAGE ${LANG_GERMAN}     SetupUser
  StrCmp $LANGUAGE ${LANG_GREEK}      SetupUser
  StrCmp $LANGUAGE ${LANG_ITALIAN}    SetupUser
  StrCmp $LANGUAGE ${LANG_PORTUGUESE} SetupUser
  StrCmp $LANGUAGE ${LANG_RUSSIAN}    SetupUser
  StrCmp $LANGUAGE ${LANG_SPANISH}    SetupUser
  IfSilent SetupUser

  ; An LCID was specified, but it's not one that we support

  StrCmp $LANGUAGE "" SelectLanguage
  MessageBox MB_OK|MB_ICONEXCLAMATION "Unrecognized LCID $LANGUAGE.$\nLCID must be one of the following:$\n  ${LANG_ENGLISH} (English),$\n  ${LANG_FRENCH} (French),$\n  ${LANG_GERMAN} (German),$\n  ${LANG_GREEK} (Greek),$\n  ${LANG_ITALIAN} (Italian),$\n  ${LANG_PORTUGUESE} (Portuguese),$\n  ${LANG_RUSSIAN} (Russian), and$\n  ${LANG_SPANISH} (Spanish).$\n"
  Abort

SelectLanguage:
  ; Language selection dialog
  Push ""
  Push ${LANG_ENGLISH}
  Push English
  Push ${LANG_FRENCH}
  Push French
  Push ${LANG_GERMAN}
  Push German
  Push ${LANG_GREEK}
  Push Greek
  Push ${LANG_ITALIAN}
  Push Italian
  Push ${LANG_PORTUGUESE}
  Push Portuguese
  Push ${LANG_RUSSIAN}
  Push Russian
  Push ${LANG_SPANISH}
  Push Spanish
  Push A ; A means auto count languages
         ; for the auto count to work the first empty push (Push "") must remain
  LangDLL::LangDialog "Installer Language" "Please select the language to install"

  Pop $LANGUAGE
  StrCmp $LANGUAGE "cancel" 0 SetupUser
    Abort

  ; assume regular user until we know they are a power user
SetupUser:
  SetShellVarContext current
  StrLen $2 "$PROFILE\FMSLogo"
  StrCpy $INSTDIR "$PROFILE\FMSLogo" $2 0

  ClearErrors
  UserInfo::GetName
  IfErrors SetupUser.Win9x
  Pop $0
  UserInfo::GetAccountType
  Pop $1

  StrCmp $1 "Admin" SetupUser.AllUsers +1
  StrCmp $1 "Power" SetupUser.AllUsers +1
  goto SetupUser.Done

SetupUser.Win9x:
SetupUser.AllUsers:
  SetShellVarContext all
  StrLen $2       "$PROGRAMFILES\FMSLogo"
  StrCpy $INSTDIR "$PROGRAMFILES\FMSLogo" $2 0

  ; We can write to the system directory, so enable the screen saver
  SectionGetFlags ${sectionid_screensaver} $3
  IntOp $3 $3 | ${SF_SELECTED}
  SectionSetFlags ${sectionid_screensaver} $3

  goto SetupUser.Done

SetupUser.Done:

  ;
  ; Abort if another instance of the installer is running
  ; 
  System::Call 'kernel32::CreateMutexA(i 0, i 0, t "LogoForWindowsMutex") i .r1 ?e'
  Pop $R0 
  StrCmp $R0 0 checkifinstalled

  ; Silent installs should abort without a dialog box
  IfSilent Abort

  ; Notify the user that the install cannot continue.
  ; We can't use a LangString because those aren't available in .onInit
  StrCmp $LANGUAGE ${LANG_GERMAN} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "Either the installer or FMSLogo is currently running.$\nThis installation cannot continue." ; NOT_YET_LOCALIZED 
     Abort
  StrCmp $LANGUAGE ${LANG_SPANISH} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "Either the installer or FMSLogo is currently running.$\nThis installation cannot continue." ; NOT_YET_LOCALIZED
     Abort
  StrCmp $LANGUAGE ${LANG_ITALIAN} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "L'installatore o FMSLogo sono giа in esecuzione.$\nL'installazione non puт continuare."
     Abort
  StrCmp $LANGUAGE ${LANG_PORTUGUESE} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "O instalador ou o FMSLogo estб rodando.$\nEssa instalaзгo nгo poderб prosseguir."
     Abort
  StrCmp $LANGUAGE ${LANG_FRENCH} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "L'installateur ou bien FMSLogo est en cours d'exйcution.$\nL'installation ne peut continuer." 
     Abort
  StrCmp $LANGUAGE ${LANG_GREEK} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "ѕ егкбфбуф№фзт ё з FMSLogo екфелеяфбй ёдз.$\nЅхфё з егкбф№уфбуз де мрпсея нб ухнечйуфея."
     Abort
  StrCmp $LANGUAGE ${LANG_RUSSIAN} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "»ли инсталл€тор или FMSLogo в насто€щее врем€ запущены.$\n”становка не может быть продолжена." 
     Abort
  ; default to English
  MessageBox MB_OK|MB_ICONEXCLAMATION "Either the installer or FMSLogo is currently running.$\nThis installation cannot continue."
  Abort

checkifinstalled:

  ;
  ; If FMSLogo is already installed, either uninstall it or abort. 
  ;

  ; If this is a silent install, assume that the user wants it
  ; to succeed (unintall the previous instance of logo).
  IfSilent uninstall

  ReadRegStr $0 SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "UninstallString"

  ; If no uninstaller was found, then we're done
  StrCmp $0 "" end 0

  ; Extract the file path from the full path to the uninstaller.
  ; hack: assumes the string is quoted and ends in `\uninstall.exe"'.
  StrCpy $previousinstalldir $0 -15 1
  IfFileExists "$previousinstalldir\*.*" 0 end

  ; Notify the user that the install cannot continue until the existing FMSLogo is uninstalled
  ; We can't use a LangString because those aren't available in .onInit
  StrCmp $LANGUAGE ${LANG_GERMAN} 0 +2
    MessageBox MB_YESNO "The existing copy of FMSLogo must be uninstalled to continue.$\nDo you want to uninstall it?$\n$\n(Selecting No will abort the installation)" IDYES uninstall IDNO abort ; NOT_YET_LOCALIZED
  StrCmp $LANGUAGE ${LANG_SPANISH} 0 +2
    MessageBox MB_YESNO "The existing copy of FMSLogo must be uninstalled to continue.$\nDo you want to uninstall it?$\n$\n(Selecting No will abort the installation)" IDYES uninstall IDNO abort ; NOT_YET_LOCALIZED
  StrCmp $LANGUAGE ${LANG_ITALIAN} 0 +2
    MessageBox MB_YESNO "La versione attualmente installata di FMSLogo deve essere disinstallata prima di procedere.$\nVuoi procedere con la disinstallazione?$\n$\n(Selezionando No verrа interrotta l'installazione)" IDYES uninstall IDNO abort
  StrCmp $LANGUAGE ${LANG_PORTUGUESE} 0 +2
    MessageBox MB_YESNO "Jб existe uma cуpia do FMSLogo e precisa ser desinstalada para prosseguir.$\nDeseja desinstalб-la?$\n$\n(Escolher Nгo cessarб a instalaзгo)" IDYES uninstall IDNO abort 
  StrCmp $LANGUAGE ${LANG_FRENCH} 0 +2
    MessageBox MB_YESNO "La version existante de FMSLogo doit кtre dйsinstallйe pour continuer.$\nVoulez-vous la dйsinstaller?$\n$\n(Choisir Non terminera l'installation)" IDYES uninstall IDNO abort 
  StrCmp $LANGUAGE ${LANG_GREEK} 0 +2
    MessageBox MB_YESNO "‘п хр№счпн бнфягсбцп фзт FMSLogo рсЁрей нб брегкбфбуфбиея рсйн ухнечйуфея бхфё з егкбф№уфбуз.$\n»Ёлефе нб фп егкбфбуфёуефе;$\n$\n(≈рйлЁгпнфбт Љчй з егкбф№уфбуз иб клеяуей.)" IDYES uninstall IDNO abort
  StrCmp $LANGUAGE ${LANG_RUSSIAN} 0 +2
    MessageBox MB_YESNO "—уществующа€ копи€ FMSLogo должна быть удалена, чтобы продолжить.$\n¬ы хотите удалить ее?$\n$\n(¬ыбор Ќет прервет установку)" IDYES uninstall IDNO abort 
 ; default to English
 MessageBox MB_YESNO "The existing copy of FMSLogo must be uninstalled to continue.$\nDo you want to uninstall it?$\n$\n(Selecting No will abort the installation)" IDYES uninstall IDNO abort

abort:
    Abort

uninstall:
    ; uninstall the old version of Logo
    Call uninstall

end:

FunctionEnd




;--------------------------------
; Uninstaller

Function un.onInit

  System::Call 'kernel32::CreateMutexA(i 0, i 0, t "LogoForWindowsMutex") i .r1 ?e'
  Pop $R0
  StrCmp $R0 0 SetupUser

  ; Notify the user that the uninstall cannot continue.
  ; We can't use a LangString because those aren't available in .onInit
  StrCmp $LANGUAGE ${LANG_GERMAN} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "Either the installer or FMSLogo is currently running.$\nThis uninstallation cannot continue." ; NOT_YET_LOCALIZED
     Abort
  StrCmp $LANGUAGE ${LANG_SPANISH} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "Either the installer or FMSLogo is currently running.$\nThis uninstallation cannot continue." ; NOT_YET_LOCALIZED
     Abort
  StrCmp $LANGUAGE ${LANG_ITALIAN} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "L'installatore o FMSLogo sono giа in esecuzione.$\nL'installazione non puт continuare."
     Abort
  StrCmp $LANGUAGE ${LANG_PORTUGUESE} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "O instalador ou o FMSLogo estб rodando.$\n$\nEssa desinstalaзгo nгo poderб prosseguir." ; NOT_YET_LOCALIZED
     Abort
  StrCmp $LANGUAGE ${LANG_FRENCH} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "L'installateur ou bien FMSLogo est encours d'exйcution.$\nLa dйsinstallation ne peut continuer." 
     Abort
  StrCmp $LANGUAGE ${LANG_GREEK} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "ѕ егкбфбуф№фзт ё з FMSLogo екфелеяфбй ёдз.$\nЅхфё з брегкбф№уфбуз де мрпсея нб ухнечйуфея."
     Abort
  StrCmp $LANGUAGE ${LANG_RUSSIAN} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "»ли инсталл€тор или FMSLogo в насто€щее врем€ запущены.$\nн”даление не может быть продолжено."
     Abort
  ; default to English
  MessageBox MB_OK|MB_ICONEXCLAMATION "Either the installer or FMSLogo is currently running.$\nThis uninstallation cannot continue."
  Abort

SetupUser:
  ; assume regular user until we know they are a power user
  SetShellVarContext current

  ClearErrors
  UserInfo::GetName
  IfErrors SetupUser.Win9x
  Pop $0
  UserInfo::GetAccountType
  Pop $1

  StrCmp $1 "Admin" SetupUser.AllUsers +1
  StrCmp $1 "Power" SetupUser.AllUsers +1
  goto SetupUser.Done

SetupUser.Win9x:
SetupUser.AllUsers:
  SetShellVarContext all
  goto SetupUser.Done

SetupUser.Done:

  ReadRegStr $1 SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "UninstallString"
  StrCpy $INSTDIR $1 -15 1 ; hack: assumes the string is quoted and ends in `\uninstall.exe"'.

  ; check if FMSLogo exists where we think it does
  StrCmp $INSTDIR "" CheckIfInstallExists.ShowError 0
  IfFileExists "$INSTDIR\*.*" CheckIfInstallExists.Done CheckIfInstallExists.ShowError

CheckIfInstallExists.ShowError:
  ; Notify the user that FMSLogo does not exist where we think it does.
  ; We can't use a LangString because those aren't available in .onInit
  StrCmp $LANGUAGE ${LANG_GERMAN} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "Either FMSLogo has already been deleted or you do not have permission to uninstall it.$\nEither way, this uninstallation cannot continue." ; NOT_YET_LOCALIZED
     Abort
  StrCmp $LANGUAGE ${LANG_SPANISH} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "Either FMSLogo has already been deleted or you do not have permission to uninstall it.$\nEither way, this uninstallation cannot continue." ; NOT_YET_LOCALIZED
     Abort
  StrCmp $LANGUAGE ${LANG_ITALIAN} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "L'installatore o FMSLogo sono giа in esecuzione.$\nL'installazione non puт continuare."
     Abort
  StrCmp $LANGUAGE ${LANG_PORTUGUESE} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "Ou o FMSLogo jб foi deletado ou vocк nгo possui permissгo para desinstalб-lo.$\nEm ambos os casos, essa desinstalaзгo nгo poderб continuar." 
     Abort
  StrCmp $LANGUAGE ${LANG_FRENCH} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "FMSLogo a dйjа йtй supprimй ou vous n'avez pas la permission de le dйsinstaller.$\nLa dйsinstallation ne peut continuer." 
     Abort
  StrCmp $LANGUAGE ${LANG_GREEK} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "Either FMSLogo has already been deleted or you do not have permission to uninstall it.$\nEither way, this uninstallation cannot continue." ; NOT_YET_LOCALIZED
     Abort
  StrCmp $LANGUAGE ${LANG_RUSSIAN} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "»ли FMSLogo был уже удален, или ¬ы не имеете прав удал€ть ее.$\n¬ любом случае, удаление не может быть продолжено." 
     Abort
  ; default to English
  MessageBox MB_OK|MB_ICONEXCLAMATION "Either FMSLogo has already been deleted or you do not have permission to uninstall it.$\nEither way, this uninstallation cannot continue."
  Abort

CheckIfInstallExists.Done:

FunctionEnd


Section "Uninstall"
  ; Remove registry keys
  DeleteRegKey SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo"

  ; Remove files and uninstaller
  Delete $INSTDIR\fmslogo.exe
  Delete $INSTDIR\fmslogo-${LANG_ENGLISH}.exe
  Delete $INSTDIR\fmslogo-${LANG_GERMAN}.exe
  Delete $INSTDIR\fmslogo-${LANG_SPANISH}.exe
  Delete $INSTDIR\fmslogo-${LANG_ITALIAN}.exe
  Delete $INSTDIR\fmslogo-${LANG_PORTUGUESE}.exe
  Delete $INSTDIR\fmslogo-${LANG_GREEK}.exe
  Delete $INSTDIR\fmslogo-${LANG_FRENCH}.exe
  Delete $INSTDIR\fmslogo-${LANG_RUSSIAN}.exe

  Delete $INSTDIR\startup.logoscript
  Delete $INSTDIR\startup-${LANG_ENGLISH}.logoscript
  Delete $INSTDIR\startup-${LANG_GERMAN}.logoscript
  Delete $INSTDIR\startup-${LANG_SPANISH}.logoscript
  Delete $INSTDIR\startup-${LANG_ITALIAN}.logoscript
  Delete $INSTDIR\startup-${LANG_PORTUGUESE}.logoscript
  Delete $INSTDIR\startup-${LANG_GREEK}.logoscript
  Delete $INSTDIR\startup-${LANG_FRENCH}.logoscript
  Delete $INSTDIR\startup-${LANG_RUSSIAN}.logoscript

  Delete $INSTDIR\logohelp.chm
  Delete $INSTDIR\logohelp-${LANG_ENGLISH}.chm
  Delete $INSTDIR\logohelp-${LANG_GERMAN}.chm
  Delete $INSTDIR\logohelp-${LANG_SPANISH}.chm
  Delete $INSTDIR\logohelp-${LANG_ITALIAN}.chm
  Delete $INSTDIR\logohelp-${LANG_PORTUGUESE}.chm
  Delete $INSTDIR\logohelp-${LANG_GREEK}.chm
  Delete $INSTDIR\logohelp-${LANG_FRENCH}.chm
  Delete $INSTDIR\logohelp-${LANG_RUSSIAN}.chm

  Delete $SYSDIR\fmslogo.scr
  Delete $INSTDIR\fmslogo-${LANG_ENGLISH}.scr
  Delete $INSTDIR\fmslogo-${LANG_GERMAN}.scr
  Delete $INSTDIR\fmslogo-${LANG_SPANISH}.scr
  Delete $INSTDIR\fmslogo-${LANG_ITALIAN}.scr
  Delete $INSTDIR\fmslogo-${LANG_PORTUGUESE}.scr
  Delete $INSTDIR\fmslogo-${LANG_GREEK}.scr
  Delete $INSTDIR\fmslogo-${LANG_FRENCH}.scr
  Delete $INSTDIR\fmslogo-${LANG_RUSSIAN}.scr

  Delete $INSTDIR\README.TXT
  Delete $INSTDIR\LICENSE.TXT
  Delete $INSTDIR\turtle.bmp

  Delete $INSTDIR\uninstall.exe


  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\FMSLogo\*.*"
  Delete "$DESKTOP\FMSLogo.lnk"

  ; Remove directories used
  RMDir "$SMPROGRAMS\FMSLogo"
  RMDir /r "$INSTDIR\logolib"
  RMDir /r "$INSTDIR\examples"
  RMDir "$INSTDIR"

  ; remove the file association
  DeleteRegValue SHELL_CONTEXT "software\classes\.lgo" "Logo program"
  DeleteRegKey   SHELL_CONTEXT "software\classes\Logo program"

SectionEnd
