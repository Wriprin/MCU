#include<reg51.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char

uint m, n;

void delay(uint t)
{
	int i, j;
	for (i = 0; i < t; i++)
		for (j = 0; j < 110; j++);
}

void led1()
{
	P0 = 0xfe;
	for (m = 0; m < 8; m++)
	{
		delay(500);
		P0 = _crol_(P0, 1);
	}
}

void led2()
{
	P0 = 0x7f;
	for (n = 0; n < 8; n++)
	{
		delay(500);
		P0 = _cror_(P0, 1);
	} 	
}

void init()
{
	EA = 1;
	EX1 = 1;
	EX0 = 1;
	IT1 = 1;
	IT0 = 1;
	PX0 = 1;
	PX1 = 0;
}

void int0() interrupt 0
{
	uint i;
	for (i = 0; i < 3; i++)
	{
		P0 = 0x00;	delay(500);	
		P0 = 0xff;	delay(500);	
	}
}

void int1() interrupt 3
{
	uint i;
	for (i = 0; i < 3; i++)
	{
		P0 = 0xaa;	delay(500);	
		P0 = 0x55;	delay(500);	
	}	
}


void main()
{
	init();
	while(1)
	{
		led1();
		led2();					
	}
}					
