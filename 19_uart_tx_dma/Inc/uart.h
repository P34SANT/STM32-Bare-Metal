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

#define DMA_TCIF6       (1U<<21)
#define DMA_CTCIF6 		(1U<<21)

void UART2_init(void);
char UART2_read(void);
void UART2_write(int ch);
void UART2_write_string(const char *str);
void UART2_RXinterrupt_init ();
void dma1_stream6_init(uint32_t src , uint32_t dst , uint32_t len);


bool SR_FLAG ();

#endif
