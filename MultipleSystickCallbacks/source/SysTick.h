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
#define INITIAL_SYSTICK_ELEMENTS_ARRAY_LENGTH	200

typedef struct SysTickElement
{
	int callbackID;
	void (*callback)(void*);
	int timersPeriodMultiple;
	int counter;
	bool paused;
} SysTickElement;


typedef enum SystickError {SystickNoError = 0, SystickNotMultipleOfSystickPeriod = -1, SystickNoIdFound = -2} SystickError;


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
int SysTick_AddCallback(void (*newCallback)(void*), int newTime);
SystickError Systick_ClrCallback(int id);
SystickError Systick_PauseCallback(int id);
SystickError Systick_ResumeCallback(int id);
SystickError Systick_ChangeCallbackTime(int id, int newTime);


/*******************************************************************************
 ******************************************************************************/
#endif
