include ../version.mk

HHP_STYLESHEET = htmlhelp.xsl 
ROOTFILE       = logohelp.xml
SOURCEFILES    = $(wildcard *.xml) logoversion.xml

HHC = "C:\Program Files\Help Workshop\hhc.exe"


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

# generate an XML file that contains the version
logoversion.xml : ../version.mk
	echo -n $(FMSLOGO_VERSION) > $@

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

