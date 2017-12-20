/* ��׼C����� */
#include <string.h>
#include <stdio.h>
#include <stddef.h> 

/* ����ת�� */



/* INCLUDES */
#include "driver.h"
#include "key.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"                                                                                                                                                                                                                                                                          
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++  ƽ̨���� +++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/********************************************************************************************************
*  Function: Driver_MCU_Init						                                                           
*  Object: MCU��ʼ��               
*  ���룺 ��
*  ����� ��								                         	                                     
*  ��ע�� ʱ������ MCU������һЩ����                                      
********************************************************************************************************/
void Driver_MCU_Init(void)
{
  	//--------------------------- CLK INIT, HSE PLL ----------------------------
		ErrorStatus HSEStartUpStatus;
		//RCC reset
		RCC_DeInit();
		//Enable HSE
		RCC_HSEConfig(RCC_HSE_ON); 
		//Wait HSE is ready
		HSEStartUpStatus = RCC_WaitForHSEStartUp();
		//If HSE start fail, wail and wail.
		while(HSEStartUpStatus == ERROR);
		//Set bus clock
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div1);
		RCC_PCLK2Config(RCC_HCLK_Div1);
		//HSE8M PLL-> 72M
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
		RCC_PLLCmd(ENABLE); 
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		//Select PLL as system clock source
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		while(RCC_GetSYSCLKSource() != 0x08);

		//----------------------------- CLOSE HSI ---------------------------
		RCC_HSICmd(DISABLE);

		//--------------------------- OPEN GPIO CLK -------------------------
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

		//---------------------------- INT CONFIG ---------------------------
		//2-level interrupt 
		//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
			
		//---------------------------- JTAG CONFIG ---------------------------
		//JTAG/SWD disable
		//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
		//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
}		   



void Driver_OpenEA(void)
{
		//���ж�
		__enable_irq(); 
}


void TIM3_PWM_Init(u16 arr,u16 psc)
{
			GPIO_InitTypeDef GPIO_InitStructure;
			TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
			TIM_OCInitTypeDef  TIM_OCInitStructure;
			NVIC_InitTypeDef NVIC_InitStructure; 
    
													
			NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	  
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;	
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);

		  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB| RCC_APB2Periph_GPIOF,ENABLE);	
			GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7| GPIO_Pin_6;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);	
			GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0| GPIO_Pin_1;
			GPIO_Init(GPIOB, &GPIO_InitStructure);	
			TIM_TimeBaseStructure.TIM_Period = arr;       //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
			TIM_TimeBaseStructure.TIM_Prescaler = psc;	    //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ72MHz
			TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
			TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
			TIM_OCInitStructure.TIM_Pulse = 360;	
			TIM_OC1Init(TIM3, &TIM_OCInitStructure);	
			TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
			
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
			TIM_OCInitStructure.TIM_Pulse = 360;	
			TIM_OC2Init(TIM3, &TIM_OCInitStructure);	
			TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
			
//		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
//		TIM_OCInitStructure.TIM_Pulse = 500;	
//		TIM_OC3Init(TIM3, &TIM_OCInitStructure);	
//		TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
			
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
			TIM_OCInitStructure.TIM_Pulse = 360;	
			TIM_OC4Init(TIM3, &TIM_OCInitStructure);	
			TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
			
			TIM_ARRPreloadConfig(TIM3,ENABLE);
			TIM_Cmd(TIM3,ENABLE);
			
}

