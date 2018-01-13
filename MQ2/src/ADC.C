#include "ADC.h"
#include "reg52.h"
BYTE ch = 0;  

/*----------------------------
ADC interrupt service routine
----------------------------*/
void adc_isr() interrupt 5 using 1
{
    ADC_CONTR &= !ADC_FLAG;         //Clear ADC interrupt flag




    
    if (++ch > 7) ch = 0;           //switch to next channel
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | ch;
}
int dat()
{
	return ADC_RES;
}
/*----------------------------
Initial ADC sfr
----------------------------*/
void InitADC()
{
    P1ASF = 0xff;                   //Set all P1 as analog input port
    ADC_RES = 0;                    //Clear previous result
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | ch;
    Delay(2);                       //ADC power-on delay and Start A/D conversion
}




/*----------------------------
Software delay function
----------------------------*/
void Delay(WORD n)
{
    WORD x;

    while (n--)
    {
        x = 5000;
        while (x--);
    }
}