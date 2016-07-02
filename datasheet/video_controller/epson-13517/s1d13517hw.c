/******************************************************************************
 *
 *  File Name   : linux/drivers/video/epson-13517/s1d13517hw.c
 *  Function    : Frame buffer driver for Epson S1D13517 LCD controller.
 *  History     : 2009.09.01    Created by LCDC Project Team.
 *-----------------------------------------------------------------------------
 * Copyright(C) SEIKO EPSON CORPORATION 2009. All rights reserved.
 * This file is licensed under the GPLv2
 ******************************************************************************/

/*****************************************************************************
 * include files (#include)
 */
#include <linux/mm.h>
#include <linux/delay.h>
#include <linux/unistd.h>

#include "s1d13517fb.h"
#include "s1d13517.h"
#include "s1d13517registers.h"
#include "s1d13517ioctl.h"

/*****************************************************************************
 * local define
 */

/*****************************************************************************
 * Function declare
 */
static int s1d13517hw_check_input_rect(u8 *p_buf_num, u8 *p_byte_per_pixel,
							  		 	const struct s1d13517_rect *p_rect);
static void s1d13517hw_write_window_position(const u8 uc_buf_num, 
										const struct s1d13517_rect *p_rect);
static void s1d13517hw_burst_write_mem_port16(const u16* p_data, 
										u32 un_copy_size16);

/*****************************************************************************
 * Global Variables
 */
static volatile u16 *gp_indirect_index;	// HCL indirect index register
static volatile u16 *gp_indirect_data;	// HCL indirect data register
static spinlock_t spinlock_hw;

/*****************************************************************************
*  [Function Name]	s1d13517hw_init
*
*  [Description]	Hhardware interface initialize.
*
*  [Parameters]		info	: S1D13517 furame buffer info structure pointer
*
*  [Return]			0		: Successfully
*					-EINVAL	: pcmcia device initialize error
*							  ioremap error
*
*  [Note]
******************************************************************************/
int s1d13517hw_init(void)
{
	dbg_info("%s() start:\n",__FUNCTION__);

#ifdef CONFIG_FB_EPSON_PCMCIA
	if (s1d13517pcmcia_init() != 0)
	{
		printk(KERN_ERR "s1d13517hw_init: PCMCIA init failed\n"); 
		return -EINVAL;
	}
#else
	u8 *reg_addr = (u8*)ioremap_nocache(
						S1D_PHYSICAL_REG_ADDR,S1D_MMAP_PHYSICAL_REG_SIZE);
	if (reg_addr == NULL)
	{
		return -EINVAL; 
	}
	dbg_info("%s(): RegAddr 0x%p\n", __FUNCTION__, reg_addr);

	s1d13517hw_set_reg_addr(reg_addr);
#endif
	spin_lock_init(&spinlock_hw);
	dbg_info("%s() exit:\n",__FUNCTION__);
	return 0;
}

/*****************************************************************************
*  [Function Name]	s1d13517hw_set_reg_addr
*
*  [Description]	Set chip register global address.
*
*  [Parameters]		reg_addr	: LCDC chip register logical address 
*
*  [Return]			none.
*
*  [Note]
******************************************************************************/
void s1d13517hw_set_reg_addr(u8 *reg_addr)
{
	dbg_info("%s() start:\n",__FUNCTION__);
	gp_indirect_index  = (u16 *)(reg_addr + 0); // index OFFSET 0
    gp_indirect_data   = (u16 *)(reg_addr + 4); // data OFFSET 4

	dbg_info("%s():gp_indirect_index=0x%p gp_indirect_data=0x%p\n",
			__FUNCTION__, gp_indirect_index, gp_indirect_data);
	s1d13517fb_set_info_addr(reg_addr, S1D_MMAP_PHYSICAL_REG_SIZE); 
	dbg_info("%s() exit:\n",__FUNCTION__);
}

