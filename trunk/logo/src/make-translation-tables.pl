use strict;
use IO::File;

sub MakeTranslationTables($$) {

  my $CountryCode = shift or die "not enough arguments";
  my $LocaleId    = shift or die "not enough arguments";

  my %english            = ();
  my %englishtolocalized = ();
  my %localizedtoenglish = ();

  #
  # Build a table of everything that has already been translated
  #
  my $englishfile = new IO::File "localizedstrings-en.h" or die $!;
  while (<$englishfile>) {
    chomp;
    if (m/^\#define\s+LOCALIZED_ALTERNATE_([\w\d_]+)\s*"([^"]+)"/) {
      $english{$1} = $2;
    }
  }
  $englishfile->close();

  #
  # extract the primitives that were translated
  #
  my $localizedfile = new IO::File "localizedstrings-$CountryCode.h" or die $!;
  while (<$localizedfile>) {
    if (m/^\#define\s+LOCALIZED_ALTERNATE_([\w\d_]+)\s*"([^"]+)"/) {
      my $symbolicname  = $1;
      my $localizedname = $2;
      my $englishword   = $english{$symbolicname};

      $englishword or die "Found a translated $symbolicname that is not English";

      unless (m/NOT_YET_LOCALIZED/) {
        $englishtolocalized{$englishword} = () if not $englishtolocalized{$englishword};
        push @{$englishtolocalized{$englishword}}, $localizedname;

        $localizedtoenglish{$localizedname} = $englishword;
      }
    }
  }
  $localizedfile->close();


  #
  # extract the primitives that were translated
  #
  $localizedfile = new IO::File "startup-$LocaleId.logoscript" or die $!;
  while (<$localizedfile>) {
    if (m/copydef\s+"([\S]+)\s+"([\S_]+)/i) {
      my $newname  = lc $1;
      my $original = lc $2;

      # they probably copydef'd the localized version
      if ($localizedtoenglish{$original}) {
        $original = $localizedtoenglish{$original};
      }

      $englishtolocalized{$original} = () if not $englishtolocalized{$original};
      push @{$englishtolocalized{$original}}, $newname;

      $localizedtoenglish{$newname} = $original;
    }
  }
  $localizedfile->close();


  my $fromenglish = new IO::File "> fromenglish-$LocaleId.txt" or die $!;
  my $longestlength = 0;
  foreach my $english (sort keys %englishtolocalized) {
    $longestlength = length $english if $longestlength < length $english;
  }
  foreach my $english (sort keys %englishtolocalized) {
    my $spacing = ' ' x ($longestlength - length $english);
    foreach my $translation (@{$englishtolocalized{$english}}) {
      $fromenglish->print("$english $spacing $translation\n");
    }
  }
  $fromenglish->close();


  my $toenglish = new IO::File "> toenglish-$LocaleId.txt" or die $!;
  $longestlength = 0;
  foreach my $translation (sort keys %localizedtoenglish) {
    $longestlength = length $translation if $longestlength < length $translation;
  }
  foreach my $translation (sort keys %localizedtoenglish) {
    my $spacing = ' ' x ($longestlength - length $translation);
    $toenglish->print("$translation $spacing $localizedtoenglish{$translation}\n");
  }
  $toenglish->close();
}


MakeTranslationTables('fr', 1036);
MakeTranslationTables('gr', 1032);
