#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

/**
 *
 *  Jeu du fil de fer
 *
 *
 *  @author: Nicolas GUILLAUME <nicolas@guillaume-fr.net> 2008 - 2009
 *
 */

/** Port utilisé pour le LED et le buzzer
 */
#define LB_PORT PORTC
#define LB_DDR  DDRC

/** Pin du buzzer
 */
#define LB_BUZZER PC4

/** Nombre de leds d'affichage
 */
#define LB_LED_COUNT 3
#define LB_LED_DELAY 70

/** Leds allumées lors d'un contact
 */
static char leds[LB_LED_COUNT] = { PC0, PC1, PC2 };




int main(void)
{
    int i, k;

    /* Initialisation des ports
     */

    LB_DDR |= _BV(LB_BUZZER);

    for(i = 0; i < LB_LED_COUNT; i++)
	LB_DDR |= _BV(leds[i]);

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
