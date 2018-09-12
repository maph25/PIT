/**
 * @file    PIT_Delay.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "PIT.h"
#include "NVIC.h"
#include "Bits.h"
#include "GPIO.h"
#define SYSTEM_CLOCK 21000000
#define DELAY 0.25F



int main(void) {

	uint8 pitIntrStatus = FALSE;
	GPIO_pinControlRegisterType pinControlRegisterPORTD = GPIO_MUX1;

	GPIO_clock_gating(GPIO_D);
	GPIO_pin_control_register(GPIO_D,BIT0,&pinControlRegisterPORTD);
	GPIO_data_direction_pin(GPIO_D,GPIO_OUTPUT,BIT0);
	GPIO_toogle_pin(GPIO_D,BIT0);
	PIT_clockGating();
	NVIC_enableInterruptAndPriotity(PIT_CH0_IRQ, PRIORITY_10);
	EnableInterrupts;

    while(1) {
    	GPIO_toogle_pin(GPIO_D,BIT0);
    	pitIntrStatus = PIT_getIntrStutus();
		PIT_delay(PIT_0,SYSTEM_CLOCK,DELAY);
		while(FALSE == pitIntrStatus);
		GPIO_toogle_pin(GPIO_D,BIT0);
		PIT_clear();
		PIT_delay(PIT_0,SYSTEM_CLOCK,DELAY);
		pitIntrStatus = PIT_getIntrStutus();
		while(FALSE == pitIntrStatus);
    }
    return 0 ;
}
