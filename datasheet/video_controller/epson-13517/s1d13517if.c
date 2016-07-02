/******************************************************************************
 *
 *  File Name   : linux/drivers/video/epson-13517/s1d13517if.c
 *  Function    : Frame buffer driver for Epson S1D13517 LCD controller.
 *  History     : 2009.09.01    Created by LCDC Project Team.
 *-----------------------------------------------------------------------------
 * Copyright(C) SEIKO EPSON CORPORATION 2009. All rights reserved.
 * This file is licensed under the GPLv2
 ******************************************************************************/

#define S1D13517FB_VERSION "S1D13517FB: $Revision: 1.3 $"

/*****************************************************************************
 * include files (#include)
 */
#include <linux/kernel.h>
#include <linux/fb.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <linux/signal.h>

#include "s1d13517.h"
#include "s1d13517fb.h"
#include "s1d13517ioctl.h"

#ifdef CONFIG_FB_EPSON_SHOW_SETTINGS

	/* This section only reports the configuration settings		*/

	#warning Configuring for Epson S1D13517 Frame Buffer

	#ifdef CONFIG_FB_EPSON_PCMCIA
		#warning Using PCMCIA interface
	#else
		#warning Not using PCMCIA interface
	#endif

	#ifdef EPSON_VIRTUAL_FRAMEBUFFER
		#warning Using Virtual Framebuffer(copy of framebuffer in system memory)
	#else
		#warning Direct pointers to framebuffer
	#endif

	#ifdef CONFIG_FB_EPSON_PROC
		#warning Adding /proc functions
	#else
		#warning No /proc functions
	#endif

	#ifdef CONFIG_FB_EPSON_DEBUG_PRINTK
		#warning Enable debugging printk() calls
	#else
		#warning No debugging printk() calls
	#endif

#endif

/*****************************************************************************
 * local define
 */
 /* s1d13517fb_init_flag				*/
#define	LCDC_NOT_INITIAL			0	/* LCDC register is not intialized. */
#define	LCDC_INITIALIZED			1	/* LCDC register is initialized.	*/

/*****************************************************************************
 * Function declare
 */
int  __devinit s1d13517fb_init(void);
int  __devinit s1d13517fb_setup(char *options, int *ints);
void __exit s1d13517fb_exit(void);
static int	s1d13517fb_open(struct fb_info *info, int user);
static int  s1d13517fb_set_par(struct fb_info *info); 
static void s1d13517fb_fillrect(struct fb_info *p,
						const struct fb_fillrect *rect);
static void s1d13517fb_copyarea(struct fb_info *p, 
  						const struct fb_copyarea *area);
static void s1d13517fb_imageblit(struct fb_info *p,
						const struct fb_image *image);
static int  s1d13517fb_check_var(struct fb_var_screeninfo *var,
						struct fb_info *info);
static int  s1d13517fb_setcolreg(unsigned regno, unsigned red, unsigned green,
						unsigned blue, unsigned transp, struct fb_info *info);
static int  s1d13517fb_ioctl(struct fb_info *info, unsigned int cmd,
						unsigned long arg);
static int  s1d13517fb_mmap(struct fb_info *info, struct vm_area_struct *vma);
static void s1d13517fb_init_registers(void);
#ifdef EPSON_VIRTUAL_FRAMEBUFFER
static int  s1d13517fb_set_virtual_framebuffer(void);
#endif

/*****************************************************************************
 * Global Variables
 */
char *s1d13517fb_version	= S1D13517FB_VERSION;

static struct fb_ops s1d13517fb_ops =
{
	.owner			= THIS_MODULE,
	.fb_open		= s1d13517fb_open,
	.fb_set_par		= s1d13517fb_set_par,
	.fb_check_var	= s1d13517fb_check_var,
	.fb_setcolreg	= s1d13517fb_setcolreg,
	.fb_fillrect	= s1d13517fb_fillrect,
	.fb_copyarea	= s1d13517fb_copyarea,
	.fb_imageblit	= s1d13517fb_imageblit,
	.fb_mmap		= s1d13517fb_mmap,
	.fb_ioctl		= s1d13517fb_ioctl,
};

