/*
 * adc.h
 *
 * Created: 10/19/2023 9:20:12 PM
 *  Author: awjpp
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <stdbool.h>


typedef struct adc_int_handler_t
{
	void (*adc0_wcmp_handler)();
	void (*adc0_resrdy_handler)();
}adc_int_handler_t;


void adc_enable();
void adc_disable();
void adc_set_conversion_mode(uint8_t convmode);		//single ended (0) or differential mode (1).
void adc_set_resolution(uint8_t ressel);			//sets the resolution.
void adc_free_running(bool freerun);				//true for free run mode, false for not free run mode.
void adc_set_sample_number(uint8_t sampnum);		//sets the number of sample to be accumulated, 0 for none, otherwise ADC_SAMPNUM_xxx.
void adc_set_clk_prescaler(uint8_t presc);			//sets the prescaler division factor from clk_per, minimum ADC_PRESC_DIV2_gc.
void adc_set_init_delay(uint8_t initdly);			//sets the amount of clock cycles to delay upon initialization.
void adc_set_sample_delay(uint8_t num_clk_cycles);	//sets the amount of clock cycles to delay between samples, max 15.
void adc_enable_window_mode(uint8_t wincm,			//enables window mode, type of window mode with wincm,
							uint16_t winlt, uint16_t winht);	//and sets the bounds of the window with winlt and winht.
void adc_disable_window_mode();						//sets the adc to no window comparision mode (default).
void adc_set_sample_length(uint8_t samplen);		//number of adc clock cycles to sample for (default is 2).
void adc_set_pos_input(uint8_t muxpos);				//sets the positive input of the adc channel.
void adc_set_neg_input(uint8_t muxneg);				//sets the negative input of the adc channel (usually gnd).
void adc_start_conversion();							//self explanatory.
void adc_stop_conversion();							//self explanatory.
void adc_enable_event_input();						//enables an input event as the trigger for starting a conversion.
void adc_disable_event_input();						//disables the ability for an input event to trigger a conversion.
void adc_enable_window_int();
void adc_disable_window_int();
void adc_enable_result_rdy_int();
void adc_disable_result_rdy_int();
void adc_clear_int_flags();
void adc_run_in_debug(bool enable);					//true to enable, false to disable.
uint8_t adc_get_result_rdy_flag();					//returns the result ready status flag.
uint16_t adc_get_result();							//returns the result register.

void adc_set_int_handler(void* func, uint8_t adc_vect_num);

#endif /* ADC_H_ */