/***************************************************************************//**
  @file     Button.c
  @brief    Button configurations
  @author   Carlos and Matias
 ******************************************************************************/


#include "button.h"
#include "SysTick.h"
#include "gpio.h"

static typedef  struct
	{
		pin_t pin=-1;
		enum type typefunction = -1;
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

/**
 * @brief Configure button array based on user input
 * @param button, button's pin number
 * @param type, button's type of working (typematic, lkp)
 * @return Configure succeed
 */
bool buttonConfiguration(pin_t button, int type)
{
	int count;
	//I move through the button arrangement and look for the same pin to reconfigure
	for(count=0;count<BUTTON_NUM;count++)
	{
		if(buttons[count].pin == button)
		{
			buttons[count].typefunction=type;
			return true;
		}
	}
	//if the pin was not there use an empty space
	for(count=0;count<BUTTON_NUM;count++)
		{
		if(buttons[count].pin==-1)
		{
			buttons[count].pin=button;
			buttons[count].typefunction=type;
			return true;
		}
	}
	//if there is no empty space for the value
	return false;
}
