
#include "allwind.h"

static HANDLE ComId;
static bool   ComIsOpen = false;

NODE *lmouseon(NODE *args)
   {
   // get args
   char lbuttondown[MAX_BUFFER_SIZE];
   cnv_strnode_string(lbuttondown, args);

   char lbuttonup[MAX_BUFFER_SIZE];
   cnv_strnode_string(lbuttonup, args = cdr(args));

   char rbuttondown[MAX_BUFFER_SIZE];
   cnv_strnode_string(rbuttondown, args = cdr(args));

   char rbuttonup[MAX_BUFFER_SIZE];
   cnv_strnode_string(rbuttonup, args = cdr(args));

   char mousemove[MAX_BUFFER_SIZE];
   cnv_strnode_string(mousemove, args = cdr(args));

   // most of mouse code is in DEFWNDPROC when this flag is on
   MouseCaptureIsEnabled = true;

   if (mouse_lbuttondown == NULL)
      {
      mouse_lbuttondown = (char *) malloc(MAX_BUFFER_SIZE);
      mouse_lbuttonup = (char *) malloc(MAX_BUFFER_SIZE);
      mouse_rbuttondown = (char *) malloc(MAX_BUFFER_SIZE);
      mouse_rbuttonup = (char *) malloc(MAX_BUFFER_SIZE);
      mouse_mousemove = (char *) malloc(MAX_BUFFER_SIZE);
      }

   // these really should be NODEs but not yet

   strcpy(mouse_lbuttondown, lbuttondown);
   strcpy(mouse_lbuttonup, lbuttonup);
   strcpy(mouse_rbuttondown, rbuttondown);
   strcpy(mouse_rbuttonup, rbuttonup);
   strcpy(mouse_mousemove, mousemove);

   return Unbound;
   }

NODE *lmouseoff(NODE *)
   {
   // tell handler not to do anything with messages for mouse
   MouseCaptureIsEnabled = false;

   return Unbound;
   }

NODE *lkeyboardon(NODE *args)
   {
   if (keyboard_keyup == NULL)
      {
      keyboard_keyup = (char *) malloc(MAX_BUFFER_SIZE);
      keyboard_keydown = (char *) malloc(MAX_BUFFER_SIZE);
      }

   // get args
   if (cdr(args) == NIL)
      {
      char keyboardup[MAX_BUFFER_SIZE];
      cnv_strnode_string(keyboardup, args);

      // most keyboard processing is done in DEFWNDPROC
      KeyboardCapture = KEYBOARDCAPTURE_KeyDown;

      strcpy(keyboard_keyup, keyboardup);
      }
   else
      {
      char keyboarddown[MAX_BUFFER_SIZE];
      cnv_strnode_string(keyboarddown, args);

      char keyboardup[MAX_BUFFER_SIZE];
      cnv_strnode_string(keyboardup, cdr(args));

      // most keyboard processing is done in DEFWNDPROC
      KeyboardCapture = KEYBOARDCAPTURE_KeyDownKeyUp;

      strcpy(keyboard_keydown, keyboarddown);
      strcpy(keyboard_keyup, keyboardup);
      }

   return Unbound;
   }

NODE *lkeyboardoff(NODE *)
   {
   // tell handler not to do anything with messages for keyboard
   KeyboardCapture = KEYBOARDCAPTURE_Off;

   return Unbound;
   }

void keyboard_uninit()
   {
   free(keyboard_keyup);
   keyboard_keyup = NULL;
   
   free(keyboard_keydown);
   keyboard_keydown = NULL;
   }

NODE *lmousepos(NODE *)
   {

   // return current mouse position

   // return cons_list(
   //    make_intnode(  mouse_posx+MainWindowx->Scroller->XPos-xoffset*the_zoom),
   //    make_intnode(-(mouse_posy+MainWindowx->Scroller->YPos-yoffset*the_zoom)));

   return cons_list(
      make_intnode(  (mouse_posx + MainWindowx->ScreenWindow->Scroller->XPos) / the_zoom - xoffset),
      make_intnode(-((mouse_posy + MainWindowx->ScreenWindow->Scroller->YPos) / the_zoom - yoffset)));
   }

NODE *lkeyboardvalue(NODE *)
   {
   // return current keyboard value
   return make_intnode(keyboard_value);
   }

