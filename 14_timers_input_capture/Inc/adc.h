#ifndef ADC_H_
#define ADC_H_

#include "stm32f4xx.h"
#include <stdint.h>

void start_conversion();
uint32_t adc_read();
void pb0_adc_init();

#endif
