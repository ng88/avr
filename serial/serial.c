#include "serial.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#include <lcutil/delay.h>
#include <lcutil/assert.h>

#define USART_BAUD_CALC(UART_BAUD_RATE,F_OSC) ((F_OSC)/((UART_BAUD_RATE)*16l)-1)

static FILE usart_stdout = FDEV_SETUP_STREAM(&usart_putchar, NULL, _FDEV_SETUP_WRITE);

int usart_putchar(char c, FILE * stream)
{
    if(c == '\n')
        usart_putchar('\r', stream);
    loop_until_bit_is_set(UCSRA, UDRE);
    UDR = c;
    return 0;
}

void usart_init(int enable_stream)
{
    // Qet baud rate
    UBRRH = (uint8_t)(USART_BAUD_CALC(USART_BAUD_RATE,F_OSC) >> 8);
    UBRRL = (uint8_t)USART_BAUD_CALC(USART_BAUD_RATE,F_OSC);

    loop_until_bit_is_clear(UCSRA, RXC);
    loop_until_bit_is_set(UCSRA, UDRE);
    
    // Enable receiver and transmitter; enable RX interrupt
    UCSRB = _BV(RXEN) | _BV(TXEN) ;//| _BV(RXCIE);
 
    // Asynchronous 8N1
//    UCSRC = _BV(URSEL) | (3 << UCSZ0);
    UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
    if(enable_stream)
	stderr = stdout = &usart_stdout;

}


int usart_getchar()
{

while ( !(UCSRA & (1<<RXC)) );      // RXC: USART Recieve Complete
       
    return UDR; 
/*
   loop_until_bit_is_set(UCSRA, RXC);
   return UDR;
*/
}