struct fb_fix_screeninfo s1d13517fb_fix = 
{
	.id				= "s1d13517", 
	.type			= FB_TYPE_PACKED_PIXELS,
	.type_aux		= 0,
	.xpanstep		= 0,
	.ypanstep		= 0,
	.ywrapstep		= 0,
	.smem_len		= S1D_SCREEN_SIZE,
	.line_length	= S1D_LINE_LENGTH, 
	.accel			= FB_ACCEL_NONE,
};

struct fb_info		s1d13517_fb;
FB_INFO_S1D13517	s1d13517fb_info;
static int			s1d13517fb_init_flag	= LCDC_NOT_INITIAL;
static spinlock_t 	spinlock_if;

/*****************************************************************************
*  [Function Name] s1d13517fb_open
*
*  [Description]	Fill in the 'var' structure.
*
*  [Parameters]		info	: Frame buffer info structure pointer 
*  					user	: Frame buffer accessing user
*							  userland(1)/another console 
*
*  [Return]			0		: Successfully
* 
*  [Note]
******************************************************************************/
static int s1d13517fb_open(struct fb_info *info, int user)
{
	dbg_info("%s() start:\n",__FUNCTION__); 
	/* LCDC chip register initialize	*/
	s1d13517fb_lcdc_init();	
	dbg_info("%s() exit:\n",__FUNCTION__); 
	return 0;
}

/*****************************************************************************
*  [Function Name] s1d13517fb_check_var
*
*  [Description]	Fill in the 'var' structure.
*
*  [Parameters]		var		: Variable screen info structure pointer
*  					info	: Frame buffer info structure pointer
*
*  [Return]			0		: Successfully
*					-EINVAL	: Invalid image bit per pixel.
* 
*  [Note]
******************************************************************************/
static int s1d13517fb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	var->xres			= S1D_DISPLAY_WIDTH;
	var->yres			= S1D_DISPLAY_HEIGHT;
	var->xres_virtual	= var->xres;
	var->yres_virtual	= var->yres;
	var->xoffset		= var->yoffset = 0;
	var->bits_per_pixel	= S1D_DISPLAY_BPP;
	var->grayscale		= 0;
	var->nonstd			= 0;				/* != 0 Non standard pixel format */
	var->activate		= FB_ACTIVATE_NOW;	/* see FB_ACTIVATE_*             */
	var->height			= -1;				/* height of picture in mm       */
	var->width			= -1;				/* width of picture in mm        */
	var->accel_flags	= 0;				/* acceleration flags (hints     */
	var->pixclock		= S1D_DISPLAY_PCLK;
	var->right_margin	= 0;
	var->lower_margin	= 0;
	var->hsync_len		= 0;
	var->vsync_len		= 0;
	var->left_margin	= 0;
	var->upper_margin	= 0;
	var->sync			= 0;
	var->vmode			= FB_VMODE_NONINTERLACED;
	var->red.msb_right  = var->green.msb_right = var->blue.msb_right = 0;
	var->transp.offset  = var->transp.length = var->transp.msb_right = 0;

	dbg_info("%s() start:\n",__FUNCTION__); 

	s1d13517fb_fix.visual = FB_VISUAL_TRUECOLOR;

	switch (info->var.bits_per_pixel)
	{
		case S1D_IMAGE_16BPP:		/* RGB 565 */
			var->red.offset				= 11;
			var->red.length				= 5;
			var->green.offset			= 5;
			var->green.length			= 6;
			var->blue.offset			= 0;
			var->blue.length			= 5;
			var->transp.offset			= 0;
			var->transp.length			= 0;
			break;
		case S1D_IMAGE_24BPP:		/* RGB 888 */
			var->red.offset 			= 16;
			var->red.length 			= 8;
			var->green.offset 			= 8;
			var->green.length 			= 8;
			var->blue.offset 			= 0;
			var->blue.length 			= 8;
			var->transp.offset 			= 0;
			var->transp.length 			= 0;
			break;
		default:
			printk(KERN_WARNING "%dbpp is not supported.\n",
					info->var.bits_per_pixel);
			return -EINVAL;
	}

	dbg_info("%s() exit:\n",__FUNCTION__); 
	return 0;
}

