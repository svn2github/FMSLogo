#! /usr/bin/perl -W
###############################################################################
# Searches that the manual for style violations:
#
# * Files of the form "command-<word>.xml" document the command <word>
# * All uppercase words are documented commands.
# * All commands in <link> tags have the expected linkend attribute.
# * No abbreviations of commands are allowed.
# * Emphasis is not given with upper-case.
# * All commands have a <title> element that matches the command.
# * All commands have an <indexterm> element that matches the command.
# * All <book> elements have an id attribute.
# * All <preface> elements have an id attribute.
# * All <chapter> elements have an id attribute.
# * All <section> elements have an id attribute.
# * All occurances of "Logo" and "FMSLogo" are correct.
# * There is no extraneous whitespace in program listings or synopses.
# * Banned words/phrases are not used
# * Examples include at least one instance of the command that they document.
# * There is no trailing whitespace.
# * All procedures are documented.
#
# Missing checks:
# * Spelling is correct.
# * Only the first reference to a command in any section is hyperlinked.
# * Commands are not hyperlinked when they occurs within their own definition.
# * All instances of the <parameter> tag refer to actual parameters.
# * All abbreviations are correct (and that the list is complete).
# * Ensure program listings are 75 columns or less.
# * Links in the "See Also" section don't reference the current page.
#
###############################################################################


use strict;
use IO::File;

$main::TotalErrors   = 0;
$main::TotalWarnings = 0;

@main::BannedWords = (
  'left-hand',        # use "left", instead
  'right-hand',       # use "right", instead
  'ie',               # use "that is", instead
  'i.e.',             # use "that is", instead
  'e.g.',             # use "for example", instead
  'eg',               # use "for example", instead
  'terminal',         # use "the Commander", instead
  'multidimensional', # use "multi-dimensional", instead
);

my %Commands = ();

my %AlternateSpellings = ();
$AlternateSpellings{ARRAYP}         = ['ARRAY?'];
$AlternateSpellings{BACKSLASHEDP}   = ['BACKSLASHED?'];
$AlternateSpellings{BACK}           = ['BK'];
$AlternateSpellings{BEFOREP}        = ['BEFORE?'];
$AlternateSpellings{BUTFIRSTS}      = ['BFS'];
$AlternateSpellings{BUTFIRST}       = ['BF'];
$AlternateSpellings{BUTLAST}        = ['BL'];
$AlternateSpellings{CLEARSCREEN}    = ['CS'];
$AlternateSpellings{CLEARTEXT}      = ['CT'];
$AlternateSpellings{CONTINUE}       = ['CO'];
$AlternateSpellings{DEFINEDP}       = ['DEFINED?'];
$AlternateSpellings{DIFFERENCE}     = ['-'];
$AlternateSpellings{DOWNPITCH}      = ['DOWN'];
$AlternateSpellings{EDIT}           = ['ED'];
$AlternateSpellings{EMPTYP}         = ['EMPTY?'];
$AlternateSpellings{EOFP}           = ['EOF?'];
$AlternateSpellings{EQUALP}         = ['EQUAL?', '='];
$AlternateSpellings{ERASEFILE}      = ['ERF'];
$AlternateSpellings{ERASE}          = ['ER'];
$AlternateSpellings{FLOODCOLOR}     = ['FLOODCOLOUR'];
$AlternateSpellings{FORWARD}        = ['FD'];
$AlternateSpellings{FULLSCREEN}     = ['FS'];
$AlternateSpellings{GREATEREQUALP}  = ['GREATEREQUAL?', '>='];
$AlternateSpellings{GREATERP}       = ['GREATER?', '>'];
$AlternateSpellings{HIDETURTLE}     = ['HT'];
$AlternateSpellings{IFFALSE}        = ['IFF'];
$AlternateSpellings{IFTRUE}         = ['IFT'];
$AlternateSpellings{KEYP}           = ['KEY?'];
$AlternateSpellings{LEFTROLL}       = ['LR'];
$AlternateSpellings{LEFT}           = ['LT'];
$AlternateSpellings{LESSEQUALP}     = ['LESSEQUAL?', '<='];
$AlternateSpellings{LESSP}          = ['LESS?', '<'];
$AlternateSpellings{LISTP}          = ['LIST?'];
$AlternateSpellings{MACROP}         = ['MACRO?'];
$AlternateSpellings{MEMBERP}        = ['MEMBER?'];
$AlternateSpellings{MINUS}          = ['--'];
$AlternateSpellings{NAMEP}          = ['NAME?'];
$AlternateSpellings{NOTEQUALP}      = ['NOTEQUAL?', '<>'];
$AlternateSpellings{NUMBERP}        = ['NUMBER?'];
$AlternateSpellings{OUTPUT}         = ['OP'];
$AlternateSpellings{PENCOLOR}       = ['PENCOLOUR', 'PC'];
$AlternateSpellings{PENDOWNP}       = ['PENDOWN?'];
$AlternateSpellings{PENDOWN}        = ['PD'];
$AlternateSpellings{PENERASE}       = ['PE'];
$AlternateSpellings{PENPAINT}       = ['PPT'];
$AlternateSpellings{PENREVERSE}     = ['PX'];
$AlternateSpellings{PENUP}          = ['PU'];
$AlternateSpellings{PRIMITIVEP}     = ['PRIMITIVE?'];
$AlternateSpellings{PRINT}          = ['PR'];
$AlternateSpellings{PROCEDUREP}     = ['PROCEDURE?'];
$AlternateSpellings{PRODUCT}        = ['*'];
$AlternateSpellings{PROPLISTP}      = ['PROPLIST?'];
$AlternateSpellings{QUOTIENT}       = ['/'];
$AlternateSpellings{READCHARS}      = ['RCS'];
$AlternateSpellings{READCHAR}       = ['RC'];
$AlternateSpellings{READLIST}       = ['RL'];
$AlternateSpellings{READWORD}       = ['RW'];
$AlternateSpellings{RIGHTROLL}      = ['RR'];
$AlternateSpellings{RIGHT}          = ['RT'];
$AlternateSpellings{SCREENCOLOR}    = ['SCREENCOLOUR'];
$AlternateSpellings{SENTENCE}       = ['SE'];
$AlternateSpellings{SETFLOODCOLOR}  = ['SETFLOODCOLOUR',  'SETFC'];
$AlternateSpellings{SETHEADING}     = ['SETH'];
$AlternateSpellings{SETPENCOLOR}    = ['SETPENCOLOUR',    'SETPC'];
$AlternateSpellings{SETSCREENCOLOR} = ['SETSCREENCOLOUR', 'SETSC'];
$AlternateSpellings{SHOWNP}         = ['SHOWN?'];
$AlternateSpellings{SHOWTURTLE}     = ['ST'];
$AlternateSpellings{SPLITSCREEN}    = ['SS'];
$AlternateSpellings{SUBSTRINGP}     = ['SUBSTRING?'];
$AlternateSpellings{SUM}            = ['+'];
$AlternateSpellings{TEXTSCREEN}     = ['TS'];
$AlternateSpellings{UPPITCH}        = ['UP'];
$AlternateSpellings{WORDP}          = ['WORD?'];

