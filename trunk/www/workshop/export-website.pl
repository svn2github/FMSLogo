#!/usr/bin/perl -w
##############################################################################
# This script prepares the Workshop website for export to the Web servers.
#
# Today, all it does is add the width and height attributes to img tags,
# but in the future, it's supposed to repackage the entire site to a separate
# directory, rebuilding the HTML pages from source.

use strict;
use IO::File;
use Image::Size;

# Reads the contents of a file into a string and returns it.
sub ReadFileIntoString($)
{
  my $FileName = shift or die "not enough arguments";

  # Read the file into a single scalar.
  my $fh = new IO::File "< $FileName" or die $!;
  my $fileContents = join '', <$fh>;
  $fh->close;

  return $fileContents;
}

# Writes the contents of a string to a file.
sub WriteStringToFile($$)
{
  my $FileName     = shift or die "not enough arguments";
  my $FileContents = shift or die "not enough arguments";

  my $fh = new IO::File "> $FileName" or die $!;
  print $fh $FileContents or die $!;
  $fh->close;
}


# Adds a width and height attribute to an IMG tag based on the
# contents of the image.
sub FixImgTag($)
{
    my $imgTag = shift or die "not enough arguments";

    # Extract the image source path from the img tag.
    #  <img src="filename.png">
    $imgTag =~ m/src\s*=\s*"([^"]+)"/ or die "Unable to locate 'src' in $imgTag";
    my $srcPath = $1;

    # Calculate the width and height of the image.
    my $sizeAttribute = Image::Size::html_imgsize($srcPath);

    # Strip out any existing width or height tags
    $imgTag =~ s/width\s*=\s*"\d+"\s*//g;
    $imgTag =~ s/height\s*=\s*"\d+"\s*//g;

    # add the new width/height
    $imgTag =~ s!\s*/>! $sizeAttribute />!;

    return $imgTag;
}

##################################################################3
# Main Execution Starts Here
##################################################################3


#
# Process each HTML file
#
foreach my $filename (<*.shtml>)
{
  # Read the file into a string for manipulation.
  my $fileContents = ReadFileIntoString($filename);

  # Add/fix the width/height attributes so that the browser won't
  # have to recaluclate the layout as images are read in.
  $fileContents =~ s/(<\s*img\s[^>]*>)/FixImgTag($1)/gem;

  # Write the file back out.
  WriteStringToFile($filename, $fileContents);
}
