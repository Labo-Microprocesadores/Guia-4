/*
 * Timer.c
 *
 *  Created on: 3 oct. 2020
 *      Author: Grupo 2
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "Timer.h"

static TimerElement timerElements[INITIAL_TIMER_ELEMENTS_ARRAY_LENGTH];
static int idCounter;
static int getArrayEffectiveLength (TimerElement timerElements [] );
void Timer_PISR(void);

bool Timer_Init (void)
{
	SysTick_Init();
	int systickCallbackID = SysTick_AddCallback(&Timer_PISR, 10000000L);
	idCounter = 1;
	return true;
}


void Timer_PISR(void){

	for(int i=0; i<(getArrayEffectiveLength(timerElements)); i++){
			timerElements[i].counter ++;
			if(timerElements[i].counter == timerElements[i].timersPeriodMultiple){
				(*timerElements[i].callback)();
				timerElements[i].counter = 0;
		}
	}
}


//CreateTimer
int Timer_AddCallback(void (*newCallback)(void), int time){

	int newMultiple = (int) (time / TIMER_ISR_PERIOD_S);	//Calculates how many SYSTICK_ISR_PERIOD_Ss are equivalent to the callback period.
		if(newMultiple!=0){
			TimerElement newTimerElement = {idCounter,newCallback, newMultiple, 0, false};	//Creates the new element
			timerElements[getArrayEffectiveLength(timerElements)] = newTimerElement;
			return idCounter++;
		}
	return TimerNotMultipleOfSystickPeriod;
}

//PauseTimer

TimerError Timer_Pause(int timerID){

	bool idFound = false;
	int i = 0;
	do{
		if(timerElements[i].callbackID == timerID){
			idFound = true;
			timerElements[i].paused = true;
		}
		i++;
	} while((idFound == false) && (i < getArrayEffectiveLength(timerElements)));
	if(idFound == false){
		return TimerNoIdFound;
	}
	return TimerNoError;

}

//ResumeTimer
TimerError Timer_Resume(int timerID){
	bool callbackFound = false;
	int i = 0;
	do{
		if(timerElements[i].callbackID == timerID){
			callbackFound = true;
			timerElements[i].paused = false;
		}
		i++;
	} while((callbackFound == false) && (i < getArrayEffectiveLength(timerElements)));
	if(callbackFound == false){
		return TimerNoIdFound;
	}
	return TimerNoError;
}


//CancelTimer
TimerError Timer_Delete(int timerID){

	bool idFound = false;
	int i = 0;
	int arrayEffectiveLength = getArrayEffectiveLength(timerElements);
	while((idFound == false) && (i < arrayEffectiveLength)){
		if(timerElements[i].callbackID == timerID){
			idFound = true;
			for(int j=i; j<((getArrayEffectiveLength(timerElements))-1); j++){
				timerElements[j].callbackID = timerElements[j+1].callbackID;
				timerElements[j].callback = timerElements[j+1].callback;
				timerElements[j].counter = timerElements[j+1].counter;
				timerElements[j].paused = timerElements[j+1].paused;
				timerElements[j].timersPeriodMultiple = timerElements[j+1].timersPeriodMultiple;

			}

			//"Deleting" element
			timerElements[arrayEffectiveLength-1].callback = NULL;
			timerElements[arrayEffectiveLength-1].counter = 0;
			timerElements[arrayEffectiveLength-1].paused = false;
			timerElements[arrayEffectiveLength-1].callbackID = 0;
			timerElements[arrayEffectiveLength-1].timersPeriodMultiple = 0;


		}
		i++;
	}
	if(idFound == false){
		return TimerNoIdFound;
	}
	return TimerNoError;


}


//ChangeTimerTime
TimerError Timer_ChangeTime(int timerID, int newTime){

	bool idFound = false;
	int i = 0;
	do{
		if(timerElements[i].callbackID == timerID){
			idFound = true;
			int newMultiple = (int) (newTime / TIMER_ISR_PERIOD_S);
			if(newMultiple!=0){
				timerElements[i].timersPeriodMultiple = newMultiple;
				timerElements[i].counter = 0;
			}
		}
		i++;
	} while((idFound == false) && (i < getArrayEffectiveLength(timerElements)));
	if(idFound == false){
		return TimerNoIdFound;
	}
	return TimerNoError;


}



//Returns the number of elements added to the array (the number of elements before an element with NULL callback is found).
static int getArrayEffectiveLength (TimerElement timerElements[] ){
	int i = 0;
	bool foundLast = false;
	while (foundLast == false && i < INITIAL_TIMER_ELEMENTS_ARRAY_LENGTH){

		if (timerElements[i].callback == NULL){
			foundLast = true;
		}else{
			i ++;
		}
	}
	return i;
}



