/*****************************/
/* Author:  Amr Magdi        */
/* Date:    18/6/2018        */
/* Version: 1.0              */
/*****************************/

#include "std_types.h"
#include "bit_math.h"
#include "WDT_reg.h"
#include "WDT.h"

static void (*WDT_CallBack) (void);

void WDT_voidInitialize(void){
	
	/*Clear Watchdog System Reset Flag*/
	MCUSR &= ~(1<<WDRF);
	if(WDT_cfg[0].mode == System_Reset){
		/* Enable Watchdog System Reset & Enable Watchdog Change Enable to change the prescaler bits*/
		WDTCSR |= (1<<WDCE) | (1<<WDE);
	}
    if(WDT_cfg[0].prescaler == WDT_Oscillator_32ms){
    	WDTCSR = (1<<WDP0); // Set time-out at ~32msec.
    }
}

void WDT_voidDisable(void){
	WDTCSR &= ~(1<<WDIE); // Disable watchdog timer.
}

void WDT_voidEnable(void){
	WDTCSR |= (1<<WDIE); // Enable watchdog timer.
}

WDT_status_t WDT_u8GetStatus(void){

	WDT_status_t state = Disabled;

	if ( WDTCSR & (1<<WDIE) ){
		state = Disabled;
	}
	else{
		state = Enabled;
	}
	return state;
}

void WDT_voidSetCallBack( void (*Copy_ptr) (void) ){
	WDT_CallBack = Copy_ptr;
}


void __vector_6 (void) __attribute__((signal,used));

void __vector_6 (void){
	WDT_CallBack();
}




