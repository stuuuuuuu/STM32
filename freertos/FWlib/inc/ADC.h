#ifndef __ADC__
#define __ADC__





#include "stm32f10x.h"

extern void ADC1_Init(void);
extern void ADC_change(void);
extern int rt_BPM(void);
extern int rt_IBI(void);
extern void spend(void);





#endif
