/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V02								*/
/************************************************/

#include "std_types.h"
#include "TIM0_reg.h"
#include "TIM0.h"

static void StundFn(void);
 void StundFn(void)
 {
	 
 }

void TIM0_voidInitialize(void)
{
	/*force CMP*/
	TCCR0B &= ~(1<<FOC0A);
	TCCR0B &= ~(1<<FOC0B);
	
	/*timer mode */
	switch(TIM0_cfgArr[0].TIM0_Mode)
	{
		case TIM0_NORMAL:
			TCCR0B &= ~(1<<WGM02);
			TCCR0A &= ~(1<<WGM01);
			TCCR0A &= ~(1<<WGM00);
		break;
		case TIM0_CTC:
			TCCR0B &= ~(1<<WGM02);
			TCCR0A |=  (1<<WGM01);
			TCCR0A &= ~(1<<WGM00);
		break;
	}
	
	
	/*channelA mode and ChannelB mode*/
	if(TIM0_cfgArr[0].TIM0_Mode==TIM0_NORMAL)
	{
		TCCR0A &= ~(1<<COM0A1); 
		TCCR0A &= ~(1<<COM0A0);
		TCCR0A &= ~(1<<COM0B1); 
		TCCR0A &= ~(1<<COM0B0);
	}
	else if(TIM0_cfgArr[0].TIM0_Mode==TIM0_CTC)
	{
		switch(TIM0_cfgArr[0].TIM0_ChannelA_Mode)
		{
			case TIM0_DIS_CONNECT_OC0A:
				TCCR0A &= ~(1<<COM0A1); 
				TCCR0A &= ~(1<<COM0A0);
			break;
			case TIM0_TOGGLE_OC0A:
				TCCR0A &= ~(1<<COM0A1); 
				TCCR0A |=  (1<<COM0A0);
			break;
			case TIM0_CLEAR_OC0A:
				TCCR0A |=  (1<<COM0A1); 
				TCCR0A &= ~(1<<COM0A0);
			break;
			case TIM0_SET_OC0A:
				TCCR0A |=  (1<<COM0A1); 
				TCCR0A |=  (1<<COM0A0);
			break;
		}
		
		switch(TIM0_cfgArr[0].TIM0_ChannelB_Mode)
		{
			case TIM0_DIS_CONNECT_OC0B:
				TCCR0A &= ~(1<<COM0B1); 
				TCCR0A &= ~(1<<COM0B0);
			break;
			case TIM0_TOGGLE_OC0B:
				TCCR0A &= ~(1<<COM0B1); 
				TCCR0A |=  (1<<COM0B0);
			break;
			case TIM0_CLEAR_OC0B:
				TCCR0A |=  (1<<COM0B1); 
				TCCR0A &= ~(1<<COM0B0);
			break;
			case TIM0_SET_OC0B:
				TCCR0A |=  (1<<COM0B1); 
				TCCR0A |=  (1<<COM0B0);
			break;
		}
	}
	

	TIM0_voidSetCallBack(StundFn);
	TIM0_voidSetCallBackCA(StundFn);
	TIM0_voidSetCallBackCB(StundFn);

	/*disable all interrupts*/
	TIMSK0 &= ~(1<<TOIE0);
	TIMSK0 &= ~(1<<OCIE0A);
	TIMSK0 &= ~(1<<OCIE0B);
	
	/*clock*/
	switch(TIM0_cfgArr[0].TIM0_CLOCK)
	{
		case TIM0_DIV_PRESCAL_1:
			TCCR0B &= ~(1<<CS02); 
			TCCR0B &= ~(1<<CS01);  
			TCCR0B |=  (1<<CS00); 
		break;
		case TIM0_DIV_PRESCAL_8:
			TCCR0B &= ~(1<<CS02); 
			TCCR0B |=  (1<<CS01);  
			TCCR0B &= ~(1<<CS00);
		break;
		case TIM0_DIV_PRESCAL_64:
			TCCR0B &= ~(1<<CS02); 
			TCCR0B |=  (1<<CS01);  
			TCCR0B |=  (1<<CS00);
		break;
		case TIM0_DIV_PRESCAL_256:
			TCCR0B |=  (1<<CS02); 
			TCCR0B &= ~(1<<CS01);  
			TCCR0B &= ~(1<<CS00);
		break;
		case TIM0_DIV_PRESCAL_1024:
			TCCR0B |=  (1<<CS02); 
			TCCR0B &= ~(1<<CS01);  
			TCCR0B |=  (1<<CS00);
		break;
	}
}

