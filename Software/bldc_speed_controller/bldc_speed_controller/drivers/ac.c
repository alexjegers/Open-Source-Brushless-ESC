/*
 * ac.c
 *
 * Created: 8/19/2023 8:25:02 PM
 *  Author: AJ992
 */ 

#include "drivers/ac.h"	
#include <avr/interrupt.h>
#include <stdio.h>

ac_int_handler_t ac_int_handlers;

ISR(AC0_AC_vect)
{
	if (ac_int_handlers.ac0_handler != NULL)
	{
		ac_int_handlers.ac0_handler();
	}
}

ISR(AC1_AC_vect)
{
	if (ac_int_handlers.ac1_handler != NULL)
	{
		ac_int_handlers.ac1_handler();
	}	
}

ISR(AC2_AC_vect)
{
	if (ac_int_handlers.ac2_handler != NULL)
	{
		ac_int_handlers.ac2_handler();
	}	
}

void ac_enable(AC_t* ac)
{
	ac->CTRLA |= AC_ENABLE_bm;
}

void ac_disable(AC_t* ac)
{
	ac->CTRLA &= ~(AC_ENABLE_bm);
}

void ac_output_pad_enable(AC_t* ac)
{
	ac->CTRLA |= AC_OUTEN_bm;
}

void ac_output_pad_disable(AC_t* ac)
{
	ac->CTRLA &= ~(AC_OUTEN_bm);
}

void ac_set_power_mode(AC_t* ac, uint8_t power)
{
	ac->CTRLA &= ~(0x3 << 3);			//clear the bits.
	ac->CTRLA |= power;					
}

void ac_set_hysteresis_mode(AC_t* ac, uint8_t hysmode)
{
	ac->CTRLA &= ~(0x3 << 1);			//clear the bits.
	ac->CTRLA |= hysmode;
}

void ac_window_selection(AC_t* ac, uint8_t winsel)
{
	ac->CTRLB = winsel;
}

void ac_mux_pos_input(AC_t* ac, uint8_t muxpos)
{
	ac->MUXCTRL &= ~(0x3 << 3);			//clear the bits.
	ac->MUXCTRL |= muxpos;
}

void ac_mux_neg_input(AC_t* ac, uint8_t muxneg)
{
	ac->MUXCTRL &= ~(0x3);				//clear the bits.
	ac->MUXCTRL |= muxneg;
}

void ac_initial_value(AC_t* ac, uint8_t initval)
{
	ac->MUXCTRL &= ~(initval);			//clear the bit.
	ac->MUXCTRL |= initval;
}

void ac_invert_out_enable(AC_t* ac)
{
	ac->MUXCTRL |= AC_INVERT_bm;
}

void ac_invert_out_disable(AC_t* ac)
{
	ac->MUXCTRL &= ~(AC_INVERT_bm);
}

void ac_set_dacref(AC_t* ac, uint8_t dacref)
{
	ac->DACREF = dacref;
}

void ac_interrupt_mode(AC_t* ac, uint8_t intmode)
{
	ac->INTCTRL &= 1;				//clear the bits.
	ac->INTCTRL |= intmode;	
}

void ac_interrupts_enable(AC_t* ac)
{
	ac->INTCTRL |= 1;
}

void ac_interrupt_disable(AC_t* ac)
{
	ac->INTCTRL &= ~(1);
}

uint8_t ac_window_state(AC_t* ac)
{
	return ac->STATUS & (0x2 << 6);
}

uint8_t ac_compare_state(AC_t* ac)
{
	return ac->STATUS & (1 << 4);
}

uint8_t ac_int_flag(AC_t* ac)
{
	return ac->STATUS & 1;
}

void ac_clear_int_flag(AC_t* ac)
{
	ac->STATUS = 1;
}

void ac_set_int_handler(AC_t* ac, void* func)
{
	if (ac == &AC0)
	{
		ac_int_handlers.ac0_handler = func;
	}
	else if(ac == &AC1)
	{
		ac_int_handlers.ac1_handler = func;
	}
	else if(ac == &AC2)
	{
		ac_int_handlers.ac2_handler = func;
	}
}