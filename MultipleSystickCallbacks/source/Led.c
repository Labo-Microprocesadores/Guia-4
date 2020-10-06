/***************************************************************************//**
  @file     Led.c
  @brief    Led functions
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Timer.h"
#include "board.h"
#include "gpio.h"
#include "Led.h"

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
/**
 * @brief 	Searches for a LedElement with a corresponding ID in the ledElements array and returns its index if found.
 * 			If the ID is not found, returns -1.
 * @param id The id of the LED to be found.
 * @return The index of the LedElement associated with the id in the ledElements array.
 */
static int findLedIndexByID (LedID id);

/**
 * @brief Manages the time and events of the processes taking place in each LED.
 */
static void Led_PISR(void);


/*******************************************************************************
 * PRIVATE VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*A LedElement's array to store the information and state of each led.*/
static LedElement ledElements[3];
/* Default structures for the LEDs to be created with.
 * These may change if a "On For Defined Time", "Blink", or "Repetition Blink" process is requested.
 */
static OnForDefinedTimeProperties defaultOnForDefinedTimeProperties = {0,0,0};
static BlinkProperties defaultBlinkProperties = {0,0,0,0,0};
static InfiniteBlinkProperties defaultInfiniteBlinkProperties = {NO_SPEED, 0,0};
static RepetitionBlinkProperties defaultRepetitionBlinkProperties = {0,0,0,0,0};

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
bool Led_Init (void)
{
	/*LEDs are defined as OUTPUT*/
	gpioMode(LED_RED, OUTPUT);
	gpioMode(LED_GREEN, OUTPUT);
	gpioMode(LED_BLUE, OUTPUT);

	/*LEDs are turned to its default state (generally OFF).*/
	gpioWrite(LED_RED, DEFAULT_LED_STATE);
	gpioWrite(LED_GREEN, DEFAULT_LED_STATE);
	gpioWrite(LED_BLUE, DEFAULT_LED_STATE);

	/*Each led is created as a LedElement with the default structures.*/
	LedElement redLed = {LED_RED, false, false, false, false, defaultInfiniteBlinkProperties, defaultOnForDefinedTimeProperties, defaultBlinkProperties, defaultRepetitionBlinkProperties};
	LedElement greenLed = {LED_GREEN, false, false, false, false, defaultInfiniteBlinkProperties, defaultOnForDefinedTimeProperties, defaultBlinkProperties, defaultRepetitionBlinkProperties};
	LedElement blueLed = {LED_BLUE, false, false, false, false, defaultInfiniteBlinkProperties, defaultOnForDefinedTimeProperties, defaultBlinkProperties, defaultRepetitionBlinkProperties};

	/*The LedElements are added to the array of LEDs*/
	ledElements[0] = redLed;
	ledElements[1] = greenLed;
	ledElements[2] = blueLed;

	Timer_AddCallback(&Led_PISR, LED_ISR_PERIOD); //Requests Timer to periodically call the Led's ISR.
	return true;
}

void Led_On(LedID ledID)
{
	gpioWrite(ledID, ON);
}

void Led_Off(LedID ledID)
{
	gpioWrite(ledID, OFF);
}

void Led_Toggle(LedID ledID)
{
	gpioToggle(ledID);
}

LedError Led_OnForDefinedTime(LedID ledID, int onTime)
{
	unsigned int onTimeConvertion = onTime * MS_TO_TICK_CONVERTION;	//Converts the time in ms to ticks.
	int indexInArray = findLedIndexByID(ledID);	//Finds the LED index in the ledElements array.
	if (indexInArray == -1)
		return LedNoIdFound;

	int quotient = (int) (onTimeConvertion / LED_ISR_PERIOD);	//Calculates how many LED_ISR_PERIOD are equivalent to the onTime period.

	if (quotient <= 0)
		return LedPeriodError;	//period must be greater than LED_ISR_PERIOD.

	/*Defines a "On For Defined Time" process variables.*/
	ledElements[indexInArray].onForDefinedTimeProperties.onTime = onTime;
	ledElements[indexInArray].onForDefinedTimeProperties.onTimeCounterLimit = quotient;	//Indicates the amount of times the Led's ISR must occur before the LED turns off.
	ledElements[indexInArray].onForDefinedTimeProperties.onTimeCounter = 0;				//Counts the amount of times the Led's ISR occurred.
	Led_On(ledElements[indexInArray].ledID);	//Turns the LED on (starts the process).

	ledElements[indexInArray].isOnForDefinedTime = true;	//Flag indicating the process is taking place.
	return LedNoError;
}


