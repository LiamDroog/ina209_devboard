/*
 * command.c
 *
 *  Created on: May 31, 2022
 *      Author: Liam
 */

#include "command.h"
#include "debug.h"
#include "ina209.h"
#include "i2c.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
void uart_handle_command(char *cmd) {
    switch(*cmd) {
    case 'i':;
        switch(*(cmd+1)){
            case '2':
                handle_i2c16_8_cmd(cmd); // needs to handle 16 / 8 bit stuff
                break;
                }
        break;

    case 'h':
		DBG_PUT("Help: \r\n");
		break;

        }

}


static inline const char* next_token(const char *ptr) {
    /* move to the next space */
    while(*ptr && *ptr != ' ') ptr++;
    /* move past any whitespace */
    while(*ptr && isspace(*ptr)) ptr++;

    return (*ptr) ? ptr : NULL;
}


static void handle_i2c16_8_cmd(const char *cmd){
	// format should be i2c read 0xXX and i2c write 0xXX 0xXXXX
    char buf[64];
    const char *rwarg = next_token(cmd);

    if (!rwarg) {
        DBG_PUT("rwarg broke\r\n");
        return;
    }

    const char *regptr = next_token(rwarg);
    if (!regptr) {
        DBG_PUT("regptr broke\r\n");
        return;
    }

    uint32_t reg;
    if (sscanf(regptr, "%lx", &reg) != 1) {
        DBG_PUT("reg broke\r\n");
        return;
    }

    switch(*rwarg) {
    case 'r':
        {
            uint16_t val;
            val = i2c1_read8_16(INA209, reg);
            sprintf(buf, "Device 0x%lx register 0x%lx = 0x%x\r\n", INA209, reg, val);
        }
        break;

    case 'w':
        {
            const char *valptr = next_token(regptr);
            if (!valptr) {
                sprintf(buf, "reg write 0x%lx: missing reg value\r\n", reg);
                break;
            }
            uint16_t val;
            if (sscanf(valptr, "%lx", &val) != 1) {
                sprintf(buf, "reg write 0x%lx: bad val '%s'\r\n", reg, valptr);
                break;
            }
            i2c1_write8_16(INA209, reg, val);

            sprintf(buf, "Device 0x%lx register 0x%lx wrote 0x%02lx\r\n", INA209, reg, val);
        }
        break;
    default:
        sprintf(buf, "reg op must be read or write, '%s' not supported\r\n", rwarg);
        break;
    }
    DBG_PUT(buf);

}
