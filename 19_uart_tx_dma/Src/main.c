#include "uart.h"
#include <stdio.h>
#include <stdint.h>
#include "led.h"

static void dma_callback(void);

char TX_BUF[] = "DONG DONG DONG \n\r DONG\n\r";
int main(void){

    led_init();
    UART2_init();
    //UART2_RXinterrupt_init ();
    dma1_stream6_init((uint32_t )(TX_BUF) , (uint32_t)&(USART2->DR) ,  sizeof(TX_BUF) - 1);


    while(1){






}//end while

}// end main


static void dma_callback(void){

	led(1);

}


void DMA1_Stream6_IRQHandler(void){

	if (DMA1->HISR & DMA_TCIF6){

		DMA1->HIFCR |= DMA_CTCIF6;

		dma_callback();

	}



}










