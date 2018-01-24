#ifndef _sta_tcpclent_test_H
#define _sta_tcpclent_test_H


#include "system.h"


#define User_ESP8266_SSID	  "123"	      //Ҫ���ӵ��ȵ������
#define User_ESP8266_PWD	  "526809654"	  //Ҫ���ӵ��ȵ������

#define User_ESP8266_TCPServer_IP	  "192.168.43.240"	  //Ҫ���ӵķ�������IP
#define User_ESP8266_TCPServer_PORT	  "8080"	  //Ҫ���ӵķ������Ķ˿�


extern volatile uint8_t TcpClosedFlag;  //����һ��ȫ�ֱ���
extern u8 hz;

void ESP8266_STA_TCPClient_Test(void);

extern void send(void);

#endif