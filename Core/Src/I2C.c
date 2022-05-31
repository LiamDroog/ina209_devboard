#include <I2C.h>
#include <stdio.h>
#include "stm32l0xx_hal.h"
#include "debug.h"
#include "main.h"
extern I2C_HandleTypeDef hi2c1;

uint16_t i2c1_read8_16(uint8_t addr, uint8_t register_pointer){
	uint16_t val = hi2c_read8_16(hi2c1, addr, register_pointer);
	return val;
}
void i2c1_write8_16(uint8_t addr, uint8_t register_pointer, uint16_t register_value){
	hi2c_write8_16(hi2c1, addr, register_pointer, register_value);
	return;
}

uint16_t hi2c_read8_16(I2C_HandleTypeDef hi2c, uint8_t addr, uint8_t register_pointer)
{
    uint16_t return_value = 0;
	HAL_StatusTypeDef status = HAL_OK;
    status = HAL_I2C_Mem_Read(&hi2c, addr << 1, (uint8_t)register_pointer, I2C_MEMADD_SIZE_8BIT, &return_value, 2, 100);
    if (status != HAL_OK) {
            char buf[64];
            sprintf(buf, "I2C8_16 read from 0x%x register 0x%x failed\r\n", addr, register_pointer);
            DBG_PUT(buf);
        }
    return return_value;
}

void hi2c_write8_16(I2C_HandleTypeDef hi2c, uint8_t addr, uint8_t register_pointer, uint16_t register_value)
{
    uint16_t dataBuffer[1];
	HAL_StatusTypeDef status = HAL_OK;
    dataBuffer[0] = register_value;
    status = HAL_I2C_Mem_Write(&hi2c, addr << 1, (uint8_t)register_pointer, I2C_MEMADD_SIZE_8BIT, dataBuffer, 2, 100);
    if (status != HAL_OK) {
            char buf[64];
            sprintf(buf, "I2C8_16 write to 0x%x failed: 0x%x\r\n", addr, register_pointer);
            DBG_PUT(buf);
        }
}
