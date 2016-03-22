// Copyright (C) 1995 by the Regents of the University of California
// Copyright (C) 1995 by George Mills
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include <time.h>
#include "startup.h"


// Input a byte from a port
static unsigned char asm_inportb(unsigned short port)
{
   unsigned char value = 0;

#ifndef NOASM
#if defined __BORLANDC__
        _asm
        {
            mov dx,    port
            xor al,    al
            in  al,    dx
            mov value, al
        }
#elif defined __GNUC__
        asm(
            "inb %1, %0;"
            : "=a"(value)   // output
            : "d" (port)    // input
            :
            );
#else
#  error Assembly code not supported on this compiler.
#endif // assembly by compiler
#endif // NOASM

   return value;
}

// Input a word from a port
static unsigned short asm_inport(unsigned short port)
{
   unsigned short value = 0;

#ifndef NOASM
#if defined __BORLANDC__
        _asm
        {
            mov dx,    port
            xor ax,    ax
            in  ax,    dx
            mov value, ax
        }
#elif defined __GNUC__
        asm(
            "in %1, %0;"
            : "=a"(value)  // output
            : "d" (port)   // input
            :
            );
#else
#  error Assembly code not supported on this compiler.
#endif // assembly by compiler
#endif // NOASM

   return value;
}

// Write a byte to a port
static void asm_outportb(unsigned short port, unsigned char value)
{
#ifndef NOASM
#if defined __BORLANDC__
        _asm
        {
            mov dx, port
            mov al, value
            out dx, al
        }
#elif defined __GNUC__
        asm(
            "outb %1, %0;"
            :                         // outputs
            : "d" (port), "a"(value)  // inputs
            :                         // clobbered
            );
#else
#  error Assembly code not supported on this compiler.
#endif // assembly by compiler
#endif // NOASM
}

// Write a word to a port
static void asm_outport(unsigned short port, unsigned short value)
{
#ifndef NOASM
#if defined __BORLANDC__
        _asm
        {
            mov dx, port
            mov ax, value
            out dx, ax
        }
#elif defined __GNUC__
        asm(
            "out %1,%0;"
            :                         // outputs
            : "d" (port), "a"(value)  // inputs
            :                         // clobbered
            );
#else
#  error Assembly code not supported on this compiler.
#endif // assembly by compiler
#endif // NOASM
}

BOOL MyBeep(DWORD frequency, DWORD duration)
{
    // Beep() ignores frequency/duration on Win9X series
    if (g_OsVersionInformation.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        // use the Win32 Beep
        Beep(frequency, duration);
    }
    else
    {
        // interface directly with the Intel 8254 programmable interval timer.

        // The crystal oscilates at 1,193,182 Hz
        WORD count = 1193182L / frequency;
        unsigned char count_lo = LOBYTE(count);
        unsigned char count_hi = HIBYTE(count);

        // Write 0xB6 to port 0x43.
        // This sets the hardware into mode 3: Square Wave, and configures
        // counter 2 (port 0x42) to be read as two separate bytes.
        asm_outportb(0x43, 0xB6);

        // How long to wait to port 0x42 as two bytes
        asm_outportb(0x42, count_lo);
        asm_outportb(0x42, count_hi);

        // Read status byte from port 0x61, set the bottom two bits in
        // order to turn on the timer and the speaker, then write it back.
        unsigned char status = asm_inportb(0x61);
        asm_outportb(0x61, status | 0x03);

        // Wait for the time to pass
#ifdef __BORLANDC__
        // Borland's compiler defines CLOCKS_PER_SEC to be 0, but it's in ms.
        const clock_t duration_in_clocks = duration;
#else
        const int MS_PER_SECOND = 1000;
        const clock_t duration_in_clocks = duration * CLOCKS_PER_SEC / MS_PER_SECOND;
#endif
        clock_t endTime = duration_in_clocks + clock();
        while (endTime > clock())
        {
            // empty loop
        }

        // Turn off the timer and the speaker.
        status = asm_inportb(0x61);
        asm_outportb(0x61, status & 0xFC);
    }

    return TRUE;
}

void Myoutportb(short portid, unsigned char value)
{
    // the assembly code would crash on Windows NT
    if (g_OsVersionInformation.dwPlatformId != VER_PLATFORM_WIN32_NT)
    {
        asm_outportb(portid, value);
    }
}

