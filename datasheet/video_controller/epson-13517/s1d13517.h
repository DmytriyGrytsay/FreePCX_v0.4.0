/******************************************************************************
 *
 *  File Name   : linux/drivers/video/epson-13517/s1d13517.h
 *  Function    : Register initialize data for Epson S1D13517 LCD controller.
 *  History     : 2009.09.01    Created by LCDC Project Team.
 *-----------------------------------------------------------------------------
 * Copyright(C) SEIKO EPSON CORPORATION 2009. All rights reserved.
 * This file is licensed under the GPLv2
 ******************************************************************************/
#ifndef __S1D13517_H__
#define __S1D13517_H__

#include "s1d13517registers.h"

#define S1D_13517
#define S1D_IMAGE_16BPP					16
#define S1D_IMAGE_24BPP					24
#define S1D_IMAGE_32BPP					32
#define S1D_DISPLAY_WIDTH               640
#define S1D_DISPLAY_HEIGHT              480
#define S1D_DISPLAY_BPP                 S1D_IMAGE_24BPP
#define S1D_DISPLAY_SCANLINE_BYTES      1600
#define S1D_DISPLAY_FRAME_RATE          0
#define S1D_DISPLAY_PCLK                10000000L
#define S1D_DISPLAY_VNDP				4
#define S1D_DISPLAY_HDISP				((S1D_DISPLAY_WIDTH/8)-1)
#define S1D_DISPLAY_VDISP				(S1D_DISPLAY_HEIGHT-1)
#define S1D_DISPLAY_HNDP				((10/2)-1)	
#define S1D_DISPLAY_HSWIDTH				1
#define S1D_DISPLAY_HSSTART				0
#define S1D_DISPLAY_VSWIDTH				1
#define S1D_DISPLAY_VSSTART				0
#define S1D_SYSCLK                      50000000L
#define S1D_PHYSICAL_REG_ADDR			0x00000000L
#define S1D_SDRAM_START_ADDR			0x00000000L
#define S1D_PHYSICAL_REG_SIZE           0x5010
#define S1D_REGRESERVED                 0xF0
#define S1D_REGDELAYPLL                 0xFC
#define S1D_REGDELAYOFF                 0xFD
#define S1D_REGDELAY					0xFE

#define	S1D_LINE_LENGTH					(S1D_DISPLAY_WIDTH*S1D_DISPLAY_BPP/8)
#define	S1D_SCREEN_SIZE					(S1D_DISPLAY_HEIGHT*S1D_LINE_LENGTH)
#define S1D_MMAP_PHYSICAL_REG_SIZE  	0x06

typedef unsigned char S1D_INDEX;
typedef unsigned char S1D_VALUE;

typedef struct
{
    S1D_INDEX index;
    S1D_VALUE value;
} S1D_REGS;


