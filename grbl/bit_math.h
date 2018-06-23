/*****************************/
/* Author:  Amr Magdi        */
/* Date:    27/1/2018        */
/* Version: 1.0              */
/*****************************/
#ifndef _BIT_MATH_H
#define _BIT_MATH_H


#define SETBIT(REG, BITNO)				(REG) |=  (1 << (BITNO) )
#define CLRBIT(REG, BITNO)				(REG) &= ~(1 << (BITNO) )
#define TOGLBIT(REG, BITNO)				(REG) ^=  (1 << (BITNO) )
#define GETBIT(REG, BITNO)				(0x01) & ((REG) >> (BITNO) )
/***************************************************************************/
#define SET_LOW_NIB(REG)				(REG) |= (0x0F)
#define CLR_LOW_NIB(REG)				(REG) &= (0xF0)
#define TOGL_LOW_NIB(REG)				(REG) ^= (0x0F)
/***************************************************************************/
#define SET_HIGH_NIB(REG)				(REG) |= (0xF0)
#define CLR_HIGH_NIB(REG)				(REG) &= (0x0F)
#define TOGL_HIGH_NIB(REG)				(REG) ^= (0xF0)
/***************************************************************************/
#define CONCBIT(B7,B6,B5,B4,B3,B2,B1,B0)	CONC_HELP(B7,B6,B5,B4,B3,B2,B1,B0)
#define CONC_HELP(B7,B6,B5,B4,B3,B2,B1,B0)	0b##B7##B6##B5##B4##B3##B2##B1##B0


#endif