/*****************************************************************************
*  [Function Name]	s1d13517fb_setcolreg
*
*  [Description]	Set a single color register. The values supplied have a 
*					16 bit magnitude.
*
*  [Parameters]		regno	: Pallete number
*  					red		: The red value which can be up to 16 bits wide
*  					green	: The red value which can be up to 16 bits wide 
*  					blue	: The red value which can be up to 16 bits wide
*  					transp	: The alpha value which can be up to 16 bits wide
*  					info	: Frame buffer info structure pointer
*
*  [Return]			0		: Successfully
* 
*  [Note]			We get called even if we specified that we don't have 
*					a programmable palette or in direct/true color modes!
******************************************************************************/
static int s1d13517fb_setcolreg(unsigned regno, unsigned red, unsigned green,
						 unsigned blue, unsigned transp, struct fb_info *info) 
{
	dbg_info("%s() start:\n",__FUNCTION__); 
	dbg_info("regno=%02Xh red=%04Xh green=%04Xh blue=%04Xh transp=%04Xh\n",
			regno, red, green, blue, transp);

	/* Make the first 16 LUT entries available to the console	*/
	switch (info->var.bits_per_pixel) 
	{
		default:
		case S1D_IMAGE_16BPP:
			/* This code will only work when LUT1 has been set to bypass mode.
			 * When LUT1 is bypassed, driver is in FB_VISUAL_TRUECOLOR mode.
			 */
			if (regno < S1D13517_PALETTE_MAX)
			{	/* RGB 565		*/ 
				((u32*)info->pseudo_palette)[regno] = 
				(red & 0xf800)|((green & 0xfc00) >> 5)|((blue & 0xf800) >> 11); 
			}
			break;
	}

	dbg_info("%s() exit:\n",__FUNCTION__); 
	return 0; 
}

/*****************************************************************************
*  [Function Name]	s1d13517fb_set_par
*
*  [Description]	Fill in the 'fix' structure.
*
*  [Parameters]		info	: Frame buffer info structure pointer 
*
*  [Return]			0		: Successfully
* 
*  [Note]
******************************************************************************/
static int s1d13517fb_set_par(struct fb_info *info)
{
	dbg_info("%s() start:\n",__FUNCTION__); 

	info->fix = s1d13517fb_fix;
	info->fix.mmio_start = 
			(unsigned long)virt_to_phys((void*)s1d13517fb_info.reg_addr);
	info->fix.mmio_len   = 
			s1d13517fb_info.reg_addr_mapped_size; 
	info->fix.smem_start = 
			virt_to_phys((void*)s1d13517fb_info.framebuffer_addr);
	info->screen_base    = 
			(unsigned char*)s1d13517fb_info.framebuffer_addr;
	info->screen_size    = S1D_SCREEN_SIZE; 

	dbg_info("%s() exit:\n",__FUNCTION__); 
	return 0;
}

