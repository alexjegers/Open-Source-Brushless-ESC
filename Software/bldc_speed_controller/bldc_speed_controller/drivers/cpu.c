/*
 * cpu.c
 *
 * Created: 8/19/2023 8:25:42 PM
 *  Author: AJ992
 */ 

#include "cpu.h"

uint8_t cpuint_status()
{
	return CPUINT.STATUS;
}

void cpu_enable_global_int()
{
	CPU_CCP_IOREG;
	SREG |= 0x80;
}

void cpu_disable_global_int()
{
	CPU_CCP_IOREG;
	SREG &= ~(0x80);
}

void cpuint_enable_round_robin_int()
{
	CPU_CCP_IOREG;
	CPUINT.CTRLA |= CPUINT_LVL0RR_bm;
}
