/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V01								*/
/************************************************/

#include "std_types.h"
#include "TIM1_reg.h"
#include "TIM1.h"

static void StundFn(void);
 void StundFn(void)
 {
	 
 }
extern void TIM1_voidSetPrescaler(TIM1_CLOCK_cfg clk){
	/*clock*/
		switch(clk)
		{
			case TIM1_DIV_PRESCAl_1:
				TCCR1B &= ~(1<<CS12);
				TCCR1B &= ~(1<<CS11);
				TCCR1B |=  (1<<CS10);
			break;
			case TIM1_DIV_PRESCAl_8:
				TCCR1B &= ~(1<<CS12);
				TCCR1B |=  (1<<CS11);
				TCCR1B &= ~(1<<CS10);
			break;
			case TIM1_DIV_PRESCAl_64:
				TCCR1B &= ~(1<<CS12);
				TCCR1B |=  (1<<CS11);
				TCCR1B |=  (1<<CS10);
			break;
			case TIM1_DIV_PRESCAl_256:
				TCCR1B |=  (1<<CS12);
				TCCR1B &= ~(1<<CS11);
				TCCR1B &= ~(1<<CS10);
			break;
			case TIM1_DIV_PRESCAl_1024:
				TCCR1B |=  (1<<CS12);
				TCCR1B &= ~(1<<CS11);
				TCCR1B |=  (1<<CS10);
			break;
		}
}
extern void TIM1_voidInitialize(void)
{
	/*force CMP*/
	TCCR1C &= ~(1<<FOC1A);
	TCCR1C &= ~(1<<FOC1B);
	
	/*timer mode */
	switch(TIM1_cfgArr[0].TIM1_Mode)
	{
		case TIM1_NORMAL:
			TCCR1B &= ~(1<<WGM13);
			TCCR1B &= ~(1<<WGM12);
			TCCR1A &= ~(1<<WGM11);
			TCCR1A &= ~(1<<WGM10);
		break;
		case TIM1_CTC:
			TCCR1B &= ~(1<<WGM13);
			TCCR1B |=  (1<<WGM12);
			TCCR1A &= ~(1<<WGM11);
			TCCR1A &= ~(1<<WGM10);
		break;
	}
	
	
	/*channelA mode and ChannelB mode*/
	if(TIM1_cfgArr[0].TIM1_Mode==TIM1_NORMAL)
	{
		TCCR1A &= ~(1<<COM1A1); 
		TCCR1A &= ~(1<<COM1A0);
		TCCR1A &= ~(1<<COM1B1); 
		TCCR1A &= ~(1<<COM1B0);
	}
	else if(TIM1_cfgArr[0].TIM1_Mode==TIM1_CTC)
	{
		switch(TIM1_cfgArr[0].TIM1_ChannelA_Mode)
		{
			case TIM1_DIS_CONNECT_OC1A:
				TCCR1A &= ~(1<<COM1A1); 
				TCCR1A &= ~(1<<COM1A0);
			break;
			case TIM1_TOGGLE_OC1A:
				TCCR1A &= ~(1<<COM1A1); 
				TCCR1A |=  (1<<COM1A0);
			break;
			case TIM1_CLEAR_OC1A:
				TCCR1A |=  (1<<COM1A1); 
				TCCR1A &= ~(1<<COM1A0);
			break;
			case TIM1_SET_OC1A:
				TCCR1A |=  (1<<COM1A1); 
				TCCR1A |=  (1<<COM1A0);
			break;
		}
		
		switch(TIM1_cfgArr[0].TIM1_ChannelB_Mode)
		{
			case TIM1_DIS_CONNECT_OC1B:
				TCCR1A &= ~(1<<COM1B1); 
				TCCR1A &= ~(1<<COM1B0);
			break;
			case TIM1_TOGGLE_OC1B:
				TCCR1A &= ~(1<<COM1B1); 
				TCCR1A |=  (1<<COM1B0);
			break;
			case TIM1_CLEAR_OC1B:
				TCCR1A |=  (1<<COM1B1); 
				TCCR1A &= ~(1<<COM1B0);
			break;
			case TIM1_SET_OC1B:
				TCCR1A |=  (1<<COM1B1); 
				TCCR1A |=  (1<<COM1B0);
			break;
		}
	}
	
	TIM1_voidSetCallBack(StundFn);
	TIM1_voidSetCallBackCA(StundFn);
	TIM1_voidSetCallBackCB(StundFn);
	
	
	/*disable all interrupts*/
	TIMSK1 &= ~(1<<TOIE1);
	TIMSK1 &= ~(1<<OCIE1A);
	TIMSK1 &= ~(1<<OCIE1B);
	
	/*clock*/
	switch(TIM1_cfgArr[0].TIM1_CLOCK)
	{
		case TIM1_DIV_PRESCAl_1:
			TCCR1B &= ~(1<<CS12); 
			TCCR1B &= ~(1<<CS11);  
			TCCR1B |=  (1<<CS10); 
		break;
		case TIM1_DIV_PRESCAl_8:
			TCCR1B &= ~(1<<CS12); 
			TCCR1B |=  (1<<CS11);  
			TCCR1B &= ~(1<<CS10);
		break;
		case TIM1_DIV_PRESCAl_64:
			TCCR1B &= ~(1<<CS12); 
			TCCR1B |=  (1<<CS11);  
			TCCR1B |=  (1<<CS10);
		break;
		case TIM1_DIV_PRESCAl_256:
			TCCR1B |=  (1<<CS12); 
			TCCR1B &= ~(1<<CS11);  
			TCCR1B &= ~(1<<CS10);
		break;
		case TIM1_DIV_PRESCAl_1024:
			TCCR1B |=  (1<<CS12); 
			TCCR1B &= ~(1<<CS11);  
			TCCR1B |=  (1<<CS10);
		break;
	}
}
/*********************************************************************/
/*normal mode */

