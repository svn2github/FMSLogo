/*

gbmhelp.c - Helpers for GBM file I/O stuff

*/

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include <stdio.h>
   #include <ctype.h>
   #include <stddef.h>
   #include <stdlib.h>
   #include <string.h>
   #include <memory.h>
   #include <malloc.h>
   #ifdef __GNUC__
      #include <unistd.h>
   #else
      #include <io.h>
   #endif
   #include <fcntl.h>
   #include <sys/types.h>
   #include <sys/stat.h>
   #include "gbm.h"
   #include "gbmhelp.h"
   #include "debugheap.h"
#endif


BOOLEAN gbm_same(const char *s1, const char *s2, int n)
{
    for ( ; n--; s1++, s2++ )
        if ( tolower(*s1) != tolower(*s2) )
            return FALSE;
    return TRUE;
}

const char *gbm_find_word(const char *str, const char *substr)
{
    char buf[100+1], *s;
    int  len = strlen(substr);

    for ( s  = strtok(strcpy(buf, str), " \t,");
          s != NULL;
          s  = strtok(NULL, " \t,") )
        if ( gbm_same(s, substr, len) && s[len] == '\0' )
            return str + (s - buf);
    return NULL;
}

const char *gbm_find_word_prefix(const char *str, const char *substr)
{
    char buf[100+1], *s;
    int  len = strlen(substr);

    for ( s  = strtok(strcpy(buf, str), " \t,");
          s != NULL;
          s  = strtok(NULL, " \t,") )
        if ( gbm_same(s, substr, len) )
            return str + (s - buf);
    return NULL;
}

int gbm_file_open(const char *fn, int mode)
{ 
    return open(fn, mode);
}
int gbm_file_create(const char *fn, int mode)
{
    return open(fn, O_CREAT|O_TRUNC|mode, S_IREAD|S_IWRITE);
}
void gbm_file_close(int fd)
{
    close(fd);
}
long gbm_file_lseek(int fd, long pos, int whence)
{
    return lseek(fd, pos, whence);
}
int gbm_file_read(int fd, void *buf, int len)
{
    return read(fd, buf, len);
}
int gbm_file_write(int fd, const void *buf, int len)
{
    return write(fd, buf, len);
}

AHEAD *gbm_create_ahead(int fd)
{
    AHEAD *ahead;

    if ( (ahead = (AHEAD *)malloc((size_t) sizeof(AHEAD))) == NULL )
        return NULL;

    ahead->inx = 0;
    ahead->cnt = 0;
    ahead->fd  = fd;

    return ahead;
}

void gbm_destroy_ahead(AHEAD *ahead)
{
    free(ahead);
}	

int gbm_read_ahead(AHEAD *ahead)
{
    if ( ahead->inx >= ahead->cnt )
    {
        ahead->cnt = gbm_file_read(ahead->fd, (char *) ahead->buf, AHEAD_BUF);
        if ( ahead->cnt <= 0 )
            return -1;
        ahead->inx = 0;
    }
    return (int) (unsigned int) ahead->buf[ahead->inx++];
}
