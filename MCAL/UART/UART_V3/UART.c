/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V03								*/
/************************************************/
#include "STD_TYPES.h"
#include "UART_reg.h"
#include "UART.h"



/*flags to checks if user sets the callback functions or not*/
static boolean TxFlagISR=0;
static boolean RxFlagISR=0;
static boolean ResetCondFlag=0;


/*this function is used as stundard callback function*/
/*it is use to avoid crashing because user doesn't setting */
/*callback fn */
static void voidStundFn(void);
void voidStundFn(void)
{

}


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
	

	/*set call back standard condition if user didn't set set*/
	if(ResetCondFlag==0)
	{
		UART_voidSetResetCondFn(voidStundFn);
	}
	
	/*set call back default Tx ISR if user didn't set set*/
	if(TxFlagISR==0)
	{
		UART_voidSetCallBackTx(UART_voidDefaultTxISR);
	}
	
	/*set call back default Tx ISR if user didn't set set*/
	if(RxFlagISR==0)
	{
		UART_voidSetCallBackRx(UART_voidDefaultRxISR);
	}

	/*enable UART*/
	UCSR0B |= (1<<RXEN0);
	UCSR0B |= (1<<TXEN0);
	
	/*enable interrupts*/
	UCSR0B |= (1<<RXCIE0);
}


static void (*SetRetCond)(void);
void UART_voidSetResetCondFn(void (*Copy_Ptr2Fn)(void))
{
	ResetCondFlag=1;
	SetRetCond = Copy_Ptr2Fn;
}

/******************************************************************/
u8 u8BufferTx[255];

/*head is used to set elements in buffer*/
u8 u8BufferTxHead = 0;

/*tail is used to fetch elements from buffer*/
volatile u8 u8BufferTxTail = 0;

void UART_voidTx(u8 Copy_u8Data)
{

	u8 Local_u8NextHead = u8BufferTxHead+1;
	/*to start from first location of buffer (head != tail)*/
	if(Local_u8NextHead==Buffer_cfgArr[0].UART_TxBufferLen)
	{
		Local_u8NextHead=0;
	}
	
	/*if there is no space in buffer*/
	while(Local_u8NextHead == u8BufferTxTail)
	{
		/*breaking conditon*/
		SetRetCond();
	}
	
	/*set the data in buffer*/
	u8BufferTx[u8BufferTxHead]=Copy_u8Data;
	
	/* set the head*/
	u8BufferTxHead = Local_u8NextHead;

	/* Enable Data Register Empty Interrupt */
	UCSR0B |=  (1 << UDRIE0);
}

u8 UART_u8GetNumTxBufferAvailable(void)
{
	u8 Local_u8RetVal;
	u8 Local_u8BufferTxTail = u8BufferTxTail;
	if(u8BufferTxHead >= Local_u8BufferTxTail)
	{
		Local_u8RetVal = u8BufferTxHead - Local_u8BufferTxTail;
	}
	else
	{
		Local_u8RetVal = Buffer_cfgArr[0].UART_TxBufferLen - (Local_u8BufferTxTail - u8BufferTxHead);
	}
	return Local_u8RetVal;
}

/*this fuction is used to set call back */
/*it may be as default or by user*/
static void (*CallBackTx)(void);
void UART_voidSetCallBackTx(void (*Copy_PTR2Fn)(void))
{
	TxFlagISR=1;
	CallBackTx = Copy_PTR2Fn;
}


/*this is a default TX_ISR			*/
/*user can override it				*/
void UART_voidDefaultTxISR(void)
{
	/*for optimization */
	/*u8BufferTxTail is volatile so all operations will be without optimization*/
	u8 Local_u8BufferTxTail = u8BufferTxTail;
	
	/*set data register with element from tx buffer*/
	UDR0 = u8BufferTx[Local_u8BufferTxTail];
	
	/* Update tail position*/
	Local_u8BufferTxTail++;
	if(Local_u8BufferTxTail == Buffer_cfgArr[0].UART_TxBufferLen)
	{
		/*if next place expected in buffer is out of range */
		Local_u8BufferTxTail=0;
	}
	u8BufferTxTail = Local_u8BufferTxTail;
	
	/*if tail == head (no elements to be transmitted)--> disable transmittion  */
	if(Local_u8BufferTxTail == u8BufferTxHead)
	{
		UCSR0B &= ~(1 << UDRIE0);
	}
}

