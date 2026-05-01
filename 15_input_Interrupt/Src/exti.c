/*
 * exti.c
 *
 *  Created on: Apr 2, 2026
 *      Author: Peasant
 */

#include "exti.h"

#define GPIOAEN          (1U<<0)
#define PIN0             (0)
#define Button_PIN       (PIN0)
#define SYSCFGEN         (1U<<14)
#define CR1_EXTI0        (0)
#define IMR_MR0          (1U<<0)
#define FTSR_TR0         (1U<<0)


void pa0EXTI_init(void) {
    __disable_irq();

    // 1. Enable Clock for GPIOA and SYSCFG
    RCC->AHB1ENR |= GPIOAEN;
    RCC->APB2ENR |= SYSCFGEN;

    // 2. Set PA0 as Input
    GPIOA->MODER &= ~(0x3 << (2 * PIN0));

    // 3. Set PA0 as Pull-up (Essential for Falling Edge trigger)
    GPIOA->PUPDR &= ~(0x3 << (2 * PIN0));
    GPIOA->PUPDR |= (0x1 << (2 * PIN0)); // 01: Pull-up

    // 4. Map EXTI0 to PA0
    SYSCFG->EXTICR[0] &= ~(0xF << CR1_EXTI0);

    // 5. Unmask EXTI0
    EXTI->IMR |= IMR_MR0;

    // 6. Set Falling Edge Trigger
    EXTI->RTSR &= ~FTSR_TR0; // Disable Rising (optional)
    EXTI->FTSR |= FTSR_TR0;  // Enable Falling

    // 7. NVIC Configuration
    NVIC_SetPriority(EXTI0_IRQn, 0); // Set priority if needed
    NVIC_EnableIRQ(EXTI0_IRQn);

    __enable_irq();
}
