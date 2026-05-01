/*
 * systick.c
 *
 *  Created on: Mar 27, 2026
 *      Author: Peasant
 */

#include "systick.h"

#define SYSTICK_LOAD_VAL  (16000 - 1)   // 1ms برای کلاک 16MHz
#define CTRL_ENABLE       (1U << 0)
#define CTRL_CLKSRC       (1U << 2)
#define CTRL_COUNTFLAG    (1U << 16)

void systick_init(void)
{
    SysTick->LOAD = SYSTICK_LOAD_VAL;  // بارگذاری مقدار شمارش
    SysTick->VAL = 0;                  // پاک کردن شمارنده
    SysTick->CTRL = CTRL_CLKSRC | CTRL_ENABLE; // فعال‌سازی با کلاک CPU
}

void systick_delay_ms(uint32_t ms)
{
    for(uint32_t i = 0; i < ms; i++)
    {
        while(!(SysTick->CTRL & CTRL_COUNTFLAG)); // انتظار برای پرچم 1ms
    }
}
