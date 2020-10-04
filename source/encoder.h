/*
 * encoder.h
 *
 *  Created on: 25 sep. 2020
 *      Author: Grupo 2
 */

#ifndef ENCODER_H_
#define ENCODER_H_

void Encoder_Init(void);

int Encoder_GetMove(void);

void Encoder_PISR(void);
void Encoder_ISR(void);

#endif /* ENCODER_H_ */
