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

void UartIni(void);//���ڳ�ʼ��
void UARTSendByte(uint8_t DAT);	//���ڷ���һ�ֽ�����
void PrintCom(uint8_t *DAT,uint8_t len); //��ӡ�����ַ�������




#endif