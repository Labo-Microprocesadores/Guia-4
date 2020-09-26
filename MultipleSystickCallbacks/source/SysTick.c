#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "SysTick.h"
#include "startup/hardware.h"

timerElement timerElements[INTIAL_TIMER_ELEMENTS_ARRAY_LENGTH];

bool SysTick_Init (void)
{
	SysTick->CTRL = 0x00;
	SysTick->LOAD = SYSTICK_ISR_PERIOD_S - 1;
	SysTick->VAL = 0x00;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk |	SysTick_CTRL_ENABLE_Msk;


	return true;


}

__ISR__ SysTick_Handler (void)
{
	for(int i=0; i<(getArrayEffectiveLength(timerElements)); i++){
		timerElements[i].counter ++;
		if(timerElements[i].counter == timerElements[i].timersPeriodMultiple){
			(*timerElements[i].callback)();
			timerElements[i].counter = 0;
		}
	}
}

//Systick_ClrCallback adds an element to the array of callbacks.
//newTime should be greater than SYSTICK_ISR_PERIOD_S. It indicates the period for the callback to be called.
void SysTick_AddCallback(void (*newCallback)(void), int newTime)
{
	int newMultiple = (int) (newTime / SYSTICK_ISR_PERIOD_S);	//Calculates how many SYSTICK_ISR_PERIOD_Ss are equivalent to the callback period.
	if(newMultiple!=0){
		timerElement newTimerElement = {newCallback, newMultiple, 0};	//Creates the new element
		//timerElements = (timerElement*)realloc(timerElements, sizeof(timerElement)*((sizeof(timerElements)/sizeof(timerElement))+1)); //((sizeof(timerElements)/sizeof(timerElement))+1, sizeof(timerElement));
		timerElements[getArrayEffectiveLength(timerElements)] = newTimerElement;
	}
}//AGREGAR QUE DEVUELVA INDICACION DE ERROR


//Systick_ClrCallback cancels a callback element.
void Systick_ClrCallback(void (*oldCallback)(void))
{
	bool callbackFound = false;
	int i = 0;
	int arrayEffectiveLength = getArrayEffectiveLength(timerElements);
	while((callbackFound == false) && (i < arrayEffectiveLength)){
		if(timerElements[i].callback == oldCallback){
			callbackFound = true;
			for(int j=i; j<((getArrayEffectiveLength(timerElements))-1); j++){
				timerElements[j].callback = timerElements[j+1].callback;
				timerElements[j].counter = timerElements[j+1].counter;
				timerElements[j].timersPeriodMultiple = timerElements[j+1].timersPeriodMultiple;

			}

			//"Deleting" element
			timerElements[arrayEffectiveLength-1].callback = NULL;
			timerElements[arrayEffectiveLength-1].counter = 0;
			timerElements[arrayEffectiveLength-1].timersPeriodMultiple = 0;

			//timerElements = (timerElement*)realloc(timerElements, sizeof(timerElement)*((sizeof(timerElements)/sizeof(timerElement))-1));
		}
		i++;
	}
	if(callbackFound == false){
		//return ERROR_NO_CALLBACK;
	}
	//return OK;
}

//Systick_ChangeCallbackTime changes the time at which a callback is called.
void Systick_ChangeCallbackTime(void (*oldCallback)(void), int newTime)
{
	bool callbackFound = false;
	int i = 0;
	do{
		if(timerElements[i].callback == oldCallback){
			callbackFound = true;
			int newMultiple = (int) (newTime / SYSTICK_ISR_PERIOD_S);
			if(newMultiple!=0){
				timerElements[i].timersPeriodMultiple = newMultiple;
				timerElements[i].counter = 0;
			}
		}
		i++;
	} while((callbackFound == false) && (i < getArrayEffectiveLength(timerElements)));
}


//Returns the number of elements added to the array (the number of elements before an element with NULL callback is found).
int getArrayEffectiveLength (timerElement timerElements[] ){
	int i = 0;
	bool foundLast = false;
	while (foundLast == false && i < INTIAL_TIMER_ELEMENTS_ARRAY_LENGTH){

		if (timerElements[i].callback == NULL){
			foundLast = true;
		}else{
			i ++;
		}
	}
	return i;
}




