/******************************************************************************
 *
 *  File Name   : linux/drivers/video/epson-13517/s1d13517ioctl.h
 *  Function    : IOCTL definitions for Epson S1D13517 LCD controller.
 *  History     : 2009.09.01    Created by LCDC Project Team.
 *-----------------------------------------------------------------------------
 * Copyright(C) SEIKO EPSON CORPORATION 2009. All rights reserved.
 * This file is licensed under the GPLv2
 ******************************************************************************/
#ifndef __S1D13517IOCTL_H__
#define __S1D13517IOCTL_H__

/* ioctls
    0x45 is 'E'  
                                                        */

struct s1d13517_rect
{
	unsigned int xstart;
	unsigned int ystart;
	unsigned int xend;
	unsigned int yend;
};

struct s1d13517_ioctl_hwc
{
	unsigned int 			addr;
	unsigned int 			value;
	void 					*buffer;
	unsigned int			buf_num;
	struct s1d13517_rect 	rect;
};

#define S1D13517_REGREAD				0x4500
#define S1D13517_REGWRITE				0x4501
#define S1D13517_MEMBURSTWRITE			0x4502
#define S1D13517_VBUF_REFRESH			0x4503

#endif  //__S1D13517IOCTL_H__
