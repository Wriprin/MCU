#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char

sbit dula = P2^0;
sbit wela = P2^1;

uchar count, tens, unit;
uint arg = 60;

uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};

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
	P0=0xfe; wela=1; wela=0; delay(5);

	P0=0xff; wela=1; wela=0;
	P0=table[unit]; dula=1; dula=0;
	P0=0xfd; wela=1; wela=0; delay(5);			
}

void init()
{
	TMOD = 0x15;
	
	TH1 = (65536 - 45872) / 256; 
	TL1 = (65536 - 45872) % 256;
	
	TH0 = (65536 - 1) / 256;
	TL0 = (65536 - 1) % 256; 

	EA = 1;
	EX0 = 1;
	EX1 = 1;
	IT0 = 1;
	IT1 = 1;

	ET0 = 1;
	ET1 = 1;
	TR0 = 1;
	TR1 = 0;
}


//控制启动
void int0() interrupt 0
{
	TR1 = 1;
}

//控制暂停
void int1() interrupt 2
{
	TR1 = 0;	
}

//复位
void t0() interrupt 1
{
	TH0 = (65536 - 1) / 256;
	TL0 = (65536 - 1) % 256;
	arg = 60;
	TR1 = 0;
}

//定时器
void t1() interrupt 3
{
	TH1 = (65536 - 45872) / 256; 
	TL1 = (65536 - 45872) % 256;
	count++;
	if (count >= 5)
	{
		count = 0;
		arg--;
	}

	if (arg == 0)
	{
		TR1 = 0;		
	} 
}

void main()
{
	init();
	while(1)
	{
		display(arg / 10, arg % 10);	
	} 
	
}