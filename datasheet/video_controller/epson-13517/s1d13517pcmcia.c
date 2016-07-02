/******************************************************************************
 *
 *  File Name   : linux/drivers/video/epson-13517/s1d13517pcmcia.c
 *  Function    : Optional PCI specific code for frame buffer driver
 *              :                              for Epson S1D13517 controllers.
 *  History     : 2009.09.01    Created by LCDC Team.
 *-----------------------------------------------------------------------------
 * Copyright(C) SEIKO EPSON CORPORATION 2009. All rights reserved.
 * This file is licensed under the GPLv2
 ******************************************************************************/

#ifdef CONFIG_FB_EPSON_PCMCIA

/*****************************************************************************
 * include files (#include)
 */
#include <linux/version.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/fb.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>

#include <pcmcia/cs_types.h>
#include <pcmcia/cisreg.h>
#include <pcmcia/cistpl.h>
#include <pcmcia/device_id.h>
#include <pcmcia/ss.h>
#include <pcmcia/cs.h>
#include <pcmcia/ds.h>

#include "s1d13517fb.h"
#include "s1d13517.h"

/*****************************************************************************
 * define
 */
#define	TUPLE_BUF_SIZE			(64)		// tuple buffer size
#define	WIN_REQUEST_SIZE		(0x1000)	// 4096byte
#define	GET_ADDRESS_RETRY_MAX	(10)		// 10times
#define	GET_ADDRESS_SLEEP_TIME	(1000)		// 1000msec

/*****************************************************************************
 * debug define
 */

/*****************************************************************************
 * Function declare
 */
static int s1d13517pcmcia_probe (struct pcmcia_device *link);
static void s1d13517pcmcia_detach(struct pcmcia_device *link);

/*****************************************************************************
 * Global Variables
 */
/* PCMCIA device id			*/
static struct pcmcia_device_id s1d13517_ids[] = {
	PCMCIA_DEVICE_FUNC_ID(254),
	PCMCIA_DEVICE_PROD_ID12("EPSON R&D "," PCCARD Adapter ",
							0x65076f8d, 0x161f990a),
	PCMCIA_DEVICE_NULL
};
MODULE_DEVICE_TABLE(pcmcia, s1d13517_ids);

/* PCMCIA driver			*/
static struct pcmcia_driver s1d13517_pcmcia_driver = {
	.owner		= THIS_MODULE,
	.drv		= {
		.name	= "s1d13517_pcmcia"
	},
	.probe		= s1d13517pcmcia_probe,
	.remove		= s1d13517pcmcia_detach,
	.id_table	= s1d13517_ids,
};

