//main.c
#include "uart.h"
#include <stdio.h>
#include <stdint.h>
#include <util.h>
#include "adc.h"
#include "systick.h"

uint32_t ADC1PB0;
char sensor[20];
uint32_t val;
int main(void){
	systick_init();
    pb0_adc_init();
    UART2_init();
    start_conversion();
    led_init();

    while(1){


    	val = SysTick->VAL;
        ADC1PB0 = adc_read();
        sprintf(sensor,"%lu\n",ADC1PB0);
        UART2_write_string(sensor);
        systick_delay_ms(1000);
        led(1);
        systick_delay_ms(1000);
        led(0);



    }
}
