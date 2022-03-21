#ifndef __MOTOR_H__
#define __MOTOR_H__

/*步进电机接口P1*/
/*直流减速电机接口*/
sbit in1=P2^3;	 //0左舵机
sbit in2=P2^4;	 //1左舵机
sbit in3=P2^5;	 //2右舵机
sbit in4=P2^6;   //3右舵机

extern unsigned char sport;//运动模式标志

void UsartConfiguration();//配置串口通讯
void MotorInit();//电机初始化
#endif