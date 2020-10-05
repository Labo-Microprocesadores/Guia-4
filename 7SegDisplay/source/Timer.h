/*
 * Timer.h
 *
 *  Created on: 3 oct. 2020
 *      Author: Grupo 2
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "SysTick.h"
#include <stdbool.h>


#define TIMER_ISR_PERIOD_S 10000000L //100ms
#define INITIAL_TIMER_ELEMENTS_ARRAY_LENGTH	20

typedef struct TimerElement
{
	int callbackID;
	void (*callback)(void);
	int timersPeriodMultiple;
	int counter;
	bool paused;
} TimerElement;


typedef enum TimerError {TimerNoError = 0, TimerNotMultipleOfSystickPeriod = -1, TimerNoIdFound = -2} TimerError;

bool Timer_Init (void);

//CreateTimer
int Timer_AddCallback(void (*newCallback)(void), int time);

//PauseTimer

TimerError Timer_Pause(int timerID);

//ResumeTimer
TimerError Timer_Resume(int timerID);


//CancelTimer
TimerError Timer_Delete(int timerID);


//ChangeTimerTime
TimerError Timer_ChangeTime(int timerID, int newTime);



#endif /* TIMER_H_ */
