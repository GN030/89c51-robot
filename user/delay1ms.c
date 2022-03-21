#include "delay1ms.h"

void delay1ms(unsigned char n) //约n(ms)延时
{
    unsigned char i,j,k;
    for(k=0; k<n; k++)
    {
        for(j=0; j<10; j++) // 约1ms延时
        {
            for(i=0; i<30; i++) //约0.1ms延时
            {
                ;
            }
        }
    }
}