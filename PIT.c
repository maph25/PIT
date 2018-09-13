/*
 * PIT.c
 *
 *  Created on: Sep 11, 2018
 *      Author: LuisFernando
 */

#include "MK64F12.h"
#include "PIT.h"
#include "Bits.h"
#include "NVIC.h"

extern uint8_t InterruptStatus;

void PIT_delay(PIT_Timer_t pitTimer,float systemClock ,float period)
{
	/**Es necesario hacer un cast para pasar del numero float a entero, y de ahi a hexa**/
	float clockPeriod = 1/systemClock;
	float cycles = (period/clockPeriod) - 1;
	/** Turn on PIT**/
	PIT->MCR = MCR_ON;
	PIT->CHANNEL[pitTimer].LDVAL = cycles;
	/**
	 * TIE enables interrupts for the timer
	 * TEN starts the timer**/
	PIT->CHANNEL[pitTimer].TCTRL |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;
}

void PIT_clock_gating(void)
{
	/**Enable PIT clock**/
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	/**Turn on PIT timer*/
	PIT->MCR |=~ (PIT_MCR_MDIS_MASK);

}

uint8 PIT_interrupt_flag_status();


uint8 PIT_get_interrupt_status(PIT_Timer_t pitTimer,InterruptType InterruptStatus)
{
	PIT->CHANNEL[pitTimer].TFLG |= PIT_TCTRL_TEN_MASK;
	PIT->CHANNEL[pitTimer].TFLG |= PIT_TCTRL_TIF_MASK;

	return InterruptStatus;
}

void PIT_clear(void)
{
	PIT_TFLG |= PIT_TFLG_TIF_MASK;
	/**PIT_TCTRL; //read control register for clear PIT flag, this is silicon bug*/
	PIT_TCTRL &= ~(PIT_TCTRL_TIE_MASK);//enables PIT timer interrupt
	PIT_TCTRL &= ~(PIT_TCTRL_TEN_MASK);//enables timer0
	InterruptStatus = FALSE;
}