my %CanonicalSpelling = ();

my %Exceptions = ();
$Exceptions{'command-.eq.xml'}{'allcaps'}{'WARNING'}        = 1;

$Exceptions{'command-.macro.xml'}{'allcaps'}{'EXAMPLE'}     = 1;
$Exceptions{'command-.macro.xml'}{'allcaps'}{'LISP'}        = 1;
$Exceptions{'command-.macro.xml'}{'allcaps'}{'MY.REPEAT'}   = 1;
$Exceptions{'command-.macro.xml'}{'allcaps'}{'REPEAT.DONE'} = 1;
$Exceptions{'command-.macro.xml'}{'allcaps'}{'REPEAT1'}     = 1;
$Exceptions{'command-.macro.xml'}{'allcaps'}{'TRY'}         = 1;

$Exceptions{'command-.setbf.xml'}{'allcaps'}{'WARNING'}     = 1;

$Exceptions{'command-.setfirst.xml'}{'allcaps'}{'WARNING'}  = 1;

$Exceptions{'command-.setitem.xml'}{'allcaps'}{'WARNING'}   = 1;

$Exceptions{'command-backtick.xml'}{'propername'}         = '`';

$Exceptions{'command-beforep.xml'}{'allcaps'}{'ABC'}      = 1;

$Exceptions{'command-bitsave.xml'}{'allcaps'}{'BMP'}      = 1;

$Exceptions{'command-bury.xml'}{'allcaps'}{'BAR'}         = 1;
$Exceptions{'command-bury.xml'}{'allcaps'}{'FOO'}         = 1;

$Exceptions{'command-buryall.xml'}{'allcaps'}{'BAR'}      = 1;
$Exceptions{'command-buryall.xml'}{'allcaps'}{'FOO'}      = 1;

$Exceptions{'command-catch.xml'}{'allcaps'}{'MYPROGRAM1'} = 1;
$Exceptions{'command-catch.xml'}{'allcaps'}{'MYPROGRAM2'} = 1;

$Exceptions{'command-cascade.2.xml'}{'allcaps'}{'FIBONACCI'} = 1;

$Exceptions{'command-cascade.xml'}{'allcaps'}{'FIBONACCI'} = 1;
$Exceptions{'command-cascade.xml'}{'allcaps'}{'VOWELP'}    = 1;
$Exceptions{'command-cascade.xml'}{'allcaps'}{'PIGLATIN'}  = 1;

$Exceptions{'command-chdir.xml'}{'allcaps'}{'DOS'} = 1;

$Exceptions{'command-checkboxcreate.xml'}{'allcaps'}{'CHECKONTHINGS'} = 1;

$Exceptions{'command-checkboxget.xml'}{'allcaps'}{'CHECKONTHINGS'} = 1;

$Exceptions{'command-comboboxaddstring.xml'}{'allcaps'}{'DODRAW'} = 1;

$Exceptions{'command-comboboxgettext.xml'}{'allcaps'}{'DODRAW'} = 1;

$Exceptions{'command-contents.xml'}{'allcaps'}{'MYPROGRAM'} = 1;

$Exceptions{'command-continue.xml'}{'allcaps'}{'MYPROGRAM'} = 1;
$Exceptions{'command-continue.xml'}{'allcaps'}{'OK'}        = 1;

$Exceptions{'command-copydef.xml'}{'allcaps'}{'SAYHELLO'} = 1;
$Exceptions{'command-copydef.xml'}{'allcaps'}{'WELCOME'}  = 1;

$Exceptions{'command-crossmap.xml'}{'allcaps'}{'CSLS'} = 1;

$Exceptions{'command-dialogcreate.xml'}{'allcaps'}{'MYSETUP'} = 1;
$Exceptions{'command-dialogcreate.xml'}{'allcaps'}{'OK'}      = 1;

$Exceptions{'command-dialogdelete.xml'}{'allcaps'}{'MYSETUP'} = 1;
$Exceptions{'command-dialogdelete.xml'}{'allcaps'}{'OK'}      = 1;

