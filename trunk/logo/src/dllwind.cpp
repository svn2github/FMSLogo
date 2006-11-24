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

#include "allwind.h"

static HINSTANCE hDLLModule = NULL;

extern "C" void PASCAL pushw(WORD);
extern "C" void PASCAL pushl(DWORD);
extern "C" void PASCAL pushf(double);
extern "C" void PASCAL pushs(LPCSTR);

static
void
ShowDllErrorAndStop(
   const char * ErrorMessage
   )
   {
   ShowMessageAndStop(LOCALIZED_ERROR_DLL, ErrorMessage);
   }

NODE *ldllload(NODE *arg)
   {
   if (hDLLModule)
      {
      ShowDllErrorAndStop(LOCALIZED_ERROR_DLLALREADYLOADED);
      }
   else
      {
      char dllname[MAX_BUFFER_SIZE];
      cnv_strnode_string(dllname, arg);

      hDLLModule = LoadLibrary(dllname);
      if (hDLLModule == NULL)
         {
         ShowDllErrorAndStop(LOCALIZED_ERROR_DLLLOADFAILED);
         }
      }

   return Unbound;
   }

NODE *ldllfree(NODE *)
   {
   if (hDLLModule == NULL)
      {
      ShowDllErrorAndStop(LOCALIZED_ERROR_DLLNOTLOADED);
      }
   else
      {
      FreeLibrary(hDLLModule);
      hDLLModule = 0;
      }

   return Unbound;
   }

NODE *ldllcall(NODE *arg)
   {
   if (hDLLModule == NULL)
      {
      ShowDllErrorAndStop(LOCALIZED_ERROR_DLLNOTLOADED);
      return Unbound;
      }

   // get args
   NODE * args = car(arg);

   // must be a list that contains something
   if (is_list(args) && (args != NIL))
      {

      // count items in list and check that they are pairs
      int total_args = list_length(args);
      bool even_args = even_p(total_args);

      // if we have pairs continue
      if (even_args)
         {
         arg = args;

         char fkind[MAX_BUFFER_SIZE];
         cnv_strnode_string(fkind, arg);
         arg = cdr(arg);

         char fname[MAX_BUFFER_SIZE];
         cnv_strnode_string(fname, arg);
         arg = cdr(arg);

         FARPROC theFunc = GetProcAddress(hDLLModule, fname);
         if (!theFunc) 
            {
            theFunc = GetProcAddress(hDLLModule, (char *) atol(fname));
            }

         if (theFunc)
            {
            char *values[1024];  // strings we must free

            /* fill queue with type/data pairs */
            int i = 0;
            while (arg != NIL)
               {
               char akind[MAX_BUFFER_SIZE];
               cnv_strnode_string(akind, arg);
               arg = cdr(arg);

               char avalue[MAX_BUFFER_SIZE];
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
                     ShowDllErrorAndStop(LOCALIZED_ERROR_DLLINVALIDDATATYPE);
                     return Unbound;
                     }
                  }
               }

            char areturn[MAX_BUFFER_SIZE];
            switch (fkind[0])
               {
               case 'w':
               case 'W':
                  {
                  WORD w = (*(WORD(WINAPI *)()) theFunc)();
                  sprintf(areturn, "%d", w);
                  break;
                  }

               case 'l':
               case 'L':
                  {
                  DWORD dw = (*(DWORD(WINAPI *)()) theFunc)();
                  sprintf(areturn, "%ld", dw);
                  break;
                  }

               case 'f':
               case 'F':
                  {
                  double dw = (*(double (WINAPI *)()) theFunc)();
                  sprintf(areturn, "%f", dw);
                  break;
                  }

               case 's':
               case 'S':
                  {
                  LPSTR lp = (*(LPSTR(WINAPI *)()) theFunc)();
                  strncpy(areturn, lp, MAX_BUFFER_SIZE);
                  // free global string mem.
                  // this should not be like this because lp[]
                  // can be bigger than resp[] but for now...
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
                  ShowDllErrorAndStop(LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE);
                  break;
                  }
               }

            for (int j = 0; j < i; j++) 
               {
               free(values[j]);
               }

            if (strlen(areturn))
               {
               NODE * targ = make_strnode(areturn);
               NODE * val = parser(targ, false);
               return val;
               }

            }
         else
            {
            ShowDllErrorAndStop(LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND);
            }
         }
      else
         {
         ShowDllErrorAndStop(LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED);
         }
      }
   else
      {
      ShowDllErrorAndStop(LOCALIZED_ERROR_BADINPUT);
      }

   return Unbound;
   }

