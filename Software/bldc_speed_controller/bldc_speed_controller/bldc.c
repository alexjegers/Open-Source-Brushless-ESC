/*
 * bldc.c
 *
 * Created: 10/15/2023 7:01:24 PM
 *  Author: awjpp
 */ 
#define F_CPU 24000000UL



#include <avr/io.h>
#include <util/delay.h>
#include "drivers.h"
#include "bldc.h"
#include "_bldc.h"
#include "debug.h"


static void (*_bldc_step_arr[6])() = {_bldc_step_one, _bldc_step_two,
							_bldc_step_three, _bldc_step_four,
							_bldc_step_five, _bldc_step_six };
							
static uint8_t _bldc_current_step = 0;
static uint32_t _bldc_initial_input_pwm_val = 0;
bldc_status_t bldc_status = { 0, 0 };

void bldc_init_led() 
{
	/*turn off all leds.*/
	io_out_high(LED_G);
	io_out_high(LED_R);
	io_out_high(LED_B);	
	
	io_data_dir_out(LED_R);
	io_data_dir_out(LED_G);
	io_data_dir_out(LED_B);

}

void bldc_init_clk()
{	
	clkctrl_internal_osc_freq(CLKCTRL_FRQSEL_24M_gc);			//set internal oscillator to 24MHz.
	clkctrl_mclk_prescale_dis();								//disable prescaler.
	clkctrl_mclk_src(CLKCTRL_CLKSEL_OSCHF_gc);					//select internal oscillator as source.
	while((clkctrl_mclk_status() & CLKCTRL_MCLKSTATUS) == 0) {}
	
	io_data_dir_out(CLKOUT_PIN);
	clkctrl_mclk_out_en();										//enable clkout pin.
	
	debug_blink_quantity(LED_G, 1);
	debug_led_on(LED_R);
}


void bldc_init_gate_drivers()
{
	/*set the io for the all gates as outputs and drive the low side low and high side high (inverting circuitry).*/
	io_data_dir_out(GATE_DRIVERS_port, A_LOW_pin | B_LOW_pin | C_LOW_pin 
									| A_HIGH_pin |B_HIGH_pin | C_HIGH_pin);
	io_out_low(GATE_DRIVERS_port, A_LOW_pin | B_LOW_pin | C_LOW_pin);
	io_out_high(GATE_DRIVERS_port, A_HIGH_pin | B_HIGH_pin | C_HIGH_pin);
	
	tca_single_set_mode(&TCA0, TCA_SINGLE_WGMODE_SINGLESLOPE_gc);			//standard pwm mode.
	
	uint32_t tca_per = F_CPU / GATE_PWM_FREQUENCY;							//calculate the TOP value for the timer to achieve desired frequency
	tca_single_set_per(&TCA0, (uint16_t)tca_per);							//write the TOP value to the period register.
	tca_enable(&TCA0);														//enable the timer.
	_bldc_output_pwm_top = tca_per;											//store the top value to a global variable to be used in input pwm interrupt.
	bldc_enable_v_gate_drive();												//enables the boost converter.
}

