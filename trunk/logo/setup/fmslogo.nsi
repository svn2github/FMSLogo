;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Filename    : fmslogo.nsi
; Description : The NSIS installer script that builds the FMSLogo's installer.
;
; Localization Instructions: 
; 
;   1) If there are no place-holders for your language, then a feature request
;   on the FMSLogo project asking someone to add the place-holders.
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

; Compiler Flags
SetCompressor /SOLID lzma

; The name of the installer
Name "FMSLogo"

; The file to write
OutFile "fmslogo.exe"

; Use an XP manifest
XPStyle on

; The default installation directory
InstallDir "$PROGRAMFILES\FMSLogo"

; Registry key to check for directory 
; (so if you install again, it will overwrite the old one automatically)
InstallDirRegKey HKLM "Software\FMSLogo" "Install_Dir"

;--------------------------------

; Pages

Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

; variables
var previousinstalldir ; full path to the uninstaller
var UserType           ; "limited" or "power"

; Languages
LoadLanguageFile "${NSISDIR}\Contrib\Language files\English.nlf"  ; the default language
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Italian.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Spanish.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\French.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Greek.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Portuguese.nlf"

LangString DesktopShortcut ${LANG_ENGLISH}    "Desktop Shortcut"
LangString DesktopShortcut ${LANG_SPANISH}    "Desktop Shortcut" ; NOT_YET_LOCALIZED
LangString DesktopShortcut ${LANG_ITALIAN}    "Desktop Shortcut" ; NOT_YET_LOCALIZED
LangString DesktopShortcut ${LANG_PORTUGUESE} "Atalho no Desktop"
LangString DesktopShortcut ${LANG_FRENCH}     "Raccourci Bureau" 
LangString DesktopShortcut ${LANG_GREEK}      "Συντόμευση Επιφάνειας Εργασίας"

LangString StartMenuShortcuts ${LANG_ENGLISH}    "Start Menu Shortcuts"
LangString StartMenuShortcuts ${LANG_SPANISH}    "Start Menu Shortcuts" ; NOT_YET_LOCALIZED
LangString StartMenuShortcuts ${LANG_ITALIAN}    "Start Menu Shortcuts" ; NOT_YET_LOCALIZED
LangString StartMenuShortcuts ${LANG_PORTUGUESE} "Atalho no Menu Iniciar"
LangString StartMenuShortcuts ${LANG_FRENCH}     "Raccourcis Menu Dιmarrer" 
LangString StartMenuShortcuts ${LANG_GREEK}      "Συντομεύσεις Μενού Έναρξη" 


; uninstall must be able to remove all traces of any previous installation.
Function uninstall

  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo"

  ; Remove files and uninstaller
  Delete $previousinstalldir\fmslogo.exe
  Delete $previousinstalldir\fmslogo-${LANG_ENGLISH}.exe
  Delete $previousinstalldir\fmslogo-${LANG_SPANISH}.exe
  Delete $previousinstalldir\fmslogo-${LANG_ITALIAN}.exe
  Delete $previousinstalldir\fmslogo-${LANG_PORTUGUESE}.exe
  Delete $previousinstalldir\fmslogo-${LANG_GREEK}.exe
  Delete $previousinstalldir\fmslogo-${LANG_FRENCH}.exe

  Delete $previousinstalldir\startup.logoscript
  Delete $previousinstalldir\startup-${LANG_ENGLISH}.logoscript
  Delete $previousinstalldir\startup-${LANG_SPANISH}.logoscript
  Delete $previousinstalldir\startup-${LANG_ITALIAN}.logoscript
  Delete $previousinstalldir\startup-${LANG_PORTUGUESE}.logoscript
  Delete $previousinstalldir\startup-${LANG_GREEK}.logoscript
  Delete $previousinstalldir\startup-${LANG_FRENCH}.logoscript

  Delete $previousinstalldir\logohelp.chm
  Delete $previousinstalldir\logohelp-${LANG_ENGLISH}.chm
  Delete $previousinstalldir\logohelp-${LANG_SPANISH}.chm
  Delete $previousinstalldir\logohelp-${LANG_ITALIAN}.chm
  Delete $previousinstalldir\logohelp-${LANG_PORTUGUESE}.chm
  Delete $previousinstalldir\logohelp-${LANG_GREEK}.chm
  Delete $previousinstalldir\logohelp-${LANG_FRENCH}.chm

  Delete $previousinstalldir\logo.hlp
  Delete $previousinstalldir\logo.gid
  Delete $previousinstalldir\logo.fts

  Delete $previousinstalldir\mcistrwh.hlp
  Delete $previousinstalldir\mcistrwh.gid
  Delete $previousinstalldir\mcistrwh.fts

  Delete $previousinstalldir\fmslogo.txt
  Delete $previousinstalldir\license.txt

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
  DeleteRegValue HKCR ".lgo" "Logo program"
  DeleteRegKey HKCR "Logo program"

