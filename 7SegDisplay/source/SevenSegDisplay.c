/***************************************************************************//**
  @file     7SegDisplay.c
  @brief    Display configurations
  @author   Grupo 2
 ******************************************************************************/

#include "gpio.h"
#include "SevenSegDisplay.h"
#include "SysTick.h"



static uint8_t screen[4] = {NONE, NONE, NONE, NONE};
static pin_t displayPins[SEG_LEN] = {PIN_SEGA, PIN_SEGB, PIN_SEGC, PIN_SEGD,
							 	 	 PIN_SEGE, PIN_SEGF, PIN_SEGG, PIN_SEGDP};
static pin_t selectPins[SEL_LEN] = {PIN_SEL0, PIN_SEL1};

bool SevenSegDisplay_Init(void)
{
	static bool isInit = false;
	if(!isInit)
	{
		Timer_Init();
		uint8_t count;
		for(count=0; count<SEG_LEN ;count++)
		{
			gpioMode(displayPins[count], OUTPUT);
		}
		for(count=0; count<SEL_LEN ;count++)
		{
			gpioMode(selectPins[count], OUTPUT);
		}
	    //pongo los 2 pin a demultiplexar en 00 para que solo se prenda un 7segmentos
	    gpioWrite (selectPins[0], false);
	    gpioWrite (selectPins[1], false);

		int systickCallbackID = Timer_AddCallback(&SevenSegDisplay_PISR, 10000000L); //ver si queda este tiempo
	//idCounter = 1;
	}
	return true;
}

void SevenSegDisplay_PISR(void)
{
	SevenSegDisplay_PrintScreen();
}

bool SevenSegDisplay_ChangeCharacter(int screen_char, uint8_t new_char)
{
	screen[screen_char] = new_char;
}

/**
 * @brief print one character on one 7 segments display
 * @param character to print
 * @param array with pins to 7 segments display
 * @return printed succeed
 */
bool SevenSegDisplay_PrintCharacter(uint8_t character)
{
	bool result[8];
	int count;
	//convert the number to binary and then with shifts find each bit, put them in result array
	for(count=0; count<SEG_LEN; count++)
	{
		result[count]=(bool)(character & MASK);
		character = character>>1;
	}
	//turn on the pins according to result array
	for(count=0; count<SEG_LEN; count++)
	{
		gpioWrite(displayPins[count], result[count]);
	}
	return 0;
}

void SevenSegDisplay_PrintScreen(void)
{
	static int displayCounter = 0;
	SevenSegDisplay_PrintCharacter(screen[displayCounter]);
	if (displayCounter == (int)(sizeof(screen)/sizeof(screen[0])))
	{
		displayCounter = 0;
	}
	else
		displayCounter++;
}

void SevenSegDisplay_EraseScreen(void)
{
	for(int i = 1; i<((int)(sizeof(screen)/sizeof(screen[0]))); i++)
	{
		screen[i] = NONE;
	}
}


