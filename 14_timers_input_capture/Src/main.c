//main.c
#include "uart.h"
#include <stdio.h>
#include <stdint.h>
#include <util.h>
#include "adc.h"
#include "systick.h"
#include "tim.h"


int val;
int oldval;
int diff;
char     valstr[20];
int main(void){
	//systick_init();
	//tim2_init(); // 1hz
	tim2_PA1outputCompare_init();
    // pb0_adc_init();
	tim3_PA6inputCapture_init();
    UART2_init();
    //start_conversion();
   // led_init();
    tim2_wait();
    tim2_wait();


    while(1){


    	diff = val- oldval;
    	oldval=val;
    	tim3_wait_Capture();
    	sprintf(valstr,"%lu\n",diff);
        UART2_write_string(valstr);
    	val = tim3_read_Capture();






    }
}
