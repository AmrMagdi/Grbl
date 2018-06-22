/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V01								*/
/************************************************/

#ifndef	_TIM0_CFG_H
#define	_TIM0_CFG_H


typedef enum
{
	NORMAL=0,
	CTC
}TIM0_Mode_cfg;

typedef enum
{
	DIV_PRESCAl_1=0,
	DIV_PRESCAl_8,
	DIV_PRESCAl_64,
	DIV_PRESCAl_256,
	DIV_PRESCAl_1024,
}CLOCK_cfg;

typedef enum
{
	DIS_CONNECT_OC0A=0,
	TOGGLE_OC0A,
	CLEAR_OC0A,
	SET_OC0A
}ChannelA_Mode_cfg;

typedef enum
{
	DIS_CONNECT_OC0B=0,
	TOGGLE_OC0B,
	CLEAR_OC0B,
	SET_OC0B
}ChannelB_Mode_cfg;

typedef struct
{
	CLOCK_cfg CLOCK;
	TIM0_Mode_cfg TIM0_Mode;
	ChannelA_Mode_cfg ChannelA_Mode;
	ChannelB_Mode_cfg ChannelB_Mode;
}TIM0_cfg;

extern const TIM0_cfg TIM0_cfgArr[1];



#endif