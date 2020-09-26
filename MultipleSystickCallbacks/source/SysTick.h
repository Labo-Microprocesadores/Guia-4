/***************************************************************************//**
  @file     SysTick.h
  @brief    SysTick driver
  @author   Grupo2
 ******************************************************************************/

#ifndef _SYSTICK_H_
#define _SYSTICK_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdbool.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define SYSTICK_ISR_FREQUENCY_HZ 1000U //?
#define SYSTICK_ISR_PERIOD_S 12500000L //125ms
#define INTIAL_TIMER_ELEMENTS_ARRAY_LENGTH	50

typedef struct timerElement
{
	void (*callback)(void);
	int timersPeriodMultiple;
	int counter;
} timerElement;

extern timerElement timerElements[INTIAL_TIMER_ELEMENTS_ARRAY_LENGTH];



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Initialize SysTic driver
 * @param funcallback Function to be call every SysTick
 * @return Initialization and registration succeed
 **/
bool SysTick_Init (void);
void SysTick_AddCallback(void (*newCallback)(void), int newTime);
void Systick_ClrCallback(void (*oldCallback)(void));
void Systick_ChangeCallbackTime(void (*oldCallback)(void), int newTime);
int getArrayEffectiveLength (timerElement timerElements [] );

/*******************************************************************************
 ******************************************************************************/
#endif
