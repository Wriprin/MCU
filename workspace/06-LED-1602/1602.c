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

//写指令
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

//写数据
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

//初始化时若屏幕数据从右向左显示，那么主函数中write_com的值也应该修改
void init()
{
	//0x38		0x01	0x04/0x06/0x07	 0x0c/0x0e有光标不闪烁/0x0f

	write_com(0x38);	//显示模式(必须有)

	//write_com(0x01);	//清屏指令，可有可无

	//write_com(0x04);	//指针和光标向左移
	//write_com(0x06);	//指针和光标向右移
	//write_com(0x07);	//整个屏幕的数据从右向左滚动显示

	//write_com(0x0e);	//光标显示&&不闪烁
	//write_com(0x0f);	//光标显示&&闪烁
	write_com(0x0c);	//光标不显示&&不闪烁

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