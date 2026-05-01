/*
 * led.c
 *
 *  Created on: Mar 27, 2026
 *      Author: Peasant
 */

#include <util.h>
#define GPIOAEN      (1U<<0)
#define PIN1         (1U<<1)
#define LED_PIN      (PIN1)


void led_init(){
	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER &= ~(3U << 2);
	GPIOA->MODER |=  (1U << 2);
	GPIOA->PUPDR  &= ~(3U << 2);

}

void led(bool state){
	if (state){
		GPIOA->BSRR = (1U<<17);
	}else{
		GPIOA->BSRR = LED_PIN;
	}
}

void sleep(int sec){
	for(volatile int i=0;i<16000000 * sec;i++);
}
