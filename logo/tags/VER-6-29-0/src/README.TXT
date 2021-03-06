----------------------------------------------------------------------
FMSLogo Version 6.29.0 for Microsoft Windows
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

  fmslogo-6.29.0.exe       (binary kit: Windows self-extracting installer)
  fmslogo-6.29.0.zip       (binary kit: Windows ZIP archive)

II. New features/bugs fixed:

  * Changed in 6.29.0
    o QUESTIONBOX, READCHAR, READCHARS, READWORD, READRAWLINE, and READLIST
      no longer limit the user's input to 255 characters.
    o STATICCREATE, STATICUPDATE, YESNOBOX, MESSAGEBOX, and others no longer
      truncate their inputs at 255 character.
    o Fix bug #3571274; SHELL, PORTOPEN, and many other procedures no longer
      truncate their inputs based on PRINTWIDTHLIMIT or PRINTDEPTHLIMIT.
    o Fix bug #3570553; ALLOPEN no longer leaks memory.
    o Fix bug #3566411; Closing editor no longer claims that the contents
      have changed after "File->Save to Workspace" in expert mode.
    o Fix bug #3564270; FMSLogo no longer leaks memory when saving the
      editor encounters an error which the user ignores.
    o Fix bug #3563059; "ARRAY 1073741825" no longer crashes.
    o Fix bug #3558071; QUESTIONBOX now resizes to fit the question.
    o Fix bug #3551212; FMSLogo once again places the editor's caret at the
      first error when saving the contents fails due to a syntax error.
    o Fix bug #3150920; FMSLogo no longer leaks memory or corrupts memory
      when halted while evaluating a parameter's default value that requires
      a separate function call.
    o Fix bug #2943335; Selecting a long line in the commander history no
      longer inserts a space into the line at the point where it was wrapped.
      This is only fixed in the wxWidgets version of FMSLogo.
    o Fix bug #1895669; NETSHUTDOWN no longer has a race condition that can
      corrupt internal memory.
    o Fix bug #1568629; FMSLogo no longer leaks memory when its internal
      garbage collection stack is exhausted.
    o Fix bug #1471162; FMSLogo no longer leaks memory when calling procedures
      that have parameters with default values.
    o Minor improvements to the manual.

  For a complete history of changes across all versions of FMSLogo, see
  http://fmslogo.cvs.sourceforge.net/*checkout*/fmslogo/logo/src/CHANGELOG.TXT

III. Standard features

  * Supports Windows 95/98/ME/NT/2000/XP/WS03/Vista/Windows 7.
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
  * Supports 1, 4, 8, 16, 24 bits per pixels colors.
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

    Borland C++ 5.02 for windows (for .EXE)
    Borland Turbo 32bit Assembler (for .EXE)
    DocBook, xsltproc, and Microsoft Help Workshop (for online help)
    Nullsoft Scriptable Install System (NSIS) (for the installer)

VII. Minimum System Requirements

   Pentium class processor with minimum of 16 MB RAM running Windows 95.

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
    Hensley Bass
    Igor Baglaev
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