/*****************************************************************************
*  [Function Name]	s1d13517hw_terminate
*
*  [Description]	Hardware interface terminate.
*
*  [Parameters]		info	: S1D13517 furame buffer info structure pointer
*
*  [Return]			none.
*
*  [Note]
******************************************************************************/
void s1d13517hw_terminate(FB_INFO_S1D13517 *info)
{
	dbg_info("%s() start:\n",__FUNCTION__);

#ifdef CONFIG_FB_EPSON_PCMCIA
	s1d13517pcmcia_terminate();
#endif
	dbg_info("%s() exit:\n",__FUNCTION__);
}

/*****************************************************************************
*  [Function Name]	s1d13517hw_read_reg8
*
*  [Description]	LCDC chip register read.
*
*  [Parameters]		index	: LCDC register offset address
*
*  [Return]			value	: Register value
*
*  [Note]
******************************************************************************/
u8 s1d13517hw_read_reg8(u8 index)
{
	u16 value;
	unsigned long flags;

	spin_lock_irqsave(&spinlock_hw,flags);
	*gp_indirect_index = (u16)index;
	value = *gp_indirect_data;
	spin_unlock_irqrestore(&spinlock_hw,flags);
	return value;
}

/*****************************************************************************
*  [Function Name]	s1d13517hw_write_reg8
*
*  [Description]	LCDC chip regster write.
*
*  [Parameters]		index	: LCDC register offset address
*					value	: write data
*
*  [Return]			none.
*
*  [Note]
******************************************************************************/
void s1d13517hw_write_reg8(u8 index, u8 value)
{
	unsigned long flags;

	spin_lock_irqsave(&spinlock_hw,flags);
	*gp_indirect_index = (u16)index;
	*gp_indirect_data  = (u16)value;
	spin_unlock_irqrestore(&spinlock_hw,flags);
}

/*****************************************************************************
*  [Function Name]	s1d13517hw_modify_reg8
*
*  [Description]	PCMCIA hardware interface terminate.
*
*  [Parameters]		index		: LCDC register offset address
*					clear_bits	: value for clear bits
*					set_bits	: value for set bits
*
*  [Return]			value		: write value
*
*  [Note]
******************************************************************************/
u8 s1d13517hw_modify_reg8(u8 index, u8 clear_bits, u8 set_bits)
{
	u16 value;
	unsigned long flags;

	spin_lock_irqsave(&spinlock_hw,flags);
	*gp_indirect_index = (u16)index;
	value = *gp_indirect_data;
	value = ((value & ~clear_bits) | set_bits);
	*gp_indirect_index = index;
	*gp_indirect_data = value;
	spin_unlock_irqrestore(&spinlock_hw,flags);
	return value;
}

