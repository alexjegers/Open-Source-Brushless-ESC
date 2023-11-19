/*
 * vref.c
 *
 * Created: 10/18/2023 8:00:12 PM
 *  Author: awjpp
 */ 


#include "vref.h"

void vref_set_adc0ref(uint8_t refsel)
{
	VREF.ADC0REF &= (1 << 7);			//clear the bits.
	VREF.ADC0REF = refsel;
}
void vref_adc0ref_always_on(bool enable)
{
	VREF.ADC0REF &= (0x7);				//clear the bit.
	VREF.ADC0REF |= (enable << 7);
}

uint16_t vref_get_adc0ref()
{
	switch (VREF.ADC0REF)
	{
		case VREF_REFSEL_1V024_gc:
		{
			return 1024;
		}
		case VREF_REFSEL_2V048_gc:
		{
			return 2048;
		}
		case VREF_REFSEL_4V096_gc:
		{
			return 4096;
		}
		case VREF_REFSEL_2V500_gc:
		{
			return 2500;
		}
		default:
		{
			return VREF.ADC0REF;
		}
	}
}

void vref_set_dac0ref(uint8_t refsel)
{
	VREF.DAC0REF &= (1 << 7);			//clear the bits.
	VREF.DAC0REF = refsel;	
}
void vref_dac0ref_always_on(bool enable)
{
	VREF.DAC0REF &= (0x7);				//clear the bit.
	VREF.DAC0REF |= (enable << 7);	
}

void vref_set_acref(uint8_t refsel)
{
	VREF.ACREF &= (1 << 7);			//clear the bits.
	VREF.ACREF = refsel;	
}
void vref_acref_always_on(bool enable)
{
	VREF.DAC0REF &= (0x7);				//clear the bit.
	VREF.DAC0REF |= (enable << 7);	
}