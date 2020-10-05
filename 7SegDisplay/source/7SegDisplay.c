/***************************************************************************//**
  @file     7SegDisplay.c
  @brief    Display configurations
  @author   Grupo 2
 ******************************************************************************/

#include "7SegDisplay.h"
#include "SysTick.h"
#include "gpio.h"

/**
 * @brief print one character on one 7 segments display
 * @param character to print
 * @param array with pins to 7 segments display
 * @return printed succeed
 */
bool printCaracter(uint8_t character, pin_t pins[])
{
	bool result[8];
	int count;
	//convert the number to binary and then with shifts find each bit, put them in result array
	for(count=0; count<8; count++)
	{
		result[count]=(bool)(character & controller);
		character = character>>1;
	}
	//turn on the pins acording to result array
	for(count=0; count<8; count++)
	{
		gpioWrite(pins[count], result[count]);
	}
	return 0;
}

