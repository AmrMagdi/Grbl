/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V01								*/
/************************************************/

#ifndef	_UART_H_
#define _UART_H_

#include "UART_cfg.h"

extern void UART_voidInitialize(void);


/*transmission using interrupt */
extern boolean UART_booleanTx(u8* Copy_u8Ptr2Data,u16 Copy_u16Length);

/*receiving using interrupt */
extern boolean UART_booleanRx(u8* Copy_u8Ptr2Data,u16 Copy_u16Length);

#endif