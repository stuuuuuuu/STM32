#include "REG51.H"
#include "INTRINS.H"
#include "DS18B20.h"
#include  "led.h"

typedef unsigned char BYTE;

sbit DQ = P3^3;                     //DS18B20的数据口位P3.3
Temp = 0;
void DelayXus(BYTE n);
void DS18B20_Reset();
void DS18B20_WriteByte(BYTE dat);
BYTE DS18B20_ReadByte();

void DS18B20_init()
{	 
	BYTE TPL ;
	BYTE TPH ;
    DS18B20_Reset();                //设备复位
    DS18B20_WriteByte(0xCC);        //跳过ROM命令
    DS18B20_WriteByte(0x44);        //开始转换命令
    
    DS18B20_Reset();                //设备复位
    DS18B20_WriteByte(0xCC);        //跳过ROM命令
    DS18B20_WriteByte(0xBE);        //读暂存存储器命令
    TPL = DS18B20_ReadByte();       //读温度低字节
    TPH = DS18B20_ReadByte();       //读温度高字节
	Temp = TPH;
	Temp <<= 8;
	Temp |= TPL;
	Temp = Temp * 0.0625 *10 + 0.5;


}

/**************************************
延时X*10微秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数
当改用1T的MCU时,请调整此延时函数
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
复位DS18B20,并检测设备是否存在
**************************************/
void DS18B20_Reset()
{
    CY = 1;
    while (CY)
    {
        DQ = 0;                     //送出低电平复位信号
        DelayX0us(48);              //延时至少480us
        DQ = 1;                     //释放数据线
        DelayX0us(6);               //等待60us
        CY = DQ;                    //检测存在脉冲
        DelayX0us(42);              //等待设备释放数据线
    }
}

/**************************************
从DS18B20读1字节数据
**************************************/
BYTE DS18B20_ReadByte()
{
    BYTE i;
    BYTE dat = 0;

    for (i=0; i<8; i++)             //8位计数器
    {
        dat >>= 1;
        DQ = 0;                     //开始时间片
        _nop_();                    //延时等待
        _nop_();
        DQ = 1;                     //准备接收
        _nop_();                    //接收延时
        _nop_();
        if (DQ) dat |= 0x80;        //读取数据
        DelayX0us(6);               //等待时间片结束
    }

    return dat;
}

/**************************************
向DS18B20写1字节数据
**************************************/
void DS18B20_WriteByte(BYTE dat)
{
    char i;

    for (i=0; i<8; i++)             //8位计数器
    {
        DQ = 0;                     //开始时间片
        _nop_();                    //延时等待
        _nop_();
        dat >>= 1;                  //送出数据
        DQ = CY;
        DelayX0us(6);               //等待时间片结束
        DQ = 1;                     //恢复数据线
    }
}
