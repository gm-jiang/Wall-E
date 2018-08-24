#ifndef _DBG_PRINT_H
#define _DBG_PRINT_H

#include "stm32f10x.h"
#define BUFFER_SIZE          512

enum
{
    PRINT_LEVEL_DEBUG,
    PRINT_LEVEL_ERROR,
    PRINT_LEVEL_WARNING,
    PRINT_LEVEL_INFO,
    PRINT_LEVEL_INFO_LOWLEVEL,
    PRINT_LEVEL_VERBOSE
};

#define PRINT_LEVEL PRINT_LEVEL_WARNING

void dbg_print(int printf_level, char *fmt, ...);

#endif
