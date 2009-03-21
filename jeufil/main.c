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
 *
 *  Configuration par défaut (cf local_pin_config.h) :
 *
 *  Leds : PORTC PC0, PC1, PC2, PC3, PC4
 *  Buzzer : PORTD PD4
 *  Fil de fer : PORTD PD2
 *
 */

/** Nombre de leds d'affichage
 */
#define LB_LED_COUNT 3
#define LB_LED_DELAY 150

/** Leds allumées lors d'un contact
 */
static int leds[LB_LED_COUNT] = { PC0, PC1, PC2 };
static int leds_total = 0;

/** Nombre de maladresses
 */
static int nbhit = 0;

/** Son joué lors d'un contact
 */
#define PART_CONTACT_COUNT 2
static  note_t note_contact[PART_CONTACT_COUNT] =
{
    N_LA_3, N_DO_3,
};
static note_len_t note_len_contact[PART_CONTACT_COUNT] =
{
    N_BLANCHE, N_BLANCHE,
};


#define N_TEMPO 200.00

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
    if(nbhit <= LB_LED_COUNT)
    {
	bz_play(note_contact, note_len_contact, PART_CONTACT_COUNT, N_TEMPO);
	for(k = 0; k <= 5; k++)
	{
	    LB_PORT |= _BV(leds[nbhit]);
	    _delay_ms(LB_LED_DELAY);
	    LB_PORT &= ~_BV(leds[nbhit]); 
	    _delay_ms(LB_LED_DELAY);
	}
	LB_PORT |= _BV(leds[nbhit]);
	nbhit++;
    }

    if(nbhit == LB_LED_COUNT)
    {
	/* Partie finie, clignotement infini */
	while(1)
	{
	    PORTC &= ~leds_total;
	    _delay_ms(LB_LED_DELAY);
	    LB_PORT |= leds_total;
	    _delay_ms(LB_LED_DELAY);
	}
    }
    sei();
}


int main()
{
    int i, k;

    /* Initialisation des ports puis des interruptions
     */
    
    leds_total = 0;
    for(i = 0; i < LB_LED_COUNT; i++)
	leds_total |= _BV(leds[i]);

    LB_DDR |= leds_total;
    BZ_DDR |= _BV(BZ_PIN);

    /*MCUCR |= ISC0_FALLING_EDGE;
    GIMSK |= _BV(INT0);
GICR|=0xE0;
MCUCR=0x0A;
MCUCSR=0x00;
GIFR=0xE0; */
  MCUCR |=0x0f; // front montant
  GICR  = 0x80; // INT1 enable

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
	
	for(i = LB_LED_COUNT - 2; i >= 0; i--)
	{
	    LB_PORT |= _BV(leds[i]);
	    _delay_ms(LB_LED_DELAY);
	    PORTC &= ~_BV(leds[i]);
	}
    }

    sei();

    while(1);

    return 0;

}

