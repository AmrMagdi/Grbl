/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V03								*/
/************************************************/

#ifndef _UART_REG_H
#define _UART_REG_H

#define UDR0 		*((volatile u8*) 0x0C6)

/**********************************************************************/
#define UCSR0A		*((volatile u8*) 0x0C0)
#define RXC0 		7
#define TXC0 		6
#define UDRE0 		5
#define FE0 		4
#define DOR0 		3
#define UPE0 		2
#define U2X0 		1
#define MPCM0		0

/**********************************************************************/
#define UCSR0B		*((volatile u8*) 0x0C1)
#define RXCIE0		7 
#define TXCIE0      6
#define UDRIE0      5
#define RXEN0       4
#define TXEN0       3
#define UCSZ02      2
#define RXB80       1
#define TXB80       0

/**********************************************************************/
#define UCSR0C		*((volatile u8*) 0x0C2)
#define UMSEL01		7
#define UMSEL00     6
#define UPM01       5
#define UPM00       4
#define USBS0       3
#define UCSZ01      2
#define UCSZ00      1
#define UCPOL0      0

/**********************************************************************/
#define UBRR0L		*((volatile u8*) 0x0C4)

#define UBRR0H		*((volatile u8*) 0x0C5)

#endif