LedError Led_CustomBlink(LedID ledID,int blinkTimes, int blinkPeriod, int onTime)
{
	unsigned int blinkPeriodConvertion = blinkPeriod * MS_TO_TICK_CONVERTION; //Converts the time in ms to ticks.
	int indexInArray = findLedIndexByID(ledID); //Finds the LED index in the ledElements array.
	if (indexInArray == -1)
		return LedNoIdFound;
	int quotient = (int) (blinkPeriodConvertion / LED_ISR_PERIOD); //Calculates how many LED_ISR_PERIOD are equivalent to a blinkPeriod.
	if (quotient <= 0)
		return LedPeriodError;	//blinkPeriod must be greater than LED_ISR_PERIOD.

	/* Defines a "Blink" process variables.
	 * A "Blink" process consists of a LED being turned on and off repeatedly. In other words, multiple "On For Defined Time" processes taking place repeatedly.
	 * A "On For Defined Time" process consists of a LED being ON during a defined time. After this time has elapsed, the LED is turned off.
	 */
	ledElements[indexInArray].blinkProperties.blinkPeriod = blinkPeriod;
	ledElements[indexInArray].blinkProperties.blinkTimes = blinkTimes;
	ledElements[indexInArray].blinkProperties.blinkCounter = 0;
	ledElements[indexInArray].blinkProperties.blinkTimeCounterLimit = quotient;
	ledElements[indexInArray].blinkProperties.blinkTimeCounter = 0;
	/*"On For Defined Time" subprocesses properties*/
	ledElements[indexInArray].onForDefinedTimeProperties.onTime = onTime;

	ledElements[indexInArray].isBlinking = true;	//Flag indicating the process is taking place.

	//Requests a "On For Defined Time" process (starts a "Blink" process).
	Led_OnForDefinedTime(ledElements[indexInArray].ledID, ledElements[indexInArray].onForDefinedTimeProperties.onTime);
	return LedNoError;
}

LedError Led_CustomRepetitionBlink(LedID ledID, int repetitionTimes ,int repetitionPeriod ,int blinkTimesEachRepetition, int blinkPeriodEachRepetition, int onTimeEachBlink)
{

	unsigned int repetitionPeriodConvertion = repetitionPeriod * MS_TO_TICK_CONVERTION; //Converts the time in ms to ticks.
	int indexInArray = findLedIndexByID(ledID); //Finds the LED index in the ledElements array.
	if (indexInArray == -1)
		return LedNoIdFound;
	int quotient = (int) (repetitionPeriodConvertion / LED_ISR_PERIOD);	//Calculates how many LED_ISR_PERIOD are equivalent to a repetitionPeriod.
	if (quotient <= 0)
		return LedPeriodError;	//repetitionPeriod must be greater than LED_ISR_PERIOD.

	/* Defines a "Repetition Blink" process variables.
	 * A "Repetition Blink" process consists of multiple "Blink" processes taking place repeatedly.
	 * A "Blink" process consists of a LED being turned on and off repeatedly. In other words, multiple "On For Defined Time" processes taking place repeatedly.
	 * A "On For Defined Time" process consists of a LED being ON during a defined time. After this time has elapsed, the LED is turned off.
	 */
	ledElements[indexInArray].repetitionBlinkProperties.repetitionTimes = repetitionTimes;	//How many times a "Blink" process must occur.
	ledElements[indexInArray].repetitionBlinkProperties.repetitionCounter = 0;
	ledElements[indexInArray].repetitionBlinkProperties.repetitionPeriod = repetitionPeriod;
	ledElements[indexInArray].repetitionBlinkProperties.repetitionBlinkTimeCounterLimit = quotient;
	ledElements[indexInArray].repetitionBlinkProperties.repetitionBlinkTimeCounter = 0;

	/*"Blink" subprocesses properties*/
	ledElements[indexInArray].blinkProperties.blinkPeriod = blinkPeriodEachRepetition;
	ledElements[indexInArray].blinkProperties.blinkTimes = blinkTimesEachRepetition;
	ledElements[indexInArray].blinkProperties.blinkCounter = 0;

	/*"On For Defined Time" subprocesses properties*/
	ledElements[indexInArray].onForDefinedTimeProperties.onTime = onTimeEachBlink;

	ledElements[indexInArray].isRepeatedlyBlinking = true; //Flag indicating the process is taking place.

	//Requests a "Blink" process (starts a "Repetition Blink" process).
	Led_CustomBlink(ledElements[indexInArray].ledID,blinkTimesEachRepetition,blinkPeriodEachRepetition, onTimeEachBlink);


	return LedNoError;
}

