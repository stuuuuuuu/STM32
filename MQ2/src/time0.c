#include <reg52.h>
#include <time0.h>
int flag_20ms = 0;
sfr AUXR = 0x8e;
void Timer0Init(void)		//2微秒@11.0592MHz
{

	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xFE;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;
}


void t0(void) interrupt 1 using 0
{
	static int count = 10;
	TL0 = 0xEA;	
	TH0 = 0xFF;	
	if(count-- == 0)
	{
	  count = 10;
	  flag_20ms = 1;
	}
}


