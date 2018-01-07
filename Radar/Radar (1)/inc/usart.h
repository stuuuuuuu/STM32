#ifndef __usart_H
#define __usart_H
#include "reg52.h"	 
#include "intrins.h"
#include "string.h"

typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       long int int64_t;

    /* exact-width unsigned integer types */
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       long int uint64_t;

void UartIni(void);//串口初始化
void UARTSendByte(uint8_t DAT);	//串口发送一字节数据
void PrintCom(uint8_t *DAT,uint8_t len); //打印串口字符串数据




#endif