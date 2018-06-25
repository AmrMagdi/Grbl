/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V01								*/
/************************************************/

#ifndef	_TIM1_H
#define	_TIM1_H

#include "TIM1_cfg.h"
#include "std_types.h"

extern void TIM1_voidInitialize(void);

/* Configure */

extern void TIM1_voidSetPrescaler(TIM1_Clock_cfg clk);
extern void TIM1_voidSetMode(TIM1_Mode_cfg mode);

/*normal mode */
extern void TIM1_voidEnable(void);
extern void TIM1_voidDisable(void);
extern void TIM1_voidSetTIM1Reg(u16 Copy_u16Reg);
extern void TIM1_voidSetCallBack(void (*Copy_PTR2Fn)(void));


/*channelA*/
extern void TIM1_voidEnableChannelA(void);
extern void TIM1_voidDisableChannelA(void);
extern void TIM1_voidSetCTCChAReg(u16 Copy_u16Reg);
extern void TIM1_voidSetCallBackCA(void (*Copy_PTR2Fn)(void));

/*channelB*/
extern void TIM1_voidEnableChannelB(void);
extern void TIM1_voidDisableChannelB(void);
extern void TIM1_voidSetCTCChBReg(u16 Copy_u16Reg);
extern void TIM1_voidSetCallBackCB(void (*Copy_PTR2Fn)(void));

#endif
