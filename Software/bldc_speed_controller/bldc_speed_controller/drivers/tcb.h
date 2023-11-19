/*
 * tcb.h
 *
 * Created: 8/22/2023 6:13:43 PM
 *  Author: AJ992
 */ 


#ifndef TCB_H_
#define TCB_H_

#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "drivers/clkctrl.h"

typedef struct tcb_int_handler_t
{
	void (*tcb0_handler)();
	void (*tcb1_handler)();
	void (*tcb2_handler)();
}tcb_int_handlers_t;

void tcb_enable(TCB_t* tcb);						//enables a tcb.
void tcb_disable(TCB_t* tcb);						//disables a tcb.
void tcb_clksel(TCB_t* tcb, uint8_t clksel_bm);		//selects clock source for TCBx.
void tcb_runstdby(TCB_t* tcb, bool runstdby);		//true for run in standby, false for dont run in standby.
void tcb_cntmode(TCB_t* tcb, uint8_t cntmode_bm);	//sets the mode of the timer. 		
void tcb_input_filter(TCB_t* tcb, bool filter);		//true to enable filter, false to disable filter.
void tcb_edge_event(TCB_t* tcb, bool edge);			//behavior dependent on tcb mode.
void tcb_input_cap_event(TCB_t* tcb, bool enable);	//true to enable the input capture event, false to disable.
void tcb_overflow_int(TCB_t* tcb, bool enable);		//true enables overflow interrupt, false disables.
void tcb_capture_int(TCB_t* tcb, bool enable);		//true enables interrupt, false disables.
uint8_t tcb_int_flags(TCB_t* tcb);					//returns the interrupt flags.
void tcb_clear_int_flags(TCB_t* tcb);				//clears all interrupt flags.
void tcb_dbgrun(TCB_t* tcb, bool enable);			//true to enable run in debug, flase to disable.
void tcb_set_count(TCB_t* tcb, uint16_t cnt);		//writes to the count register.
uint16_t tcb_get_count(TCB_t* tcb);					//returns the count register.
void tcb_set_cmp(TCB_t* tcb, uint16_t cmp);			//writes to the compare register.
uint16_t tcb_get_cmp(TCB_t* tcb);					//returns the compare register.
void tcb_set_tcb0_handler(void (*func)());
void tcb_set_tcb1_handler(void (*func)());
void tcb_set_tcb2_handler(void (*func)());

#endif /* TCB_H_ */