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
        // interface directly with the hardware
      
#ifndef NOASM
        WORD count = 1193180L / frequency;
        unsigned char count_lo = LOBYTE(count);
        unsigned char count_hi = HIBYTE(count);

        _asm
        {
            mov al, 0xB6
            out 0x43, al
            mov al, count_lo
            out 0x42, al
            mov al, count_hi
            out 0x42, al
            xor al, al
            in al, 0x61
            or al, 0x03
            out 0x61, al
        }

        clock_t endTime = duration + clock();
        while (endTime > clock())
        {
            // empty loop
        }

        _asm
        {
            xor al, al
            in al, 0x61
            xor al, 0x03
            out 0x61, al
        }
#endif // NOASM
    }

    return TRUE;
}

void Myoutportb(short portid, unsigned char value)
{
    // the assembly code would crash on Windows NT
    if (g_OsVersionInformation.dwPlatformId != VER_PLATFORM_WIN32_NT)
    {
#ifndef NOASM
        _asm
        {
            mov dx, portid
            mov al, value
            out dx, al
        }
#endif // NOASM
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
#ifndef NOASM
        _asm
        {
            mov dx, portid
            xor al, al
            in al, dx
            mov value, al
        }
#endif // NOASM
    }

    return value;
}

void Myoutport(short portid, short value)
{
    // the assembly code would crash on Windows NT
    if (g_OsVersionInformation.dwPlatformId != VER_PLATFORM_WIN32_NT)
    {
#ifndef NOASM
        _asm
        {
            mov dx, portid
            mov ax, value
            out dx, ax
        }
#endif // NOASM
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
#ifndef NOASM
        _asm
        {
            mov dx, portid
            xor ax, ax
            in ax, dx
            mov value, ax
        }
#endif // NOASM
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

