#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>

#define GPIOAEN         (1U<<0)
#define USART2EN        (1U<<17)
#define SYS_FREQ        16000000UL
#define APB1CLK         SYS_FREQ
#define UART_BAUDRATE   9600UL

#define CR1_TE          (1U<<3)
#define CR1_UE          (1U<<13)
#define SR_TXE          (1U<<7)

static void set_uart_baudrate(USART_TypeDef *USARTx , uint32_t pclk , uint32_t baudrate);

static uint16_t calculate_uart_baudrate(uint32_t pclk , uint32_t baudrate);

void UART2_init ();

void UART2_write (int ch);

int __io_putchar(int ch){
	UART2_write(ch);
	return ch;
}


int main(void){

    UART2_init();

    while(1){

        printf("HMMMM\n\r");

        for(volatile int i=0;i<100000;i++);

    }
}


void UART2_init (){

    RCC->AHB1ENR |= GPIOAEN;

    GPIOA->MODER &= ~(3 << 4);
    GPIOA->MODER |=  (2 << 4);

    GPIOA->AFR[0] &= ~(0b1111<<8);
    GPIOA->AFR[0] |=  (0b0111<<8);

    RCC->APB1ENR |= USART2EN;

    set_uart_baudrate(USART2, APB1CLK, UART_BAUDRATE);

    USART2->CR1 = CR1_TE;

    USART2->CR1 |= CR1_UE;

}

void UART2_write (int ch){

    while(!(USART2->SR & SR_TXE));

    USART2->DR = (ch & 0xFF);

}


static void set_uart_baudrate(USART_TypeDef *USARTx , uint32_t pclk , uint32_t baudrate){

    USARTx->BRR = calculate_uart_baudrate(pclk,baudrate);

}

static uint16_t calculate_uart_baudrate(uint32_t pclk , uint32_t baudrate){

    return ((pclk + (baudrate/2U))/baudrate);

}
