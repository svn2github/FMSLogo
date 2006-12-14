############################################################
# clean-html.pl
#
# This script removes some unnecessary tags from the HTML
# that is used by HTML Help.  This is done to decrease the
# overall size of the .CHM and to improve rendering speed.
#
# Ideally, this would be done in XLST and the unnecessary
# tags simply wouldn't be generated, but I don't know how
# to do that.
############################################################

use IO::File;
use strict;

sub CleanHtmlFile($) {

   my $Filename = shift or die "too few arguments";

   my $htmlfile = new IO::File $Filename or die $!;
   my @lines = <$htmlfile>;
   $htmlfile->close();


   # reopen the file for writing
   $htmlfile = new IO::File "> $Filename" or die $!;
   foreach my $line (@lines)
   {
      $line =~ s/<meta name="generator" [^>]*>//;
      $line =~ s/<link rel="start" [^>]*>//;
      $line =~ s/<link rel="up" [^>]*>//;
      $line =~ s/<link rel="next" [^>]*>//;
      $line =~ s/<link rel="prev" [^>]*>//;
      $line =~ s/<body [^>]*>/<body>/;
      $line =~ s/<(\w+) class="chapter" lang="en">/<$1>/g;
      $line =~ s/<(\w+) class="command">/<$1>/g;
      $line =~ s/<(\w+) class="informaltable">/<$1>/g;
      $line =~ s/<(\w+) class="parameter">/<$1>/g;
      $line =~ s/<(\w+) class="section" lang="en">/<$1>/g;
      $line =~ s/<(\w+) class="section">/<$1>/g;
      $line =~ s/<(\w+) class="term">/<$1>/g;
      $line =~ s/<(\w+) class="title">/<$1>/g;
      $line =~ s/<(\w+) class="titlepage">/<$1>/g;
      $line =~ s/<(\w+) class="toc">/<$1>/g;
      $line =~ s/<(\w+) class="userinput">/<$1>/g;
      $line =~ s/<(\w+) class="variablelist">/<$1>/g;

      $htmlfile->print($line);
   }
   $htmlfile->close();
}

while (<*.html>)
{
  CleanHtmlFile($_);
}

while (<*.htm>)
{
  CleanHtmlFile($_);
}
