
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

    int i;
    char sens;

    for(i = 0; i < 10; ++i)
    {
	PORTB|= _BV(PB0);
	_delay_ms(i);
	PORTB &= ~_BV(PB0);
	_delay_ms(i);
    }


    for(i = 0; i < 10; ++i)
    {
	PORTB|= _BV(PB1);
	_delay_ms(i);
	PORTB &= ~_BV(PB1);
	_delay_ms(i);
    }

    sens = 1;
    i = FDS;

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

	if(sens)
	{
	    i++;
	    if(i >= 240)
		sens = 0;
	}
	else
	{
	    i--;
	    if(i <= FDS)
		sens = 1;
	}	

    }
}

