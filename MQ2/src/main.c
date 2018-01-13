#include "reg52.h"
#include "ds18b20.h"
#include "led.h"
#include "time0.h"
#include "ADC.h"
int main()
{
  uint temp;
  uint count_1s;
  uint oil;
  InitLcd();
  InitADC();
  IE = 0X90;
  Timer0Init();	
  temp = DS18B20_init();
  
  while(1)
  {
	
	if(flag_20ms == 0)
	{	  
	count_1s++;
	disp2(temp);
	oil = dat();
	flag_20ms = 0;
	P11 = !P11;
	}
	if(count_1s == 50)
	{
	temp  = DS18B20_init();
	count_1s =0;
	}
 	
  }
  
}