unsigned char Myinportb(short portid)
{
    unsigned char value = 0;

    if (g_OsVersionInformation.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        // Add a Special case for reading the joystick port on WinNT.
        // Reading it directly would cause an access violation,
        // but we can read it through the Win32 API.
        if (portid == 0x201)
        {
            // hardware port for the joystick port
            UINT totalJoysticks = joyGetNumDevs();
            if (totalJoysticks == 0)
            {
                return 0;
            }

            JOYCAPS joystickCapabilities;

            MMRESULT result = joyGetDevCaps(
                JOYSTICKID1,
                &joystickCapabilities,
                sizeof joystickCapabilities);
            if (result != JOYERR_NOERROR)
            {
                return 0;
            }

            JOYINFOEX joystickInfo;
            joystickInfo.dwSize  = sizeof joystickInfo;
            joystickInfo.dwFlags = JOY_RETURNBUTTONS;

            result = joyGetPosEx(
                JOYSTICKID1,
                &joystickInfo);
            if (result == JOYERR_NOERROR)
            {
                // Reassemble the original value from the hardware port
                // It doesn't have to be exact, just good enough.
                int button1Released = (joystickInfo.dwButtons & JOY_BUTTON1) == 0;
                int button2Released = (joystickInfo.dwButtons & JOY_BUTTON2) == 0;
                int button3Released = (joystickInfo.dwButtons & JOY_BUTTON3) == 0;
                int button4Released = (joystickInfo.dwButtons & JOY_BUTTON4) == 0;

                value =
                    (button1Released << 4) |
                    (button2Released << 5) |
                    (button3Released << 6) |
                    (button4Released << 7);
            }
        }
    }
    else
    {
        value = asm_inportb(portid);
    }

    return value;
}

void Myoutport(short portid, short value)
{
    // the assembly code would crash on Windows NT
    if (g_OsVersionInformation.dwPlatformId != VER_PLATFORM_WIN32_NT)
    {
        asm_outport(portid, value);
    }
}

short Myinport(short portid)
{
    short value = 0;

    if (g_OsVersionInformation.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        // Add a Special case for reading the joystick port on WinNT.
        // Reading it directly would cause an access violation,
        // but we can read it through the Win32 API.
        if (portid == 0x201)
        {
            // hardware port for the joystick port
            UINT totalJoysticks = joyGetNumDevs();
            if (totalJoysticks == 0)
            {
                return 0;
            }

            JOYCAPS joystickCapabilities;

            MMRESULT result = joyGetDevCaps(
                JOYSTICKID1,
                &joystickCapabilities,
                sizeof joystickCapabilities);
            if (result != JOYERR_NOERROR)
            {
                return 0;
            }


            JOYINFOEX joystickInfo;
            joystickInfo.dwSize  = sizeof joystickInfo;
            joystickInfo.dwFlags = JOY_RETURNBUTTONS;
            
            result = joyGetPosEx(
                JOYSTICKID1,
                &joystickInfo);
            if (result == JOYERR_NOERROR)
            {
                // Reassemble the original value from the hardware port
                // It doesn't have to be exact, just good enough.
                int button1Released = (joystickInfo.dwButtons & JOY_BUTTON1) == 0;
                int button2Released = (joystickInfo.dwButtons & JOY_BUTTON2) == 0;
                int button3Released = (joystickInfo.dwButtons & JOY_BUTTON3) == 0;
                int button4Released = (joystickInfo.dwButtons & JOY_BUTTON4) == 0;

                value =
                    (button1Released << 4) |
                    (button2Released << 5) |
                    (button3Released << 6) |
                    (button4Released << 7);
            }
        }
    }
    else
    {
        value = asm_inport(portid);
    }

    return value;
}

int Myingameport(short portid, short mask)
{
    int value = -1;

    UINT totalJoysticks = joyGetNumDevs();
    if (totalJoysticks == 0)
    {
        return -1;
    }

    JOYCAPS joystickCapabilities;

    MMRESULT result = joyGetDevCaps(
        JOYSTICKID1,
        &joystickCapabilities,
        sizeof joystickCapabilities);
    if (result != JOYERR_NOERROR)
    {
        return -1;
    }

    JOYINFOEX joystickInfo;
    joystickInfo.dwSize  = sizeof joystickInfo;
    joystickInfo.dwFlags = JOY_RETURNX | JOY_RETURNY | JOY_RETURNZ | JOY_RETURNR;

    result = joyGetPosEx(
        JOYSTICKID1,
        &joystickInfo);
    if (result == JOYERR_NOERROR)
    {
        if (mask == 1)
        {
            if (joystickCapabilities.wXmin != joystickCapabilities.wXmax)
            {
                value = 
                    (joystickInfo.dwXpos - joystickCapabilities.wXmin) * 1000 /
                    (joystickCapabilities.wXmax - joystickCapabilities.wXmin);
            }
        }
        else if (mask == 2)
        {
            if (joystickCapabilities.wYmin != joystickCapabilities.wYmax)
            {
                value = 
                    (joystickInfo.dwYpos - joystickCapabilities.wYmin) * 1000 /
                    (joystickCapabilities.wYmax - joystickCapabilities.wYmin);
            }
        }
        else if (mask == 4)
        {
            if (joystickCapabilities.wRmin != joystickCapabilities.wRmax)
            {
                value = 
                    (joystickInfo.dwRpos - joystickCapabilities.wRmin) * 1000 /
                    (joystickCapabilities.wRmax - joystickCapabilities.wRmin);
            }
        }
        else if (mask == 8)
        {
            if (joystickCapabilities.wZmin != joystickCapabilities.wZmax)
            {
                value = 
                    (joystickInfo.dwZpos - joystickCapabilities.wZmin) * 1000 /
                    (joystickCapabilities.wZmax - joystickCapabilities.wZmin);
            }
        }
    }

    return value;
}
