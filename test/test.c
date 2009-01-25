#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>


#define L_ON  (0xFF)
#define L_OFF (0x00)

#define MAP_COUNT 9
#define LED_COUNT 3
#define BLINK_P 15

#define set_leds(a, b, c) (PORTC = ((a) & _BV(PC0)) | ((b) & _BV(PC1)) | ((c) & _BV(PC2)))

/*
static char lmap[MAP_COUNT][LED_COUNT] = 
        {
	    {L_OFF, L_OFF, L_OFF},
	    {L_OFF, L_OFF, L_ON },
	    {L_OFF, L_ON , L_ON },
	    {L_OFF, L_ON , L_OFF},
	    {L_ON , L_ON , L_OFF},
	    {L_ON , L_ON , L_ON },
	    {L_ON , L_OFF, L_ON },
	    {L_ON , L_OFF, L_OFF},
	    {L_OFF, L_OFF, L_OFF},
	};
*/

int main(void)
{
    int k, i;

    DDRC|= _BV(PC0) | _BV(PC1) | _BV(PC2) | _BV(PC3);

    while(1)
    {
	for(k = 0; k < 1000; k++)
	{
	     PORTC |= _BV(PC3);
	    _delay_ms(1);
	    PORTC &= ~_BV(PC3);
	    _delay_ms(1);
	    }

	PORTC |= _BV(PC0);
	for(i = 0; i < 5; i++)
	    _delay_ms(100);

	PORTC &= ~_BV(PC0);
    }
/*

    while(1)
    {
	for(k = 0; k < MAP_COUNT - 1; k++)
	{
	    for(i = 0; i < BLINK_P; i++)
	    {
		set_leds(lmap[k][0], lmap[k][1], lmap[k][2]);
		_delay_ms(BLINK_P - i);
		set_leds(lmap[k + 1][0], lmap[k + 1][1], lmap[k + 1][2]);
		_delay_ms(i);
	    }

	    for(i = 0; i < 5; i++)
		_delay_ms(100);
	}
    }
*/
    return 0;

}
