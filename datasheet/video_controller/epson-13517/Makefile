#
# Makefile for the Epson s1d13517 framebuffer device drivers
#

obj-$(CONFIG_FB_EPSON_S1D13517)	+= s1d13517fb.o
s1d13517fb-objs			+= s1d13517if.o 

ifdef CONFIG_FB_EPSON_PROC
s1d13517fb-objs			+= s1d13517proc.o
endif

ifdef CONFIG_FB_EPSON_PCMCIA
s1d13517fb-objs			+= s1d13517pcmcia.o
endif

s1d13517fb-objs			+= s1d13517hw.o



