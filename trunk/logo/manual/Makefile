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

# prevent the hhp files from being automatically deleted
.SECONDARY : htmlhelp-1032.hhp htmlhelp-1033.hhp htmlhelp-1036.hhp


# by default, build the English CHM file
logohelp.chm : logohelp-1033.chm
	cp $^ $@

index.html : $(SOURCEFILES) $(HTML_STYLESHEET)
	cp translations-1033.xml translations.xml
	$(XSLTPROC) --nonet $(HTML_STYLESHEET) $(ROOTFILE)

logohelp.fo : $(SOURCEFILES) $(FO_STYLESHEET)
	cp translations-1033.xml translations.xml
	$(XSLTPROC) --nonet --output $@ $(FO_STYLESHEET) $(ROOTFILE)

logohelp-%.chm : htmlhelp-%.hhp logohelp.css
	perl -W clean-html.pl
	-$(HHC) htmlhelp-$*.hhp

# Greek builds requires a different character set
logohelp-1032.chm : htmlhelp-1032.hhp logohelp.css
	perl -W clean-html.pl windows-1253
	-$(HHC) htmlhelp-1032.hhp

htmlhelp-%.hhp : translations-%.xml $(SOURCEFILES) $(HHP_STYLESHEET)
	cp translations-$*.xml translations.xml
	$(XSLTPROC) --nonet --param htmlhelp.chm "'logohelp-$*.chm'" $(HHP_STYLESHEET) $(ROOTFILE)
	mv htmlhelp.hhp htmlhelp-$*.hhp

# The "all" target builds all translations of the .chm
all : logohelp-1032.chm logohelp-1033.chm logohelp-1036.chm;

logohelp.ps : $(SOURCEFILES)
	docbook2ps $(ROOTFILE)

logohelp.pdf : logohelp.fo
	$(FOP) -q -fo $< -pdf $@

logohelp.rtf : $(SOURCEFILES)
	docbook2rtf $(ROOTFILE)

website : index.html
	-mkdir www
	cp $(shell /usr/bin/find -maxdepth 1 -name '*.html') www
	cp logohelp.css www

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
	$(RM) $(wildcard *.htm)
	$(RM) $(wildcard *.hhp)
	$(RM) $(wildcard *.hhc)
	$(RM) $(wildcard *.hhk)
	$(RM) $(wildcard *.chw)
	$(RM) $(wildcard *.chm)
	$(RM) $(wildcard *~)

test :
	perl -W check-manual.pl

