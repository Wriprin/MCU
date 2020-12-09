#include<reg51.h>
#define uchar unsigned char 
#define uint unsigned int
//1.波特率 9600	
//2.fosc = 11.0592
//3.波特率不加倍;SMOD = 0
//4.串口方式1：SM0=0；SM1=1
//5.查表 T1溢出率	TH1 = 0xfd；TL1 = fd；

//发送初始化
void init ()
{
	//串口初始化
	EA = 1;//总中断允许
	ES = 1;//串行口中断允许

	//串口方式1	发送
	SM0 = 0;
	SM1 = 1;
	
	//T1方式2定时器模式
	ET1 = 1;//t1中断允许
	TR1 = 1; TMOD = 0x20;// SMOD = 0;
	TH1 = 0xfd; TL1 = 0xfd;

}

main()
{
	uchar temp = 0;
	init();
	while(1)
	{
		temp = P0;
		SBUF = temp;
		while(TI == 0);//等待发送结束
		TI = 0;			
	}
}
