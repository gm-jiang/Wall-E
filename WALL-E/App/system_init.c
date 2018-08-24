#include "stm32f10x.h"
#include "dbg_print.h"
#include "system_init.h"
#include "bsp_uart.h"
#include "bsp_gpio.h"

const uint8_t *uid = (uint8_t*)MCU_ID_ADDRESS;
static int get_cpu_id(void)
{
    uint8_t i;
    dbg_print(PRINT_LEVEL_DEBUG, "SYSTEM CPU-ID: ");
    for (i=0; i<12; i++) {
        dbg_print(PRINT_LEVEL_DEBUG, "%02X", uid[i]);
    }
    dbg_print(PRINT_LEVEL_DEBUG, "\r\n");
    return 0;
}

void system_init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0);
    serial_init();
    get_cpu_id();
    gpio_cfg();
    pwm_cfg();
}

