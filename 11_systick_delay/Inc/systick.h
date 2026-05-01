/*
 * systick.h
 *
 *  Created on: Mar 27, 2026
 *      Author: Peasant
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "stm32f4xx.h"
#include <stdint.h>

void systick_init(void);
void systick_delay_ms(uint32_t ms);

#endif
