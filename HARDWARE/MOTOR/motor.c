#include "motor.h"
#include "timer.h"
#include "led.h"
#include "delay.h"
void clamp(int angle)//夹爪
{
	TIM_SetCompare1(TIM2,angle*100/9+500);
}

void forward(int angle)//前推
{
	
	TIM_SetCompare2(TIM2,angle*100/9+500);//前推
	
	TIM_SetCompare3(TIM2,angle*100/9+500);//前推
	
}
void Yaw_rotate(int angle)//旋转
{
	
	 TIM_SetCompare4(TIM2,angle*100/9+500);
}
void Auto_Ctrl(void)
{
	
	

}

void Clamp(void)
{
	GPIO_ResetBits(GPIOE,GPIO_Pin_5);
	delay_ms(1000);
}

void Throw(void)
{
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
	delay_ms(100);
}

