use strict;
use IO::File;

if (@ARGV != 2) {
  print "Usage: $0 country_code locale_name\n";
  exit 1;
}

my $newLocale  = $ARGV[0];
my $localeName = $ARGV[1];

my %translations = ();

#
# Build a table of everything that has already been translated
#
my $existingStringTable = new IO::File "localizedstrings-$newLocale.h";
if ($existingStringTable) {

  while (<$existingStringTable>) {
    chomp;
    if (m/^\#define\s+([\w\d_]+)\s*(.*)$/) {
      $translations{$1} = $2;
    }
  }
  $existingStringTable->close();
}

my $newFile = new IO::File "> localizedstrings-$newLocale.h" or die $!;


#
# Write out the new localization using the English one as a basis
#
my $original = new IO::File "localizedstrings-en.h" or die $!;
while (<$original>) {
  chomp;
  my $line = $_;

  if ($line =~ m/^\#define\s+([\w\d_]+)(\s*).*$/) {
    if ($translations{$1}) {
      # this has already been localized
      print $newFile "#define $1$2$translations{$1}\n";
    }
    else {
      # this has not yet been translated
      print $newFile "$line // NOT_YET_LOCALIZED\n";
    }
  }
  elsif ($line =~ m/localized strings for English/) {
    # translate the locale English
    $line =~ s/English/$localeName/;
    print $newFile "$line\n";
  }
  else {
    # this line is not localizable
    print $newFile "$line\n";
  }
}

$original->close();
$newFile->close();
