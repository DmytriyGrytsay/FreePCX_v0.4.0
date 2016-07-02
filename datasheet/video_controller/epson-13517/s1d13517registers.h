/******************************************************************************
 *
 *  File Name   : linux/drivers/video/epson-13517/s1d13517registers.h
 *  Function    : Register definitions for Epson S1D13517 LCD controller.
 *  History     : 2009.09.01    Created by LCDC Project Team.
 *-----------------------------------------------------------------------------
 * Copyright(C) SEIKO EPSON CORPORATION 2009. All rights reserved.
 * This file is licensed under the GPLv2
 ******************************************************************************/
#ifndef __S1D13517REGISTERS_H__
#define __S1D13517REGISTERS_H__

// LCDC Register Mapping
#define REG_LCD_BASE				0x00
#define REG00_PRODINFO				0x00
#define REG02_CFGREADBACK			0x02
#define REG04_PLLDDIV				0x04
#define REG06_PLLSET0				0x06
#define REG08_PLLSET1				0x08
#define REG0A_PLLSET2				0x0A
#define REG0C_PLLNDIV				0x0C
#define REG0E_SSCTRL0				0x0E
#define REG10_SSCTRL1				0x10
#define REG12_CLKSRCSEL				0x12
#define REG14_PANELTYPE				0x14
#define REG16_HDISP					0x16
#define REG18_HNDP					0x18
#define REG1A_VDISP0				0x1A
#define REG1C_VDISP1				0x1C
#define REG1E_VNDP					0x1E
#define REG20_HSW					0x20
#define REG22_HPS					0x22
#define REG24_VSW					0x24
#define REG26_VPS					0x26
#define REG28_PCLKPOL				0x28
#define REG2A_DISPMODE				0x2A
#define REG2C_PIP1SADDR0			0x2C
#define REG2E_PIP1SADDR1			0x2E
#define REG30_PIP1SADDR2			0x30
#define REG32_PIP1XSPOS				0x32
#define REG34_PIP1YSPOS0			0x34
#define REG36_PIP1YSPOS1			0x36
#define REG38_PIP1XEPOS				0x38
#define REG3A_PIP1YEPOS0			0x3A
#define REG3C_PIP1YEPOS1			0x3C
#define REG3E_PIP2SADDR0			0x3E
#define REG40_PIP2SADDR1			0x40
#define REG42_PIP2SADDR2			0x42
#define REG44_PIP2XSPOS				0x44
#define REG46_PIP2YSPOS0			0x46
#define REG48_PIP2YSPOS1			0x48
#define REG4A_PIP2XEPOS				0x4A
#define REG4C_PIP2YEPOS0			0x4C
#define REG4E_PIP2YEPOS1			0x4E
#define REG50_DISPCTRL				0x50
#define REG52_INPUTMODE				0x52
#define REG54_KEYCOLORR				0x54
#define REG56_KEYCOLORG				0x56
#define REG58_KEYCOLORB				0x58
#define REG5A_WRXSPOS				0x5A
#define REG5C_WRYSPOS0				0x5C
#define REG5E_WRYSPOS1				0x5E
#define REG60_WRXEPOS				0x60
#define REG62_WRYEPOS0				0x62
#define REG64_WRYEPOS1				0x64
#define REG66_MEMORYPORT0			0x66
#define REG67_MEMORYPORT1			0x67
#define REG68_POWERSAVE				0x68
#define REG6A_NDPSTS				0x6A
#define REG6C_GPIO0					0x6C
#define REG6E_GPIO1					0x6E
#define REG70_PWMCTRL				0x70
#define REG72_PWMHDUTY0				0x72
#define REG74_PWMHDUTY1				0x74
#define REG76_PWMHDUTY2				0x76
#define REG78_PWMHDUTY3				0x78
#define REG7A_PWMLDUTY0				0x7A
#define REG7C_PWMLDUTY1				0x7C
#define REG7E_PWMLDUTY2				0x7E
#define REG80_PWMLDUTY3				0x80
#define REG82_RAMCTRL				0x82
#define REG84_RAMSTS0				0x84
#define REG86_RAMSTS1				0x86
#define REG88_RAMMRSVAL0			0x88
#define REG8A_RAMMRSVAL1			0x8A
#define REG8C_RAMREFERRSHCOUNT0		0x8C
#define REG8E_RAMREFERRSHCOUNT1		0x8E
#define REG90_RAMWRBUFMEMSIZE		0x90
#define REG92_RAMDEBUG				0x92
#define REG94_ABLENDCTRL			0x94
#define REG96_ABLENDSTS				0x96
#define REG98_ABLENDHSIZE			0x98
#define REG9A_ABLENDVSIZE0			0x9A
#define REG9C_ABLENDVSIZE1			0x9C
#define REG9E_ABLENDVALUE			0x9E
#define REGA0_ABLENDIN1SADDR0		0xA0
#define REGA2_ABLENDIN1SADDR1		0xA2
#define REGA4_ABLENDIN1SADDR2		0xA4
#define REGA6_ABLENDIN2SADDR0		0xA6
#define REGA8_ABLENDIN2SADDR1		0xA8
#define REGAA_ABLENDIN2SADDR2		0xAA
#define REGAC_ABLENDOUTSADDR0		0xAC
#define REGAE_ABLENDOUTSADDR1		0xAE
#define REGB0_ABLENDOUTSADDR2		0xB0
#define REGB2_INTRCTRL				0xB2
#define REGB4_INTRSTS				0xB4
#define REGB6_INTRCLEAR				0xB6
#define REGFLAG_ENDOFTABLE			0xFF	// End of register table flag.

/* REG2A_DISPMODE bit define	*/
#define DISPLAY_ON					0x01

/* REG96_ABLENDSTS bit define	*/
#define ABLEND_STATUS_BIT			0x01

/* REG6A_NDPSTS bit define		*/
#define VNDP_STATUS_BIT				0x80

/* REG14_PANELTYPE bit define 	*/
#define LCD_DATA_TYPE_BIT			0x06
#define LCD_DATA_TYPE_24BPP			0x00
#define LCD_DATA_TYPE_32BPP			0x02
#define LCD_DATA_TYPE_16BPP			0x04

/* REG1C_VDISP1 bit define 	*/
#define LCD_VDISP1_BIT				0x03
#define LCD_VDISP1_OFFSET			0x100

/* REG52_INPUTMODE bit define 	*/
enum s1d13517_buf_num {
	LCD_WRITE_BUF1				= 0,
	LCD_WRITE_BUF2				,
	LCD_WRITE_BUF3				,
	LCD_WRITE_BUF4				,
	LCD_WRITE_BUF5				,
	LCD_WRITE_BUF6				,
	LCD_WRITE_BUF7				,
	LCD_WRITE_BUF8				,
	LCD_WRITE_BUF9				,
	LCD_WRITE_BUF10				,
	LCD_WRITE_BUF11				,
	LCD_WRITE_BUF12				,
	LCD_WRITE_BUF13				,
	LCD_WRITE_BUF14				,
	LCD_WRITE_BUF15				,
	LCD_WRITE_BUF16
};
#define LCD_WRITE_BUF_MAX			LCD_WRITE_BUF16 + 1
#define LCD_WRITE_BUF_SHIFT_LEFT	4
#define LCD_WRITE_BUF_MASK			0xf0

/* s1d13517if_ModifyReg8 bit define 	*/
#define MR_NOT_CLR					0x00


#endif // __S1D13517REGISTERS_H__
