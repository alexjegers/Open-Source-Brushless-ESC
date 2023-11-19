/*
 * _bldc.h
 *
 * Created: 10/15/2023 7:07:23 PM
 *  Author: awjpp
 */ 


#ifndef _BLDC_H_
#define _BLDC_H_

static void (*_bldc_step_arr[6])();
static uint8_t _bldc_current_step;					//the current step of the commutation cycle.
static uint32_t _bldc_initial_input_pwm_val;		//this is the value of the input pwm signal at 0% throttle.
static uint32_t _bldc_output_pwm_top;				//the max value of the output pwm.

/*analog comparator interrupt handlers for back emf.*/
void _bldc_ac_bemf_int_handler();

/*adc interrupt handler for current limit.*/
void _bldc_current_limit_int_handler();

/*interrupt handler for the input pwm.*/
void _bldc_input_pwm_handler();


void bldc_set_duty_cycle(uint16_t cmp_val);	//sets the compare value of each tca channel.

/*commutation steps.*/
void _bldc_step_one();
void _bldc_step_two();
void _bldc_step_three();
void _bldc_step_four();
void _bldc_step_five();
void _bldc_step_six();

void _bldc_next_step();

#endif /* _BLDC_H_ */