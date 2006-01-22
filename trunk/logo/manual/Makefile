HHP_STYLESHEET = htmlhelp.xsl 
ROOTFILE       = logohelp.xml
SOURCEFILES    = $(wildcard *.xml)

all : htmlhelp.hhp ;

htmlhelp.hhp : $(SOURCEFILES)  $(HHP_STYLESHEET)
	xsltproc --nonet $(HHP_STYLESHEET) $(ROOTFILE)

logohelp.pdf : $(SOURCEFILES)
	docbook2pdf $(ROOTFILE)

logohelp.rtf : $(SOURCEFILES)
	docbook2rtf $(ROOTFILE)

clean :
	$(RM) logohelp.rtf logohelp.pdf logohelp.dvi *.html *.hhp *.hhc *.chm *~