$Exceptions{'command-dialogenable.xml'}{'allcaps'}{'MYSETUP'} = 1;
$Exceptions{'command-dialogenable.xml'}{'allcaps'}{'OK'}      = 1;

$Exceptions{'command-dir.xml'}{'allcaps'}{'LOGO.HLP'}    = 1;
$Exceptions{'command-dir.xml'}{'allcaps'}{'LICENSE.TXT'} = 1;
$Exceptions{'command-dir.xml'}{'allcaps'}{'FMSLOGO.TXT'} = 1;
$Exceptions{'command-dir.xml'}{'logo'}                   = 1;

$Exceptions{'command-directories.xml'}{'logo'}           = 1;

$Exceptions{'command-dllcall.xml'}{'allcaps'}{'DLL'}    = 1;
$Exceptions{'command-dllcall.xml'}{'allcaps'}{'DOUBLE'} = 1;
$Exceptions{'command-dllcall.xml'}{'allcaps'}{'DWORD'}  = 1;
$Exceptions{'command-dllcall.xml'}{'allcaps'}{'LPSTR'}  = 1;
$Exceptions{'command-dllcall.xml'}{'allcaps'}{'TCHAR'}  = 1;

$Exceptions{'command-dllfree.xml'}{'allcaps'}{'DLL'}  = 1;

$Exceptions{'command-dllload.xml'}{'allcaps'}{'DLL'}  = 1;

$Exceptions{'command-edall.xml'}{'allcaps'}{'MYPROGRAM'}  = 1;

$Exceptions{'command-edit.xml'}{'allcaps'}{'MYPROGRAM'}  = 1;

$Exceptions{'command-edn.xml'}{'allcaps'}{'MYPROGRAM'}  = 1;

$Exceptions{'command-edns.xml'}{'allcaps'}{'MYPROGRAM'}  = 1;

$Exceptions{'command-edps.xml'}{'allcaps'}{'MYPROGRAM1'}  = 1;
$Exceptions{'command-edps.xml'}{'allcaps'}{'MYPROGRAM2'}  = 1;

$Exceptions{'command-end.xml'}{'allcaps'}{'ECHO'}  = 1;

$Exceptions{'command-erall.xml'}{'allcaps'}{'BAR'} = 1;
$Exceptions{'command-erall.xml'}{'allcaps'}{'FOO'} = 1;

$Exceptions{'command-erase.xml'}{'allcaps'}{'FOO'} = 1;

$Exceptions{'command-erps.xml'}{'allcaps'}{'BAR'}  = 1;
$Exceptions{'command-erps.xml'}{'allcaps'}{'FOO'}  = 1;

$Exceptions{'command-error.xml'}{'allcaps'}{'MYPROGRAM'}   = 1;

$Exceptions{'command-files.xml'}{'allcaps'}{'LOGO.HLP'}    = 1;
$Exceptions{'command-files.xml'}{'allcaps'}{'LICENSE.TXT'} = 1;
$Exceptions{'command-files.xml'}{'allcaps'}{'FMSLOGO.TXT'} = 1;
$Exceptions{'command-files.xml'}{'logo'}                   = 1;

$Exceptions{'command-fill.xml'}{'allcaps'}{'SQUARE'}  = 1;

$Exceptions{'command-filter.xml'}{'allcaps'}{'?REST'}  = 1;
$Exceptions{'command-filter.xml'}{'allcaps'}{'VOWELP'} = 1;

$Exceptions{'command-find.xml'}{'allcaps'}{'?REST'}  = 1;
$Exceptions{'command-find.xml'}{'allcaps'}{'MYFIND'} = 1;

$Exceptions{'command-foreach.xml'}{'allcaps'}{'?REST'} = 1;

$Exceptions{'command-fulltext.xml'}{'allcaps'}{'ABC'} = 1;

$Exceptions{'command-gensym.xml'}{'allcaps'}{'G1'} = 1;
$Exceptions{'command-gensym.xml'}{'allcaps'}{'G2'} = 1;

$Exceptions{'command-gifload.xml'}{'allcaps'}{'GIF'} = 1;

$Exceptions{'command-gifsave.xml'}{'allcaps'}{'GIF'} = 1;

$Exceptions{'command-gifsize.xml'}{'allcaps'}{'GIF'} = 1;

$Exceptions{'command-goto.xml'}{'allcaps'}{'STATES'} = 1;

$Exceptions{'command-groupboxcreate.xml'}{'allcaps'}{'CHECKONTHINGS'} = 1;

$Exceptions{'command-icon.xml'}{'allcaps'}{'HIDEANDSHOW'}  = 1;

$Exceptions{'command-if.xml'}{'allcaps'}{'MAX'}  = 1;

$Exceptions{'command-ifelse.xml'}{'allcaps'}{'MAX'}  = 1;

$Exceptions{'command-iffalse.xml'}{'allcaps'}{'MYTEST'}  = 1;

$Exceptions{'command-iftrue.xml'}{'allcaps'}{'MYTEST'}  = 1;

$Exceptions{'command-ignore.xml'}{'allcaps'}{'MYPROGRAM'}  = 1;

$Exceptions{'command-keyp.xml'}{'allcaps'}{'CBREAK'}  = 1;
$Exceptions{'command-keyp.xml'}{'allcaps'}{'UNIX'}    = 1;

$Exceptions{'command-label.xml'}{'allcaps'}{'AXIS'}     = 1;
$Exceptions{'command-label.xml'}{'allcaps'}{'FLASH'}    = 1;
$Exceptions{'command-label.xml'}{'allcaps'}{'TELLJOKE'} = 1;

