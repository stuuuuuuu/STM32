#include "reg52.h"
#include "led.h"
#include "syn6288.h"
#include "usart.h"
#include "time0.h"
#include "DS18B20.h"
#include "HC-SR04.h"
#include "stdio.h"
unsigned char text[]={"当前距离"};
int distancee;
float  gSpeed;
char b,c,d,e;

sbit P20 = P2^0;
int main()
{
	  
	  init();	    //中断初始化
	  InitLcd();	//1602初始化
	  UartIni();	//串口初始化  
	  Init_MCU();
	  Init_Parameter();
	  DS18B20_init();
	  
  while(1)
  	{
	

	
	 if(flag_20ms == 1)
	  {
		DS18B20_init();	
		display(Temp);			
		flag_20ms = 0;
		if(distancee <= 500)
		{
		  P20=~P20;	
		}
	   }	
		
		 Trig_SuperSonic();         //触发超声波发射
		 while(INPUT == 0)          //等待回声
         {
             ;
         }
		 distancee = Measure_Distance(); 
		 Init_Parameter();    
 	 if(flag_2s == 0)
	  {
	  if(distancee <= 1000)
	  	{
	  	sprintf(text,"小于1米");				   		//60s读取一次温度
		SYN_FrameInfo(0,text);
		}
	 if(distancee <= 1500 && distancee >= 500)
	  	{
			P20=~P20;
		}
	  if(distancee <= 2000 && distancee >= 1000)
	  	{
	  	sprintf(text,"小于2米");				   		//60s读取一次温度
		SYN_FrameInfo(0,text);
		}
	  if(distancee <= 3000 && distancee >= 2000)
	  	{
	  	sprintf(text,"小于3米");				   		//60s读取一次温度
		SYN_FrameInfo(0,text);
		}
	  }
	 }
}