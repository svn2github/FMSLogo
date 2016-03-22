!include ..\version.mk

MAKENSIS="C:\Program Files\NSIS\makensis.exe"
CP=copy /Y
RM=del
MV=move


TARGET=fmslogo-$(FMSLOGO_VERSION).exe

all : $(TARGET)


$(TARGET) : fmslogo.nsi
	$(MAKENSIS) $?
	$(MV) fmslogo.exe $@

clean :
	$(RM) fmslogo.exe
	$(RM) $(TARGET)
