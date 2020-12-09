#include <reg51.h>
#define uchar unsigned char 
#define uint unsigned int

sbit dula = P2^0;
sbit wela = P2^1;

uchar count, arg, tens, unit;

void delay(uint t);
void display(uchar tens, uchar unit);

uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};

void delay(uint t)
{
	int i,j;
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


void init()
{

	TMOD = 0x01;
	TH0 = 19456 / 256;
	TL0 = 19456 % 256;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	
	count = 0;
	unit = 0;
	tens = 0;
	arg = 60;

}

void t0() interrupt 1
{  	
	TH0 = (65536 - 45872) / 256;
	TL0 = (65536 - 45872) % 256;

	count++;
	
	if (count == 1)
	{
		count = 0;
		arg--;
	}
	
	if (arg == 0)
	{
		TR0 = 0;		
	}
	

}

main()
{
	init();

	while(1)
	{
		display(arg / 10,arg % 10);		
	}

}	
