#include "serial.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#include <lcutil/delay.h>
#include <lcutil/assert.h>

#define USART_BAUD_CALC(RATE, F) ((F) / ((RATE) * 16UL) - 1)

static FILE usart_in_out = FDEV_SETUP_STREAM(&usart_putchar, &usart_getchar, _FDEV_SETUP_RW);

void usart_init(int enable_stream)
{
/*    
    loop_until_bit_is_clear(UCSRA, RXC);
    loop_until_bit_is_set(UCSRA, UDRE);
    
    // Enable receiver and transmitter; enable RX interrupt
    UCSRB = _BV(RXEN) | _BV(TXEN) ;//| _BV(RXCIE);
 
    // Asynchronous 8N1
    UCSRC = _BV(URSEL) | (3 << UCSZ0);
*/
    UCSRB |= (1 << RXEN) | (1 << TXEN);   // Turn on the transmission and reception circuitry
    UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); // Use 8-bit character sizes

    UBRRL = USART_BAUD_CALC(USART_BAUD_RATE, F_OSC);
    UBRRH = (USART_BAUD_CALC(USART_BAUD_RATE, F_OSC) >> 8);

    if(enable_stream)
	stdin = stderr = stdout = &usart_in_out;

}

int usart_getchar(FILE * stream)
{
    while((UCSRA & (1 << RXC)) == 0);
    //loop_until_bit_is_set(UCSRA, RXC);


    return UDR;
}

char usart_getbyte()
{
    while((UCSRA & (1 << RXC)) == 0);
    return UDR;
}

int usart_putchar(char c, FILE * stream)
{
    if(c == '\n')
        usart_putchar('\r', stream);
 
    //loop_until_bit_is_set(UCSRA, UDRE);
    while((UCSRA & (1 << UDRE)) == 0);

    UDR = c;
    return 0;
}

void usart_putbyte(char b)
{
    while((UCSRA & (1 << UDRE)) == 0);
    UDR = b;
}


#ifdef SERIAL_FGETS
char * usart_fgets(char *str, int size)
{
        char *cp;
        int c;

        if (size <= 0)
                return NULL;

        size--;
        for (c = 0, cp = str; !(c == '\r' || c == '\n') && size > 0; size--, cp++)
	{
	    if ((c = usart_getchar(0)) == EOF)
		return NULL;
	    *cp = (char)c;
        }
        *cp = '\0';

        return str;
}
#endif
