/*
 * sccb.h
 *
 *  Created on: Feb 7, 2022
 *      Author: Liam
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_
#include "stm32l0xx_hal.h"

uint16_t i2c1_read8_16(uint8_t addr, uint8_t register_pointer);
void i2c1_write8_16(uint8_t addr, uint8_t register_pointer, uint16_t register_value);
uint16_t hi2c_read8_16(I2C_HandleTypeDef hi2c, uint8_t addr, uint8_t register_pointer);
void hi2c_write8_16(I2C_HandleTypeDef hi2c, uint8_t addr, uint8_t register_pointer, uint16_t register_value);


#endif /* INC_I2C_H_ */
