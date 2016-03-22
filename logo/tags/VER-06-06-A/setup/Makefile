!include ..\version.mk

MAKENSIS="C:\Program Files\NSIS\makensis.exe"
CP=copy /Y
RM=del


TARGET=fmslogo-$(FMSLOGO_VERSION).exe

all : $(TARGET)


$(TARGET) : fmslogo.nsi
	$(MAKENSIS) $?
	$(CP) fmslogo.exe $@

clean :
	$(RM) fmslogo.exe
	$(RM) $(TARGET)
