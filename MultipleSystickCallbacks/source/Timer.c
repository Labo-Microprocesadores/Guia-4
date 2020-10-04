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

bool Timer_Init (void)
{
	SysTick_Init();

	idCounter = 1;
	return true;
}


//CreateTimer
int Timer_Create(void (*timerCallback)(void*), int time){

	int id = SysTick_AddCallback(timerCallback, time);

	if (id > 0){
		TimerElement newTimerElement = {id, timerCallback, time, false};	//Creates the new element
		timerElements[getArrayEffectiveLength(timerElements)] = newTimerElement;

	}
	return id; //Element id or error;
}

//PauseTimer

TimerError Timer_Pause(int timerID){

	bool idFound = false;
	int i = 0;
	do{
		if(timerElements[i].callbackID == timerID){
			idFound = true;
		}
		i++;
	} while((idFound == false) && (i < getArrayEffectiveLength(timerElements)));

	if(idFound == false){
		return TimerNoIdFound;
	}

	TimerError error = Systick_PauseCallback(timerID);
	if (error == TimerNoError)
		timerElements[i].paused = true;
	return error;

}

//ResumeTimer
TimerError Timer_Resume(int timerID){
	bool idFound = false;
	int i = 0;
	do{
		if(timerElements[i].callbackID == timerID){
			idFound = true;

		}
		i++;
	} while((idFound == false) && (i < getArrayEffectiveLength(timerElements)));

	if(idFound == false){
		return TimerNoIdFound;
	}

	TimerError error = Systick_ResumeCallback(timerID);
	if (error == TimerNoError)
		timerElements[i].paused = false;
	return error;
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
				timerElements[j].paused = timerElements[j+1].paused;
				timerElements[j].time = timerElements[j+1].time;
			}

			//"Deleting" element
			timerElements[arrayEffectiveLength-1].callback = NULL;
			timerElements[arrayEffectiveLength-1].paused = false;
			timerElements[arrayEffectiveLength-1].callbackID = 0;
			timerElements[arrayEffectiveLength-1].time = 0;


		}
		i++;
	}

	if(idFound == false){
		return TimerNoIdFound;
	}

	Systick_ClrCallback(timerID);

	return TimerNoError;


}


//ChangeTimerTime
TimerError Timer_ChangeTime(int timerID, int newTime){

	bool idFound = false;
	int i = 0;
	do{
		if(timerElements[i].callbackID == timerID){
			idFound = true;

		}
		i++;
	} while((idFound == false) && (i < getArrayEffectiveLength(timerElements)));

	if(idFound == false){
		return TimerNoIdFound;
	}

	TimerError error = Systick_ChangeCallbackTime(timerID, newTime);

	if (error == TimerNoError)
		timerElements[i].time = newTime;

	return error;


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



