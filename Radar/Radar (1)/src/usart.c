#include "usart.h"



void UartIni(void)									   //��ʼ��
{
	
	SCON = 0x50 ; //SCON: serail mode 1, 8-bit UART, enable ucvr  	
	TMOD |= 0x20 ; //TMOD: timer 1, mode 2, 8-bit reload 	
	PCON |= 0x80 ; //SMOD=1; 	
	TL1 = 0xFA;	
	TH1 = 0xFA; //Baud:9600 	
	IE |= 0x90 ; //Enable Serial Interrupt 
	REN = 1;
	TI = 0;
	RI = 0;
	TR1 = 1 ; // timer 1 run 
	ES=1;
}											   
void UARTSendByte(uint8_t DAT)					//���͵�����	   
{
	ES  =  0;
	TI=0;
	SBUF = DAT;
	while(TI==0);
	TI=0;
	ES = 1;
}
void PrintCom(uint8_t *DAT,uint8_t len)			 //��ӡ�ַ�
{
	uint8_t i;
	for(i=0;i<len;i++)
	{
	 	UARTSendByte(*DAT++);
	}	
}
void Uart_Isr() interrupt 4 using 1				 //�����ж�
{	
	if(RI)
	{	
		  RI = 0;
	}

}