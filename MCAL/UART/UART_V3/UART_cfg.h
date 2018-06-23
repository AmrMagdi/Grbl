/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V03								*/
/************************************************/


#ifndef	_UART_CFG_H
#define	_UART_CFG_H

typedef enum
{
	Data_Len_5=0,
	Data_Len_6,
	Data_Len_7,
	Data_Len_8,
	Data_Len_9
}DataLength_cfg;

typedef enum
{
	Parity_None=0,
	Parity_Even,
	Parity_Odd
}Parity_cfg;

typedef enum
{
	Stop_len_1=0,
	Stop_len_2
}StopLength_cfg;

typedef enum
{
	BR_115200=0
}BaudRate_cfg;

typedef struct
{
	DataLength_cfg  DataLength;
	Parity_cfg		Parity;
	StopLength_cfg	StopLength;
	BaudRate_cfg	BaudRate;
}UART_cfg;

typedef struct
{
	u8 UART_TxBufferLen;
	u8 UART_RxBufferLen;
}Buffer_cfg;

extern const UART_cfg UART_cfg_ARR[1];

extern const Buffer_cfg Buffer_cfgArr[1];


#endif
