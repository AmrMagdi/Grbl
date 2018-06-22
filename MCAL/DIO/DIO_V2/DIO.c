

#include "STD_TYPES.h"
#include "DIO_reg.h"
#include "DIO.h"

typedef enum
{	
	PB=0,
	PC,
	PD
}PORT_cfg;



void DIO_Initialize(void)
{
	u8 PortName;
	u8 PinNumber;
	for (u8 index=0;index<24;index++)
	{
		PortName = index /8;
		PinNumber = index%8;
		switch(PortName)
		{
			case PB:
				if(DIO_cfg[index].PinMode == InputWithoutPullUpResistancor)
				{
					DDRB &= ~(1<<PinNumber);
				}
				else if(DIO_cfg[index].PinMode == Output)
				{
					DDRB |=  (1<<PinNumber);
				}
				else if(DIO_cfg[index].PinMode == InputWithPullUpResistancor)
				{
					DDRB &= ~(1<<PinNumber);
					PORTB |= (1<<PinNumber);
				}
			break;
			case PC:
				if(DIO_cfg[index].PinMode == InputWithoutPullUpResistancor)
				{
					DDRC &= ~(1<<PinNumber);
				}
				else if(DIO_cfg[index].PinMode == Output)
				{
					DDRC |=  (1<<PinNumber);
				}
				else if(DIO_cfg[index].PinMode == InputWithPullUpResistancor)
				{
					DDRC &= ~(1<<PinNumber);
					PORTC |= (1<<PinNumber);
				}
			break;
			case PD:
				if(DIO_cfg[index].PinMode == InputWithoutPullUpResistancor)
				{
					DDRD &= ~(1<<PinNumber);
				}
				else if(DIO_cfg[index].PinMode == Output)
				{
					DDRD |=  (1<<PinNumber);
				}
				else if(DIO_cfg[index].PinMode == InputWithPullUpResistancor)
				{
					DDRD &= ~(1<<PinNumber);
					PORTD |= (1<<PinNumber);
				}
			break;
		}
	}
}

void DIO_voidWritePin(DIO_PinNAme_t Copy_PinName,boolean Value)
{
	u8 PORT;
	u8 PINNumber;
	PORT = Copy_PinName / 8;
	PINNumber = Copy_PinName % 8;
	switch(PORT)
	{
		case PB:
			if(Value!=0)
			{
				PORTB |= (1<<PINNumber);
			}
			else
			{
				PORTB &= ~(1<<PINNumber);
			}		
		break;
		case PC:
			if(Value!=0)
			{
				PORTC |= (1<<PINNumber);
			}
			else
			{
				PORTC &= ~(1<<PINNumber);
			}
		break;
		case PD:
			if(Value!=0)
			{
				PORTD |= (1<<PINNumber);
			}
			else
			{
				PORTD &= ~(1<<PINNumber);
			}
		break;
	}
}

boolean DIO_booleanReadPin(DIO_PinNAme_t Copy_PinName)
{
	u8 PIN;
	u8 PINNumber;
	u8 Value;
	PIN = Copy_PinName / 8;
	PINNumber = Copy_PinName % 8;
	switch(PIN)
	{
		case PB:
			Value = PINB&(1<<PINNumber); 
		break;
		case PC:
			Value = PINC&(1<<PINNumber); 
		break;
		case PD:
			Value = PIND&(1<<PINNumber); 
		break;
	}
	return Value;
}