static
int min(int a, int b)
   {
   if (a < b)
      {
      return a; 
      }
   else 
      {
      return b;
      }
   }

NODE *lportclose(NODE *)
   {
   // if port closed output error else close it
   if (!ComIsOpen)
      {
      ShowMessageAndStop("Error", "Could not CLOSE port");
      }
   else
      {
      ComIsOpen = false;
      CloseHandle(ComId);
      }

   return Unbound;
   }

NODE *lportopen(NODE *args)
   {
   char comport[MAX_BUFFER_SIZE];
   cnv_strnode_string(comport, args);

   // if port open output error else open it
   if (ComIsOpen)
      {
      ShowMessageAndStop("Error", "PORT already open");
      }
   else
      {
      ComId = CreateFile(comport, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

      SetupComm(ComId, 4096, 4096);

      SetCommMask(ComId, 0);

      PurgeComm(ComId, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

      COMMTIMEOUTS CommTimeOuts;
      CommTimeOuts.ReadIntervalTimeout = MAXDWORD;
      CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
      CommTimeOuts.ReadTotalTimeoutConstant = 0;
      CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
      CommTimeOuts.WriteTotalTimeoutConstant = 0;
      SetCommTimeouts(ComId, &CommTimeOuts);

      DCB dcb;
      GetCommState(ComId, &dcb); // If we don't do this it won't work in Win95 !!!
      SetCommState(ComId, &dcb);

      if (ComId < 0)
         {
         ShowMessageAndStop("Error", "Could not open PORT");
         }
      else
         {
         ComIsOpen = true;
         }
      }

   return Unbound;
   }

NODE *lportflush(NODE */* args */)
   {
   if (!ComIsOpen)
      {
      ShowMessageAndStop("Error", "PORT not open");
      }
   else
      {
      int err = FlushFileBuffers(ComId);
      if (err == 0)
         {
         ShowMessageAndStop("Error", "Could not flush PORT");
         }
      }

   return Unbound;
   }

NODE *lportmode(NODE *args)
   {
   char commode[MAX_BUFFER_SIZE];
   cnv_strnode_string(commode, args);

   // if closed output error else set mode
   if (!ComIsOpen)
      {
      ShowMessageAndStop("Error", "PORT not open");
      }
   else
      {
      // build dcb, if no error continue
      DCB dcb;
      memset(&dcb, 0, sizeof(DCB));
      dcb.DCBlength = sizeof(DCB);
      int err = BuildCommDCB(commode, &dcb);

      if (err == 0)
         {
         ShowMessageAndStop("Error", "Could not build dcb on PORT");
         }
      else
         {
         // now set Id in dcb and set the state
         DCB dcbold;

         GetCommState(ComId, &dcbold);

         dcbold.BaudRate = dcb.BaudRate;
         dcbold.ByteSize = dcb.ByteSize;
         dcbold.Parity   = dcb.Parity;
         dcbold.StopBits = dcb.StopBits;

         err = SetCommState(ComId, &dcbold);
         if (err == 0)
            {
            ShowMessageAndStop("Error", "Could not set PORT");
            }
         }
      }

   return Unbound;
   }

NODE *lportwritearray(NODE *args)
   {
   NODE * val = pos_int_arg(args);
   NODE * obj = cadr(args);

   while ((obj == NIL || obj == Null_Word) && NOT_THROWING)
      {
      setcar(cdr(args), err_logo(BAD_DATA, obj));
      obj = cadr(args);
      }

   if (NOT_THROWING)
      {
      if (nodetype(obj) == ARRAY)
         {

         // if closed the error, else continue
         if (!ComIsOpen)
            {
            ShowMessageAndStop("Error", "PORT not open");
            }
         else
            {
            // get min of max array and the array
            char txbuffer[MAX_BUFFER_SIZE];
            DWORD count = min(min(getint(val), getarrdim(obj)), sizeof(txbuffer));

            // fill buffer with elements of the array
            for (int i = 0; i < count; i++)
               {
               NODE * item = litem(cons_list(make_intnode(i + getarrorg(obj)), obj));
               txbuffer[i] = getint(cnv_node_to_numnode(item));
               }

            // now write buffer
            DWORD Error;
            ClearCommError(ComId, &Error, NULL);

            DWORD actual;
            int status = WriteFile(ComId, txbuffer, count, &actual, NULL);

            // if problem GetComError will Put up Message box
            if (status == 0)
               {
               ClearCommError(ComId, &Error, NULL);
               }

            // return byte count sent
            return make_intnode(status);
            }
         }
      else
         {
         ShowMessageAndStop("Error", "First arg must be an array");
         }
      }

   return make_intnode(0);
   }

NODE *lportreadarray(NODE *args)
   {
   NODE * val = pos_int_arg(args);
   NODE * obj = cadr(args);

   while ((obj == NIL || obj == Null_Word) && NOT_THROWING)
      {
      setcar(cdr(args), err_logo(BAD_DATA, obj));
      obj = cadr(args);
      }

   if (NOT_THROWING)
      {
      if (nodetype(obj) == ARRAY)
         {

         // if closed the error, else continue

         if (!ComIsOpen)
            {
            ShowMessageAndStop("Error", "PORT not open");
            }
         else
            {
            // don't overflow buffer
            char rxbuffer[MAX_BUFFER_SIZE];
            int count = min(min(getarrdim(obj), getint(val)), sizeof(rxbuffer));

            // Clear any errors
            DWORD Error;
            COMSTAT Stat;
            ClearCommError(ComId, &Error, &Stat);

            // do the read (let it fail if nothing is there, it should not hang)
            DWORD actual;
            ReadFile(ComId, rxbuffer, count, &actual, NULL);

            // if nothing there then return 0 count
            if (actual == 0) 
               {
               return make_intnode(0);
               }

            count = actual;

            // now fill in the array
            for (int i = 0; i < count; i++)
               {
               lsetitem(
                  cons_list(
                     make_intnode(i + getarrorg(obj)),
                     obj,
                     make_intnode(rxbuffer[i])));
               }

            // return actual transfered
            return make_intnode(count);
            }
         }
      }

   return make_intnode(0);
   }

NODE *lportwritechar(NODE *args)
   {
   // get arg
   char txchar[1];
   txchar[0] = getint(pos_int_arg(args));

   // if not open output error, else continue

   if (!ComIsOpen)
      {
      ShowMessageAndStop("Error", "PORT not open");
      }
   else
      {
      // write the 1 byte
      DWORD status;
      if (!WriteFile(ComId, txchar, 1, &status, NULL))
         {
         status = -1;
         }

      // if problem GetComError will Put up Message box
      if (status != 1)
         {
         DWORD Error;
         ClearCommError(ComId, &Error, NULL);
         }

      // return byte count sent
      return make_intnode(status);
      }

   return make_intnode(0);
   }

NODE *lportreadchar(NODE *)
   {
   // if closed output error, else continue
   if (!ComIsOpen)
      {
      ShowMessageAndStop("Error", "PORT not open");
      }
   else
      {
      // Clear Comm Error in case last operation failed otherwise we won't get anything
      DWORD Error;
      ClearCommError(ComId, &Error, NULL);

      // ReadFile will return immediately even if there is nothing to read
      char rxchar[64];
      DWORD actual;
      ReadFile(ComId, rxchar, 1, &actual, NULL);

      // if something was read then return it else return -1
      if (actual == 1)
         {
         return make_intnode(rxchar[0]);
         }
      else
         {
         return make_intnode(-1);
         }
      }

   return make_intnode(-1);
   }

NODE *loutportb(NODE *args)
   {
   // get args
   int portid = getint(pos_int_arg(args));
   int value = getint(pos_int_arg(cdr(args)));

   Myoutportb(portid, value);

   return Unbound;
   }

NODE *linportb(NODE *args)
   {
   int portid = getint(pos_int_arg(args));
   int value = Myinportb(portid);

   return make_intnode(value);
   }

NODE *loutport(NODE *args)
   {
   // get args
   int portid = getint(pos_int_arg(args));
   int value = getint(pos_int_arg(cdr(args)));

   Myoutport(portid, value);

   return Unbound;
   }

NODE *linport(NODE *args)
   {
   int portid = getint(pos_int_arg(args));
   int value = Myinport(portid);

   return make_intnode(value);
   }

NODE *lingameport(NODE *args)
   {
   int portid;

   int mask = getint(pos_int_arg(args));

   if (cdr(args) == NIL)
      {
      portid = 0x201;
      }
   else
      {
      portid = getint(pos_int_arg(cdr(args)));
      }

   int value = Myingameport(portid, mask);

   return make_intnode(value);
   }

