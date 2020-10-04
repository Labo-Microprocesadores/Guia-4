/*
 * Led.h
 *
 *  Created on: 3 oct. 2020
 *      Author: Grupo 2
 */

#ifndef LED_H_
#define LED_H_

#include "Timer.h"
#include "board.h"


typedef enum LedSpeed {SLOW, FAST} LedSpeed;

typedef enum LedID {LED_RED = PIN_LED_RED , LED_BLUE = PIN_LED_BLUE, LED_GREEN = PIN_LED_GREEN} LedID;

typedef struct LedElement
{
	LedID ledID;
	int timersPeriodMultiple;
	int counter;
	bool isOn;
} LedElement;

void Led_LongPeriod(LED, int times ,int period,int blink_times, int blinkPeriod, int onTime)
	//timer(led_blink, 30segundos)

void Led_Blink(LED,int blink_times, int blinkPeriod, int onTime);
	//timer(led_onTime, 3segundos)

void Led_OnTime(LED, int onTime);
	//timer(ledOff, 1segundos)

void Led_On(LED);

void Led_Off(LED);




#endif /* LED_H_ */
