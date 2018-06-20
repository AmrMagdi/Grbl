/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V02								*/
/************************************************/

#ifndef	_PWM2_CFG_H
#define	_PWM2_CFG_H


typedef enum
{
	PWM2_PWM_PHASE_CORRECT=0,
	PWM2_PWM_FAST
}PWM2_Mode_cfg;

typedef enum
{
	PWM2_DIV_PRESCAl_1=0,
	PWM2_DIV_PRESCAl_8,
	PWM2_DIV_PRESCAl_32,
	PWM2_DIV_PRESCAl_64,
	PWM2_DIV_PRESCAl_128,
	PWM2_DIV_PRESCAl_256,
	PWM2_DIV_PRESCAl_1024,
}PWM2_CLOCK_cfg;

typedef enum
{
	PWM2_TOGGLE_OC2A=0,
	PWM2_NON_INVERT_OC2A,
	PWM2_INVERT_OC2A
}PWM2_ChannelA_Mode_cfg;

typedef enum
{
	PWM2_NON_INVERT_OC2B=0,
	PWM2_INVERT_OC2B
}PWM2_ChannelB_Mode_cfg;

typedef struct
{
	PWM2_CLOCK_cfg PWM2_CLOCK;
	PWM2_Mode_cfg PWM2_Mode;
	PWM2_ChannelA_Mode_cfg PWM2_ChannelA_Mode;
	PWM2_ChannelB_Mode_cfg PWM2_ChannelB_Mode;
}PWM2_cfg;

extern const PWM2_cfg PWM2_cfgArr[1];




#endif
