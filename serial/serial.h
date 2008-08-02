#ifndef SERIAL_H
#define SERIAL_H

#define F_OSC F_CPU
#define UART_BAUD_RATE 38400
//9600

#include <stdio.h>

int uart_putchar(char c, FILE * stream);
void uart_delay_ms(unsigned short ms);
void uart_init(int enable_stream);

#endif


