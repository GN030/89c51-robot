#include <reg52.h>
#include "dht11.h"
sbit dht=P2^0;//dht11��������

unsigned int resultByte[5];//ʪ��������ʪ��С�����¶��������¶�С����У��λ

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

/*����DHT11*/
void DHT11_Start()
{
    dht=1;
    dht=0;
    delay20ms();
    dht=1;
    delay70us();
    while(dht==0);//׼����������
    while(dht==1);
}
/*��һ���ֽڵ�����*/
unsigned int DHT11_Read_Byte(void)
{
    unsigned int i,flag,byteRead=0;
    for(i=0; i<8; i++)
    {
        while(dht==0);//����50us
        delay33us();
        if(dht==1)//��ȡ������1
        {
            flag=1;
            while(dht==1);
        }
        else
            flag=0;
        byteRead<<=1;//����һλ
        byteRead|=flag;
    }
    return byteRead;
}
/*���¶Ⱥ�ʪ�Ⱥ����������ֽ�*/
void DHT11_Read(void)
{
    unsigned char i;
    delay1500ms();
    DHT11_Start();
    for(i=0; i<5; i++) //��ȡ����:ʪ������,ʪ��С��,�¶�����,�¶�С��,У����
    {
        resultByte[i]=DHT11_Read_Byte();
    }
}