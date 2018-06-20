/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V01								*/
/************************************************/


#ifndef	_TIM0_H
#define	_TIM0_H

#include "TIM0_cfg.h"

extern void TIM0_voidInitialize(void);


/*normal mode */
extern void TIM0_voidEnable(void);
extern void TIM0_voidDisable(void);
extern void TIM0_voidSetTIM0Reg(u8 Copy_u8Reg);
extern void TIM0_voidSetCallBack(void (*Copy_PTR2Fn)(void));

/*channelA*/
extern void TIM0_voidEnableChannelA(void);
extern void TIM0_voidDisableChannelA(void);
extern void TIM0_voidSetCTCChAReg(u8 Copy_u8Reg);
extern void TIM0_voidSetCallBackCA(void (*Copy_PTR2Fn)(void));

/*channelB*/
extern void TIM0_voidEnableChannelB(void);
extern void TIM0_voidDisableChannelB(void);
extern void TIM0_voidSetCTCChBReg(u8 Copy_u8Reg);
extern void TIM0_voidSetCallBackCB(void (*Copy_PTR2Fn)(void));

#endif