LedError Led_InfiniteBlink(LedID ledID, LedBlinkSpeed speed)
{
	if (speed == NO_SPEED)
		return LedOtherErrors;
	int indexInArray = findLedIndexByID(ledID); //Finds the LED index in the ledElements array.
	if (indexInArray == -1)
		return LedNoIdFound;

	InfiniteBlinkProperties properties = {speed, speed, 0}; //LedBlinkSpeed is defined as an enum. Each element indicates the quotient between the toggle period and the LED_ISR_PERIOD.
	ledElements[indexInArray].infiniteBlinkProperties = properties;
	ledElements[indexInArray].isInfinitelyBlinking = true;

	return LedNoError;
}

LedError Led_StopInfiniteBlink(LedID ledId)
{
	int indexInArray = findLedIndexByID(ledId); //Finds the LED index in the ledElements array.
	if (indexInArray == -1)
		return LedNoIdFound;

	ledElements[indexInArray].isInfinitelyBlinking = false;
	ledElements[indexInArray].infiniteBlinkProperties = defaultInfiniteBlinkProperties;
	gpioWrite(ledId, DEFAULT_LED_STATE);
	return LedNoError;
}

LedError Led_StopAllProcesses(LedID ledId)
{
	int indexInArray = findLedIndexByID(ledId); //Finds the LED index in the ledElements array.
	if (indexInArray == -1)
		return LedNoIdFound;

	/*Sets processes' flags to false*/
	ledElements[indexInArray].isRepeatedlyBlinking = false;
	ledElements[indexInArray].isBlinking = false;
	ledElements[indexInArray].isOnForDefinedTime = false;
	ledElements[indexInArray].isInfinitelyBlinking = false;

	/*Resets the properties of the processes*/
	ledElements[indexInArray].infiniteBlinkProperties = defaultInfiniteBlinkProperties;
	ledElements[indexInArray].blinkProperties = defaultBlinkProperties;
	ledElements[indexInArray].repetitionBlinkProperties = defaultRepetitionBlinkProperties;
	ledElements[indexInArray].onForDefinedTimeProperties = defaultOnForDefinedTimeProperties;

	/*Turns the LED to its default state.*/
	gpioWrite(ledId, DEFAULT_LED_STATE);

	return LedNoError;
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static int findLedIndexByID (LedID id)
{
	for (int i = 0; i < sizeof(ledElements)/sizeof(ledElements[0]); i++)	//Iterates through all the elements.
	{
		if (ledElements[i].ledID == id)	//If the id is found, returns the index.
			return i;
	}
	return -1; //Not found
}


static void Led_PISR(void)
{
	for (int i = 0; i < sizeof(ledElements)/sizeof(ledElements[0]); i++) //Iterates through each LED
	{
		if (ledElements[i].isOnForDefinedTime)	//Checks if a "On For Defined Time" process is taking place.
		{
			ledElements[i].onForDefinedTimeProperties.onTimeCounter++;
			/*Checks if the process has to be finished*/
			if(ledElements[i].onForDefinedTimeProperties.onTimeCounter == ledElements[i].onForDefinedTimeProperties.onTimeCounterLimit)
			{
				//Finishes the process and resets variables.
				ledElements[i].isOnForDefinedTime = false;
				ledElements[i].onForDefinedTimeProperties.onTimeCounterLimit = 0;
				ledElements[i].onForDefinedTimeProperties.onTimeCounter = 0;
				Led_Off(ledElements[i].ledID);	//Turns the LED off (finishes the process).
			}
		}

		if(ledElements[i].isBlinking) //Checks if a "Blink" process is taking place.
		{
			ledElements[i].blinkProperties.blinkTimeCounter++;
			/*Checks if a "On For Defined Time" subprocess has finished*/
			if(ledElements[i].blinkProperties.blinkTimeCounter == ledElements[i].blinkProperties.blinkTimeCounterLimit)
			{
				//Finishes the "On For Defined Time" subprocess and resets variables.
				ledElements[i].blinkProperties.blinkTimeCounter = 0;
				ledElements[i].blinkProperties.blinkCounter++;
				/*Checks if the "Blink" process has completed*/
				if(ledElements[i].blinkProperties.blinkCounter == ledElements[i].blinkProperties.blinkTimes)
				{
					//Finishes the process and resets variables.
					ledElements[i].blinkProperties.blinkCounter = 0;
					ledElements[i].isBlinking = false;
				}
				else
				{
					/*If the "Blink" process has not completed, another "On For Defined" subprocess is started*/
					Led_OnForDefinedTime(ledElements[i].ledID, ledElements[i].onForDefinedTimeProperties.onTime);
				}
			}
		}

		if(ledElements[i].isRepeatedlyBlinking) //Checks if a "Repetition Blink" process is taking place.
		{
			ledElements[i].repetitionBlinkProperties.repetitionBlinkTimeCounter ++;
			/*Checks if a "Blink" subprocess has finished*/
			if(ledElements[i].repetitionBlinkProperties.repetitionBlinkTimeCounter == ledElements[i].repetitionBlinkProperties.repetitionBlinkTimeCounterLimit)
			{
				//Finishes the "Blink" subprocess and resets variables.
				ledElements[i].repetitionBlinkProperties.repetitionBlinkTimeCounter = 0;
				ledElements[i].repetitionBlinkProperties.repetitionCounter++;
				/*Checks if the "Repetition Blink" process has completed*/
				if(ledElements[i].repetitionBlinkProperties.repetitionCounter == ledElements[i].repetitionBlinkProperties.repetitionTimes)
				{
					//Finishes the process and resets variables.
					ledElements[i].repetitionBlinkProperties.repetitionCounter = 0;
					ledElements[i].isRepeatedlyBlinking = false;
				}
				else
				{
					/*If the "Repetition Blink" process has not completed, another "Blink" subprocess is started*/
					Led_CustomBlink(ledElements[i].ledID, ledElements[i].blinkProperties.blinkTimes, ledElements[i].blinkProperties.blinkPeriod, ledElements[i].onForDefinedTimeProperties.onTime);
				}

			}
		}

		if(ledElements[i].isInfinitelyBlinking) //Checks if a "Infinite Blink" process is taking place.
		{
			ledElements[i].infiniteBlinkProperties.toggleTimeCounter ++;
			/*Checks if a toggle needs to be done.*/
			if (ledElements[i].infiniteBlinkProperties.toggleTimeCounter == ledElements[i].infiniteBlinkProperties.toggleTimeCounterLimit)
			{
				ledElements[i].infiniteBlinkProperties.toggleTimeCounter = 0;
				Led_Toggle(ledElements[i].ledID);	//Toggles the LED
			}
		}
	}
}
