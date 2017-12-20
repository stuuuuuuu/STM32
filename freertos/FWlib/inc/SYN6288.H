#ifndef __SYN6288__
#define __SYN6288__

#include "stdio.h"
#include "system.h" 

extern void USART_Send_Byte(u8 mydata);
extern void TTS_Init(void);
extern void TTSPlay(u8 sound,char *Text);
extern void USART3_Init(u32 bound);




#endif
