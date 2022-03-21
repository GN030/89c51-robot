#include <reg52.h>
#include "motor.h"

#define MotorData P1                    //����������ƽӿڶ���
unsigned char sport;//�˶�ģʽ��־
unsigned char phasecw[4] = {0x88,0x44,0x22,0x11}; //��ת �����ͨ���� D-C-B-A
unsigned char phaseccw[4]= {0x11,0x22,0x44,0x88}; //��ת �����ͨ���� A-B-C-D


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
//˳ʱ��ת��
void MotorCW(void)
{
    unsigned char i;
    for(i=0; i<4; i++)
    {
        MotorData=phasecw[i];
        Delay_xms(4);//ת�ٵ���
    }
}
//��ʱ��ת��
void MotorCCW(void)
{
    unsigned char i;
    for(i=0; i<4; i++)
    {
        MotorData=phaseccw[i];
        Delay_xms(4);//ת�ٵ���
    }
}
//ֹͣת��
void MotorStop(void)
{
    MotorData=0x00;
}
void HandDown()
{
    unsigned char i;
    for(i=0; i<171; i++)
    {
        MotorCCW();  //��ʱ��ת��
    }
    MotorStop();  //ֹͣת��
}
void HandUp()
{
    unsigned char i;
    for(i=0; i<171; i++)
    {
        MotorCW();  //��ʱ��ת��
    }
    MotorStop();  //ֹͣת��
}
void MotorInit()
{
    MotorStop();
    stop();
}
/*4���ж���Ӧ����*/
void Com_Int(void) interrupt 4	//���ǵ�Ƭ���Ĵ���ͨ���жϳ���,interrupt 4���ǵ��ĸ��ж�Դ��Ϊ�����ж�
{
    unsigned char receive_data;
    if(RI) 		//RI�����жϱ�־λ��RI=1��ʾ֡������ɡ���Ѱַ��־λ����ʽ1ʱ����λ��Ӳ����λ��
    {
        RI=0; 	//��RI�����������
        receive_data = SBUF;//��sm2=0ʱ���Ͳ��ܵ�9λ������0����1�����ý���������sbuf���������ж����롣����ʱri�Ƿ���λ��sm2��rb8��ͬ������
        switch(receive_data)//�˶�ģʽ�б�
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
            switch(receive_data)//��������ָ��ı��Ӧ����ĵ�λ
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
/*���ô���ͨ��*/
void UsartConfiguration()
{
    SCON=0X50;	//SCON���пڿ��ƼĴ��������ڿ��ƴ���ͨ�ŵķ�ʽѡ�񡢽��պͷ��ͣ�ָʾ���ڵ�״̬��
    //��ʽ1,���п�Ϊ10λͨ���첽�ӿڡ����ͻ����һ֡������ϢΪ10λ������1λ��ʼλ��0����8λ����λ��1λֹͣλ��1����
    TMOD=0X20;	//TMOD��ʱ����������ģʽ���ƼĴ���	,0x20��8λ�Զ����ض�ʱ��1
    PCON=0X00;	//PCON��Ƭ����Դ����ר�üĴ���
    TH1=0Xfd;	//��ʱ������ֵ
    TL1=0Xfd;	//��ʱ����ֵ ������Ϊ9600�������fd250
    TR1= 1;	//��ʱ��1���п���λ������塰0������GATE=0��TR1�á�1��������ʱ��1��
    ES = 1;	//ES=1�������пڽ��ܡ������жϡ�
    EA = 1;	//EA=1��CPU�������жϿ���
}