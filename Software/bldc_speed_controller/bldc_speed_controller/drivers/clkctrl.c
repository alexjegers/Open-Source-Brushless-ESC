/*
 * clkctrl.c
 *
 * Created: 8/19/2023 8:25:31 PM
 *  Author: AJ992
 */ 

#include "clkctrl.h"
#include "cpu.h"

void clkctrl_mclk_src(uint8_t clksel)
{
	uint8_t reg = CLKCTRL.MCLKCTRLA & 0xF0;
	CPU_CCP_IOREG;
	CLKCTRL.MCLKCTRLA = reg;					//Clear the clksel bits.
	
	reg = CLKCTRL.MCLKCTRLA | clksel;
	CPU_CCP_IOREG;
	CLKCTRL.MCLKCTRLA = reg;
}

void clkctrl_mclk_out_en()
{
	uint8_t reg = CLKCTRL.MCLKCTRLA | CLKCTRL_CLKOUT_bm;
	CPU_CCP_IOREG;
	CLKCTRL.MCLKCTRLA = reg;
}

void clkctrl_mclk_out_dis()
{
	CPU_CCP_IOREG;
	CLKCTRL.MCLKCTRLA &= ~(CLKCTRL_CLKOUT_bm);
}

void clkctrl_mclk_prescale_dis()
{
	CPU_CCP_IOREG;
	CLKCTRL.MCLKCTRLB &= ~(CLKCTRL_PEN_bm);
}

void clkctrl_mclk_prescale_en(uint8_t pdiv)
{
	uint8_t reg = pdiv | CLKCTRL_PEN_bm;
	CPU_CCP_IOREG;
	CLKCTRL.MCLKCTRLB = 0;
	CPU_CCP_IOREG;
	CLKCTRL.MCLKCTRLB = reg;
}

uint8_t clkctrl_mclk_status()
{
	return CLKCTRL.MCLKSTATUS;
}

void clkctrl_internal_osc_freq(uint8_t frqsel)
{
	uint8_t reg = CLKCTRL.OSCHFCTRLA & (CLKCTRL_RUNSTDBY_bm | CLKCTRL_AUTOTUNE_bm);
	CPU_CCP_IOREG;
	CLKCTRL.OSCHFCTRLA = reg;														//clears the frqsel bits.
	CPU_CCP_IOREG;
	CLKCTRL.OSCHFCTRLA |= frqsel;
	
	while ((clkctrl_mclk_status() & CLKCTRL_OSCHFS_bm) == 0){}
}

void clkctrl_internal_osc_en_stdby()
{
	CLKCTRL.OSCHFCTRLA |= CLKCTRL_RUNSTDBY_bm;
}

void clkctrl_internal_osc_dis_stdby()
{
	CPU_CCP_IOREG;
	CLKCTRL.OSCHFCTRLA &= ~(CLKCTRL_RUNSTDBY_bm);	
}
