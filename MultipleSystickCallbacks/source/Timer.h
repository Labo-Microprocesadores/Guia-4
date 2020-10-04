/*
 * Timer.h
 *
 *  Created on: 3 oct. 2020
 *      Author: Grupo 2
 */

#ifndef TIMER_H_
#define TIMER_H_

#define INITIAL_TIMER_ELEMENTS_ARRAY_LENGTH	200

#include "SysTick.h"
#include <stdbool.h>
typedef struct TimerElement
{
	int callbackID;
	void (*callback)(void);
	int time;
	bool paused;
} TimerElement;


typedef enum TimerError {TimerNoError = SystickNoError, TimerNotMultipleOfSystemPeriod = SystickNotMultipleOfSystickPeriod, TimerNoIdFound = SystickNoIdFound} TimerError;

bool Timer_Init (void);

//CreateTimer
int Timer_Create(void (*timerCallback)(void*), int time);

//PauseTimer

TimerError Timer_Pause(int timerID);

//ResumeTimer
TimerError Timer_Resume(int timerID);


//CancelTimer
TimerError Timer_Delete(int timerID);


//ChangeTimerTime
TimerError Timer_ChangeTime(int timerID, int newTime);



#endif /* TIMER_H_ */
