/*
 * tcb.c
 *
 * Created: 8/22/2023 6:13:51 PM
 *  Author: AJ992
 */ 

#include "tcb.h"

tcb_int_handlers_t tcb_int_handlers;

ISR(TCB0_INT_vect)
{
	if (tcb_int_handlers.tcb0_handler != NULL)
	{
		tcb_int_handlers.tcb0_handler();
	}
}

ISR(TCB1_INT_vect)
{
	if (tcb_int_handlers.tcb1_handler != NULL)
	{
		tcb_int_handlers.tcb1_handler();
	}
}

ISR(TCB2_INT_vect)
{
	if (tcb_int_handlers.tcb2_handler != NULL)
	{
		tcb_int_handlers.tcb2_handler();
	}
}

void tcb_enable(TCB_t* tcb)
{
	tcb->CTRLA |= TCB_ENABLE_bm;
}

void tcb_disable(TCB_t* tcb)
{
	tcb->CTRLA &= ~(TCB_ENABLE_bm);
}

void tcb_clksel(TCB_t* tcb, uint8_t clksel_bm)
{
	/*Clear the clksel bits.*/
	tcb->CTRLA &= ~(TCB_RUNSTDBY_bm |
					TCB_CASCADE_bm |
					TCB_ENABLE_bm);
	tcb->CTRLA |= clksel_bm;
}

void tcb_runstdby(TCB_t* tcb, bool runstdby)
{
	tcb->CTRLA &= ~(TCB_RUNSTDBY_bm);				//clear bit.
	tcb->CTRLA |= (runstdby << TCB_RUNSTDBY_bp);	//set bit.
}

void tcb_cntmode(TCB_t* tcb, uint8_t cntmode_bm)
{
	tcb->CTRLB &= ~(TCB_CASCADE_bm |
					TCB_CCMPINIT_bm |
					TCB_CCMPEN_bm);					//clear bits.
	tcb->CTRLB |= cntmode_bm;						//set bits.
}

void tcb_input_filter(TCB_t* tcb, bool filter)
{
	tcb->EVCTRL &= ~(TCB_FILTER_bm);				//clear bit.
	tcb->EVCTRL |= (filter << TCB_FILTER_bp);		//set bit.
}

void tcb_edge_event(TCB_t* tcb, bool edge)
{
	tcb->EVCTRL &= ~(TCB_EDGE_bm);
	tcb->EVCTRL |= (edge << TCB_EDGE_bp);	
}
	
void tcb_input_cap_event(TCB_t* tcb, bool enable)
{
	tcb->EVCTRL &= ~(TCB_CAPTEI_bm);
	tcb->EVCTRL |= (enable << TCB_CAPTEI_bp);		
}

void tcb_overflow_int(TCB_t* tcb, bool enable)
{
	tcb->INTCTRL &= ~(TCB_OVF_bm);
	tcb->INTCTRL |= (enable << TCB_OVF_bp);
}

void tcb_capture_int(TCB_t* tcb, bool enable)
{
	tcb->INTCTRL &= ~(TCB_CAPT_bm);
	tcb->INTCTRL |= (enable << TCB_CAPT_bp);
}

uint8_t tcb_int_flags(TCB_t* tcb)
{
	return tcb->INTFLAGS;
}

void tcb_clear_int_flags(TCB_t* tcb)
{
	tcb->INTFLAGS = 0xFF;
}

void tcb_dbgrun(TCB_t* tcb, bool enable)
{
	tcb->DBGCTRL = enable;
}
	
void tcb_set_count(TCB_t* tcb, uint16_t cnt)
{
	tcb->CNT = cnt;
}

uint16_t tcb_get_count(TCB_t* tcb)
{
	return tcb->CNT;
}

void tcb_set_cmp(TCB_t* tcb, uint16_t cmp)
{
	tcb->CCMP = cmp;
}

uint16_t tcb_get_cmp(TCB_t* tcb)
{
	return tcb->CCMP;
}

void tcb_set_tcb0_handler(void (*func)())
{
	tcb_int_handlers.tcb0_handler = func;
}

void tcb_set_tcb1_handler(void (*func)())
{
	tcb_int_handlers.tcb1_handler = func;
}

void tcb_set_tcb2_handler(void (*func)())
{
	tcb_int_handlers.tcb2_handler = func;
}