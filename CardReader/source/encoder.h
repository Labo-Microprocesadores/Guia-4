/*
 * encoder.h
 * Created on: Sep. 2020
 * Author: Grupo II
 */

#ifndef ENCODER_H_
#define ENCODER_H_

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/*
 * @brief Inicializa los pines del driver del encoder
 */
void Encoder_Init(void);

/*
 * @brief Para verificar si se realizo algun movimiento
 * @return 0-> sin movimiento, 1-> movimiento en sentido horario, -1 -> sentido antihorario
 */
int Encoder_GetMove();

void Encoder_PISR(void);
void Encoder_ISR(void);

#endif /* ENCODER_H_ */
