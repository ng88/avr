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
   
enum
{
    KEY_UP       = 0xf0,
    KEY_LSHIFT   = 0x12,
    KEY_RSHIFT   = 0x59,
    KEY_LALT     = 0x11,
    KEY_RALT     = 0x11, /* extended */
    KEY_LCTRL    = 0x14,
    KEY_RCTRL    = 0x14, /* extended */

};
    sei();

    dbg_printf("\n\nInitialisation...\n"); 

    dbg_printf("Bienvenue !\n"); 

    int c;
    while(1)
    {
       /*
        PORTD |= _BV(PD5);
	delay_ms(100);
	PORTD &= ~_BV(PD5);
	
	delay_ms(1300);

	
	while( (c = kb_getscancode()) != EOB )
	{
	    printf("SCANCODE=%X %d\n", (char)c, (char)c == (char)KEY_UP);
	}
	*/

	char k = kb_getchar();
	printf("KEY = %c %d %X\n", k, k ,k);

    }
    return 0;
}


