/***************************************************************************//**
  @file     App.c
  @brief    Application functions
  @author   Nicolás Magliola
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "board.h"
#include "gpio.h"
#include "SysTick.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define LED PORTNUM2PIN(PB,23) //PTA0
#define SW PORTNUM2PIN(PC,0)
#define DELAY 8
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void delayLoop(uint32_t);
void callback_systick(void);
void callback_switch(void);
/***
#define VECTORTABLE_SIZE        (NUMBER_OF_INT_VECTORS)    // size of the used vector tables
                                         // see startup file startup_ARMCM3.c
#define VECTORTABLE_ALIGNMENT   (0x100U) // 16 Cortex + 32 ARMCM3 = 48 words
                                         // next power of 2 = 256
// externals from startup_ARMCM3.c
extern uint32_t __VECTOR_TABLE[VECTORTABLE_SIZE];        // vector table ROM
//new vector table in RAM, same size as vector table in ROM
uint32_t vectorTable_RAM[VECTORTABLE_SIZE] __attribute__(( aligned (VECTORTABLE_ALIGNMENT) ));
***/

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
    gpioMode(PIN_SW2, INPUT_PULLUP);
    gpioMode(LED, OUTPUT);
    gpioMode(PIN_LED_RED, OUTPUT);

    //gpioWrite(LED, HIGH);
    gpioWrite(PIN_LED_RED, HIGH);
    SysTick_Init(&callback_systick);
    gpioIRQ(PIN_SW2, GPIO_IRQ_MODE_FALLING_EDGE, callback_switch);
}

static bool baliza = false;
static uint32_t b_counter = DELAY;
static bool interrupted = false;
/* Función que se llama constantemente en un ciclo infinito */

void App_Run (void)
{
	if(interrupted)
	{
		delayLoop(7150000UL);
		interrupted = false;
	}
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static void delayLoop(volatile uint32_t veces)
{
    while (veces--);
}

void callback_systick(void)
{
	if (baliza)
	{
		if (--b_counter == 0)
		{
			b_counter = DELAY;
			gpioToggle(LED);
		}
	}
}

void callback_switch(void)
{
	PORT_ClearInterruptFlag(PIN_SW2);
	if (!interrupted )
	{
		interrupted = true;
		baliza = !baliza;
		gpioToggle(PIN_LED_RED);
		if(baliza)
		{
			gpioWrite(LED, HIGH);
			b_counter = DELAY; //prendo la baliza
		}
		else
			gpioWrite(LED, LOW); // apago la baliza
	}
}
/*******************************************************************************
 ******************************************************************************/
