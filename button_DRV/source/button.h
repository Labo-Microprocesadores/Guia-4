/***************************************************************************//**
  @file     Button.c
  @brief    Button configurations
  @author   Carlos and Matias
 ******************************************************************************/

#ifndef BUTTON_H_
#define BUTTON_H_
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define BUTTON_NUM 1
#define TIME_BASE 3

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

	enum type{NORMAL,TYPEMATIC, LKP};


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
void buttonsInit(void);

bool wasPressed(pin_t button);

bool wasReleased(pin_t button);

bool buttonConfiguration(pin_t button, int type,int time);


#endif /* BUTTON_H_ */
