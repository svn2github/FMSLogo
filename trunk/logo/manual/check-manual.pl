#! /usr/bin/perl -W
###############################################################################
# Searches that the manual for style violations:
#
# * Files of the form "command-<word>.xml" document the command <word>
# * All uppercase words are documented commands.
# * All commands in <link> tags have the expected linkend attribute.
# * No abbreviations of commands are allowed.
# * Emphasis is not given with upper-case.
# * The <title> element matches the filename.
#
# Missing checks:
# * Spelling is correct.
# * Examples include at least one instance of the command that they document.
# * Only the first reference to a command in any section is hyperlinked.
# * Commands are not hyperlinked when they occurs within their own definition.
# * All occurances of "Logo" and "MSWLogo" are correct.
# * All instances of the <parameter> tag refer to actual parameters.
#
###############################################################################


use strict;
use IO::File;

$main::TotalErrors   = 0;
$main::TotalWarnings = 0;

my %Commands = ();

my %AlternateSpellings = ();
$AlternateSpellings{ARRAYP}         = ['ARRAY?'];
$AlternateSpellings{BACKSLASHEDP}   = ['BACKSLASHED?'];
$AlternateSpellings{BACK}           = ['BK'];
$AlternateSpellings{BEFOREP}        = ['BEFORE?'];
$AlternateSpellings{BUTFIRST}       = ['BF'];
$AlternateSpellings{BUTFIRSTS}      = ['BFS'];
$AlternateSpellings{BUTLAST}        = ['BL'];
$AlternateSpellings{CLEARSCREEN}    = ['CS'];
$AlternateSpellings{CLEARTEXT}      = ['CT'];
$AlternateSpellings{CONTINUE}       = ['CO'];
$AlternateSpellings{DEFINEDP}       = ['DEFINED?'];
$AlternateSpellings{DOWNPITCH}      = ['DOWN'];
$AlternateSpellings{EDIT}           = ['ED'];
$AlternateSpellings{EMPTYP}         = ['EMPTY?'];
$AlternateSpellings{EQUALP}         = ['EQUAL?'];
$AlternateSpellings{ERASEFILE}      = ['ERF'];
$AlternateSpellings{ERASE}          = ['ER'];
$AlternateSpellings{FLOODCOLOR}     = ['FLOODCOLOUR'];
$AlternateSpellings{FORWARD}        = ['FD'];
$AlternateSpellings{FULLSCREEN}     = ['FS'];
$AlternateSpellings{HIDETURTLE}     = ['HT'];
$AlternateSpellings{IFFALSE}        = ['IFF'];
$AlternateSpellings{IFTRUE}         = ['IFT'];
$AlternateSpellings{LEFTROLL}       = ['LR'];
$AlternateSpellings{LEFT}           = ['LT'];
$AlternateSpellings{LISTP}          = ['LIST?'];
$AlternateSpellings{MACROP}         = ['MACRO?'];
$AlternateSpellings{MEMBERP}        = ['MEMBER?'];
$AlternateSpellings{NAMEP}          = ['NAME?'];
$AlternateSpellings{NUMBERP}        = ['NUMBER?'];
$AlternateSpellings{OUTPUT}         = ['OP'];
$AlternateSpellings{PENCOLOR}       = ['PENCOLOUR'];
$AlternateSpellings{PENDOWNP}       = ['PENDOWN?'];
$AlternateSpellings{PENDOWN}        = ['PD'];
$AlternateSpellings{PENERASE}       = ['PE'];
$AlternateSpellings{PENPAINT}       = ['PPT'];
$AlternateSpellings{PENREVERSE}     = ['PX'];
$AlternateSpellings{PENUP}          = ['PU'];
$AlternateSpellings{PRIMITIVEP}     = ['PRIMITIVE?'];
$AlternateSpellings{PRINT}          = ['PR'];
$AlternateSpellings{PROCEDUREP}     = ['PROCEDURE?'];
$AlternateSpellings{READCHARS}      = ['RCS'];
$AlternateSpellings{READCHAR}       = ['RC'];
$AlternateSpellings{READLIST}       = ['RL'];
$AlternateSpellings{READWORD}       = ['RW'];
$AlternateSpellings{RIGHTROLL}      = ['RR'];
$AlternateSpellings{RIGHT}          = ['RT'];
$AlternateSpellings{SCREENCOLOR}    = ['SCREENCOLOUR'];
$AlternateSpellings{SENTENCE}       = ['SE'];
$AlternateSpellings{SETFLOODCOLOR}  = ['SETFLOODCOLOUR',  'SETFC'];
$AlternateSpellings{SETPENCOLOR}    = ['SETPENCOLOUR',    'SETPC'];
$AlternateSpellings{SETSCREENCOLOR} = ['SETSCREENCOLOUR', 'SETSC'];
$AlternateSpellings{SHOWNP}         = ['SHOWN?'];
$AlternateSpellings{SHOWTURTLE}     = ['ST'];
$AlternateSpellings{SPLITSCREEN}    = ['SS'];
$AlternateSpellings{SUBSTRINGP}     = ['SUBSTRING?'];
$AlternateSpellings{TEXTSCREEN}     = ['TS'];
$AlternateSpellings{UPPITCH}        = ['UP'];
$AlternateSpellings{WORDP}          = ['WORD?'];

my %CanonicalSpelling = ();

my %Exceptions = ();
$Exceptions{'command-.eq.xml'}{'allcaps'}{'WARNING'}        = 1;