FunctionEnd


Function .onInit

  ;Language selection dialog

  Push ""
  Push ${LANG_ENGLISH}
  Push English
  Push ${LANG_FRENCH}
  Push French
  Push ${LANG_GREEK}
  Push Greek
  Push ${LANG_PORTUGUESE}
  Push Italian
  Push ${LANG_ITALIAN}
  Push Portuguese
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
  StrCpy $UserType "limited"
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
  StrCpy $UserType "power"
  StrLen $2       "$PROGRAMFILES\FMSLogo"
  StrCpy $INSTDIR "$PROGRAMFILES\FMSLogo" $2 0
  goto SetupUser.Done

SetupUser.Done:

  ;
  ; Abort if another instance of the installer is running
  ; 
  System::Call 'kernel32::CreateMutexA(i 0, i 0, t "LogoForWindowsMutex") i .r1 ?e'
  Pop $R0 
  StrCmp $R0 0 checkifinstalled

  ; Notify the user that the install cannot continue.
  ; We can't use a LangString because those aren't available in .onInit
  StrCmp $LANGUAGE ${LANG_SPANISH} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "Either the installer or FMSLogo is currently running.$\nThis installation cannot continue." ; NOT_YET_LOCALIZED
     Abort
  StrCmp $LANGUAGE ${LANG_ITALIAN} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "Either the installer or FMSLogo is currently running.$\nThis installation cannot continue." ; NOT_YET_LOCALIZED
     Abort
  StrCmp $LANGUAGE ${LANG_PORTUGUESE} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "O instalador ou o FMSLogo estα rodando.$\nEssa instalaηγo nγo poderα prosseguir."
     Abort
  StrCmp $LANGUAGE ${LANG_FRENCH} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "L'installateur ou bien FMSLogo est en cours d'exιcution.$\nL'installation ne peut continuer." 
     Abort
  StrCmp $LANGUAGE ${LANG_GREEK} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "Ο εγκαταστάτης ή η FMSLogo εκτελείται ήδη.$\nΑυτή η εγκατάσταση δε μπορεί να συνεχιστεί."
     Abort
  ; default to English
  MessageBox MB_OK|MB_ICONEXCLAMATION "Either the installer or FMSLogo is currently running.$\nThis installation cannot continue."
  Abort

checkifinstalled:

  ;
  ; If FMSLogo is already installed, either uninstall it or abort. 
  ;
  StrCmp $UserType "power" GetPreviousInstall.AllUsers GetPreviousInstall.CurrentUser

GetPreviousInstall.AllUsers:
  ReadRegStr $0 HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "UninstallString"
  goto GetPreviousInstall.Done

GetPreviousInstall.CurrentUser:
  ReadRegStr $0 HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "UninstallString"
  goto GetPreviousInstall.Done

