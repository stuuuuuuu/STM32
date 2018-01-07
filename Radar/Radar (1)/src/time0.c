#include <reg52.h>
#include "led.h"
#include <time0.h>
flag_20ms = 0;
flag_2s = 1;

void init(void )
{
	TH0 = (65536-2000)/256;
 	TL0 = (65536-2000)%256;
	TMOD = 0x01;    //��ʱ��0��16λ������ʽ
	TR0 = 1;	     //������ʱ��0
	ET0 = 1;        //�򿪶�ʱ��0�ж�
	EX0 = 0;        //�ر��ⲿ�ж�


	RCAP2L =(65536-2000)/256;;		//���ö�ʱ����ֵ
	RCAP2H =(65536-2000)%256;;		//���ö�ʱ����ֵ
	T2CON = 0;
	T2MOD = 0;
	TR2 = 1;	  
	ET2 = 1;
	EA  = 1;         //�����ж�0

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
