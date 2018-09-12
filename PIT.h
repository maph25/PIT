/*
 * PIT.h
 *
 *  Created on: Sep 11, 2018
 *      Author: LuisFernando
 */

#ifndef PIT_H_
#define PIT_H_

#include "DataTypeDefinitions.h"
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function configure the PIT to generate a delay base on the system clock.
 	 Internally it configures the clock gating and enables the PIT module.
 	 It is important to note that this strictly is not device driver since everything is
 	 contained in a single function, but in general you have to avoid this practices, this only
 	 for the propose of the homework

 	 \param[in]  portName Port to be configured.
 	 \return void
 */

typedef enum {PIT_0,PIT_1,PIT_2,PIT_3}PIT_Timer_t;
typedef enum {MCR_ON,MCR_OFF}MCR_State;
void PIT_delay(PIT_Timer_t pitTimer,float systemClock ,float period);

void PIT_clockGating(void);

uint8 PIT_getIntrStatus(void);

void PIT_clear(void);

uint32 decToHexa(uint32 value);

/*Funct called from startup_mk64f12.c*/
void PIT0_IRQHandler(void);

#endif /* PIT_H_ */
