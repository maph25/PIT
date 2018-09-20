/*
 * PIT.c
 *
 *  Created on: Sep 11, 2018
 *      Author: LuisFernando
 *      PIT_IRQHandler baasado en Manuel Alejandro obtenido de la pagina de NXP
 */

#include "MK64F12.h"
#include "PIT.h"
#include "DataTypeDefinitions.h"

static uint8 intrFlag = FALSE;
//preguntar si esto es valido ya que se utiliza en dos funciones


void PIT_delay(PIT_Timer_t pitTimer,ufloat32 systemClock ,ufloat32 period)
{
	/**Es necesario hacer un cast para pasar del numero float a entero, y de ahi a hexa**/
	ufloat32 clockPeriod = 0.0F;
	uint32 cycles = 0;
	systemClock = systemClock/2;
	clockPeriod = 1/systemClock;
	cycles = (uint32)(period/clockPeriod);
	cycles = cycles - 1;

	PIT->CHANNEL[pitTimer].LDVAL = cycles;
	PIT_enable_interrupt(pitTimer);
}

void PIT_enable(void)
{
	PIT->MCR = MCR_ON;
}

void PIT_stop(void)
{
	PIT->MCR = MCR_OFF;
}

void PIT_LDVAL(PIT_Timer_t pitTimer);

void PIT_enable_interrupt(PIT_Timer_t pitTimer)
{
	/**
	 * TIE enables interrupts for the timer
	 * TEN starts the timer**/
	PIT->CHANNEL[pitTimer].TCTRL |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;
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
	intrFlag = FALSE;
}
/**
 * Funct called from startup_mk64f12.c**/
void PIT0_IRQHandler(void)
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
	/****/
	intrFlag = TRUE;
}
