#ifndef __key__
#define __key__
/*--------------------------------------------------------------------------------------
*  @version  base on stm32f10x   
*  @date     2013.11.08
*  @brief    none
---------------------------------------------------------------------------------------*/
#include "driver.h"
#include <stdbool.h>

typedef unsigned char       u8;
typedef unsigned short      u16;
extern u8 ucKeySec;
extern u16 fr;
extern u16 dc;
extern u16 numb;
extern u16 hz;
static	   u8 ucKeyLock1;
static		 u8 ucKeyLock2;
static		 u8 ucKeyLock3;
static		 u8 ucKeyLock4;
static	   u8 ucKeyLock5;
static	   u8 ucKeyLock6;
/*-------------------------------------------------------------------------------------------------------
*  向外声明					 
-------------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------------
*  向外接口	为应用层提供的接口										 
-------------------------------------------------------------------------------------------------------*/

//KEY
extern bool Driver_Key1Sta(void);
extern bool Driver_Key2Sta(void);
extern bool Driver_Key3Sta(void);
extern bool Driver_Key4Sta(void);
extern bool Driver_Key5Sta(void);
extern bool Driver_Key6Sta(void);
extern void key_service(void);
extern void key_scan(void);
extern float Get_Hz(void);
extern int Get_Cuty(void);
extern void Speak_Value(void);

#endif

