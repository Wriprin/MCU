# 51 单片机

------



- [x] ## 1. 控制小灯点亮、熄灭、闪烁、流水灯	

- [x] ## 2. 数码管显示任意位任意（不大于8位）数据 display()


- [x] ## 3. 外部中断：控制小灯、数码管（带中断秒表或电子表、交通灯、计分器等）

- [x] ## 4. 定时器/计数器中断：控制数码管（电子表、正计时或倒计时秒表、交通信号倒计时等）

- [x] ## 5. 串口通信：双机通信发送和接收数据。

- [x] ## 6. 液晶屏1602显示字符、时间：位置、方式、显示时间、时间可调



## 1. Hello Wriprin

![](http://cdn.jsdelivr.net/gh/Wriprin/Wriprin-Gallery/Gallery/Circuit_Hellowriprin.gif)



## 2. 创建工程文件（.c），.hex调试



## 3. I/O口控制小灯任意位置任意数量

```c
//点亮 熄灭  闪烁  流水灯
0 点亮  1 熄灭  delay();//tms
P0^7 ...  P0^0=P0
P0=0xf0  P0=0x0f
//数组法、循环左移右移函数
_crol_   _cror_
```



## 4. 数码管显示

```c
//display(uchar one,.......);
//显示任意数字，任意位置，任意位数
0xfe fd fb  f7  ef  df  bf 7f
display(1,2,3,4);
```



## 5. 外部中断 int0  int1 

```
主程序：标志位设置  优先级  PX0  PX1   1   0
int0 int1中断函数
```



| 中断名<img> |       中断请求  （TCON中断控制寄存器）       |    中断控制（中断触发）  （TCON中断控制寄存器）     |      中断允许  （IE中断允许寄存器 ）      | 中断优先级  （IP中断优先级  寄存器） |
| ----------- | :------------------------------------------: | :-------------------------------------------------: | :---------------------------------------: | :----------------------------------: |
| Int0        |                    IE0=1                     |         IT0=1跳沿触发<br/>  IT0=0低电平触发         | EA=1  总中断允许<br/>  EX0=1 int0中断允许 |  PX0=1高优先级<br/>  PX0=0低优先级   |
| Int1        |                    IE1=1                     |         IT1=1跳沿触发 <br> IT1=0低电平触发          | EA=1  总中断允许<br/>  EX1=1 int1中断允许 |  PX1=1高优先级<br/>  PX1=0低优先级   |
| T0          |                    TF0=1                     | TR0=1启动定时器/计数器<br/>  TR0=0启动定时器/计数器 |  EA=1  总中断允许<br/>  ET0=1 T0中断允许  |  PT0=1高优先级<br/>  PT0=0低优先级   |
| T1          |                    TF1=1                     | TR1=1启动定时器/计数器<br/>  TR1=0启动定时器/计数器 |  EA=1  总中断允许<br/>  ET1=1 T1中断允许  |  PT1=1高优先级<br/>  PT1=0低优先级   |
| 串口        | TI=1发送请求<br/>  RI=1接收请求(SCON寄存器） |                                                     | EA=1  总中断允许<br/>  ES=1 串口中断允许  |   PS=1高优先级 <br/> PS=0低优先级    |



## 6. 定时器中断t0 t1  +  数码管

```c
//电子表、秒表、交通数字倒计时
//主程序：标志位设置  初值设置
//中断计次函数：初值，20次   1次中断    1s   60   1fen   60   1xiaoshi  24
display(num / 10, num % 10);  num = 24   num = 1234
display(num / 1000, num / 100 % 10, num / 10 % 10, num % 10);
```



## 7. 外部中断+计数器中断+数码管

```c
//3个中断标志位设置
//计分器    加分int0  减分 int1 清零 
//t0 计数器作为外部中断使用  65536-1  TMOD = 0x05
```



## 8. 串口中断

```c
//中断标志位设置，根据条件查表初值
//发送程序  接收程序

//串口通用接收程序
uchar receive()
{
	uchar dat;
	while(RI == 0);
	RI = 0;
	dat = SBUF;
	return dat;
}

//串口通用发送程序
void send(uchar dat)
{
	SBUF = dat;
	while(TI == 0);
	TI = 0;
}
```



## 9. 液晶屏1602显示

```c
//任意位置任意字符串任意显示方式  0c  0e   0f
0x80+y  0xc0+y
//液晶显示时钟表
```










