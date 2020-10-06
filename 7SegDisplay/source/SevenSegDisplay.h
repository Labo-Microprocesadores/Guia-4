/*
 * SevenSegDisplay.h
 *
 *  Created on: 3 oct. 2020
 *      Author: Grupo 2
 */

#ifndef SEVENSEGDISPLAY_H_
#define SEVENSEGDISPLAY_H_

#include "gpio.h"
#include <stdint.h>
#include <stdbool.h>
#include "Timer.h"
#include "board.h"

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
#define MASK	(uint8_t)0x01
#define NONE	(uint8_t)0x00

#define SEG_LEN	8
#define SEL_LEN	2

bool SevenSegDisplay_Init(void);

void SevenSegDisplay_PISR(void);

bool SevenSegDisplay_ChangeCharacter(int screen_char, uint8_t new_char);

bool SevenSegDisplay_PrintCharacter(uint8_t character);

void SevenSegDisplay_PrintScreen(void);

void SevenSegDisplay_EraseScreen(void);

//bool SevenSegDisplay_BlinkScreen(void);

//bool SevenSegDisplay_BlinkCharacter(void);






#endif /* SEVENSEGDISPLAY_H_ */
