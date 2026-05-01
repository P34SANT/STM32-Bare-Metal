#include "uart.h"
#include <stdio.h>
#include <stdint.h>

#define GPIOAEN      (1U<<0)
#define PIN1         (1U<<1)
#define LED_PIN      (PIN1)



char KEY ;
int main(void){

    UART2_init();

	RCC->AHB1ENR |= GPIOAEN;


	GPIOA->MODER &= ~(3U << 2);
	GPIOA->MODER |=  (1U << 2);


	GPIOA->PUPDR  &= ~(3U << 2);

    while(1){

    	KEY = UART2_read();
    	if(KEY == '0'){
		GPIOA->BSRR = LED_PIN;
		for(int i =0 ; i < 400000 ; i++);
		UART2_write ('0');
		UART2_write_string("off\n");
			for(int i =0 ; i < 400000 ; i++);
    	}

		if(KEY == '1'){
		GPIOA->BSRR = (1U<<17);
		for(int i =0 ; i < 400000 ; i++);
		UART2_write('1');
		UART2_write_string("on\n");
		for(int i =0 ; i < 400000 ; i++);


    }
}
}


