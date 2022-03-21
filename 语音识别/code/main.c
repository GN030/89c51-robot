/*******************************************************
**  �������ƣ�YS-V0.7����ʶ��ģ����������
**	CPU: STC11L32XE
**	����22.1184MHZ
**	�����ʣ�9600 bit/S
**	���ײ�Ʒ��Ϣ��YS-V0.7����ʶ�𿪷���            
/*********************************************************/
#include "config.h"
/************************************************************************************/
//	nAsrStatus ������main�������б�ʾ�������е�״̬������LD3320оƬ�ڲ���״̬�Ĵ���
//	LD_ASR_NONE:		��ʾû������ASRʶ��
//	LD_ASR_RUNING��		��ʾLD3320������ASRʶ����
//	LD_ASR_FOUNDOK:		��ʾһ��ʶ�����̽�������һ��ʶ����
//	LD_ASR_FOUNDZERO:	��ʾһ��ʶ�����̽�����û��ʶ����
//	LD_ASR_ERROR:		��ʾһ��ʶ��������LD3320оƬ�ڲ����ֲ���ȷ��״̬
/***********************************************************************************/
uint8 idata nAsrStatus=0;	
void MCU_init(); 
void ProcessInt0(); //ʶ������
void delay(unsigned long uldata);
void User_handle(uint8 dat);//�û�ִ�в�������
void Led_test(void);//��Ƭ������ָʾ
void Delay200ms();
uint8_t G0_flag=DISABLE;//���б�־��ENABLE:���С�DISABLE:��ֹ���� 
sbit LED=P4^2;//�ź�ָʾ��
//Ӧ��IO�ڶ��� ��ģ���ע P2��
sbit PA1=P1^0; //��Ӧ���ϱ�� P1.0
sbit PA2=P1^1;  //��Ӧ���ϱ�� P1.1
sbit PA3=P1^2;  //.....
sbit PA4=P1^3;  //.....
sbit PA5=P1^4;  //.....
sbit PA6=P1^5;  //.....
sbit PA7=P1^6;  //��Ӧ���ϱ�� P1.6
sbit PA8=P1^7;  //��Ӧ���ϱ�� P1.7

//������
void  main(void)
{	
	uint8 idata nAsrRes;
	uint8 i=0;
	Led_test();
	MCU_init();
	LD_Reset();
	UartIni(); /*���ڳ�ʼ��*/
	nAsrStatus = LD_ASR_NONE;		//	��ʼ״̬��û������ASR
	#ifdef TEST	
  PrintCom("һ�����С��ͬѧ\r\n"); /*text.....*/
	PrintCom("�������1������˭\r\n"); /*text.....*/
	PrintCom("	2���㼸����\r\n"); /*text.....*/
	PrintCom("	3�����רҵ�ò���\r\n"); /*text.....*/
	#endif

	
	
	while(1)
	{
		switch(nAsrStatus)
		{
			case LD_ASR_RUNING:
			case LD_ASR_ERROR:		
				break;
			case LD_ASR_NONE:
			{
				nAsrStatus=LD_ASR_RUNING;
				if (RunASR()==0)	/*	����һ��ASRʶ�����̣�ASR��ʼ����ASR��ӹؼ��������ASR����*/
				{
					nAsrStatus = LD_ASR_ERROR;
				}
				break;
			}
			case LD_ASR_FOUNDOK: /*	һ��ASRʶ�����̽�����ȥȡASRʶ����*/
			{				
				nAsrRes = LD_GetResult();		/*��ȡ���*/
				User_handle(nAsrRes);//�û�ִ�к��� 
				nAsrStatus = LD_ASR_NONE;
				break;
			}
			case LD_ASR_FOUNDZERO:
			default:
			{
				nAsrStatus = LD_ASR_NONE;
				break;
			}
		}// switch	 			
	}// while

}

// LED�Ƽ�ⵥƬ���Ƿ���ָʾ
void Led_test(void)
{
	LED=~ LED;
	Delay200ms();
	LED=~ LED;
	Delay200ms();
	LED=~ LED;
	Delay200ms();
	LED=~ LED;
	Delay200ms();
	LED=~ LED;
	Delay200ms();
	LED=~ LED;
}