$Exceptions{'command-labelsize.xml'}{'allcaps'}{'CENTERLABEL'}   = 1;
$Exceptions{'command-labelsize.xml'}{'allcaps'}{'VERTICALLABEL'} = 1;

$Exceptions{'command-listboxaddstring.xml'}{'allcaps'}{'DODRAW'} = 1;

$Exceptions{'command-listboxgetselect.xml'}{'allcaps'}{'DODRAW'} = 1;

$Exceptions{'command-load.xml'}{'allcaps'}{'MYPROGRAM1'} = 1;
$Exceptions{'command-load.xml'}{'allcaps'}{'MYPROGRAM2'} = 1;

$Exceptions{'command-local.xml'}{'allcaps'}{'ABC'} = 1;
$Exceptions{'command-local.xml'}{'allcaps'}{'FOO'} = 1;

$Exceptions{'command-localmake.xml'}{'allcaps'}{'SAYHELLO'} = 1;

$Exceptions{'command-logoversion.xml'}{'logo'} = 1;

$Exceptions{'command-map.xml'}{'allcaps'}{'?REST'}     = 1;

$Exceptions{'command-map.se.xml'}{'allcaps'}{'?REST'}  = 1;

$Exceptions{'command-mci.xml'}{'allcaps'}{'CD'}        = 1;
$Exceptions{'command-mci.xml'}{'allcaps'}{'SOUNDIT'}   = 1;

$Exceptions{'command-messagebox.xml'}{'allcaps'}{'OK'}    = 1;

$Exceptions{'command-midiclose.xml'}{'allcaps'}{'MIDI'}   = 1;

$Exceptions{'command-midimessage.xml'}{'allcaps'}{'MIDI'} = 1;

$Exceptions{'command-midiopen.xml'}{'allcaps'}{'MIDI'}   = 1;
$Exceptions{'command-midiopen.xml'}{'allcaps'}{'MAPPER'} = 1;
$Exceptions{'command-midiopen.xml'}{'allcaps'}{'.MID'}   = 1;
$Exceptions{'command-midiopen.xml'}{'allcaps'}{'.MDI'}   = 1;

$Exceptions{'command-namelist.xml'}{'allcaps'}{'BAR'} = 1;
$Exceptions{'command-namelist.xml'}{'allcaps'}{'FOO'} = 1;

$Exceptions{'command-names.xml'}{'allcaps'}{'BAR'} = 1;
$Exceptions{'command-names.xml'}{'allcaps'}{'FOO'} = 1;

$Exceptions{'command-netconnecton.xml'}{'allcaps'}{'DNS'}   = 1;
$Exceptions{'command-netconnecton.xml'}{'allcaps'}{'HOSTS'} = 1;
$Exceptions{'command-netconnecton.xml'}{'allcaps'}{'IP'}    = 1;
$Exceptions{'command-netconnecton.xml'}{'allcaps'}{'TCP'}   = 1;

$Exceptions{'command-netstartup.xml'}{'allcaps'}{'DNS'}  = 1;

$Exceptions{'command-noyield.xml'}{'allcaps'}{'CPU'}     = 1;

$Exceptions{'command-openappend.xml'}{'allcaps'}{'LF'}   = 1;
$Exceptions{'command-openappend.xml'}{'allcaps'}{'CRLF'} = 1;

$Exceptions{'command-openread.xml'}{'allcaps'}{'CRLF'} = 1;
$Exceptions{'command-openread.xml'}{'allcaps'}{'LF'}   = 1;

$Exceptions{'command-openupdate.xml'}{'allcaps'}{'CRLF'} = 1;
$Exceptions{'command-openupdate.xml'}{'allcaps'}{'LF'}   = 1;

$Exceptions{'command-openwrite.xml'}{'allcaps'}{'CRLF'} = 1;
$Exceptions{'command-openwrite.xml'}{'allcaps'}{'LF'}   = 1;

$Exceptions{'command-output.xml'}{'allcaps'}{'MYPROGRAM'} = 1;

$Exceptions{'command-pause.xml'}{'allcaps'}{'MYPROGRAM'} = 1;
$Exceptions{'command-pause.xml'}{'allcaps'}{'OK'} = 1;

$Exceptions{'command-perspective.xml'}{'allcaps'}{'GROW.LGO'} = 1;

$Exceptions{'command-playwave.xml'}{'allcaps'}{'WAVE'} = 1;

$Exceptions{'command-pllist.xml'}{'allcaps'}{'BAR'} = 1;
$Exceptions{'command-pllist.xml'}{'allcaps'}{'FOO'} = 1;

$Exceptions{'command-portopen.xml'}{'allcaps'}{'COM1'}   = 1;
$Exceptions{'command-portopen.xml'}{'allcaps'}{'COM4'}   = 1;
$Exceptions{'command-portopen.xml'}{'allcaps'}{'LPT1'}   = 1;
$Exceptions{'command-portopen.xml'}{'allcaps'}{'LPT3'}   = 1;

$Exceptions{'command-portreadchar.xml'}{'allcaps'}{'OK'}  = 1;

$Exceptions{'command-portwritechar.xml'}{'allcaps'}{'OK'} = 1;

$Exceptions{'command-portmode.xml'}{'allcaps'}{'COM'}    = 1;
$Exceptions{'command-portmode.xml'}{'allcaps'}{'DATA'}   = 1;
$Exceptions{'command-portmode.xml'}{'allcaps'}{'DOS'}    = 1;
$Exceptions{'command-portmode.xml'}{'allcaps'}{'MODE'}   = 1;
$Exceptions{'command-portmode.xml'}{'allcaps'}{'PARITY'} = 1;
$Exceptions{'command-portmode.xml'}{'allcaps'}{'SPEED'}  = 1;

