#! /usr/bin/perl -W
###############################################################################
# Searches that the manual for style violations:
#
# * Files of the form "command-<word>.xml" document the command <word>
# * All uppercase words are documented commands.
# * All commands in <link> tags have the expected linkend attribute.
# * No abbreviations of commands are allowed.
# * Emphasis is not given with upper-case.
#
# Missing checks:
# * Spelling is correct.
# * Examples include at least one instance of the command that they document.
# * Only the first reference to a command in any section is hyperlinked.
# * All instances of Logo and MSWLogo are correct.
#
###############################################################################


use strict;
use IO::File;

$main::TotalErrors   = 0;
$main::TotalWarnings = 0;

my %Commands = ();

my %Exceptions = ();
$Exceptions{'command-.eq.xml'}{'allcaps'}{'WARNING'}        = 1;

$Exceptions{'command-.macro.xml'}{'allcaps'}{'MY.REPEAT'}   = 1;
$Exceptions{'command-.macro.xml'}{'allcaps'}{'REPEAT.DONE'} = 1;
$Exceptions{'command-.macro.xml'}{'allcaps'}{'EXAMPLE'}     = 1;

$Exceptions{'command-.setbf.xml'}{'allcaps'}{'WARNING'}     = 1;

$Exceptions{'command-.setfirst.xml'}{'allcaps'}{'WARNING'}  = 1;

$Exceptions{'command-.setitem.xml'}{'allcaps'}{'WARNING'}   = 1;

$Exceptions{'command-backtick.xml'}{'propername'}           = '`';

$Exceptions{'command-beforep.xml'}{'allcaps'}{'ABC'}        = 1;

$Exceptions{'command-yield.xml'}{'allcaps'}{'CPU'}          = 1;

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

#
# Determine the proper name for all commands
#
foreach my $filename (<command-*.xml>) {

  my $propername;

  # extract the command name from the file contents
  my $fh = new IO::File "< $filename" or die $!;

  my $linenumber = 0;
  foreach my $line (<$fh>) {
    $linenumber++;

    if ($line =~ m!<synopsis>\s*\(?\s*<command>(.*?)</command>!) {

      $propername = $1;

      if ($filename ne "command-" . lc $propername . ".xml" and
          (not defined $Exceptions{$filename} or $filename ne $Exceptions{$filename}{'propername'})) {
        LogError($filename, $linenumber, "contains command for $propername");
      }

      # We found a command name so we can break out of the loop.
      # (The first listed command is the canonical name)
      last;
    }
  }

  $fh->close;

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

    while ($line =~ m!<link linkend="(.*?)">(.*?)</link>!g) {
      my $linkend = $1;
      my $command = $2;

      # if the link text is all upper-case, then it is probably a command
      if ($command eq uc $command) {

        if ($linkend ne "command-" . lc($command)) {
          LogError($filename, $linenumber, "link and linkend don't match: `$command' -> `$linkend'");
        }
      }
    }

    while ($line =~ m![^\.\w](\.??[A-Z](\.??[A-Z])+)[\.\W]!g) {
      my $command = $1;

      if (not $Commands{$command} and not $Exceptions{$filename}{allcaps}{$command}) {
        LogWarning($filename, $linenumber, "use of undocumented all-caps word `$command'");
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
