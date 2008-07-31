#ifndef SERIAL_H
#define SERIAL_H


#define F_OSC 4000000		           /* oscillator-frequency in Hz */
#define UART_BAUD_RATE 9600

void uart_delay_ms(unsigned short ms);
void uart_putc(unsigned char c);
void uart_puts (char *s);
void uart_init();

#endif


