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
#include "SysTick.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define LED PORTNUM2PIN(PB,23) //PTA0
#define SW PORTNUM2PIN(PC,0)
#define DELAY 6
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void delayLoop(uint32_t veces);
void callback(void);


static uint32_t b_counter = DELAY;
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
    gpioMode(SW, INPUT_PULLUP);
    gpioMode(LED, OUTPUT);
    gpioMode(PIN_LED_RED, OUTPUT);

    //gpioWrite(LED, HIGH);
    gpioWrite(PIN_LED_RED, HIGH);
    SysTick_Init();
    SysTick_AddCallback(&callback, 12500000L*8); //1s
}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run (void)
{

}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void delayLoop(volatile uint32_t veces)
{
    while (veces--);
}

void callback(void)
{
	static int i = 0;

	i++;
	gpioToggle(PIN_LED_RED);

	if (i == 5){
		Systick_ChangeCallbackTime(&callback, 12500000L*4);	//Makes it faster after 5 cycles.

	}

	if (i == 15){

		Systick_ClrCallback(&callback);	//Cancels the toggle after 15 cycles.
	}

}

/*******************************************************************************
 ******************************************************************************/
