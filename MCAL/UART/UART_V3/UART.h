/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V03								*/
/************************************************/

#ifndef	_UART_H_
#define _UART_H_

#include "UART_cfg.h"

#define BUFFER_NO_DATA 0xff

//serial_init
extern void UART_voidInitialize(void);

/*set reinitialize condition fn*/
/*this function is used to break any uncoditional loop inUART driver*/
/*mainly here used to break loop of no place in Tx buffer*/
extern void UART_voidSetResetCondFn(void (*Copy_Ptr2Fn)(void));

//serial_write
/*used to write new element in tx buffer*/
extern void UART_voidTx(u8 Copy_u8Data);

/* used ti fetch element from buffer*/
//serial_read
extern u8 UART_u8Rx(void);

/*clear rx buffer*/
//serial_reset_read_buffer
extern void UART_voidClearRxBuffer(void);

/* Returns the number of bytes available in the RX buffer*/
//serial_get_rx_buffer_available
extern u8 UART_u8GetNumRxBufferFree(void);

/* Returns the number of bytes used in the Rx buffer*/
// NOTE: Deprecated. Not used unless classic status reports are enabled in config.h.
//serial_get_rx_buffer_count
extern u8 UART_u8GetNumRxBufferAvailable(void);

// Returns the number of bytes used in the TX serial buffer*/
// NOTE: Not used except for debugging and ensuring no TX bottlenecks.
//serial_get_tx_buffer_count
extern u8 UART_u8GetNumTxBufferAvailable(void);


/*set callback fn for Tx */
extern void UART_voidDefaultTxISR(void);
extern void UART_voidSetCallBackTx(void (*Copy_PTR2Fn)(void));

/*set callback fn for Rx */
extern void UART_voidDefaultRxISR(void);
extern void UART_voidSetCallBackRx(void (*Copy_PTR2Fn)(void));

/*get data reg direct without using buffer for real time*/
extern void UART_voidGetDataReg(u8* Copt_PTR2DataReg);



#endif