GetPreviousInstall.Done:

  ; If no uninstaller was found, then we're done
  StrCmp $0 "" end 0

  ; Extract the file path from the full path to the uninstaller.
  ; hack: assumes the string is quoted and ends in `\uninstall.exe"'.
  StrCpy $previousinstalldir $0 -15 1
  IfFileExists "$previousinstalldir\*.*" 0 end

  ; Notify the user that the install cannot continue until the existing FMSLogo is uninstalled
  ; We can't use a LangString because those aren't available in .onInit
  StrCmp $LANGUAGE ${LANG_SPANISH} 0 +2
    MessageBox MB_YESNO "The existing copy of FMSLogo must be uninstalled to continue.$\nDo you want to uninstall it?$\n$\n(Selecting No will abort the installation)" IDYES uninstall IDNO abort ; NOT_YET_LOCALIZED
  StrCmp $LANGUAGE ${LANG_ITALIAN} 0 +2
    MessageBox MB_YESNO "The existing copy of FMSLogo must be uninstalled to continue.$\nDo you want to uninstall it?$\n$\n(Selecting No will abort the installation)" IDYES uninstall IDNO abort ; NOT_YET_LOCALIZED
  StrCmp $LANGUAGE ${LANG_PORTUGUESE} 0 +2
    MessageBox MB_YESNO "Jα existe uma cσpia do FMSLogo e precisa ser desinstalada para prosseguir.$\nDeseja desinstalα-la?$\n$\n(Escolher Nγo cessarα a instalaηγo)" IDYES uninstall IDNO abort 
  StrCmp $LANGUAGE ${LANG_FRENCH} 0 +2
    MessageBox MB_YESNO "La version existante de FMSLogo doit κtre dιsinstallιe pour continuer.$\nVoulez-vous la dιsinstaller?$\n$\n(Choisir Non terminera l'installation)" IDYES uninstall IDNO abort 
  StrCmp $LANGUAGE ${LANG_GREEK} 0 +2
    MessageBox MB_YESNO "Το υπάρχον αντίγραφο της FMSLogo πρέπει να απεγκατασταθεί πριν συνεχιστεί αυτή η εγκατάσταση.$\nΘέλετε να το εγκαταστήσετε;$\n$\n(Επιλέγοντας Όχι η εγκατάσταση θα κλείσει.)" IDYES uninstall IDNO abort
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

; The stuff to install
Section "FMSLogo"

  SectionIn RO

  ;
  ; Set output path to the installation directory.
  ;
  SetOutPath $INSTDIR
  
  ;
  ; Put file there
  ;
  File "..\src\startup-${LANG_ENGLISH}.logoscript"
  File "..\src\startup-${LANG_SPANISH}.logoscript"
  File "..\src\startup-${LANG_ITALIAN}.logoscript"
  File "..\src\startup-${LANG_PORTUGUESE}.logoscript"
  File "..\src\startup-${LANG_FRENCH}.logoscript"
  File "..\src\startup-${LANG_GREEK}.logoscript"

  File "..\src\fmslogo-${LANG_ENGLISH}.exe"
  File "..\src\fmslogo-${LANG_SPANISH}.exe"
  File "..\src\fmslogo-${LANG_ITALIAN}.exe"
  File "..\src\fmslogo-${LANG_PORTUGUESE}.exe"
  File "..\src\fmslogo-${LANG_FRENCH}.exe"
  File "..\src\fmslogo-${LANG_GREEK}.exe"

  File "..\manual\logohelp-${LANG_ENGLISH}.chm"
  File "..\manual\logohelp-${LANG_SPANISH}.chm"
  File "..\manual\logohelp-${LANG_ITALIAN}.chm"
  File "..\manual\logohelp-${LANG_PORTUGUESE}.chm"
  File "..\manual\logohelp-${LANG_FRENCH}.chm"
  File "..\manual\logohelp-${LANG_GREEK}.chm"

  File "..\src\Mcistrwh.hlp"
  File "..\src\fmslogo.txt"
  File "..\src\license.txt"
  File /r /x CVS "..\src\logolib"
  File /r /x CVS "..\src\examples"

  CopyFiles "$INSTDIR\startup-$LANGUAGE.logoscript" "$INSTDIR\startup.logoscript"
  CopyFiles "$INSTDIR\fmslogo-$LANGUAGE.exe"        "$INSTDIR\fmslogo.exe"
  CopyFiles "$INSTDIR\logohelp-$LANGUAGE.chm"       "$INSTDIR\logohelp.chm"

  ; Remove the unused language files
  Delete $INSTDIR\fmslogo-${LANG_ENGLISH}.exe
  Delete $INSTDIR\fmslogo-${LANG_SPANISH}.exe
  Delete $INSTDIR\fmslogo-${LANG_ITALIAN}.exe
  Delete $INSTDIR\fmslogo-${LANG_PORTUGUESE}.exe
  Delete $INSTDIR\fmslogo-${LANG_GREEK}.exe
  Delete $INSTDIR\fmslogo-${LANG_FRENCH}.exe

  Delete $INSTDIR\startup-${LANG_ENGLISH}.logoscript
  Delete $INSTDIR\startup-${LANG_SPANISH}.logoscript
  Delete $INSTDIR\startup-${LANG_ITALIAN}.logoscript
  Delete $INSTDIR\startup-${LANG_PORTUGUESE}.logoscript
  Delete $INSTDIR\startup-${LANG_GREEK}.logoscript
  Delete $INSTDIR\startup-${LANG_FRENCH}.logoscript

  Delete $INSTDIR\logohelp-${LANG_ENGLISH}.chm
  Delete $INSTDIR\logohelp-${LANG_SPANISH}.chm
  Delete $INSTDIR\logohelp-${LANG_ITALIAN}.chm
  Delete $INSTDIR\logohelp-${LANG_PORTUGUESE}.chm
  Delete $INSTDIR\logohelp-${LANG_GREEK}.chm
  Delete $INSTDIR\logohelp-${LANG_FRENCH}.chm

  ;
  ; Write the uninstall keys for Windows
  ;
  StrCmp $UserType "power" Uninstaller.AllUsers Uninstaller.CurrentUser

Uninstaller.AllUsers:
  ; Write the installation path into the registry
  WriteRegStr HKLM "Software\FMSLogo" "Install_Dir" "$INSTDIR"

  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "DisplayName" "FMSLogo"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "NoRepair" 1
  goto Uninstaller.Done

Uninstaller.CurrentUser:
  ; Write the installation path into the registry
  WriteRegStr HKCU "Software\FMSLogo" "Install_Dir" "$INSTDIR"

  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "DisplayName" "FMSLogo"
  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "NoModify" 1
  WriteRegDWORD HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "NoRepair" 1
  goto Uninstaller.Done

Uninstaller.Done:
  WriteUninstaller "uninstall.exe"


  ;
  ; create a file association for .lgo
  ;
  StrCmp $UserType "power" FileAssociation.AllUsers FileAssociation.CurrentUser

FileAssociation.AllUsers:
  WriteRegStr HKCR ".lgo" ""             "Logo program"
  WriteRegStr HKCR ".lgo" "Logo program" "Logo program"
  WriteRegStr HKCR "Logo program\shell"              "" "open"
  WriteRegStr HKCR "Logo program\DefaultIcon"        "" "$INSTDIR\fmslogo.exe,0"
  WriteRegStr HKCR "Logo program\shell\open\command" "" '$INSTDIR\fmslogo.exe -L%1'
  goto FileAssociation.Done

FileAssociation.CurrentUser:
  WriteRegStr HKCU "software\classes\.lgo"      ""             "Logo program"
  WriteRegStr HKCU "software\classes\.lgo"      "Logo program" "Logo program"
  WriteRegStr HKCU "software\classes\Logo program\shell"              "" "open"
  WriteRegStr HKCU "software\classes\Logo program\DefaultIcon"        "" '$INSTDIR\fmslogo.exe,0'
  WriteRegStr HKCU "software\classes\Logo program\shell\open\command" "" '$INSTDIR\fmslogo.exe -L%1'
  goto FileAssociation.Done

FileAssociation.Done:

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


;--------------------------------
; Uninstaller

Function un.onInit

  System::Call 'kernel32::CreateMutexA(i 0, i 0, t "LogoForWindowsMutex") i .r1 ?e'
  Pop $R0
  StrCmp $R0 0 SetupUser

  ; Notify the user that the uninstall cannot continue.
  ; We can't use a LangString because those aren't available in .onInit
  StrCmp $LANGUAGE ${LANG_SPANISH} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "Either the installer or FMSLogo is currently running.$\nThis uninstallation cannot continue." ; NOT_YET_LOCALIZED
     Abort
  StrCmp $LANGUAGE ${LANG_ITALIAN} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "Either the installer or FMSLogo is currently running.$\nThis uninstallation cannot continue." ; NOT_YET_LOCALIZED
     Abort
  StrCmp $LANGUAGE ${LANG_PORTUGUESE} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "O instalador ou o FMSLogo estα rodando.$\n$\nEssa desinstalaηγo nγo poderα prosseguir." ; NOT_YET_LOCALIZED
     Abort
  StrCmp $LANGUAGE ${LANG_FRENCH} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "L'installateur ou bien FMSLogo est encours d'exιcution.$\nLa dιsinstallation ne peut continuer." 
     Abort
  StrCmp $LANGUAGE ${LANG_GREEK} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "Ο εγκαταστάτης ή η FMSLogo εκτελείται ήδη.$\nΑυτή η απεγκατάσταση δε μπορεί να συνεχιστεί."
     Abort
  ; default to English
  MessageBox MB_OK|MB_ICONEXCLAMATION "Either the installer or FMSLogo is currently running.$\nThis uninstallation cannot continue."
  Abort

SetupUser:
  ; assume regular user until we know they are a power user
  SetShellVarContext current
  StrCpy $UserType "limited"
  ReadRegStr $1 HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "UninstallString"
  StrCpy $INSTDIR $1 -15 1 ; hack: assumes the string is quoted and ends in `\uninstall.exe"'.

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
  StrCpy $UserType "power"
  ReadRegStr $1 HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "UninstallString"
  StrCpy $INSTDIR $1 -15 1 ; hack: assumes the string is quoted and ends in `\uninstall.exe"'.

  goto SetupUser.Done

SetupUser.Done:

  ; check if FMSLogo exists where we think it does
  StrCmp $INSTDIR "" CheckIfInstallExists.ShowError 0
  IfFileExists "$INSTDIR\*.*" CheckIfInstallExists.Done CheckIfInstallExists.ShowError

CheckIfInstallExists.ShowError:
  ; Notify the user that FMSLogo does not exist where we think it does.
  ; We can't use a LangString because those aren't available in .onInit
  StrCmp $LANGUAGE ${LANG_SPANISH} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "Either FMSLogo has already been deleted or you do not have permission to uninstall it.$\nEither way, this uninstallation cannot continue." ; NOT_YET_LOCALIZED
     Abort
  StrCmp $LANGUAGE ${LANG_ITALIAN} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "Either FMSLogo has already been deleted or you do not have permission to uninstall it.$\nEither way, this uninstallation cannot continue." ; NOT_YET_LOCALIZED
     Abort
  StrCmp $LANGUAGE ${LANG_PORTUGUESE} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "Ou o FMSLogo jα foi deletado ou vocκ nγo possui permissγo para desinstalα-lo.$\nEm ambos os casos, essa desinstalaηγo nγo poderα continuar." 
     Abort
  StrCmp $LANGUAGE ${LANG_FRENCH} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "FMSLogo a dιjΰ ιtι supprimι ou vous n'avez pas la permission de le dιsinstaller.$\nLa dιsinstallation ne peut continuer." 
     Abort
  StrCmp $LANGUAGE ${LANG_GREEK} 0 +3
     MessageBox MB_OK|MB_ICONEXCLAMATION "Either FMSLogo has already been deleted or you do not have permission to uninstall it.$\nEither way, this uninstallation cannot continue." ; NOT_YET_LOCALIZED
     Abort
  ; default to English
  MessageBox MB_OK|MB_ICONEXCLAMATION "Either FMSLogo has already been deleted or you do not have permission to uninstall it.$\nEither way, this uninstallation cannot continue."
  Abort

CheckIfInstallExists.Done:

FunctionEnd


Section "Uninstall"
  ; Remove registry keys
  DeleteRegKey HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo"
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo"

  ; Remove files and uninstaller
  Delete $INSTDIR\fmslogo.exe
  Delete $INSTDIR\fmslogo-${LANG_ENGLISH}.exe
  Delete $INSTDIR\fmslogo-${LANG_SPANISH}.exe
  Delete $INSTDIR\fmslogo-${LANG_ITALIAN}.exe
  Delete $INSTDIR\fmslogo-${LANG_PORTUGUESE}.exe
  Delete $INSTDIR\fmslogo-${LANG_GREEK}.exe
  Delete $INSTDIR\fmslogo-${LANG_FRENCH}.exe

  Delete $INSTDIR\startup.logoscript
  Delete $INSTDIR\startup-${LANG_ENGLISH}.logoscript
  Delete $INSTDIR\startup-${LANG_SPANISH}.logoscript
  Delete $INSTDIR\startup-${LANG_ITALIAN}.logoscript
  Delete $INSTDIR\startup-${LANG_PORTUGUESE}.logoscript
  Delete $INSTDIR\startup-${LANG_GREEK}.logoscript
  Delete $INSTDIR\startup-${LANG_FRENCH}.logoscript

  Delete $INSTDIR\logohelp.chm
  Delete $INSTDIR\logohelp-${LANG_ENGLISH}.chm
  Delete $INSTDIR\logohelp-${LANG_SPANISH}.chm
  Delete $INSTDIR\logohelp-${LANG_ITALIAN}.chm
  Delete $INSTDIR\logohelp-${LANG_PORTUGUESE}.chm
  Delete $INSTDIR\logohelp-${LANG_GREEK}.chm
  Delete $INSTDIR\logohelp-${LANG_FRENCH}.chm

  Delete $INSTDIR\mcistrwh.hlp
  Delete $INSTDIR\mcistrwh.gid
  Delete $INSTDIR\mcistrwh.fts

  Delete $INSTDIR\fmslogo.txt
  Delete $INSTDIR\license.txt

  Delete $INSTDIR\uninstall.exe


  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\FMSLogo\*.*"
  Delete "$DESKTOP\FMSLogo.lnk"

  ; Remove directories used
  RMDir "$SMPROGRAMS\FMSLogo"
  RMDir /r "$INSTDIR\logolib"
  RMDir /r "$INSTDIR\examples"
  RMDir "$INSTDIR"

  ; remove the file association for .LGO
  DeleteRegValue HKCR ".lgo" "Logo program"
  DeleteRegKey HKCR "Logo program"

SectionEnd

