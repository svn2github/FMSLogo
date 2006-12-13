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

while (<*.html>)
{
   my $filename = $_;

   my $htmlfile = new IO::File $filename or die $!;
   my @lines = <$htmlfile>;
   $htmlfile->close();


   # reopen the file for writing
   $htmlfile = new IO::File "> $filename" or die $!;
   foreach my $line (@lines)
   {
      $line =~ s/<meta name="generator" [^>]*>//;
      $line =~ s/<link rel="start" [^>]*>//;
      $line =~ s/<link rel="up" [^>]*>//;
      $line =~ s/<link rel="next" [^>]*>//;
      $line =~ s/<link rel="prev" [^>]*>//;
      $htmlfile->print($line);
   }
   $htmlfile->close();
}
