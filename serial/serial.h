#ifndef SERIAL_H
#define SERIAL_H

#define F_OSC F_CPU
#define UART_BAUD_RATE 38400
//9600

void uart_putc(unsigned char c);
void uart_delay_ms(unsigned short ms);
void uart_init();

#endif


