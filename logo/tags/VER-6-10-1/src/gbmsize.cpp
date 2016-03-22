/*

gbmsize.c - Change size of General Bitmap

*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <memory.h>
#include <malloc.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifndef O_BINARY
#define	O_BINARY	0
#endif
#include "gbm.h"

int gbmBmpToGif(char *fn_src, char *fn_dst)
	{
	int	w = -1, h = -1;
	char	opt_src[] = "";
   char  opt_dst[] = "";
	int	fd, ft_src, ft_dst, stride, flag;
	GBM_ERR	rc;
	GBMFT	gbmft;
	GBM	gbm;
	GBMRGB	gbmrgb[0x100];
	byte	*data;

	gbm_init();

   ft_src = 0;
   ft_dst = 1;

	if ( (fd = gbm_io_open(fn_src, O_RDONLY|O_BINARY)) == -1 )
      {
//		fatal("can't open %s", fn_src);
      return 1;
      }

	if ( (rc = gbm_read_header(fn_src, fd, ft_src, &gbm, opt_src)) != GBM_ERR_OK )
		{
		gbm_io_close(fd);
//		fatal("can't read header of %s: %s", fn_src, gbm_err(rc));
      return 2;
		}

   w = gbm.w;
   h = gbm.h;

	gbm_query_filetype(ft_dst, &gbmft);
	switch ( gbm.bpp )
		{
		case 24:	flag = GBM_FT_W24;break;
		case 8:	flag = GBM_FT_W8;	break;
		case 4:	flag = GBM_FT_W4;	break;
		case 1:	flag = GBM_FT_W1;	break;
		}

	if ( (gbmft.flags & flag) == 0 )
		{
		gbm_io_close(fd);
//		fatal("output bitmap format %s does not support writing %d bpp data", gbmft.short_name, gbm.bpp);
      return 3;
		}

	if ( (rc = gbm_read_palette(fd, ft_src, &gbm, gbmrgb)) != GBM_ERR_OK )
		{
		gbm_io_close(fd);
//		fatal("can't read palette of %s: %s", fn_src, gbm_err(rc));
      return 4;
		}

	stride = ( ((gbm.w * gbm.bpp + 31)/32) * 4 );
	if ( (data = (byte *)malloc((size_t) (stride * gbm.h))) == NULL )
		{
		gbm_io_close(fd);
//		fatal("out of memory allocating %d bytes for input bitmap", stride * gbm.h);
      return 5;
		}

	if ( (rc = gbm_read_data(fd, ft_src, &gbm, data)) != GBM_ERR_OK )
		{
		free(data);
		gbm_io_close(fd);
//		fatal("can't read bitmap data of %s: %s", fn_src, gbm_err(rc));
      return 6;
		}

	gbm_io_close(fd);

extern int bAppendMode;

   if (bAppendMode)
      {
      if ( (fd = gbm_io_open(fn_dst, O_RDWR|O_BINARY)) == -1 )
         {
         free(data);
//       fatal("can't create %s", fn_dst);
         return 7;
         }
      gbm_io_lseek(fd, -1, SEEK_END);
      }
   else
      {
      if ( (fd = gbm_io_create(fn_dst, O_WRONLY|O_BINARY)) == -1 )
         {
         free(data);
//       fatal("can't create %s", fn_dst);
         return 7;
         }
      }

	gbm.w = w;
	gbm.h = h;

	if ( (rc = gbm_write(fn_dst, fd, ft_dst, &gbm, gbmrgb, data, opt_dst)) != GBM_ERR_OK )
		{
		gbm_io_close(fd);
		remove(fn_dst);
		free(data);
//		fatal("can't write %s: %s", fn_dst, gbm_err(rc));
      return 8;
		}

	gbm_io_close(fd);
	free(data);

	gbm_deinit();

	return 0;
	}

int gbmGifToBmp(char *fn_src, char *fn_dst)
	{
	int	w = -1, h = -1;
	char	opt_src[] = "";
   char  opt_dst[] = "";
	int	fd, ft_src, ft_dst, stride, flag;
	GBM_ERR	rc;
	GBMFT	gbmft;
	GBM	gbm;
	GBMRGB	gbmrgb[0x100];
	byte	*data;

	gbm_init();

   ft_src = 1;
   ft_dst = 0;

	if ( (fd = gbm_io_open(fn_src, O_RDONLY|O_BINARY)) == -1 )
      {
//		fatal("can't open %s", fn_src);
      return 1;
      }

	if ( (rc = gbm_read_header(fn_src, fd, ft_src, &gbm, opt_src)) != GBM_ERR_OK )
		{
		gbm_io_close(fd);
//		fatal("can't read header of %s: %s", fn_src, gbm_err(rc));
      return 2;
		}

   w = gbm.w;
   h = gbm.h;

	gbm_query_filetype(ft_dst, &gbmft);
	switch ( gbm.bpp )
		{
		case 24:	flag = GBM_FT_W24;break;
		case 8:	flag = GBM_FT_W8;	break;
		case 4:	flag = GBM_FT_W4;	break;
		case 1:	flag = GBM_FT_W1;	break;
		}

	if ( (gbmft.flags & flag) == 0 )
		{
		gbm_io_close(fd);
//		fatal("output bitmap format %s does not support writing %d bpp data", gbmft.short_name, gbm.bpp);
      return 3;
		}

	if ( (rc = gbm_read_palette(fd, ft_src, &gbm, gbmrgb)) != GBM_ERR_OK )
		{
		gbm_io_close(fd);
//		fatal("can't read palette of %s: %s", fn_src, gbm_err(rc));
      return 4;
		}

	stride = ( ((gbm.w * gbm.bpp + 31)/32) * 4 );
	if ( (data = (byte *)malloc((size_t) (stride * gbm.h))) == NULL )
		{
		gbm_io_close(fd);
//		fatal("out of memory allocating %d bytes for input bitmap", stride * gbm.h);
      return 5;
		}

	if ( (rc = gbm_read_data(fd, ft_src, &gbm, data)) != GBM_ERR_OK )
		{
		free(data);
		gbm_io_close(fd);
//		fatal("can't read bitmap data of %s: %s", fn_src, gbm_err(rc));
      return 6;
		}

	gbm_io_close(fd);

   if ( (fd = gbm_io_create(fn_dst, O_WRONLY|O_BINARY)) == -1 )
      {
      free(data);
      //       fatal("can't create %s", fn_dst);
      return 7;
      }
   
	gbm.w = w;
	gbm.h = h;

	if ( (rc = gbm_write(fn_dst, fd, ft_dst, &gbm, gbmrgb, data, opt_dst)) != GBM_ERR_OK )
		{
		gbm_io_close(fd);
		remove(fn_dst);
		free(data);
//		fatal("can't write %s: %s", fn_dst, gbm_err(rc));
      return 8;
		}

	gbm_io_close(fd);
	free(data);

	gbm_deinit();

	return 0;
	}

