#include <key.h>
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include <stdbool.h>
#include "sta_tcpclent_test.h"
#include "usart.h"
#include "esp8266_drive.h"
#include "SYN6288.h"
#define  True  1
#define  False 0
char text[10]={0};

typedef unsigned char       u8;
typedef unsigned short      u16;
/********************************************************************************************************
*  Function: Driver_Key1Sta						                                                           
*  Object: 按键键1状态
*  输入: 无
*  输出: 1/0                                 
*  备注: 无                         
********************************************************************************************************/

u8 ucKeySec=0;
u16 fr =300;
u16 numb=1;
u16 crr=50;
u16 hz = 30;
float Speak_hz = 30.0;
u16 cont = 20;
const  u16 pl[]={5000  ,4878 ,4762 ,4651 ,4545 ,4444 ,4347 ,4255 ,4167 ,4082 ,
								4000  ,3922 ,3846 ,3774 ,3704 ,3636 ,3571 ,3509 ,3448 ,3390 ,
                3333  ,3279 ,3226 ,3175	,3125	,3077	,3030	,2985	,2941	,2899	, 			//30
								2857	,2817	,2778	,2740	,2703	,2667	,2632	,2597	,2564	,2532	,				//35
								2500	,2469	,2439	,2410	,2381	,2353	,2326	,2299	,2273	,2247	,				//40
								2222	,2198	,2174	,2151	,2128	,2105	,2083	,2062	,2041	,2020	,				//45
								2000	,1980	,1961	,1942	,1923	,1905	,1887	,1869	,1852	,1835	,				//50
								1818	,1802	,1786	,1770	,1754	,1739	,1724	,1709	,1695	,1681	,				//55
								1667	,1653	,1639	,1626	,1613	,1600	,1587	,1575	,1563	,1550	,				//60
								1538	,1527	,1515	,1504	,1493	,1481	,1471	,1460	,1449	,1439	,1429	};	//65	-70	
const u16 Cuty[] = {36	,72	,108	,144	,180	,216	,252	,288	,324	,360,
										396	,432	,468	,504	,540	,576	,612	,648	,684}; 				//5%-95%
bool Driver_Key1Sta(void)
{
		static bool StartFlag = True;
		if(StartFlag)
		{	
			GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//下拉输入
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	 	
			GPIO_Init(GPIOF, &GPIO_InitStructure);
			StartFlag = False;
		}
		return GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1);
}

