#include <reg52.h>
#include "led.h"
#include <time0.h>
flag_20ms = 0;
flag_2s = 1;

void init(void )
{
	TH0 = (65536-2000)/256;
 	TL0 = (65536-2000)%256;
	TMOD = 0x01;    //定时器0，16位工作方式
	TR0 = 1;	     //启动定时器0
	ET0 = 1;        //打开定时器0中断
	EX0 = 0;        //关闭外部中断


	RCAP2L =(65536-2000)/256;;		//设置定时重载值
	RCAP2H =(65536-2000)%256;;		//设置定时重载值
	T2CON = 0;
	T2MOD = 0;
	TR2 = 1;	  
	ET2 = 1;
	EA  = 1;         //打开总中断0

}
void timer0() interrupt 1 
{	 
	
	static int count1 = 10;
	static int count2 = 1000;  
	
	TH0=(65536-2000)/256;	   //2ms
 	TL0=(65536-2000)%256;
	if(count1-- == 0)
	{
	 flag_20ms = 1;
	 count1	= 10;
	}
	if(count2-- == 0)
	{
	 
	 flag_2s = 0;
	 count2 = 1000;
	}
	
}
