include ../version.mk

HHP_STYLESHEET  = htmlhelp.xsl 
HTML_STYLESHEET = html.xsl
FO_STYLESHEET   = fo.xsl
ROOTFILE        = logohelp.xml
SOURCEFILES     = $(wildcard *.xml) logoversion.xml

XSLTPROC = xsltproc
HHC      = "C:\Program Files\Help Workshop\hhc.exe"
FOP      = "C:\Program Files\fop-0.20.5\fop.bat"
UNIXECHO = "c:\cygwin\bin\echo.exe"

CSSOPTIONS=--stringparam html.stylesheet logohelp.css --stringparam html.stylesheet.type text/css


htmlhelp.hhp : $(SOURCEFILES) $(HHP_STYLESHEET)
	$(XSLTPROC) --nonet $(CSSOPTIONS) $(HHP_STYLESHEET) $(ROOTFILE)

index.html : $(SOURCEFILES) $(HTML_STYLESHEET)
	$(XSLTPROC) --nonet $(CSSOPTIONS) $(HTML_STYLESHEET) $(ROOTFILE)

logohelp.fo : $(SOURCEFILES) $(FO_STYLESHEET)
	$(XSLTPROC) --nonet --output $@ $(FO_STYLESHEET) $(ROOTFILE)

logohelp.chm : htmlhelp.hhp logohelp.css
	-$(HHC) htmlhelp.hhp

logohelp.ps : $(SOURCEFILES)
	docbook2ps $(ROOTFILE)

logohelp.pdf : logohelp.fo
	$(FOP) -q -fo $< -pdf $@

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
	$(RM) logohelp.ps
	$(RM) logohelp.fo
	$(RM) $(wildcard *.html)
	$(RM) $(wildcard *.hhp) 
	$(RM) $(wildcard *.hhc)
	$(RM) $(wildcard *.chm) 
	$(RM) $(wildcard *~)

all : htmlhelp.hhp logohelp.ps logohelp.pdf logohelp.rtf logohelp.fo


test :
	perl -W check-manual.pl

