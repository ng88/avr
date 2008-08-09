/* 
 *  Author: Nicolas GUILLAUME <ng@ngsoft-fr.com>
 */

#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include <serial/serial.h>
#include <lcutil/delay.h>
#include <lcutil/assert.h>
#include <lcutil/cbuffer.h>


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

    dbg_printf("Initialisation...\n"); 

    dbg_printf("Bienvenue !\n"); 

    while(1)
    {
      
	/*
	int c;
	while( (c = kb_getscancode()) != EOB )
	{
	    printf("SCANCODE=%X\n", (char)c);
	}
	*/

	char k = kb_getchar();
	//printf("KEY = %c %d %X\n", k, k ,k);
	putchar(k);


    }
    return 0;
}