$Exceptions{'command-polyend.xml'}{'allcaps'}{'SQUARE'} = 1;

$Exceptions{'command-polystart.xml'}{'allcaps'}{'SQUARE'} = 1;

$Exceptions{'command-polyview.xml'}{'allcaps'}{'SQUARE'} = 1;

$Exceptions{'command-primitivep.xml'}{'allcaps'}{'FWD'} = 1;

$Exceptions{'command-procedurep.xml'}{'allcaps'}{'BAR'} = 1;

$Exceptions{'command-procedures.xml'}{'allcaps'}{'BAR'} = 1;
$Exceptions{'command-procedures.xml'}{'allcaps'}{'FOO'} = 1;

$Exceptions{'command-questionbox.xml'}{'allcaps'}{'OK'} = 1;

$Exceptions{'command-radiobuttoncreate.xml'}{'allcaps'}{'CHECKONTHINGS'} = 1;

$Exceptions{'command-radiobuttonget.xml'}{'allcaps'}{'CHECKONTHINGS'} = 1;

$Exceptions{'command-radiobuttonset.xml'}{'allcaps'}{'CHECKONTHINGS'} = 1;

$Exceptions{'command-reduce.xml'}{'allcaps'}{'MAX'} = 1;

$Exceptions{'command-save.xml'}{'allcaps'}{'MYPROGRAM1'} = 1;
$Exceptions{'command-save.xml'}{'allcaps'}{'MYPROGRAM2'} = 1;

$Exceptions{'command-savel.xml'}{'allcaps'}{'MYPROGRAM1'} = 1;
$Exceptions{'command-savel.xml'}{'allcaps'}{'MYPROGRAM2'} = 1;

$Exceptions{'command-selectbox.xml'}{'allcaps'}{'OK'} = 1;

$Exceptions{'command-setbitmode.xml'}{'allcaps'}{'XOR'} = 1;

$Exceptions{'command-setlight.xml'}{'allcaps'}{'SQUARE'} = 1;

$Exceptions{'command-setmargins.xml'}{'allcaps'}{'TV'} = 1;

$Exceptions{'command-settimer.xml'}{'allcaps'}{'OK'} = 1;

$Exceptions{'command-setturtlemode.xml'}{'allcaps'}{'XOR'} = 1;

$Exceptions{'command-slowdraw.xml'}{'allcaps'}{'BK'} = 1;
$Exceptions{'command-slowdraw.xml'}{'allcaps'}{'FD'} = 1;

$Exceptions{'command-sound.xml'}{'allcaps'}{'PC'} = 1;

$Exceptions{'command-soundoff.xml'}{'allcaps'}{'NT'} = 1;
$Exceptions{'command-soundoff.xml'}{'allcaps'}{'XP'} = 1;

$Exceptions{'command-soundon.xml'}{'allcaps'}{'NT'} = 1;
$Exceptions{'command-soundon.xml'}{'allcaps'}{'PC'} = 1;
$Exceptions{'command-soundon.xml'}{'allcaps'}{'XP'} = 1;

$Exceptions{'command-standout.xml'}{'bannedword'}{'terminal'} = 1;

$Exceptions{'command-startup.xml'}{'allcaps'}{'MYPROGRAM'} = 1;

$Exceptions{'command-step.xml'}{'allcaps'}{'MYPROGRAM'} = 1;
$Exceptions{'command-step.xml'}{'allcaps'}{'OK'}        = 1;

$Exceptions{'command-stepped.xml'}{'allcaps'}{'MYFORWARD'} = 1;

$Exceptions{'command-stop.xml'}{'allcaps'}{'MYPROGRAM'} = 1;

$Exceptions{'command-tag.xml'}{'allcaps'}{'STATES'} = 1;

$Exceptions{'command-test.xml'}{'allcaps'}{'MYTEST'} = 1;

$Exceptions{'command-thing.xml'}{'allcaps'}{'FOO'} = 1;

$Exceptions{'command-throw.xml'}{'allcaps'}{'MYPROGRAM1'}  = 1;
$Exceptions{'command-throw.xml'}{'allcaps'}{'MYPROGRAM2'}  = 1;
$Exceptions{'command-throw.xml'}{'allcaps'}{'SYSTEM'}      = 1;
$Exceptions{'command-throw.xml'}{'allcaps'}{'TOPLEVEL'}    = 1;

$Exceptions{'command-to.xml'}{'allcaps'}{'ECHO'} = 1;
$Exceptions{'command-to.xml'}{'allcaps'}{'PROC'} = 1;

$Exceptions{'command-tone.xml'}{'allcaps'}{'PC'} = 1;

$Exceptions{'command-trace.xml'}{'allcaps'}{'MYPRINT'} = 1;

$Exceptions{'command-traced.xml'}{'allcaps'}{'MYFORWARD'} = 1;

$Exceptions{'command-transfer.xml'}{'allcaps'}{'?IN'}  = 1;
$Exceptions{'command-transfer.xml'}{'allcaps'}{'?OUT'} = 1;

$Exceptions{'command-unicon.xml'}{'allcaps'}{'HIDEANDSHOW'} = 1;

$Exceptions{'command-unstep.xml'}{'allcaps'}{'MYPROGRAM'} = 1;
$Exceptions{'command-unstep.xml'}{'allcaps'}{'OK'}        = 1;

$Exceptions{'command-untrace.xml'}{'allcaps'}{'MYPRINT'} = 1;

$Exceptions{'command-uppercase.xml'}{'allcaps'}{'HELLO'} = 1;

