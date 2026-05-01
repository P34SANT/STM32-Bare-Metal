/*
 * tim.c
 *
 *  Created on: Mar 28, 2026
 *      Author: Peasant
 */
#include "tim.h"
#define TIM2EN           (1U<<0)
#define TIM3EN           (1U<<1)
#define CR1_CEN          (1U<<0)
#define SR_UIF           (1U<<0)
#define SR_CC1IF         (1U<<1)
#define CCMR_OC2M        (12)
#define CCMR_CC2S        (8)
#define CC1S_IN_TI1      (0b01)
#define CCMR_CC1S        (0)
#define OC2M_TOGGLE      (0b011)
#define CCER_CC2E        (1U<<4)
#define CCER_CC1E        (1U<<0)
#define CCER_CC1P        (1U<<1)
#define CCER_CC1NP       (1U<<3)
#define GPIOAEN          (1U<<0)
#define PA1              (1)
#define PA6              (6)
#define LED_PIN          (1U<<PA1)
#define MODER_ALT        (0b10)
#define AF1              (0b0001)
#define AF2              (0b0010)
#define AFR_AFRL1        (4)
#define AFR_AFRL6        (24)
void tim2_init(){
	//clk access
	RCC->APB1ENR |= TIM2EN;
	//tim prescaler
	TIM2->PSC = 1600 - 1 ;// 16 000 000 / 1600 = 10 000
	//auto reload
	TIM2->ARR = 10000 - 1; //10 000 / 10 000 = 1hz
	//clear counter
	TIM2->CNT = 0 ;
	//enable counter
	TIM2->CR1 = CR1_CEN;

}

void tim2_PA1outputCompare_init(){

    RCC->AHB1ENR |= GPIOAEN;

    GPIOA->MODER &= ~(0x3 << (2*PA1));
    GPIOA->MODER |=  (MODER_ALT << (2*PA1));

    GPIOA->AFR[0] &= ~(0xF << AFR_AFRL1);
    GPIOA->AFR[0] |=  (AF1 << AFR_AFRL1);

    RCC->APB1ENR |= TIM2EN;

    TIM2->PSC = 1600 - 1;
    TIM2->ARR = 10000 - 1;

    TIM2->CCR2 = 5000;

    TIM2->CCMR1 &= ~(0x7 << CCMR_OC2M);
    TIM2->CCMR1 |=  (OC2M_TOGGLE << CCMR_OC2M);

    TIM2->CCER |= CCER_CC2E;

    TIM2->CNT = 0;

    TIM2->CR1 = CR1_CEN;
}


void tim3_PA6inputCapture_init(){
	//gpio
    RCC->AHB1ENR |= GPIOAEN;

    GPIOA->MODER &= ~(0x3 << (2*PA6));
    GPIOA->MODER |=  (MODER_ALT << (2*PA6));

    GPIOA->AFR[0] &= ~(0xF << AFR_AFRL6);
    GPIOA->AFR[0] |=  (AF2 << AFR_AFRL6);
    //timer
    RCC->APB1ENR |= TIM3EN;

    TIM3->PSC = 16000 - 1; //each step 1ms


    TIM3->CCMR1 &= ~(0x3 << CCMR_CC1S);
    TIM3->CCMR1 |=  (CC1S_IN_TI1 << CCMR_CC1S);

    TIM3->CCER &= ~(CCER_CC1P);
	TIM3->CCER &= ~(CCER_CC1NP);//rising edge

    TIM3->CCER |= CCER_CC1E;//input en

    TIM3->CR1 = CR1_CEN;
}

void tim2_wait(){
	while(!(TIM2->SR & SR_UIF));
	TIM2->SR &= ~(SR_UIF);
}


void tim3_wait_Capture(){
	while(!(TIM3->SR & SR_CC1IF));
	TIM3->SR &= ~(SR_CC1IF);
}

int tim3_read_Capture(){
	int CCR_1 = TIM3->CCR1;
	return CCR_1;


}
