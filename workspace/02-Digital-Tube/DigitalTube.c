#include<reg51.h>
#define uint unsigned int
#define	uchar unsigned char

sbit dula = P2^0;
sbit wela = P2^1;

void delay(uint t);
void display(a, b, c, d);
void demo1();
void demo2();
void demo3();
void demo4();
void Birth(a, b, c, d, e, f, g, h);

uchar code table[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};	 //共阴极数码管段选编码=>显示0-9.

//高6位显示‘1’
void demo1()
{

	//清管：数码管所有位断开
	P0=0xff; wela=1; wela=0;		

	//送段码
	P0=0x06; dula=1; dula=0;

	//送位码
	P0=0xC0; wela=1; wela=0;

}
//8位都显示‘2’
void demo2()
{

	//清管：数码管所有位断开
	P0=0xff; wela=1; wela=0;		

	//送段码
	P0=0x5b; dula=1; dula=0;

	//送位码
	P0=0x00; wela=1; wela=0;	
		
}

//高4位显示‘5’
void demo3()
{

	//清管：数码管所有位断开
	P0=0xff; wela=1; wela=0;		

	//送段码
	P0=0x6d; dula=1; dula=0;

	//送位码
	P0=0xf0; wela=1; wela=0;

}

//第5位显示‘0’（从高到低）
void demo4()
{

	//清管：数码管所有位断开
	P0=0xff; wela=1; wela=0;		

	//送段码
	P0=0x3f; dula=1; dula=0;

	//送位码
	P0=0xef; wela=1; wela=0;

}


void display(a, b, c, d)
{
	P0=0xff; wela=1; wela=0;		
	P0=table[a]; dula=1; dula=0; delay(5);
	P0=0xfe; wela=1; wela=0;

	P0=0xff; wela=1; wela=0;		
	P0=table[b]; dula=1; dula=0;delay(5);
	P0=0xfd; wela=1; wela=0;

	P0=0xff; wela=1; wela=0;		
	P0=table[c]; dula=1; dula=0;delay(5);
	P0=0xfb; wela=1; wela=0;

	P0=0xff; wela=1; wela=0;		
	P0=table[d]; dula=1; dula=0;delay(5);
	P0=0xf7; wela=1; wela=0;
}

void Birth(a, b, c, d, e, f, g, h)
{

	P0=0xff; wela=1; wela=0;		
	P0=table[a]; dula=1; dula=0; delay(5);
	P0=0xfe; wela=1; wela=0;

	P0=0xff; wela=1; wela=0;		
	P0=table[b]; dula=1; dula=0; delay(5);
	P0=0xfd; wela=1; wela=0;

	P0=0xff; wela=1; wela=0;		
	P0=table[c]; dula=1; dula=0; delay(5);
	P0=0xfb; wela=1; wela=0;

	P0=0xff; wela=1; wela=0;		
	P0=table[d]; dula=1; dula=0; delay(5);
	P0=0xf7; wela=1; wela=0;

	P0=0xff; wela=1; wela=0;		
	P0=table[e]; dula=1; dula=0; delay(5);
	P0=0xef; wela=1; wela=0;

	P0=0xff; wela=1; wela=0;		
	P0=table[f]; dula=1; dula=0; delay(5);
	P0=0xdf; wela=1; wela=0;

	P0=0xff; wela=1; wela=0;		
	P0=table[g]; dula=1; dula=0; delay(5);
	P0=0xbf; wela=1; wela=0;

	P0=0xff; wela=1; wela=0;		
	P0=table[h]; dula=1; dula=0; delay(5);
	P0=0x7f; wela=1; wela=0;


}

//延时函数
void delay(uint t)
{
	int i, j;
	for (i = 0; i < t; i++)
		for (j = 0; j < 110; j++);
}


void main()
{
//	demo1();	//高6位显示‘1’
//	demo2();	//8位都显示‘2’
//	demo3();	//高4位显示‘5’
//	demo4();	//第5位显示‘0’（从高到低）
//	display();	//2020
	int m = 1;

	while(1)
	{
		switch(m)
		{
			case 0: 		
			Birth(2, 0, 0, 0, 0, 8, 0, 2);
			break;

			case 1:
			demo1();
			break;

			case 2:
			demo2();
			break;

			case 3:
			demo3();
			break;

			case 4:
			demo4();
			break;

			case 5:
			display(2, 0, 2, 0);
			break;
	
		}
	}



}

