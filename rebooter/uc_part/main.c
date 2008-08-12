/* 
 *  Author: Nicolas GUILLAUME <ng@ngsoft-fr.com>
 */

#include <avr/pgmspace.h>

#include <lcutil/delay.h>


int main()
{
    DDRD = 0x00;
    DDRD |= _BV(PD4) | _BV(PD5);


    while(1)
    {
    
	PORTD |= (1 << PD4) | (1 << PD5);

	delay_ms(1000);
	PORTD &= ~(1 << PD4) & ~(1 << PD5);

	delay_ms(3000);
    }


    return 0;
}


