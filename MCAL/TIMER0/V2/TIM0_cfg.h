/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V02								*/
/************************************************/

#ifndef	_TIM0_CFG_H
#define	_TIM0_CFG_H

typedef enum
{
	TIM0_NORMAL=0,
	TIM0_CTC
}TIM0_Mode_cfg;

typedef enum
{
	TIM0_DIV_PRESCAl_1=0,
	TIM0_DIV_PRESCAl_8,
	TIM0_DIV_PRESCAl_64,
	TIM0_DIV_PRESCAl_256,
	TIM0_DIV_PRESCAl_1024,
}TIM0_CLOCK_cfg;

typedef enum
{
	TIM0_DIS_CONNECT_OC0A=0,
	TIM0_TOGGLE_OC0A,
	TIM0_CLEAR_OC0A,
	TIM0_SET_OC0A
}TIM0_ChannelA_Mode_cfg;

typedef enum
{
	TIM0_DIS_CONNECT_OC0B=0,
	TIM0_TOGGLE_OC0B,
	TIM0_CLEAR_OC0B,
	TIM0_SET_OC0B
}TIM0_ChannelB_Mode_cfg;

typedef struct
{
	TIM0_CLOCK_cfg TIM0_CLOCK;
	TIM0_Mode_cfg TIM0_Mode;
	TIM0_ChannelA_Mode_cfg TIM0_ChannelA_Mode;
	TIM0_ChannelB_Mode_cfg TIM0_ChannelB_Mode;
}TIM0_cfg;

extern const TIM0_cfg TIM0_cfgArr[1];



#endif
