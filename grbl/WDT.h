/*****************************/
/* Author:  Amr Magdi        */
/* Date:    28/3/2018        */
/* Version: 1.0              */
/*****************************/
#ifndef _WDT_H
#define _WDT_H

#include "WDT_cfg.h"

typedef enum{
	Disabled=0,
	Enabled
}WDT_status_t;

extern void WDT_voidInitialize(void);
extern void WDT_voidDisable(void);
extern void WDT_voidEnable(void);
extern WDT_status_t WDT_u8GetStatus(void);
extern void WDT_voidSetCallBack( void (*Copy_ptr) (void) );


#endif