$Exceptions{'command-windowfileedit.xml'}{'allcaps'}{'DEMO'} = 1;
$Exceptions{'command-windowfileedit.xml'}{'logo'}            = 1;

$Exceptions{'command-windowset.xml'}{'allcaps'}{'HIDEANDRESTORE'} = 1;

$Exceptions{'command-yield.xml'}{'allcaps'}{'CPU'}     = 1;

$Exceptions{'commander.xml'}{'allcaps'}{'ENTER'}       = 1;

$Exceptions{'commandline-options.xml'}{'allcaps'}{'OK'}   = 1;
$Exceptions{'commandline-options.xml'}{'logo'}            = 1;

$Exceptions{'communication.xml'}{'allcaps'}{'DLL'}        = 1;
$Exceptions{'communication.xml'}{'allcaps'}{'PORT'}       = 1;
$Exceptions{'communication.xml'}{'allcaps'}{'RS'}         = 1;

$Exceptions{'control-structures.xml'}{'allcaps'}{'DOTPRODUCT'}     = 1;
$Exceptions{'control-structures.xml'}{'allcaps'}{'MATRIXMULTIPLY'} = 1;
$Exceptions{'control-structures.xml'}{'allcaps'}{'MIT'}            = 1;
$Exceptions{'control-structures.xml'}{'allcaps'}{'PROC'}           = 1;
$Exceptions{'control-structures.xml'}{'allcaps'}{'TRANSPOSE'}      = 1;
$Exceptions{'control-structures.xml'}{'logo'}                      = 1;

$Exceptions{'editor.xml'}{'allcaps'}{'CTRL'}   = 1;
$Exceptions{'editor.xml'}{'allcaps'}{'F1'}     = 1;

$Exceptions{'error-processing.xml'}{'allcaps'}{'DATUM'}    = 1;
$Exceptions{'error-processing.xml'}{'allcaps'}{'PROC'}     = 1;
$Exceptions{'error-processing.xml'}{'allcaps'}{'THROWTAG'} = 1;
$Exceptions{'error-processing.xml'}{'allcaps'}{'VALUE'}    = 1;
$Exceptions{'error-processing.xml'}{'allcaps'}{'VAR'}      = 1;

$Exceptions{'environment-commands.xml'}{'logo'} = 1;

$Exceptions{'introduction.xml'}{'allcaps'}{'FD'}          = 1;
$Exceptions{'introduction.xml'}{'allcaps'}{'LISP'}        = 1;
$Exceptions{'introduction.xml'}{'allcaps'}{'MIT'}         = 1;
$Exceptions{'introduction.xml'}{'allcaps'}{'PENTAGON'}    = 1;
$Exceptions{'introduction.xml'}{'allcaps'}{'PENTAGON?'}   = 1;
$Exceptions{'introduction.xml'}{'allcaps'}{'POLYGON'}     = 1;
$Exceptions{'introduction.xml'}{'allcaps'}{'RT'}          = 1;
$Exceptions{'introduction.xml'}{'allcaps'}{'SHAPES.LGO'}  = 1;
$Exceptions{'introduction.xml'}{'allcaps'}{'SQUARE'}      = 1;
$Exceptions{'introduction.xml'}{'allcaps'}{'TRIANGLE'}    = 1;
$Exceptions{'introduction.xml'}{'logo'}                   = 1;

$Exceptions{'logohelp.xml'}{'allcaps'}{'ANY'}             = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'DOCTYPE'}         = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'DTD'}             = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'EN'}              = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'ENTITY'}          = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'FITNESS'}         = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'GENERICNAME'}     = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'GNU'}             = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'LOGOEXE'}         = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'MA'}              = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'MERCHANTABILITY'} = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'OASIS'}           = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'PARTICULAR'}      = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'PRODUCTNAME'}     = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'PRODUCTVERSION'}  = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'PUBLIC'}          = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'PURPOSE'}         = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'SYSTEM'}          = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'USA'}             = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'V4.2'}            = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'WARRANTY'}        = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'WITHOUT'}         = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'XML'}             = 1;
$Exceptions{'logohelp.xml'}{'logo'}                       = 1;

$Exceptions{'networking-commands.xml'}{'allcaps'}{'DNS'}       = 1;
$Exceptions{'networking-commands.xml'}{'allcaps'}{'FTP'}       = 1;
$Exceptions{'networking-commands.xml'}{'allcaps'}{'HOSTS'}     = 1;
$Exceptions{'networking-commands.xml'}{'allcaps'}{'HOSTS.SAM'} = 1;
$Exceptions{'networking-commands.xml'}{'allcaps'}{'IP'}        = 1;
$Exceptions{'networking-commands.xml'}{'allcaps'}{'PING'}      = 1;
$Exceptions{'networking-commands.xml'}{'allcaps'}{'POPMAIL'}   = 1;
$Exceptions{'networking-commands.xml'}{'allcaps'}{'PPP'}       = 1;
$Exceptions{'networking-commands.xml'}{'allcaps'}{'SERVICES'}  = 1;
$Exceptions{'networking-commands.xml'}{'allcaps'}{'TCP'}       = 1;
$Exceptions{'networking-commands.xml'}{'allcaps'}{'TELNET'}    = 1;

$Exceptions{'main-menu.xml'}{'allcaps'}{'MS'}   = 1;
$Exceptions{'main-menu.xml'}{'allcaps'}{'HTML'} = 1;
$Exceptions{'main-menu.xml'}{'allcaps'}{'BMP'}  = 1;
$Exceptions{'main-menu.xml'}{'allcaps'}{'GIF'}  = 1;
$Exceptions{'main-menu.xml'}{'allcaps'}{'DEMO'} = 1;
$Exceptions{'main-menu.xml'}{'logo'}            = 1;

