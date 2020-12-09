#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int

sbit dula=P2^0;
sbit wela=P2^1;

uchar unit, tens, count;
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};

void delay(uint t);
void display(tens, unit);

void delay(uint t)
{
	int i,j;
	for (i = 0; i < t; i++)
		for (j = 0; j < 110; j++);		
}
				  


void int0() interrupt 0
{
	delay(5);
	if(count < 99) 
		count++;
	
}

void int1() interrupt 2
{
	delay(5);
	if(count > 0) 
		count--;
		
}

void t0() interrupt 1
{
	delay(5);
	count = 0;
	TH0 = 0xff;
    TL0 = 0xff;
}

void display(tens, unit)
{
	P0=0xff; wela=1; wela=0;
	P0=table[tens]; dula=1; dula=0;
	P0=0xfe; wela=1; wela=0; delay(5);

	P0=0xff; wela=1; wela=0;
	P0=table[unit]; dula=1; dula=0;
	P0=0xfd; wela=1; wela=0; delay(5);
}


void main()
{
	TMOD = 0x05;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	TH0 = 0xff;
	TL0 = 0xff;
	EX0 = 1;
	EX1 = 1;
	IT0 = 1;
	IT1 = 1;
	count = 0;
	unit = 0;
	tens = 0;
	while(1)
	{
		display(count / 10, count % 10);
	}
}