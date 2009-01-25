#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#define N_DO_3 262
#define N_DOD_3 277
#define N_RE_3 294
#define N_RED_3 311
#define N_MI_3 330
#define N_FA_3 349
#define N_FAD_3 370
#define N_SOL_3 392
#define N_SOLD_3 415
#define N_LA_3 440
#define N_LAD_3 466
#define N_SI_3 494

#define N_BLANCHE 4
#define N_NOIRE   2
#define N_RONDE   8
#define N_CROCHE  1

#define N_TEMPO 250.00

#define P_COUNT 44

static unsigned short int part[P_COUNT][2] = 
{
    {N_DO_3/2.0, N_CROCHE},
    {N_DO_3/2.0, N_CROCHE},
    {N_DO_3/2.0, N_CROCHE},
    {N_RE_3, N_CROCHE},

    {N_MI_3, N_NOIRE},
    {N_RE_3, N_NOIRE},

    {N_DO_3/2.0, N_CROCHE},
    {N_MI_3, N_CROCHE},
    {N_RE_3, N_CROCHE},
    {N_RE_3, N_CROCHE},

    {N_DO_3/2.0, N_BLANCHE},

    {N_DO_3/2.0, N_CROCHE},
    {N_DO_3/2.0, N_CROCHE},
    {N_DO_3/2.0, N_CROCHE},
    {N_RE_3, N_CROCHE},

    {N_MI_3, N_NOIRE},
    {N_RE_3, N_NOIRE},

    {N_DO_3/2.0, N_CROCHE},
    {N_MI_3, N_CROCHE},
    {N_RE_3, N_CROCHE},
    {N_RE_3, N_CROCHE},

    {N_DO_3/2.0, N_BLANCHE},

    {N_RE_3, N_CROCHE},
    {N_RE_3, N_CROCHE},
    {N_RE_3, N_CROCHE},
    {N_RE_3, N_CROCHE},

    {N_LA_3/2.0, N_NOIRE},
    {N_LA_3/2.0, N_NOIRE},

    {N_RE_3, N_CROCHE},
    {N_DO_3/2.0, N_CROCHE},
    {N_LA_3/2.0, N_CROCHE},
    {N_SI_3/2.0, N_CROCHE},

    {N_SOL_3/2.0, N_BLANCHE},

    {N_DO_3/2.0, N_CROCHE},
    {N_DO_3/2.0, N_CROCHE},
    {N_DO_3/2.0, N_CROCHE},
    {N_RE_3, N_CROCHE},

    {N_MI_3, N_NOIRE},
    {N_RE_3, N_NOIRE},

    {N_DO_3/2.0, N_CROCHE},
    {N_MI_3, N_CROCHE},
    {N_RE_3, N_CROCHE},
    {N_RE_3, N_CROCHE},

    {N_DO_3/2.0, N_BLANCHE},
};


#define rand_rg(a, b) ((a) + ((b) * (rand() / (RAND_MAX + 1.0))))

void mbeep(double freq, double len_ms)
{
    double d;
    int k, n;

    n =  (int)(freq * len_ms / 1000.00);
    d = len_ms / (2.0 * n);

    for(k = 0; k < n; k++)
    {
	PORTC |= _BV(PC3);
	_delay_ms(d);
	PORTC &= ~_BV(PC3);
	_delay_ms(d);
    }
}

int main(void)
{
    int k = 1, i;

    DDRC|= _BV(PC0) | _BV(PC1) | _BV(PC2) | _BV(PC3);

    while(1)
    {

	for(i = 0; i < P_COUNT; i++)
	{
	    PORTC |= _BV(PC0);  
	    mbeep((double)part[i][0], (double)part[i][1] * N_TEMPO);
	    PORTC &= ~_BV(PC0);
	    PORTC |= _BV(PC1);

	    _delay_ms(N_TEMPO / 5.0);
	    PORTC &= ~_BV(PC1);
	}

	_delay_ms(1000);
    }

    return 0;

}
