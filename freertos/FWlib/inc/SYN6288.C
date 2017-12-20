#include "SYN6288.h"

#include "stdarg.h"

void USART3_Init(u32 bound)
{

		GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    USART_ClockInitTypeDef USART_ClockInitStructure;
     

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //??????
 
 
    GPIO_InitStructure.GPIO_Pin    =  GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_Out_PP;    //????
    GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;    //50M????
    GPIO_Init(GPIOB, &GPIO_InitStructure);

 
 
    /* B10 USART3_Tx */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       //????-TX
    GPIO_Init(GPIOB, &GPIO_InitStructure);
 
    /* B11 USART3_Rx  */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//????-RX
    GPIO_Init(GPIOB, &GPIO_InitStructure);
 
 
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
    USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
    USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
    USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
    USART_ClockInit(USART3, &USART_ClockInitStructure);
    USART_Init(USART3, &USART_InitStructure);
 
    /* Enable the USARTx */
    USART_Cmd(USART3, ENABLE);
     

    USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);               //使能串口3 	
}
void USART_Send_Byte(u8 mydata)
{           
        USART_ClearFlag(USART3,USART_FLAG_TC); 
        USART_SendData(USART3, mydata); 
        while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);
        USART_ClearFlag(USART3,USART_FLAG_TC);
}
void USART3_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USART3);	//读取接收到的数据
		USART_ClearFlag(USART2,USART_FLAG_RXNE);
   	} 
} 
void TTS_Init(void)
{
          
		GPIO_InitTypeDef  GPIO_InitStructure;
				
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);         
		
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2;                                
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               
		GPIO_Init(GPIOD, &GPIO_InitStructure);                                                    
											
}
void TTSPlay(u8 sound,char *Text)
{

        va_list  arg_ptr;
        u8 i=0,xorcrc=0,uLen;
        u8 SoundBuf[110];                                        //???????? 
        char  tmpBuf[120];                                        //
        uLen = (u8)vsprintf(tmpBuf, Text, arg_ptr);
	
        for (i=0;i<100;i++) SoundBuf[i]=0x00;
        SoundBuf[0]=0xFD;
        SoundBuf[1]=0x00;
        SoundBuf[2]=uLen+15;
        SoundBuf[3]=0x01;
        SoundBuf[4]=0x00;
        
        for (i=0;i<uLen;i++)
        {
                SoundBuf[17+i]=tmpBuf[i];
				
        }
        for (i=0;i<uLen+17;i++)
        {
                xorcrc=xorcrc ^ SoundBuf[i];
                USART_Send_Byte(SoundBuf[i]);

        }
        USART_Send_Byte(xorcrc);
}
