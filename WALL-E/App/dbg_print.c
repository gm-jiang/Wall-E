#include "dbg_print.h"
#include "stm32f10x_usart.h"
#include "stm32f10x.h"
#include "bsp_uart.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

static char buffer[BUFFER_SIZE];

static void sendstring(char *str)
{
    while(*str!='\0') {
        while(!(USART1->SR & USART_FLAG_TXE));
        USART1->DR = (*str & 0x1FF);
        str++;
    }
}

void dbg_print(int print_level, char *fmt, ...)
{
    if (print_level > PRINT_LEVEL) {
        return;
    } else {
        va_list argp;
        va_start(argp, fmt);
        vsprintf(buffer,fmt, argp);
        sendstring(buffer);
        va_end(argp);
    }
}
