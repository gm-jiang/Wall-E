/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  WALL-E
  * @version V3.5.0
  * @date    25-08-2018
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * 
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <string.h>

#include "dbg_print.h"
#include "bsp_port.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/** @addtogroup 
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


TaskHandle_t sendHandle;
TaskHandle_t recvHandle;
TaskHandle_t ledHandle;
QueueHandle_t queueTest;

xSemaphoreHandle mutex = NULL;

typedef struct send_msg {
    char data[32];
    char len;
    uint8_t type;
    uint16_t tid;
}send_msg_t;

void sendTask(void *pvParameters)
{
    portBASE_TYPE sendStatus;
    uint16_t i = 0;
    send_msg_t msg_send;
    memset(&msg_send, 0, sizeof(send_msg_t));
    msg_send.type = 1;
    msg_send.tid = i;

    while(1)
    {
        msg_send.tid = i++;
        sendStatus = xQueueSendToBack(queueTest, &msg_send, 1000);
        xSemaphoreTake(mutex, portMAX_DELAY);
        if (sendStatus != pdPASS) {
            dbg_print(PRINT_LEVEL_DEBUG, "[%08dms]SEND TASK: Can not send msg to the queue tid=%d\r\n", xTaskGetTickCount(), msg_send.tid);
        } else {
            dbg_print(PRINT_LEVEL_DEBUG, "[%08dms]<--SEND TASK: Send msg to the queue\r\n", xTaskGetTickCount());
        }
        xSemaphoreGive(mutex);
        vTaskDelay(1000/portTICK_RATE_MS);
    }
}

void recvTask(void *pvParameters)
{
    portBASE_TYPE recvStatus;
    send_msg_t msg_recv;
    while(1)
    {
        recvStatus = xQueueReceive(queueTest, &msg_recv, 0);
        xSemaphoreTake(mutex, portMAX_DELAY);
        if (recvStatus == pdPASS) {
            dbg_print(PRINT_LEVEL_DEBUG, "[%08dms]-->RECV TASK: recvice data: tid=%d type=%d\r\n", xTaskGetTickCount(), msg_recv.tid, msg_recv.type);
        } else {
            dbg_print(PRINT_LEVEL_DEBUG, "[%08dms]***RECV TASK: No data can recvice\r\n", xTaskGetTickCount());
        }
        xSemaphoreGive(mutex);
        vTaskDelay(2000/portTICK_RATE_MS);
    }
}

void ledTask(void *pvParameters)
{
    uint8_t dir = 1;
    uint16_t cnt = 0;
    while(1)
    {
        if (dir == 1) {
            TIM_SetCompare4(TIM3, cnt++);
            //TIM_SetCompare3(TIM3, cnt++);
            if (cnt > 666) {dir = 0;}
        } else {
            TIM_SetCompare4(TIM3, cnt--);
            //TIM_SetCompare3(TIM3, cnt--);
            if (cnt == 0) {dir = 1;}
        }
        vTaskDelay(5);
    }
}

static system_hw_init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    DebugUartInit();
    wall_e_pwm_init();
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     

  /* USARTx configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  /* Infinite loop */
    system_hw_init();

    queueTest = xQueueCreate(3, sizeof(send_msg_t));
    if (queueTest == NULL) {
        return -1;
    }
    mutex = xSemaphoreCreateMutex();

    xTaskCreate(sendTask, "send", 200, NULL, 1, &sendHandle);
    xTaskCreate(recvTask, "recv", 200, NULL, 1, &recvHandle);
    xTaskCreate(ledTask, "led", 200, NULL, 1, &ledHandle);
    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

    // Should never reach there
    while(1);
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
