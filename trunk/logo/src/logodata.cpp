/*
*      logodata.c      logo data management module             dvb
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

//char special_chars[] = " \t\n()[]+-*/=<>\"\\~:;|?";
char special_chars[] = " \t\n(\?\?\?\?\?\?\?+~)[]-*/=<>\"\\:;|\?";

#ifdef ecma

#define upper_p(ch)     (isupper((ch) & 0xFF))
#define lower_p(ch)     (islower((ch) & 0xFF))

char ecma_array[128];

int ecma_size = sizeof(special_chars);

char ecma_set(int ch)
   {
   ch &= 0xFF;
   if (ch >= 0x80) return (ch);
   return ecma_array[ch];
   }

char ecma_clear(int ch)
   {
   ch &= 0xFF;
   if (ch < ecma_begin || ch >= ecma_begin + sizeof(special_chars)) 
      {
      return ch;
      }
   if (ch >= 0x7 && ch <= 0xD) 
      {
      return ch;
      }

   return special_chars[ch - ecma_begin];
   }

int ecma_get(int ch)
   {
   ch &= 0xFF;
   return ((ch >= ecma_begin && ch < ecma_begin + sizeof(special_chars))
      && (ch < 0x7 || ch > 0xD));
   }

#else

#define upper_p(c)     (c >= 'A' && c <= 'Z')
#define lower_p(c)     (c >= 'a' && c <= 'z')

#endif

char *strnzcpy(char *dst, const char *src, int len)
   {
   strncpy(dst, src, len);
   dst[len] = '\0';
   return dst;
   }

char *word_strnzcpy(char *dst, NODE *wordlist, int len)
   {
   char *temp = dst;

   while (wordlist != NIL)
      {
      strncpy(dst, getstrptr(car(wordlist)), getstrlen(car(wordlist)));
      dst += getstrlen(car(wordlist));
      wordlist = cdr(wordlist);
      }
   temp[len] = '\0';
   return temp;
   }

char *noparity_strnzcpy(char *dst, const char * src, int len)
   {
   for (int i = 0; i < len; i++)
      {
      dst[i] = clearparity(src[i]);
      }
   dst[len] = '\0';

   return dst;
   }

char *mend_strnzcpy(char *dst, const char * src, int len)
   {
   bool vbar = false;

   for (int i = 0; i < len;)
      {
      while (*src == '|')
         {
         vbar = !vbar;
         src++;
         }
      if (vbar)
         {
         if (strchr(special_chars, (int) * src))
            dst[i++] = setparity(*src++);
         else
            dst[i++] = *src++;
         }
      else
         {
         while (*src == ';' || (*src == '~' && *(src + 1) == '\n'))
            {
            while (*src == '~' && *(src + 1) == '\n') src += 2;
            if (*src == ';')
               do
                  {
                  src++;
                  }
               while (*src != '\0' && *src != '~' && *(src + 1) != '\n');
            }
         if (*src != '|') dst[i++] = *src++;
         }
      }
   dst[len] = '\0';
   return (dst);
   }

char *mend_nosemi(char *dst, const char * src, int len)
   {
   bool vbar = false;

   for (int i = 0; i < len;)
      {
      while (*src == '|')
         {
         vbar = !vbar;
         src++;
         }
      if (vbar)
         {
         if (strchr(special_chars, (int) * src))
            dst[i++] = setparity(*src++);
         else
            dst[i++] = *src++;
         }
      else
         {
         while ((*src == '~' && *(src + 1) == '\n'))
            {
            while (*src == '~' && *(src + 1) == '\n') src += 2;
            }
         if (*src != '|') dst[i++] = *src++;
         }
      }
   dst[len] = '\0';
   return (dst);
   }

char *quote_strnzcpy(char *dst, const char *src, int len)
   {
   dst[0] = '"';
   strncpy(dst + 1, src, len - 1);
   dst[len] = '\0';
   return dst;
   }

