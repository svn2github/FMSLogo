----------------------------------------------------------------------
FMSLogo Version 7.0.0 for Microsoft Windows
----------------------------------------------------------------------

   I. Kit Description/Location
  II. New features/bugs fixed
 III. Standard features
  IV. Recommended usage
   V. Reporting bugs
  VI. Sources
 VII. Minimum System Requirements
VIII. Acknowledgements

I. Kit Description/Location (http://sourceforge.net/projects/fmslogo)

  fmslogo-7.0.0.exe   - Installer for the Logo environment
  fmslogo-7.0.0.zip   - ZIP of the Logo environment

II. New features/bugs fixed:

  Changed in 7.0.0
  o Drop support for the Win 9X versions of Windows.
  o Drop support for the original Pentium processor.
  o Drop support for display depths less than 16-bit true color.
  o Fix bug #212 up/down arrow is no longer sluggish when the commander history
    has a very long line.
  o Fix bug #373; the screen saver now supports all commands that the main
    environment supports, although some commands which have no meaning in
    this environment do nothing (for example CLEARTEXT does nothing because
    there's no commander).
  o Fix bug #401; the commander history no longer hides very long lines
    (>65535 characters).
  o Fix bug #437; FMSLogo no longer crashes if BITMAPTURTLE has no bitmap
    (it now behaves as if it had a zero-sized bitmap).
  o Fix bug #471; the uninstaller now removes the preferences that are stored
    in the registry.
  o Fix bug #472; SETPIXEL now behaves correctly in PENREVERSE mode.
  o Fix bug #473; KEYBOARDVALUE once again returns values for a handful of
    characters on a US keyboard (;/`[]\=) that are consistent with previous
    versions of FMSLogo.
  o Fix bug #477; POLYEND now throws an error if the polygon has two vertices
    (same as if the polygon has one vertex).
  o Implement feature #37; the installer now shows a clear "completed" page
    when it is done.
  o Implement feature #59; use a new icon that doesn't look like a mismash of
    red, white, and black.  The icon was provided by Jan Grabe.
  o Implement feature #32; the "X" close button on the undocked commander's
    title bar is now disabled.
  o Change the working directory in the screensaver to be the directory which
    holds the screen saver program.  This makes LOAD with a relative path work.
  o Add syntax coloring and matching paren highlights to the minieditor.
  o Various improvements to the installer, including a configurable start menu
    folder and faster start time.
  o Minor improvements to the manual.

  For a complete history of changes across all versions of FMSLogo, see
  https://sourceforge.net/p/fmslogo/source/HEAD/tree/trunk/logo/src/CHANGELOG.TXT

III. Standard features

  * Supports TCP/IP WinSock Networking.
  * Supports Text in all available fonts and sizes.
  * Supports 1024 independent Turtles.
  * Supports Bitmapped Turtles.
  * Supports Cut, Paste and stretching bitmaps.
  * Supports Clipboard Text and Bitmaps.
  * Supports MIDI devices.
  * Supports Direct I/O for Controlling External hardware.
  * Supports Serial and Parallel Port communications.
  * Supports Zooming.
  * Supports Tail recursion (optimizes most recursive functions).
  * Supports User error handling.
  * Supports "Standard" Logo parsing.
  * Supports Floodfill.
  * Supports Save and restore images in .BMP format files.
  * Supports standard Windows Hypertext Help.
  * Supports standard Windows Printing.
  * Supports separate library and work area.
  * Supports construction of Windows Dialog Boxes.
  * Supports Event Driven programming (Mouse, Keyboard, Timer).
  * Supports MultiMedia Devices (.WAV sound files, CD-ROM control etc.)
  * Supports Event Timers allowing multiprocessing.
  * Supports 3D Perspective drawing (Wireframe and Solids).
  * Supports Animated GIF generation.

IV. Recommended usage

  * Ages 6 and up
     o Beginner     - Forward 100, Right 90
     o Intermediate - Explore mathematics, art, music, robotics, language, and more
     o Expert       - Create games

V. Reporting bugs

  Report bugs at http://sourceforge.net/projects/fmslogo/

VI. Sources

  Source code is available.  It's your legal right!  (See LICENSE.TXT).

  The FMSLogo sources were written/compiled with:

    MinGW w64 (for .EXE and screen saver)
    wxWidgets (GUI toolkit for .EXE and screen saver)
    DocBook, xsltproc, and Microsoft Help Workshop (for online help)
    Nullsoft Scriptable Install System (NSIS) (for the installer)

VII. Minimum System Requirements

   Windows XP with 512 MB of RAM.

VIII. Acknowledgements

  I wish to extend my sincerest thanks to everyone who has used, supported,
  criticized, praised, filed a bug on, or otherwise contributed to either
  FMSLogo or MSWLogo.

  Thanks to:
    Alexandre Soares
    Andreas Micheler
    Andy Owen
    Anthony Barnett
    Ayurzanaeva Aryuna
    Bertrand Carette
    Bob Gorman
    Bruce Mardle
    Carl Bogardus
    Clem Rutter
    Daniel Ajoy
    Domagoj Kuna
    Hensley Bass
    Igor Baglaev
    Jan Grabe
    Jason Gervich
    Jim Foster
    Juan J. Paredes G.
    Kari Hoijarvi
    Lion Nik Kucev
    Lionel Laske
    Michael Malin
    Mike Sandy
    Narayanan Chitoor
    Pavel Boytchev
    Ralf Kurth
    Relja Medic
    Stefano Federici
    Stephan Vogel
    Tankhasaev Ayur
    Theodoros Chatzigiannakis

  Special thanks to:
    George Mills
    Brian Harvey
    Jim Muller
    Erich Neuwirth
    Yehuda Katz
