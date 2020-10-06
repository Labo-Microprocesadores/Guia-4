/*
 * lector.h
 *
 *  Created on: 3 oct. 2020
 *      Author: grupo2
 */

#ifndef LECTOR_H_
#define LECTOR_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
	uint8_t card_number[19];
	uint8_t extra_data[15];
}card_t;

/*
 * Inicializa el lector de tarjetas
 */
void Lector_Init(void);

/*
 * Devuelve si hay un evento para levantar del lector
 */
bool Lector_Event(void);


/*
 * Escribe un array de datos en el puntero data
 * Devuelve true si fue exitoso, false en caso de error
 */
bool Lector_GetData(card_t * data);


#endif /* LECTOR_H_ */
