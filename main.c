/*
 * Copyright (c) 2016, NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    PIT_Delay.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "PIT.h"
#include "NVIC.h"
#include "GPIO.h"
#define SYSTEM_CLOCK 21000000
#define DELAY 0.00025F



int main(void) {

	uint8 pitIntrStatus = FALSE;
	GPIO_pinControlRegisterType pinControlRegisterPORTD = GPIO_MUX1;

	GPIO_clockGating(GPIO_D);
	GPIO_pinControlRegister(GPIO_D,BIT0,&pinControlRegisterPORTD);
	GPIO_dataDirectionPIN(GPIO_D,GPIO_OUTPUT,BIT0);
	GPIO_setPIN(GPIO_D,BIT0);
	PIT_clockGating();
	NVIC_enableInterruptAndPriotity(PIT_CH0_IRQ, PRIORITY_10);
	EnableInterrupts;

    while(1) {
    	GPIO_tooglePIN(GPIO_D,BIT0);        //Invierte el estado, lo apaga
    	pitIntrStatus = PIT_getIntrStatus();
    	PIT_delay(PIT_0,SYSTEM_CLOCK,DELAY);
    	PIT_clear();
    	/*Waits for an interruption to occur*/
    	while(FALSE == pitIntrStatus);
    	/*GPIO_tooglePIN(GPIO_D,BIT0);    //Enciende el puerto
    	PIT_clear();
    	PIT_delay(PIT_0,SYSTEM_CLOCK,DELAY);   //recarga nuevamente el valor del timer
    	pitIntrStatus = PIT_getIntrStatus();   //falso
    	while(FALSE == pitIntrStatus);*/
    }
    return 0 ;
}
