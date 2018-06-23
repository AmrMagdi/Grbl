/*****************************/
/* Author:  Amr Magdi        */
/* Date:    18/6/2018        */
/* Version: 1.0              */
/*****************************/
#ifndef _WDT_CFG_H
#define _WDT_CFG_H

typedef enum {
	WDT_Oscillator_16ms = 0,
	WDT_Oscillator_32ms,
	WDT_Oscillator_64ms,
	WDT_Oscillator_125ms,
	WDT_Oscillator_250ms,
	WDT_Oscillator_500ms,
	WDT_Oscillator_1000ms,
	WDT_Oscillator_2000ms,
	WDT_Oscillator_4000ms,
	WDT_Oscillator_8000ms,

}WDT_prescale_t;

typedef enum {
	Stopped = 0,
	Interrupt,
	System_Reset,
	Interrupt_and_System_Reset

}WDT_mode_t;


typedef struct {
	WDT_prescale_t prescaler;
	WDT_mode_t mode;

}WDT_cfg_t;


extern const WDT_cfg_t WDT_cfg[];

#endif
