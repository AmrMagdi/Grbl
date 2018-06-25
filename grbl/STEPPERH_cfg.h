

#ifndef _STEPPERF_CFG_H
#define _STEPPERF_CFG_H

#define STEP_PULSE_DELAY 16 //configured by user

typedef enum
{
	NO_STEPPER_DELAY=0,
	STEPPER_DELAY
}STEPPER_DELAY_cfg;	

typedef struct
{
	STEPPER_DELAY_cfg stepperDelay;
}STEPPER_cfg;


extern const STEPPER_cfg STEPPER_cfgArr[1];
#endif
