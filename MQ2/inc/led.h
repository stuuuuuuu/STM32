#ifndef __LED_H
#define	__LED_H

#define uchar unsigned char 
#define uint unsigned int 
extern unsigned char ge,shiw,bai;
extern unsigned char dcshi,dcge;
	
extern void DelayUs(unsigned char us);
extern void WriteCommand(unsigned char c);
extern void WriteData(unsigned char c);
extern void ShowChar(unsigned char pos,unsigned char c);
extern void ShowChar2(unsigned char pos,unsigned char c);
extern void ShowString (unsigned char line,char *ptr) ;
extern void InitLcd();
extern void disp(void);
extern void disp2(int temp_data);
#endif 