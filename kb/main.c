/* 
 *  Author: Nicolas GUILLAUME <ng@ngosft-fr.com>
 */

#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include <serial/serial.h>
#include <lcutil/delay.h>
#include <lcutil/assert.h>

#include "kb.h"


int main()
{
    DDRD = 0x00;
    DDRD |= _BV(PD5);
    DDRD |= _BV(PD7);
    GIMSK = 0x00;
    GIMSK  |= _BV(INT0);
 
    usart_init(1);
    kb_init();
   

    sei();

    dbg_printf("\n\nInitialisation...\n"); 

    dbg_printf("Bienvenue !\n"); 

    //int a = kb_getchar();
    //dbg_printf("Touche pressée %c / %d\n", a, a); 

    while (1)
    {
	PORTD |= _BV(PD5);
	delay_ms(100);
	PORTD &= ~_BV(PD5);
	
	delay_ms(1300);
    }
    return 0;
}


