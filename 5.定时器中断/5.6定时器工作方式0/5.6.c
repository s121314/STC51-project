/*
利用定时器0的工作方式0,编写间隔为1秒的LED灯闪烁程序

定时器工作方式0为13位计数器,最多可转载2^13=8192个数
*/

/*
实验板的时钟频率为11.0592MHz,所以机器周期为12*(1/11059200)
=1.0851us,若t=5ms,那么N=5000/1.0851=4607
*/

/*
定时器方式0为13位计数器,计数时只使用了TL0的低5位,这5位
最多可转载32个数字,再加一就会进位,所以对32求模
*/

#include<reg52.h>
#define uchar unsigned char
sbit led=P1^0;

uchar num;

void init();				  //中断服务初始化程序

void main()
{
	init();					  //中断服务初始化
	while(1)
	{
		if(200==num)		  //1s
		{
			num=0;
			led=~led;
		}	
	}
}

/*中断服务初始化程序*/
void init()
{
	TMOD=0x00;				  //设置定时器0为工作方式0(0000 0000)
	TH0=(9192-4607)/32;		  //装初值,5ms
	TL0=(9192-4607)%32;
	EA=1;					  //开总中断
	ET0=1;					  //开定时器0中断
	TR0=1;					  //启动定时器0
}

/*定时器0中断服务程序*/
void T0_time() interrupt 1
{
	TH0=(8192-4607)/32;
	TL0=(8192-4607)%32;
	num++;	
}