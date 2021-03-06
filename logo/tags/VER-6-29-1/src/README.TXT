----------------------------------------------------------------------
FMSLogo Version 6.29.1 for Microsoft Windows
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

  fmslogo-6.29.1.exe   - Installer for the mainline Logo environment
  fmslogo-6.29.1.zip   - ZIP of the mainline Logo environment
  wxfmslogo-6.29.1.exe - Installer for the Beta wxWidgets-based Logo environment

II. New features/bugs fixed:

  * Changed in 6.29.1
    o Fix a bug in the wxWidgets version of FMSLogo where double-clicking on
      the commander history box to run TEXTSCREEN could crash.
    o Fix bug #3576174; The commander's splitter is now visible on Windows 7
      when using the wxWidgets version of FMSLogo.
    o Fix bug #3575314; The FMSLogo icon now appears in the Alt+Tab task
      selector in high DPI modes ("large text size" on Vista or later)
      when using the wxWidgets version of FMSLogo.
    o Fix bug #3575313; In the wxWidgets version of FMSLogo, the commander
      buttons can now be pressed with Enter.  Pressing them with Spacebar
      no longer presses them twice.  Pressing the Edall button with Spacebar
      no longer crashes.
    o Fix bug #3575310; The wxWidgets-based version of FMSLogo now works when
      installed to a folder with an even number of characters.
    o Fix bug #1602922; The commander buttons can now be pressed with the
      spacebar.  This is only fixed in the wxWidgets version of FMSLogo.
    o Fix bug #1327746; FMSLogo no longer beeps if you press a key when a
      commander button has focus.  This is only fixed in the wxWidgets
      version of FMSLogo.

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
    MinGW (for the screen saver)
    MinGW package of cygwin (for wxWidgets .EXE)
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