$Exceptions{'multimedia-commands.xml'}{'allcaps'}{'CD'}   = 1;
$Exceptions{'multimedia-commands.xml'}{'allcaps'}{'FX'}   = 1;
$Exceptions{'multimedia-commands.xml'}{'allcaps'}{'LSB'}  = 1;
$Exceptions{'multimedia-commands.xml'}{'allcaps'}{'MIDI'} = 1;
$Exceptions{'multimedia-commands.xml'}{'allcaps'}{'MSB'}  = 1;

$Exceptions{'tokenization.xml'}{'logo'} = 1;

# translation tables are completely exempt
$Exceptions{'translations-1032.xml'}  = 1;
$Exceptions{'translations-1033.xml'}  = 1;
$Exceptions{'translations-1034.xml'}  = 1;
$Exceptions{'translations-1036.xml'}  = 1;
$Exceptions{'translations-2070.xml'}  = 1;
$Exceptions{'translations.xml'}       = 1;

$Exceptions{'windows-commands.xml'}{'allcaps'}{'GUI'}       = 1;
$Exceptions{'windows-commands.xml'}{'allcaps'}{'SETUP'}     = 1;
$Exceptions{'windows-commands.xml'}{'allcaps'}{'WIN'}       = 1;
$Exceptions{'windows-commands.xml'}{'allcaps'}{'MYRED'}     = 1;
$Exceptions{'windows-commands.xml'}{'allcaps'}{'MYEND'}     = 1;
$Exceptions{'windows-commands.xml'}{'allcaps'}{'DRAWTHING'} = 1;

$Exceptions{'workspace-management.xml'}{'logo'}             = 1;



sub LogError($$$)
{
  print "$_[0]:$_[1] error: $_[2]\n";
  $main::TotalErrors++;
}

sub LogWarning($$$)
{
  print "$_[0]:$_[1] warning: $_[2]\n";
  $main::TotalWarnings++;
}

sub FilenameToCommand($)
{
  my $filename = shift or die "not enough inputs";

  # check there is a special-case for this filename
  if ($Exceptions{$filename} and
      $Exceptions{$filename}{propername}) {
    return  $Exceptions{$filename}{propername};
  }

  # there is no special-case, process this as normal
  if ($filename =~ m/^command-(.*)\.xml$/) {
    return uc $1;
  }

  return undef;
}

sub CommandToId($)
{
  my $command = shift or die "not enough inputs";

  if ($command eq '`') {
    return 'command-backtick';
  }

  return 'command-' . lc $command;
}

# Infer some Exceptions from the alternate spellings of words.
foreach my $command (keys %AlternateSpellings) {
  foreach my $alternate (@{$AlternateSpellings{$command}}) {
    # an alternate spelling of a command is always allowed within the definition of the command
    $Exceptions{'command-' . lc $command . '.xml'}{'allcaps'}{$alternate} = 1;

    # all alternate spellings are permissible in 'abbreviations.xml'
    $Exceptions{'abbreviations.xml'}{'allcaps'}{$alternate} = 1;

    # fill in the canonical spelling
    $CanonicalSpelling{$alternate} = $command;

  }
}


#
# Determine the proper name for all documented commands
#
foreach my $filename (<command-*.xml>) {

  my $propername = FilenameToCommand($filename);

  if (not $propername) {
    LogError($filename, 1, "could not determine command");
  }

  # note the existence of this command
  if ($propername) {
    $Commands{$propername} = 1;
  }
}


