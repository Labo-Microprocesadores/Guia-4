/***************************************************************************//**
  @file     App.c
  @brief    Application functions
  @author   Nicolás Magliola
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "gpio.h"
#include "board.h"
#include "SevenSegDisplay.h"
#include "encoder.h"
#include "lector.h"
#include "MplxLed.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define TAMANIO_PINES (uint8_t)10

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/



/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
	gpioMode(TP, OUTPUT);
	gpioWrite(TP, LOW);

    gpioMode(PIN_LED_RED, OUTPUT);
    gpioMode(PIN_LED_GREEN, OUTPUT);
    gpioWrite(PIN_LED_RED,HIGH);
    gpioWrite(PIN_LED_GREEN, HIGH);

    Encoder_Init();
    Lector_Init();
    SevenSegDisplay_Init();
    SevenSegDisplay_SetBright(MAX);
    MplxLed_Init();
    MplxLed_InfiniteBlink(1,NORMAL);
}

/* Función que se llama constantemente en un ciclo infinito */

void App_Run (void)
{
	static card_t my_message;
	static const uint8_t nums[] = {ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE};

	int8_t moves = Encoder_GetMove();

	if (Lector_Event())
	{
		bool result = Lector_GetData(&my_message);
		if (result)
		{
			gpioWrite(PIN_LED_GREEN, LOW);
			gpioWrite(PIN_LED_RED, HIGH);
			uint8_t datos[30];
			uint8_t i;
			for(i = 0; i<my_message.number_len; i++)
			{
				 datos[i] = nums[my_message.card_number[i]];
			}
			SevenSegDisplay_EraseScreen();
			SevenSegDisplay_WriteBuffer(datos, my_message.number_len, 0 );
			SevenSegDisplay_SetPos(0);
		}
		else
		{
			gpioWrite(PIN_LED_GREEN, HIGH);
			gpioWrite(PIN_LED_RED,LOW);
			uint8_t i;
			for(i = 0; i<4; i++)
			{
				SevenSegDisplay_ChangeCharacter(i, EIGHT);
			}
		}
	}

	if(moves != 0)
	{
		MplxLed_Toggle(0);
		SevenSegDisplay_Swipe(my_message.number_len);
	}

}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


/*******************************************************************************
 ******************************************************************************/