void bldc_init_feedback()
{
	vref_set_acref(VREF_REFSEL_VREFA_gc);
	
	/*for A_BEMF.*/
	ac_set_dacref(A_BEMF_AC_CHANNEL, 255);
	ac_set_int_handler(A_BEMF_AC_CHANNEL, _bldc_ac_bemf_int_handler);	
	ac_mux_pos_input(A_BEMF_AC_CHANNEL, A_BEMF_AC_POS_IN);
	ac_mux_neg_input(A_BEMF_AC_CHANNEL, NEUTRAL_BEMF_AC_NEG_IN);
	ac_interrupt_mode(A_BEMF_AC_CHANNEL, AC_INTMODE_NORMAL_BOTHEDGE_gc);
	ac_enable(A_BEMF_AC_CHANNEL);
	
	/*for B_BEMF.*/
	ac_set_dacref(B_BEMF_AC_CHANNEL, 255);
	ac_set_int_handler(B_BEMF_AC_CHANNEL, _bldc_ac_bemf_int_handler);	
	ac_mux_pos_input(B_BEMF_AC_CHANNEL, B_BEMF_AC_POS_IN);
	ac_mux_neg_input(B_BEMF_AC_CHANNEL, NEUTRAL_BEMF_AC_NEG_IN);
	ac_interrupt_mode(B_BEMF_AC_CHANNEL, AC_INTMODE_NORMAL_BOTHEDGE_gc);
	ac_enable(B_BEMF_AC_CHANNEL);
	
	/*for C_BEMF.*/
	ac_set_dacref(C_BEMF_AC_CHANNEL, 255);
	ac_set_int_handler(C_BEMF_AC_CHANNEL, _bldc_ac_bemf_int_handler);	
	ac_mux_pos_input(C_BEMF_AC_CHANNEL, C_BEMF_AC_POS_IN);
	ac_mux_neg_input(C_BEMF_AC_CHANNEL, NEUTRAL_BEMF_AC_NEG_IN);
	ac_interrupt_mode(C_BEMF_AC_CHANNEL, AC_INTMODE_NORMAL_BOTHEDGE_gc);
	ac_enable(C_BEMF_AC_CHANNEL);
	
}

void bldc_enable_v_gate_drive()
{
	io_data_dir_out(V_GATE_DRIVE_EN);
	io_out_high(V_GATE_DRIVE_EN);
}

void bldc_disable_v_gate_drive()
{
	io_data_dir_out(V_GATE_DRIVE_EN);
	io_out_low(V_GATE_DRIVE_EN);
}

void bldc_enable_current_limit()
{
	adc_enable_window_int();
}

void bldc_disable_current_limit()
{
	adc_disable_window_int();
}

void bldc_init_input_pwm()
{
	io_data_dir_in(INPUT_PWM);
	tcb_clksel(&TCB2, TCB_CLKSEL_DIV2_gc);
	tcb_cntmode(&TCB2, TCB_CNTMODE_PW_gc);
	tcb_input_cap_event(&TCB2, true);
	tcb_dbgrun(&TCB2, true);
	tcb_capture_int(&TCB2, true);
	tcb_set_tcb2_handler(&_bldc_input_pwm_handler);

	EVSYS.CHANNEL2 = EVSYS_CHANNEL2_PORTC_PIN0_gc;							//config the event generator for channel 2 port c pin 0.
	EVSYS.USERTCB2CAPT = EVSYS_USER_CHANNEL2_gc;
	EVSYS.USERTCB2COUNT = EVSYS_USER_CHANNEL2_gc;
	
	tcb_enable(&TCB2);	
	
	for (uint8_t i = 0; i < 5;)
	{
		while ((tcb_int_flags(&TCB2) & TCB_CAPT_bm) == 0) {}
		_bldc_initial_input_pwm_val += tcb_get_cmp(&TCB2);
		i++;
	}
	
	_bldc_initial_input_pwm_val /= 5;
	debug_blink_quantity(LED_B, 3);
}

void bldc_init_current_limit()
{
	/*for current limit.*/
	vref_set_adc0ref(VREF_REFSEL_VDD_gc);
	
	adc_run_in_debug(true);
	
	adc_set_pos_input(ADC_MUXPOS_AIN0_gc);
	adc_set_neg_input(ADC_MUXNEG_GND_gc);
	adc_set_conversion_mode(0);
	adc_set_resolution(ADC_RESSEL_12BIT_gc);
	adc_free_running(true);
	adc_set_sample_number(0);
	adc_set_clk_prescaler(ADC_PRESC_DIV2_gc);
	adc_set_init_delay(ADC_INITDLY_DLY16_gc);
	adc_set_sample_length(25);
	adc_enable_window_mode(ADC_WINCM_ABOVE_gc, 0, ADC_WINDOW_HIGH);
	adc_set_int_handler(_bldc_current_limit_int_handler, ADC0_WCMP_vect_num);
	adc_enable_window_int();
	
	adc_enable();
	adc_start_conversion();
	
	while (adc_get_result() > ADC_WINDOW_HIGH)
	{
		while (adc_get_result_rdy_flag() == 0){}
	}	
}

