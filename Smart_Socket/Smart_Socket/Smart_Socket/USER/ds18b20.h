#ifndef __DS18B20_H__
#define __DS18B20_H__

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"


#define  SkipROM    0xCC
#define  SearchROM  0xF0
#define  ReadROM    0x33
#define  MatchROM   0x55
#define  AlarmROM   0xEC

#define  StartConvert    0x44
#define  ReadScratchpad  0xBE
#define  WriteScratchpad 0x4E
#define  CopyScratchpad  0x48
#define  RecallEEPROM    0xB8
#define  ReadPower       0xB4


void ds18b20_init(void);
float ds18b20_read(void);
//unsigned short ds18b20_read(void);


#endif
