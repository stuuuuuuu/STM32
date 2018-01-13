#include <reg52.h>
#include <time0.h>
int flag_20ms = 0;
sfr AUXR = 0x8e;
void Timer0Init(void)		//2΢��@11.0592MHz
{

	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0xFE;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
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


