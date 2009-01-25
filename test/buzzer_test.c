

#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include <buzzer/buzzer.h>

#define N_TEMPO 250.00

#define P_COUNT 44

static unsigned short int part_acdll[P_COUNT][2] = 
{
    {N_DO_3/2, N_CROCHE},
    {N_DO_3/2, N_CROCHE},
    {N_DO_3/2, N_CROCHE},
    {N_RE_3, N_CROCHE},

    {N_MI_3, N_NOIRE},
    {N_RE_3, N_NOIRE},

    {N_DO_3/2, N_CROCHE},
    {N_MI_3, N_CROCHE},
    {N_RE_3, N_CROCHE},
    {N_RE_3, N_CROCHE},

    {N_DO_3/2, N_BLANCHE},

    {N_DO_3/2, N_CROCHE},
    {N_DO_3/2, N_CROCHE},
    {N_DO_3/2, N_CROCHE},
    {N_RE_3, N_CROCHE},

    {N_MI_3, N_NOIRE},
    {N_RE_3, N_NOIRE},

    {N_DO_3/2, N_CROCHE},
    {N_MI_3, N_CROCHE},
    {N_RE_3, N_CROCHE},
    {N_RE_3, N_CROCHE},

    {N_DO_3/2.0, N_BLANCHE},

    {N_RE_3, N_CROCHE},
    {N_RE_3, N_CROCHE},
    {N_RE_3, N_CROCHE},
    {N_RE_3, N_CROCHE},

    {N_LA_3/2, N_NOIRE},
    {N_LA_3/2, N_NOIRE},

    {N_RE_3, N_CROCHE},
    {N_DO_3/2, N_CROCHE},
    {N_LA_3/2, N_CROCHE},
    {N_SI_3/2, N_CROCHE},

    {N_SOL_3/2, N_BLANCHE},

    {N_DO_3/2, N_CROCHE},
    {N_DO_3/2, N_CROCHE},
    {N_DO_3/2, N_CROCHE},
    {N_RE_3, N_CROCHE},

    {N_MI_3, N_NOIRE},
    {N_RE_3, N_NOIRE},

    {N_DO_3/2, N_CROCHE},
    {N_MI_3, N_CROCHE},
    {N_RE_3, N_CROCHE},
    {N_RE_3, N_CROCHE},

    {N_DO_3/2, N_BLANCHE},
};

int main(void)
{
    DDRC|= _BV(PC0) | _BV(PC1) | _BV(PC2) | _BV(PC3);

    while(1)
    {
	bz_play(part_acdll, P_COUNT, N_TEMPO);

	_delay_ms(1000);
    }

    return 0;

}

