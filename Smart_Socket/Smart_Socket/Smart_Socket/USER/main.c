#include "esp8266_drive.h"
#include "sta_tcpclent_test.h"
#include "esp8266_public.h"
#include "system.h"
#include "SysTick.h"
#include "usart.h"
#include "tim.h"
#include "key.h"
#include "driver.h"
#include "system.h"
#include "ds18b20.h"
#include "ADC.h"
volatile u32 time;
/*
 * 函数名：main
 * 描述  : 主函数
 * 输入  ：无
 * 输出  : 无
 */
void GPIO_Config(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
    //LED
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

}

int main(void)
{
    Driver_MCU_Init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    GPIO_Config();

    Systick_Init(72);
    TIM2_NVIC_Configuration();
    TIM2_Configuration();
    TIM3_Init(9999,7199);
    ESP8266_Init(115200);
		
    ESP8266_STA_TCPClient_Test();
    ds18b20_init();
//    ADC1_Init();
		GPIO_ResetBits(GPIOA,GPIO_Pin_1) ;
    while(1)
    {
        send();

    }


}

