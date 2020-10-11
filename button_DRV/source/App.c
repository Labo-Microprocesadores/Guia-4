/***************************************************************************//**
  @file     App.c
  @brief    Application functions
  @author   Nicolás Magliola
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "board.h"
#include "gpio.h"
#include "button.h"
#include "SysTick.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define LED PORTNUM2PIN(PB,23) //PTA0
#define SW PORTNUM2PIN(PC,0)
#define DELAY 8
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void delayLoop(uint32_t);
void callback_systick(void);
void callback_switch(void);


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
	gpioMode(PIN_LED_RED, OUTPUT);
	gpioMode(PIN_LED_GREEN, OUTPUT);
	//gpioMode(PIN_LED_BLUE, OUTPUT);
	gpioWrite(PIN_LED_RED, HIGH);
	gpioWrite(PIN_LED_GREEN, HIGH);
	gpioMode(PIN_SW3, INPUT);
	SysTick_Init();
	buttonsInit();
	buttonConfiguration(PIN_SW3, TYPEMATIC , 50);

}

/* Función que se llama constantemente en un ciclo infinito */

void App_Run (void)
{
	if(wasPressed(PIN_SW3))
	{
		gpioToggle(PIN_LED_RED);
	}
	else if(wasReleased(PIN_SW3))
	{
		gpioWrite(PIN_LED_RED, HIGH);
		gpioWrite(PIN_LED_GREEN, HIGH);
	}else if(wasLkp(PIN_SW3))
	{
		gpioWrite(PIN_LED_RED, HIGH);
		gpioWrite(PIN_LED_GREEN, HIGH);
	}

}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/*******************************************************************************
 ******************************************************************************/
