/*
 * tim.h
 *
 *  Created on: Mar 28, 2026
 *      Author: Peasant
 */

#ifndef TIM_H_
#define TIM_H_
#include "stm32f4xx.h"
#include <stdint.h>
void tim2_init();
void tim2_wait();
void tim2_PA1outputCompare_init();
void tim3_PA6inputCapture_init();
void tim3_wait_Capture();
int tim3_read_Capture();
#endif /* TIM_H_ */
