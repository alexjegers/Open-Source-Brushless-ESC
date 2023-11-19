/*
 * adc.c
 *
 * Created: 10/19/2023 9:20:26 PM
 *  Author: awjpp
 */ 
#include "adc.h"
#include <avr/interrupt.h>
#include <stdio.h>


adc_int_handler_t adc_int_handlers;

ISR(ADC0_RESRDY_vect)
{
	if (adc_int_handlers.adc0_resrdy_handler != NULL)
	{
		adc_int_handlers.adc0_resrdy_handler();
	}
}

ISR(ADC0_WCMP_vect)
{
	if (adc_int_handlers.adc0_wcmp_handler != NULL)
	{
		adc_int_handlers.adc0_wcmp_handler();
	}	
}

void adc_enable(ADC_t* adc)
{
	ADC0.CTRLA |= ADC_ENABLE_bm;
}

void adc_disable(ADC_t* adc)
{
	ADC0.CTRLA &= ~(ADC_ENABLE_bm);
}
void adc_set_conversion_mode(uint8_t convmode)
{
	ADC0.CTRLA &= ~(1 << 5);				//clear the bit.
	ADC0.CTRLA |= convmode;
}	

void adc_set_resolution(uint8_t ressel)
{
	ADC0.CTRLA &= ~(0x3 << 2);				//bit clear.
	ADC0.CTRLA |= ressel;
}

void adc_free_running(bool freerun)
{
	ADC0.CTRLA &= ~(1 << 1);				//bit clear.
	ADC0.CTRLA |= (freerun << 1);
}

void adc_set_sample_number(uint8_t sampnum)
{
	ADC0.CTRLB = sampnum;
}

void adc_set_clk_prescaler(uint8_t presc)
{
	ADC0.CTRLC = presc;
}

void adc_set_init_delay(uint8_t initdly)
{
	ADC0.CTRLD &= ~(0x7 << 5);				//bit clear.
	ADC0.CTRLD |= initdly;
}

void adc_set_sample_delay(uint8_t num_clk_cycles)
{
	ADC0.CTRLD &= ~(0x0F);			//bit clear.
	ADC0.CTRLD |= num_clk_cycles;
}

void adc_enable_window_mode(uint8_t wincm,		
uint16_t winlt, uint16_t winht)
{
	ADC0.WINLT = winlt;
	ADC0.WINHT = winht;
	ADC0.CTRLE = wincm;
}	

void adc_disable_window_mode(ADC_t* adc)
{
	ADC0.CTRLE = 0;
}

void adc_set_sample_length(uint8_t samplen)
{
	ADC0.SAMPCTRL = samplen;	
}

void adc_set_pos_input(uint8_t muxpos)
{
	ADC0.MUXPOS = muxpos;
}

void adc_set_neg_input(uint8_t muxneg)
{
	ADC0.MUXNEG = muxneg;
}

void adc_start_conversion(ADC_t* adc)
{
	ADC0.COMMAND = 1;
}

void adc_stop_conversion(ADC_t* adc)
{
	ADC0.COMMAND = (1 << 1);
}

void adc_enable_event_input(ADC_t* adc)
{
	ADC0.EVCTRL = 1;
}

void adc_disable_event_input(ADC_t* adc)
{
	ADC0.EVCTRL = 0;
}

void adc_enable_window_int(ADC_t* adc)
{
	ADC0.INTCTRL |= (1 << 1);
}

void adc_disable_window_int(ADC_t* adc)
{
	ADC0.INTCTRL &= ~(1 << 1);
}

void adc_enable_result_rdy_int(ADC_t* adc)
{
	ADC0.INTCTRL |= 1;
}

void adc_disable_result_rdy_int(ADC_t* adc)
{
	ADC0.INTCTRL &= ~1;
}

void adc_clear_int_flags(ADC_t* adc)
{
	ADC0.INTFLAGS = 0x3;
}

void adc_run_in_debug(bool enable)
{
	ADC0.DBGCTRL = enable;
}

uint16_t adc_get_result(ADC_t* adc)
{
	return ADC0.RES;
}

uint8_t adc_get_result_rdy_flag()
{
	return ADC0.INTFLAGS & ADC_RESRDY_bm;
}

void adc_set_int_handler(void* func, uint8_t adc_vect_num)
{
	switch (adc_vect_num)
	{
	case ADC0_RESRDY_vect_num:
		adc_int_handlers.adc0_resrdy_handler = func;
		return;
	case ADC0_WCMP_vect_num:
		adc_int_handlers.adc0_wcmp_handler = func;
		return;
	}
	
}