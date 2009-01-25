#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <buzzer/buzzer.h>

#include "local_pin_config.h"

#define ISC0_FALLING_EDGE 2
#define ISC0_RISING_EDGE 3

/**
 *
 *  Jeu du fil de fer
 *
 *
 *  @author: Nicolas GUILLAUME <nicolas@guillaume-fr.net> 2008 - 2009
 *
 */

/** Nombre de leds d'affichage
 */
#define LB_LED_COUNT 3
#define LB_LED_DELAY 70

/** Leds allumées lors d'un contact
 */
static int leds[LB_LED_COUNT] = { PC0, PC1, PC2 };
static int leds_total = 0;

/** Nombre de maladresses
 */
static int nbhit = 0;


/** Routine d'interruption déclenchée à chaque fois
 * quel le fil de fer est touché.
 */
ISR(INT0_vect)
{
    int k;
    /* On désactive les interruptions, cela permet une "invincibilité de quelques
     * temps apres un hit.
     */
    cli();
    if(nbhit < LB_LED_COUNT)
    {
	for(k = 0; k <= 5; k++)
	{
	    LB_PORT |= _BV(leds[nbhit]);
	    _delay_ms(LB_LED_DELAY);
	    LB_PORT &= ~_BV(leds[nbhit]); 
	}
	LB_PORT |= leds[nbhit];
	nbhit++;
    }

    if(nbhit == LB_LED_COUNT)
    {
	/* Partie finie */
	for(k = 0; k <= 5; k++)
	{
	    PORTC &= ~leds_total;
	    _delay_ms(LB_LED_DELAY);
	    LB_PORT |= leds_total;
	}
    }
    sei();
}

int main(void)
{
    int i, k;

    /* Initialisation des ports puis des interruptions
     */
    
    leds_total = 0;
    for(i = 0; i < LB_LED_COUNT; i++)
	leds_total |= _BV(leds[i]);

    LB_DDR = _BV(BZ_PIN) | leds_total;

    MCUCR = ISC0_RISING_EDGE;
    GIMSK = _BV(INT0);

    /* Bienvenue !
     */
    for(k = 1; k <= 2; k++)
    {
	for(i = 0; i < LB_LED_COUNT; i++)
	{
	    LB_PORT |= _BV(leds[i]);
	    _delay_ms(LB_LED_DELAY);
	    PORTC &= ~_BV(leds[i]);
	}

	for(i = LB_LED_DELAY - 2; i >= 0; i--)
	{
	    LB_PORT |= _BV(leds[i]);
	    _delay_ms(LB_LED_DELAY);
	    PORTC &= ~_BV(leds[i]);
	}
    }

    sei();
    while(1);

    /*while(1)
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
	}*/

    return 0;

}
