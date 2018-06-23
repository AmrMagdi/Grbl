/*****************************/
/* Author:  Amr Magdi        */
/* Date:    18/6/2018        */
/* Version: 1.0              */
/*****************************/
#ifndef _WDT_REG_H
#define _WDT_REG_H


/* Registers			*/

#define MCUSR		*((volatile u8*) 0x54)
#define WDTCSR		*((volatile u8*) 0x60)

/*MCUSR Register Bit names			*/
#define WDRF		3

/*WDTCSR Register Bit names			*/
#define WDP0		0	
#define WDP1		1
#define WDP2		2
#define WDE			3
#define WDCE		4
#define WDP3		5
#define WDIE		6
#define WDIF		7


#endif