void bldc_startup()
{
	uint16_t cmp_val = 200;										//duty cycle, 5%.
	uint16_t delay_in_us = 3000;								//time to hold each step.
	tca_single_set_cmp0(&TCA0, cmp_val);						//set duty cycle.
	tca_single_set_cmp1(&TCA0, cmp_val);						//set duty cycle.	
	tca_single_set_cmp2(&TCA0, cmp_val);						//set duty cycle.
	for (uint16_t x = 0; x < 350; x++)
	{
			_bldc_next_step();
			for (int delay_time = 0; delay_time < delay_in_us; delay_time++)
			{
				_delay_us(1);
			}
		
 		delay_in_us -= 5;
	}
	cpu_enable_global_int();
}

void bldc_enable_bemf_int()
{
	ac_interrupts_enable(A_BEMF_AC_CHANNEL);	
	ac_interrupts_enable(B_BEMF_AC_CHANNEL);	
	ac_interrupts_enable(C_BEMF_AC_CHANNEL);	
}

void bldc_disable_bemf_int()
{
	ac_interrupt_disable(A_BEMF_AC_CHANNEL);
	ac_interrupt_disable(B_BEMF_AC_CHANNEL);
	ac_interrupt_disable(C_BEMF_AC_CHANNEL);
}

/***********************************************/
/********************_bldc.h********************/
/***********************************************/
void _bldc_ac_bemf_int_handler()
{
	_bldc_next_step();
	ac_clear_int_flag(A_BEMF_AC_CHANNEL);
	ac_clear_int_flag(B_BEMF_AC_CHANNEL);
	ac_clear_int_flag(C_BEMF_AC_CHANNEL);
}

void _bldc_current_limit_int_handler()
{
	io_out_low(GATE_DRIVERS_port, A_LOW_pin | B_LOW_pin | C_LOW_pin);	
	
	while (adc_get_result() > ADC_WINDOW_HIGH)
	{
		while (adc_get_result_rdy_flag() == 0){}
	}
	
	adc_clear_int_flags();
}

void _bldc_input_pwm_handler()
{
	uint16_t current_val = tcb_get_cmp(&TCB2);												//gets the raw current PWM in value.
	int32_t diff = current_val - _bldc_initial_input_pwm_val;								//finds the difference between the "0" value and current value.
	int32_t pwm_cmp_val = (((diff + 6379) * (0 + _bldc_output_pwm_top)) / (0 + 6379));	//maps the difference in input value to a value that can be passed to the output PWM timer.
	
	if (pwm_cmp_val < (_bldc_output_pwm_top - 30))
	{
		if (bldc_status.is_moving == 1)
		{
			bldc_set_duty_cycle(pwm_cmp_val);
			return;	
		}
		else
		{
			bldc_startup();
			bldc_set_duty_cycle(pwm_cmp_val);
			bldc_status.is_moving = 1;
			return;
		}
	}
	bldc_status.is_moving = 0;
	bldc_set_duty_cycle(_bldc_output_pwm_top);
}

void bldc_set_duty_cycle(uint16_t cmp_val)
{
	tca_single_set_cmp0(&TCA0, cmp_val);						//set duty cycle.
	tca_single_set_cmp1(&TCA0, cmp_val);						//set duty cycle.
	tca_single_set_cmp2(&TCA0, cmp_val);						//set duty cycle.	
}


