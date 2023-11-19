/*
 * timers.h
 *
 * Created: 8/19/2023 8:27:22 PM
 *  Author: AJ992
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

#include <avr/io.h>
#include <stdbool.h>
#include "clkctrl.h"

void tca_enable_split_mode(TCA_t* tca);					//enables split mode for type a timer.
void tca_mclk_prescaler(TCA_t* tca, uint8_t clksel);	//prescales the main clock (main clock has to be the source) (use TCA_CLKSEL_xxx).
void tca_enable(TCA_t* tca);							//enables a tca instance.
void tca_disable(TCA_t* tca);							//disables a tca instance.
void tca_dbgrun(TCA_t* tca, bool run_in_debug);			//run_in_debug = true timer will run in debug, false it will not.


void tca_single_set_mode(TCA_t* tca, uint8_t wgmode);	//sets the operational mode of the single timer (singleslope for standard pwm).
void tca_single_en_cmp(TCA_t* tca, uint8_t cmpxen);		//enables the compare channel, overrides the port output for corresponding WOn pin.
void tca_single_dis_cmp(TCA_t* tca, uint8_t cmpxen);	//disables the wave output(s).
void tca_single_tgl_cmp(TCA_t* tca, uint8_t cmpxen);	//toggles a wave output(s).
void tca_single_set_cnt(TCA_t* tca, uint16_t cnt);		//sets the count.
uint16_t tca_single_get_cnt(TCA_t* tca);				//returns the count.
uint16_t tca_single_get_per(TCA_t* tca);				//returns the period (TOP) value. This is used for duty cycle.
void tca_single_set_per(TCA_t* tca, uint16_t per);		//sets period which is the TOP value. This is used for duty cycle.
void tca_single_set_cmp0(TCA_t* TCA, uint16_t cmp);
void tca_single_set_cmp1(TCA_t* TCA, uint16_t cmp);
void tca_single_set_cmp2(TCA_t* TCA, uint16_t cmp);

void tca_split_en_cmp(TCA_t* tca, uint8_t cmpxen);		//enables the compare channel, overrides the port output for corresponding WOn pin.
void tca_split_dis_cmp(TCA_t* tca, uint8_t cmpxen);		//disables the wave output(s).
void tca_split_tgl_cmp(TCA_t* tca, uint8_t cmpxen);		//toggles a wave output(s).
void tca_split_set_lcnt(TCA_t* tca, uint8_t cnt);		//sets the low count byte.
void tca_split_set_hcnt(TCA_t* tca, uint8_t cnt);		//sets the high count byte.
uint8_t tca_split_get_lcnt(TCA_t* tca);					//returns the low count.
uint8_t tca_split_get_hcnt(TCA_t* tca);					//returns the high count.
void tca_split_set_lper(TCA_t* tca, uint8_t per);		//sets low period which is the TOP value.
void tca_split_set_hper(TCA_t* tca, uint8_t per);		//same as above but for the high channel.
void tca_split_set_lcmp0(TCA_t* tca, uint8_t cmp);
void tca_split_set_lcmp1(TCA_t* tca, uint8_t cmp);
void tca_split_set_lcmp2(TCA_t* tca, uint8_t cmp);
void tca_split_set_hcmp0(TCA_t* tca, uint8_t cmp);
void tca_split_set_hcmp1(TCA_t* tca, uint8_t cmp);
void tca_split_set_hcmp2(TCA_t* tca, uint8_t cmp);


#endif /* TIMERS_H_ */