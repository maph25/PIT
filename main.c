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
/**#define DELAY 0.01785F
 * #define DELAY 0.00050F */

uint8 InterruptStatus = FALSE;

int main(void) {


	/**GPIO_pinControlRegisterType pinControlRegisterPORTD = GPIO_MUX1;*/

	GPIO_clock_gating(GPIO_D);
	GPIO_pin_control_register(GPIO_D,BIT0, *GPIO_pin_control_register);
	GPIO_data_direction_pin(GPIO_D,GPIO_OUTPUT,BIT0);
	GPIO_toogle_pin(GPIO_D,BIT0);
	PIT_clock_gating();
	NVIC_enableInterruptAndPriotity(PIT_CH0_IRQ, PRIORITY_10);
	EnableInterrupts;

    while(1) {
    	GPIO_toogle_pin(GPIO_D,BIT0);
    	InterruptStatus = PIT_get_interrupt_status();
		PIT_delay(PIT_0,SYSTEM_CLOCK,DELAY);
		while(FALSE == InterruptStatus);
		GPIO_toogle_pin(GPIO_D,BIT0);
		PIT_clear();
		PIT_delay(PIT_0,SYSTEM_CLOCK,DELAY);
		InterruptStatus = PIT_get_interrupt_status();
		while(FALSE == InterruptStatus);
    }
    return 0 ;
}
