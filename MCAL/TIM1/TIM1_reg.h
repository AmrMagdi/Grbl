/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V01								*/
/************************************************/

#ifndef _TIM1_REG_H
#define	_TIM1_REG_H


#define TCCR1A	*((volatile u8*) 0x80)
#define COM1A1	7 	
#define COM1A0  6
#define COM1B1  5 
#define COM1B0  4
#define WGM11   1
#define WGM10   0
/***************************************/

#define TCCR1B 	*((volatile u8*) 0x81)
#define ICNC1 	7
#define ICES1 	6
#define WGM13 	4
#define WGM12 	3
#define CS12  	2 
#define CS11  	1
#define CS10  	0
/***************************************/

#define TCCR1C 	*((volatile u8*) 0x82)
#define FOC1A	7
#define FOC1B	6
/***************************************/

#define TCNT1 	*((volatile u16*) 0x84)
/***************************************/

#define OCR1A	*((volatile u16*) 0x88)
/***************************************/

#define OCR1B	*((volatile u16*) 0x8A)
/***************************************/

#define TIMSK1	*((volatile u8*) 0x6F)
#define ICIE1   5 
#define OCIE1B  2 
#define OCIE1A  1
#define TOIE1   0
/***************************************/

#define TIFR1	*((volatile u8*) 0x36)
#define ICF1	5 
#define OCF1B	2 
#define OCF1A 	1
#define TOV1	0




#endif