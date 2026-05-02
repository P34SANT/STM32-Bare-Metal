#include "uart.h"
#include <stdio.h>
#include <stdint.h>
#include <util.h>
#include "adc.h"

uint32_t ADC1PB0;
char sensor[20];

static void adc_callback(void);



int main(void){

	pb0_adc_interrupt_init();
    UART2_init();
    start_conversion();

    while(1){


    }
}



static void adc_callback(void){
	ADC1PB0 = ADC1->DR;
    sprintf(sensor,"%lu\n\r",ADC1PB0);
    UART2_write_string(sensor);


}


void ADC_IRQHandler(void){
		//check if eoc flag is set
		if((ADC1->SR & ADC_SR_ENDC) != 0){

			//clear flag
			ADC1->SR &= ~ADC_SR_ENDC;


			adc_callback();
		}

}
