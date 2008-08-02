#ifndef SERIAL_H
#define SERIAL_H

#ifndef F_OSC
# define F_OSC F_CPU
#endif

#ifndef USART_BAUD_RATE
# define USART_BAUD_RATE 38400
#endif

#include <stdio.h>

int usart_putchar(char c, FILE * stream);
int usart_getchar();
void usart_delay_ms(unsigned short ms);
void usart_init(int enable_stream);



#endif