/*****************************************************************************
*  [Function Name]	s1d13517fb_mmap
*
*  [Description]	Remaps virtual framebuffer from virtual memory space to
*					a physical space.
*
*  [Parameters]		info	: Frame buffer info structure pointer 
*					vma		: Virtual memory area structure pointer
*
*  [Return]			0		: Successfully
*					-EINVAL	: 
*					-EAGAIN	: Remap error
* 
*  [Note]			If no virtual framebuffer is used, the default fb_mmap
*					outline should be fine, unless there is a concern over
*					to use of o_remap_pfn_range versus remap_pfn_range.
******************************************************************************/
static int s1d13517fb_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	unsigned long off;
	unsigned long start;
	u32 len;

	dbg_info("%s() start:\n",__FUNCTION__); 

	off = vma->vm_pgoff << PAGE_SHIFT;

	/* frame buffer memory 			*/
	start = info->fix.smem_start;
	len = PAGE_ALIGN((start & ~PAGE_MASK) + info->fix.smem_len);

	if (off >= len) 
	{
		/* memory mapped io 		*/
		off -= len;

		if (info->var.accel_flags)
		{
			return -EINVAL;
		}

		start = info->fix.mmio_start;
		len = PAGE_ALIGN((start & ~PAGE_MASK) + info->fix.mmio_len);
	}

	start &= PAGE_MASK;

	if ((vma->vm_end - vma->vm_start + off) > len)
	{
		return -EINVAL;
	}

	off += start;
	vma->vm_pgoff = off >> PAGE_SHIFT;

	/* This is an IO map - tell maydump to skip this VMA 	*/
	vma->vm_flags |= VM_RESERVED;

	if (remap_pfn_range(vma, vma->vm_start, off >> PAGE_SHIFT,
						vma->vm_end - vma->vm_start, vma->vm_page_prot))
	{
		return -EAGAIN;
	}

	dbg_info("%s() exit:\n",__FUNCTION__); 
	return 0;
}

#ifdef EPSON_VIRTUAL_FRAMEBUFFER
/*****************************************************************************
*  [Function Name]	s1d13517fb_set_virtual_framebuffer
*
*  [Description]	Allocates virtual framebuffer..
*
*  [Parameters]		none. 
*
*  [Return]			0		: Successfully
*					1		: memory allocate error
* 
*  [Note]
******************************************************************************/
static int s1d13517fb_set_virtual_framebuffer(void)
{
	u32 order = 0;
	u32 size = S1D_SCREEN_SIZE;
	u32 addr;

	dbg_info("%s() start:\n",__FUNCTION__); 

	while (size > (PAGE_SIZE * (1 << order)))
	{
		order++;
	}

	s1d13517fb_info.framebuffer_addr = 
			(unsigned char*)__get_free_pages(GFP_KERNEL, order);

	if (s1d13517fb_info.framebuffer_addr == 0)
	{
		printk(KERN_WARNING "%s(): Could not allocate memory"
							"for virtual display buffer.\n", 
							__FUNCTION__);
		return 1;
	}

	for (addr = (u32)s1d13517fb_info.framebuffer_addr;
		 addr < ((u32)s1d13517fb_info.framebuffer_addr+size);
		 addr += PAGE_SIZE)
	{
		SetPageReserved(virt_to_page(addr));
	}

	dbg_info("%s() exit:\n",__FUNCTION__); 
	return 0;
}
#endif


/*****************************************************************************
*  [Function Name]	s1d13517fb_init
*
*  [Description]	Initialize the chip and the frame buffer driver.
*
*  [Parameters]		none. 
*
*  [Return]			0		: Successfully
*					-EINVAL	: framebuffer registory error
* 
*  [Note]
******************************************************************************/
int s1d13517fb_init(void)
{  
	dbg_info("%s() start:\n",__FUNCTION__); 

	/* Initialize the chip to use Indirect Interface	*/
	if (s1d13517hw_init() != 0)
	{
		printk(KERN_WARNING "s1d13517fb_init: InterfaceInit error\n"); 
		return -EINVAL;
	}
#ifdef EPSON_VIRTUAL_FRAMEBUFFER
	/* Allocate the virtual framebuffer			*/
	if (s1d13517fb_set_virtual_framebuffer())
	{
		printk(KERN_WARNING "s1d13517fb_init: _get_free_pages() failed.\n");
		return -EINVAL;
	}
#endif

#ifndef CONFIG_FB_EPSON_PCMCIA
	if (s1d13517fb_fb_registers())
	{
		printk(KERN_ERR "s1d13517fb_init(): Could not register"
						"frame buffer with kernel.\n");
		return -EINVAL;
	}
#endif
	spin_lock_init(&spinlock_if);
	dbg_info("%s() exit:\n",__FUNCTION__); 
	return 0;
}

