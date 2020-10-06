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

#define PIN_CHARACTERA	PORTNUM2PIN()
#define PIN_CHARACTERB	PORTNUM2PIN()
#define PIN_CHARACTERC	PORTNUM2PIN()
#define PIN_CHARACTERD	PORTNUM2PIN()
#define PIN_CHARACTERE	PORTNUM2PIN()
#define PIN_CHARACTERF	PORTNUM2PIN()
#define PIN_CHARACTERG	PORTNUM2PIN()
#define PIN_CHARACTERDP	PORTNUM2PIN()


#define LED_ACTIVE      HIGH


// On Board User Switches
#define PIN_SW2         PORTNUM2PIN(PC,6) // PTA4
#define PIN_SW3         PORTNUM2PIN(PA,4) // PTA4

#define SW_ACTIVE       LOW
#define SW_INPUT_TYPE   INPUT_PULLDOWN


/*******************************************************************************
 ******************************************************************************/

#endif // _BOARD_H_
