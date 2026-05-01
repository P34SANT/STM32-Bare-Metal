#define PERIPH_BASE        0x40000000UL
#define AHB1_OFFSET        0x00020000UL
#define AHB1_BASE          (PERIPH_BASE + AHB1_OFFSET)

#define GPIOA_BASE         (AHB1_BASE + 0x0000UL)
#define RCC_BASE           (AHB1_BASE + 0x3800UL)

#define RCC_AHB1ENR        (*(volatile unsigned int *)(RCC_BASE + 0x30UL))
#define GPIOA_MODER        (*(volatile unsigned int *)(GPIOA_BASE + 0x00UL))
#define GPIOA_ODR          (*(volatile unsigned int *)(GPIOA_BASE + 0x14UL))
#define GPIOA_PUPDR        (*(volatile unsigned int *)(GPIOA_BASE + 0x0CUL))

#define GPIOAEN            (1U << 0)
#define LED_PIN            (1U << 1)

int main(void)
{
    RCC_AHB1ENR |= GPIOAEN;

    GPIOA_MODER &= ~(3U << 2);
    GPIOA_MODER |=  (1U << 2);

    GPIOA_PUPDR &= ~(3U << 2);

    while (1)
    {
        GPIOA_ODR ^= LED_PIN;
        for (volatile int i = 0; i < 200000; i++);
    }
}
