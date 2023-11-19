/*
 * debug.h
 *
 * Created: 10/17/2023 9:25:36 AM
 *  Author: awjpp
 */ 


#ifndef DEBUG_H_
#define DEBUG_H_

#include <avr/io.h>

#define LED_R				&PORTF, PIN3_bm
#define LED_G				&PORTF, PIN2_bm
#define LED_B				&PORTF, PIN4_bm
#define CLKOUT_PIN			&PORTA, PIN7_bm


void debug_led_on(PORT_t* port, uint8_t pin);									//turns the led to a specific color.
void debug_blink(PORT_t* port, uint8_t pin);									//forever loops blinking a specified led.
void debug_blink_quantity(PORT_t* port, uint8_t pin, uint8_t num_blinks);		//blinks a certain led for 0.5s a certain amount of times.
void debug_led_on_duration(PORT_t* port, uint8_t pin, uint16_t duration_ms);	//turn an led on for a certain duration.


#endif /* DEBUG_H_ */