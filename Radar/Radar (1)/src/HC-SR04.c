#include "HC-SR04.h"
#include "reg52.h"
#include "intrins.h"
#include "DS18B20.h"
#define uchar unsigned char 
#define  uint unsigned int 
             //���������˿�
long int distance=0;               //�������
uchar count;
int t = 0;
int DHTFlag = 1;
long Th0;
long Tl0;
void delayt(uint x)
{
    uchar j;
    while(x-- > 0)
    {
  	    for(j = 0;j < 125;j++)
        {
            ;
        }
    }
}
void Init_MCU(void)
{
	T2CON=0;
	T2MOD=0;
 	TL2 = 0x66;
	TH2 = 0xfc;	      //1ms
    ET2 = 1;	      //����ʱ��2
	EA = 1;		      //���ж�ʹ��
}
void Trig_SuperSonic(void)//��������
{
	 OUTPUT = 1;
	 delayt(1);
	 OUTPUT = 0;
}
void Init_Parameter(void)
{
	 OUTPUT =1;
	 INPUT = 1;
	 count = 0;
	 distance = 0;
}
int Measure_Distance(void)
{
	uchar l;
	uint h,y;
	TR2 = 1;
	while(INPUT)
    {
        ;
    }	
	TR2 = 0;
	l = TL2;
	h = TH2;
	y = (h << 8) + l;
	y = y - 0xfc66;//us����
	distance = y + 1000 * count;//������ʱ��
	TL2 = 0x66;
	TH2 = 0xfc;
	delayt(30);
	distance = VELOCITY_30C * distance / 20000;
	return distance;
}





void timer3 (void) interrupt 5
{
	TF2 = 0;
	TL2= 0x66;
	TH2 = 0xfc;
	count++;
	if(count == 18)//�����������������18ms
	{
		TR2 =0;
		TL2= 0x66;
		TH2 = 0xfc;
		count = 0;
	}
}

