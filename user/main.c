#include <reg52.h>
#include "motor.h"
#include "LCD1602.h"
#include "dht11.h"
#include "delay1ms.h"

void main()
{
    sport=0;
    UsartConfiguration();	//配置串口通信方式
    MotorInit();//运动系统初始化
    DHT11_Read();//DHT11温湿度传感器初始化
    LCDInit();//LCD液晶显示屏初始化
    while(1)
    {
        if(sport==0)//进行运动模式判别
        {   DHT11_Read();
            LCD_T();
            LCD_H();
        }
    }
}