//main.c
#include "uart.h"
#include <stdio.h>
#include <stdint.h>
#include <util.h>
#include "adc.h"
#include "systick.h"
#include "tim.h"

uint32_t ADC1PB0;
char sensor[20];
uint32_t val;
int main(void){
	systick_init();
	tim2_init(); // 1hz
    // pb0_adc_init();
    UART2_init();
    //start_conversion();
    led_init();


    while(1){


    	tim2_wait();
        led(1);
        UART2_write_string("1s has passed\n");
        tim2_wait();
        led(0);



    }
}
