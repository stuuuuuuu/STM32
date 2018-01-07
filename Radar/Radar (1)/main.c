#include "reg52.h"
#include "led.h"
#include "syn6288.h"
#include "usart.h"
#include "time0.h"
#include "DS18B20.h"
#include "HC-SR04.h"
#include "stdio.h"
unsigned char text[]={"��ǰ����"};
int distancee;
float  gSpeed;
char b,c,d,e;

sbit P20 = P2^0;
int main()
{
	  
	  init();	    //�жϳ�ʼ��
	  InitLcd();	//1602��ʼ��
	  UartIni();	//���ڳ�ʼ��  
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
		
		 Trig_SuperSonic();         //��������������
		 while(INPUT == 0)          //�ȴ�����
         {
             ;
         }
		 distancee = Measure_Distance(); 
		 Init_Parameter();    
 	 if(flag_2s == 0)
	  {
	  if(distancee <= 1000)
	  	{
	  	sprintf(text,"С��1��");				   		//60s��ȡһ���¶�
		SYN_FrameInfo(0,text);
		}
	 if(distancee <= 1500 && distancee >= 500)
	  	{
			P20=~P20;
		}
	  if(distancee <= 2000 && distancee >= 1000)
	  	{
	  	sprintf(text,"С��2��");				   		//60s��ȡһ���¶�
		SYN_FrameInfo(0,text);
		}
	  if(distancee <= 3000 && distancee >= 2000)
	  	{
	  	sprintf(text,"С��3��");				   		//60s��ȡһ���¶�
		SYN_FrameInfo(0,text);
		}
	  }
	 }
}