#include "stm32f4xx.h"


#define GPIOAEN      (1U<<0)
#define PIN1         (1U<<1)
#define LED_PIN      (PIN1)

int main(void){


	RCC->AHB1ENR |= GPIOAEN;


	GPIOA->MODER &= ~(3U << 2);
	GPIOA->MODER |=  (1U << 2);


	GPIOA->PUPDR  &= ~(3U << 2);
	while(1){

		GPIOA->BSRR = LED_PIN;
			for(int i =0 ; i < 400000 ; i++);

		GPIOA->BSRR = (1U<<17);
			for(int i =0 ; i < 400000 ; i++);
	}
}
