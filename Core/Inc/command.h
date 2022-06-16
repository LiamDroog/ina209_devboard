/*
 * command.h
 *
 *  Created on: May 31, 2022
 *      Author: Liam
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_

void uart_handle_command(char *cmd);
static inline const char* next_token(const char *ptr);
static void handle_i2c16_8_cmd(const char *cmd);
#define INA209 0x42
#endif /* INC_COMMAND_H_ */
