/*
 * clkctrl.h
 *
 * Created: 8/19/2023 8:26:47 PM
 *  Author: AJ992
 */ 


#ifndef CLKCTRL_H_
#define CLKCTRL_H_

#define MCLK_SPEED					16000000
#define CLK_PER						MCLK_SPEED

#include <avr/io.h>

void clkctrl_mclk_src(uint8_t clksel);					//sets the source for the main clock.
void clkctrl_mclk_out_en();								//enables the main clock out pin (PA7).
void clkctrl_mclk_out_dis();							//disables the main clock out pin (PA7).
void clkctrl_mclk_prescale_dis();						//disables main clock prescaler.
void clkctrl_mclk_prescale_en(uint8_t pdiv);			//enables main clock prescaler set to CLKCTRL_PDIVxxx
uint8_t clkctrl_mclk_status();							//returns MCLKSTATUS.
void clkctrl_internal_osc_freq(uint8_t frqsel);			//sets frequency of internal high speed oscillator. use CLKCTRL_FREQSEL_xxx
void clkctrl_internal_osc_en_stdby();					//enables run in standby mode for the internal high speed oscillator.
void clkctrl_internal_osc_dis_stdby();					//disables run in standby mode for the internal oscillator.
void clkctrl_32k_osc_en_stdby();						//enables run in standby mode for the internal 32kHz oscillator.
void clkctrl_32k_osc_dis_stdby();						//disables run in standby mode for the internal 32kHz oscillator.


#endif /* CLKCTRL_H_ */