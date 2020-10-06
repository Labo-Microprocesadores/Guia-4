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


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define TAMANIO_PINES (uint8_t)10

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void delayLoop(uint32_t veces);


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
    pin_t pins[TAMANIO_PINES];
    SevenSegDisplay_Init(pins, TAMANIO_PINES);
 //harcodeado para prueba
    //pongo los 2 pin a demultiplexar en 00 para que solo se prenda un 7segmentos
    gpioWrite (pins[8], false);
    gpioWrite (pins[9], false);

    SevenSegDisplay_PrintCharacter(7, pins)
 //fin de harcodeo
}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run (void)
{
    delayLoop(4000000UL);
    gpioToggle(PIN_LED_BLUE);
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void delayLoop(uint32_t veces)
{
    while (veces--);
}


/*******************************************************************************
 ******************************************************************************/
