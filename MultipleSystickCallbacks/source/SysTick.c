#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "SysTick.h"
#include "startup/hardware.h"

static SysTickElement sysTickElements[INITIAL_SYSTICK_ELEMENTS_ARRAY_LENGTH];
static int idCounter;
static int getArrayEffectiveLength (SysTickElement sysTickElements [] );

bool SysTick_Init (void)
{
	SysTick->CTRL = 0x00;
	SysTick->LOAD = SYSTICK_ISR_PERIOD_S - 1;
	SysTick->VAL = 0x00;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk |	SysTick_CTRL_ENABLE_Msk;

	idCounter = 1;
	return true;
}

__ISR__ SysTick_Handler (void)
{
	for(int i=0; i<(getArrayEffectiveLength(sysTickElements)); i++){
		sysTickElements[i].counter ++;
		if(sysTickElements[i].counter == sysTickElements[i].timersPeriodMultiple){
			(*sysTickElements[i].callback)();
			sysTickElements[i].counter = 0;
		}
	}
}

//Systick_ClrCallback adds an element to the array of callbacks.
//newTime should be greater than SYSTICK_ISR_PERIOD_S. It indicates the period for the callback to be called.
//Returns ID if no error was found;
int SysTick_AddCallback(void (*newCallback)(void), int newTime)
{
	int newMultiple = (int) (newTime / SYSTICK_ISR_PERIOD_S);	//Calculates how many SYSTICK_ISR_PERIOD_Ss are equivalent to the callback period.
	if(newMultiple!=0){
		SysTickElement newSystickElement = {idCounter,newCallback, newMultiple, 0, false};	//Creates the new element
		//sysTickElements = (timerElement*)realloc(sysTickElements, sizeof(timerElement)*((sizeof(sysTickElements)/sizeof(timerElement))+1)); //((sizeof(sysTickElements)/sizeof(timerElement))+1, sizeof(timerElement));
		sysTickElements[getArrayEffectiveLength(sysTickElements)] = newSystickElement;
		return idCounter++;
	}
	return SystickNotMultipleOfSystickPeriod;
}


//Systick_ClrCallback cancels a callback element.
SystickError Systick_ClrCallback(int id)
{
	bool idFound = false;
	int i = 0;
	int arrayEffectiveLength = getArrayEffectiveLength(sysTickElements);
	while((idFound == false) && (i < arrayEffectiveLength)){
		if(sysTickElements[i].callbackID == id){
			idFound = true;
			for(int j=i; j<((getArrayEffectiveLength(sysTickElements))-1); j++){
				sysTickElements[j].callbackID = sysTickElements[j+1].callbackID;
				sysTickElements[j].callback = sysTickElements[j+1].callback;
				sysTickElements[j].counter = sysTickElements[j+1].counter;
				sysTickElements[j].paused = sysTickElements[j+1].paused;
				sysTickElements[j].timersPeriodMultiple = sysTickElements[j+1].timersPeriodMultiple;

			}

			//"Deleting" element
			sysTickElements[arrayEffectiveLength-1].callback = NULL;
			sysTickElements[arrayEffectiveLength-1].counter = 0;
			sysTickElements[arrayEffectiveLength-1].paused = false;
			sysTickElements[arrayEffectiveLength-1].callbackID = 0;
			sysTickElements[arrayEffectiveLength-1].timersPeriodMultiple = 0;

			//sysTickElements = (timerElement*)realloc(sysTickElements, sizeof(timerElement)*((sizeof(sysTickElements)/sizeof(timerElement))-1));
		}
		i++;
	}
	if(idFound == false){
		return SystickNoIdFound;
	}
	return SystickNoError;
}

//Systick_ChangeCallbackTime changes the time at which a callback is called.
SystickError Systick_ChangeCallbackTime(int id, int newTime)
{
	bool idFound = false;
	int i = 0;
	do{
		if(sysTickElements[i].callbackID == id){
			idFound = true;
			int newMultiple = (int) (newTime / SYSTICK_ISR_PERIOD_S);
			if(newMultiple!=0){
				sysTickElements[i].timersPeriodMultiple = newMultiple;
				sysTickElements[i].counter = 0;
			}
		}
		i++;
	} while((idFound == false) && (i < getArrayEffectiveLength(sysTickElements)));
	if(idFound == false){
		return SystickNoIdFound;
	}
	return SystickNoError;
}

//Systick_PauseCallback pauses a callback.
SystickError Systick_PauseCallback(int id)
{
	bool idFound = false;
	int i = 0;
	do{
		if(sysTickElements[i].callbackID == id){
			idFound = true;
			sysTickElements[i].paused = true;
		}
		i++;
	} while((idFound == false) && (i < getArrayEffectiveLength(sysTickElements)));
	if(idFound == false){
		return SystickNoIdFound;
	}
	return SystickNoError;
}

//Systick_ResumeCallback resumes a callback.
SystickError Systick_ResumeCallback(int id)
{
	bool callbackFound = false;
	int i = 0;
	do{
		if(sysTickElements[i].callbackID == id){
			callbackFound = true;
			sysTickElements[i].paused = false;
		}
		i++;
	} while((callbackFound == false) && (i < getArrayEffectiveLength(sysTickElements)));
	if(callbackFound == false){
		return SystickNoIdFound;
	}
	return SystickNoError;
}

//Returns the number of elements added to the array (the number of elements before an element with NULL callback is found).
static int getArrayEffectiveLength (SysTickElement sysTickElements[] ){
	int i = 0;
	bool foundLast = false;
	while (foundLast == false && i < INITIAL_SYSTICK_ELEMENTS_ARRAY_LENGTH){

		if (sysTickElements[i].callback == NULL){
			foundLast = true;
		}else{
			i ++;
		}
	}
	return i;
}




