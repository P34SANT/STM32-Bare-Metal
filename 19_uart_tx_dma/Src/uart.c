#include "uart.h"

#define GPIOAEN         (1U<<0)
#define USART2EN        (1U<<17)
#define SYS_FREQ        16000000UL
#define APB1CLK         SYS_FREQ
#define UART_BAUDRATE   57600UL

#define CR1_TE          (1U<<3)
#define CR1_UE          (1U<<13)
#define CR1_RE          (1U<<2)
#define SR_TXE          (1U<<7)
#define SR_RXNE         (1U<<5)
#define CR1_RXNEIE      (1U<<5)

#define CR3_DMAT        (1U<<7)

#define DMA1EN          (1U<<21)
#define DMA_SxCR_EN     (1U<<0)


#define DMA_CHTIF6 		(1U<<20)
#define DMA_CTEIF6		(1U<<19)
#define DMA_CDMEIF6     (1U<<18)
#define DMA_CFEIF6		(1U<<16)
#define DMA_SxCR_CH     (25)
#define DMA_SxCR_TCIE   (1U<<4)
#define CHANNEL4        (0b100)

#define DMA_SxCR_MINC   (1U<<10)


#define PA2             (2)
#define PA3             (3)

static void set_uart_baudrate(USART_TypeDef *USARTx , uint32_t pclk , uint32_t baudrate);
static uint16_t calculate_uart_baudrate(uint32_t pclk , uint32_t baudrate);

void UART2_write (int ch);

int __io_putchar(int ch){
	UART2_write(ch);
	return ch;
}


void UART2_RXinterrupt_init (){

    RCC->AHB1ENR |= GPIOAEN;

    //TX
    GPIOA->MODER &= ~(3 << (2*PA2));
    GPIOA->MODER |=  (2 << (2*PA2));

    GPIOA->AFR[0] &= ~(0b1111<<8);
    GPIOA->AFR[0] |=  (0b0111<<8);

    RCC->APB1ENR |= USART2EN;

    set_uart_baudrate(USART2, APB1CLK, UART_BAUDRATE);

    USART2->CR1 = CR1_TE | CR1_RE;
    USART2->CR1 |= CR1_RXNEIE;
    USART2->CR1 |= CR1_UE;

    NVIC_EnableIRQ(USART2_IRQn);


    //RX
    GPIOA->MODER &= ~(3 << (2*PA3));
    GPIOA->MODER |=  (2 << (2*PA3));

    GPIOA->AFR[0] &= ~(0b1111<<12);
    GPIOA->AFR[0] |=  (0b0111<<12);
}



void UART2_init (){

    RCC->AHB1ENR |= GPIOAEN;

    //TX
    GPIOA->MODER &= ~(3 << (2*PA2));
    GPIOA->MODER |=  (2 << (2*PA2));

    GPIOA->AFR[0] &= ~(0b1111<<8);
    GPIOA->AFR[0] |=  (0b0111<<8);

    RCC->APB1ENR |= USART2EN;

    set_uart_baudrate(USART2, APB1CLK, UART_BAUDRATE);

    USART2->CR1 = CR1_TE | CR1_RE;
    USART2->CR1 |= CR1_UE;

    //RX
    GPIOA->MODER &= ~(3 << (2*PA3));
    GPIOA->MODER |=  (2 << (2*PA3));

    GPIOA->AFR[0] &= ~(0b1111<<12);
    GPIOA->AFR[0] |=  (0b0111<<12);
}


void dma1_stream6_init(uint32_t src , uint32_t dst , uint32_t len){
	//clk access
	RCC->AHB1ENR |= DMA1EN;

	//clear other accesses to dma1 and stream6 of it
	DMA1_Stream6->CR &= ~(DMA_SxCR_EN);
	while (DMA1_Stream6->CR & DMA_SxCR_EN);

	DMA1->HIFCR |=	(DMA_CTCIF6);
	DMA1->HIFCR |=	(DMA_CHTIF6);
	DMA1->HIFCR |=	(DMA_CTEIF6);
	DMA1->HIFCR |=	(DMA_CDMEIF6);
	DMA1->HIFCR |=	(DMA_CFEIF6);





	//set the destination
	DMA1_Stream6->PAR = dst;

	//set the source
	DMA1_Stream6->M0AR = src;
	//set the length
	DMA1_Stream6->NDTR = len;

	//set stream6 to ch4
	DMA1_Stream6->CR &= ~(0b111 << DMA_SxCR_CH); // DMA_SxCR_CH = bit 25
	DMA1_Stream6->CR |= (CHANNEL4 << DMA_SxCR_CH);



	//enable mem inc
	DMA1_Stream6->CR |= DMA_SxCR_MINC;


	//direction
	DMA1_Stream6->CR |= (1U << 6);  //bit 6 is DIR , DIR = 01 means m to p
	//full t flag
	DMA1_Stream6->CR |= DMA_SxCR_TCIE;
	//direct without fifo
	DMA1_Stream6->FCR = 0; // direct mode is enabled when DMDIS bit is 0

	//enable usart2 transmitter dma
	USART2->CR3 |= CR3_DMAT;
	//dma interrupt (full complition)
	NVIC_EnableIRQ(DMA1_Stream6_IRQn);

	//enable stream6 dma1
	DMA1_Stream6->CR |= (DMA_SxCR_EN);

}

void UART2_write (int ch){

    while(!(USART2->SR & SR_TXE));

    USART2->DR = (ch & 0xFF);
}

void UART2_write_string(const char *str)
{
    while(*str)
    {
        UART2_write(*str++);
    }
}

bool SR_FLAG (){
	return USART2->SR & SR_RXNE;
}
char UART2_read (void){

	while(!(USART2->SR & SR_RXNE));

	return USART2->DR;
}


static void set_uart_baudrate(USART_TypeDef *USARTx , uint32_t pclk , uint32_t baudrate){

    USARTx->BRR = calculate_uart_baudrate(pclk,baudrate);
}


static uint16_t calculate_uart_baudrate(uint32_t pclk , uint32_t baudrate){

    return ((pclk + (baudrate/2U))/baudrate);
}
