#include<reg51.h>
#define uchar unsigned char 
#define uint unsigned int
//1.������ 9600	
//2.fosc = 11.0592
//3.�����ʲ��ӱ�;SMOD = 0
//4.���ڷ�ʽ1��SM0=0��SM1=1
//5.��� T1�����	TH1 = 0xfd��TL1 = fd��

//���ͳ�ʼ��
void init ()
{
	//���ڳ�ʼ��
	EA = 1;//���ж�����
	ES = 1;//���п��ж�����

	//���ڷ�ʽ1	����
	SM0 = 0;
	SM1 = 1;
	
	//T1��ʽ2��ʱ��ģʽ
	ET1 = 1;//t1�ж�����
	TR1 = 1; TMOD = 0x20;// SMOD = 0;
	TH1 = 0xfd; TL1 = 0xfd;

}

main()
{
	uchar temp = 0;
	init();
	while(1)
	{
		temp = P0;
		SBUF = temp;
		while(TI == 0);//�ȴ����ͽ���
		TI = 0;			
	}
}