/*****************************************************************************
*  [Function Name]	s1d13517pcmcia_probe
*
*  [Description]	PCMCIA device driver probe
*
*  [Parameters]		link	: PCMCIA device structure pointer
*
*  [Return]			0		: Successfully
*					<0		: get tuple data error
*					-ENOMEM	: ioremap failed
*					-EFAULT	: pcmcia driver register failed
*
*  [Note]
******************************************************************************/
static int s1d13517pcmcia_probe (struct pcmcia_device *link)
{
	int 			ret = 0;
	tuple_t 		tuple;
	cisparse_t 		parse;
	unsigned short 	buf[TUPLE_BUF_SIZE];
	win_req_t 		req;
	unsigned char	*regaddr;

	dbg_info("%s() start:\n",__FUNCTION__);

	tuple.Attributes = 0;
	tuple.TupleData = (cisdata_t *)buf;
	tuple.TupleDataMax = sizeof(buf);
	tuple.TupleOffset = 0;
	tuple.DesiredTuple = RETURN_FIRST_TUPLE;

	while (ret == 0) {
		ret = pcmcia_get_tuple_data(link, &tuple);

		if (ret != 0) {
			cs_error(link, GetTupleData, ret);
			printk(KERN_ERR "s1d13517pcmcia_probe(): "
							"pcmcia_get_tuple_data failed\n");
			goto exit_probe;
		}
		ret = pcmcia_get_next_tuple(link, &tuple);
	}

	/* memory settings */
	tuple.DesiredTuple = CISTPL_CFTABLE_ENTRY;

	ret = pcmcia_get_first_tuple(link, &tuple);
	if (ret != 0) {
		cs_error(link, GetFirstTuple, ret);
		printk(KERN_ERR "s1d13517pcmcia_probe(): "
						"pcmcia_get_first_tuple failed\n");
		goto exit_probe;
	}

	ret = pcmcia_get_tuple_data(link, &tuple);
	if (ret != 0) {
		cs_error(link, GetTupleData, ret);
		printk(KERN_ERR "s1d13517pcmcia_probe(): "
						"pcmcia_get_tuple_data failed\n");
		goto exit_probe;
	}

	ret = pcmcia_parse_tuple(&tuple, &parse);
	if (ret != 0) {
		cs_error(link, ParseTuple, ret);
		printk(KERN_ERR "s1d13517pcmcia_probe(): "
						"pcmcia_parse_tuple failed\n");
		goto exit_probe;
	}

	dbg_info("%s():cftable_entry.mem.nwin[%d]\n",__FUNCTION__,
			parse.cftable_entry.mem.nwin);
	if (parse.cftable_entry.mem.nwin > 0) {
		req.Attributes 	= WIN_DATA_WIDTH_16 | WIN_MEMORY_TYPE_CM
						| WIN_ENABLE;
		req.Base 		= 0;
		req.Size 		= WIN_REQUEST_SIZE;
		req.AccessSpeed = 0;
		link->win = (window_handle_t)link;

		ret = pcmcia_request_window(&link, &req, &link->win);
		if (ret != 0) {
			cs_error(link, RequestWindow, ret);
			printk(KERN_ERR "s1d13517pcmcia_probe(): "
							"pcmcia_request_window failed\n");
			goto exit_probe;
		}

		dbg_info("%s():req.Base[%x] req.Size[%x]\n",__FUNCTION__,
			(int)req.Base, req.Size);
		regaddr = (unsigned char *)ioremap_nocache(
								req.Base, S1D_MMAP_PHYSICAL_REG_SIZE);
		if (regaddr == NULL) {
			printk(KERN_ERR "s1d13517pcmcia_probe(): ioremap failed\n");
			ret = -ENOMEM;
			goto exit_probe;
		}

		s1d13517hw_set_reg_addr(regaddr);

		if (s1d13517fb_fb_registers()) {
			printk(KERN_ERR "s1d13517pcmcia_probe(): Could not register"
							"frame buffer with kernel.\n");
			ret = -EFAULT;
			goto exit_probe;
		}
	}
exit_probe:
	dbg_info("%s() exit:\n",__FUNCTION__);
	return ret;
}

/*****************************************************************************
*  [Function Name]	s1d13517pcmcia_detach
*
*  [Description]	PCMCIA device driver detach	
*
*  [Parameters]		link	: PCMCIA device structure pointer
*
*  [Return]			none.
*
*  [Note]
******************************************************************************/
static void s1d13517pcmcia_detach(struct pcmcia_device *link)
{
	dbg_info("%s() start:\n",__FUNCTION__);
	if (link->win) {
		pcmcia_release_window(link->win);
	}
	dbg_info("%s() exit:\n",__FUNCTION__);
}

/*****************************************************************************
*  [Function Name]	s1d13517pcmcia_init
*
*  [Description]	PCMCIA device driver initialize   	
*
*  [Parameters]		none.
*
*  [Return]			0		: Successfully
*					!0		: pcmcia_register_driver failed
*
*  [Note]
******************************************************************************/
int  __devinit s1d13517pcmcia_init(void)
{
	int ret = 0;

	dbg_info("%s() start:\n",__FUNCTION__);

	ret = pcmcia_register_driver(&s1d13517_pcmcia_driver);
	if (ret != 0)
	{
		printk(KERN_ERR "s1d13517pcmcia_init: Failed to "
						"register PCMCIA device\n");
		return ret;
	}
	dbg_info("%s() exit:\n",__FUNCTION__);
	return ret;
}


/*****************************************************************************
*  [Function Name] s1d13517pcmcia_terminate
*
*  [Description]	PCMCIA device driver terminate   	
*
*  [Parameters]		none.
*
*  [Return]			none.
*
*  [Note]
******************************************************************************/
void __devexit s1d13517pcmcia_terminate(void)
{
	dbg_info("%s() start:\n",__FUNCTION__);
	pcmcia_unregister_driver(&s1d13517_pcmcia_driver);
	dbg_info("%s() exit:\n",__FUNCTION__);
}

#endif


