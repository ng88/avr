/* 
 *  Author: Nicolas GUILLAUME <ng@ngosft-fr.com>
 */

#define  F_CPU 3686400
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "kb.h"
#include "serial.h"


int main()
{
	uart_init(); // init USART
	kb_init();
	GIMSK |= 0x40;
	sei();  // enable interrupts
	
	// send initial character
	while(!(UCSRA & (1 << UDRE)));
	UDR = 0x43; // "C"
	while(!(UCSRA & (1 << UDRE)));
	UDR = 0x0d;

	uart_puts("salut \n\r");

	char a = 'a';
	// enable  PD5 as output
	DDRD |= (1<<PD5);
	DDRD |= (1<<PD7);
	while (1) {
		// PIN5 PORTD clear -> LED off
		PORTD &= ~(1 << PD5);

		uart_delay_ms(500);
		// PIN5 PORTD set -> LED on
		PORTD |= (1 << PD5);

		uart_delay_ms(500);
		uart_putc(a++);
		if(a > 'z') a = 'a';
		//kb_getchar();
	}
	return 0;
}


