/*
 * uart.c
 *
 * Created: 8/19/2023 8:26:19 PM
 *  Author: AJ992
 */ 
#include "uart.h"
#include "clkctrl.h"

usart_int_handlers_struct* usart_int_handlers_p;

ISR(USART0_DRE_vect)
{
	if (usart_int_handlers_p == NULL)
	{
		return;
	} 
	if (usart_int_handlers_p->usart0_dre_handler != NULL)
	{
		usart_int_handlers_p->usart0_dre_handler();
	} 
	return;
}

ISR(USART0_RXC_vect)
{
	if (usart_int_handlers_p == NULL)
	{
		return;
	} 
	if (usart_int_handlers_p->usart0_rxc_handler != NULL)
	{
		usart_int_handlers_p->usart0_rxc_handler();
	} 
	return;
}

ISR(USART0_TXC_vect)
{
	if (usart_int_handlers_p == NULL)
	{
		return;
	} 
	if (usart_int_handlers_p->usart0_txc_handler != NULL)
	{
		usart_int_handlers_p->usart0_txc_handler();
	} 
	return;
}

ISR(USART1_DRE_vect)
{
	if (usart_int_handlers_p == NULL)
	{
		return;
	}
	if (usart_int_handlers_p->usart1_dre_handler != NULL)
	{
		usart_int_handlers_p->usart1_dre_handler();
	}
	return;
}

ISR(USART1_RXC_vect)
{
	if (usart_int_handlers_p == NULL)
	{
		return;
	}
	if (usart_int_handlers_p->usart1_rxc_handler != NULL)
	{
		usart_int_handlers_p->usart1_rxc_handler();
	}
	return;
}

ISR(USART1_TXC_vect)
{
	if (usart_int_handlers_p == NULL)
	{
		return;
	}
	if (usart_int_handlers_p->usart1_txc_handler != NULL)
	{
		usart_int_handlers_p->usart1_txc_handler();
	}
	return;
}

ISR(USART2_DRE_vect)
{
	if (usart_int_handlers_p == NULL)
	{
		return;
	}
	if (usart_int_handlers_p->usart2_dre_handler != NULL)
	{
		usart_int_handlers_p->usart2_dre_handler();
	}
	return;
}

ISR(USART2_RXC_vect)
{
	if (usart_int_handlers_p == NULL)
	{
		return;
	}
	if (usart_int_handlers_p->usart2_rxc_handler != NULL)
	{
		usart_int_handlers_p->usart2_rxc_handler();
	}
	return;
}

ISR(USART2_TXC_vect)
{
	if (usart_int_handlers_p == NULL)
	{
		return;
	}
	if (usart_int_handlers_p->usart2_txc_handler != NULL)
	{
		usart_int_handlers_p->usart2_txc_handler();
	}
	return;
}

void usart_enable(USART_t* usart)
{
	usart->CTRLB = (USART_RXEN_bm						//enable receiver.
					| USART_TXEN_bm						//enable transmitter.
					| USART_SFDEN_bm					//enable start of frame detection
					| USART_RXMODE_NORMAL_gc);			//receive mode, normal.
	usart->CTRLC = (USART_CMODE_ASYNCHRONOUS_gc			//async mode.
					| USART_PMODE_DISABLED_gc			//parity disabled.
					| USART_SBMODE_1BIT_gc				//1 stop bit.
					| USART_CHSIZE_8BIT_gc);			//8 bit data transmissions.
}

void usart_disable(USART_t* usart)
{
	usart->CTRLB &= ~(USART_RXEN_bm | USART_TXEN_bm);	//disable receiver and transmitter.
}

void usart_set_baud(USART_t* usart, uint32_t baud_rate)
{
	uint32_t baud_reg = (64 * CLK_PER) / (16 * baud_rate);
	usart->BAUD = (uint16_t)baud_reg;
}

void usart_write(USART_t* usart, uint8_t data)
{
	usart->TXDATAL = data;
}

uint8_t usart_read(USART_t* usart)
{
	return usart->RXDATAL;
}

uint8_t usart_status(USART_t* usart)
{
	return usart->STATUS;
}

void usart_enable_int(USART_t* usart, uint8_t usart_xxxie)
{
	usart->CTRLA |= usart_xxxie;
}

void usart_disable_int(USART_t* usart, uint8_t usart_xxxie)
{
	usart->CTRLA &= ~(usart_xxxie);
}

void usart_clear_int_flags(USART_t* usart)
{
	usart->STATUS = 0xFF;
}

void usart_dbgrun(USART_t* usart, bool enable)
{
	usart->DBGCTRL = enable;
}