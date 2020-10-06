/***************************************************************************//**
  @file     7SegDisplay.c
  @brief    Display configurations
  @author   Grupo 2
 ******************************************************************************/

#include "7SegDisplay.h"
#include "SysTick.h"
#include "gpio.h"



bool SevenSegDisplay_Init(pin_t pins[], uint8_t tamanio)
{
	Timer_Init();
    uint8_t count;
	for(count=0; count<tamanio;count++)
	{
	    gpioMode(pins[count], OUTPUT);
	}
	int systickCallbackID = Timer_AddCallback(&SevenSegDisplay_PISR, 10000000L); //ver si queda este tiempo
	//idCounter = 1;
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
bool SevenSegDisplay_PrintCharacter(uint8_t character, pin_t pins[])
{
	bool result[8];
	int count;
	//convert the number to binary and then with shifts find each bit, put them in result array
	for(count=0; count<8; count++)
	{
		result[count]=(bool)(character & controller);
		character = character>>1;
	}
	//turn on the pins according to result array
	for(count=0; count<8; count++)
	{
		gpioWrite(pins[count], result[count]);
	}
	return 0;
}

void SevenSegDisplay_PrintScreen(pin_t pins[])
{
	static int displayCounter = 0;
	SevenSegDisplay_PrintCharacter(screen[displayCounter], pins);
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


