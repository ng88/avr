#ifndef SERIAL_H
#define SERIAL_H

#ifndef F_OSC
# define F_OSC F_CPU
#endif

#ifndef USART_BAUD_RATE
# define USART_BAUD_RATE 38400
#endif

#include <stdio.h>


/** put ascii data char c */
int usart_putchar(char c, FILE * stream);
/** get binary/ascii data */
int usart_getchar(FILE * stream);
void usart_delay_ms(unsigned short ms);
void usart_init(int enable_stream);


/** put binary data byte b */
void usart_putbyte(char b);

#ifdef SERIAL_FGETS
/** fgets that supports both \r and \n line terminator.*/
char * usart_fgets(char *str, int size);
#endif


#endif


