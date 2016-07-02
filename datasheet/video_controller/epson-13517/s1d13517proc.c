/******************************************************************************
 *
 *  File Name   : linux/drivers/video/epson-13517/s1d13517proc.c
 *  Function    : proc handling for frame buffer driver 
 *											for Epson S1D13517 LCD controller.
 *  History     : 2009.09.01    Created by LCDC Project Team.
 *-----------------------------------------------------------------------------
 * Copyright(C) SEIKO EPSON CORPORATION 2009. All rights reserved.
 * This file is licensed under the GPLv2
 ******************************************************************************/

#ifdef CONFIG_FB_EPSON_PROC
/*****************************************************************************
 * include files (#include)
 */
#include <linux/version.h>
#include <linux/proc_fs.h>
#include "s1d13517.h"
#include "s1d13517fb.h"
#include "s1d13517ioctl.h"

/*****************************************************************************
 * local define
 */
#define PROC_INFO						(0)
#define PROC_REGIO						(1)
#define PROC_BPP						(2)
#define PROC_MEMADDR					(3)
#define PROC_FILL16						(4)
#define PROC_FRAME						(5)

#ifdef EPSON_VIRTUAL_FRAMEBUFFER
#define	PROC_ENTRY_FT					("ft")
#endif
#define	PROC_ENTRY_FILL16				("fill16")
#define	PROC_ENTRY_MEMADDR				("memaddr")
#define	PROC_ENTRY_BPP					("bpp")
#define	PROC_ENTRY_REGIO				("regio")
#define	PROC_ENTRY_INFO					("info")
#define	PROC_DIR_NAME					("s1d13517fb")

/*****************************************************************************
 * Function declare
 */
static int proc_read_fb(char *page, char **start, off_t off, int count,
						int *eof, void *data);
static int proc_write_fb(struct file *file, const char *buffer,
						unsigned long count, void *data);
static int s1d13517proc_atoi(const char *s);
static int s1d13517proc_toupper(int c);
static int s1d13517proc_isxdigit(int c);
static long s1d13517proc_htol(const char *sz_ascii);
static int s1d13517proc_iswhitechar(int c);

/*****************************************************************************
 * Global Variables
 */
static struct proc_dir_entry *s1d13517fb_dir;
static struct proc_dir_entry *info_file;
static struct proc_dir_entry *reg_file;
static struct proc_dir_entry *bpp_file; 
static struct proc_dir_entry *memaddr_file;
static struct proc_dir_entry *fill16_file;

#ifdef EPSON_VIRTUAL_FRAMEBUFFER
static struct proc_dir_entry *ft_file;
#endif

static unsigned long proc_reg_index	= 0;
static unsigned long proc_reg_val		= 0;

/*****************************************************************************
*  [Function Name]	s1d13517proc_init
*
*  [Description]	PROC file system initialize.
*
*  [Parameters]		none.
*
*  [Return]			0		: Successfully
*					-ENOMEM	: Failed to create proc entry
*
*  [Note]
******************************************************************************/
int s1d13517proc_init(void)
{
	dbg_info("%s() start:\n",__FUNCTION__);

	/* Setup /proc support			*/

	/* First setup a subdirectory for s1d13517fb	*/
	s1d13517fb_dir = proc_mkdir(PROC_DIR_NAME, NULL);

	if (!s1d13517fb_dir)
	{
		return -ENOMEM;
	}
	s1d13517fb_dir->owner = THIS_MODULE;
	/* Create INFO entry		*/
	info_file = create_proc_read_entry(PROC_ENTRY_INFO, 0444, s1d13517fb_dir,
										proc_read_fb, (void*)PROC_INFO);
	if (info_file == NULL)
	{
		return -ENOMEM;
	}

	/* Create REGIO entry		*/
	reg_file = create_proc_entry(PROC_ENTRY_REGIO, 0644, s1d13517fb_dir);
	if (reg_file == NULL)
	{
		return -ENOMEM;
	}
	reg_file->data			= (void *)PROC_REGIO;
	reg_file->read_proc		= proc_read_fb;
	reg_file->write_proc	= proc_write_fb;
	reg_file->owner			= THIS_MODULE;

	/* Create BPP entry		*/
	bpp_file = create_proc_entry(PROC_ENTRY_BPP, 0644, s1d13517fb_dir);
	if (bpp_file == NULL)
	{
		return -ENOMEM;
	}
	bpp_file->data = (void *)PROC_BPP;
	bpp_file->read_proc = proc_read_fb;
	bpp_file->write_proc = proc_write_fb;
	bpp_file->owner = THIS_MODULE;

	/* Create MEMEADDR entry		*/
	memaddr_file = create_proc_read_entry(PROC_ENTRY_MEMADDR, 0444, s1d13517fb_dir,
											proc_read_fb, (void*)PROC_MEMADDR);
	if (memaddr_file == NULL)
	{
		return -ENOMEM;
	}

	/* Create FILL16 entry		*/
	fill16_file = create_proc_entry(PROC_ENTRY_FILL16, 0222, s1d13517fb_dir);
	if (!fill16_file)
	{
		return -ENOMEM;
	}
	fill16_file->data		= (void *)PROC_FILL16;
	fill16_file->read_proc	= proc_read_fb;
	fill16_file->write_proc	= proc_write_fb;
	fill16_file->owner		= THIS_MODULE;

#ifdef EPSON_VIRTUAL_FRAMEBUFFER
	/* Create FT entry		*/
	ft_file = create_proc_entry(PROC_ENTRY_FT, 0644, s1d13517fb_dir);
	if (ft_file == NULL)
	{
		return -ENOMEM;
	}
	ft_file->data			= (void *)PROC_FRAME;
	ft_file->read_proc		= proc_read_fb;
	ft_file->write_proc		= proc_write_fb;
	ft_file->owner			= THIS_MODULE;
#endif

	dbg_info("%s() exit:\n",__FUNCTION__);
	return 0;
}

