#include "REG51.H"
#include "INTRINS.H"
#include "DS18B20.h"
#include  "led.h"

typedef unsigned char BYTE;

sbit DQ = P3^3;                     //DS18B20�����ݿ�λP3.3
Temp = 0;
void DelayXus(BYTE n);
void DS18B20_Reset();
void DS18B20_WriteByte(BYTE dat);
BYTE DS18B20_ReadByte();

void DS18B20_init()
{	 
	BYTE TPL ;
	BYTE TPH ;
    DS18B20_Reset();                //�豸��λ
    DS18B20_WriteByte(0xCC);        //����ROM����
    DS18B20_WriteByte(0x44);        //��ʼת������
    
    DS18B20_Reset();                //�豸��λ
    DS18B20_WriteByte(0xCC);        //����ROM����
    DS18B20_WriteByte(0xBE);        //���ݴ�洢������
    TPL = DS18B20_ReadByte();       //���¶ȵ��ֽ�
    TPH = DS18B20_ReadByte();       //���¶ȸ��ֽ�
	Temp = TPH;
	Temp <<= 8;
	Temp |= TPL;
	Temp = Temp * 0.0625 *10 + 0.5;


}

/**************************************
��ʱX*10΢��(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺���
������1T��MCUʱ,���������ʱ����
**************************************/
void DelayX0us(BYTE n)
{
    while (n--)
    {
        _nop_();
        _nop_();
    }
}

/**************************************
��λDS18B20,������豸�Ƿ����
**************************************/
void DS18B20_Reset()
{
    CY = 1;
    while (CY)
    {
        DQ = 0;                     //�ͳ��͵�ƽ��λ�ź�
        DelayX0us(48);              //��ʱ����480us
        DQ = 1;                     //�ͷ�������
        DelayX0us(6);               //�ȴ�60us
        CY = DQ;                    //����������
        DelayX0us(42);              //�ȴ��豸�ͷ�������
    }
}

/**************************************
��DS18B20��1�ֽ�����
**************************************/
BYTE DS18B20_ReadByte()
{
    BYTE i;
    BYTE dat = 0;

    for (i=0; i<8; i++)             //8λ������
    {
        dat >>= 1;
        DQ = 0;                     //��ʼʱ��Ƭ
        _nop_();                    //��ʱ�ȴ�
        _nop_();
        DQ = 1;                     //׼������
        _nop_();                    //������ʱ
        _nop_();
        if (DQ) dat |= 0x80;        //��ȡ����
        DelayX0us(6);               //�ȴ�ʱ��Ƭ����
    }

    return dat;
}

/**************************************
��DS18B20д1�ֽ�����
**************************************/
void DS18B20_WriteByte(BYTE dat)
{
    char i;

    for (i=0; i<8; i++)             //8λ������
    {
        DQ = 0;                     //��ʼʱ��Ƭ
        _nop_();                    //��ʱ�ȴ�
        _nop_();
        dat >>= 1;                  //�ͳ�����
        DQ = CY;
        DelayX0us(6);               //�ȴ�ʱ��Ƭ����
        DQ = 1;                     //�ָ�������
    }
}