/*********************************************************************/
/* Configure Prescale */
void TIM0_voidSetPrescaler(TIM0_Clock_cfg clk)
{
	/*clock*/
		switch(clk)
		{
		case TIM0_DISCONNECT:
			TCCR0B &= ~(1<<CS02);
			TCCR0B &= ~(1<<CS01);
			TCCR0B &= ~(1<<CS00);
		break;
		case TIM0_DIV_PRESCAL_1:
			TCCR0B &= ~(1<<CS02);
			TCCR0B &= ~(1<<CS01);
			TCCR0B |=  (1<<CS00);
		break;
		case TIM0_DIV_PRESCAL_8:
			TCCR0B &= ~(1<<CS02);
			TCCR0B |=  (1<<CS01);
			TCCR0B &= ~(1<<CS00);
		break;
		case TIM0_DIV_PRESCAL_64:
			TCCR0B &= ~(1<<CS02);
			TCCR0B |=  (1<<CS01);
			TCCR0B |=  (1<<CS00);
		break;
		case TIM0_DIV_PRESCAL_256:
			TCCR0B |=  (1<<CS02);
			TCCR0B &= ~(1<<CS01);
			TCCR0B &= ~(1<<CS00);
		break;
		case TIM0_DIV_PRESCAL_1024:
			TCCR0B |=  (1<<CS02);
			TCCR0B &= ~(1<<CS01);
			TCCR0B |=  (1<<CS00);
		break;
		}
}

/*********************************************************************/
/* Configure Mode */
void TIM0_voidSetMode(TIM0_Mode_cfg mode)
{
	switch(mode){
		case TIM0_NORMAL:
			TCCR0B &= ~(1<<WGM02);
			TCCR0A &= ~(1<<WGM01);
			TCCR0A &= ~(1<<WGM00);
		break;
		case TIM0_CTC:
			TCCR0B &= ~(1<<WGM02);
			TCCR0A |=  (1<<WGM01);
			TCCR0A &= ~(1<<WGM00);
		break;
	}
}


/***********************************************/
/* normal mode */
static void (*CallBackFn) (void);

void TIM0_voidEnable(void)
{
	TIMSK0 |= (1<<TOIE0);
}

void TIM0_voidDisable(void)ffg
{
	TIMSK0 &= ~(1<<TOIE0);
}

void TIM0_voidSetTIM0Reg(u8 Copy_u8Reg)
{
	TCNT0 = Copy_u8Reg;
}

void TIM0_voidSetCallBack(void (Copy_PTR2Fn)(void))
{
	CallBackFn = Copy_PTR2Fn;
}

void __vector_16(void) __attribute__((signal,used));
void __vector_16(void)
{
	CallBackFn();
}

/***********************************************/ 
/* ChannelA */
static void (*CallBackFnChA) (void);
 
void TIM0_voidEnableChannelA(void)
{
	TIMSK0 |= (1<<OCIE0A);
}

void TIM0_voidDisableChannelA(void)
{
	TIMSK0 &= ~(1<<OCIE0A);
}

void TIM0_voidSetCTCChAReg(u8 Copy_u8Reg)
{
	OCR0A = Copy_u8Reg;
}

void TIM0_voidSetCallBackCA(void (*Copy_PTR2Fn)(void))
{
	CallBackFnChA=Copy_PTR2Fn;
}

void __vector_14(void) __attribute__((signal,used));
void __vector_14(void)
{
	CallBackFnChA();
}

/***********************************************/
/* ChannelB */
static void (*CallBackFnChB) (void);

void TIM0_voidEnableChannelB(void)
{
	TIMSK0 |= (1<<OCIE0B);
}

void TIM0_voidDisableChannelB(void)
{
	TIMSK0 &= ~(1<<OCIE0B);
}

void TIM0_voidSetCTCChBReg(u8 Copy_u8Reg)
{
	OCR0B = Copy_u8Reg;
}

void TIM0_voidSetCallBackCB(void (*Copy_PTR2Fn)(void))
{
	CallBackFnChB=Copy_PTR2Fn;
}

void __vector_15(void) __attribute__((signal,used));
void __vector_15(void)
{
	CallBackFnChB();
}
