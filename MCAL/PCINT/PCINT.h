
/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V01								*/
/************************************************/

#ifndef _PCINT_H
#define _PCINT_H

#include "PCINT_cfg.h"

extern void PCINT_voidInitialize(void);

extern void PCINT_voidEnablePCINT0(void);
extern void PCINT_voidDisablePCINT0(void);
extern void PCINT_voidSetCallPCINT0(void (*Copy_PTR2Fn)(void));

extern void PCINT_voidEnablePCINT1(void);
extern void PCINT_voidDisablePCINT1(void);
extern void PCINT_voidSetCallPCINT1(void (*Copy_PTR2Fn)(void));

extern void PCINT_voidEnablePCINT2(void);
extern void PCINT_voidDisablePCINT2(void);
extern void PCINT_voidSetCallPCINT2(void (*Copy_PTR2Fn)(void));


#endif
