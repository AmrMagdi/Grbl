/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V01								*/
/************************************************/

#include "STD_TYPES.h"
#include "GIE_reg.h"
#include "GIE.h"

void GIE_voidInitialize(void)
{
	
}

void GIE_voidEnable(void)
{
	SREG |=  (1<<I);
}

void GIE_voidDisable(void)
{
	SREG &= ~(1<<I);
}
