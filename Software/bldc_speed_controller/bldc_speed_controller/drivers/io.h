/*
 * io.h
 *
 * Created: 8/19/2023 8:26:29 PM
 *  Author: AJ992
 */ 


#ifndef IO_H_
#define IO_H_

#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

/*Function pointers for interrupts.*/	
typedef struct io_int_handler_t
{
	void (*porta_handler)();
	void (*portc_handler)();
	void (*portd_handler)();
	void (*portf_handler)();
}io_int_handlers_t;
	
/*General register control for port.*/
void io_data_dir_out(PORT_t* port, uint8_t pins);								//sets pin as an output pin.
void io_data_dir_in(PORT_t* port, uint8_t pins);									//sets pin as an input.
void io_out_high(PORT_t* port, uint8_t pins);									//drives pin high.
void io_out_low(PORT_t* port, uint8_t pins);										//drives pin low.
void io_out_tgl(PORT_t* port, uint8_t pins);										//toggles pin output.
uint8_t io_get_out_reg(PORT_t* port);											//returns the "OUT" register.
uint8_t io_read(PORT_t* port);													//returns the voltage level on all pins of a port.
uint8_t io_int_flags(PORT_t* port);												//returns the interrupt flags of a port.
void io_clear_int_flags(PORT_t* port);											//clears the interrupt flags of a port.
void io_invert_enable(PORT_t* port, uint8_t pins);								//enables inverted io pin.
void io_invert_disable(PORT_t* port, uint8_t pins);								//disables inverted io pin (default state).
void io_pullup_enable(PORT_t* port, uint8_t pins);								//enables pullup resistor.
void io_pullup_disable(PORT_t* port, uint8_t pins);								//disables pullup resistor.
void io_interrupt_rising(PORT_t* port, uint8_t pins);							//enables interrupt on rising edge.
void io_interrupt_falling(PORT_t* port, uint8_t pins);							//enables interrupt on falling edge.
void io_interrupt_edge(PORT_t* port, uint8_t pins);								//enables interrupt on both rising and falling edge.
void io_interrupt_disable(PORT_t* port, uint8_t pins);							//disables interrupts.
void io_input_disable(PORT_t* port, uint8_t pins);								//disables input buffer.
void io_interrupt_low(PORT_t* port, uint8_t pins);								//enables interrupt on a low level.

/*Setters for port interrupts.*/
void io_set_porta_handler(void (*func)());
void io_set_portc_handler(void (*func)());
void io_set_portd_handler(void (*func)());
void io_set_portf_handler(void (*func)());


#endif /* IO_H_ */