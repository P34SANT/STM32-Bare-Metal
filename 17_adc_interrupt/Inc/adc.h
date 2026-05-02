#ifndef ADC_H_
#define ADC_H_

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdbool.h>
#define ADC_SR_ENDC  (1U<<1)
void start_conversion();
uint32_t adc_read();
void pb0_adc_init();
void pb0_adc_interrupt_init();

#endif