/*****************************************************************************
*  [Function Name]	s1d13517fb_fb_registers
*
*  [Description]	Initialize the chip register.
*
*  [Parameters]		none. 
*
*  [Return]			0		: Successfully
*					1		: framebuffer registory error
* 
*  [Note]
******************************************************************************/
int s1d13517fb_fb_registers(void)
{
	dbg_info("%s() start:\n",__FUNCTION__); 

	/* Set the controller registers and initialize the display	*/
	s1d13517fb_set_par(&s1d13517_fb);

	/* Set flags for controller supported features		*/
	s1d13517_fb.flags = FBINFO_FLAG_DEFAULT;

	/* Set the pseudo palette			*/
	s1d13517_fb.pseudo_palette = s1d13517fb_info.pseudo_palette;

	s1d13517fb_check_var(&s1d13517_fb.var, &s1d13517_fb);
	s1d13517_fb.fbops = &s1d13517fb_ops;
	s1d13517_fb.node = -1;

	if (register_framebuffer(&s1d13517_fb) < 0)
	{
		return 1;
	}

	printk(KERN_INFO "fb%d: %s frame buffer device\n",
			s1d13517_fb.node, s1d13517_fb.fix.id);

#ifdef CONFIG_FB_EPSON_PROC
	s1d13517proc_init();
#endif
	dbg_info("%s() exit:\n",__FUNCTION__); 
	return 0;
}

/*****************************************************************************
*  [Function Name]	s1d13517fb_lcdc_init
*
*  [Description]	Initialize the LCDC chip register.
*
*  [Parameters]		none. 
*
*  [Return]			none.
* 
*  [Note]
******************************************************************************/
void s1d13517fb_lcdc_init(void)
{
	unsigned long flags;

	dbg_info("%s() start:\n",__FUNCTION__); 
	spin_lock_irqsave(&spinlock_if,flags);
	if (s1d13517fb_init_flag != LCDC_INITIALIZED) {
		s1d13517fb_init_registers();
		s1d13517fb_init_flag = LCDC_INITIALIZED;
	}
	spin_unlock_irqrestore(&spinlock_if,flags);
	dbg_info("%s() exit:\n",__FUNCTION__); 
}

/*****************************************************************************
*  [Function Name]	s1d13517fb_init_registers
*
*  [Description]	Initialize the chip register.
*
*  [Parameters]		none. 
*
*  [Return]			none.
* 
*  [Note]
******************************************************************************/
static void s1d13517fb_init_registers(void)
{
	S1D_INSTANTIATE_REGISTERS(static,init_reg_array);
	int i;

	dbg_info("%s() start:\n",__FUNCTION__); 

	/* Needed for OS functions like seOsDelayUS, this function takes to long     to 
	 * be run with each delay call, but must be called for each thread
	 */
	set_current_state(TASK_UNINTERRUPTIBLE);

	/* Initialize the registers.		*/
	for (i = 0; i < sizeof(init_reg_array)/sizeof(init_reg_array[0]); i++)
	{
		if (init_reg_array[i].index > S1D_REGRESERVED)
		{
			msleep(init_reg_array[i].value);  /* ms delay.		*/
		}
		else
		{
			s1d13517hw_write_reg8(init_reg_array[i].index, 
								 init_reg_array[i].value);
			dbg_info("%s(): Reg[0x%02x]:=0x%02x\n", __FUNCTION__,
					init_reg_array[i].index, init_reg_array[i].value);
		}
	}

	dbg_info("%s() exit:\n",__FUNCTION__); 
}

