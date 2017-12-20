#ifndef _SysTick_H
#define _SysTick_H

#include "system.h"

void Systick_Init(u8 SYSCLK);
extern void Delay(u32 time);
void delay_us(u32 nus);



#endif
