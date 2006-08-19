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

static HMIDIOUT hMidiOut = 0;

NODE *lsound(NODE *arg)
   {
   /* open sound and get arg list */
   NODE *args = car(arg);

   /* must be a list that contains something */
   if (is_list(args) && (args != NIL))
      {

      /* count items in list and check that they are pairs */
      int total_args = list_length(args);
      bool even_args = even_p(total_args);

      /* if sound creation ok and we have pairs continue */
      if (even_args)
         {
         /* play each freq/duration pair */
         for (arg = args;
              arg != NIL;
              arg = cdr(arg))
            {
            int duration = 0;

            int hertz = int_arg(arg);
            if (cdr(arg) != NIL)
               {
               duration = int_arg(arg = cdr(arg));
               }

            /* play it */
            tone(hertz, duration);
            }
         }
      else
         {
         ShowMessageAndStop("Sound Error", "Not paired");
         }
      }
   else
      {
      ShowMessageAndStop("Sound Error", "Bad argument");
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
            ShowMessageAndStop("Midi Error", "Invalid Midi device");
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
         ShowMessageAndStop("Midi Error", MidiErrorBuffer);
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
      ShowMessageAndStop("Midi Error", "Already Open");
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
         ShowMessageAndStop("Midi Error", MidiErrorBuffer);
         }
      }
   else
      {
      ShowMessageAndStop("Midi Error", "Already closed");
      }

   return Unbound;
   }

NODE *lmidimessage(NODE *arg)
   {
   union
      {
      long mylong;
      char mybyte[4];
      }
   bytetolong;

   /* if midi open continue */
   if (hMidiOut)
      {
      NODE * args = car(arg);

      /* if a list with something in it continue */
      if (is_list(args) && (args != NIL))
         {
         UINT MidiError;

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
            int i = list_length(args);

            /* allocate structure buffer */
            // REVISIT: why not use malloc()?
            HANDLE    HdrHandle = (HANDLE) GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT, sizeof(MIDIHDR));
            MIDIHDR * MidiOutHdr = (MIDIHDR *) GlobalLock((HGLOBAL) HdrHandle);

            HANDLE DataHandle = (HANDLE) GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT, i);
            BYTE * MidiOutData = (BYTE *) GlobalLock((HGLOBAL) DataHandle);

            /* pack the buffer array and set size */
            arg = args;

            for (int j = 0; j < i; j++)
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
            char MidiErrorBuffer[MAX_BUFFER_SIZE];
            midiOutGetErrorText(MidiError, MidiErrorBuffer, MAX_BUFFER_SIZE);
            ShowMessageAndStop("Midi Error", MidiErrorBuffer);
            }
         }
      else
         {
         ShowMessageAndStop("Midi Error", "Bad argument");
         }
      }
   else
      {
      ShowMessageAndStop("Midi Error", "Not Open");
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
      ShowMessageAndStop("MCI Error", MciErrorBuffer);
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
   // get the timer id 
   int id = int_arg(args);

   // get delay
   int delay = getint(pos_int_arg(args = cdr(args)));

   // get callback
   char callback[MAX_BUFFER_SIZE];
   cnv_strnode_string(callback, args = cdr(args));

   if (NOT_THROWING)
      {
      if ((id > 0) && (id < MAX_TIMERS))
         {
         if (timer_callback[id] == NULL) 
            {
            timer_callback[id] = (char *) malloc(MAX_BUFFER_SIZE);
            }
         strcpy(timer_callback[id], callback);

         // if not set sucessfully error
         if (!::SetTimer(MainWindowx->HWindow, id, delay, NULL))
            {
            ShowMessageAndStop("Error", "Too Many Timers");
            }
         }
      else
         {
         ShowMessageAndStop("Error", "Bad Timer Id");
         }
      }

   return Unbound;
   }

NODE *lcleartimer(NODE *args)
   {
   // get args
   int id = int_arg(args);

   // if timer was not set let user know
   if (!::KillTimer(MainWindowx->HWindow, id))
      {
      ShowMessageAndStop("Error", "Timer not found");
      }

   return Unbound;
   }

void uninitialize_timers()
   {
   for (int id = 0; id < MAX_TIMERS; id++)
      {
      free(timer_callback[id]);
      timer_callback[id] = NULL;
      }
   }

NODE *lplaywave(NODE *args)
   {
   char name[MAX_BUFFER_SIZE];
   cnv_strnode_string(name, args);

   int flag = getint(pos_int_arg(args = cdr(args)));

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
