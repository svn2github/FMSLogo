############################################################
# make-translation-tables.pl
#
# This script reads the source code and startup files for
# each language, LANG, and outputs the "LANG-to-English" and
# "English-to-LANG" tables that are built into the online
# documentation.
############################################################
use locale;
use utf8;
use IO::File;
use strict;

# commands that are undocumented and shouldn't be put into
# the translation tables.
$main::UndocumentedCommands{buttonp}     = 1;
$main::UndocumentedCommands{demo}        = 1;
$main::UndocumentedCommands{ellispa2}    = 1;
$main::UndocumentedCommands{filep}       = 1;
$main::UndocumentedCommands{goto}        = 1;
$main::UndocumentedCommands{maketurtle}  = 1;
$main::UndocumentedCommands{mousecopy}   = 1;
$main::UndocumentedCommands{nodes}       = 1;
$main::UndocumentedCommands{setclip}     = 1;
$main::UndocumentedCommands{settextfont} = 1;
$main::UndocumentedCommands{tag}         = 1;
$main::UndocumentedCommands{textfont}    = 1;
$main::UndocumentedCommands{tutor}       = 1;

sub PrintShadowedProcedures($$$) {
  my $LocaleName         = shift or die "not enough arguments";
  my $English            = shift or die "not enough arguments";
  my $LocalizedToEnglish = shift or die "not enough arguments";

  # foreach localized command check to see if:
  # 1) It's also the name of an English command
  # 2) It's not a localization of that English command
  foreach my $localizedCommand (keys %{$LocalizedToEnglish}) {
    foreach my $englishCommand (values %{$English}) {

      # It's okay if predicates that end in "?" shadow the "p"
      # form of the English predicate.
      # The Spanish translation does this because "p" has no meaning.
      if ($localizedCommand =~ m/^(.*)\?$/ and $$LocalizedToEnglish{$localizedCommand} eq "$1p") {
        next;
      }

      if ($englishCommand eq $localizedCommand and
          $$LocalizedToEnglish{$localizedCommand} ne $englishCommand) {
        print "WARNING: $LocaleName shadows the English command `$localizedCommand' as a translations for `$$LocalizedToEnglish{$localizedCommand}'\n";
      }
    }
  }
}

sub PrintTranslationsAsText($$$) {

  my $LocaleId           = shift or die "not enough arguments";
  my $EnglishToLocalized = shift or die "not enough arguments";
  my $LocalizedToEnglish = shift or die "not enough arguments";

  my $fromenglish = new IO::File "> fromenglish-$LocaleId.txt" or die $!;
  my $longestlength = 0;
  foreach my $english (sort keys %{$EnglishToLocalized}) {
    $longestlength = length $english if $longestlength < length $english;
  }
  foreach my $english (sort keys %{$EnglishToLocalized}) {
    my $spacing = ' ' x ($longestlength - length $english);
    foreach my $translation (@{$$EnglishToLocalized{$english}}) {
      $fromenglish->print("$english $spacing $translation\n");
    }
  }
  $fromenglish->close();


  my $toenglish = new IO::File "> toenglish-$LocaleId.txt" or die $!;
  $longestlength = 0;
  foreach my $translation (sort keys %{$LocalizedToEnglish}) {
    $longestlength = length $translation if $longestlength < length $translation;
  }
  foreach my $translation (sort keys %{$LocalizedToEnglish}) {
    my $spacing = ' ' x ($longestlength - length $translation);
    $toenglish->print("$translation $spacing $$LocalizedToEnglish{$translation}\n");
  }
  $toenglish->close();
}

sub GetLinkend($) {
  my $EnglishCommand = shift or die "not enough arguments";

  my $linkend = lc "command-$EnglishCommand";

  $linkend =~ s/\?$/p/; # predicates are indexed by their 'P' suffix.

  return $linkend
}

