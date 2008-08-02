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

     // Enable receiver and transmitter; enable RX interrupt
    UCSRB = _BV(RXEN) | _BV(TXEN) | _BV(RXCIE);
 
    // Asynchronous 8N1
    UCSRC = _BV(URSEL) | (3 << UCSZ0);

    if(enable_stream)
	stderr = stdout = &usart_stdout;
}


// INTERRUPT can be interrupted
// SIGNAL can't be interrupted
SIGNAL (SIG_USART_RECV) { // USART RX interrupt
	unsigned char c;
	c = UDR;
	PORTD |= _BV(PD5);
	delay_ms(100);
	PORTD &= ~_BV(PD5);
	usart_putchar(c, 0);
}

static char c = 0;

ISR(USART_RX_vect)
{
    //if(UCSRA & _BV(RXC))
        c = UDR;
}

int usart_getchar()
{

    while (!(UCSRA & 0x01));

return (UDR); 
}


