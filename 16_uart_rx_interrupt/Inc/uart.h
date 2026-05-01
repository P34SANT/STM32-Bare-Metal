/*
 * uart.h
 *
 *  Created on: Mar 25, 2026
 *      Author: Peasant
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


void UART2_init(void);
char UART2_read(void);
void UART2_write(int ch);
void UART2_write_string(const char *str);
void UART2_RXinterrupt_init ();
bool SR_FLAG ();

#endif
