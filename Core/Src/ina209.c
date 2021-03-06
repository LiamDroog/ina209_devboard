/*
 *  INA209.c
 *	Drivers for INA209 Current Sense
 *	See Datasheet for possible register values
 *	https://www.ti.com/lit/ds/symlink/ina209.pdf
 *
 *	INA209 registers are Most Significant Byte first - LSB PEEPS BEWARE
 *	(MSB peeps just toss the _flip_byte_order() function)
 *  Created on: May 10, 2022
 *  Author: Liam Droog
 */

#include <ina209.h>
#include "I2C.h"
uint16_t get_configuration(uint8_t addr){
	// POR is x399F
	uint16_t rtn = _flip_byte_order(i2c1_read8_16(addr, 0x00));
	return rtn;
}

void set_configuration(uint8_t addr, uint16_t val){
	i2c1_write8_16(addr, 0x02, _flip_byte_order(val));
	return;
}

uint16_t get_status_flags(uint8_t addr){
	//	POR is x0000
	uint16_t rtn = _flip_byte_order(i2c1_read8_16(addr, 0x01));
	return rtn;
}

uint16_t get_control_register(uint8_t addr){
	uint16_t rtn = _flip_byte_order(i2c1_read8_16(addr, 0x02));
	return rtn;
}
void set_control_register(uint8_t addr, uint16_t val){
	i2c1_write8_16(addr, 0x02, _flip_byte_order(val));
	return;
}
uint16_t get_shunt_voltage(uint8_t addr){
	uint16_t rtn = _flip_byte_order(i2c1_read8_16(addr, 0x03));
	return rtn;
}

uint16_t get_bus_voltage(uint8_t addr){
	uint16_t rtn = _flip_byte_order(i2c1_read8_16(addr, 0x04));
	return rtn;
}

uint16_t get_power(uint8_t addr){
	uint16_t rtn = _flip_byte_order(i2c1_read8_16(addr, 0x05));
	return rtn;
}

// Current defaults to 0 on POR before calibration register (x16) is set
uint16_t get_current(uint8_t addr){
	uint16_t rtn = _flip_byte_order(i2c1_read8_16(addr, 0x06));
	return rtn;
}

uint16_t get_shunt_voltage_peak_pos(uint8_t addr){
	uint16_t rtn = _flip_byte_order(i2c1_read8_16(addr, 0x07));
	return rtn;
}

uint16_t get_shunt_voltage_peak_neg(uint8_t addr){
	uint16_t rtn = _flip_byte_order(i2c1_read8_16(addr, 0x08));
	return rtn;
}

uint16_t get_bus_voltage_peak_max(uint8_t addr){
	uint16_t rtn = _flip_byte_order(i2c1_read8_16(addr, 0x09));
	return rtn;
}

uint16_t get_bus_voltage_peak_min(uint8_t addr){
	uint16_t rtn = _flip_byte_order(i2c1_read8_16(addr, 0x0A));
	return rtn;
}

uint16_t get_power_peak(uint8_t addr){
	uint16_t rtn = _flip_byte_order(i2c1_read8_16(addr, 0x0B));
	return rtn;
}

uint16_t get_power_overlimit(uint8_t addr){
	uint16_t rtn = _flip_byte_order(i2c1_read8_16(addr, 0x11));
	return rtn;
}

void set_power_overlimit(uint8_t addr, uint16_t val){
	i2c1_write8_16(addr, 0x11, _flip_byte_order(val));
	return;
}

uint16_t get_bus_voltage_overlimit(uint8_t addr){
	uint16_t rtn = _flip_byte_order(i2c1_read8_16(addr, 0x12));
	return rtn;
}

void set_bus_voltage_overlimit(uint8_t addr, uint16_t val){
	i2c1_write8_16(addr, 0x12, _flip_byte_order(val));
	return;
}

uint16_t get_bus_voltage_underlimit(uint8_t addr){
	uint16_t rtn = _flip_byte_order(i2c1_read8_16(addr, 0x13));
	return rtn;
}

void set_bus_voltage_underlimit(uint8_t addr, uint16_t val){
	i2c1_write8_16(addr, 0x13, _flip_byte_order(val));
	return;
}

uint16_t get_calibration(uint8_t addr){
	uint16_t rtn = _flip_byte_order(i2c1_read8_16(addr, 0x16));
	return rtn;
}

void set_calibration(uint8_t addr, uint16_t val){
	i2c1_write8_16(addr, 0x16, _flip_byte_order(val));
	return;
}

void init_ina209(uint8_t addr){
	// clear POR flags
	for (uint8_t i=0; i<5; i++){get_status_flags(addr);}
	// set calibration register
	set_calibration(addr, 0xF9A6);
	// set power overlimit
	set_power_overlimit(addr, 0x0100);
	// set bit masks
	set_control_register(addr, 0x0000);
	HAL_Delay(2);
	set_control_register(addr, 0xFFFF);
	return;
}

void reset_ina209(uint8_t addr){
	set_control_register(addr, 0x0000);
	HAL_Delay(2);
	set_control_register(addr, 0xFFFF);
}

