; Compiler Flags
SetCompressor /SOLID lzma

; The name of the installer
Name "FMSLogo"

; The file to write
OutFile "fmslogo.exe"


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
var uninstallExe


; uninstall must be able to remove all traces of any 
; previous installation.
Function uninstall

  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo"

  ; Remove files and uninstaller
  Delete $INSTDIR\fmslogo.exe

  Delete $INSTDIR\logo.hlp
  Delete $INSTDIR\logo.gid
  Delete $INSTDIR\logo.fts
  Delete $INSTDIR\logohelp.chm

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

FunctionEnd


Function .onInit
  ;
  ; Abort if another instance of the installer is running
  ; 
  System::Call 'kernel32::CreateMutexA(i 0, i 0, t "LogoForWindowsMutex") i .r1 ?e'
  Pop $R0 
  StrCmp $R0 0 checkifinstalled
    MessageBox MB_OK|MB_ICONEXCLAMATION "Either the installer or FMSLogo is currently running.$\nThis installation cannot continue."
    Abort


checkifinstalled:

  ;
  ; If FMSLogo is already installed, either uninstall it or abort. 
  ;
  ReadRegStr $0 HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "UninstallString"

  ; remove quotes from $uninstallExe
  StrLen $1 $0
  IntOp  $1 $1 - 2
  StrCpy $uninstallExe $0 $1 1 

  IfFileExists $uninstallExe 0 end
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
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File "..\src\fmslogo.exe"
  File "..\src\logohelp.chm"
  File "..\src\Mcistrwh.hlp"
  File "..\src\fmslogo.txt"
  File "..\src\license.txt"
  File /r /x CVS "..\src\logolib"
  File /r /x CVS "..\src\examples"

  ; Write the installation path into the registry
  WriteRegStr HKLM "Software\FMSLogo" "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "DisplayName" "FMSLogo"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "NoRepair" 1
  WriteUninstaller "uninstall.exe"

  ; create a file association for .lgo
  WriteRegStr HKCR ".lgo" "" "Logo program"
  WriteRegStr HKCR "Logo program"                    "" "Logo program"
  WriteRegStr HKCR "Logo program\shell"              "" "open"
  WriteRegStr HKCR "Logo program\DefaultIcon"        "" "$INSTDIR\fmslogo.exe,0"
  WriteRegStr HKCR "Logo program\shell\open\command" "" '$INSTDIR\fmslogo.exe -L%1'
 
SectionEnd


Section "Start Menu Shortcuts"
  CreateDirectory "$SMPROGRAMS\FMSLogo"
  CreateShortCut "$SMPROGRAMS\FMSLogo\Uninstall.lnk"        "$INSTDIR\uninstall.exe"       "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\FMSLogo\FMSLogo.lnk"          "$INSTDIR\fmslogo.exe"         "" "$INSTDIR\fmslogo.exe" 0
  CreateShortCut "$SMPROGRAMS\FMSLogo\Examples.lnk"         "$INSTDIR\examples"            "" "$INSTDIR\examples" 0
  CreateShortCut "$SMPROGRAMS\FMSLogo\Examples (index).lnk" "$INSTDIR\examples\index.html" "" "$INSTDIR\examples\index.html" 0
SectionEnd


Section "Desktop Shortcut"
  CreateShortCut "$DESKTOP\FMSLogo.lnk" "$INSTDIR\fmslogo.exe" "" "$INSTDIR\fmslogo.exe" 0 
SectionEnd


;--------------------------------
; Uninstaller

Section "Uninstall"
  System::Call 'kernel32::CreateMutexA(i 0, i 0, t "LogoForWindowsMutex") i .r1 ?e'
  Pop $R0 
  StrCmp $R0 0 uninstall
    MessageBox MB_OK|MB_ICONEXCLAMATION "Either the installer or FMSLogo is currently running.$\nThis installation cannot continue."
    Abort

uninstall:

  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo"

  ; Remove files and uninstaller
  Delete $INSTDIR\fmslogo.exe

  Delete $INSTDIR\logohelp.chm

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

