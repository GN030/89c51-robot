#ifndef __DHT11_H__
#define __HDT11_H__

#include "intrins.h"

extern unsigned int resultByte[5];//湿度整数，湿度小数，温度整数，温度小数，校验位

void DHT11_Read();//读温度和湿度函数,共五字节

#endif