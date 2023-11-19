/*
 * timers.c
 *
 * Created: 8/19/2023 8:24:54 PM
 *  Author: AJ992
 */ 

#include "tca.h"

void tca_enable_split_mode(TCA_t* tca)
{
	tca->SINGLE.CTRLD = TCA_SPLIT_ENABLE_bm;
}

void tca_mclk_prescaler(TCA_t* tca, uint8_t clksel)
{
	tca->SINGLE.CTRLA &= (TCA_SINGLE_RUNSTDBY_bm | TCA_SINGLE_ENABLE_bm);
	tca->SINGLE.CTRLA |= clksel;
}

void tca_enable(TCA_t* tca)
{
	tca->SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}

void tca_disable(TCA_t* tca)
{
	tca->SINGLE.CTRLA &= ~(TCA_SINGLE_ENABLE_bm);
}



void tca_single_set_mode(TCA_t* tca, uint8_t wgmode)
{
	tca->SINGLE.CTRLB &= ~(0x7);		//clear the bits.
	tca->SINGLE.CTRLB |= wgmode;		//write the mode.
}

void tca_single_en_cmp(TCA_t* tca, uint8_t cmpxen)
{
	tca->SINGLE.CTRLB |= cmpxen;
}

void tca_single_dis_cmp(TCA_t* tca, uint8_t cmpxen)
{
	tca->SINGLE.CTRLB &= ~(cmpxen);
}

void tca_single_tgl_cmp(TCA_t* tca, uint8_t cmpxen)
{
	tca->SINGLE.CTRLB ^= cmpxen;
}

void tca_single_set_cnt(TCA_t* tca, uint16_t cnt)
{
	tca->SINGLE.CNT = cnt;
}

uint16_t tca_single_get_cnt(TCA_t* tca)
{
	return tca->SINGLE.CNT;
}

uint16_t tca_single_get_per(TCA_t* tca)
{
	return tca->SINGLE.PER;
}

void tca_single_set_per(TCA_t* tca, uint16_t per)
{
	tca->SINGLE.PER = per;
}

void tca_single_set_cmp0(TCA_t* TCA, uint16_t cmp)
{
	TCA->SINGLE.CMP0 = cmp;
}

void tca_single_set_cmp1(TCA_t* TCA, uint16_t cmp)
{
	TCA->SINGLE.CMP1 = cmp;
}

void tca_single_set_cmp2(TCA_t* TCA, uint16_t cmp)
{
	TCA->SINGLE.CMP2 = cmp;
}


void tca_split_en_cmp(TCA_t* tca, uint8_t cmpxen)
{
	tca->SPLIT.CTRLB |= cmpxen;
}

void tca_split_dis_cmp(TCA_t* tca, uint8_t cmpxen)
{
	tca->SPLIT.CTRLB &= ~(cmpxen);
}

void tca_split_tgl_cmp(TCA_t* tca, uint8_t cmpxen)
{
	tca->SPLIT.CTRLB ^= cmpxen;
}

void tca_dbgrun(TCA_t* tca, bool run_in_debug)
{
	tca->SINGLE.DBGCTRL = (uint8_t)run_in_debug;
}

void tca_split_set_lcnt(TCA_t* tca, uint8_t cnt)
{
	tca->SPLIT.LCNT = cnt;
}

void tca_split_set_hcnt(TCA_t* tca, uint8_t cnt)
{
	tca->SPLIT.HCNT = cnt;
}

uint8_t tca_split_get_lcnt(TCA_t* tca)
{
	return tca->SPLIT.LCNT;
}

uint8_t tca_split_get_hcnt(TCA_t* tca)
{
	return tca->SPLIT.LCNT;
}

void tca_split_set_lper(TCA_t* tca, uint8_t per)
{
	tca->SPLIT.LPER = per;
}

void tca_split_set_hper(TCA_t* tca, uint8_t per)
{
	tca->SPLIT.HPER = per;
}

void tca_split_set_lcmp0(TCA_t* tca, uint8_t cmp) 
{ 
	tca->SPLIT.LCMP0 = cmp; 
}

void tca_split_set_lcmp1(TCA_t* tca, uint8_t cmp) 
{ 
	tca->SPLIT.LCMP1 = cmp; 
}

void tca_split_set_lcmp2(TCA_t* tca, uint8_t cmp) 
{ 
	tca->SPLIT.LCMP2 = cmp; 
}

void tca_split_set_hcmp0(TCA_t* tca, uint8_t cmp) 
{ 
	tca->SPLIT.HCMP0 = cmp; 
}

void tca_split_set_hcmp1(TCA_t* tca, uint8_t cmp) 
{ 
	tca->SPLIT.HCMP1 = cmp; 
}

void tca_split_set_hcmp2(TCA_t* tca, uint8_t cmp) 
{ 
	tca->SPLIT.HCMP2 = cmp; 
} 
