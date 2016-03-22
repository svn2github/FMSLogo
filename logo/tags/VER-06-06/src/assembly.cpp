/*
*
*  Copyright (C) 1995 by the Regents of the University of California
*  Copyright (C) 1995 by George Mills
*
*      This program is free software; you can redistribute it and/or modify
*      it under the terms of the GNU General Public License as published by
*      the Free Software Foundation; either version 2 of the License, or
*      (at your option) any later version.
*
*      This program is distributed in the hope that it will be useful,
*      but WITHOUT ANY WARRANTY; without even the implied warranty of
*      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*      GNU General Public License for more details.
*
*      You should have received a copy of the GNU General Public License
*      along with this program; if not, write to the Free Software
*      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
*/

#include "allwind.h"

BOOL MyBeep(DWORD dwFreq, DWORD dwDuration)
   {
#ifndef NOASM
   WORD count = 1193180L / dwFreq;
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

   clock_t endTime = dwDuration + clock();
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
#endif

   return TRUE;
   }

void Myoutportb(short portid, unsigned char value)
   {
#ifndef NOASM
   _asm
      {
      mov dx, portid
      mov al, value
      out dx, al
      }
#endif
   }

unsigned char Myinportb(short portid)
   {
   unsigned char value = 0;

#ifndef NOASM
   _asm
      {
      mov dx, portid
      xor al, al
      in al, dx
      mov value, al
      }
#endif

   return value;
   }

void Myoutport(short portid, short value)
   {
#ifndef NOASM
   _asm
      {
      mov dx, portid
      mov ax, value
      out dx, ax
      }
#endif
   }

short Myinport(short portid)
   {
   short value = 0;

#ifndef NOASM
   _asm
      {
      mov dx, portid
      xor ax, ax
      in ax, dx
      mov value, ax
      }
#endif

   return value;
   }

short Myingameport(short portid, short mask)
   {
   short value = 0;

#ifndef NOASM
   _asm
       {
       mov bx, mask   /* Store mask in bx   */
       mov dx, portid /* Store port in dx   */
       mov cx, 0x0000 /* Init counter       */
anal1: in al, dx      /* Sample port        */
       test al, bl    /* Test Idle?         */
       jz anal2       /* Branch if done     */
       loop anal1     /* Loop and dec cx    */
       jmp error      /* Time out (cx wrap?)*/
anal2: mov cx, 0x0000 /* Init counter       */
       cli            /* Disable interrupts */
       mov ax, mask   /* Get mask into al   */
       out dx, al     /* Reset Gameport     */
anal3: in al, dx      /* Sample Gameport    */
       test al, bl    /* Test if done       */
       jz anal4       /* Branch if done     */
       loop anal3     /* loop and dec cx    */
       sti            /* Restore interrupts */
       jmp error      /* Time out           */
anal4: sti            /* restor interrupts  */
       neg cx         /* negate counter     */
       jmp anal5      /* return             */
error: mov cx, 0xffff /* return error code  */
anal5: mov value, cx  /* return value       */
      }
#endif

   return value;
   }

