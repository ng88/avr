#include "serial.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#define UART_BAUD_CALC(UART_BAUD_RATE,F_OSC) ((F_OSC)/((UART_BAUD_RATE)*16l)-1)

static FILE uart_stdout = FDEV_SETUP_STREAM(&uart_putchar, NULL, _FDEV_SETUP_WRITE);

int uart_putchar(char c, FILE * stream)
{
    if(c == '\n')
        uart_putchar('\r', stream);
    loop_until_bit_is_set(UCSRA, UDRE);
    UDR = c;
    return 0;
}

void uart_init()
{
    // Qet baud rate
    UBRRH = (uint8_t)(UART_BAUD_CALC(UART_BAUD_RATE,F_OSC)>>8);
    UBRRL = (uint8_t)UART_BAUD_CALC(UART_BAUD_RATE,F_OSC);
    
    // Enable receiver and transmitter; enable RX interrupt
    UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);
    
    // Asynchronous 8N1
    UCSRC = (1 << URSEL) | (3 << UCSZ0);

    stderr = stdout = &uart_stdout;
}

// INTERRUPT can be interrupted
// SIGNAL can't be interrupted
SIGNAL (SIG_UART_RECV) { // USART RX interrupt
	unsigned char c;
	c = UDR;
	uart_putchar(c, 0);
}



