

#ifndef	_PWM2_CFG_H
#define	_PWM2_CFG_H


typedef enum
{
	PWM_PHASE_CORRECT=0,
	PWM_FAST
}PWM2_Mode_cfg;

typedef enum
{
	DIV_PRESCAl_1=0,
	DIV_PRESCAl_8,
	DIV_PRESCAl_32,
	DIV_PRESCAl_64,
	DIV_PRESCAl_128,
	DIV_PRESCAl_256,
	DIV_PRESCAl_1024,
}CLOCK_cfg;

typedef enum
{
	TOGGLE_OC2A=0,
	NON_INVERT_OC2A,
	INVERT_OC2A
}ChannelA_Mode_cfg;

typedef enum
{
	NON_INVERT_OC2B=0,
	INVERT_OC2B
}ChannelB_Mode_cfg;

typedef struct
{
	CLOCK_cfg CLOCK;
	PWM2_Mode_cfg PWM2_Mode;
	ChannelA_Mode_cfg ChannelA_Mode;
	ChannelB_Mode_cfg ChannelB_Mode;
}PWM2_cfg;

extern const PWM2_cfg PWM2_cfgArr[1];




#endif