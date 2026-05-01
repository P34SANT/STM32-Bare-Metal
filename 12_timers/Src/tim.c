/*
 * tim.c
 *
 *  Created on: Mar 28, 2026
 *      Author: Peasant
 */
#include "tim.h"
#define TIM2EN  (1U<<0)
#define CR1_CEN (1U<<0)
#define SR_UIF  (1U<<0)



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

void tim2_wait(){
	while(!(TIM2->SR & SR_UIF));
	TIM2->SR &= ~(SR_UIF);
}
