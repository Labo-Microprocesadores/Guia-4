/***************************************************************************//**
  @file     Button.c
  @brief    Button configurations
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
	uint8_t controller=0x01;
	int count;
	for(count=0; count<8; count++)
	{
		result[count]=caracter & controller;
		caracter>>1;
	}
	return 0;
}


