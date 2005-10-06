#define NUMBER double

struct display
   {
   NUMBER turtx, turty, turth;         /* current values                      */
   NUMBER xlow, xhigh, ylow, yhigh;    /* limits for this dpy                 */
   NUMBER stdscrunch;                  /* standard aspect ratio               */
   long cleared;                       /* nonzero after first use             */
   char *init, *finish;                /* printed to enable, disable gfx      */
   char *totext;                       /* printed for temporary textscreen    */
   char *clear;                        /* printed for cs, and after init      */
   void (*drawturt) (long);            /* one arg, 0 to show, 1 to erase      */
   void (*drawfrom) (NUMBER, NUMBER);  /* 2 args, x and y, draw vector        */
   void (*drawto) (NUMBER, NUMBER);    /* 2 args, x and y, draw vector        */
   void (*txtchk)();                   /* make error if can't gfx in txtmode  */
   void (*infn) (void);
   void (*outfn)();                    /* no args, called to enable, disable  */
   void (*turnturt)();                 /* no args, tell Atari turtle heading  */
   void (*penc) (long);
   void (*setc)();                     /* color map routines                  */
   void (*state) (char);               /* one arg, state change flag          */
   void (*done) (void);                /* call when done with graphics        */
   void (*undone) (void);              /* call to turn graphics back on       */
   }
;

#define IBUFSIZ 1000
#define FILDES int