/*****************************************************************************
*  [Function Name]	s1d13517proc_terminate
*
*  [Description]	PROC file system terminate.
*
*  [Parameters]		none.
*
*  [Return]			none.
*
*  [Note]
******************************************************************************/
void s1d13517proc_terminate(void)
{       
	dbg_info("%s() start:\n",__FUNCTION__);

#ifdef EPSON_VIRTUAL_FRAMEBUFFER
	remove_proc_entry(PROC_ENTRY_FT, s1d13517fb_dir);
#endif
	remove_proc_entry(PROC_ENTRY_FILL16, s1d13517fb_dir);
	remove_proc_entry(PROC_ENTRY_MEMADDR, s1d13517fb_dir);
	remove_proc_entry(PROC_ENTRY_BPP, s1d13517fb_dir);
	remove_proc_entry(PROC_ENTRY_REGIO, s1d13517fb_dir);
	remove_proc_entry(PROC_ENTRY_INFO, s1d13517fb_dir);
	remove_proc_entry(PROC_DIR_NAME, NULL);
	dbg_info("%s() exit:\n",__FUNCTION__);
}

/*****************************************************************************
*  [Function Name]	proc_read_fb
*
*  [Description]	PROC read operation.
*
*  [Parameters]		page	:
*					start	:
*					off		:
*					count	:
*					eof		:
*					data	:
*
*  [Return]			len		:
*
*  [Note]
******************************************************************************/
static int proc_read_fb(char *page, char **start, off_t off, int count, 
						int *eof, void *data)
{
	int len = 0;
	int	bpp = 0;

	dbg_info("%s() start:\n",__FUNCTION__);

	/* LCDC chip register initialize	*/
	s1d13517fb_lcdc_init();

	dbg_info("%s() start: *eof=%d\n",__FUNCTION__, *eof);
	switch ((u32)data)
	{
		default:
		case PROC_INFO:
			len = sprintf(page, "%s\n"
				"Syntax when writing to reg:  [index=hex] [val=hex]\n"
				"To read a register, only set index=hex and then read from reg.\n"
				"For example, to read register 0xAB:\n"
				"   echo index=AB > /proc/s1d13517fb/regio\n"
				"   cat /proc/s1d13517fb/regio\n\n",
				s1d13517fb_version
				);
			break;

		case PROC_REGIO:
			len = sprintf(page, 
				"Register I/O: REG[%0lXh]=%0lXh\n\n"
				"Syntax when writing to reg:  [index=hex] [val=hex]\n"
				"To read a register, only set index=hex and then read from reg\n",
				proc_reg_index&0xff, 
				(unsigned long)s1d13517hw_read_reg8(proc_reg_index));
			break;

		case PROC_BPP:
			switch (s1d13517hw_read_reg8(REG14_PANELTYPE) & LCD_DATA_TYPE_BIT)
			{
				case LCD_DATA_TYPE_24BPP:    bpp = S1D_IMAGE_24BPP;  break;
				case LCD_DATA_TYPE_32BPP:    bpp = S1D_IMAGE_32BPP;  break;
				default:   					 bpp = S1D_IMAGE_16BPP;  break;
			}

			len = sprintf(page, 
				"Bits Per Pixel: Driver:%lu  Reg:%lu\n\n"
				"Syntax when writing to bpp:  [16|24|32]\n",
				(unsigned long)s1d13517_fb.var.bits_per_pixel,(unsigned long)bpp);
			break;

		case PROC_MEMADDR:
			len = sprintf(page, 
				"Register: Linear Addr:%lXh  Mapped Length:%lXh\n"
				"Virtual Frame Buffer Addr:%lXh\n",
				(unsigned long)s1d13517fb_info.reg_addr, 
				(unsigned long)s1d13517fb_info.reg_addr_mapped_size, 
				(unsigned long)s1d13517fb_info.framebuffer_addr); 
			break;

		case PROC_FILL16:
			len = sprintf(page, 
				"Fill display memory at 0x%08X (only to size of visible "
				"LCD 0x%X bytes)\n"
				"Syntax when writing to fill16:\n\n"
				"echo hexval > /proc/s1d13517fb/fill16\n\n",
				(unsigned)s1d13517fb_info.framebuffer_addr,
				(unsigned)s1d13517fb_fix.smem_len);
			break;

#ifdef EPSON_VIRTUAL_FRAMEBUFFER
		case PROC_FRAME:
			//len = sprintf(page,"s1d13517fb_flush_virtual_framebuffer()\n\n");
			s1d13517fb_flush_virtual_framebuffer(0, NULL);
			break;
#endif
	}

	dbg_info("%s() exit:\n",__FUNCTION__);
	return len;
}

