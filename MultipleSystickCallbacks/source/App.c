/***************************************************************************//**
  @file     App.c
  @brief    Application functions
  @author   Nicolás Magliola
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "gpio.h"
#include "Timer.h"
#include "Led.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define SW PORTNUM2PIN(PC,0)
#define DELAY 6
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
int id1, id2;
/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
	gpioMode(SW, INPUT_PULLUP);
    Timer_Init();
    Led_Init();

    //Led_OnForDefinedTime(LED_RED, 125*64); //8s
    //Led_CustomBlink(LED_RED, 3, 125*32, 125*8);
    //Led_CustomRepetitionBlink(LED_RED, 4, 125*240, 3, 125*40, 125*32);
    Led_InfiniteBlink(LED_RED, FAST);
    Led_InfiniteBlink(LED_GREEN, SLOW);
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



/*******************************************************************************
 ******************************************************************************/