//��Ƭ����ʼ��
void MCU_init()
{
	P0 = 0xff;
	P1 = 0x00;
	P2 = 0xff;
	P3 = 0xff;
	P4 = 0xff;
	
	PA1=1;PA2=1;PA3=1;PA4=1;PA5=1;PA6=1;PA7=1;PA8=1;//��ʼ���ߵ�ƽ

	P1M0=0XFF;	//P1�˿�����Ϊ����������ܣ������IO�������������������̵���ģ�鹤��
	P1M1=0X00;

	LD_MODE = 0;		//	����MD�ܽ�Ϊ�ͣ�����ģʽ��д
	IE0=1;
	EX0=1;
	EA=1;
}

//��ʱ����
void Delay200us()		//@22.1184MHz
{
	unsigned char i, j;
	_nop_();
	_nop_();
	i = 5;
	j = 73;
	do
	{
		while (--j);
	} while (--i);
}

void  delay(unsigned long uldata)
{
	unsigned int j  =  0;
	unsigned int g  =  0;
	while(uldata--)
	Delay200us();
}

void Delay200ms()		//@22.1184MHz
{
	unsigned char i, j, k;

	i = 17;
	j = 208;
	k = 27;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void Delay1000ms()		//@22.1184MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 85;
	j = 12;
	k = 155;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay2800ms()		//@22.1184MHz  ��һ���ش�
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 236;
	j = 84;
	k = 188;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay2000ms()		//@22.1184MHz  �ڶ����ش�
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 169;
	j = 24;
	k = 59;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay5000ms()		//@22.1184MHz  �������ش�
{
	unsigned char i, j, k;

	i = 165;
	j = 59;
	k = 28;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


//�жϴ�����
void ExtInt0Handler(void) interrupt 0  
{ 	
	ProcessInt0();				/*	LD3320 �ͳ��ж��źţ�����ASR�Ͳ���MP3���жϣ���Ҫ���жϴ������зֱ���*/
}


//�û�ִ�к��� 
//ʶ��ɹ���ִ�ж������ڴ˽����޸� 
// ͨ������PAx�˿ڵĸߵ͵�ƽ���Ӷ������ⲿ�̵�����ͨ��					 

void 	User_handle(uint8 dat)
{			
			
     //UARTSendByte(dat);//����ʶ���루ʮ�����ƣ�
		 if(0==dat)
		 {
		  	G0_flag=ENABLE;
				LED=0;
				PrintCom("����\r\n"); /*text.....*/
			  PA1=0;//���͵�ƽ
				Delay1000ms();
			  PA1=1;//���ߵ�ƽ
			 
		 }
		 else if(ENABLE==G0_flag)
		 {	
		 		G0_flag=DISABLE;
				LED=1;
			 switch(dat)		   /*�Խ��ִ����ز���,��Ӧ�޸�*/
			  {
				  case CODE_MZ:			/*�����ݡ�*/
						PrintCom("���ǵ�ƻ�����\r\n"); //���������ʾ��Ϣ����ɾ����
						PA2=0;//���ߵ�ƽ
					  Delay2800ms();
						PA2=1;//���ߵ�ƽ				
						break;
					
					case CODE_NL:	 /*������䡱*/
						PrintCom("��1����\r\n");//���������ʾ��Ϣ����ɾ����
						PA3=0;//���͵�ƽ
					  Delay2000ms();
					  PA3=1;//���ߵ�ƽ
						break;
					
					case CODE_ZY:		/*���רҵ��*/				
						PrintCom("���רҵ����õ�רҵ���Ұ����\r\n"); //���������ʾ��Ϣ����ɾ����
						PA4=0;//���ߵ�ƽ
					  Delay5000ms();Delay2000ms();
						PA4=1;//���ߵ�ƽ
						break;				
					
							default:PrintCom("������ʶ�𷢿���\r\n"); //���������ʾ��Ϣ����ɾ����
													break;
				}	
			}	
			else 	
			{
				PrintCom("��˵��һ������\r\n"); //���������ʾ��Ϣ����ɾ����	
			}
}	 
