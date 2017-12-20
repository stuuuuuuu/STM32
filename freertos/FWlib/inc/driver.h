#ifndef __Driver__
#define __Driver__
/*--------------------------------------------------------------------------------------
*  @file     Driver.h
*  @version  base on stm32f10x   
*  @brief    none
---------------------------------------------------------------------------------------*/
#include <stdbool.h>

typedef unsigned char       u8;
typedef unsigned short      u16;


/*-------------------------------------------------------------------------------------------------------
*  向外声明					 
-------------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------------
*  向外接口	为应用层提供的接口										 
-------------------------------------------------------------------------------------------------------*/
//mcu
extern void Driver_MCU_Init(void);



extern void CCR_switch(const u16 *crr);
extern void LED_switch(u16 *num);
extern void TIM3_PWM_Init(u16 arr,u16 psc);
#endif
