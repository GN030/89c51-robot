#ifndef __MOTOR_H__
#define __MOTOR_H__

/*��������ӿ�P1*/
/*ֱ�����ٵ���ӿ�*/
sbit in1=P2^3;	 //0����
sbit in2=P2^4;	 //1����
sbit in3=P2^5;	 //2�Ҷ��
sbit in4=P2^6;   //3�Ҷ��

extern unsigned char sport;//�˶�ģʽ��־

void UsartConfiguration();//���ô���ͨѶ
void MotorInit();//�����ʼ��
#endif