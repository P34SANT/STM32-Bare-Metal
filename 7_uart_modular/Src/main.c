#include "uart.h"
#include <stdio.h>


int main(void){

    UART2_init();

    while(1){

        printf("HEYYYY\n\r");

        for(volatile int i=0;i<100000;i++);

    }
}


