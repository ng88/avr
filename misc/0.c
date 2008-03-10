

#define  F_CPU 3686400
#include <avr/io.h>
#include <util/delay.h>


#define FDS 60
int main()
{
    /* INITIALIZE */

    DDRB|= _BV(PB0);
    DDRB|= _BV(PB1);
    DDRB|= _BV(PB2);

    int i = FDS;

    while(1)
    {
	
	PORTB|= _BV(PB0);
	_delay_ms(i);
	PORTB &= ~_BV(PB0);
	_delay_ms(i);
       

	PORTB|= _BV(PB1);
	_delay_ms(i);
	PORTB &= ~_BV(PB1);
	_delay_ms(i);
	

	PORTB|= _BV(PB2);
	_delay_ms(i);
	PORTB &= ~_BV(PB2);
	_delay_ms(i);

	PORTB|= _BV(PB1);
	_delay_ms(i);
	PORTB &= ~_BV(PB1);
	_delay_ms(i);	

    }
}