/*****************************************************************************
*  [Function Name]	proc_write_fb
*
*  [Description]	PROC write operation.
*
*  [Parameters]		file	: file structure pointer
*					buffer	: input string buffer 
*					count	:
*					data	:
*
*  [Return]			len		: count(input parameter)
*
*  [Note]
******************************************************************************/
static int proc_write_fb(struct file *file, const char *buffer, 
						 unsigned long count, void *data)
{
	int got_reg_val	= FALSE;
	int len			= count;
	char *buf		= (char *)buffer;
	u16 *ptr16;
	u16 val16;
	unsigned long i;
	int bpp			= 0;
	int ret			= 0;

	dbg_info("%s() start:\n",__FUNCTION__);

#define SKIP_OVER_WHITESPACE(str,count)							\
{																\
	while ((count > 0) && !s1d13517proc_iswhitechar(*(str)))	\
	{															\
		(str)++;												\
		count--;												\
	}															\
																\
	while ((count > 0) && s1d13517proc_iswhitechar(*(str)))		\
	{															\
		(str)++;												\
		count--;												\
	}															\
}
	/* LCDC chip register initialize	*/
	s1d13517fb_lcdc_init();

	switch ((int)data)
	{
		case PROC_REGIO:
			got_reg_val = FALSE;

			while (count > 0)
			{
				if (!strncmp(buf,"index=",6))
				{
					proc_reg_index = s1d13517proc_htol(buf+6);
				}
				else if (!strncmp(buf,"val=",4))
				{
					proc_reg_val = s1d13517proc_htol(buf+4);
					got_reg_val = 1;
				}
				else
				{
					count = 0;
					break;
				}

				SKIP_OVER_WHITESPACE(buf,count);
			}

			if (got_reg_val)
			{
				dbg_info("%s(): PROC_REGIO: Write  index=0x%04x val=0x%x\n",
					__FUNCTION__, (unsigned int)proc_reg_index, (unsigned int)proc_reg_val);
				s1d13517hw_write_reg8(proc_reg_index,proc_reg_val);
			}
			break;

		case PROC_BPP:
			bpp = s1d13517proc_atoi(buf);

			/* Set LCDC panel type register		*/
			switch(bpp)
			{
				case S1D_IMAGE_16BPP:
					s1d13517hw_modify_reg8(REG14_PANELTYPE, 
										  LCD_DATA_TYPE_BIT, 
										  LCD_DATA_TYPE_16BPP);
					break;
				case S1D_IMAGE_24BPP:
					s1d13517hw_modify_reg8(REG14_PANELTYPE, 
										  LCD_DATA_TYPE_BIT, 
										  LCD_DATA_TYPE_24BPP);
					break;

				case S1D_IMAGE_32BPP:
					s1d13517hw_modify_reg8(REG14_PANELTYPE, 
										  LCD_DATA_TYPE_BIT, 
										  LCD_DATA_TYPE_32BPP);
					break;
				default:
					printk(KERN_WARNING "[%d]BPP is not supported.\n", 
							bpp);
					ret = 1;
					break;
			}
			if (ret == 0) 
			{
				s1d13517_fb.var.bits_per_pixel = bpp;
				s1d13517_fb.fix.line_length = S1D_DISPLAY_WIDTH*bpp/8;
			}
			break;

		case PROC_FILL16:
			val16 = (u16)s1d13517proc_htol(buf);
			ptr16 = (u16*)s1d13517fb_info.framebuffer_addr;

			dbg_info("%s(): PROC_FILL16: Fill at 0x%08x 0x%x bytes with %04x\n",
				__FUNCTION__, (unsigned)ptr16,s1d13517fb_fix.smem_len,val16);

			for (i = 0; i < s1d13517fb_fix.smem_len/sizeof(short); i++)
			{
				*ptr16++ = swab16(val16);
			}
			break;
		default:
			break;

	}
	dbg_info("%s() exit:\n",__FUNCTION__);
	return len;
}

