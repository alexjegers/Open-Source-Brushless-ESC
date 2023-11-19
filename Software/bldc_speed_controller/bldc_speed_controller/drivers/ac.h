/*
 * ac.h
 *
 * Created: 8/19/2023 8:26:37 PM
 *  Author: AJ992
 */ 


#ifndef AC_H_
#define AC_H_

#include <avr/io.h>



typedef struct ac_int_handler_t
{
	void (*ac0_handler)();
	void (*ac1_handler)();
	void (*ac2_handler)();	
}ac_int_handler_t;

void ac_enable(AC_t* ac);								//enables the peripheral.
void ac_disable(AC_t* ac);								//disables the peripheral.
void ac_output_pad_enable(AC_t* ac);					//enables output to the output pin.
void ac_output_pad_disable(AC_t* ac);					//disables output to the output pin.
void ac_set_power_mode(AC_t* ac, uint8_t power);		//set the power mode.
void ac_set_hysteresis_mode(AC_t* ac, uint8_t hysmode);	//set the hysteresis to none, low, med, or high.
void ac_window_selection(AC_t* ac, uint8_t winsel);		//used to enable window mode.
void ac_mux_pos_input(AC_t* ac, uint8_t muxpos);		//AINP(0-3).
void ac_mux_neg_input(AC_t* ac, uint8_t muxneg);		//AINN(0-2) or DACREF.
void ac_initial_value(AC_t* ac, uint8_t initval);		//sets the initial output value.
void ac_invert_out_enable(AC_t* ac);					//enables an inverted output.
void ac_invert_out_disable(AC_t* ac);					//disables the inverted output (default).					
void ac_set_dacref(AC_t* ac, uint8_t dacref);			//Vdacref = (DACREF / 256) * Vref
void ac_interrupt_mode(AC_t* ac, uint8_t intmode);		//sets the interrupts mode when operating with a single comparator.
void ac_interrupts_enable(AC_t* ac);					//enables interrupt.
void ac_interrupt_disable(AC_t* ac);					//disable interrupts.
uint8_t ac_window_state(AC_t* ac);						//returns the state of the window if window mode is enabled.
uint8_t ac_compare_state(AC_t* ac);						//returns the value of the comparator.
uint8_t ac_int_flag(AC_t* ac);							//returns the value of the interrupt flag.
void ac_clear_int_flag(AC_t* ac);						//clears the interrupts flag.

/*Setters for port interrupts.*/
void ac_set_int_handler(AC_t* ac, void* func);

#endif /* AC_H_ */