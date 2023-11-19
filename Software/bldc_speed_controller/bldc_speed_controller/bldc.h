/*
 * bldc.h
 *
 * Created: 10/15/2023 7:01:37 PM
 *  Author: awjpp
 */ 


#ifndef BLDC_H_
#define BLDC_H_

#define GATE_PWM_FREQUENCY	(uint32_t)90000				//has to be greater than 400Hz
#define CURRENT_LIMIT_AMPS	1

/*ports definitions.*/
#define GATE_DRIVERS_port		&PORTA
#define V_GATE_DRIVE_EN_port	&PORTD

/*pin bit masks.*/
#define A_LOW_pin				PIN3_bm
#define B_LOW_pin				PIN4_bm
#define C_LOW_pin				PIN5_bm
#define A_HIGH_pin				PIN0_bm
#define B_HIGH_pin				PIN1_bm
#define C_HIGH_pin				PIN2_bm
#define V_GATE_DRIVE_EN_pin		PIN5_bm

/*port and pin macros for easy writes to io.*/
#define A_LOW					GATE_DRIVERS_port, PIN3_bm
#define B_LOW					GATE_DRIVERS_port, PIN4_bm
#define C_LOW					GATE_DRIVERS_port, PIN5_bm
#define A_HIGH					GATE_DRIVERS_port, PIN0_bm
#define B_HIGH					GATE_DRIVERS_port, PIN1_bm
#define C_HIGH					GATE_DRIVERS_port, PIN2_bm
#define V_GATE_DRIVE_EN			V_GATE_DRIVE_EN_port, V_GATE_DRIVE_EN_pin

/*tca timer channels for the high side gates.*/
#define A_HIGH_CMP_bm			TCA_SINGLE_CMP0EN_bm
#define B_HIGH_CMP_bm			TCA_SINGLE_CMP1EN_bm
#define C_HIGH_CMP_bm			TCA_SINGLE_CMP2EN_bm

/*definitions for analog comparator channels.*/
#define A_BEMF_AC_CHANNEL		&AC0
#define B_BEMF_AC_CHANNEL		&AC1
#define C_BEMF_AC_CHANNEL		&AC2
#define A_BEMF_AC_POS_IN		AC_MUXPOS_AINP0_gc
#define B_BEMF_AC_POS_IN		AC_MUXPOS_AINP2_gc
#define C_BEMF_AC_POS_IN		AC_MUXPOS_AINP3_gc
#define NEUTRAL_BEMF_AC_NEG_IN	AC_MUXNEG_AINN2_gc

/*ADC input for current limit.*/
#define CURRENT_LIMIT_MUX_POS	ADC_MUXPOS_AIN0_gc
#define ADC_WINDOW_HIGH			4000

/*defines for input pwm.*/
#define INPUT_PWM_port			&PORTC
#define INPUT_PWM_pin			PIN0_bm
#define INPUT_PWM				INPUT_PWM_port, INPUT_PWM_pin


typedef struct bldc_status_t
{
	uint8_t is_moving		:1;			//1 for moving, 0 for stopped.
	uint8_t reverse			:1;			//0 for forward, 1 for reverse.
}bldc_status_t;


void bldc_init_led();					//initialize the rgb led.
void bldc_init_clk();					//setup master clock.
void bldc_init_gate_drivers();			//sets up the PWM timer for high side and io for low side.
void bldc_init_feedback();				//sets up the analog comparators.
void bldc_init_input_pwm();				//sets up a timer to measure the input pwm signal.
void bldc_init_current_limit();			//initializes the adc.

void bldc_enable_v_gate_drive();		//turns on the boost converter.
void bldc_disable_v_gate_drive();		//turns off the boost converter.
void bldc_enable_current_limit();		//enables the adc interrupt.
void bldc_disable_current_limit();		//disables the adc interrupt.

void bldc_startup();					//start up sequence to get the motor turning.
void bldc_enable_bemf_int();			//enables the back emf interrupts.
void bldc_disable_bemf_int();			//disables the back emf interrupts.

void bldc_set_duty_cycle(uint16_t cmp_val);	//sets the compare value of each tca channel.


#endif /* BLDC_H_ */