

#define  F_CPU 3686400
#include <avr/io.h>
#include <util/delay.h>


#define FDS 60
int main()
{
    /* INITIALIZE */

    int i;
    i=0;
    DDRD|= _BV(PD2);
    DDRD|= _BV(PD3);
    DDRD|= _BV(PD4);    
    DDRD|= _BV(PD5);
    DDRD|= _BV(PD6);
    DDRD|= _BV(PD7);

    PORTD|= _BV(PD2);
    _delay_ms(5);

    while(1)
    {
	
	PORTD|= _BV(PD3);
	_delay_ms(1);


	if(i % 5) PORTD|= _BV(PD4); else PORTD&= _BV(PD4);
	if(i % 7) PORTD|= _BV(PD5); else PORTD&= _BV(PD5);
	if(i % 3) PORTD|= _BV(PD6); else PORTD&= _BV(PD6);
	if(i % 8) PORTD|= _BV(PD7); else PORTD&= _BV(PD7);

	
    }
}

