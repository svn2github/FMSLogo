include ../version.mk

HHP_STYLESHEET = htmlhelp.xsl 
ROOTFILE       = logohelp.xml
SOURCEFILES    = $(wildcard *.xml) logoversion.xml

HHC      = "C:\Program Files\Help Workshop\hhc.exe"
UNIXECHO = "c:\cygwin\bin\echo.exe"


htmlhelp.hhp : $(SOURCEFILES)  $(HHP_STYLESHEET)
	xsltproc --nonet $(HHP_STYLESHEET) $(ROOTFILE)

logohelp.chm : htmlhelp.hhp
	-$(HHC) htmlhelp.hhp

logohelp.ps : $(SOURCEFILES)
	docbook2ps $(ROOTFILE)

logohelp.pdf : $(SOURCEFILES)
	docbook2pdf $(ROOTFILE)

logohelp.rtf : $(SOURCEFILES)
	docbook2rtf $(ROOTFILE)

# Generate an XML file that contains the version
# We use the UNIX version of echo to make sure there is no newline
logoversion.xml : ../version.mk
	$(UNIXECHO) -n $(FMSLOGO_VERSION) > $@

clean :
	$(RM) logohelp.rtf 
	$(RM) logohelp.pdf 
	$(RM) logohelp.dvi
	$(RM) $(wildcard *.html)
	$(RM) $(wildcard *.hhp) 
	$(RM) $(wildcard *.hhc)
	$(RM) $(wildcard *.chm) 
	$(RM) $(wildcard *~)

all : htmlhelp.hhp logohelp.ps logohelp.pdf logohelp.rtf


test :
	perl -W check-manual.pl

