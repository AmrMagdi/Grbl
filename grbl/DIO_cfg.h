

#ifndef _DIO_CFG_H
#define _DIO_CFG_H



typedef enum
{
	PB0=0,
	PB1,
	PB2,
	PB3,
	PB4,
	PB5,
	PB6,
	PB7,
	PC0,
	PC1,
	PC2,
	PC3,
	PC4,
	PC5,
	PC6,
	resv,
	PD0,
	PD1,
	PD2,
	PD3,
	PD4,
	PD5,
	PD6,
	PD7
}DIO_PinNAme_t;

typedef enum
{
	InputWithoutPullUpResistancor=0,
	InputWithPullUpResistancor,
	Output
}DIO_PinMode_t;


typedef struct
{
	DIO_PinNAme_t PinName;
	DIO_PinMode_t PinMode;
}DIO_cfg_t;

extern const DIO_cfg_t DIO_cfg[];

#endif
