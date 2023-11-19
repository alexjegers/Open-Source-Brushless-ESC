/*
 * vref.h
 *
 * Created: 10/18/2023 7:59:26 PM
 *  Author: awjpp
 */ 


#ifndef VREF_H_
#define VREF_H_

#include <stdbool.h>
#include <avr/io.h>

void vref_set_adc0ref(uint8_t refsel);
void vref_adc0ref_always_on(bool enable);
uint16_t vref_get_adc0ref();					//returns the current vref voltage * 1000 (to avoid using floating point) or
												//returns 0x5 for VDD, or 0x6 for the VREFA pin.

void vref_set_dac0ref(uint8_t refsel);
void vref_dac0ref_always_on(bool enable);

void vref_set_acref(uint8_t refsel);
void vref_acref_always_on(bool enable);


#endif /* VREF_H_ */