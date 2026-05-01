//main.c
#include "uart.h"
#include <stdio.h>
#include <stdint.h>
#include <util.h>
#include "adc.h"
#include "systick.h"
#include "tim.h"
#include "exti.h"


int val;
int oldval;
int diff;
char     valstr[20];
int main(void){

    UART2_init();

    pa0EXTI_init();

    UART2_write_string("HELLO");

    while(1){








    }


}

void EXTI0_CALLBACK(){

	UART2_write_string("OOPS");
}


void EXTI0_IRQHandler(void) {
    if (EXTI->PR & LINE0) {
        EXTI->PR = LINE0; // Write 1 to clear the pending bit
        EXTI0_CALLBACK();
    }
}




