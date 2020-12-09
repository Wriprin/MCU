#include<reg51.h>
#define uint  unsigned int
#define uchar  unsigned char

sbit dula = P2^0;
sbit wela = P2^1;
sbit led1 = P0^2;

uchar hour1, hour2, min1, min2, sec1, sec2, count, min, sec, hour;

void delay(uint t);
void display(uchar hour1, uchar hour2, uchar min1, uchar min2, uchar sec1, uchar sec2);

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

void init()
{
	TMOD = 0X01;
	TH0 = 19456 / 256;
	TL0 = 19456 % 256;
	EA = 1;
	ET0 = 1;
	TR0 = 1;	 
}

void time0() interrupt 1 
{
	TH0 = 19456 / 256;
	TL0 = 19456 % 256;
	count++;
	if (count >= 20)	//TH0、TL0初值为50ms => 所以20次 = 20*50 = 1000ms = 1s. 
	{
		count = 0;
		sec ++;
		if (sec >= 60)
		{
			sec = 0; 
			min++;
			if (min >= 60)
			{
				min = 0;
				hour++;
				if (hour >= 24)
				{
					hour = 0;
				}
			}
		}
	}

	sec2 = sec / 10;
	sec1 = sec % 10; 
	min2 = min / 10;
	min1 = min % 10;
	hour2 = hour / 10;
	hour1 = hour % 10;

}


void display(uchar hour2, uchar hour1, uchar min2, uchar min1, uchar sec2, uchar sec1)
{
 	P0=0xff; wela=1; wela=0;
	P0=table[hour2]; dula=1; dula=0;
	P0=0xfe; wela=1; wela=0; delay(1);

	P0=0xff; wela=1; wela=0;
	P0=table[hour1]; dula=1; dula=0;
	P0=0xfd; wela=1; wela=0; delay(1);
	
	P0=0xff; wela=1; wela=0;
	P0=table[min2]; dula=1; dula=0;
	P0=0xfb; wela=1; wela=0; delay(1);
	
	P0=0xff; wela=1; wela=0;
	P0=table[min1]; dula=1; dula=0;
	P0=0xf7; wela=1; wela=0; delay(1);
	
	P0=0xff; wela=1; wela=0;
	P0=table[sec2]; dula=1; dula=0;
	P0=0xef; wela=1; wela=0; delay(1);			

	P0=0xff; wela=1; wela=0;
	P0=table[sec1]; dula=1; dula=0;
	P0=0xdf; wela=1; wela=0; delay(1);			
}


void main()
{
	init();
	while(1)
	{
		display(hour2, hour1, min2, min1, sec2, sec1);		
	}
}

				