char *colon_strnzcpy(char *dst, const char * src, int len)
   {
   dst[0] = ':';
   strncpy(dst + 1, src, len - 1);
   dst[len] = '\0';
   return (dst);
   }

#define uncapital(c)    (c - 'A' + 'a')

char *low_strnzcpy(char *dst, const char * src, int len)
   {
   char *temp = dst;

   for (int i = 0; i < len; i++)
      {
      if (upper_p(*src))
         {
         *dst++ = uncapital(*src++);
         }
      else
         {
         *dst++ = *src++;
         }
      }
   *dst = '\0';
   return temp;
   }

#define capital(c)    (c - 'a' + 'A')

char *cap_strnzcpy(char *dst, const char * src, int len)
   {
   char *temp = dst;

   for (int i = 0; i < len; i++)
      {
      if (lower_p(*src))
         {
         *dst++ = capital(*src++);
         }
      else
         {
         *dst++ = *src++;
         }
      }
   *dst = '\0';
   return (temp);
   }

char *noparitylow_strnzcpy(char *dst, const char *src, int len)
   {
   char *temp = dst;

   for (int i = 0; i < len; i++)
      {
      char c = clearparity(*src++);
      if (upper_p(c))
         {
         *dst++ = uncapital(c);
         }
      else
         {
         *dst++ = c;
         }
      }
   *dst = '\0';
   return temp;
   }

int low_strncmp(const char *s1, const char * s2, int len)
   {
   for (int i = 0; i < len; i++)
      {
      if (*s1 != *s2)
         {
         if (upper_p(*s2))
            {
            if (upper_p(*s1))
               {
               if (uncapital(*s1) != uncapital(*s2))
                  return (uncapital(*s1) - uncapital(*s2));
               }
            else
               {
               if (*s1 != uncapital(*s2))
                  return (*s1 - uncapital(*s2));
               }
            }
         else if (upper_p(*s1))
            {
            if (uncapital(*s1) != *s2)
               return (uncapital(*s1) - *s2);
            }
         else return (*s1 - *s2);
         }
      s1++, s2++;
      }
   return 0;
   }

int noparity_strncmp(const char * s1, const char * s2, int len)
   {
   for (int i = 0; i < len; i++)
      {
      if (clearparity(*s1) != clearparity(*s2))
         return (clearparity(*s1) - clearparity(*s2));
      s1++, s2++;
      }
   return 0;
   }

int noparitylow_strncmp(const char * s1, const char * s2, int len)
   {
   for (int i = 0; i < len; i++)
      {
      char c1 = clearparity(*s1);
      char c2 = clearparity(*s2);
      if (c1 != c2)
         {
         if (upper_p(c2))
            {
            if (upper_p(c1))
               {
               if (uncapital(c1) != uncapital(c2))
                  return (uncapital(c1) - uncapital(c2));
               }
            else
               {
               if (c1 != uncapital(c2))
                  return (c1 - uncapital(c2));
               }
            }
         else if (upper_p(c1))
            {
            if (uncapital(c1) != c2)
               return (uncapital(c1) - c2);
            }
         else return (c1 - c2);
         }
      s1++, s2++;
      }
   return 0;
   }


// Makes a string node by copying a NUL-terminated string
// into a NODE structure.
NODE * 
make_strnode(
   const char *string, 
   int         len,
   NODETYPES   typ,  
   char *    (*copy_routine) (char *, const char *, int)
)
   {
   assert(string != NULL);

   if (len == 0 && Null_Word != NIL)
      {
      return Null_Word;
      }

   // allocate enough to hold the header, the string, and NUL.
   char * strhead = (char *) malloc(sizeof(short) + len + 1);
   if (strhead == NULL)
      {
      err_logo(OUT_OF_MEM, NIL);
      return Unbound;
      }

   // set the "string pointer" to just after the header
   char * strptr = strhead + sizeof(short);
   copy_routine(strptr, string, len);

   // set the reference count to 1.
   unsigned short *header = (unsigned short *) strhead;
   setstrrefcnt(header, 1);

   NODE * strnode = newnode(typ);
   setstrlen(strnode, len);
   setstrptr(strnode, strptr);
   setstrhead(strnode, strhead);
   return strnode;
   }