/********************************************************************************************************
*  Function: Driver_Key2Sta						                                                           
*  Object: 按键键2状态
*  输入: 无
*  输出: 1/0                                 
*  备注: 无                              
********************************************************************************************************/
bool Driver_Key2Sta(void)
{
		static bool StartFlag = True;
		if(StartFlag)
		{	
			GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//下拉输入
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	 	
			GPIO_Init(GPIOF, &GPIO_InitStructure);
			StartFlag = False;
		}
		return GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_3);
}
/********************************************************************************************************
*  Function: Driver_Key2Sta						                                                           
*  Object: 按键键3状态
*  输入: 无
*  输出: 1/0                                 
*  备注: 无                              
********************************************************************************************************/
bool Driver_Key3Sta(void)
{
		static bool StartFlag = True;
		if(StartFlag)
		{	
			GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//下拉输入
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	 	
			GPIO_Init(GPIOF, &GPIO_InitStructure);
			StartFlag = False;
		}
		return GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5);
}
/********************************************************************************************************
*  Function: Driver_Key2Sta						                                                           
*  Object: 按键键4状态
*  输入: 无
*  输出: 1/0                                 
*  备注: 无                              
********************************************************************************************************/
bool Driver_Key4Sta(void)
{
	static bool StartFlag = True;
		if(StartFlag)
		{	
			GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//下拉输入
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	 	
			GPIO_Init(GPIOF, &GPIO_InitStructure);
			StartFlag = False;
		}
		return GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7);
}
/********************************************************************************************************
*  Function: Driver_Key2Sta						                                                           
*  Object: 按键键5状态
*  输入: 无
*  输出: 1/0                                 
*  备注: 无                              
********************************************************************************************************/
bool Driver_Key5Sta(void)
{
	static bool StartFlag = True;
		if(StartFlag)
		{	
			GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//下拉输入
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	 	
			GPIO_Init(GPIOF, &GPIO_InitStructure);
			StartFlag = False;
		}
		return GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_9);
}
bool Driver_Key6Sta(void)
{
		static bool StartFlag = True;
		if(StartFlag)
		{	
			GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		//下拉输入
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	 	
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			StartFlag = False;
		}
		return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
}
void send()
{
		char str[100]={0};
		 
		sprintf (str,"频率为\"%3.1f\" 赫兹\r\n",Speak_hz);
		ESP8266_SendString ( ENABLE, str, 15, Single_ID_2 );
		
		
	
}
float Get_Hz(void)
{
	return Speak_hz;
}
int Get_Cuty(void)
{
	 return crr;
}
void  Speak_Value(void)
{
	sprintf(text,"频率为\"%6.1f\"赫兹",Speak_hz);  TTSPlay('0',text);
}
void key_service(void)
{
//	TIM_SetAutoreload(TIM3,200);TIM_SetCompare2(TIM3,3000);
		static u16 Cuty_cont=9;

	
		switch(ucKeySec)
		{
				
			case 1:numb++; if(numb==4)numb=1;CCR_switch(&Cuty[Cuty_cont]);LED_switch(&numb);							ucKeySec=0;break;
			case 2:hz += 5;Speak_hz += 0.5;cont++;if(cont>99)cont=99;	TIM3->PSC=pl[cont];									ucKeySec=0;break;
			case 3:hz -= 5;Speak_hz -= 0.5;cont--;if(cont<2)cont=2;		TIM3->PSC=pl[cont];									ucKeySec=0;break;
			case 4:crr += 5;Cuty_cont += 1;CCR_switch(&Cuty[Cuty_cont]);			if(Cuty_cont>=19)   Cuty_cont=19;			ucKeySec=0;break;
			case 5:crr -= 5;Cuty_cont -= 1;CCR_switch(&Cuty[Cuty_cont]);			if(Cuty_cont<=1)		Cuty_cont=1;			ucKeySec=0;break;
//			case 6:			ucKeySec=0;break;
		
		}
}
void key_scan(void)
{
		if(!Driver_Key1Sta())
				{	
						ucKeyLock1=0;
				}
				else if(ucKeyLock1==0)
				{
					
						
						ucKeyLock1=1;
						ucKeySec=1; 				  	 					
				}
			 if(!Driver_Key2Sta())
			 {
				  ucKeyLock2=0;
			 }
			 else if(ucKeyLock2==0)
				{
			
						
						ucKeyLock2=1;
						ucKeySec=2;
						
				}
				if(!Driver_Key3Sta())
				 {
				 ucKeyLock3=0;
			 }
			 else if(ucKeyLock3==0)
				{
		
						
						ucKeyLock3=1;
						ucKeySec=3;
						
				}
					if(!Driver_Key4Sta())
				 {
				 ucKeyLock4=0;
			 }
			 else if(ucKeyLock4==0)
				{
			
						
						ucKeyLock4=1;
						ucKeySec=4;
						
				}
					if(!Driver_Key5Sta())
				 {
				 ucKeyLock5=0;
			 }
			 else if(ucKeyLock5==0)
				{
			
						
						ucKeyLock5=1;
						ucKeySec=5;						
				}
						if(!Driver_Key6Sta())
				 {
				 ucKeyLock6=0;
			 }
			 else if(ucKeyLock6==0)
				{
			
						
						ucKeyLock6=1;
						ucKeySec=6;						
				}
}
void CCR_switch(const u16 *crr)
{
			switch(numb)
			{
				case 1:TIM_SetCompare1(TIM3,*crr);break;       //TIM_SetCompare1(TIM3,*crr);TIM_SetCompare2(TIM3,*crr);TIM_SetCompare4(TIM3,*crr);
				case 2:TIM_SetCompare2(TIM3,*crr);break;
				case 3:TIM_SetCompare4(TIM3,*crr);break;
			}
}
void LED_switch(u16 *num)
{

			switch(*num)
			{
				case 1:TIM_CCxCmd(TIM3,TIM_Channel_1,ENABLE);	TIM_CCxCmd(TIM3,TIM_Channel_2,DISABLE);TIM_CCxCmd(TIM3,TIM_Channel_4,DISABLE);break;
				case 2:TIM_CCxCmd(TIM3,TIM_Channel_2,ENABLE); TIM_CCxCmd(TIM3,TIM_Channel_1,DISABLE);break; 
				case 3:TIM_CCxCmd(TIM3,TIM_Channel_4,ENABLE); TIM_CCxCmd(TIM3,TIM_Channel_2,DISABLE);break; 				
				
			}
}


