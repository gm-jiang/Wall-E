#ifndef __BSP_PORT_H
#define __BSP_PORT_H

#ifdef __cpluspluss
extern "C" {
#endif

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

void DebugUartInit(void);
void wall_e_pwm_init(void);

#ifdef __cpluspluss
}
#endif

#endif
