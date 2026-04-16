#ifndef _BSP_USART_H
#define _BSP_USART_H
#include "stm32f10x.h"
void uart4_init(void);
void usartSendByte(USART_TypeDef* USARTx, uint16_t Data);
#endif
