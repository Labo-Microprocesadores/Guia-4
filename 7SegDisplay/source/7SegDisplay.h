/*
 * 7SegDisplay.h
 *
 *  Created on: 3 oct. 2020
 *      Author: Grupo 2
 */

#ifndef SEVENSEGDISPLAY_H_
#define SEVENSEGDISPLAY_H_


#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"
#include "Timer.h"

#define ZERO	(uint8_t)0x3F
#define ONE		(uint8_t)0x06
#define TWO		(uint8_t)0x5B
#define THREE	(uint8_t)0x4F
#define FOUR	(uint8_t)0x66
#define FIVE	(uint8_t)0x6D
#define SIX		(uint8_t)0x7D
#define SEVEN	(uint8_t)0x07
#define EIGHT	(uint8_t)0x7F
#define NINE	(uint8_t)0x6F
#define LINE	(uint8_t)0x80
#define NONE	(uint8_t)0x00

uint8_t screen[4] = {NONE, NONE, NONE, NONE};

bool SevenSegDisplay_Init(void);

bool SevenSegDisplay_PrintCharacter(uint8_t);

bool SevenSegDisplay_PrintScreen(void);

bool SevenSegDisplay_EraseScreen(void);

//bool SevenSegDisplay_BlinkScreen(void);

bool SevenSegDisplay_BlinkCharacter(void);






#endif /* SEVENSEGDISPLAY_H_ */
