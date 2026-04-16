#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
 #include "step.h"
 #include "bsp_usart.h"
 #include "vision.h"
 #include "motor.h"
 #include "GDM.h"
/************************************************
 ALIENTEK精英STM32开发板实验9
 PWM输出实验  
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
vu8 key=0;
extern int k;
extern int flag;
int duojiflag;
int workdata=0;
extern int vision_data;
int yaw_angle=2500;
extern int HaveTast;
int ld=0;
extern int testuart;
extern Garbage garbage;
extern u8 rx[100];
int t=0;
extern int finishx0;
extern int finishy0;
extern int finishx1;
extern int finishy1;
extern int finishx2;
extern int finishy2;
int finishc=0;
int gotoxFinish=0;
int gotoyFinish=0;
int xgotodisFinish=0;
int ygotodisFinish=0;
int a=0;
 int main(void)
 {		
 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
 	DIR_Init();			     //LED端口初始化
	KEY_Init();         	//初始化与按键连接的硬件接口
	LED_Init();
  GDM_Init();
	uart4_init();//视觉通信
	 
	TIM1_PWM_Init(19999,71);//夹爪定时器初始化
	TIM2_PWM_Init(19999,71);//夹爪定时器初始
	TIM3_PWM_Init(299,180);//滑轨定时器初始化化
 	TIM4_PWM_Init(299,160);//滑轨定时器初始化
	TIM8_PWM_Init(19999,71);//夹爪定时器初始化

	 	Data_Init(&garbage);
		//Vision_Data_Solve(rx);//处理视觉数据
		Axis_Calc(&garbage);//计算各点所需坐标
		
	 while(1)
	 {
		 a=GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5);
		 if(t==1)
		 {
			 if(finishx0&&finishy0)
			 {
				 finishx0=0;
				 finishy0=0;
			//到达垃圾目标点
			GoToX(&garbage);
			GoToY(&garbage);
			gotoxFinish=1;
			gotoyFinish=1;
			 }
			if(finishx1&&finishy1)
			{
				//夹垃圾
			  Clamp();
       finishc++;
				finishx1=0;
				finishy1=0;
				//到达垃圾箱位置
				X_GO_Dis(&garbage);
				Y_GO_Dis(&garbage);
				xgotodisFinish=1;
				ygotodisFinish=1;
			}
			
			if(finishx2&&finishy2)
			{
//				finishx0=0;
//				finishy0=0;
				finishx2=0;
				finishy2=0;
				Throw();
			 //回零点
				GO_ZERO(&garbage);
        t=0;
			HaveTast=0;//完成垃圾处理后将此变量置0可继续开启下次数据接收
			
			}
	 }
		 
 }
				

 }

