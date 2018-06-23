/*****************************/
/* Author:  Amr Magdi        */
/* Date:    24/2/2018        */
/* Version: 1.0              */
/*****************************/
#include "std_types.h"
#include "bit_math.h"

#include "GIE_reg.h"
#include "GIE_priv.h"		/*import priv.h first as config.h depends on it*/
#include "GIE_config.h"
#include "GIE_int.h"



/****************************************/
/* Description: Function to enable      */
/*		         global interrupt  		*/
/*								  		*/
/****************************************/

void GIE_voidEnable(void){

	SETBIT(SREG, GIE_u8_BIT_INDEX);
}

/****************************************/
/* Description: Function to disable     */
/*		         global interrupt  		*/
/*								  		*/
/****************************************/

void GIE_voidDisable(void){

	CLRBIT(SREG, GIE_u8_BIT_INDEX);
}
