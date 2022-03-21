#ifndef __LCD1602_H__
#define __LCD1602_H__


/*生产实习lcd1602接线位置*/
sbit RS=P2^2;//rs引脚，H数据，L命令
sbit E=P2^1;//lcden引脚，高脉冲使能，使能脉宽最小150ns
//sbit RW=GND;//rw引脚，H读取，L写入

void LCD_T();
void LCD_H();
void LCDInit();
void LCDWrdata(unsigned char dat);
void LCDWrcom(unsigned char cdat);

#endif