// Makes a string node by copying from a list of word nodes.
NODE * 
make_strnode_from_wordlist(
   NODE *      wordlist, 
   int         len,
   NODETYPES   typ
)
   {
   if (len == 0 && Null_Word != NIL)
      {
      return Null_Word;
      }

   // allocate enough to hold the header, the string, and NUL.
   char * strhead = (char *) malloc(sizeof(short) + len + 1);
   if (strhead == NULL)
      {
      err_logo(OUT_OF_MEM, NIL);
      return Unbound;
      }

   // set the "string pointer" to just after the header
   char * strptr = strhead + sizeof(short);
   word_strnzcpy(strptr, wordlist, len);

   // set the reference count to 1.
   unsigned short *header = (unsigned short *) strhead;
   setstrrefcnt(header, 1);

   NODE * strnode = newnode(typ);
   setstrlen(strnode, len);
   setstrptr(strnode, strptr);
   setstrhead(strnode, strhead);
   return strnode;
   }


// Makes a string node by referencing an existing NUL-terminated string.
// This string is modified and must not be in static memory.
NODE *
make_strnode_no_copy(
   const char *strptr, 
   char       *strhead, 
   int         len,
   NODETYPES   typ
)
   {
   if (len == 0 && Null_Word != NIL)
      {
      return Null_Word;
      }

   // increment the reference count
   unsigned short * header = (unsigned short *) strhead;
   incstrrefcnt(header);

   NODE * strnode = newnode(typ);
   setstrlen(strnode, len);
   setstrptr(strnode, strptr);
   setstrhead(strnode, strhead);
   return strnode;
   }

void make_runparse(NODE *ndi)
   {
   NODE *rp_list;

   rp_list = runparse(ndi);
   ref(rp_list);                  /* I don't understand why this is necessary.*/
   setobject(ndi, rp_list);
   settype(ndi, RUN_PARSE);
   }

NODE *make_quote(NODE *qnd)
   {
   NODE * nd = cons_list(qnd);

   settype(nd, QUOTE);
   return nd;
   }

NODE *maybe_quote(NODE *nd)
   {
   if (nd == Unbound || aggregate(nd) || numberp(nd)) return (nd);
   return make_quote(nd);
   }

NODE *make_caseobj(NODE *cstrnd, NODE *obj)
   {
   NODE *nd = cons(cstrnd, obj);

   settype(nd, CASEOBJ);
   return nd;
   }

NODE *make_colon(NODE *cnd)
   {
   NODE *nd = cons_list(cnd);

   settype(nd, COLON);
   return nd;
   }

NODE *make_intnode(FIXNUM i)
   {
   NODE *nd = newnode(INTEGER);

   nd->nunion.nint = i;
   return nd;
   }

NODE *make_floatnode(FLONUM f)
   {
   NODE *nd = newnode(FLOATINGPOINT);

   nd->nunion.nfloat = f;
   return nd;
   }

