/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V01								*/
/************************************************/

#include "STD_TYPES.h"
#include "UART_reg.h"
#include "UART.h"


#include "DIO.h"

void UART_voidInitialize(void)
{
	/*asynchronous*/
	UCSR0C &=  ~(1<<UMSEL00);
	UCSR0C &=  ~(1<<UMSEL01);
	
	/*single speed*/
	UCSR0A &= ~(1<<U2X0);
	
	/*baud rate*/
	switch(UART_cfg_ARR[0].BaudRate)
	{
		case BR_115200:
			UBRR0H=0;
			UBRR0L=8;
		break;
	}

	/*data length*/
	switch(UART_cfg_ARR[0].DataLength)
	{
		case Data_Len_5:
			UCSR0B  &= ~(1<<UCSZ02);
			UCSR0C	= ~(1<<UCSZ01);
			UCSR0C	&= ~(1<<UCSZ00);
		break;
		case Data_Len_6:
			UCSR0B  &= ~(1<<UCSZ02);
			UCSR0C	&= ~(1<<UCSZ01);
			UCSR0C	|=  (1<<UCSZ00);
		break;
		case Data_Len_7:
			UCSR0B  &= ~(1<<UCSZ02);
			UCSR0C	|=  (1<<UCSZ01);
			UCSR0C	&= ~(1<<UCSZ00);
		break;
		case Data_Len_8:
			UCSR0B  &= ~(1<<UCSZ02);
			UCSR0C	|=  (1<<UCSZ01);
			UCSR0C	|=  (1<<UCSZ00);
		break;
		case Data_Len_9:
			UCSR0B  |=  (1<<UCSZ02);
			UCSR0C	|=  (1<<UCSZ01);
			UCSR0C	|=  (1<<UCSZ00);
		break;
	}

	/*parity*/
	switch(UART_cfg_ARR[0].Parity)
	{
		case Parity_None:
			UCSR0C &= ~(1<<UPM01);
			UCSR0C &= ~(1<<UPM00);
		break;
		case Parity_Even:
			UCSR0C |=  (1<<UPM01);
			UCSR0C &= ~(1<<UPM00);
		break;
		case Parity_Odd:
			UCSR0C |=  (1<<UPM01);
			UCSR0C |=  (1<<UPM00);
		break;
	}

	/*stop bits*/
	switch(UART_cfg_ARR[0].StopLength)
	{
		case Stop_len_1:
			UCSR0C &= ~(1<<USBS0);
		break;
		case Stop_len_2:
			UCSR0C |=  (1<<USBS0);
		break;
	}
	


	/*enable UART*/
	UCSR0B |= (1<<RXEN0);
	UCSR0B |= (1<<TXEN0);
	
	/*enable interrupts*/
	UCSR0B |= (1<<RXCIE0);
}

typedef enum
{
	SENDING=0,
	OK
}State_Tx_cfg;

static boolean booleanTxState=OK;
static u8 u8TxBuffer[100];
static u16 u16TxBufferLoc=0;
static u16 u16TxBufferLen;

boolean UART_booleanTx(u8* Copy_u8Ptr2Data,u16 Copy_u16Length)
{
	if(booleanTxState==OK)
	{
		for(u16 u16Index=0;u16Index<Copy_u16Length;u16Index++)
		{
			u8TxBuffer[u16Index]=Copy_u8Ptr2Data[u16Index];
		}
		u16TxBufferLen=Copy_u16Length;
		UDR0=u8TxBuffer[u16TxBufferLoc];
		u16TxBufferLoc++;
		UCSR0B |= (1<<UDRIE0);
	}
	return booleanTxState;
}

typedef enum
{
	RECEIVING=0,
}State_Rx_cfg;

static boolean booleanRxState=OK;
static u8 *u8RxBuffer;
static u16 u16RxBufferLoc=0;
static u16 u16RxBufferLen;

boolean UART_booleanRx(u8* Copy_u8Ptr2Data,u16 Copy_u16Length)
{
	if(booleanRxState==OK)
	{
		u8RxBuffer=Copy_u8Ptr2Data;
		u16RxBufferLen=Copy_u16Length;
	}
	return booleanRxState;
}



/*RX ISR*/
void __vector_18(void) __attribute__((signal,used));
void __vector_18(void)
{
	u8RxBuffer[u16RxBufferLoc]=UDR0;
	u16RxBufferLoc++;
	if(u16RxBufferLoc==u16RxBufferLen)
	{
		booleanRxState=OK;
		u16RxBufferLoc=0;
	}
	else
	{
		booleanRxState=RECEIVING;
	}
}



/*UDR ISR*/
void __vector_19(void) __attribute__((signal,used));
void __vector_19(void)
{

	/*debugging*/
	//DIO_voidWritePin(PD2,u8TxBuffer[u16TxBufferLoc]);

	if(u16TxBufferLoc==u16TxBufferLen)
	{
		booleanTxState=OK;
		u16TxBufferLoc=0;
	}
	else
	{
		booleanTxState=SENDING;
		UDR0=u8TxBuffer[u16TxBufferLoc];
		u16TxBufferLoc++;
	}


}
