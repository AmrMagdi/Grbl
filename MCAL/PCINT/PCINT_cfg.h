
/************************************************/
/*	Name 	: Zeinab Ali						*/
/*	Version : V01								*/
/************************************************/

#ifndef _PCINT_CFG_H
#define _PCINT_CFG_H

typedef enum
{
	PCINT_0=0,
	PCINT_1,
	PCINT_2,
	PCINT_3,
	PCINT_4,
	PCINT_5,
	PCINT_6, 	/*XTAL1*/
	PCINT_7,	/*XTAL2*/
	PCINT_8,
	PCINT_9,
	PCINT_10,
	PCINT_11,
	PCINT_12,
	PCINT_13,
	PCINT_14, 	/*Reset pin*/
	Resv,
	PCINT_15,
	PCINT_16,
	PCINT_17,
	PCINT_18,
	PCINT_19,
	PCINT_20,
	PCINT_21,
	PCINT_22,
	PCINT_23
}PCINT_pins;


typedef enum
{
	OFF=0,
	ON
}PCINT_state;


typedef struct
{
	PCINT_pins PCINTPinx;
	PCINT_state PCINTState;
}PCINT_cfg;

extern const PCINT_cfg PCINT_cfgArr[25];

#endif
