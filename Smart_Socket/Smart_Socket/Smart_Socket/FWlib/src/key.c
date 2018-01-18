#include <key.h>
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include <stdbool.h>
#include "sta_tcpclent_test.h"
#include "SysTick.h"
#include "usart.h"
#include "esp8266_drive.h"
#include "ds18b20.h"
#include "ADC.h"
#include "tim.h"
#define  True  1
#define  False 0

typedef unsigned char       u8;
typedef unsigned short      u16;
/********************************************************************************************************
*  Function: Driver_Key1Sta						                                                           
*  Object: 按键键1状态
*  输入: 无
*  输出: 1/0                                 
*  备注: 无                         
********************************************************************************************************/

u8 ucKeySec=0;
u16 fr =300;
u16 numb=1;
u16 crr=300;
bool Driver_Key1Sta(void)
{
		static bool StartFlag = True;
		if(StartFlag)
		{	
			GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//下拉输入
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	 	
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			StartFlag = False;
		}
		return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4);
}

/********************************************************************************************************
*  Function: Driver_Key2Sta						                                                           
*  Object: 按键键2状态
*  输入: 无
*  输出: 1/0                                 
*  备注: 无                              
********************************************************************************************************/
bool Driver_Key2Sta(void)
{
		static bool StartFlag = True;
		if(StartFlag)
		{	
			GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//下拉输入
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	 	
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			StartFlag = False;
		}
		return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5);
}
/********************************************************************************************************
*  Function: Driver_Key2Sta						                                                           
*  Object: 按键键3状态
*  输入: 无
*  输出: 1/0                                 
*  备注: 无                              
********************************************************************************************************/
bool Driver_Key3Sta(void)
{
		static bool StartFlag = True;
		if(StartFlag)
		{	
			GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//下拉输入
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	 	
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			StartFlag = False;
		}
		return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6);
}
bool Driver_Key4Sta(void)
{
	static bool StartFlag = True;
		if(StartFlag)
		{	
			GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//下拉输入
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	 	
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			StartFlag = False;
		}
		return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7);
}
bool Driver_Key5Sta(void)
{
	static bool StartFlag = True;
		if(StartFlag)
		{	
			GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//下拉输入
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	 	
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			StartFlag = False;
		}
		return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8);
}
bool StartFlag = true;
int Minute = 0;
int Get_Time(void)
{
	return Minute ;
}

void key_service(void)
{
//	TIM_SetAutoreload(TIM3,200);TIM_SetCompare2(TIM3,3000);
//		static u16 crr=50;
	
		switch(ucKeySec)
		{
			
			case 1:		if(StartFlag == true)	{	
									TIM_Cmd(TIM3,ENABLE);
									StartFlag = false ;
								}else {
									TIM_Cmd(TIM3,DISABLE);
									StartFlag = true ;
								}									;	ucKeySec=0;break;
			case 2:		Minute += 1;	if(Minute >= 1200) Minute =1200	;	ucKeySec=0;break;  //s+
			case 3:		Minute -= 1;	if(Minute <= 0) Minute =0;		ucKeySec=0;break;			 //s-
			case 4:		Minute += 60;	if(Minute >= 1200) Minute =1200	;	ucKeySec=0;break;   
			case 5:		Minute -= 60;if(Minute <= 0) Minute =0;		ucKeySec=0;break;  
		
		}
}

void send()
{
		char str[100]={0};
		static float t;
		static int counter = 0;
		static int Dc;
		static int min,Sec;
		min = Get_Time()%60;
		Sec = Get_Time()/60;
		
    t = ds18b20_read();
		Dc = Rt_ADC();
		if( t > 25)
		{
			  counter ++;
			if(counter >=6)
			{
			   GPIO_SetBits(GPIOA,GPIO_Pin_1);
			}
		}
		
		
		
		sprintf (str,"WD:%.1f_Time:%d:%d\r\n",t,Sec,min);
		
		
		ESP8266_SendString ( ENABLE, str,15, Single_ID_2 );

}


void key_scan(void)
{
		if(!Driver_Key1Sta())
				{	
						ucKeyLock1=0;
				}
				else if(ucKeyLock1==0)
				{
					
						
						ucKeyLock1=1;
						ucKeySec=1; 				  	 					
				}
			 if(!Driver_Key2Sta())
			 {
				  ucKeyLock2=0;
			 }
			 else if(ucKeyLock2==0)
				{
			
						
						ucKeyLock2=1;
						ucKeySec=2;
						
				}
				if(!Driver_Key3Sta())
				 {
				 ucKeyLock3=0;
			 }
			 else if(ucKeyLock3==0)
				{
		
						
						ucKeyLock3=1;
						ucKeySec=3;
						
				}
					if(!Driver_Key4Sta())
				 {
				 ucKeyLock4=0;
			 }
			 else if(ucKeyLock4==0)
				{
			
						
						ucKeyLock4=1;
						ucKeySec=4;
						
				}
					if(!Driver_Key5Sta())
				 {
				 ucKeyLock5=0;
			 }
			 else if(ucKeyLock5==0)
				{
			
						
						ucKeyLock5=1;
						ucKeySec=5;						
				}
}
void CCR_switch(u16 *crr)
{
			switch(numb)
			{
				case 1:TIM_SetCompare1(TIM3,*crr);break;
				case 2:TIM_SetCompare2(TIM3,*crr);break;
				case 3:TIM_SetCompare3(TIM3,*crr);break;
			}
}
void LED_switch(u16 *num)
{
			switch(*num)
			{
				case 1:TIM_CCxCmd(TIM3,TIM_Channel_1,ENABLE);	TIM_CCxCmd(TIM3,TIM_Channel_2,DISABLE);TIM_CCxCmd(TIM3,TIM_Channel_3,DISABLE);break;
				case 2:TIM_CCxCmd(TIM3,TIM_Channel_2,ENABLE); TIM_CCxCmd(TIM3,TIM_Channel_1,DISABLE);break; 
				case 3:TIM_CCxCmd(TIM3,TIM_Channel_3,ENABLE); TIM_CCxCmd(TIM3,TIM_Channel_2,DISABLE);break; 				
				
			}
}


