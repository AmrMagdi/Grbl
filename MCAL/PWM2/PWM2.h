/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V01								*/
/************************************************/


#ifndef	_PWM2_H
#define	_PWM2_H

#include "PWM2_cfg.h"

extern void PWM2_voidInitialize(void);

extern void PWM2_voidEnableChA(void);
extern void PWM2_voidSetPWMChA(u8 Copy_u8PWMValue);
extern void PWM2_voidDisableChA(void);

extern void PWM2_voidEnableChB(void);
extern void PWM2_voidSetPWMChB(u8 Copy_u8PWMValue);
extern void PWM2_voidDisableChB(void);

#endif
