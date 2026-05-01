//main.c
#include "uart.h"
#include <stdio.h>
#include <stdint.h>
#include <util.h>
#include "adc.h"
#include "systick.h"
#include "tim.h"


uint32_t val;
char     valstr[20];
int main(void){
	systick_init();
	//tim2_init(); // 1hz
	tim2_PA1outputCompare_init();
    // pb0_adc_init();
    UART2_init();
    //start_conversion();
   // led_init();


    while(1){


    	tim2_wait();
    	val++;
    	sprintf(valstr,"%lu\n",val);
        UART2_write_string(valstr);





    }
}