#if defined(EPSON_VIRTUAL_FRAMEBUFFER)
/*****************************************************************************
*  [Function Name]	s1d13517fb_flush_virtual_framebuffer
*
*  [Description]	Flushes the virtual framebuffer to the display frame buffer.
*
*  [Parameters]		buf_num		: write buffer number 
*					p_rect		: rectangle structure pointer
*
*  [Return]			0			: Successfully
*					-EFAULT		: Failed s1d13517hw_rect_write_memory16(). 
* 
*  [Note]
******************************************************************************/
int s1d13517fb_flush_virtual_framebuffer(int buf_num,
										  struct s1d13517_rect *p_rect)
{
	u16* pSource = (u16*) s1d13517fb_info.framebuffer_addr;
	struct s1d13517_rect	rect;

	dbg_info("%s() start:dest=0x%08x source=0x%08x\n",
			 __FUNCTION__, (int)S1D_SDRAM_START_ADDR, (int)pSource); 

	/* p_rect is NULL for proc,copyarea,fillrect,imgblit */
	if (p_rect == NULL)
	{
		 buf_num = s1d13517hw_read_reg8(REG52_INPUTMODE)>>4;
		 rect.xstart = 0;
		 rect.ystart = 0;
		 rect.xend   = S1D_DISPLAY_WIDTH-1;
		 rect.yend   = S1D_DISPLAY_HEIGHT-1;
		 p_rect = &rect;
	}
	/* Rect write to memory(SDRAM) */
	if (s1d13517hw_rect_write_memory16(pSource, buf_num, p_rect))
	{
		return -EFAULT;
	}

	dbg_info("%s() exit:\n",__FUNCTION__); 
	return 0;
}
#endif //EPSON_VIRTUAL_FRAMEBUFFER


/*****************************************************************************
*  [Function Name]	s1d13517fb_ioctl
*
*  [Description]	Handle IOCTL messages from the user space.
*
*  [Parameters]		info	: frame buffer info structure pointer
*					cmd		: ioctl command
*					arg		: argument 
*
*  [Return]			0		: Successfully
*					-EINVAL	: invalid command number
*					-EFAULT	: user data copy error
* 
*  [Note]
******************************************************************************/
int s1d13517fb_ioctl(struct fb_info *info, unsigned int cmd, unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	struct s1d13517_ioctl_hwc ioctl_hwc;
	int			ret = 0;

	dbg_info("%s() start:cmd[0x%04x]\n", __FUNCTION__, cmd); 

	if (copy_from_user(&ioctl_hwc, argp, sizeof(ioctl_hwc)))
	{
		return -EFAULT;
	}

	switch (cmd)
	{
	case S1D13517_VBUF_REFRESH:
#if defined(EPSON_VIRTUAL_FRAMEBUFFER)
		ret = s1d13517fb_flush_virtual_framebuffer(ioctl_hwc.buf_num,
											 &ioctl_hwc.rect);
#endif
		break;

	case S1D13517_REGREAD:
		ioctl_hwc.value = s1d13517hw_read_reg8(ioctl_hwc.addr);
		//dbg_info("s1d1351fb_ioctl: S1D13517_REGREAD reg=%04Xh value=%04Xh\n", 
		//		ioctl_hwc.addr, ioctl_hwc.value);
		ret = copy_to_user(argp, &ioctl_hwc, sizeof(ioctl_hwc)) ? -EFAULT : 0;
		break;

	case S1D13517_REGWRITE:
		//dbg_info("s1d13517fb_ioctl: S1D13517_REGWRITE reg=%04Xh value=%04Xh\n", 
		//		ioctl_hwc.addr, ioctl_hwc.value);
		s1d13517hw_write_reg8(ioctl_hwc.addr, ioctl_hwc.value);
		break;

	case S1D13517_MEMBURSTWRITE:
		ret = s1d13517hw_rect_write_memory16(
									(u16*)ioctl_hwc.buffer, 
									ioctl_hwc.buf_num,
									&ioctl_hwc.rect);
		break;

	default:
		ret = -EINVAL;
		break;
	}
	dbg_info("%s() exit:\n",__FUNCTION__); 
	return ret;
}


