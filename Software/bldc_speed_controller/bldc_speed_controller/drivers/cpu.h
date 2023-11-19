/*
 * cpu.h
 *
 * Created: 8/19/2023 8:26:59 PM
 *  Author: AJ992
 */ 


#ifndef CPUINT_H_
#define CPUINT_H_

#define CPU_CCP_IOREG					CCP = CCP_IOREG_gc;
#define CPU_CCP_SPM						CCP = CCP_SPM_gc;

#include <avr/io.h>

uint8_t cpuint_status();				//returns CPUINT_xxxxxx_bm.
void cpu_enable_global_int();			//writes to sreg to enable global interrupts.
void cpu_disable_global_int();			//clears global interrupt enable bit.

void cpuint_enable_round_robin_int();	//enables round robin interrupt scheduling.


#endif /* CPUINT_H_ */