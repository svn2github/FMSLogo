/*
*
*       Copyright (C) 1995 by the Regents of the University of California
*       Copyright (C) 1995 by George Mills
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

HMIDIOUT hMidiOut = 0;

NODE *lsound(NODE *arg)
   {
   /* open sound and get arg list */
   NODE *args = car(arg);

   /* must be a list that contains something */
   if (is_list(args) && (args != NIL))
      {

      /* count items in list and check that they are pairs */
      arg = args;
      int odd = 0;

      while (arg != NIL)
         {
         if (arg != NIL) arg = cdr(arg);
         if (arg != NIL) arg = cdr(arg); else odd = 1;
         }

      /* if sound creation ok and we have pairs continue */
      if (!odd)
         {
         arg = args;

         /* play each freq/duration pair */
         while (arg != NIL)
            {
            int duration = 0;

            int hertz = int_arg(arg);
            if (cdr(arg) != NIL)
               {
               duration = int_arg(arg = cdr(arg));
               }

            /* play it */
            tone(hertz, duration);

            if (arg != NIL)
               {
               arg = cdr(arg);
               }
            }
         }
      else
         {
         MainWindowx->CommandWindow->MessageBox("Not paired", "Sound Error");
         err_logo(STOP_ERROR, NIL);
         }
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox("Bad argument", "Sound Error");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *lmidiopen(NODE *args)
   {
   // if not open open it
   if (!hMidiOut)
      {
      UINT id = MIDIMAPPER;

      if (args != NIL)
         {
         id = int_arg(args);
         if (id > midiOutGetNumDevs())
            {
            MainWindowx->CommandWindow->MessageBox("Invalid Midi device", "Midi Error");
            err_logo(STOP_ERROR, NIL);
            }
         }

      MIDIOUTCAPS moc;
      UINT MidiError = midiOutGetDevCaps(id, &moc, sizeof(moc));
      if (!MidiError) 
         {
         MidiError = midiOutOpen(&hMidiOut, id, NULL, 0L, 0L);
         }

      if (MidiError)
         {
         char MidiErrorBuffer[MAX_BUFFER_SIZE];
         midiOutGetErrorText(MidiError, MidiErrorBuffer, MAX_BUFFER_SIZE);
         MainWindowx->CommandWindow->MessageBox(MidiErrorBuffer, "Midi Error");
         err_logo(STOP_ERROR, NIL);
         }
      else
         {
         NODE * targ = make_strnode(moc.szPname);
         NODE * val = parser(targ, false);
         return val;
         }
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox("Already Open", "Midi Error");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *lmidiclose(NODE *  /*args*/)
   {
   // if open close it 
   if (hMidiOut)
      {

      UINT MidiError = midiOutClose(hMidiOut);
      hMidiOut = 0;

      if (MidiError)
         {
         char MidiErrorBuffer[MAX_BUFFER_SIZE];
         midiOutGetErrorText(MidiError, MidiErrorBuffer, MAX_BUFFER_SIZE);
         MainWindowx->CommandWindow->MessageBox(MidiErrorBuffer, "Midi Error");
         err_logo(STOP_ERROR, NIL);
         }
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox("Already closed", "Midi Error");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *lmidimessage(NODE *arg)
   {
   NODE *args;
   UINT MidiError;
   char MidiErrorBuffer[MAX_BUFFER_SIZE];

   int i;
   int j;

   union
      {
      long mylong;
      char mybyte[4];
      }
   bytetolong;

   MIDIHDR *MidiOutHdr;
   BYTE *MidiOutData;

   HANDLE DataHandle;
   HANDLE HdrHandle;

   /* if midi open continue */

   if (hMidiOut)
      {
      args = car(arg);

      /* if a list with something in it continue */

      if (is_list(args) && (args != NIL))
         {

         /* if not system exclusive then use shortmsg else use longmsg */

         if (int_arg(args) != 0xF0)
            {

            /* pack 3 bytes at a time and send them as short messages */

            arg = args;

            while (arg != NIL)
               {
               bytetolong.mylong = 0L;
               bytetolong.mybyte[0] = int_arg(arg);
               if (cdr(arg) != NIL) bytetolong.mybyte[1] = int_arg(arg = cdr(arg));
               if (cdr(arg) != NIL) bytetolong.mybyte[2] = int_arg(arg = cdr(arg));
               MidiError = midiOutShortMsg(hMidiOut, bytetolong.mylong);
               if (MidiError) break;
               if (arg != NIL) arg = cdr(arg);
               }

            }
         else
            {

            /* count elements in list so we can allocate buffer */

            i = 0;
            arg = args;

            while (arg != NIL)
               {
               arg = cdr(arg);
               i++;
               }

            /* allocate structure buffer */

            HdrHandle = (HANDLE) GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT, sizeof(MIDIHDR));
            MidiOutHdr = (MIDIHDR *) GlobalLock((HGLOBAL) HdrHandle);

            DataHandle = (HANDLE) GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT, i);
            MidiOutData = (BYTE *) GlobalLock((HGLOBAL) DataHandle);

            /* pack the buffer array and set size */

            arg = args;

            for (j = 0; j < i; j++)
               {
               MidiOutData[j] = int_arg(arg);
               arg = cdr(arg);
               }

            MidiOutHdr->dwBufferLength = i;

            MidiOutHdr->lpData = MidiOutData;

            /* prepare it, send it out, and unprepare it */

            MidiError = midiOutPrepareHeader(hMidiOut, MidiOutHdr, sizeof(MIDIHDR));
            if (!MidiError) MidiError = midiOutLongMsg(hMidiOut, MidiOutHdr, sizeof(MIDIHDR));
            if (!MidiError) MidiError = midiOutUnprepareHeader(hMidiOut, MidiOutHdr, sizeof(MIDIHDR));

            /* free buffer and struct */

            GlobalUnlock(DataHandle);
            GlobalFree(DataHandle);

            GlobalUnlock(HdrHandle);
            GlobalFree(HdrHandle);
            }

         /* if midi error let 'em know */

         if (MidiError)
            {
            midiOutGetErrorText(MidiError, MidiErrorBuffer, MAX_BUFFER_SIZE);
            MainWindowx->CommandWindow->MessageBox(MidiErrorBuffer, "Midi Error");
            err_logo(STOP_ERROR, NIL);
            }
         }
      else
         {
         MainWindowx->CommandWindow->MessageBox("Bad argument", "Midi Error");
         err_logo(STOP_ERROR, NIL);
         }
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox("Not Open", "Midi Error");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *lmci(NODE *args)
   {
   // get mci command string 
   char textbuf[MAX_BUFFER_SIZE];
   cnv_strnode_string(textbuf, args);

   // check for optional callback routine 
   char callback[MAX_BUFFER_SIZE];
   if (cdr(args) != NIL)
      {
      cnv_strnode_string(callback, cdr(args));
      strcpy(mci_callback, callback);
      }

   char MciReturnBuffer[MAX_BUFFER_SIZE];
   MciReturnBuffer[0] = '\0';

   // send out command 
   DWORD MciError = mciSendString(
      textbuf,
      MciReturnBuffer,
      MAX_BUFFER_SIZE,
      MainWindowx->HWindow);

   if (MciError)
      {
      // let user know about the error
      char MciErrorBuffer[MAX_BUFFER_SIZE];
      mciGetErrorString(MciError, MciErrorBuffer, MAX_BUFFER_SIZE);
      MainWindowx->CommandWindow->MessageBox(MciErrorBuffer, "MCI Error");
      err_logo(STOP_ERROR, NIL);
      }
   else
      {
      // if something was returned then return it to user 
      if (strlen(MciReturnBuffer))
         {
         NODE * targ = make_strnode(MciReturnBuffer);
         NODE * val = parser(targ, false);
         return val;
         }
      }

   return Unbound;
   }

NODE *lsettimer(NODE *args)
   {
   char callback[MAX_BUFFER_SIZE];
   WORD delay;
   int id;

   // get id and if valid continue

   id = int_arg(args);

   if ((id > 0) && (id < 32))
      {

      // get delay callback

      delay = int_arg(args = cdr(args));

      cnv_strnode_string(callback, args = cdr(args));

      if (timer_callback[id] == NULL) timer_callback[id] = (char *) malloc(MAX_BUFFER_SIZE);
      strcpy(timer_callback[id], callback);

      // if not set sucessfully error

      if (!::SetTimer(MainWindowx->HWindow, id, delay, NULL))
         {
         MainWindowx->CommandWindow->MessageBox("Too Many Timers", "Error");
         err_logo(STOP_ERROR, NIL);
         }
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox("Bad Timer Id", "Error");
      err_logo(STOP_ERROR, NIL);
      }
   return Unbound;
   }

NODE *lcleartimer(NODE *args)
   {
   int id;

   // get args

   id = int_arg(args);

   // if timer was not set let user know

   if (!::KillTimer(MainWindowx->HWindow, id))
      {
      MainWindowx->CommandWindow->MessageBox("Timer not found", "Error");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

NODE *lplaywave(NODE *args)
   {
   char name[MAX_BUFFER_SIZE];
   int flag;

   cnv_strnode_string(name, args);
   flag = getint(pos_int_arg(args = cdr(args)));

   if (strlen(name) == 0)
      {
      sndPlaySound(NULL, flag);
      }
   else
      {
      sndPlaySound(name, flag);
      }

   return Unbound;
   }
