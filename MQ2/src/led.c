#include<led.h>
#include<reg52.h>
#include<stdio.h>
#include<intrins.h>

sbit RS = P2^5;//Pin4
sbit RW = P2^6; //Pin5
sbit E  = P2^7;//Pin6

#define Data  P0    //数据端口

unsigned char  TempData[8];
unsigned char  ge,shiw,bai;
unsigned char  dcshi,dcge;

//unsigned char  code  SecondLine2[]="Welcome to test ";
//unsigned char  code  FirstLine2[] ="     ^_^        ";
/******************************************************************/
/*                    函数声明                                    */
/******************************************************************/
void DelayUs(unsigned char us)//delay us
{
    unsigned char uscnt;
	uscnt=us>>1;/* Crystal frequency in 12MHz*/
	while(--uscnt);
}


void WriteCommand(unsigned char c)
{
	 DelayUs(20);//short delay before operation
	  E = 0;
	 RS = 0;
	 RW = 0;
	 _nop_();
	  E = 1;
	 Data = c;
	  E = 0;
}
/****************************************************************/
void WriteData(unsigned char c)
{
	 DelayUs(20);//short delay before operation
	 E=0;
	 RS=1;
	 RW=0;
	 _nop_();
	 E=1;
	 Data=c;
	 E=0;
	 RS=0;
}
/*********************************************************************/
void ShowChar(unsigned char pos,unsigned char c)
{
    unsigned char p;
	if (pos>=0x10)
	    p=pos+0xb0; //是第二行则命令代码高4位为0xc
	else 
	    p=pos+0x80; //是第二行则命令代码高4位为0x8
	WriteCommand (p);//write command
	WriteData (c);   //write data
}
/*************************************************************************/
void ShowString (unsigned char line,char *ptr)
{
    unsigned char l,i;
	l=line<<4;
	for (i=0;i<16;i++)
	ShowChar (l++,*(ptr+i));//循环显示16个字符
}
/*********************************************************************/
void ShowString2 (unsigned char line,char *ptr)
{
    unsigned char l,i;
	l=line<<4;
	for (i=0;i<16;i++)
	ShowChar (l++,*(ptr+i));//循环显示16个字符
}
void InitLcd()
{

	WriteCommand(0x38); //display mode
	WriteCommand(0x38); //display mode
	WriteCommand(0x38); //display mode
	WriteCommand(0x06); //显示光标移动位置
	WriteCommand(0x0c); //显示开及光标设置
	WriteCommand(0x01); //显示清屏

}



//void disp(void)
//
//{
//
//	static unsigned char  SecondLine[]="                ";
//	static unsigned char  FirstLine[] ="                ";
//    FirstLine[5]=0x30+bai;
//	FirstLine[6]=0x30+shiw;
//	FirstLine[7]='.';
//	FirstLine[8]=0x30+ge;
//	FirstLine[4]=':';
//	FirstLine[2]='H';
//	FirstLine[3]='Z';
//	
//	SecondLine[2]='D';
//	SecondLine[3]='C';
//	SecondLine[4]=':';
//	SecondLine[5]=0x30+dcshi;
//	SecondLine[6]=0x30+dcge;
//	SecondLine[7]='%';
//	
//	ShowString(0,FirstLine);
//	
//	ShowString(1,SecondLine);
//
//}
void disp2(int temp_data)

{
	static unsigned char  SecondLine[]="                ";
	static unsigned char  FirstLine[] ="                ";	 

	bai = temp_data / 100;
	shiw = temp_data %100/10;
	ge =temp_data %10;
	FirstLine[5]=0x30+bai;
	FirstLine[6]=0x30+shiw;
	FirstLine[7]='.';
	FirstLine[8]=0x30+ge;
	FirstLine[4]=':';
	FirstLine[2]='W';
	FirstLine[3]='D';
	
	SecondLine[2]='D';
	SecondLine[3]='C';
	SecondLine[4]=':';
	SecondLine[5]=0x30+dcshi;
	SecondLine[6]=0x30+dcge;
	SecondLine[7]='%';
	
	ShowString(0,FirstLine);
	
	ShowString(1,SecondLine);


}


