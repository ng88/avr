#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "local_pin_config.h"
#include <buzzer.h>


void bz_beep(double freq, double len_ms)
{
    double d;
    int k, n;

    n =  (int)(freq * len_ms / 1000.00);
    d = len_ms / (2.0 * n);

    for(k = 0; k < n; k++)
    {
	BZ_PORT |= _BV(BZ_PIN);
	_delay_ms(d);
	BZ_PORT &= ~_BV(BZ_PIN);
	_delay_ms(d);
    }
}

void bz_play(unsigned short int ** part, int size, double  tempo)
{
    int i;
    for(i = 0; i < size; i++)
    {
	bz_beep((double)part[i][0], (double)part[i][1] * tempo);
	_delay_ms(tempo / 5.0);
    }
}
