#include<reg51.h>
#include<intrins.h>	//包含_crol_函数所在的头文件
#define uint unsigned int
#define uchar unsigned char

uint m, n, p;

void delay(uint t);
void led1();
void led2();
void led3();
void led4();

void delay(uint t)
{
	uint i, j;
	for (i = 0; i < t; i++)
		for (j = 0; j < 110; j++);	
}

//1.上到下，下到上
void led1()
{	
	for (m = 0; m < 3; m++)
   	{
		P0 = 0xfe;
		for (n = 0; n < 8; n++) 
		{
			delay(500);
			P0 = _crol_(P0, 1);	
		}
		
		for (p = 0; p < 8; p++)
		{
			P0 = _cror_(P0, 1);
			delay(500);
		}   
   	}
}
	

//2.上四个下四个交替点亮五次
void led2()
{
	for (m = 0; m < 5; m++)
	{
		P0 = 0xf0;	delay(500);	   //小灯高位在下，所以上四个灯亮就是11110000，从下往上看，后四位才是上四个灯。
		P0 = 0x0f;	delay(500);
	}
	
}


//3.P0口八个小灯奇数灯偶数灯交替点亮五次
void led3()
{	
	for (m = 0; m < 5; m++)
	{
		P0 = 0xaa;	delay(500);	
		P0 = 0x55;	delay(500);
	}

}

//4.P0八个小灯从两边向中间流动点亮，然后从中间两个小灯向两边流动点亮一边
/*
01111110 0x7e
10111101 0xbd
11011011 0xdb
11100111 0xe7
*/
void led4()
{	
	unsigned char table[] = {0x7e, 0xbd, 0xdb, 0xe7, 0xe7, 0xdb, 0xbd, 0x7e};	 
	for (n = 0; n < 3; n++)
	{
		for (m = 0; m < 7; m++)
		{
			P0 = table[m];	delay(500);
		}

	}
	
}
		
/*
11111110 & 0x0f = 0x0e
11111101 & 0x0f = 0x0d
11111011 & 0x0f = 0x0b
11110111 & 0x0f = 0x07
*/
void main()
{  	
	uchar state;
	while(1)
	{
		state = P2;
		state = state & 0x0f;
		
		switch(state)
		{
			case 0x0e: led1(); break;
			case 0x0d: led2(); break;
			case 0x0b: led3(); break;
			case 0x07: led4(); break;
			default: 0xff; break;
		}

	}
	
}
