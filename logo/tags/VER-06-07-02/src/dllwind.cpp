/*
*
*       Copyright (C) 1995 by the Regents of the University of California
*       Copyright (C) 1995 by George Mills
*       Copyright (C) 1995 by Telmo Carmo
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

/**********************************************************************
*
*
**********************************************************************/

#include "allwind.h"

static HINSTANCE hDLLModule = 0;

extern "C" void PASCAL pushw(WORD);
extern "C" void PASCAL pushl(DWORD);
extern "C" void PASCAL pushf(double);
extern "C" void PASCAL pushs(LPCSTR);

NODE *ldllload(NODE *arg)
   {
   char dllname[MAX_BUFFER_SIZE];

   if (hDLLModule)
      {
      MainWindowx->CommandWindow->MessageBox("DLL already loaded", "DLL Error");
      err_logo(STOP_ERROR, NIL);
      }

   cnv_strnode_string(dllname, arg);

   hDLLModule = LoadLibrary(dllname);

   if (!hDLLModule)
      {
      MainWindowx->CommandWindow->MessageBox("DLL load failed", "DLL Error");
      err_logo(STOP_ERROR, NIL);
      hDLLModule = 0;
      }

   return Unbound;
   }

NODE *ldllfree(NODE *)
   {
   if (!hDLLModule)
      {
      MainWindowx->CommandWindow->MessageBox("DLL not loaded", "DLL Error");
      err_logo(STOP_ERROR, NIL);
      }

   FreeLibrary(hDLLModule);
   hDLLModule = 0;

   return Unbound;
   }

NODE *ldllcall(NODE *arg)
   {
   char fkind[MAX_BUFFER_SIZE];
   char fname[MAX_BUFFER_SIZE];
   char akind[MAX_BUFFER_SIZE];
   char avalue[MAX_BUFFER_SIZE];
   char areturn[MAX_BUFFER_SIZE];
   char *values[1024];

   int i;
   int j;
   int odd;

   NODE *args;
   NODE *targ;
   NODE *val;

   FARPROC theFunc;

   if (!hDLLModule)
      {
      MainWindowx->CommandWindow->MessageBox("DLL not loaded", "DLL Error");
      err_logo(STOP_ERROR, NIL);
      return Unbound;
      }

   // get args

   args = car(arg);

   /* must be a list that contains something */

   if (is_list(args) && (args != NIL))
      {

      /* count items in list and check that they are pairs */

      arg = args;
      odd = 0;

      while (arg != NIL)
         {
         if (arg != NIL) arg = cdr(arg);
         if (arg != NIL) arg = cdr(arg); else odd = 1;
         }

      /* if we have pairs continue */

      if (!odd)
         {

         arg = args;
         i = 0;

         cnv_strnode_string(fkind, arg);
         arg = cdr(arg);
         cnv_strnode_string(fname, arg);
         arg = cdr(arg);

         theFunc = GetProcAddress(hDLLModule, fname);
         if (!theFunc) theFunc = GetProcAddress(hDLLModule, (char *) atol(fname));

         if (theFunc)
            {

            /* fill queue with type/data pairs */

            while (arg != NIL)
               {
               cnv_strnode_string(akind, arg);
               arg = cdr(arg);
               cnv_strnode_string(avalue, arg);
               arg = cdr(arg);

               switch (akind[0])
                  {
                   case 'w':
                   case 'W':
                       {
                          WORD w = (WORD) atoi(avalue);
                          pushw(w);
                          break;
                       }

                   case 'l':
                   case 'L':
                       {
                          DWORD dw = (DWORD) atol(avalue);
                          pushl(dw);
                          break;
                       }

                   case 'f':
                   case 'F':
                       {
                          double df = atof(avalue);
                          pushf(df);
                          break;
                       }

                   case 's':
                   case 'S':
                       {
                          values[i] = strdup(avalue);
                          pushs((LPCSTR) values[i]);
                          i++;
                          break;
                       }

                   case 'v':
                   case 'V':
                       {
                       }
                       break;

                   default:
                       {
                          MainWindowx->CommandWindow->MessageBox("Invalid Argument Data Type", "DLL Error");
                          err_logo(STOP_ERROR, NIL);
                          return Unbound;
                       }
                  }
               }

            switch (fkind[0])
               {
                case 'w':
                case 'W':
                    {
                       WORD w;
                       w = (*(WORD(WINAPI *)()) theFunc)();
                       sprintf(areturn, "%d", w);
                       break;
                    }

                case 'l':
                case 'L':
                    {
                       DWORD dw;
                       dw = (*(DWORD(WINAPI *)()) theFunc)();
                       sprintf(areturn, "%ld", dw);
                       break;
                    }

                case 'f':
                case 'F':
                    {
                       double dw;
                       dw = (*(double (WINAPI *)()) theFunc)();
                       sprintf(areturn, "%f", dw);
                       break;
                    }

                case 's':
                case 'S':
                    {
                       LPSTR lp;
                       lp = (*(LPSTR(WINAPI *)()) theFunc)();
                       strncpy(areturn, lp, MAX_BUFFER_SIZE);
                       /* free global string mem.
                        *  this should not be like this because lp[]
                        *  can be bigger than resp[] but for now...
                        */
                       GlobalFreePtr(lp);
                       break;
                    }

                case 'v':
                case 'V':
                    {
                       (*(void (WINAPI *)()) theFunc)();
                       areturn[0] = 0;
                       break;
                    }

                default:
                    {
                       MainWindowx->CommandWindow->MessageBox("Invalid Return Data Type", "DLL Error");
                       err_logo(STOP_ERROR, NIL);
                       break;
                    }
               }

            for (j = 0; j < i; j++) free(values[j]);

            if (strlen(areturn))
               {
               targ = make_strnode(areturn, strlen(areturn), STRING, strnzcpy);
               val = parser(targ, FALSE);
               return (val);
               }

            }
         else
            {
            MainWindowx->CommandWindow->MessageBox("Function not Found", "DLL Error");
            err_logo(STOP_ERROR, NIL);
            }
         }
      else
         {
         MainWindowx->CommandWindow->MessageBox("Not Type/Data paired", "DLL Error");
         err_logo(STOP_ERROR, NIL);
         }
      }
   else
      {
      MainWindowx->CommandWindow->MessageBox("Bad argument", "DLL Error");
      err_logo(STOP_ERROR, NIL);
      }

   return Unbound;
   }

