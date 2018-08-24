#ifndef _SYSTEM_INIT_H
#define _SYSTEM_INIT_H

#include "stm32f10x.h"

#define FLASH_OFFSET    0x3000
#define MCU_ID_ADDRESS  0x1FFFF7E8

void system_init(void);

#endif

