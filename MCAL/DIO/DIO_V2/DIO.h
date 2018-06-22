

#ifndef _DIO_H
#define _DIO_H

#include "DIO_cfg.h"

extern void DIO_Initialize(void);

extern void DIO_voidWritePin(DIO_PinNAme_t Copy_PinName,boolean Value);

extern boolean DIO_booleanReadPin(DIO_PinNAme_t Copy_PinName);

#endif