/*****************************************************************************
*  [Function Name]	s1d13517fb_fillrect
*
*  [Description]	.
*
*  [Parameters]		p		: frame buffer structure pointer
*					rect	: frame buffer fillrect structure pointer	
*
*  [Return]			none.
* 
*  [Note]
******************************************************************************/
void s1d13517fb_fillrect(struct fb_info *p, const struct fb_fillrect *rect)
{
	dbg_info("%s() start:\n",__FUNCTION__); 
	cfb_fillrect(p,rect);
	/* Virtual frame buffer to SDRAM */
	s1d13517fb_flush_virtual_framebuffer(0, NULL);
	dbg_info("%s() exit:\n",__FUNCTION__); 
}

/*****************************************************************************
*  [Function Name]	s1d13517fb_copyarea
*
*  [Description]	.
*
*  [Parameters]		p		: frame buffer structure pointer
*					area	: frame buffer copyarea structure pointer	
*
*  [Return]			none.
* 
*  [Note]
******************************************************************************/
void s1d13517fb_copyarea(struct fb_info *p, const struct fb_copyarea *area)
{
	dbg_info("%s() start:\n",__FUNCTION__); 
	cfb_copyarea(p,area);
	/* Virtual frame buffer to SDRAM */
	s1d13517fb_flush_virtual_framebuffer(0, NULL);
	dbg_info("%s() exit:\n",__FUNCTION__); 
}

/*****************************************************************************
*  [Function Name]	s1d13517fb_imageblit
*
*  [Description]	.
*
*  [Parameters]		p		: frame buffer structure pointer
*					image	: frame buffer image structure pointer	
*
*  [Return]			none.
* 
*  [Note]
******************************************************************************/
void s1d13517fb_imageblit(struct fb_info *p, const struct fb_image *image)
{       
	dbg_info("%s() start:\n",__FUNCTION__); 
	cfb_imageblit(p, image);
	/* Virtual frame buffer to SDRAM */
	s1d13517fb_flush_virtual_framebuffer(0, NULL);
	dbg_info("%s() exit:\n",__FUNCTION__); 
}

/*****************************************************************************
*  [Function Name]	s1d13517fb_set_info_addr
*
*  [Description]	.
*
*  [Parameters]		reg_addr	: chip register logical address
*					map_size	: chip register size	
*
*  [Return]			none.
* 
*  [Note]
******************************************************************************/
void s1d13517fb_set_info_addr(unsigned char *reg_addr, unsigned int map_size)
{       
	dbg_info("%s() start:\n",__FUNCTION__); 
	s1d13517fb_info.reg_addr 				= reg_addr;
    s1d13517fb_info.reg_addr_mapped_size 	= map_size;
	dbg_info("%s() exit:\n",__FUNCTION__); 
}

/*****************************************************************************
*  [Function Name]	s1d13517fb_exit
*
*  [Description]	Exit the chip and the frame buffer driver.
*
*  [Parameters]		none. 
*
*  [Return]			none.
* 
*  [Note]
******************************************************************************/
void __exit s1d13517fb_exit(void)
{
	dbg_info("%s() start:\n",__FUNCTION__); 
#ifdef CONFIG_FB_EPSON_PROC
	s1d13517proc_terminate();
#endif

	unregister_framebuffer(&s1d13517_fb); 
	s1d13517hw_terminate(&s1d13517fb_info);
	dbg_info("%s() exit:\n",__FUNCTION__); 
}

module_init(s1d13517fb_init);
module_exit(s1d13517fb_exit);

MODULE_AUTHOR("Epson Research and Development");
MODULE_DESCRIPTION("Framebuffer driver for Epson s1d13517 chip");
MODULE_LICENSE("GPL");


