#ifndef KB_MIO_CONFIG_H
#define KB_MIO_CONFIG_H

#include <serial/serial.h>

#define MIO_CFG_PUTCHAR(c) uart_putc(c);
#define MIO_CFG_LN_BREAK "\r\n"

#endif

