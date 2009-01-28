

#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include <buzzer/buzzer.h>

#define N_TEMPO 250.00

#define P_COUNT 44

static note_t note_acdll[P_COUNT] = 
{
    N_DO_3/2,
    N_DO_3/2,
    N_DO_3/2,
    N_RE_3,

    N_MI_3,
    N_RE_3,

    N_DO_3/2,
    N_MI_3,
    N_RE_3,
    N_RE_3,

    N_DO_3/2,

    N_DO_3/2,
    N_DO_3/2,
    N_DO_3/2,
    N_RE_3,

    N_MI_3,
    N_RE_3,

    N_DO_3/2,
    N_MI_3,
    N_RE_3,
    N_RE_3,

    N_DO_3/2.0,

    N_RE_3,
    N_RE_3,
    N_RE_3,
    N_RE_3,

    N_LA_3/2,
    N_LA_3/2,

    N_RE_3,
    N_DO_3/2,
    N_LA_3/2,
    N_SI_3/2,

    N_SOL_3/2,

    N_DO_3/2,
    N_DO_3/2,
    N_DO_3/2,
    N_RE_3,

    N_MI_3,
    N_RE_3,

    N_DO_3/2,
    N_MI_3,
    N_RE_3,
    N_RE_3,

    N_DO_3/2,
};
static note_len_t len_acdll[P_COUNT] = 
{
    N_CROCHE,
    N_CROCHE,
    N_CROCHE,
    N_CROCHE,

    N_NOIRE,
    N_NOIRE,

    N_CROCHE,
    N_CROCHE,
    N_CROCHE,
    N_CROCHE,

    N_BLANCHE,

    N_CROCHE,
    N_CROCHE,
    N_CROCHE,
    N_CROCHE,

    N_NOIRE,
    N_NOIRE,

    N_CROCHE,
    N_CROCHE,
    N_CROCHE,
    N_CROCHE,

    N_BLANCHE,

    N_CROCHE,
    N_CROCHE,
    N_CROCHE,
    N_CROCHE,

    N_NOIRE,
    N_NOIRE,

    N_CROCHE,
    N_CROCHE,
    N_CROCHE,
    N_CROCHE,

    N_BLANCHE,

    N_CROCHE,
    N_CROCHE,
    N_CROCHE,
    N_CROCHE,

    N_NOIRE,
    N_NOIRE,

    N_CROCHE,
    N_CROCHE,
    N_CROCHE,
    N_CROCHE,

    N_BLANCHE,
};





int main(void)
{
    DDRC|= _BV(PC0) | _BV(PC1) | _BV(PC2) | _BV(PC3);

    while(1)
    {
	bz_play(note_acdll, len_acdll, P_COUNT, N_TEMPO);
	_delay_ms(1000);
    }

    return 0;

}

