/*
 * Led.h
 *
 *  Created on: 3 oct. 2020
 *      Author: Grupo 2
 */

#ifndef LED_H_
#define LED_H_

#include "SysTick.h"

typedef enum LedSpeed {SLOW, FAST} LedSpeed;

void Led_LongPeriod(LED, int times ,int period,int blink_times, int blinkPeriod, int onTime)
	//timer(led_blink, 30segundos)

void Led_Blink(LED,int blink_times, int blinkPeriod, int onTime);
	//timer(led_onTime, 3segundos)

void Led_OnTime(LED, int onTime);
	//timer(ledOff, 1segundos)

void Led_On(LED);

void Led_Off(LED);




#endif /* LED_H_ */
