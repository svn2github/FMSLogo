/*
*      ibmterm.h          IBM-specific graphics macros         mak
*
*       Copyright (C) 1989 The Regents of the University of California
*       This Software may be copied and distributed for educational,
*       research, and not for profit purposes provided that this
*       copyright and statement are included in all such copies.
*
*/

#define GR_SIZE 10000

// pen_info is a stucture type with fields for the various
// pen characteristics including the location, size, color,
// mode (e.g. XOR or COPY), pattern, visibility (0 = visible)

typedef struct
   {
   // int h;
   // int v;
   bool          penup;
   int           width;
   int           color;
   int           prev_color;
   unsigned char pattern[8];
   int           mode;
   }
pen_info;


