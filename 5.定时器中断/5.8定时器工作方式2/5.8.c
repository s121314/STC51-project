/*
工作方式2为8位计数器,自动重装,最多可转载2^8=256个数
*/

/*
实验板时钟周期为11.0592MHz,机器周期12*(1/11059200)=1.0851us;
计250个数,需要250*1.0851=271.275us;
1s需要计数1000000/271.275=3686次
*/

#include<reg52.h>
#define uint unsigned int

sbit led=P1^2;

void init();				//中断服务初始化函数

uint num;					//重要:
							//num需要计数达到3686,远远超过
							//uchar的最大范围256,需要修改
							//变量类型到uint

void main()
{
	init();
	while(1)
	{
		if(3686==num)		   //1s
		{
			num=0;
			led=~led;		
		}
	}
}

/*中断服务初始化函数*/
void init()
{
	TMOD=0x02;				//设置定时器0的工作方式2(0000 0010)
	TH0=256-250;			
	TL0=256-250;			//装初值,271.275us
	EA=1;					//开总中断
	ET0=1;					//开定时器0中断
	TR0=1;					//启动定时器0
}

void T0_time() interrupt 1
{
	TH0=256-250;		   //271.275us
	TL0=256-250;
	num++;
}