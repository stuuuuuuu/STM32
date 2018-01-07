#ifndef __HCSR04_H
#define	__HCSR04_H
#include "reg52.h"
//extern void HCSR04Init();
extern int Measure_Distance(void);
extern void Trig_SuperSonic(void);
extern void Init_MCU(void);
extern void Init_Parameter(void);

extern char b,c,d,e;
extern int distancee;
extern float  gSpeed;	

#define VELOCITY_30C	3495       //30���϶�ʱ�����٣�����V= 331.5 + 0.6*�¶ȣ� 
#define VELOCITY_23C	3453       //23���϶�ʱ�����٣�����V= 331.5 + 0.6*�¶ȣ� 
sbit INPUT  = P3^2;                //�������ն˿�
sbit OUTPUT = P1^0;   



#endif