void _bldc_step_one()
{
	/*a low, b high, b low, c high off*/	
	/*a high on, c low on*/	
	io_out_low(A_LOW);
	io_out_low(B_LOW);
	io_out_high(C_LOW);
	
	tca_single_dis_cmp(&TCA0, B_HIGH_CMP_bm | C_HIGH_CMP_bm);
	tca_single_en_cmp(&TCA0, A_HIGH_CMP_bm);
	
	ac_interrupts_enable(B_BEMF_AC_CHANNEL);
	ac_interrupt_disable(A_BEMF_AC_CHANNEL);
	ac_interrupt_disable(C_BEMF_AC_CHANNEL);
}

void _bldc_step_two()
{
	/*a low, a high, b low, c high off*/	
	/*b high on, c low on*/	
	io_out_low(A_LOW);
	io_out_low(B_LOW);
	io_out_high(C_LOW);
	
	tca_single_dis_cmp(&TCA0, A_HIGH_CMP_bm | C_HIGH_CMP_bm);
	tca_single_en_cmp(&TCA0, B_HIGH_CMP_bm);
	
	ac_interrupts_enable(A_BEMF_AC_CHANNEL);
	ac_interrupt_disable(B_BEMF_AC_CHANNEL);
	ac_interrupt_disable(C_BEMF_AC_CHANNEL);
}

void _bldc_step_three()
{
	/*a high, b low, c high, c low off*/	
	/*b high on, a low on*/	
	io_out_low(C_LOW);
	io_out_low(B_LOW);
	io_out_high(A_LOW);
	
	tca_single_dis_cmp(&TCA0, A_HIGH_CMP_bm | C_HIGH_CMP_bm);
	tca_single_en_cmp(&TCA0, B_HIGH_CMP_bm);	
	
	ac_interrupts_enable(C_BEMF_AC_CHANNEL);
	ac_interrupt_disable(B_BEMF_AC_CHANNEL);
	ac_interrupt_disable(A_BEMF_AC_CHANNEL);
}

void _bldc_step_four()
{
	/*a high, b high, b low, c low off*/
	/*c high on, a low on*/	
	io_out_low(C_LOW);
	io_out_low(B_LOW);
	io_out_high(A_LOW);
	
	tca_single_dis_cmp(&TCA0, A_HIGH_CMP_bm | B_HIGH_CMP_bm);
	tca_single_en_cmp(&TCA0, C_HIGH_CMP_bm);	

	ac_interrupts_enable(B_BEMF_AC_CHANNEL);
	ac_interrupt_disable(C_BEMF_AC_CHANNEL);
	ac_interrupt_disable(A_BEMF_AC_CHANNEL);
}

void _bldc_step_five()
{
	/*a high, a low, b high, c low off*/	
	/*c high on, b low on.*/
	io_out_low(C_LOW);
	io_out_low(A_LOW);
	io_out_high(B_LOW);
	
	tca_single_dis_cmp(&TCA0, A_HIGH_CMP_bm | B_HIGH_CMP_bm);
	tca_single_en_cmp(&TCA0, C_HIGH_CMP_bm);	

	ac_interrupts_enable(A_BEMF_AC_CHANNEL);
	ac_interrupt_disable(C_BEMF_AC_CHANNEL);
	ac_interrupt_disable(B_BEMF_AC_CHANNEL);
}

void _bldc_step_six()
{
	/*a low, b high, c high, c low off*/
	/*a high on, b low on*/	
	io_out_low(C_LOW);
	io_out_low(A_LOW);
	io_out_high(B_LOW);
	
	tca_single_dis_cmp(&TCA0, C_HIGH_CMP_bm | B_HIGH_CMP_bm);
	tca_single_en_cmp(&TCA0, A_HIGH_CMP_bm);
	
	ac_interrupts_enable(C_BEMF_AC_CHANNEL);
	ac_interrupt_disable(B_BEMF_AC_CHANNEL);
	ac_interrupt_disable(A_BEMF_AC_CHANNEL);
}

void _bldc_next_step()
{
	if (_bldc_current_step == 5)
	{
		_bldc_current_step = 0;
	}
	_bldc_step_arr[_bldc_current_step]();
	_bldc_current_step++;
}