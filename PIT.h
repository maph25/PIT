/*
 * PIT.h
 *
 *	\author Andrea Perez & Fernanda Muñoz & Luis Fernando Rodriguez
 *	\date	11/Sep/2018
 */

#ifndef PIT_H_
#define PIT_H_

#include "Bits.h"

/*! This enumerated constant are used to select the PIT to be used*/
typedef enum {PIT_0,PIT_1,PIT_2,PIT_3} PIT_Timer_t;
typedef enum {MCR_ON, MCR_OFF} MCR_State;
typedef enum {PIT_FLAG_0, PIT_FLAG_1,PIT_FLAG_2} PIT_Flag_t;

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
void PIT_delay(PIT_Timer_t pitTimer,float systemClock ,float perior);

void PIT_clock_gating(void);

uint8 PIT_interrupt_flag_status(void);

uint8 PIT_get_interrupt_status(void);

void PIT_clear(void);


#endif /* PIT_H_ */