#
# Process each XML file
#
foreach my $filename (<*.xml>) {

  if ($Exceptions{$filename} and $Exceptions{$filename} == 1) {
    # the file is completely exempt from all checks
    next;
  }

  my $fh = new IO::File "< $filename" or die $!;

  my $command = FilenameToCommand($filename);

  my $exampleIsStarted       = 0;
  my $exampleContainsCommand = 0;

  my $linenumber = 0;
  foreach my $line (<$fh>) {

    $linenumber++;
    if ($command) {

      # this is the documentation for a command
      my $expectedId = CommandToId($command);

      # the first line of all commands should be a <section> tag with the proper id attribute
      if ($linenumber == 1) {
        if ($line =~ m/^<section id="(.*?)">/) {

          my $id = $1;

          if ($id ne $expectedId) {
            LogError($filename, $linenumber, "The `id' attribute of the first section is `$id'.  It should be `$expectedId'.");
          }
        }
        else {
          LogError($filename, $linenumber, "first line is not <section id='$expectedId'>.");
        }
      }


      # the second line of all commands should be a <title> element for the command.
      if ($linenumber == 2) {
        if ($line =~ m!<title>(.*?)</title>!) {

          my $title = $1;

          if ($title ne $command) {
            LogError($filename, $linenumber, "contains command for `$title', not `$command'.");
          }
        }
        else {
          LogError($filename, $linenumber, "second line is not <title>$command</title>.");
        }
      }

      # the third line of all commands should be an <indexterm> element for the command.
      if ($linenumber == 3) {
        if ($line =~ m!<indexterm><primary>(.*?)</primary></indexterm>!) {

          my $indexterm = $1;

          if ($indexterm ne $command) {
            LogError($filename, $linenumber, "contains indexterm for `$indexterm', not `$command'.");
          }
        }
        else {
          LogError($filename, $linenumber, "third line is not <indexterm><primary>$command</primary></indexterm>.");
        }
      }

      # the first listed command in the synopsis should match the title
      if ($line =~ m!<synopsis>\s*\(?\s*<command>(.*?)</command>!) {
        my $synopsisCommand = $1;

        if ($synopsisCommand ne $command) {
          LogError($filename, $linenumber, "first command listed in synopsis is `$synopsisCommand'.  It should match the filename.");
        }
      }

      # the "Example" section for every command must contain that command
      if ($line =~ m!<term>Example</term>!) {
        $exampleIsStarted = 1;
      }
      if ($exampleIsStarted) {
        if ($line =~ m/\Q$command\E/) {
          $exampleContainsCommand = 1;
        }
      }

      # Find variations of the phrase "see also" that should be replaced
      # with a "See Also" section
      if ($line =~ m/see/i and $line =~ m/also/i and $line !~ m/<term>/) {
        LogWarning($filename, $linenumber, "Use of term 'see also'.  Consider using a formal 'See Also' section, instead.");
      }
    }

    while ($line =~ m!<link linkend="(.*?)">(.*?)</link>!g) {
      my $linkend = $1;
      my $text    = $2;

      # if the link text is all upper-case, then it is probably a command
      if ($text =~ m/^[\.\?\-A-Z]+$/) {

        if ($linkend ne CommandToId($text) and
            $linkend ne 'commandline' . lc $text) {
          LogError($filename, $linenumber, "link and linkend don't match: `$text' -> `$linkend'");
        }
      }
    }

    # Search for the use of undocumented commands word-by-word within the line
    # (these are probably misspellings)
    while ($line =~ m!
                      (^|[^\.\w?])                      # preceeded by non-word
                      ([\.?]?[A-Z](?:\.??[A-Z0-9?])+)   # logo token
                      (?=([^\.\w?]|$))                  # followed by non-word
                      !gx) {
      my $token = $2;

      if ($1 eq '&' and $3 eq ';') {
        # this is an XML element, which is always safe to ignore.
        next;
      }

      if (not $Commands{$token} and not $Exceptions{$filename}{allcaps}{$token}) {

        if ($CanonicalSpelling{$token}) {
          # this is an alternate form of a command
          LogWarning($filename, $linenumber, "use of alternate spelling `$token'.  Use `$CanonicalSpelling{$token}' instead.");
        }
        else {
          # this is an unknown word
          LogWarning($filename, $linenumber, "use of undocumented all-caps word `$token'");

          # Add this to the list of exceptions so that we don't warn multiple
          # times for the same word.
          $Exceptions{$filename}{allcaps}{$token} = 1;
        }
      }
    }

    # Find <book>, <preface>, <chapter>, and <section> elements with no id attribute
    while ($line =~ m!<(book|preface|chapter|section)>!g) {
      LogWarning($filename, $linenumber, "<$1> element does not have id attribute");
    }

    # Find non-standard uses of the word Logo
    while ($line =~ m!\b(\w*logo\w*)\b!gi) {
      my $logo = $1;

      if ($logo ne 'LOGOEXE' and not $Exceptions{$filename}{logo}) {
        LogWarning($filename, $linenumber, "non-standard usage of term `$logo'");
      }
    }


    # Find places where <userinput>, <synopsis>, or <programlisting> includes
    # undesired leading whitespace.
    # This extra space looks bad when it is rendered within a grey box.
    if ($line =~ m!<(userinput|synopsis|programlisting)>\s+!) {
      LogWarning($filename, $linenumber, "<$1> section includes leading whitespace");
    }

    # Find places where <userinput> or <synopsis> includes undesired trailing whitespace.
    # This extra space looks bad when it is rendered within a grey box.
    if ($line =~ m!<^(userinput|synopsis)>!) {
      LogWarning($filename, $linenumber, "<$1> section includes trailing whitespace");
    }


    # Find use of banned words
    foreach my $bannedWord (@main::BannedWords) {
      while ($line =~ m!\b(\Q$bannedWord\E)\b!gi) {

        if (not $Exceptions{$filename}{bannedword}{$bannedWord}) {
          LogError($filename, $linenumber, "use of banned word: $bannedWord");
        }
      }
    }

    # Find trailing whitespace
    if ($line =~ m/ +$/) {
      LogWarning($filename, $linenumber, "trailing whitespace found");
    }
  }

  if ($command and $exampleIsStarted and not $exampleContainsCommand) {
    LogWarning($filename, 0, "Example section does not reference $command");
  }

  $fh->close;
}

#
# Report all undocumented procedure
#
foreach my $filename (<../src/Logolib/*>) {

  # only files (not directories) are library routines
  if ( -f $filename ) {

    # strip off the path to get the name of the library routine
    if (my ($procedureName) = $filename =~ m!.*/(.*)!) {

      # make sure that this library routine appears in the manual
      if (not $Commands{$procedureName}) {
        LogWarning($filename, 0, "Library routine $procedureName is not documented");
      }
    }
  }
}

my $linenumber = 0;
my $fh = new IO::File "< ../src/init.cpp" or die $!;
foreach my $line (<$fh>) {
  $linenumber++;

  # look for the primitives table.  Each entry looks something like this
  #
  #    { "and", 0, 2, -1, PREFIX_PRIORITY, land, LOCALIZED_ALTERNATE_AND },
  if ($line =~ m/^\s*{\s*"([^"]+)"\s*,.*},/) {
    my $procedureName = uc($1);

    # make sure that this primitive appears in the manual
    if (not $Commands{$procedureName} and not $CanonicalSpelling{$procedureName}) {
      LogWarning('init.cpp', $linenumber, "Primitive $procedureName is not documented");
    }
  }
}

print "Found $main::TotalErrors errors and $main::TotalWarnings warnings\n";
exit 1 if $main::TotalErrors != 0;
exit 0;