NODE *cnv_node_to_numnode(NODE *ndi)
   {
   if (is_number(ndi))
      {
      return ndi;
      }

   ndi = cnv_node_to_strnode(ndi);
   if (ndi == Unbound) 
      {
      return Unbound;
      }

   int dr;
   if (((getstrlen(ndi)) < MAX_NUMBER) && (dr = numberp(ndi)))
      {
      char s2[MAX_NUMBER];
      char *s = s2;

      if (backslashed(ndi))
         {
         noparity_strnzcpy(s, getstrptr(ndi), getstrlen(ndi));
         }
      else
         {
         strnzcpy(s, getstrptr(ndi), getstrlen(ndi));
         }

      if (*s == '+') 
         {
         ++s;
         }
      if (s2[getstrlen(ndi) - 1] == '.') 
         {
         s2[getstrlen(ndi) - 1] = '\0';
         }

      NODE *val;
      if (/*TRUE || */ dr - 1 || getstrlen(ndi) > 9)
         {
         val = make_floatnode(atof(s));
         }
      else
         {
         val = make_intnode(atol(s));
         }
      gcref(ndi);
      return val;
      }
   else
      {
      gcref(ndi);
      return Unbound;
      }
   }

NODE *cnv_node_to_strnode(NODE *nd)
   {
   char s[MAX_NUMBER];

   if (nd == Unbound || aggregate(nd))
      {
      return Unbound;
      }
   switch (nodetype(nd))
      {
       case STRING:
       case BACKSLASH_STRING:
       case VBAR_STRING:
           return (nd);

       case CASEOBJ:
           return strnode__caseobj(nd);

       case QUOTE:
           nd = valref(cnv_node_to_strnode(node__quote(nd)));
           nd = reref(
              nd, 
              make_strnode(getstrptr(nd), getstrlen(nd) + 1, nodetype(nd), quote_strnzcpy));
           unref(nd);
           return nd;

       case COLON:
           nd = valref(cnv_node_to_strnode(node__colon(nd)));
           nd = reref(
              nd, 
              make_strnode(getstrptr(nd), getstrlen(nd) + 1, nodetype(nd), colon_strnzcpy));
           unref(nd);
           return nd;

       case INTEGER:
           sprintf(s, "%ld", getint(nd));
           return make_strnode(s, (int) strlen(s), STRING, strnzcpy);

       case FLOATINGPOINT:
           sprintf(s, "%0.15g", getfloat(nd));
           return make_strnode(s, (int) strlen(s), STRING, strnzcpy);
      }

   /*NOTREACHED*/
   assert(0);
   return NIL;
   }

NODE *make_static_strnode(const char *strptr)
   {
   NODE *strnode = newnode(STRING);

   setstrptr(strnode, strptr);
   setstrhead(strnode, NULL);
   setstrlen(strnode, (int) strlen(strptr));
   return (strnode);
   }


NODE *cons_list()
{
  return NIL;
}

NODE *cons_list(NODE * node1)
{
  return cons(node1, NIL);
}

NODE *cons_list(NODE * node1, NODE * node2)
{
  return cons(
     node1, 
     cons(node2, NIL));
}

NODE *cons_list(NODE * node1, NODE * node2, NODE * node3)
{
  return cons(
     node1, 
     cons(
        node2, 
        cons(node3, NIL)));
}

NODE *cons_list(NODE * node1, NODE * node2, NODE * node3, NODE * node4)
{
  return cons(
     node1, 
     cons(
        node2, 
        cons(
           node3,
           cons(node4, NIL))));
}

NODE *cons_list(NODE * node1, NODE * node2, NODE * node3, NODE * node4, NODE * node5)
{
  return cons(
     node1, 
     cons(
        node2, 
        cons(
           node3,
           cons(
              node4,
              cons(node5, NIL)))));
}

NODE *make_array(int len)
   {
   NODE* node = newnode(ARRAY);
   setarrorg(node, 1);
   setarrdim(node, len);
   if (len != 0)
      {
      NODE ** data = (NODE **) malloc(len * sizeof(NODE *));
      if (data == NULL)
         {
         err_logo(OUT_OF_MEM, NIL);
         return Unbound;
         }
      setarrptr(node, data);
      while (--len >= 0)
         {
         *data++ = NIL;
         }
      }
   return node;
   }

NODE *llowercase(NODE *args)
   {
   NODE * arg = string_arg(args);
   if (NOT_THROWING)
      {
      return make_strnode(getstrptr(arg), getstrlen(arg), nodetype(arg), low_strnzcpy);
      }
   return Unbound;
   }

