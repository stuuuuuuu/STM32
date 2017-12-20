#include "esp8266_drive.h"
#include "sta_tcpclent_test.h"
#include "esp8266_public.h"
#include "system.h"
#include "usart.h"
#include "tim.h"
#include "key.h"
#include "driver.h"
#include "FreeRTOS.h"
#include "task.h"
#include "ADC.h"
#include "SYN6288.h"
#include "lcd.h"
#include "touch.h"
#include "gui.h"
#include "test.h"
#include "RTC.h"
volatile u32 time; 
char Open_speak[] = {"��ӭ�μӲ���"};
void GUI(void * pvParameters)
{
//		const portTickType xDelay = pdMS_TO_TICKS(10);
   LCD_Init();	

		while(1)
		{
		
				main_test();


//			vTaskDelayUntil(0,xDelay);
			
		}
}
void Key_Scan(void * pvParameters)
{
	
		while(1)
		{
				key_scan();			
				vTaskDelay(20);
				key_service();	
				vTaskDelay(20);
				
		}

}
void ESP8266_Link(void * pvParameters)
{
		ESP8266_STA_TCPClient_Test();
		while(1)
		{
		
			vTaskDelay(10);
		
		}

}
void BMP_Test(void * pvParameters)
{
	
		while(1)
		{
				spend();
				vTaskDelay(10);
		}
}
void ADC_Re(void * pvParameters)
{
		while(1)
		{
				ADC_change();
				vTaskDelay(2);
		}
}

void Spend_all(void * pvParameters)
{
		while(1)
		{
				
			while(ucKeySec == 6)
			{
					Speak_Value();
					send();
					ucKeySec = 0 ;
			}
					vTaskDelay(10);
		} 
}


int main(void)
{
			Driver_MCU_Init();	
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);		
			TIM3_PWM_Init(719,4000);
//		TIM2_NVIC_Configuration();
//		TIM2_Configuration();	  
			LED_switch(&numb);	
//  	Systick_Init(72);
			USART1_Init(115200);
			USART3_Init(9600);
			ESP8266_Init(115200);
			ADC1_Init();
			RTC_Init();
			
			
		
			
			xTaskCreate(GUI, 					(const char *)"GUI", configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY + 3,NULL);
			xTaskCreate(Key_Scan, 		(const char *)"Key_Scan", configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY + 6,NULL);
			xTaskCreate(ESP8266_Link, (const char *)"ESP8266_Link", configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY + 10,NULL);
			xTaskCreate(BMP_Test, 		(const char *)"BMP_Test", configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY + 9,NULL);
			xTaskCreate(ADC_Re, 			(const char *)"ADC_Re", configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY + 11,NULL);
			xTaskCreate(Spend_all, 		(const char *)"Spend_all", configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY + 2,NULL);	
			vTaskStartScheduler();
			return 0;

	  
}

