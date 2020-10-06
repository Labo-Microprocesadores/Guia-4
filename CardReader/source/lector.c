/*
 * lector.c
 *
 *  Created on: 3 oct. 2020
 *      Author: grupo2
 */

#include "lector.h"
#include "SysTick.h"
#include "gpio.h"
#include "board.h"


/************************************************
 * Defines
 ************************************************/
#define WORD_LONG	40
#define CHAR_LONG	5
#define BITS_PER_CHAR 5
#define BUFFER_LEN 	(3*WORD_LONG*CHAR_LONG)
#define MAX_DATA_LEN 37
/*************************************************
 *  Funciones locales
 ************************************************/
void EnableIRQcallback(void);
void ClockIRQcallback(void);
bool find_ss_fs_es(uint16_t * ss, uint16_t * fs, uint16_t * es);
uint16_t find_fs(uint16_t ss);
uint16_t find_es(uint16_t ss);
/************************************************
 *  Variables internas del driver
 ************************************************/
static bool enable = false;
static bool event = false;

static uint16_t bit = 0;
static uint8_t message[BUFFER_LEN];


void Lector_Init(void)
{
	gpioMode(LECTOR_ENABLE, INPUT);
	gpioMode(LECTOR_DATA, INPUT);
	gpioMode(LECTOR_CLOCK, INPUT);

	gpioIRQ(LECTOR_ENABLE, GPIO_IRQ_MODE_BOTH_EDGES, &EnableIRQcallback);
	gpioIRQ(LECTOR_CLOCK, GPIO_IRQ_MODE_FALLING_EDGE, &ClockIRQcallback); // Busco el dato cuando esta estable no al cambiar

}

void EnableIRQcallback(void)
{
	int new_enable = gpioRead(LECTOR_ENABLE);
	if (!new_enable) // falling edge
	{
		enable = true;
	}
	else
	{
		enable = false;
		event = true;
	}
}

void ClockIRQcallback(void)
{
	if (enable)
	{
		uint8_t new_bit = gpioRead(LECTOR_DATA);
		message[bit] = new_bit;
		bit++;
	}
}

bool Lector_Event(void)
{
	return event;
}

bool Lector_GetData(card_t * data)
{
	uint16_t i, ss, fs , es;
	//card_t my_card;

	bool status = find_ss_fs_es(&ss, &fs, &es);
	if (status)
	{
		// parse and send
	}
	// Reset internal stuff
	event = false;
	bit = 0;
	for(i = 0; i<BUFFER_LEN; i++)
		message[i] = 0;

	return status;
}

bool find_ss_fs_es(uint16_t * ss, uint16_t * fs, uint16_t * es)
{
	uint16_t i, j, data, l_fs = 0, l_es = 0;
	bool find = false;
	for(i = 0; (i<(BUFFER_LEN-CHAR_LONG)) && !find; i++)
	{
		data = 0;
		for (j = 0; j<(CHAR_LONG); j++)
			data += message[i+j]<<j;

		if(data == 0xB)
		{
			l_fs = find_fs(i);
			if (l_fs != 0)
			{
				l_es = find_es(l_fs);
				if(l_fs != 0)
				{
					*ss = i;
					*fs = l_fs;
					*es = l_es;
					find = true;
				}
			}
		}
	}

	return find;
}

uint16_t find_fs(uint16_t ss)
{
	uint8_t i, j, data;
	for (i = 1; i<20 ; i++)
	{
		data = 0;
		for (j = 0; j<(CHAR_LONG); j++)
			data += message[i*CHAR_LONG+j+ss]<<j;

		if(data == 0xD)
		{
			return i*CHAR_LONG + ss;
		}
	}
	return 0;
}


uint16_t find_es(uint16_t fs)
{
	uint8_t i, j, data;
	for (i = 1; i<16 ; i++)
	{
		data = 0;
		for (j = 0; j<(CHAR_LONG); j++)
			data += message[i*CHAR_LONG+j+fs]<<j;

		if(data == 0x1F)
		{
			return i*CHAR_LONG+fs;
		}
	}
	return 0;
}
