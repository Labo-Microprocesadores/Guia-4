/***************************************************************************//**
  @file     7SegDisplay.c
  @brief    Display configurations
  @author   Grupo 2
 ******************************************************************************/

#include "7SegDisplay.h"
#include "SysTick.h"
#include "gpio.h"

typedef  struct
	{

	}Number_t;

bool printCaracter(uint8_t caracter)
{
	bool result[8];
	int count;
	for(count=0; count<8; count++)
	{
		result[count]=(bool)(caracter & controller);
		caracter = caracter>>1;
	}
	for(count=0; count<8; count++)
	{
		gpioWrite(pin_t 1, result[count]);
	}
	return 0;
}

