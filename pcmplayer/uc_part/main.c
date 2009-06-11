/* 
 *  Author: Nicolas GUILLAUME <ng@ngsoft-fr.com>
 */

#include <avr/pgmspace.h>

#include <util/delay.h>
#include <serial/serial.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>


#include <lcutil/cbuffer.h>

#include <stdlib.h>
#include "iocompat.h"

/** internal buffer of buff is volatile*/
static cbuffer_t buff;

ISR(TIMER1_OVF_vect)
{
    static int last = 0;   

    int r = cb_read(&buff);

    if(r == EOB)
	r = last;
    

	OCR = (uint16_t)r; /* 16 bit assignment is not a problem here,
			  because we're in an interrupt handler */
}


int main()
{
    int i;

    usart_init(1);

    /* Timer 1: Fast PWM, 8-bit  p98 */
    TCCR1A = _BV(WGM10) | _BV(WGM12) | _BV(COM1A1);//TIMER1_PWM_INIT;

    /*
     * Start timer 1.
     *
     * NB: TCCR1A and TCCR1B could actually be the same register, so
     * take care to not clobber it.
     */
    TCCR1B |= _BV(CS10);//TIMER1_CLOCKSOURCE;
    /*
     * Run any device-dependent timer 1 setup hook if present.
     */
    /* Set PWM value to 0. */
    OCR = 0;

    /* Enable OC1 as output. */
    DDROC = _BV (OC1);

    /* Enable timer 1 overflow interrupt. */
    TIMSK = _BV (TOIE1);
    sei();


    fputs("[PAPL_READY]", stdout);

    unsigned char sreg; 
    char c, wsuccess;

    while(1)
    {

	c = usart_getbyte();

	do
	{
	    sreg = SREG;
	    cli();
	    
	    wsuccess = cb_write(&buff, c);

	    SREG = sreg;

	    if(!wsuccess)
		putchar('!');	
	}
	while(!wsuccess);

    }

    return 0;
}



