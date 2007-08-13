use strict;
use IO::File;

my $exitCode = 0;

foreach my $filename (@ARGV) {

  next if -d $filename;

  my $lineNumber = 0;
  my $fh = new IO::File "<$filename" or die $!;
  while (<$fh>) {

    if (m/\b(ct)\b/i) {
      print "$filename:$lineNumber file uses CT, which means HIDETURTLE in French.\n";
      $exitCode = 1;
    }

    if (m/\b(bl)\b/i) {
      print "$filename:$lineNumber file uses BL, which means PENDOWN in Spanish.\n";
      $exitCode = 1;
    }

    if (m/\b(rc)\b/i) {
      print "$filename:$lineNumber file uses RC, which means SQRT in Spanish.\n";
      $exitCode = 1;
    }

    if (m/\b(se)\b/i) {
      print "$filename:$lineNumber file uses SE, which means IF in Portuguese.\n";
      $exitCode = 1;
    }

    if (m/\b(pd)\b/i) {
      print "$filename:$lineNumber file uses PD, which means RT in Portuguese.\n";
      $exitCode = 1;
    }

    if (m/\b(pe)\b/i) {
      print "$filename:$lineNumber file uses PE, which means LT in Portuguese.\n";
      $exitCode = 1;
    }

    $lineNumber++;
  }
  $fh->close;
}


exit $exitCode;
