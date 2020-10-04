/*
 * button.c
 *
 *  Created on: Sep 20, 2020
 *      Author: Carlos
 */


#include "button.h"
#include "SysTick.h"
#include "gpio.h"

static typedef  struct
	{
		pin_t pin;
		bool typematic;
		bool lkp;
		bool pullup;
		bool wasPressed;
		bool wasReleased;
		int currentCount;
		int lkpTime;
		bool wasLkp;
	}Button_t;

static Button_t buttons[BUTTON_NUM];
static int timecounter;

void systick_callback(void)
{

	int i;
	for(i=0;i<BUTTON_NUM;i++)
	{
		if(buttons[i].wasPressed && ((gpioRead(buttons[i].pin) && buttons[i].pullup)||(!gpioRead(buttons[i].pin) && !buttons[i].pullup)) )
		{
			buttons[i].wasReleased = true;
			buttons[i].wasPressed = false;
			buttons[i].currentCount = 0;
			buttons[i].wasLkp = false;
		}
		else
		{
			buttons[i].wasReleased = false;
			buttons[i].wasPressed = true;
		}
		if(buttons[i].lkp || buttons[i].typematic)
		{
			++buttons[i].currentCount == buttons[i].lkpTime ?  buttons[i].wasLkp = true : buttons[i].wasLkp = false;
		}
	}
}
