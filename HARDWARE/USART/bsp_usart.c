#include "stm32f10x.h"
#include "usart.h"
#include "vision.h"
#include "led.h"
u8 buff=0;
int i;
typedef union{
	float data_raw;
	uint8_t data[4];
}Float_Transform_u;

void uart4_init(void)
{
	GPIO_InitTypeDef GPIO_UART4;
	USART_InitTypeDef USART_UART4;
	NVIC_InitTypeDef NVIC_UART4;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_UART4.GPIO_Pin = GPIO_Pin_10;
  GPIO_UART4.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_UART4.GPIO_Mode = GPIO_Mode_AF_PP;	
  GPIO_Init(GPIOC, &GPIO_UART4);
   
 
  GPIO_UART4.GPIO_Pin = GPIO_Pin_11;
	 GPIO_UART4.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_UART4.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC,&GPIO_UART4); 
	
	USART_UART4.USART_BaudRate=115200;
	USART_UART4.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
	USART_UART4.USART_WordLength=USART_WordLength_8b;
	USART_UART4.USART_StopBits=USART_StopBits_1;
	USART_UART4.USART_Parity= USART_Parity_No;
	USART_UART4.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4, &USART_UART4); 
	
 
 USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);

	
  NVIC_UART4.NVIC_IRQChannel=UART4_IRQn;
	NVIC_UART4.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_UART4.NVIC_IRQChannelSubPriority=0;
	NVIC_UART4.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_UART4);
	
	USART_Cmd(UART4, ENABLE);
	
}

	float Pitch_angle;
  float Yaw_angle;
uint8_t usart4_rx[3];
uint8_t usart4[9];
	Float_Transform_u temp;
 int cnt = 0;
int vision_data;
extern int workdata;
/************************************/

uint8_t Res=0;
int HaveTast=0;  //数据处理标志
u8 rx[100];//接收数据数组
extern u16 USART_RX_STA;     //接收状态标记，判断头帧接收状态以及作为数组下标


/***********************************/

int testuart=0;
void UART4_IRQHandler()
{

		if((USART_GetITStatus(UART4, USART_IT_RXNE) != RESET))  //接收中断
		{
		Res =USART_ReceiveData(UART4);	//读取接收到的数据

		if(HaveTast==0)//数据处理标志
		{
			if((USART_RX_STA&0xC000)==0xC000)//成功接收帧头
			{
				
				if(Res==0x50)//接收到尾帧
				{
					USART_RX_STA=0;	 
					HaveTast=1;//标志置1，此后串口接收数据无效
					LEDG_ON();

				}
				else//数据接收
				{
					rx[USART_RX_STA&0x3fff]=Res;
					USART_RX_STA++;
				}

			}
			else//未成功接收帧头
			{
				if(USART_RX_STA&0x8000)//已经成功接收帧头0x55
				{
					//判断垃圾类型
					if(Res==Hazardous_Waste)//
					{
						USART_RX_STA |=0x4000;
						garbage.garType=Hazardous_Waste;
					}
					else if(Res==Kitchen_Waste)
					{
						USART_RX_STA |=0x4000;
						garbage.garType=Kitchen_Waste;
					}
					else if(Res==Other_Waste)
					{
						USART_RX_STA |=0x4000;
						garbage.garType=Other_Waste;
					}
					else if(Res==Recyclable_Waste)
					{
						USART_RX_STA |=0x4000;
						garbage.garType=Recyclable_Waste;
					}
					else
					{
						USART_RX_STA=0;//接收失败
					}
				}
				else//判断是否接收到头帧
				{	
					if(Res==0x55)
					{
						USART_RX_STA |=0x8000;
					}
				}
			}
		}
		
	}
	
}
 void usartSendByte(USART_TypeDef* USARTx, uint16_t Data)
{
	USART_SendData(USARTx,Data);
	while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);

}

//发送字符
void usartSendStr(USART_TypeDef* USARTx,char *str)
{
	uint16_t i = 0;
	do{
		usartSendByte(USARTx,*(str+i));
		i++;
	}while(*(str+i) != '\0');

	//判断是否发送完
	while(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
}

