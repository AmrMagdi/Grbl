/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V03								*/
/************************************************/


#include "STD_TYPES.h"
#include "UART_cfg.h"

#ifndef RX_BUFFER_SIZE
  #define RX_BUFFER_SIZE 128
#endif

#ifndef TX_BUFFER_SIZE
  #ifdef USE_LINE_NUMBERS
    #define TX_BUFFER_SIZE 112
  #else
    #define TX_BUFFER_SIZE 104
  #endif
#endif



const UART_cfg UART_cfg_ARR[1]=
{
	{Data_Len_8,Parity_None,Stop_len_1,BR_115200}
};

const Buffer_cfg Buffer_cfgArr[1]=
{
	{TX_BUFFER_SIZE,RX_BUFFER_SIZE}
};
