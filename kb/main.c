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
    DDRD |= _BV(PD5);
    DDRD |= _BV(PD7);

    usart_init(1);
    //kb_init();
    
    //GIMSK |= 0x40;
    sei();
    
    // enable  PD5 as output
  

    printf("Entrez des trucs > \n"); 

    while(1)
	printf("in=[%c]\n", usart_getchar());

    while (1)
    {
	// PIN5 PORTD clear -> LED off
	PORTD &= ~_BV(PD5);
	
	delay_ms(500);
	// PIN5 PORTD set -> LED on
	PORTD |= _BV(PD5);
	
	delay_ms(500);
    }
    return 0;
}


