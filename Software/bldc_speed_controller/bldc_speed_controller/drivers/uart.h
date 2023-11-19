/*
 * uart.h
 *
 * Created: 8/19/2023 8:27:33 PM
 *  Author: AJ992
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>


typedef struct usart_int_handlers_t
{
	void (*usart0_dre_handler)();
	void (*usart1_dre_handler)();
	void (*usart2_dre_handler)();
	void (*usart0_rxc_handler)();
	void (*usart1_rxc_handler)();
	void (*usart2_rxc_handler)();
	void (*usart0_txc_handler)();
	void (*usart1_txc_handler)();
	void (*usart2_txc_handler)();
}usart_int_handlers_struct;

extern usart_int_handlers_struct* usart_int_handlers_p;

void usart_enable(USART_t* usart);												//enables a usart as a uart module.
void usart_disable(USART_t* usart);												//disables the receiver and transmitter.
void usart_set_baud(USART_t* usart, uint32_t baud_rate);						//set the baud rate
void usart_write(USART_t* usart, uint8_t data);									//writes to the transmit register.
uint8_t usart_read(USART_t* usart);												//returns the receive register.
uint8_t usart_status(USART_t* usart);											//returns the status register.
void usart_enable_int(USART_t* usart, uint8_t usart_xxxie);						//enables an interrupt(s).
void usart_disable_int(USART_t* usart, uint8_t usart_xxxie);					//disables an interrupt(s).
void usart_clear_int_flags(USART_t* usart);										//clears all interrupt flags.
void usart_dbgrun(USART_t* usart, bool enable);									//true for run in debug false for not.
void usart_assign_int_handlers(usart_int_handlers_struct* usart_int_handlers);		//sets the function pointers for interrupt handlers.


#endif /* UART_H_ */