sub PrintTranslationsAsDocBook($$$$) {

  my $LocaleName         = shift or die "not enough arguments";
  my $LocaleId           = shift or die "not enough arguments";
  my $EnglishToLocalized = shift or die "not enough arguments";
  my $LocalizedToEnglish = shift or die "not enough arguments";


  my $docbook = '';

  $docbook .= "<appendix id='translations'>\n";
  $docbook .= "<title>Commands: English to $LocaleName</title>\n";

  $docbook .= "<informaltable>\n";
  $docbook .= "  <indexterm><primary>From English</primary></indexterm>\n";
  $docbook .= "  <tgroup cols='2'>\n";
  $docbook .= "   <thead>\n";
  $docbook .= "     <row>\n";
  $docbook .= "       <entry>English Command</entry>\n";
  $docbook .= "       <entry>$LocaleName Command</entry>\n";
  $docbook .= "     </row>\n";
  $docbook .= "   </thead>\n";
  $docbook .= "  <tbody>\n";

  # add a row for each english to localized translation
  foreach my $english (sort keys %{$EnglishToLocalized}) {

    my $englishLinkend = GetLinkend($english);

    foreach my $translation (@{$$EnglishToLocalized{$english}}) {
      utf8::encode($translation);
      $docbook .= "     <row>\n";
      $docbook .= "       <entry><link linkend='$englishLinkend'>$english</link></entry>\n";
      $docbook .= "       <entry>$translation</entry>\n";
      $docbook .= "     </row>\n";
    }
  }

  $docbook .= "  </tbody>\n";
  $docbook .= "  </tgroup>\n";
  $docbook .= "</informaltable>\n";
  $docbook .= "</appendix>\n";

  $docbook .= "\n";

  $docbook .= "<appendix>\n";
  $docbook .= "<title>Commands: $LocaleName to English</title>\n";
  $docbook .= "<indexterm><primary>To English</primary></indexterm>\n";
  $docbook .= "<informaltable>\n";
  $docbook .= "  <tgroup cols='2'>\n";
  $docbook .= "   <thead>\n";
  $docbook .= "     <row>\n";
  $docbook .= "       <entry>$LocaleName Command</entry>\n";
  $docbook .= "       <entry>English Command</entry>\n";
  $docbook .= "     </row>\n";
  $docbook .= "   </thead>\n";
  $docbook .= "  <tbody>\n";

  # add a row for each localized to English translation
  foreach my $translation (sort keys %{$LocalizedToEnglish}) {

    my $english        = $$LocalizedToEnglish{$translation};
    my $englishLinkend = GetLinkend($english);

    utf8::encode($translation);

    $docbook .= "     <row>\n";
    $docbook .= "       <entry>$translation</entry>\n";
    $docbook .= "       <entry><link linkend='$englishLinkend'>$english</link></entry>\n";
    $docbook .= "     </row>\n";
  }

  $docbook .= "  </tbody>\n";
  $docbook .= "  </tgroup>\n";
  $docbook .= "</informaltable>\n";
  $docbook .= "</appendix>\n";

  my $translations = new IO::File "> translations-$LocaleId.xml" or die $!;
  $translations->print($docbook);
  $translations->close();
}

sub MakeTranslationTables($$$) {

  my $LocaleName  = shift or die "not enough arguments";
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

      $englishword or die "Found a localization for $symbolicname that is not present in the English localization";

      # only add documented procedures to the translation tables.
      if (not $main::UndocumentedCommands{lc $englishword}) {

        unless (m/NOT_YET_LOCALIZED/) {
          if (lc $englishword ne lc $localizedname) {
            $englishtolocalized{$englishword} = () if not $englishtolocalized{$englishword};
            push @{$englishtolocalized{$englishword}}, $localizedname;

            $localizedtoenglish{$localizedname} = $englishword;
          }
        }
      }
    }
  }
  $localizedfile->close();


  #
  # extract the library routines and primitives that were translated with COPYDEF
  #
  $localizedfile = new IO::File "startup-$LocaleId.logoscript" or die $!;
  while (<$localizedfile>) {
    if (m/copydef\s+"([\S]+)\s+"([\S_]+)/i) {
      my $newname  = lc $1;
      my $original = lc $2;

      # they probably copydef'd the localized version
      while ($localizedtoenglish{$original} &&
             $localizedtoenglish{$original} ne $original) {
        $original = $localizedtoenglish{$original};
      }

      if (lc $original ne lc $newname) {

        # TODO: error-out if $original isn't an English command

        $englishtolocalized{$original} = () if not $englishtolocalized{$original};
        push @{$englishtolocalized{$original}}, $newname;

        $localizedtoenglish{$newname} = $original;
      }
    }
  }
  $localizedfile->close();

  PrintTranslationsAsText($LocaleId, \%englishtolocalized, \%localizedtoenglish);

  PrintTranslationsAsDocBook(
    $LocaleName,
    $LocaleId,
    \%englishtolocalized,
    \%localizedtoenglish);

  PrintShadowedProcedures($LocaleName, \%english, \%localizedtoenglish);
}


MakeTranslationTables('Greek',      'gr', 1032);
MakeTranslationTables('Spanish',    'es', 1034);
MakeTranslationTables('French',     'fr', 1036);
MakeTranslationTables('Portuguese', 'pt', 2070);
