#ifndef __BSP_UART_H
#define __BSP_UART_H

#include "stm32f10x.h"


#define USART1_RX_PIN            GPIO_Pin_10
#define USART1_RX_SOURCE         GPIO_PinSource10
#define USART1_TX_PIN            GPIO_Pin_9
#define USART1_TX_SOURCE         GPIO_PinSource9
#define USART1_PORT              GPIOA
#define USART1_BAUDRATE          115200

#define USART2_RX_PIN            GPIO_Pin_3
#define USART2_RX_SOURCE         GPIO_PinSource3
#define USART2_TX_PIN            GPIO_Pin_2
#define USART2_TX_SOURCE         GPIO_PinSource2
#define USART2_PORT              GPIOA
#define USART2_BAUDRATE          115200


#define USART3_RX_PIN            GPIO_Pin_11
#define USART3_RX_SOURCE         GPIO_PinSource11
#define USART3_TX_PIN            GPIO_Pin_10
#define USART3_TX_SOURCE         GPIO_PinSource10
#define USART3_PORT              GPIOB
#define USART3_BAUDRATE          115200

void serial_init(void);

#endif
