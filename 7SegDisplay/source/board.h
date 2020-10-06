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

// 7Segment Board
#define PIN_SEGA	PORTNUM2PIN(PB,2) // PTB2
#define PIN_SEGB	PORTNUM2PIN(PB,3) // PTB3
#define PIN_SEGC	PORTNUM2PIN(PB,10) // PTB10
#define PIN_SEGD	PORTNUM2PIN(PB,11) // PTB11
#define PIN_SEGE	PORTNUM2PIN(PC,11) // PTC11
#define PIN_SEGF	PORTNUM2PIN(PC,10) // PTB10
#define PIN_SEGG	PORTNUM2PIN(PB,20) // PTB20
#define PIN_SEGDP	PORTNUM2PIN(PC,5) // PTC5
#define PIN_SEL0	PORTNUM2PIN(PC,7) // PTC7
#define PIN_SEL1	PORTNUM2PIN(PC,0) // PTC0

/*******************************************************************************
 ******************************************************************************/

#endif // _BOARD_H_
