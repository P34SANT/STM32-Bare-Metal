/*
 * adc.c
 *
 *  Created on: Mar 27, 2026
 *      Author: Peasant
 */

#include "adc.h"

#define ADC1ENR      (1U<<8)

#define GPIOBEN      (1U<<1)

#define PB0          (0)

#define CH8          (8)

#define SQ1          (0)

#define seqlen       (0)

#define ADCON        (1U<<0)

#define SWCADC       (1U<<30)

#define ADC_SR_ENDC  (1U<<1)



void pb0_adc_init(){

    // enable clock
    RCC->AHB1ENR |= GPIOBEN;
    RCC->APB2ENR |= ADC1ENR;

    // set PB0 analog
    GPIOB->MODER &= ~(0b11 << (PB0*2));
    GPIOB->MODER |=  (0b11 << (PB0*2));

    // select channel 8
    ADC1->SQR3 = (CH8 << SQ1);

    // sequence length = 1
    ADC1->SQR1 = seqlen;

    // enable adc
    ADC1->CR2 |= ADCON;
}



void start_conversion(){

    ADC1->CR2 |= SWCADC;

}



uint32_t adc_read(){

    while(!(ADC1->SR & ADC_SR_ENDC)){}

    return ADC1->DR;

}

