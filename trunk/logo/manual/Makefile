HHP_STYLESHEET=/usr/share/sgml/docbook/xsl-stylesheets-1.68.1-1/htmlhelp/profile-htmlhelp.xsl

ROOTFILE   =logohelp.xml
SOURCEFILES=$(wildcard *.xml)

all : htmlhelp.hhp ;

htmlhelp.hhp : $(SOURCEFILES)
	xsltproc --nonet $(HHP_STYLESHEET) $(ROOTFILE)


logohelp.pdf : $(SOURCEFILES)
	docbook2pdf $(ROOTFILE)

logohelp.rtf : $(SOURCEFILES)
	docbook2rtf $(ROOTFILE)

clean :
	$(RM) logohelp.rtf logohelp.pdf logohelp.dvi *.html *.hhp *.hhc *.chm *~