/*UDR ISR*/
void __vector_19(void) __attribute__((signal,used));
void __vector_19(void)
{
	CallBackTx();
}

/*********************************************************************/
u8 u8BufferRx[255];

/*head is used to set elements in buffer*/
u8 u8BufferRxHead = 0;

/*tail is used to fetch elements from buffer*/
volatile u8 u8BufferRxTail = 0;


u8 UART_u8Rx(void)
{
	u8 Local_u8RetVal;
	u8 Local_u8BufferRxTail = u8BufferRxTail;
	if(u8BufferRxHead == Local_u8BufferRxTail)
	{
		/*no data in buffer*/
		Local_u8RetVal = BUFFER_NO_DATA;
	}
	else
	{
		/*fetch the data from buffer*/
		Local_u8RetVal = u8BufferRx[Local_u8BufferRxTail];
		
		if(Local_u8BufferRxTail==Buffer_cfgArr[0].UART_RxBufferLen-1)
		{
			/*if no place in buffer and tail != head , start from begining(ring)*/
			Local_u8BufferRxTail=0;
		}
		else
		{
			/*jump to the next available place in buffer*/
			Local_u8BufferRxTail++;
		}
		u8BufferRxTail = Local_u8BufferRxTail;
	}
	return Local_u8RetVal;
}


/*clear rx buffer*/
void UART_voidClearRxBuffer(void)
{
	u8BufferRxTail=u8BufferRxHead;
}



u8 UART_u8GetNumRxBufferFree(void)
{
	u8 Local_u8RetVal;
	u8 Local_u8BufferRxTail = u8BufferRxTail;
	if(u8BufferRxHead >= Local_u8BufferRxTail)
	{
		Local_u8RetVal = Buffer_cfgArr[0].UART_RxBufferLen - (u8BufferRxHead - Local_u8BufferRxTail);
	}
	else
	{
		Local_u8RetVal = Local_u8BufferRxTail - u8BufferRxHead-1;
	}
	return Local_u8RetVal;
}



u8 UART_u8GetNumRxBufferAvailable(void)
{
	u8 Local_u8RetVal;
	u8 Local_u8BufferRxTail = u8BufferRxTail;
	if(u8BufferRxHead >= Local_u8BufferRxTail)
	{
		Local_u8RetVal = u8BufferRxHead - Local_u8BufferRxTail;
	}
	else
	{
		Local_u8RetVal = Buffer_cfgArr[0].UART_RxBufferLen - (Local_u8BufferRxTail - u8BufferRxHead);
	}
	return Local_u8RetVal;
}


static void (*CallBackRx)(void);

/*static variable contains updated value of data register*/
static u8 RxDataISR;

void UART_voidDefaultRxISR(void)
{

	u8 Local_u8NextHead = u8BufferRxHead + 1;
	if (Local_u8NextHead == Buffer_cfgArr[0].UART_RxBufferLen) 
	{ 
		Local_u8NextHead = 0; 
	}
	
	// Write data to buffer unless it is full.
	if (Local_u8NextHead != u8BufferRxTail) 
	{
		u8BufferRx[u8BufferRxHead] = RxDataISR;
		u8BufferRxHead = Local_u8NextHead;
	}
	
}

/*used to read data register by passing pointer from higher layer*/
void UART_voidGetDataReg(u8* Copy_PTR2DataReg)
{
	*Copy_PTR2DataReg = RxDataISR;
}

void UART_voidSetCallBackRx(void (*Copy_PTR2Fn)(void))
{
	RxFlagISR=1;
	CallBackRx=Copy_PTR2Fn;
}


/*RX ISR*/
void __vector_18(void) __attribute__((signal,used));
void __vector_18(void)
{
	RxDataISR = UDR0;

	CallBackRx();
}
