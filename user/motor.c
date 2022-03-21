#include <reg52.h>
#include "motor.h"

#define MotorData P1                    //步进电机控制接口定义
unsigned char sport;//运动模式标志
unsigned char phasecw[4] = {0x88,0x44,0x22,0x11}; //正转 电机导通相序 D-C-B-A
unsigned char phaseccw[4]= {0x11,0x22,0x44,0x88}; //反转 电机导通相序 A-B-C-D


void stop()
{
    in1=0;
    in2=0;
    in3=0;
    in4=0;
}
void forward()
{
    in1=1;
    in2=0;
    in3=1;
    in4=0;
}
void back()
{
    in1=0;
    in2=1;
    in3=0;
    in4=1;
}
void left()
{
    in1=0;
    in2=1;
    in3=1;
    in4=0;
}
void right()
{
    in1=1;
    in2=0;
    in3=0;
    in4=1;
}
void Delay_xms(unsigned int x)
{
    unsigned int i,j;
    for(i=0; i<x; i++)
        for(j=0; j<112; j++);
}
//顺时针转动
void MotorCW(void)
{
    unsigned char i;
    for(i=0; i<4; i++)
    {
        MotorData=phasecw[i];
        Delay_xms(4);//转速调节
    }
}
//逆时针转动
void MotorCCW(void)
{
    unsigned char i;
    for(i=0; i<4; i++)
    {
        MotorData=phaseccw[i];
        Delay_xms(4);//转速调节
    }
}
//停止转动
void MotorStop(void)
{
    MotorData=0x00;
}
void HandDown()
{
    unsigned char i;
    for(i=0; i<171; i++)
    {
        MotorCCW();  //逆时针转动
    }
    MotorStop();  //停止转动
}
void HandUp()
{
    unsigned char i;
    for(i=0; i<171; i++)
    {
        MotorCW();  //逆时针转动
    }
    MotorStop();  //停止转动
}
void MotorInit()
{
    MotorStop();
    stop();
}
/*4号中断响应程序：*/
void Com_Int(void) interrupt 4	//这是单片机的串行通信中断程序,interrupt 4就是第四个中断源，为串口中断
{
    unsigned char receive_data;
    if(RI) 		//RI接收中断标志位，RI=1表示帧接收完成。可寻址标志位。方式1时，该位由硬件置位。
    {
        RI=0; 	//对RI进行软件清零
        receive_data = SBUF;//当sm2=0时，就不管第9位数据是0还是1，都得将数据送入sbuf，并发出中断申请。即此时ri是否置位由sm2和rb8共同决定。
        switch(receive_data)//运动模式判别
        {
        case('8'):
        {
            sport=0;
            break;
        }
        case('9'):
        {
            sport=1;
            break;
        }
        }
        if(sport)
        {
            switch(receive_data)//按照蓝牙指令改变对应舵机的电位
            {
            case ('0'):
            {
                stop();
                break;
            }
            case ('1'):
            {
                forward();
                break;
            }
            case ('2'):
            {
                back();
                break;
            }
            case ('3'):
            {
                left();
                break;
            }
            case ('4'):
            {
                right();
                break;
            }
            case ('5'):
            {
                HandUp();
                break;
            }
            case ('6'):
            {
                HandDown();
                break;
            }
            }
        }
    }
}
/*配置串口通信*/
void UsartConfiguration()
{
    SCON=0X50;	//SCON串行口控制寄存器，用于控制串行通信的方式选择、接收和发送，指示串口的状态。
    //方式1,串行口为10位通用异步接口。发送或接收一帧数据信息为10位，包括1位起始位“0”、8位数据位、1位停止位“1”。
    TMOD=0X20;	//TMOD定时器、计数器模式控制寄存器	,0x20，8位自动加载定时器1
    PCON=0X00;	//PCON单片机电源控制专用寄存器
    TH1=0Xfd;	//定时器重载值
    TL1=0Xfd;	//定时器初值 波特率为9600算出来的fd250
    TR1= 1;	//定时器1运行控制位。软件清“0”。当GATE=0，TR1置“1”启动定时器1。
    ES = 1;	//ES=1，允许串行口接受、发送中断。
    EA = 1;	//EA=1，CPU对所有中断开放
}