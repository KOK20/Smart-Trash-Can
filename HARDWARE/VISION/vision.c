#include "vision.h"
#include "bsp_usart.h"

Garbage garbage;
int ii=1;//数组下标,寻找逗号
int j=1;//数组下标，记录坐标第一个数字下标
int count=0;//记录数据位数
extern int HaveTast;

void Vision_Data_Solve(uint8_t dt[])
{
	if(HaveTast)
	{
	 ii=2;//数组下标,寻找逗号
	 j=2;//数组下标，记录坐标第一个数字下标
	 count=0;//记录数据位数
	
	
	while(dt[ii]!=',')
	{
		count++;//位数加1
		ii+=2;//视觉发过来数据中间有多余0
		
	}
	//此时i下标指向x坐标后逗号
	
	if(count==1) garbage.x=dt[j];
	else if(count==2) garbage.x=dt[j]*10+dt[j+2];
	else if(count==3) garbage.x=dt[j]*100+dt[j+2]*10+dt[j+4];
	else if(count==4) garbage.x=dt[j]*1000+dt[j+2]*100+dt[j+4]*10+dt[j+6];
	
	count=0;
	ii++;//下标指向y坐标第一个数
	j=ii;
	while(dt[ii]!=',')
	{
		count++;
		ii+=2;
	
	}
	//此时i下标指向y坐标后逗号
	if(count==1) garbage.y=dt[j];
	else if(count==2) garbage.y=dt[j]*10+dt[j+2];
	else if(count==3) garbage.y=dt[j]*100+dt[j+2]*10+dt[j+4];
	else if(count==4) garbage.y=dt[j]*1000+dt[j+2]*100+dt[j+4]*10+dt[j+6];


	count=0;
	ii++;
	j=ii;
	
	if(dt[j]==1) garbage.agl=ZERO;
	else garbage.agl=NINETY;
	
	
	
	
	
	}
}

void Data_Init(Garbage *init)
{
	init->garType=Recyclable_Waste;
	init->x=340;
	init->y=400;
	
}
