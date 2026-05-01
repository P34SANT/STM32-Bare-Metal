/*
 * led.h
 *
 *  Created on: Mar 27, 2026
 *      Author: Peasant
 */

#ifndef UTIL_H_
#define UTIL_H_
#include "stm32f4xx.h"
#include <stdbool.h>
void led(bool state);
void led_init();
void sleep(int sec);
#endif /* UTIL_H_ */
