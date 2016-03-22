#! /usr/bin/perl -w

use strict;

my $TDUMP       = 'TDUMP.EXE';
my $OBJDIR      = 'debug';
my $DEFFILENAME = 'logo32d.def';

open DEFFILE, ">$DEFFILENAME" or die "Couldn't open `$DEFFILENAME' for writing: $!";

print DEFFILE "EXETYPE WINDOWS\n"                   or die $!;
print DEFFILE "CODE PRELOAD MOVEABLE DISCARDABLE\n" or die $!;
print DEFFILE "DATA PRELOAD MOVEABLE MULTIPLE\n"    or die $!;
print DEFFILE "DESCRIPTION 'Logo for Windows'\n"     or die $!;

print DEFFILE "EXPORTS\n" or die $!;


foreach my $objfile (<$OBJDIR/*.obj>)
{
    open DUMP, "$TDUMP /m /oiPUBDEF $objfile |" or 
        die "Couldn't run $TDUMP on $objfile: $!";
    while (<DUMP>)
    {
        # Exported symbols are of the form:
        # 002C53 PUBDEF TThreeDSolid::TThreeDSolid()' Segment: _TEXT:0000
        if (/^[\dA-F]{6}\s+PUBDEF\s+'([^']+)'/o)
        {
            print DEFFILE "  '$1'\n";
        }
    }

    close DUMP;
}

close DEFFILE;
