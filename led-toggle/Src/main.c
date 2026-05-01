#include <stdint.h>
#define __IO               volatile
#define PERIPH_BASE        0x40000000UL
#define AHB1_OFFSET        0x00020000UL
#define AHB1_BASE          (PERIPH_BASE + AHB1_OFFSET)

#define GPIOA_BASE         (AHB1_BASE + 0x0000UL)
#define RCC_BASE           (AHB1_BASE + 0x3800UL)


#define GPIOAEN            (1U << 0)
#define LED_PIN            (1U << 1)

typedef struct{
	__IO uint32_t DUMMY[12];
	__IO uint32_t AHB1ENR;
}RCC_TypeDef;

typedef struct{
	__IO uint32_t MODER;
	__IO uint32_t DUMMY0[2];
	__IO uint32_t PUPDR;
	__IO uint32_t DUMMY1;
	__IO uint32_t ODR;
}GPIO_TypeDef;


#define RCC   ((RCC_TypeDef*)RCC_BASE)
#define GPIOA ((GPIO_TypeDef*)GPIOA_BASE)


int main(void)
{

	RCC->AHB1ENR |= GPIOAEN;


	GPIOA->MODER &= ~(3U << 2);
	GPIOA->MODER |=  (1U << 2);


	GPIOA->PUPDR  &= ~(3U << 2);

    while (1)
    {

    	GPIOA->ODR ^= LED_PIN;
        for (volatile int i = 0; i < 400000; i++);
    }
}
