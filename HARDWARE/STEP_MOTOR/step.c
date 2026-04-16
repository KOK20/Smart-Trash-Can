#include "step.h"
#include "led.h"
#include "vision.h"

int k=1;
void DIR_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_5;				 //1-7,2-4
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //开漏输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5

	GPIO_ResetBits(GPIOB,GPIO_Pin_7);//x
	GPIO_SetBits(GPIOB,GPIO_Pin_5);//y
}

void DIR()
{
	
	if(k==0)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);//灯灭提示方向
		 GPIO_SetBits(GPIOB,GPIO_Pin_7);//CCW
	//GPIO_SetBits(GPIOB,GPIO_Pin_3);
		
	}
	else
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_5);//灯亮提示方向
		 GPIO_ResetBits(GPIOB,GPIO_Pin_7);//CW	
	
		//GPIO_ResetBits(GPIOB,GPIO_Pin_3);//CCW			
	}
	
}
void DIR_Change(int axis,char dir)
{
	if(axis==X)
	{
		if(dir=='+')
		{
			 GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		}
		else if(dir=='-')
		{
			 GPIO_SetBits(GPIOB,GPIO_Pin_7);
		}
	}
	else if(axis==Y)
	{
		if(dir=='+')
		{
			 GPIO_SetBits(GPIOB,GPIO_Pin_5);
		}
		else if(dir=='-')
		{
			 GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		}
	}
}
	
int pwm_cnt_1;

void angle_1(double ag)
{

	pwm_cnt_1= ag/360*4000;
	
}
int pwm_cnt_2;

void angle_2(double ag)
{

	pwm_cnt_2= ag/360*6400;
	
}

void GoToX(Garbage *xx)
{
	DIR_Change(X,'+');
	angle_1(xx->x);
	
	TIM_Cmd(TIM4,ENABLE);
	TIM_SetCompare1(TIM4,20);
	
}
void GoToY(Garbage *yy)
{
	

	DIR_Change(Y,'+');
	angle_2(yy->y);
	
	TIM_Cmd(TIM3,ENABLE);
	TIM_SetCompare3(TIM3,20);
	
}



void GO_ZERO(Garbage *pos)
{
	DIR_Change(X,'-');
	DIR_Change(Y,'-');
		
	angle_1(pos->destination[X]);
	TIM_Cmd(TIM4,ENABLE);
	TIM_SetCompare1(TIM4,20);
	
	angle_2(pos->destination[Y]);
	TIM_Cmd(TIM3,ENABLE);
	TIM_SetCompare3(TIM3,20);
	
}
void X_GO_Dis(Garbage *pos)
{
	if(pos->destination[X] < pos->x) DIR_Change(X,'-');
	else if(pos->destination[X]>=pos->x) DIR_Change(X,'+');
	angle_1(pos->diff_val[X]);
	TIM_Cmd(TIM4,ENABLE);
	TIM_SetCompare1(TIM4,20);
	
}
void Y_GO_Dis(Garbage *pos)
{
	if(pos->destination[Y] < pos->y) DIR_Change(Y,'-');
	else if(pos->destination[Y]>=pos->y) DIR_Change(Y,'+');
	angle_2(pos->diff_val[Y]);
	TIM_Cmd(TIM3,ENABLE);
	TIM_SetCompare3(TIM3,20);
	
}
void Axis_Calc(Garbage *axis)
{
	
	if(garbage.garType==Other_Waste)
	{
		garbage.destination[X]=0;
		garbage.destination[Y]=0;
		garbage.diff_val[X]=garbage.destination[X]-garbage.x;
		garbage.diff_val[Y]=garbage.destination[Y]-garbage.y;
	}
	else if(garbage.garType==Kitchen_Waste)
	{
		garbage.destination[X]=630;
		garbage.destination[Y]=0;
		garbage.diff_val[X]=garbage.destination[X]-garbage.x;
		garbage.diff_val[Y]=garbage.destination[Y]-garbage.y;
	}
	else if(garbage.garType==Hazardous_Waste)
	{
		garbage.destination[X]=0;
		garbage.destination[Y]=700;
		garbage.diff_val[X]=garbage.destination[X]-garbage.x;
		garbage.diff_val[Y]=garbage.destination[Y]-garbage.y;
	}
	else if(garbage.garType==Recyclable_Waste)
	{
		garbage.destination[X]=630;
		garbage.destination[Y]=700;
		garbage.diff_val[X]=garbage.destination[X]-garbage.x;
		garbage.diff_val[Y]=garbage.destination[Y]-garbage.y;
	}
	
}
	


















