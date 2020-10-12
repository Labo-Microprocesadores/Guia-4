/***************************************************************************//**
  @file     board.h
  @brief    Board management
  @author   Nicolás Magliola
 ******************************************************************************/

#ifndef _BOARD_H_
#define _BOARD_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "gpio.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/***** BOARD defines **********************************************************/

// On Board User LEDs
#define PIN_LED_RED     PORTNUM2PIN(PB,22) // PTB22
#define PIN_LED_GREEN   PORTNUM2PIN(PE,26) // PTE26
#define PIN_LED_BLUE    PORTNUM2PIN(PB,21) // PTB21

#define LED_ACTIVE      LOW


// On Board User Switches
#define PIN_SW2         PORTNUM2PIN(PC,6) // PTA4
#define PIN_SW3         PORTNUM2PIN(PA,4) // PTA4

#define SW_ACTIVE       LOW
#define SW_INPUT_TYPE   INPUT_PULLDOWN

// Encoder pin's
#define ENCODER_A		PORTNUM2PIN(PC,8)
#define ENCODER_B		PORTNUM2PIN(PC,9)

// Lector de tarjetas
#define LECTOR_ENABLE 	PORTNUM2PIN(PA,2)
#define LECTOR_DATA		PORTNUM2PIN(PA,1)
#define LECTOR_CLOCK	PORTNUM2PIN(PC,3)
/*******************************************************************************
 ******************************************************************************/

#endif // _BOARD_H_
