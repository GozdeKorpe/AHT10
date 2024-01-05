/*
 * AHT10.h
 *
 *  Created on: Dec 27, 2023
 *      Author: gozde
 */

#ifndef INC_AHT10_H_
#define INC_AHT10_H_

#include "i2c.h"
void AHT10_Init();
void AHT10_Read(float *Temp, float *Hum);

#endif /* INC_AHT10_H_ */
