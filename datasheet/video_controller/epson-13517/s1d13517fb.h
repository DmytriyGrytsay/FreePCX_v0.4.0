/******************************************************************************
 *
 *  File Name   : linux/drivers/video/epson-13517/s1d13517fb.h
 *  Function    : Function header for Epson S1D13517 LCD controller.
 *  History     : 2009.09.01    Created by LCDC Project Team.
 *-----------------------------------------------------------------------------
 * Copyright(C) SEIKO EPSON CORPORATION 2009. All rights reserved.
 * This file is licensed under the GPLv2
 ******************************************************************************/
#ifndef __S1D13517FB_H__
#define __S1D13517FB_H__

#include <linux/kernel.h>
#include <linux/pci.h>
#include <linux/fb.h>
#include "s1d13517registers.h"
#include "s1d13517ioctl.h"

#ifndef FALSE
  #define FALSE (0)
#endif

#ifndef TRUE
  #define TRUE  (!FALSE)
#endif
#define S1D13517_PALETTE_MAX	(16)

// In Indirect Mode, a copy of the framebuffer is kept in system memory.
// A timer periodically writes this copy to the "real" framebuffer in
// hardware. This copy is called a virtual framebuffer.
#if !defined(CONFIG_FB_EPSON_INTERFACE_DIRECT)
        #define EPSON_VIRTUAL_FRAMEBUFFER
#endif

//----------------------------------------------------------------------------
// Structures used by s1d13517fb modules
//----------------------------------------------------------------------------
typedef struct
{
        u8 			*framebuffer_addr;
        volatile u8 *reg_addr; 
        unsigned 	reg_addr_mapped_size;
#ifdef CONFIG_FB_EPSON_PCMCIA
        u32 		phys_addr;
#endif
        u32 		pseudo_palette[S1D13517_PALETTE_MAX];
}FB_INFO_S1D13517;

extern struct 	fb_fix_screeninfo s1d13517fb_fix;
extern struct 	fb_info s1d13517_fb;
extern 			FB_INFO_S1D13517 s1d13517fb_info;
extern char 	*s1d13517fb_version;

//-----------------------------------------------------------------------------
// Global Function Prototypes
//-----------------------------------------------------------------------------

#ifdef CONFIG_FB_EPSON_DEBUG_PRINTK
#define dbg_info(fmt, args...) do { printk(KERN_INFO fmt, ## args); } while (0)
#else 
#define dbg_info(fmt, args...) do { } while (0)
#endif

#ifdef CONFIG_FB_EPSON_DEBUG_PRINTK
#define assert(expr) \
	if(!(expr)) { \
		printk( "Assertion failed! %s,%s,%s,line=%d\n",\
		#expr,__FILE__,__FUNCTION__,__LINE__); \
		BUG(); \
	}
#else
#define assert(expr)
#endif

int 	s1d13517fb_fb_registers(void);
void 	s1d13517fb_set_info_addr(unsigned char *reg_addr, unsigned int map_size);
void	s1d13517fb_lcdc_init(void);
int  __devinit s1d13517hw_init(void);
void __devexit s1d13517hw_terminate(FB_INFO_S1D13517 *info);
u8		s1d13517hw_read_reg8(u8 index);
void	s1d13517hw_write_reg8(u8 index, u8 value);

u8		s1d13517hw_modify_reg8(u8 index, u8 clear_bits, u8 set_bits);
int 	s1d13517hw_rect_write_memory16(const u16* p_data, const u32 un_buf_num,
								const struct s1d13517_rect *p_rect);
void 	s1d13517hw_set_reg_addr(u8 *reg_addr);

#ifdef CONFIG_FB_EPSON_PROC
int  __devinit s1d13517proc_init(void);
void __devexit s1d13517proc_terminate(void);
#endif

#ifdef CONFIG_FB_EPSON_PCMCIA
int  __devinit s1d13517pcmcia_init(void);
void __devexit s1d13517pcmcia_terminate(void);
#endif

#ifdef EPSON_VIRTUAL_FRAMEBUFFER
int s1d13517fb_flush_virtual_framebuffer(const int buf_num,
										 struct s1d13517_rect *p_rect);
#endif

#endif  //__S1D13517FB_H__
