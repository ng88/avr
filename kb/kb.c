/* Keyboard communication routines
 *  Author:  Nicolas GUILLAUME <ng@ngsoft-fr.com>
 */


#include "kb.h"
#include "scancodes.h"
#include <lcutil/delay.h>
#include <lcutil/cbuffer.h>


static cbuffer_t buff;

void kb_init(void)
{ 
    cb_init(&buff);
    MCUCR = ISC0_FALLING_EDGE;
}

ISR(INT0_vect)
{

    static unsigned char data = 0; /* holds the received scancode */
    static unsigned char bitcount = 11;
 
    /** 11 bits:
     *  Start (0)
     *  0..7 data byte  (Least significant bit first)
     *  Parity (odd)
     *  Stop (1)
     */
	
    if(bitcount > 2 && bitcount < 11)
    {             /* start and stop bits are ignored. */
	data = (data >> 1);
	if(bit_is_set(PIN_KB, DATAPIN))
	    data = data | 0x80; // store a 1
    }

    if(--bitcount == 0)  /* all bits received */
    {
	cb_write(&buff, data);	
	bitcount = 11;
	data = 0;
    }
}


int kb_getscancode()
{
    return cb_read(&buff);
}

int kb_decode_next_char()
{
    static unsigned char modifier = KM_NORMAL;
    char c = cb_readb(&buff);

    switch(c)
    {
    case (char)KEY_UP:
	c = cb_readb(&buff);
	if(c == (char)KEY_LSHIFT || c == (char)KEY_RSHIFT)
	    modifier = KM_NORMAL;
	break;
    case (char)KEY_EXTENDED_START:
	c = cb_readb(&buff);
	if(c == (char)KEY_UP)
	{
	    if(cb_readb(&buff) == (char)KEY_RALT)
		modifier = KM_NORMAL;
	}
	else
	{
	    if(c == (char)KEY_RALT)
		modifier = KM_ALTGRED;
	    else
		return scancode_ex_to_ascii(c, modifier);
	}
	break;
    case (char)KEY_PBRK_START:
	if(cb_readb(&buff) == (char)KEY_UP)
	    (void)cb_readb(&buff);
	(void)cb_readb(&buff);
	(void)cb_readb(&buff);
	break;
    default:
	if(c == (char)KEY_LSHIFT || c == (char)KEY_RSHIFT)
	    modifier = KM_SHIFTED;
	else if(c == (char)KEY_CAPS)
	    modifier = (modifier == KM_NORMAL) ? KM_SHIFTED : KM_NORMAL;
	else
	    return scancode_to_ascii(c, modifier);
    }

    /* no char yet */
    return EOB;
}

char kb_getchar()
{
    int c;
    while( (c = kb_decode_next_char()) == EOB );
    return (char)c;
}


