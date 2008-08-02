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
	usart_init(1);
	kb_init();

	//GIMSK |= 0x40;
	sei();
	
	putchar('\n');
	char a = usart_getchar();

	// enable  PD5 as output
	DDRD |= _BV(PD5);
	DDRD |= _BV(PD7);
	while (1) {
		// PIN5 PORTD clear -> LED off
		PORTD &= ~_BV(PD5);

		delay_ms(500);
		// PIN5 PORTD set -> LED on
		PORTD |= _BV(PD5);

		delay_ms(500);
		putchar(a++);
		if(a > 'z') a = 'a';
		//kb_getchar();
	}
	return 0;
}


