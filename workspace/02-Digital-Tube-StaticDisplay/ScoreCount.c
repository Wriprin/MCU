#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char

sbit dula = P2^0;
sbit wela = P2^1;
sbit toggle = P1^6;
sbit led = P1^7;

uchar code table[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void delay(uint t);
void display(uchar a, uchar b);

void delay(uint t)
{
	int i, j;
	for(i = 0; i < t; i++)
		for(j = 0; j < 110; j++);	
}

void display(uchar a, uchar b)
{
	P0=0xff; wela=1; wela=0;	
	P0=table[a]; dula=1; dula=0;
	P0=0xfe; wela=1; wela=0; delay(5);

	P0=0xff; wela=1; wela=0;	
	P0=table[b]; dula=1; dula=0;
	P0=0xfd; wela=1; wela=0; delay(5);		
}

void main()
{
	int count = 0;		

	
	while(1)
	{	
		delay(5); 
	
		if (count == 100)
		{
			count = 0;
		}	
		if (toggle == 0)
		{
			led = 0;
			count += 5;
			display(count / 10, count % 10);	
		}			
		else if (toggle == 1)
		{
			led = 1;
		}	
		
		display(count / 10, count % 10);

	} 		  	
}