/*****************************************************************************
*  [Function Name]	s1d13517hw_check_input_rect
*
*  [Description]	LCDC chip regster write.
*
*  [Parameters]		*p_buf_num	: Write buffer number
*					*p_byte_per_pixel	: Byte per pixel
*					p_rect		: rectangle structure pointer
*
*  [Return]			0			: Successfully
*					-EFAULT		: Invalid parameter
*
*  [Note]
******************************************************************************/
static int s1d13517hw_check_input_rect(u8 *p_buf_num, u8 *p_byte_per_pixel,
							  		 const struct s1d13517_rect *p_rect)
{
	u32		un_display_width	= 0;
	u32		un_display_height	= 0;
	u8		un_data_type		= 0;

	dbg_info("%s() start:\n",__FUNCTION__);

	/* Get panel type			*/ 
	un_data_type  = s1d13517hw_read_reg8(REG14_PANELTYPE) & LCD_DATA_TYPE_BIT;	
	dbg_info("%s() un_data_type=%d:\n",__FUNCTION__, un_data_type);
	/* Set byte per pixel count	*/
	switch (un_data_type)
	{
		case LCD_DATA_TYPE_24BPP:
			*p_byte_per_pixel = S1D_IMAGE_24BPP/8;
			break;
		case LCD_DATA_TYPE_32BPP:
			*p_byte_per_pixel = S1D_IMAGE_32BPP/8;
			break;
		default:
			*p_byte_per_pixel = S1D_IMAGE_16BPP/8;
			break;
	}

	/* Get display width		*/
	un_display_width   = (s1d13517hw_read_reg8(REG16_HDISP) + 1) * 8;	
	/* Get display height		*/
	un_display_height  = s1d13517hw_read_reg8(REG1A_VDISP0) + 1;	
	un_display_height += (s1d13517hw_read_reg8(REG1C_VDISP1) & LCD_VDISP1_BIT) 
						* LCD_VDISP1_OFFSET;	

	dbg_info("%s(): bpp=%d dips_width=%d disp_height=%d\n", __FUNCTION__,
			 *p_byte_per_pixel, un_display_width, un_display_height);
	if (s1d13517hw_read_reg8(REG90_RAMWRBUFMEMSIZE) == 0) 
	{
		*p_buf_num = 0;
	}	
	/* Check buffer number		*/
	if (*p_buf_num >= LCD_WRITE_BUF_MAX)
	{
		printk(KERN_ERR "%s: Buffer number exceeded MAX buffer number.\n", 
				 __FUNCTION__); 
		return -EFAULT;
	}
	/* Check xstart is a multiple of eight.		*/
	if ((p_rect->xstart % 8) != 0) 
	{
		printk(KERN_ERR "%s: Xstart is not a multiple of eight.\n", 
				__FUNCTION__); 
		return -EFAULT;
	}
	/* Check xend is a unit of 8pixel.			*/
	if ((p_rect->xend % 8) != 7) 
	{
		printk(KERN_ERR "%s: Xend is not a unit of 8pixel.\n", __FUNCTION__); 
		return -EFAULT;
	}
	/* Check xstart is arger than Xend.			*/
	if (p_rect->xstart > p_rect->xend) 
	{
		printk(KERN_ERR "%s: Xstart is larger than Xend. \n", __FUNCTION__); 
		return -EFAULT;
	}
	/* Check ystart is larger than Yend.		*/
	if (p_rect->ystart > p_rect->yend) 
	{
		printk(KERN_ERR "%s: Ystart is larger than Yend. \n", __FUNCTION__); 
		return -EFAULT;
	}
	/* Check xstart	is larger than display width.	*/
	if (p_rect->xstart >= un_display_width) 
	{
		printk(KERN_ERR "%s: Xstart is larger than display width.\n", 
				__FUNCTION__); 
		return -EFAULT;
	}
	/* Check xend is larger than display width.		*/
	if (p_rect->xend >= un_display_width) 
	{
		printk(KERN_ERR "%s: Xend is larger than display width.\n", 
				__FUNCTION__); 
		return -EFAULT;
	}
	/* Check ystart is larger than display height.	*/
	if (p_rect->ystart >= un_display_height) 
	{
		printk(KERN_ERR "%s: Ystart is larger than display height.\n", 
				__FUNCTION__); 
		return -EFAULT;
	}
	/* Check yend is larger than display height.	*/
	if (p_rect->yend >= un_display_height) 
	{
		printk(KERN_ERR "%s: Yend is larger than display height.\n", 
				__FUNCTION__); 
		return -EFAULT;
	}
	dbg_info("%s() exit:\n",__FUNCTION__);
	return 0;
}

