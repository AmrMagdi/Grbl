/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V01								*/
/************************************************/

#ifndef	_TIM1_CFG_H
#define	_TIM1_CFG_H


typedef enum
{
	TIM1_NORMAL=0,
	TIM1_CTC
}TIM1_Mode_cfg;

typedef enum
{
	TIM1_DIV_PRESCAl_1=0,
	TIM1_DIV_PRESCAl_8,
	TIM1_DIV_PRESCAl_64,
	TIM1_DIV_PRESCAl_256,
	TIM1_DIV_PRESCAl_1024,
}TIM1_CLOCK_cfg;

typedef enum
{
	TIM1_DIS_CONNECT_OC1A=0,
	TIM1_TOGGLE_OC1A,
	TIM1_CLEAR_OC1A,
	TIM1_SET_OC1A
}TIM1_ChannelA_Mode_cfg;

typedef enum
{
	TIM1_DIS_CONNECT_OC1B=0,
	TIM1_TOGGLE_OC1B,
	TIM1_CLEAR_OC1B,
	TIM1_SET_OC1B
}TIM1_ChannelB_Mode_cfg;

typedef struct
{
	TIM1_CLOCK_cfg TIM1_CLOCK;
	TIM1_Mode_cfg TIM1_Mode;
	TIM1_ChannelA_Mode_cfg TIM1_ChannelA_Mode;
	TIM1_ChannelB_Mode_cfg TIM1_ChannelB_Mode;
}TIM1_cfg;

extern const TIM1_cfg TIM1_cfgArr[1];


#endif