NODE *luppercase(NODE *args)
   {
   NODE * arg = string_arg(args);
   if (NOT_THROWING)
      {
      return make_strnode(getstrptr(arg), getstrlen(arg), nodetype(arg), cap_strnzcpy);
      }
   return Unbound;
   }

/* property list stuff */

NODE *getprop(NODE *plist, NODE *name, bool before)
   {
   NODE *prev = NIL;
   bool caseig = false;

   if (compare_node(valnode__caseobj(Caseignoredp), Truex, TRUE) == 0)
      caseig = TRUE;
   while (plist != NIL)
      {
      if (compare_node(name, car(plist), caseig) == 0)
         {
         return (before ? prev : plist);
         }
      prev = plist;
      plist = cddr(plist);
      }
   return NIL;
   }

NODE *lgprop(NODE *args)
   {
   NODE *val = NIL;

   NODE * plname = string_arg(args);
   NODE * pname = string_arg(cdr(args));
   if (NOT_THROWING)
      {
      plname = intern(plname);

      NODE * plist = plist__caseobj(plname);
      if (plist != NIL)
         {
         val = getprop(plist, pname, FALSE);
         }
      if (val != NIL)
         {
         return cadr(val);
         }
      }
   return NIL;
   }

NODE *lpprop(NODE *args)
   {
   NODE *val = NIL;

   NODE * plname = string_arg(args);
   NODE * pname = string_arg(cdr(args));
   NODE * newval = car(cddr(args));
   if (NOT_THROWING)
      {
      plname = intern(plname);
      if (flag__caseobj(plname, PLIST_TRACED))
         {
         ndprintf(writestream, "Pprop %s %s %s", maybe_quote(plname),
            maybe_quote(pname), maybe_quote(newval));
         if (ufun != NIL)
            ndprintf(writestream, " in %s\n%s", ufun, this_line);
         new_line(writestream);
         }

      NODE * plist = plist__caseobj(plname);
      if (plist != NIL)
         val = getprop(plist, pname, FALSE);
      if (val != NIL)
         setcar(cdr(val), newval);
      else
         setplist__caseobj(plname, cons(pname, cons(newval, plist)));
      }
   return Unbound;
   }

NODE *lremprop(NODE *args)
   {
   bool caseig = false;
   if (compare_node(valnode__caseobj(Caseignoredp), Truex, TRUE) == 0)
      {
      caseig = true;
      }

   NODE * plname = string_arg(args);
   NODE * pname = string_arg(cdr(args));
   if (NOT_THROWING)
      {
      plname = intern(plname);
      NODE * plist = plist__caseobj(plname);
      if (plist != NIL)
         {
         if (compare_node(car(plist), pname, caseig) == 0)
            setplist__caseobj(plname, cddr(plist));
         else
            {
            NODE * val = getprop(plist, pname, TRUE);
            if (val != NIL)
               setcdr(cdr(val), cddr(cddr(val)));
            }
         }
      }
   return Unbound;
   }

NODE *copy_list(NODE *arg)
   {
   NODE *lastnode;
   NODE* val = NIL;

   while (arg != NIL)
      {
      NODE * tnode = cons_list(car(arg));
      if (val == NIL)
         {
         // this is the first node
         lastnode = val = tnode;
         }
      else
         {
         // This is not the first node.
         // link it in just after the last node.
         setcdr(lastnode, tnode);
         lastnode = tnode;
         }
      arg = cdr(arg);
      }
   return val;
   }

NODE *lplist(NODE *args)
   {
   NODE *plname, *plist, *val = NIL;

   plname = string_arg(args);
   if (NOT_THROWING)
      {
      plname = intern(plname);
      plist = plist__caseobj(plname);
      if (plist != NIL)
         val = copy_list(plist);
      }
   return (val);
   }

