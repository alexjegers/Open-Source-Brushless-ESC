/*
 * io.c
 *
 * Created: 8/19/2023 8:24:42 PM
 *  Author: AJ992
 */ 
#include "io.h"

io_int_handlers_t io_int_handlers;


ISR(PORTA_PORT_vect)
{
	if (io_int_handlers.porta_handler != NULL)
	{
		io_int_handlers.porta_handler();	
	}
}

ISR(PORTC_PORT_vect)
{
	if (io_int_handlers.portc_handler != NULL)
	{
		io_int_handlers.portc_handler();
	}
}

ISR(PORTD_PORT_vect)
{
	if (io_int_handlers.portd_handler != NULL)
	{
		io_int_handlers.portd_handler();
	}
}

ISR(PORTF_PORT_vect)
{
	if (io_int_handlers.portf_handler != NULL)
	{
		io_int_handlers.portf_handler();
	}
}

void io_data_dir_out(PORT_t* port, uint8_t pins)
{
	port->DIRSET = pins;
}

void io_data_dir_in(PORT_t* port, uint8_t pins)
{
	port->DIRCLR = pins;
}

void io_out_high(PORT_t* port, uint8_t pins)
{
	port->OUTSET = pins;
}

void io_out_low(PORT_t* port, uint8_t pins)
{
	port->OUTCLR = pins;
}

void io_out_tgl(PORT_t* port, uint8_t pins)
{
	port->OUTTGL = pins;
}

uint8_t io_get_out_reg(PORT_t* port)
{
	return port->OUT;
}

uint8_t io_read(PORT_t* port)
{
	return port->IN;
}

uint8_t io_int_flags(PORT_t* port)
{
	return port->INTFLAGS;
}

void io_clear_int_flags(PORT_t* port)
{
	port->INTFLAGS = 0xFF;
}


void io_invert_enable(PORT_t* port, uint8_t pins)
{
	port->PINCONFIG = PORT_INVEN_bm;
	port->PINCTRLSET = pins;
}

void io_invert_disable(PORT_t* port, uint8_t pins)
{
	port->PINCONFIG = PORT_INVEN_bm;
	port->PINCTRLCLR = pins;
}

void io_pullup_enable(PORT_t* port, uint8_t pins)
{
	port->PINCONFIG = PORT_PULLUPEN_bm;
	port->PINCTRLSET = pins;
}

void io_pullup_disable(PORT_t* port, uint8_t pins)
{
	port->PINCONFIG = PORT_PULLUPEN_bm;
	port->PINCTRLSET = pins;
}

void io_interrupt_rising(PORT_t* port, uint8_t pins)
{	
	port->PINCONFIG = PORT_ISC_RISING_gc;
	port->PINCTRLSET = pins;	
}

void io_interrupt_falling(PORT_t* port, uint8_t pins)
{
	port->PINCONFIG = PORT_ISC_FALLING_gc;
	port->PINCTRLSET = pins;	
}

void io_interrupt_edge(PORT_t* port, uint8_t pins)
{
	port->PINCONFIG = PORT_ISC_BOTHEDGES_gc;
	port->PINCTRLSET = pins;	
}

void io_interrupt_disable(PORT_t* port, uint8_t pins)
{
	port->PINCONFIG = PORT_ISC_INTDISABLE_gc;
	port->PINCTRLSET = pins;	
}

void io_input_disable(PORT_t* port, uint8_t pins)
{
	port->PINCONFIG = PORT_ISC_INPUT_DISABLE_gc;
	port->PINCTRLSET = pins;	
}

void io_interrupt_low(PORT_t* port, uint8_t pins)
{
	port->PINCONFIG = PORT_ISC_LEVEL_gc;
	port->PINCTRLSET = pins;	
}


/*Setters for port interrupts.*/
void io_set_porta_handler(void (*func)())
{
	io_int_handlers.porta_handler = func;
}

void io_set_portc_handler(void (*func)())
{
	io_int_handlers.portc_handler = func;
}

void io_set_portd_handler(void (*func)())
{
	io_int_handlers.portd_handler = func;
}

void io_set_portf_handler(void (*func)())
{
	io_int_handlers.portf_handler = func;
}