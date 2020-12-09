#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char

sbit RS = P2^5;
sbit RW = P2^6;
sbit E = P2^7;

void delay(uint t)
{
	uint i, j;
	for (i = 0; i < t; i++)
		for (j = 0; j < 110; j++);
}

//дָ��
void write_com(uchar com)
{
	RS = 0;
	RW = 0;
	P0 = com;
	delay(5);
	E = 1;
	delay(5);	
	E = 0;	
}

//д����
void write_data(uchar dat)
{
	RS = 1;
	RW = 0;
	P0 = dat;
	delay(5);
	E = 1;
	delay(5);	
	E = 0;
	
}

//��ʼ��ʱ����Ļ���ݴ���������ʾ����ô��������write_com��ֵҲӦ���޸�
void init()
{
	//0x38		0x01	0x04/0x06/0x07	 0x0c/0x0e�й�겻��˸/0x0f

	write_com(0x38);	//��ʾģʽ(������)

	//write_com(0x01);	//����ָ����п���

	//write_com(0x04);	//ָ��͹��������
	//write_com(0x06);	//ָ��͹��������
	//write_com(0x07);	//������Ļ�����ݴ������������ʾ

	//write_com(0x0e);	//�����ʾ&&����˸
	//write_com(0x0f);	//�����ʾ&&��˸
	write_com(0x0c);	//��겻��ʾ&&����˸

}

void main()
{
	uchar code table1[] = "DATE 2000 08 02";
	uchar code table2[] = "HELLO WRIPRIN";
	uint  i,j;

	init();	

	write_com(0x80 + 1);

	for (i = 0; i < 15; i++)
	{
		write_data(table1[i]);
		delay(100);		
	} 
	
	write_com(0xc0 + 2);
		
	for (j = 0; j < 13; j++)
	{
		write_data(table2[j]);
		delay(100);			
	} 

}