/*****************************************************************************
*  [Function Name]	s1d13517hw_write_window_position
*
*  [Description]	Write Window Position register write.
*
*  [Parameters]		uc_buf_num	: Write buffer number
*					p_rect		: irectangle structure pointer
*
*  [Return]			none.
*
*  [Note]
******************************************************************************/
static void s1d13517hw_write_window_position(const u8 uc_buf_num, 
										   const struct s1d13517_rect *p_rect)
{
	unsigned long flags;

	dbg_info("%s() start:\n",__FUNCTION__);

	s1d13517hw_modify_reg8(REG52_INPUTMODE, LCD_WRITE_BUF_MASK,
						   uc_buf_num << LCD_WRITE_BUF_SHIFT_LEFT);
	spin_lock_irqsave(&spinlock_hw,flags);
	*gp_indirect_index = (u16)REG5A_WRXSPOS;
	*gp_indirect_data  = (u16)((p_rect->xstart/8)<<1);
	*gp_indirect_data  = (u16)(p_rect->ystart>>2);
	*gp_indirect_data  = (u16)(p_rect->ystart & LCD_VDISP1_BIT);
	*gp_indirect_data  = (u16)(((p_rect->xend-7)/8)<<1);
	*gp_indirect_data  = (u16)(p_rect->yend>>2);
	*gp_indirect_data  = (u16)(p_rect->yend & LCD_VDISP1_BIT);
	spin_unlock_irqrestore(&spinlock_hw,flags);
	dbg_info("REG52=0x%02x REG5A=0x%02x REG5C=0x%02x REG5E=0x%02x "
			"REG60=0x%02x REG62=0x%02x REG64=0x%02x\n", 
			uc_buf_num << LCD_WRITE_BUF_SHIFT_LEFT,
			(p_rect->xstart/8)<<1, p_rect->ystart>>2, 
			p_rect->ystart & LCD_VDISP1_BIT,
			((p_rect->xend-7)/8)<<1, p_rect->yend>>2, 
			p_rect->yend & LCD_VDISP1_BIT);
	dbg_info("%s() exit:\n",__FUNCTION__);
}

/*****************************************************************************
*  [Function Name]	s1d13517hw_rect_write_memory16
*
*  [Description]	Rect angle write to memory(sdram).
*
*  [Parameters]		p_data		: write data pointer(source)
*					un_buf_num	: write buffer number
*					p_rect		: rectangle structure pointer
*
*  [Return]			0			: Successfuly
*					-EFAULT		: Input parameter error 
*
*  [Note]
******************************************************************************/
int s1d13517hw_rect_write_memory16(const u16* p_data, const u32 un_buf_num,
								   const struct s1d13517_rect *p_rect)
{
	u8		uc_buf_num 			= (u8)un_buf_num;
	u8		uc_byte_per_pixel	= 0;
	u32		un_copy_size16		= 0;

	dbg_info("%s() start:\n",__FUNCTION__);
	dbg_info("%s():(%d, %d) - (%d, %d)\n", __FUNCTION__,
		p_rect->xstart, p_rect->ystart, p_rect->xend, p_rect->yend);

	/* Chaeck input rect parameters.	*/
	if (s1d13517hw_check_input_rect(&uc_buf_num, &uc_byte_per_pixel, p_rect))
	{
		return -EFAULT;
	}
	/* calcurate copy size(16bit-size)	*/
	un_copy_size16 = ((p_rect->xend - p_rect->xstart + 1) * uc_byte_per_pixel *
				   (p_rect->yend - p_rect->ystart + 1))/sizeof(short);
	/* Set write window position register.	*/
	s1d13517hw_write_window_position(uc_buf_num, p_rect);
	/* Write to memory data port(burst)	*/
	s1d13517hw_burst_write_mem_port16(p_data, un_copy_size16);

	dbg_info("%s(): buf_num=%d copysize=%d)\n", __FUNCTION__,
			uc_buf_num, un_copy_size16);
	dbg_info("%s() exit:\n",__FUNCTION__);
	return 0;
}

/*****************************************************************************
*  [Function Name]	s1d13517hw_burst_write_mem_port16
*
*  [Description]	Burst memory write.
*
*  [Parameters]		p_data			: write data pointer
*					un_copy_size16	: write data count
*
*  [Return]			none.
*
*  [Note]
******************************************************************************/
static void s1d13517hw_burst_write_mem_port16(const u16* p_data, 
										   u32 un_copy_size16)
{
	unsigned long flags;

	if (un_copy_size16 && p_data)
	{
		spin_lock_irqsave(&spinlock_hw,flags);
		*gp_indirect_index = REG66_MEMORYPORT0;
		while (un_copy_size16--)
		{
			*gp_indirect_data = swab16(*p_data++);
		}
		spin_unlock_irqrestore(&spinlock_hw,flags);
	}
}
