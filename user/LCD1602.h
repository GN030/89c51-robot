#ifndef __LCD1602_H__
#define __LCD1602_H__


/*����ʵϰlcd1602����λ��*/
sbit RS=P2^2;//rs���ţ�H���ݣ�L����
sbit E=P2^1;//lcden���ţ�������ʹ�ܣ�ʹ��������С150ns
//sbit RW=GND;//rw���ţ�H��ȡ��Lд��

void LCD_T();
void LCD_H();
void LCDInit();
void LCDWrdata(unsigned char dat);
void LCDWrcom(unsigned char cdat);

#endif