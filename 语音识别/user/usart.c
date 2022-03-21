
#include "config.h"
#define FOSC 22118400L      //System frequency
uint32_t baud=9600;           //UART baudrate


// ���ڳ�ʼ��
// STC10L08XE ��Ƭ�����ڳ�ʼ������
void UartIni(void)
{
    SCON = 0x50;            //8-bit variable UART
    TMOD = 0x20;            //Set Timer1 as 8-bit auto reload mode
    TH1 = TL1 = -(FOSC/12/32/baud); //Set auto-reload vaule
    TR1 = 1;                //Timer1 start run
    ES = 1;                 //Enable UART interrupt
    EA = 1;                 //Open master interrupt switch
}


void Uart_Isr() interrupt 4 using 1
{	
	if(RI)
	{	
		  
	}

}

//	���ڷ���һ�ֽ�����
//	DAT:�����͵�����

void UARTSendByte(uint8_t DAT)
{
	ES  =  0;
	TI=0;
	SBUF = DAT;
	while(TI==0);
	TI=0;
	ES = 1;
}

// ���ڷ����ַ�������
//	*DAT���ַ���ָ��
// API ���ⲿʹ�ã�ֱ�ۣ�
void PrintCom(uint8_t *DAT)
{
	while(*DAT)
	{
	 	UARTSendByte(*DAT++);
	}	
}

