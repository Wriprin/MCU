#include<reg51.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char

uchar x;

sbit mrr = P0^0;	//main_road_red/green/yellow
sbit mrg = P0^1;
sbit mry = P0^2;

sbit brr = P0^3;	//branch_road_red/green/yellow
sbit brg = P0^4;
sbit bry = P0^5;

sbit P32 = P3^2;

void DelayX500ms(uint t)
{
	uint i, j;
	for(i = 0; i < t*100; i++)
		for(j = 0; j < 550; j++);
}


void Ex0_int() interrupt 0
{
	x = P0;
	mrr = 0;
	mrg = 1;
	mry = 1;
	brr = 0;
	brg = 1;
	bry = 1;
  	DelayX500ms(40);
	while(P32 == 0);	//等待本次中断信号结束
	P0 = x;
}



void main()
{
	uchar m;
	EX0 = 1;IT0 = 1;
	EX1 = 1;IT1 = 1;
	EA = 1;
	while(1)
	{
		mrr = 1;
		mrg = 0;
		mry = 1;
		brr = 0;
		brg = 1;
		bry = 1;

		DelayX500ms(50);

		for(m = 0;m < 6; m++)
		{
			mrg = !mrg;
			DelayX500ms(1);				
		}

		mrg = 1;
		mry = 0;
		DelayX500ms(4);

		mrr = 0;
		mrg = 1;
		mry = 1;
		brr = 1;
		brg = 0;
		bry = 1;
		DelayX500ms(50);

		for(m = 0; m < 6; m++)
		{
			brg =! brg;
			DelayX500ms(1);				
		}

		brg = 1;
		bry = 0;
		DelayX500ms(4);
	}

}
