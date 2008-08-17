#include "serial.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#include <lcutil/delay.h>
#include <lcutil/assert.h>

#define USART_BAUD_CALC(RATE, F) ((F) / ((RATE) * 16l) - 1)

static FILE usart_in_out = FDEV_SETUP_STREAM(&usart_putchar, &usart_getchar, _FDEV_SETUP_RW);

void usart_init(int enable_stream)
{
    UBRRH = (uint8_t)(USART_BAUD_CALC(USART_BAUD_RATE, F_OSC) >> 8);
    UBRRL = (uint8_t)USART_BAUD_CALC(USART_BAUD_RATE, F_OSC);

    loop_until_bit_is_clear(UCSRA, RXC);
    loop_until_bit_is_set(UCSRA, UDRE);
    
    // Enable receiver and transmitter; enable RX interrupt
    UCSRB = _BV(RXEN) | _BV(TXEN) | _BV(RXCIE);
 
    // Asynchronous 8N1
    UCSRC = _BV(URSEL) | (3 << UCSZ0);

    if(enable_stream)
	stdin = stderr = stdout = &usart_in_out;

}

int usart_getchar(FILE * stream)
{

    printf("AVANT\n");
    loop_until_bit_is_set(UCSRA, RXC);
    printf("APRES\n");
   return UDR;
}

int usart_putchar(char c, FILE * stream)
{
    if(c == '\n')
        usart_putchar('\r', stream);
 
   loop_until_bit_is_set(UCSRA, UDRE);
    UDR = c;
    return 0;
}

