/*
 * PIT.c
 *
 *  Created on: Sep 11, 2018
 *      Author: LuisFernando
 */

#include "MK64F12.h"
#include "PIT.h"

uint32 decToHexa(uint32 value)
{
	uint32 hex = 0;
	uint32 base = 0;
	for(;value;value /= 10, base *= 16)
		hex += (value%10) * base;
	return hex;
}

void PIT_delay(PIT_Timer_t pitTimer,float systemClock ,float period)
{
	/**Es necesario hacer un cast para pasar del numero float a entero, y de ahi a hexa**/
	float clockPeriod = 1/systemClock;
	float cycles = (period/clockPeriod) - 1;
	cycles = (uint32)cycles;
	PIT->CHANNEL[pitTimer].LDVAL = decToHexa(cycles);
	PIT->CHANNEL[pitTimer].TCTRL |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;
	// Enable interrupt registers ISER and ICPR
	NVIC_EnableIRQ(PIT0_IRQn);
}

void PIT_clockGating(void)
{
	/**
	 * Enable PIT clock**/
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
	/**
	* Enable portD clock**/
	GPIO_clockGating(GPIO_D);
	// Turn on PIT
	PIT->MCR = FALSE;
}

uint8 PIT_getIntrStutus(void);

void PIT_clear(void);
