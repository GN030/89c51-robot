#include "delay1ms.h"

void delay1ms(unsigned char n) //Լn(ms)��ʱ
{
    unsigned char i,j,k;
    for(k=0; k<n; k++)
    {
        for(j=0; j<10; j++) // Լ1ms��ʱ
        {
            for(i=0; i<30; i++) //Լ0.1ms��ʱ
            {
                ;
            }
        }
    }
}