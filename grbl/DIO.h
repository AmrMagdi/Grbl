

#ifndef _DIO_H
#define _DIO_H

#include "DIO_cfg.h"

typedef union{
	struct{
		u8 PX0: 1;
		u8 PX1: 1;
		u8 PX2: 1;
		u8 PX3: 1;
		u8 PX4: 1;
		u8 PX5: 1;
		u8 PX6: 1;
		u8 PX7: 1;
	};
	u8 port;
}union_reg_t;

extern void DIO_Initialize(void);

extern void DIO_voidWritePin(DIO_PinNAme_t Copy_PinName,boolean Value);

extern boolean DIO_booleanReadPin(DIO_PinNAme_t Copy_PinName);

extern void DIO_voidsetPortAccess(union_reg_t* Copy_ptr_to_union);

extern void DIO_voidSetPortB(union_reg_t* Copy_ptr_to_union);

extern void DIO_voidSetPortC(union_reg_t* Copy_ptr_to_union);

extern void DIO_voidSetPortD(union_reg_t* Copy_ptr_to_union);

#endif
