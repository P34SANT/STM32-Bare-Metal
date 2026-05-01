#include "stm32f4xx.h"

#define GPIOAEN      (1U<<0)
#define PIN1         (1U<<1)
#define PIN0         (1U<<0)
#define LED_PIN      (PIN1)
#define Button_PIN   (PIN0)

int main(void){

    RCC->AHB1ENR |= GPIOAEN;


    GPIOA->MODER &= ~(3U << 2);
    GPIOA->MODER |=  (1U << 2);


    GPIOA->MODER &= ~(3U << 0);

    GPIOA->PUPDR &= ~(3U << 0);
    GPIOA->PUPDR |=  (2U << 0);

    while(1){

        if(GPIOA->IDR & Button_PIN){
            GPIOA->BSRR = LED_PIN;
        }else{
            GPIOA->BSRR = (LED_PIN << 16);
        }

        for(int i = 0 ; i < 400000 ; i++);
    }
}
