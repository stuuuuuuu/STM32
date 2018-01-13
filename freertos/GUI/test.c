#include "lcd.h"
#include "FreeRTOS.h"
#include "task.h"
#include "gui.h"
#include "test.h"
#include "touch.h"
#include "key.h" 
#include "led.h"
#include "pic.h"
#include "key.h"
#include "stdio.h"
#include "RTC.h"
#include "ADC.h"

u16 ColorTab[5]={BRED,YELLOW,RED,GREEN,BLUE};//定义颜色数组

void DrawTestPage(u8 *str)
{
//绘制固定栏up
LCD_Fill(0,0,lcddev.width,20,RED);
//绘制固定栏down
LCD_Fill(0,lcddev.height-20,lcddev.width,lcddev.height,RED);
POINT_COLOR=WHITE;
Gui_StrCenter(0,2,WHITE,RED,str,16,1);//居中显示
Gui_StrCenter(0,lcddev.height-18,WHITE,RED,(u8*)"www.w3cschool.cn",16,1);//居中显示
//绘制测试区域
LCD_Fill(0,20,lcddev.width,lcddev.height-20,BLACK);
}


char Disp_Hz[10]={0};
char Disp_Duty[10]={0};
char Disp_BPM[10]={0};
char Disp_IBI[10]={0};
char Time[];
u8 t=0;
//float aa;	
void main_test(void)
{
	
	
	Gui_StrCenter(0,30,RED,BLUE,(u8*)"Welcome to Test",16,1);//居中显示
//	Gui_StrCenter(0,120,BLUE,BLUE,"2017-11-9",16,1);//居中显示	
	if(t!=calendar.sec)
		{
			t=calendar.sec;
			sprintf(Time,"%d年%d月%d日%d时%d分%d秒",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
			 Show_Str(60,120,BLUE,BLUE,(u8*)Time,16,1);
		}
//	aa=Get_Hz();
	sprintf(Disp_BPM,"BPM:%d ",rt_BPM());
	Show_Str(60,60,RED,BLACK,(u8*)Disp_BPM,16,1);
	sprintf(Disp_IBI,"IBI:%d ms",rt_IBI());
	Show_Str(60,80,RED,BLACK,(u8*)Disp_IBI,16,1);
	sprintf(Disp_Hz,"hz:%3.1f",Get_Hz());
	Show_Str(180,60,RED,BLACK,(u8*)Disp_Hz,16,1);
	sprintf(Disp_Duty,"Duty:%d%%",Get_Cuty());
	Show_Str(180,80,RED,BLACK,(u8*)Disp_Duty,16,1);
	
	vTaskDelay(500);
}


//******************************************************************
//函数名：  Test_Color
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    颜色填充测试，依次填充白色、黑色、红色、绿色、蓝色
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************
void Test_Color(void)
{
	DrawTestPage("测试1:纯色填充测试");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	Show_Str(lcddev.width-50,30,BLUE,YELLOW,"White",16,1);vTaskDelay(500);
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,BLACK);
	Show_Str(lcddev.width-50,30,BLUE,YELLOW,"Black",16,1);vTaskDelay(500);
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,RED);
	Show_Str(lcddev.width-50,30,BLUE,YELLOW,"Red",16,1); vTaskDelay(500);
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,GREEN);
	Show_Str(lcddev.width-50,30,BLUE,YELLOW,"Green",16,1);vTaskDelay(500);
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,BLUE);
	Show_Str(lcddev.width-50,30,WHITE,YELLOW,"Blue",16,1);vTaskDelay(500);

}


void Test_FillRec(void)
{
	u8 i=0;
	DrawTestPage("测试2:GUI矩形填充测试");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	for (i=0; i<5; i++) 
	{
		LCD_DrawRectangle(lcddev.width/2-80+(i*15),lcddev.height/2-80+(i*15),lcddev.width/2-80+(i*15)+60,lcddev.height/2-80+(i*15)+60); 
		POINT_COLOR=ColorTab[i];
	}
	vTaskDelay(1500);	
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE); 
	for (i=0; i<5; i++) 
	{
		LCD_DrawFillRectangle(lcddev.width/2-80+(i*15),lcddev.height/2-80+(i*15),lcddev.width/2-80+(i*15)+60,lcddev.height/2-80+(i*15)+60); 
		POINT_COLOR=ColorTab[i];
	}
	vTaskDelay(1500);
}

//******************************************************************
//函数名：  Test_FillRec
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    圆形框显示和填充测试，依次显示粉红色、黄色、红色、绿色、蓝色圆形框，
//       	延时1500毫秒后，依次按照粉红色、黄色、红色、绿色、蓝色填充圆形框 
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************
void Test_Circle(void)
{
	u8 i=0;
	DrawTestPage("测试3:GUI画圆填充测试");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	for (i=0; i<5; i++)  
		gui_circle(lcddev.width/2-80+(i*25),lcddev.height/2-50+(i*25),ColorTab[i],30,0);
	vTaskDelay(1500);	
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE); 
	for (i=0; i<5; i++) 
	  	gui_circle(lcddev.width/2-80+(i*25),lcddev.height/2-50+(i*25),ColorTab[i],30,1);
	vTaskDelay(1500);
}

//******************************************************************
//函数名：  English_Font_test
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    英文显示测试 
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************
void English_Font_test(void)
{
	DrawTestPage("测试4:英文显示测试");
	POINT_COLOR=RED;
	BACK_COLOR=BLUE;
	LCD_ShowString(10,30,12,"6X12:abcdefghijklmnopqrstuvwxyz0123456789",0);
	LCD_ShowString(10,45,12,"6X12:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",1);
	LCD_ShowString(10,60,12,"6X12:~!@#$%^&*()_+{}:<>?/|-+.",0);
	LCD_ShowString(10,80,16,"8X16:abcdefghijklmnopqrstuvwxyz0123456789",0);
	LCD_ShowString(10,100,16,"8X16:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",1);
	LCD_ShowString(10,120,16,"8X16:~!@#$%^&*()_+{}:<>?/|-+.",0); 
	vTaskDelay(1200);
}

//******************************************************************
//函数名：  Chinese_Font_test
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    中文显示测试
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************
void Chinese_Font_test(void)
{	
	DrawTestPage("测试5:中文显示测试");
	Show_Str(10,30,BLUE,YELLOW,"16X16:全动电子技术有限公司欢迎您",16,0);
	Show_Str(10,50,BLUE,YELLOW,"16X16:Welcome全动电子",16,1);
	Show_Str(10,70,BLUE,YELLOW,"24X24:深圳市中文测试",24,1);
	Show_Str(10,100,BLUE,YELLOW,"32X32:字体测试",32,1);
	vTaskDelay(1200);
}

//******************************************************************
//函数名：  Pic_test
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    图片显示测试，依次显示三幅40X40 QQ图像
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************