static void (*CallBackFn) (void);

extern void TIM1_voidEnable(void)
{
	TIMSK1 |= (1<<TOIE1);
}

extern void TIM1_voidDisable(void)
{
	TIMSK1 &= ~(1<<TOIE1);
}

extern void TIM1_voidSetTIM1Reg(u16 Copy_u16Reg)
{
	TCNT1 = Copy_u16Reg;
}

extern void TIM1_voidSetCallBack(void (*Copy_PTR2Fn)(void))
{
	CallBackFn = Copy_PTR2Fn;
}

void __vector_13(void) __attribute__((signal,used));
void __vector_13(void)
{
	CallBackFn();
}

/******************************************************/
/*channelA*/

static void (*CallBackFnChA) (void);

extern void TIM1_voidEnableChannelA(void)
{
	TIMSK1 |= (1<<OCIE1A);
}

extern void TIM1_voidDisableChannelA(void)
{
	TIMSK1 &= ~(1<<OCIE1A);
}

extern void TIM1_voidSetCTCChAReg(u16 Copy_u16Reg)
{
	OCR1A = Copy_u16Reg;
}

extern void TIM1_voidSetCallBackCA(void (*Copy_PTR2Fn)(void))
{
	CallBackFnChA=Copy_PTR2Fn;
}

void __vector_11(void) __attribute__((signal,used));
void __vector_11(void)
{
	CallBackFnChA();
}

/********************************************************/
/*channelB*/

static void (*CallBackFnChB) (void);

extern void TIM1_voidEnableChannelB(void)
{
	TIMSK1 |= (1<<OCIE1B);
}
extern void TIM1_voidDisableChannelB(void)
{
	TIMSK1 &= ~(1<<OCIE1B);
}

extern void TIM1_voidSetCTCChBReg(u16 Copy_u16Reg)
{
	OCR1B = Copy_u16Reg;
}

extern void TIM1_voidSetCallBackCB(void (*Copy_PTR2Fn)(void))
{
	CallBackFnChB=Copy_PTR2Fn;
}

void __vector_12(void) __attribute__((signal,used));
void __vector_12(void)
{
	CallBackFnChB();
}