$Exceptions{'command-.macro.xml'}{'allcaps'}{'MY.REPEAT'}   = 1;
$Exceptions{'command-.macro.xml'}{'allcaps'}{'REPEAT.DONE'} = 1;
$Exceptions{'command-.macro.xml'}{'allcaps'}{'EXAMPLE'}     = 1;

$Exceptions{'command-.setbf.xml'}{'allcaps'}{'WARNING'}     = 1;

$Exceptions{'command-.setfirst.xml'}{'allcaps'}{'WARNING'}  = 1;

$Exceptions{'command-.setitem.xml'}{'allcaps'}{'WARNING'}   = 1;

$Exceptions{'command-backtick.xml'}{'propername'}         = '`';

$Exceptions{'command-beforep.xml'}{'allcaps'}{'ABC'}      = 1;

$Exceptions{'command-bury.xml'}{'allcaps'}{'BAR'}         = 1;
$Exceptions{'command-bury.xml'}{'allcaps'}{'FOO'}         = 1;

$Exceptions{'command-buryall.xml'}{'allcaps'}{'BAR'}      = 1;
$Exceptions{'command-buryall.xml'}{'allcaps'}{'FOO'}      = 1;

$Exceptions{'command-cascade.xml'}{'allcaps'}{'VOWELP'}   = 1;
$Exceptions{'command-cascade.xml'}{'allcaps'}{'PIGLATIN'} = 1;

$Exceptions{'command-yield.xml'}{'allcaps'}{'CPU'}        = 1;

$Exceptions{'communication.xml'}{'allcaps'}{'DLL'}        = 1;
$Exceptions{'communication.xml'}{'allcaps'}{'PORT'}       = 1;
$Exceptions{'communication.xml'}{'allcaps'}{'RS'}         = 1;

$Exceptions{'editor.xml'}{'allcaps'}{'CTRL'}              = 1;

$Exceptions{'error-processing.xml'}{'allcaps'}{'DATUM'}    = 1;
$Exceptions{'error-processing.xml'}{'allcaps'}{'PROC'}     = 1;
$Exceptions{'error-processing.xml'}{'allcaps'}{'THROWTAG'} = 1;
$Exceptions{'error-processing.xml'}{'allcaps'}{'VALUE'}    = 1;
$Exceptions{'error-processing.xml'}{'allcaps'}{'VAR'}      = 1;

$Exceptions{'logohelp.xml'}{'allcaps'}{'DOCTYPE'}         = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'DTD'}             = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'EN'}              = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'ENTITY'}          = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'FITNESS'}         = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'GNU'}             = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'MA'}              = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'MERCHANTABILITY'} = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'OASIS'}           = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'PARTICULAR'}      = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'PUBLIC'}          = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'SYSTEM'}          = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'USA'}             = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'WARRANTY'}        = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'WITHOUT'}         = 1;
$Exceptions{'logohelp.xml'}{'allcaps'}{'XML'}             = 1;

$Exceptions{'windows-commands.xml'}{'allcaps'}{'SQUARE'}  = 1;



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
  if ($Exceptions{$filename} and $Exceptions{$filename}{propername}) {
    return  $Exceptions{$filename}{propername};
  }

  # there is no special-case, process this as normal
  if ($filename =~ m/^command-(.*)\.xml$/) {
    return uc $1;
  }

  return undef;
}

# Infer some Exceptions from the alternate spellings of words.
foreach my $command (keys %AlternateSpellings) {
  foreach my $alternate (@{$AlternateSpellings{$command}}) {
    # an alternate spelling of a command is always allowed within the definition of the command
    $Exceptions{'command-' . lc $command . '.xml'}{'allcaps'}{$alternate} = 1;

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

  my $fh = new IO::File "< $filename" or die $!;

  my $linenumber = 0;
  foreach my $line (<$fh>) {

    $linenumber++;

    my $command = FilenameToCommand($filename);
    if ($command) {

      # this is the documentation for a command
      my $expectedId = "command-" . lc $command;

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

      # the first listed command in the synopsis should match the title
      if ($line =~ m!<synopsis>\s*\(?\s*<command>(.*?)</command>!) {
        my $synopsisCommand = $1;

        if ($synopsisCommand ne $command) {
          LogError($filename, $linenumber, "first command listed in synopsis is `$synopsisCommand'.  It should match the filename.");
        }
      }
    }

    while ($line =~ m!<link linkend="(.*?)">(.*?)</link>!g) {
      my $linkend = $1;
      my $text    = $2;

      # if the link text is all upper-case, then it is probably a command
      if ($text eq uc $text) {

        if ($linkend ne "command-" . lc($text)) {
          LogError($filename, $linenumber, "link and linkend don't match: `$text' -> `$linkend'");
        }
      }
    }

    while ($line =~ m![^\.\w](\.??[A-Z](\.??[A-Z?])+)[\.\W]!g) {
      my $token = $1;

      if (not $Commands{$token} and not $Exceptions{$filename}{allcaps}{$token}) {

        if ($CanonicalSpelling{$token}) {
          # this is an alternate form of a command
          LogWarning($filename, $linenumber, "use of alternate spelling `$token'.  Use `$CanonicalSpelling{$token}' instead.");
        }
        else {
          # this is an unknown word
          LogWarning($filename, $linenumber, "use of undocumented all-caps word `$token'");
        }
      }
    }

    if (0) {
      # Find non-standard uses of the word Logo
      while ($line =~ m!\b(\w*logo\w*)\b!gi) {
        my $logo = $1;

        if ($logo ne 'MSWLogo' and not $Exceptions{$filename}{logo}) {
          LogWarning($filename, $linenumber, "non-standard usage of term `$logo'");
        }
      }
    }
  }

  $fh->close;
}
