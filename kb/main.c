/* 
 *  Author: Nicolas GUILLAUME <ng@ngosft-fr.com>
 */

#define  F_CPU 3686400
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "kb.h"
#include "serial.h"


int main(void) {
	uart_init(); // init USART
	sei();  // enable interrupts
	
	// send initial character
	while(!(UCSRA & (1 << UDRE)));
	UDR = 0x43; // "C"
	while(!(UCSRA & (1 << UDRE)));
	UDR = 0x0d;

	// enable  PD5 as output
	DDRD |= (1<<PD5);
	while (1) {
		// PIN5 PORTD clear -> LED off
		PORTD &= ~(1 << PD5);
		uart_delay_ms(500);
		// PIN5 PORTD set -> LED on
		PORTD |= (1 << PD5);
		uart_delay_ms(500);	
	}
	return 0;
}