/*****************************************************************************
*  [Function Name]	s1d13517proc_iswhitechar
*
*  [Description]	White char check function.
*
*  [Parameters]		c		: check charactor 
*
*  [Return]			1		: c is white charactor
*					0		: c is not white charactor
*
*  [Note]
******************************************************************************/
static int s1d13517proc_iswhitechar(int c)
{
	return ((c == ' ') || (c >= 0x09 && c <= 0x0d)); 
}

/*****************************************************************************
*  [Function Name]	s1d13517proc_toupper
*
*  [Description]	To upper function.
*
*  [Parameters]		c		: input char
*
*  [Return]			c		: output char
*
*  [Note]
******************************************************************************/
static int s1d13517proc_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c += 'A'-'a';
	}
	return c;
}

/*****************************************************************************
*  [Function Name]	s1d13517proc_isxdigit
*
*  [Description]	Char digit check function.
*
*  [Parameters]		c		: ascii code
*
*  [Return]			0		: c is digit
*					1		: c is not digit
*
*  [Note]
******************************************************************************/
static int s1d13517proc_isxdigit(int c)
{
	if ((c >= '0' && c <= '9') || 
		(c >= 'a' && c <= 'f') ||
		(c >= 'A' && c <= 'F'))
	{
		return 1;
	}

	return 0;
}

/*****************************************************************************
*  [Function Name]	s1d13517proc_htol
*
*  [Description]	Hex to long function.
*
*  [Parameters]		sz_ascii	: input char
*
*  [Return]			lTmp		: output
*
*  [Note]
******************************************************************************/
static long s1d13517proc_htol(const char *sz_ascii)
{
	long lTmp;
	char ch;

	lTmp = 0;

	// skip whitespace
	while (s1d13517proc_iswhitechar(*sz_ascii))
	{
		sz_ascii++;
	}

	while (!s1d13517proc_iswhitechar((int) *sz_ascii) && ('\0' != *sz_ascii))
	{
		ch = (char)s1d13517proc_toupper(*sz_ascii);

		if (!s1d13517proc_isxdigit((int) ch))
		{
			return 0;
		}

		if ((ch >= 'A') && (ch <= 'F'))
		{
			lTmp = lTmp * 16 + 10 + (ch - 'A');
		}
		else
		{
			lTmp = lTmp * 16 + (ch - '0');
		}
		sz_ascii++;
	}

	return lTmp;
}

/*****************************************************************************
*  [Function Name]	s1d13517proc_atoi
*
*  [Description]	Ascii to int function.
*
*  [Parameters]		s		: input char
*
*  [Return]			k		: output
*
*  [Note]
******************************************************************************/
static int s1d13517proc_atoi(const char *s)
{
	int k = 0;

	while (*s != '\0' && *s >= '0' && *s <= '9') {
		k = 10 * k + (*s - '0');
		s++;
	}
	return k;
}


#endif // CONFIG_FB_EPSON_PROC
