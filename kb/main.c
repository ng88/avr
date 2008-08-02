/* 
 *  Author: Nicolas GUILLAUME <ng@ngosft-fr.com>
 */

#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include <serial/serial.h>
#include <lcutil/delay.h>
#include <lcutil/assert.h>

#include "kb.h"


int main()
{
	uart_init();
	kb_init();

	GIMSK |= 0x40;
	sei();
	

	char a = 'a';

	// enable  PD5 as output
	DDRD |= (1<<PD5);
	DDRD |= (1<<PD7);
	while (1) {
		// PIN5 PORTD clear -> LED off
		PORTD &= ~(1 << PD5);

		delay_ms(500);
		// PIN5 PORTD set -> LED on
		PORTD |= (1 << PD5);

		delay_ms(500);
		uart_putchar(a++, 0);
		if(a > 'z') a = 'a';
		//kb_getchar();
	}
	return 0;
}


