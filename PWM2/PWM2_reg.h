

#ifndef	_PWM2_REG_H
#define _PWM2_REG_H

#define TCCR2A	*((volatile u8*) 0xB0)
#define COM2A1	7	
#define COM2A0 	6
#define COM2B1 	5
#define COM2B0 	4
#define WGM21   1
#define WGM20	0
/******************************************************/

#define TCCR2B	*((volatile u8*) 0xB1)
#define FOC2A 	7
#define FOC2B   6
#define WGM22   3
#define CS22    2
#define CS21    1
#define CS20    0
/******************************************************/

#define TCNT2	*((volatile u8*) 0xB2)
/******************************************************/

#define OCR2A	*((volatile u8*) 0xB3)
/******************************************************/

#define OCR2B	*((volatile u8*) 0xB4)
/******************************************************/

#define TIMSK2	*((volatile u8*) 0x70)
#define OCIE2B  2
#define OCIE2A  1
#define TOIE2   0
/******************************************************/

#define TIFR2	*((volatile u8*) 0x37)
#define OCF2B   2
#define OCF2A   1
#define TOV2    0
/******************************************************/

#define ASSR	*((volatile u8*) 0xB6)
#define EXCLK   6
#define AS2     5
#define TCN2UB  4
#define OCR2AUB 3
#define OCR2BUB 2
#define TCR2AUB 1
#define TCR2BUB 0

#endif
