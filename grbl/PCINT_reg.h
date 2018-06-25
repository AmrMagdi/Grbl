

/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V01								*/
/************************************************/

#ifndef	_PCINT_REG_H
#define	_PCINT_REG_H

#define PCICR	*((volatile u8*) 0x68)
#define PCIE2 	2
#define PCIE1   1
#define PCIE0   0

#define PCIFR	*((volatile u8*) 0x3B)
#define PCIF2 	2
#define PCIF1   1
#define PCIF0   0

#define PCMSK2	*((volatile u8*) 0x6D)
#define PCINT23 7
#define PCINT22 6
#define PCINT21 5
#define PCINT20 4
#define PCINT19 3
#define PCINT18 2
#define PCINT17 1
#define PCINT16 0

#define PCMSK1	*((volatile u8*) 0x6C)
#define PCINT14 6
#define PCINT13 5
#define PCINT12 4
#define PCINT11 3
#define PCINT10 2
#define PCINT9  1
#define PCINT8  0

#define PCMSK0	*((volatile u8*) 0x6B)
#define PCINT7	7 
#define PCINT6  6
#define PCINT5  5
#define PCINT4  4
#define PCINT3  3
#define PCINT2  2
#define PCINT1  1
#define PCINT0  0

#endif