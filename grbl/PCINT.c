
/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V01								*/
/************************************************/

#include "std_types.h"
#include "PCINT_reg.h"
#include "PCINT.h"


#include "DIO.h"

#define GET_VAL_MASK 0x01
#define CLEAR_MASK	 0x00

typedef enum
{
	PCMSK_0=0,
	PCMSK_1,
	PCMSK_2
};

static void voidStund(void);
void voidStund(void)
{

}

extern void PCINT_voidInitialize(void)
{
	for( u8 u8Index=0;u8Index<25;u8Index++)
	{
		u8 u8Reg =  u8Index/ 8;
		u8 u8Bit =  u8Index % 8;
		switch(u8Reg)
		{
			case PCMSK_0:
				switch(PCINT_cfgArr[u8Index].PCINTState)
				{
					case OFF:
						PCMSK0 &= ~(1<<u8Bit);
					break;
					case ON:
						PCMSK0 |=  (1<<u8Bit);
					break;
				}
			break;
			case PCMSK_1:
				switch(PCINT_cfgArr[u8Index].PCINTState)
				{
					case OFF:
						PCMSK1 &= ~(1<<u8Bit);
					break;
					case ON:
						PCMSK1 |=  (1<<u8Bit);
					break;
				}
			break;
			case PCMSK_2:
				switch(PCINT_cfgArr[u8Index].PCINTState)
				{
					case OFF:
						PCMSK2 &= ~(1<<u8Bit);
					break;
					case ON:
						PCMSK2 |=  (1<<u8Bit);
					break;
				}
			break;
		}
	}
	PCINT_voidSetCallPCINT0(voidStund);
	PCINT_voidSetCallPCINT1(voidStund);
	PCINT_voidSetCallPCINT2(voidStund);
}

/*****************************************************/
static void (*voidSetCallBackPCINT0) (void);

extern void PCINT_voidEnablePCINT0(void)
{
	PCICR |=  (1<<PCIE0);
}

extern void PCINT_voidDisablePCINT0(void)
{
	PCICR &= ~(1<<PCIE0);
}

extern void PCINT_voidSetCallPCINT0(void (*Copy_PTR2Fn)(void))
{
	voidSetCallBackPCINT0 = Copy_PTR2Fn;
}

void __vector_3(void) __attribute__((signal,used));
void __vector_3(void)
{
	voidSetCallBackPCINT0();
}

/*****************************************************/
static void (*voidSetCallBackPCINT1) (void);

extern void PCINT_voidEnablePCINT1(void)
{
	PCICR |=  (1<<PCIE1);
}

extern void PCINT_voidDisablePCINT1(void)
{
	PCICR &= ~(1<<PCIE1);
}

extern void PCINT_voidSetCallPCINT1(void (*Copy_PTR2Fn)(void))
{
	voidSetCallBackPCINT1 = Copy_PTR2Fn;
}

void __vector_4(void) __attribute__((signal,used));
void __vector_4(void)
{
	voidSetCallBackPCINT1();
}

/*****************************************************/
static void (*voidSetCallBackPCINT2) (void);

extern void PCINT_voidEnablePCINT2(void)
{
	PCICR |=  (1<<PCIE2);
}

extern void PCINT_voidDisablePCINT2(void)
{
	PCICR &= ~(1<<PCIE2);
}

extern void PCINT_voidSetCallPCINT2(void (*Copy_PTR2Fn)(void))
{
	voidSetCallBackPCINT2 = Copy_PTR2Fn;
}

void __vector_5(void) __attribute__((signal,used));
void __vector_5(void)
{
	voidSetCallBackPCINT2();
}
