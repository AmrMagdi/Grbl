/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V02								*/
/************************************************/

#include "std_types.h"
#include "PWM2_reg.h"
#include "PWM2.h"

void PWM2_voidInitialize(void)
{
	/*CMP force reset*/
	TCCR2B &= ~(1<< FOC2A);
	TCCR2B &= ~(1<< FOC2B);
	
	/*PWM mode*/
	switch(PWM2_cfgArr[0].PWM2_Mode)
	{
		case PWM2_PWM_PHASE_CORRECT:
			TCCR2A &= ~(1<<WGM21);
			TCCR2A |=  (1<<WGM20);
		break;
		case PWM2_PWM_FAST:
			TCCR2A |=  (1<<WGM21);
			TCCR2A |=  (1<<WGM20);
		break;
	}
	
	/*disable ChannelA*/
	TCCR2A &= ~(1<<COM2A1);
	TCCR2A &= ~(1<<COM2A0);
	
	/*disable ChannelB*/
	TCCR2A |=  (1<<COM2B1);
   	TCCR2A |=  (1<<COM2B0);
	
	/*clock*/
	switch(PWM2_cfgArr[0].PWM2_CLOCK)
	{
		case PWM2_DIV_PRESCAl_1:
			TCCR2B &= ~(1<<CS22);
			TCCR2B &= ~(1<<CS21);
			TCCR2B |=  (1<<CS20);
		break; 
		case PWM2_DIV_PRESCAl_8:
			TCCR2B &= ~(1<<CS22);
			TCCR2B |=  (1<<CS21);
			TCCR2B &= ~(1<<CS20);
		break;
		case PWM2_DIV_PRESCAl_32:
			TCCR2B &= ~(1<<CS22);
		    TCCR2B |=  (1<<CS21);
		    TCCR2B |=  (1<<CS20);
		break;
		case PWM2_DIV_PRESCAl_64:
			TCCR2B |=  (1<<CS22);
		    TCCR2B &= ~(1<<CS21);
		    TCCR2B &= ~(1<<CS20);
		break;
		case PWM2_DIV_PRESCAl_128:
			TCCR2B |=  (1<<CS22);
		    TCCR2B &= ~(1<<CS21);
		    TCCR2B |=  (1<<CS20);
		break;
		case PWM2_DIV_PRESCAl_256:
			TCCR2B |=  (1<<CS22);
		    TCCR2B |=  (1<<CS21);
		    TCCR2B &= ~(1<<CS20);
		break;
		case PWM2_DIV_PRESCAl_1024:
			TCCR2B |=  (1<<CS22);
		    TCCR2B |=  (1<<CS21);
		    TCCR2B |=  (1<<CS20);
		break;
	}
}

/***************************************************************************/
/*channelA*/
void PWM2_voidSetPWMChA(u8 Copy_u8PWMValue)
{
	OCR2A = Copy_u8PWMValue;
}

void PWM2_voidEnableChA(void)
{
	switch(PWM2_cfgArr[0].PWM2_ChannelA_Mode)
	{
		case PWM2_TOGGLE_OC2A:
			TCCR2B |=  (1<<WGM22);
			TCCR2A &= ~(1<<COM2A1);
			TCCR2A |=  (1<<COM2A0);
		break;
		case PWM2_NON_INVERT_OC2A:
			TCCR2A |=  (1<<COM2A1);
			TCCR2A &= ~(1<<COM2A0);
		break;
		case PWM2_INVERT_OC2A:
			TCCR2A |=  (1<<COM2A1);
			TCCR2A |=  (1<<COM2A0);
		break;
	}
}

void PWM2_voidDisableChA(void)
{
	TCCR2A &= ~(1<<COM2A1);
	TCCR2A &= ~(1<<COM2A0);
}

/***************************************************************************/
/*channelB*/

void PWM2_voidSetPWMChB(u8 Copy_u8PWMValue)
{
	OCR2B = Copy_u8PWMValue;
}

void PWM2_voidEnableChB(void)
{
		switch(PWM2_cfgArr[0].PWM2_ChannelB_Mode)
	{
		case PWM2_NON_INVERT_OC2B:
			TCCR2A |=  (1<<COM2B1);
			TCCR2A &= ~(1<<COM2B0);
		break;
		case PWM2_INVERT_OC2B:
			TCCR2A |=  (1<<COM2B1);
			TCCR2A |=  (1<<COM2B0);
		break;
	}
}

void PWM2_voidDisableChB(void)
{
	TCCR2A &=  ~(1<<COM2B1);
   	TCCR2A &=  ~(1<<COM2B0);
}
