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
		bool lastState;
		int currentCount;
		int lkpTime;
		int typeTime;
		bool wasLkp;
		bool wasPressed;
		bool wasReleased;
	}Button_t;

static Button_t buttons[BUTTON_NUM];
static int timecounter;

static void systick_callback(void)
{

	int i;
	for( i=0 ; i<BUTTON_NUM ; i++ )
	{
		if( buttons[i].lastState && !gpioRead(buttons[i].pin) )
		{
			buttons[i].wasReleased = true;
			buttons[i].wasPressed = false;
			buttons[i].currentCount = 0;
			buttons[i].lastState = false;
		}
		else if( gpioRead(buttons[i].pin) )
		{
			buttons[i].wasReleased = false;
			buttons[i].wasPressed = true;
			buttons[i].lastState = false;

			if( buttons[i].lkp )
			{
				++buttons[i].currentCount == buttons[i].lkpTime ?  buttons[i].wasLkp = true : buttons[i].wasLkp = false;
			}
			else if( buttons[i].typematic && ++buttons[i].currentCount == buttons[i].typeTime)
			{
				 buttons[i].wasPressed= true;
				 buttons[i].currentCount = 0;
			}
		}
	}
}

bool wasPressed(pin_t button)
{
	int count;
	for(count=0;count<BUTTON_NUM;count++)
		{
			if(buttons[count].pin == button )
			{
				bool aux =buttons[count].wasPressed;
				if(aux)
					buttons[count].wasPressed = false;

				return aux ;
			}
		}

}

bool wasReleased(pin_t button)
{
	int count;
		for(count=0;count<BUTTON_NUM;count++)
			{
				if(buttons[count].pin == button )
				{
					bool aux =buttons[count].wasReleased;
					if(aux)
						buttons[count].wasReleased = false;

					return aux ;
				}
			}

}

bool wasLkp(pin_t button)
{
	int count;
		for(count=0;count<BUTTON_NUM;count++)
			{
				if(buttons[count].pin == button )
				{
					bool aux =buttons[count].wasLkp;
					if(aux)
						buttons[count].wasLkp = false;

					return aux ;
				}
			}
}
/**
 * @brief Configure button array based on user input
 * @param button, button's pin number
 * @param type, button's type of working (typematic, lkp)
 * @return Configure succeed
 */
bool buttonConfiguration(pin_t button, int type, int time)
{
	int count;
	//I move through the button arrangement and look for the same pin to reconfigure
	for(count=0;count<BUTTON_NUM;count++)
	{
		if(buttons[count].pin == button)
		{
			buttons[count].typefunction=type;
			if(type == LKP)
				buttons[count].lkpTime = time;
			else
				buttons[count].typeTime = time;
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

void buttonsInit(void)
{
	//ver que mas poner aca, no entiendo muy bien
	SysTick_AddCallback(&systick_callback, SYSTICK_ISR_PERIOD_S);
}
