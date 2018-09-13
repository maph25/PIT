/*
 * PIT.c
 *
 *  Created on: Sep 11, 2018
 *      Author: LuisFernando
 */

#include "MK64F12.h"
#include "PIT.h"
#include "GPIO.h"
#include "Bits.h"
#include "NVIC.h"

static uint8 intrFlag = TRUE;

uint32 decToHexa(uint32 value)
{
	uint32 hex = ZERO;
	uint32 base = ZERO;
	for(; value ; value /= TEN, base *= SIXTEEN)
		hex += (value%TEN) * base;
	return hex;
}

void PIT_delay(PIT_Timer_t pitTimer,float systemClock ,float period)
{
	/**Es necesario hacer un cast para pasar del numero float a entero, y de ahi a hexa**/
	float clockPeriod = ONE/systemClock;
	float cycles = (period/clockPeriod) - ONE;
	cycles = (uint32)cycles;
	/**
	* Turn on PIT**/
	PIT->MCR = MCR_ON;
	PIT->CHANNEL[pitTimer].LDVAL = decToHexa(cycles);
	/**
	 * TIE enables interrupts for the timer
	 * TEN starts the timer**/
	PIT->CHANNEL[pitTimer].TCTRL |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;
	intrFlag = FALSE;
}

void PIT_clock_gating(void)
{
	/**
	 * Enable PIT clock
	 * **/
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
}

uint8 PIT_get_interrupt_status(void)
{
	return intrFlag;
}

void PIT_clear(void)
{
	intrFlag = TRUE;
}
/**
 * Funct called from startup_mk64f12.c**/
void PIT0_IRQ_handler(void)
{
	PIT->CHANNEL[PIT_0].TFLG |= PIT_TFLG_TIF_MASK;
	/**
	 * Read control reg for clear PIT flag
	 * **/
	PIT->CHANNEL[PIT_0].TCTRL;
	/**
	 * Enables PIT timer interrupt
	 * **/
	PIT->CHANNEL[PIT_0].TCTRL &= ~(PIT_TCTRL_TIE_MASK);
	/**Enables timer cero**/
	PIT->CHANNEL[PIT_0].TCTRL &= ~(PIT_TCTRL_TEN_MASK);
}