#define S1D_INSTANTIATE_REGISTERS(scope_prefix,variable_name)  \
  scope_prefix S1D_REGS variable_name[] =  \
  {  \
	{ REG04_PLLDDIV				,0x17 }, \
	{ REG06_PLLSET0				,0x51 }, \
	{ REG08_PLLSET1				,0x01 }, \
	{ REG0C_PLLNDIV				,0x59 }, \
	{ REG12_CLKSRCSEL			,0x01 }, \
	{ REG04_PLLDDIV				,0x97 }, \
	{ REG0E_SSCTRL0				,0xBF }, \
	{ S1D_REGDELAY				,0x0A }, \
	{ REG12_CLKSRCSEL			,0x81 }, \
	{ REG68_POWERSAVE			,0x01 }, \
	{ REG14_PANELTYPE			,0x00 }, \
	{ REG16_HDISP				,S1D_DISPLAY_HDISP }, \
	{ REG18_HNDP				,S1D_DISPLAY_HNDP }, \
	{ REG1A_VDISP0				,(S1D_DISPLAY_VDISP&0xff) }, \
	{ REG1C_VDISP1				,(S1D_DISPLAY_VDISP>>8) }, \
	{ REG1E_VNDP				,(S1D_DISPLAY_VNDP/2) }, \
	{ REG20_HSW					,(S1D_DISPLAY_HSWIDTH-1) }, \
	{ REG22_HPS					,S1D_DISPLAY_HSSTART }, \
	{ REG24_VSW					,(S1D_DISPLAY_VSWIDTH-1) }, \
	{ REG26_VPS					,S1D_DISPLAY_VSSTART }, \
	{ REG28_PCLKPOL				,0x00 }, \
	{ REG2A_DISPMODE			,0x00 }, \
	{ REG2C_PIP1SADDR0			,0x00 }, \
	{ REG2E_PIP1SADDR1			,0x00 }, \
	{ REG30_PIP1SADDR2			,0x00 }, \
	{ REG32_PIP1XSPOS			,0x00 }, \
	{ REG34_PIP1YSPOS0			,0x00 }, \
	{ REG36_PIP1YSPOS1			,0x00 }, \
	{ REG38_PIP1XEPOS			,0x00 }, \
	{ REG3A_PIP1YEPOS0			,0x00 }, \
	{ REG3C_PIP1YEPOS1			,0x00 }, \
	{ REG3E_PIP2SADDR0			,0x00 }, \
	{ REG40_PIP2SADDR1			,0x00 }, \
	{ REG42_PIP2SADDR2			,0x00 }, \
	{ REG44_PIP2XSPOS			,0x00 }, \
	{ REG46_PIP2YSPOS0			,0x00 }, \
	{ REG48_PIP2YSPOS1			,0x00 }, \
	{ REG4A_PIP2XEPOS			,0x00 }, \
	{ REG4C_PIP2YEPOS0			,0x00 }, \
	{ REG4E_PIP2YEPOS1			,0x00 }, \
	{ REG52_INPUTMODE			,0x00 }, \
	{ REG54_KEYCOLORR			,0x00 }, \
	{ REG56_KEYCOLORG			,0x00 }, \
	{ REG58_KEYCOLORB			,0x00 }, \
	{ REG5A_WRXSPOS				,0x00 }, \
	{ REG5C_WRYSPOS0			,0x00 }, \
	{ REG5E_WRYSPOS1			,0x00 }, \
	{ REG60_WRXEPOS				,0x78 }, \
	{ REG62_WRYEPOS0			,0xA0 }, \
	{ REG64_WRYEPOS1			,0x00 }, \
	{ REG6A_NDPSTS				,0x00 }, \
	{ REG6C_GPIO0				,0x00 }, \
	{ REG6E_GPIO1				,0x00 }, \
	{ REG70_PWMCTRL				,0x00 }, \
	{ REG72_PWMHDUTY0			,0x00 }, \
	{ REG74_PWMHDUTY1			,0x00 }, \
	{ REG76_PWMHDUTY2			,0x00 }, \
	{ REG78_PWMHDUTY3			,0x00 }, \
	{ REG7A_PWMLDUTY0			,0x00 }, \
	{ REG7C_PWMLDUTY1			,0x00 }, \
	{ REG7E_PWMLDUTY2			,0x00 }, \
	{ REG80_PWMLDUTY3			,0x00 }, \
	{ REG94_ABLENDCTRL			,0x00 }, \
	{ REG98_ABLENDHSIZE			,0x00 }, \
	{ REG9A_ABLENDVSIZE0		,0x00 }, \
	{ REG9C_ABLENDVSIZE1		,0x00 }, \
	{ REG9E_ABLENDVALUE			,0x00 }, \
	{ REGA0_ABLENDIN1SADDR0		,0x00 }, \
	{ REGA2_ABLENDIN1SADDR1		,0x00 }, \
	{ REGA4_ABLENDIN1SADDR2		,0x00 }, \
	{ REGA6_ABLENDIN2SADDR0		,0x00 }, \
	{ REGA8_ABLENDIN2SADDR1		,0x00 }, \
	{ REGAA_ABLENDIN2SADDR2		,0x00 }, \
	{ REGAC_ABLENDOUTSADDR0		,0x00 }, \
	{ REGAE_ABLENDOUTSADDR1		,0x00 }, \
	{ REGB0_ABLENDOUTSADDR2		,0x00 }, \
	{ REG82_RAMCTRL				,0x03 }, \
	{ REG88_RAMMRSVAL0			,0x22 }, \
	{ REG8C_RAMREFERRSHCOUNT0	,0x90 }, \
	{ REG8E_RAMREFERRSHCOUNT1	,0x01 }, \
	{ REG90_RAMWRBUFMEMSIZE		,0x40 }, \
	{ REG92_RAMDEBUG			,0x00 }, \
	{ REG68_POWERSAVE			,0xE8 }, \
	{ REG68_POWERSAVE			,0x00 }, \
	{ REG68_POWERSAVE			,0x01 }, \
	{ REG84_RAMSTS0				,0x82 } \
  }

#endif	//  __S1D13517_H__
