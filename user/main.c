#include <reg52.h>
#include "motor.h"
#include "LCD1602.h"
#include "dht11.h"
#include "delay1ms.h"

void main()
{
    sport=0;
    UsartConfiguration();	//���ô���ͨ�ŷ�ʽ
    MotorInit();//�˶�ϵͳ��ʼ��
    DHT11_Read();//DHT11��ʪ�ȴ�������ʼ��
    LCDInit();//LCDҺ����ʾ����ʼ��
    while(1)
    {
        if(sport==0)//�����˶�ģʽ�б�
        {   DHT11_Read();
            LCD_T();
            LCD_H();
        }
    }
}