

#include "std_types.h"
#include "nuts_bolts.h"
#include "STEPPERH.h"
#include "DIO.h"
#include "settings.h"

#define X_STEP_BIT      PD2  // Uno Digital Pin 2
#define Y_STEP_BIT      PD3  // Uno Digital Pin 3
#define Z_STEP_BIT      PD4  // Uno Digital Pin 4
#define STEPPERS_DISABLE_BIT    PB0  // Uno Digital Pin 8
#define X_DIRECTION_BIT   PD5  // Uno Digital Pin 5
#define Y_DIRECTION_BIT   PD6  // Uno Digital Pin 6
#define Z_DIRECTION_BIT   PD7  // Uno Digital Pin 7

#ifndef SEGMENT_BUFFER_SIZE
  #define SEGMENT_BUFFER_SIZE 6
#endif

// Used to avoid ISR nesting of the "Stepper Driver Interrupt". Should never occur though.
static volatile u8 busy;

typedef struct {
	u32 steps[N_AXIS];
	u32 step_event_count;
	u32 direction_bits;
#ifdef VARIABLE_SPINDLE
	u8 is_pwm_rate_adjusted; // Tracks motions that require constant laser power/rate
#endif
} st_block_t;
static st_block_t st_block_buffer[SEGMENT_BUFFER_SIZE - 1];

// Primary stepper segment ring buffer. Contains small, short line segments for the stepper
// algorithm to execute, which are "checked-out" incrementally from the first block in the
// planner buffer. Once "checked-out", the steps in the segments buffer cannot be modified by
// the planner, where the remaining planner block steps still can.
typedef struct {
	u8 n_step;    // Number of step events to be executed for this segment
	u8 cycles_per_tick; // Step distance traveled per ISR tick, aka step rate.
	u8 st_block_index; // Stepper block data index. Uses this information to execute this segment.
#ifdef ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING
	u8 amass_level; // Indicates AMASS level for the ISR to execute this segment
#else
	u8 prescaler; // Without AMASS, a prescaler is required to adjust for slow timing.
#endif
#ifdef VARIABLE_SPINDLE
	u8 spindle_pwm;
#endif
} segment_t;
static segment_t segment_buffer[SEGMENT_BUFFER_SIZE];

// Stepper ISR data struct. Contains the running data for the main stepper ISR.
typedef struct {
	// Used by the bresenham line algorithm
	u32 counter_x,       // Counter variables for the bresenham line tracer
			counter_y, counter_z;
#ifdef STEP_PULSE_DELAY
	u8 step_bits; // Stores out_bits output to complete the step pulse delay
#endif

	u8 execute_step;     // Flags step execution for each interrupt.
	u8 step_pulse_time;  // Step pulse reset time after step rise.
	u8 step_outbits;         // The next stepping-bits to be output.
	u8 dir_outbits;
#ifdef ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING
	uint32_t steps[N_AXIS];
#endif

	u16 step_count;       // Steps remaining in line segment motion
	u8 exec_block_index; // Tracks the current st_block index. Change indicates new block.
	st_block_t *exec_block; // Pointer to the block data for the segment being executed
	segment_t *exec_segment;  // Pointer to the segment being executed
} stepper_t;
static stepper_t st;


	// Configure Timer 0: Stepper Port Reset Interrupt
//	TIMSK0 &= ~((1 << OCIE0B) | (1 << OCIE0A) | (1 << TOIE0)); // Disconnect OC0 outputs and OVF interrupt.


//  TCCR0A = 0; // Normal operation
	TIM0_voidSetMode(TIM0_NORMAL);
//  TCCR0B = 0; // Disable Timer0 until needed
	TIM0_voidSetPrescaler(TIM0_DISCONNECT);

//  TIMSK0 |= (1<<TOIE0); // Enable Timer0 overflow interrupt
	TIM0_voidEnable();
#ifdef STEP_PULSE_DELAY
//	TIMSK0 |= (1<<OCIE0A); // Enable Timer0 Compare Match A interrupt
	TIM0_voidEnableChannelA();
#endif
}
void STEPPER_voidInitialize(void)
{
	/*timer1*/
	//Timer1 configuration
	
	/*timer0*/
	/*initialize timer0*/
	TIM0_voidInitialize();

	/*disable timer0*/
	TIM0_voidDisable();

	/*disconnect channelA pin*/
	TIM0_voidDisableChannelA();

	/*disconnect channelB pin*/
	TIM0_voidDisableChannelB();
	switch(STEPPER_cfgArr[0].stepperDelay)
	{
		case NO_STEPPER_DELAY:
		//normal mode
		break;
		case STEPPER_DELAY:
		//ctc mode
		break;
	}
	
}


void st_wake_up(void)
{
	if (bit_istrue(settings.flags,BITFLAG_INVERT_ST_ENABLE))
	{
		DIO_voidWritePin(STEPPERS_DISABLE_BIT,1);
	}
	else
	{
		DIO_voidWritePin(STEPPERS_DISABLE_BIT,0);
	}
	
	// Initialize stepper output bits to ensure first ISR call does not step.
	st.step_outbits = step_port_invert_mask;
	
	
	// Initialize step pulse timing from settings. Here to ensure updating after re-writing.
	switch(STEPPER_cfgArr[0].stepperDelay)
	{
		case NO_STEPPER_DELAY:
			// Set step pulse time. Ad hoc computation from oscilloscope. Uses two's complement.
			st.step_pulse_time = -(((settings.pulse_microseconds-2)*TICKS_PER_MICROSECOND) >> 3);
		break;
		case STEPPER_DELAY:
			st.step_pulse_time = -(((settings.pulse_microseconds+STEP_PULSE_DELAY-2)*TICKS_PER_MICROSECOND) >> 3);
			// Set delay between direction pin write and step command.
			TIM0_voidSetCTCChAReg(-(((settings.pulse_microseconds)*TICKS_PER_MICROSECOND) >> 3));
		break;
	}
	
	// Enable Stepper Driver Interrupt
    TIM1_voidEnableChannelA();

}


void st_go_idle(void)
{
	// Disable Stepper Driver Interrupt. Allow Stepper Port Reset Interrupt to finish, if active.
	TIM1_voidDisableChannelA();
	// Reset clock to no prescaling.*/
	TIM1_voidSetPrescaler(TIM1_DIV_PRESCAl_1);
	
	busy = false;	
	
	// Set stepper driver idle state, disabled or enabled, depending on settings and circumstances.
	boolean pin_state = false; // Keep enabled.
	if (((settings.stepper_idle_lock_time != 0xff) || sys_rt_exec_alarm || sys.state == STATE_SLEEP) && sys.state != STATE_HOMING) {
		// Force stepper dwell to lock axes for a defined amount of time to ensure the axes come to a complete
		// stop and not drift from residual inertial forces at the end of the last movement.
		delay_ms(settings.stepper_idle_lock_time);
		pin_state = true; // Override. Disable steppers.
	}
	if (bit_istrue(settings.flags,BITFLAG_INVERT_ST_ENABLE))
	{ 
			pin_state = !pin_state; } // Apply pin invert.
			if (pin_state) 
			{ 
				STEPPERS_DISABLE_PORT |= (1<<STEPPERS_DISABLE_BIT); 
			}
	else 
	{ 
		STEPPERS_DISABLE_PORT &= ~(1<<STEPPERS_DISABLE_BIT); }
	}
