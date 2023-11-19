/*
 * debug.c
 *
 * Created: 10/17/2023 9:25:46 AM
 *  Author: awjpp
 */ 

#define F_CPU 24000000UL				//needed for delay.h

#include "debug.h"
#include <util/delay.h>
#include "drivers/io.h"

void debug_led_on(PORT_t* port, uint8_t pin)
{
	/*turn off all leds.*/
	io_out_high(LED_G);
	io_out_high(LED_R);
	io_out_high(LED_B);
	
	io_out_low(port, pin);		//turn on specified one.
}

void debug_blink(PORT_t* port, uint8_t pin)
{
	/*turn off all leds.*/
	io_out_high(LED_G);
	io_out_high(LED_R);
	io_out_high(LED_B);
	
	/*blink forever.*/
	while(1)
	{
		io_out_low(port, pin);
		_delay_ms(500);
		io_out_high(port, pin);
		_delay_ms(500);
	}
}

void debug_blink_quantity(PORT_t* port, uint8_t pin, uint8_t num_blinks)
{
	/*turn off all leds.*/
	io_out_high(LED_G);
	io_out_high(LED_R);
	io_out_high(LED_B);
	
	/*blink.*/
	for (int i = 0; i < num_blinks; i++)
	{
		io_out_low(port, pin);
		_delay_ms(500);
		io_out_high(port, pin);
		_delay_ms(500);
	}	
}

void debug_led_on_duration(PORT_t* port, uint8_t pin, uint16_t duration_ms)
{
	/*turn off all leds.*/
	io_out_high(LED_G);
	io_out_high(LED_R);
	io_out_high(LED_B);
	
	io_out_low(port, pin);
	for (int i = 0; i < duration_ms; i++)
	{
		_delay_ms(1);
	}

	/*turn off all leds.*/
	io_out_high(LED_G);
	io_out_high(LED_R);
	io_out_high(LED_B);
	
	
}