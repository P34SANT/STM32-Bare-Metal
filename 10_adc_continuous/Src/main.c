#include "uart.h"
#include <stdio.h>
#include <stdint.h>
#include <util.h>
#include "adc.h"

uint32_t ADC1PB0;
char sensor[20];
int main(void){

    pb0_adc_init();
    UART2_init();
    start_conversion();

    while(1){



        ADC1PB0 = adc_read();
        sprintf(sensor,"%lu\n",ADC1PB0);
        UART2_write_string(sensor);
        sleep(0.4);

    }
}
