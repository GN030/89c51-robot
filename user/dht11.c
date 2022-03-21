#include <reg52.h>
#include "dht11.h"
sbit dht=P2^0;//dht11数据引脚

unsigned int resultByte[5];//湿度整数，湿度小数，温度整数，温度小数，校验位

void delay33us()		//@11.0592MHz
{
    unsigned char i;

    _nop_();
    i = 12;
    while (--i);
}
void delay20ms()		//@11.0592MHz
{
    unsigned char i, j;

    i = 36;
    j = 217;
    do
    {
        while (--j);
    } while (--i);
}
void delay1500ms()		//@11.0592MHz
{
    unsigned char i, j, k;

    _nop_();
    i = 11;
    j = 130;
    k = 111;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}
void delay70us()		//@11.0592MHz
{
    unsigned char i;

    _nop_();
    i = 29;
    while (--i);
}

/*启动DHT11*/
void DHT11_Start()
{
    dht=1;
    dht=0;
    delay20ms();
    dht=1;
    delay70us();
    while(dht==0);//准备接受数据
    while(dht==1);
}
/*读一个字节的数据*/
unsigned int DHT11_Read_Byte(void)
{
    unsigned int i,flag,byteRead=0;
    for(i=0; i<8; i++)
    {
        while(dht==0);//跳过50us
        delay33us();
        if(dht==1)//读取到数据1
        {
            flag=1;
            while(dht==1);
        }
        else
            flag=0;
        byteRead<<=1;//左移一位
        byteRead|=flag;
    }
    return byteRead;
}
/*读温度和湿度函数，共五字节*/
void DHT11_Read(void)
{
    unsigned char i;
    delay1500ms();
    DHT11_Start();
    for(i=0; i<5; i++) //读取数据:湿度整数,湿度小数,温度整数,温度小数,校验数
    {
        resultByte[i]=DHT11_Read_Byte();
    }
}