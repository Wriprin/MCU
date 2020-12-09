#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char

sbit dula = P2^0;
sbit wela = P2^1;

uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};

void delay(uint t);
void display(uchar tens, uchar unit);

uchar num, count, flag;

void delay(uint t)
{
	int i, j;
	for (i = 0; i < t; i++)
		for (j = 0; j < 110; j++);	
}

void display(uchar tens, uchar unit)
{
 	P0=0xff; wela=1; wela=0;
	P0=table[tens]; dula=1; dula=0;
	P0=0xfe; wela=1; wela=0; delay(1);

	P0=0xff; wela=1; wela=0;
	P0=table[unit]; dula=1; dula=0;
	P0=0xfd; wela=1; wela=0; delay(1);		
}

//int0,int1,t0初始化
void init()
{
//int0,int1初始化
	EA = 1;
	EX0 = 1;
	EX1 = 1;
	IT0 = 1;
	IT1 = 1;

//t0初始化		
	ET0 = 1;	  
	TR0 = 1;
	TMOD = 0x01; 
	TH0 = (65536 - 1) / 256;
	TL0 = (65536 - 1) % 256;
}

void int0() interrupt 0
{
	flag++;
	if (flag % 2 == 1)	//点第一（奇数）次，计时；点第二（偶数）次，停止
	{
		TR0 = 1; 
		TH0 = (65536 - 1)/256;
		TL0 = (65536 - 1)%256;
	}
	else
	{
		TR0 = 0;
	}
}

void int1() interrupt 2
{
	num = 0;
	TR0 = 0;
	flag = 0;	
}

void t0() interrupt 1
{
	count++;
	if (count == 20)
	{
		count = 0;
		num++;
	}				

	if (num == 99)
	{
		TR0 = 0;
		TH0 = (65536 - 1)/256;
		TL0 = (65536 - 1)%256;
	}
}

main()
{
	init();
	while(1)				                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
	{
		display(num / 10,num % 10);	
	}	
}