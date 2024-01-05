/*
 * AHT10.c
 *
 *  Created on: Dec 27, 2023
 *      Author: gozde
 */
#include "AHT10.h"

#define AHT10_ADRESS 0x70

void AHT10_Init(){
	uint8_t readBuffer; // recieves the status information
	HAL_Delay(40);
	HAL_I2C_Master_Receive(&hi2c1,AHT10_ADRESS,&readBuffer,1,HAL_MAX_DELAY);
	if((readBuffer & 0x08) == 0x00){
		uint8_t sendBuffer[3] = {0xBE, 0x08, 0x00};
		HAL_I2C_Master_Transmit(&hi2c1,AHT10_ADRESS,sendBuffer,3,HAL_MAX_DELAY);
	}
}
 void AHT10_Read(float *Temp, float *Hum) {
	 uint8_t sendBuffer[3] = {0xAC, 0x33, 0x00};
	 uint8_t readBuffer[6];
	 HAL_I2C_Master_Transmit(&hi2c1,AHT10_ADRESS,sendBuffer,3,HAL_MAX_DELAY);
	 HAL_Delay(75);
	 HAL_I2C_Master_Receive(&hi2c1,AHT10_ADRESS,readBuffer,6,HAL_MAX_DELAY);

	 if ((readBuffer[0] & 0x80) == 0x00){
		 uint32_t data = 0;
		 data = ((uint32_t)readBuffer[3] >> 4) + ((uint32_t)readBuffer[2] << 4) + ((uint32_t)readBuffer[1] << 12);
		 *Hum = data * 100.0f / (1 << 20);

		 data = (((uint32_t)readBuffer[3] & 0x0F) << 16) + ((uint32_t)readBuffer[4] << 8) + (uint32_t)readBuffer[5];
		 *Temp = data * 200.0f / (1 << 20) - 50;
	 }
 }
