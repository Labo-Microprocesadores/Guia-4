/*
 * Led.c
 *
 *  Created on: 3 oct. 2020
 *      Author: Grupo 2
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
void Led_PISR(void);

bool Led_Init (void)
{
	int timerCallbackID = Timer_AddCallback(&Led_PISR, 10000000L);
	return true;
}

void Led_PISR(void){


}
