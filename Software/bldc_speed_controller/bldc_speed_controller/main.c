/*
 * bldc_speed_controller.c
 *
 * Created: 10/15/2023 10:16:12 AM
 * Author : awjpp
 */ 



#include <avr/io.h>
#include "bldc.h"
#include "debug.h"
#include "drivers/cpu.h"

int main(void)
{
	debug_led_on(LED_R);
	bldc_init_led();
	bldc_init_clk();
	bldc_init_gate_drivers();
	bldc_init_feedback();
	bldc_init_input_pwm();
	bldc_enable_v_gate_drive();
	bldc_init_current_limit();
	
	debug_led_on(LED_G);
	cpu_enable_global_int();
	cpuint_enable_round_robin_int();

    while (1) 
    {
		
    }
}

