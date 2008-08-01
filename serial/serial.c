#include "serial.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#define UART_BAUD_CALC(UART_BAUD_RATE,F_OSC) ((F_OSC)/((UART_BAUD_RATE)*16l)-1)

void uart_delay_ms(unsigned short ms) {
	unsigned short outer1, outer2;
	outer1 = 200; 
	while (outer1) {
		outer2 = 1000;
		while (outer2) {
			while ( ms ) ms--;
			outer2--;
		}
		outer1--;
	}
}

void uart_putc(unsigned char c) {
   // wait until UDR ready
	while(!(UCSRA & (1 << UDRE)));
	UDR = c;    // send character
}

void uart_puts (char *s) {
	//  loop until *s != NULL
	while (*s) {
		uart_putc(*s);
		s++;
	}
}

void uart_init() {
	// set baud rate
	UBRRH = (uint8_t)(UART_BAUD_CALC(UART_BAUD_RATE,F_OSC)>>8);
	UBRRL = (uint8_t)UART_BAUD_CALC(UART_BAUD_RATE,F_OSC);

	// Enable receiver and transmitter; enable RX interrupt
	UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);

	//asynchronous 8N1
	UCSRC = (1 << URSEL) | (3 << UCSZ0);
}

// INTERRUPT can be interrupted
// SIGNAL can't be interrupted
SIGNAL (SIG_UART_RECV) { // USART RX interrupt
	unsigned char c;
	c = UDR;
	uart_putc(c);
}



