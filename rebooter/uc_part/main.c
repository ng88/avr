/* 
 *  Author: Nicolas GUILLAUME <ng@ngsoft-fr.com>
 */

#include <avr/pgmspace.h>

#include <util/delay.h>
#include <serial/serial.h>

#define PIN_LED PD7

/** Declaration des relais
 */

#define RELAY_COUNT 2

static unsigned char relay_pin[RELAY_COUNT] = 
                 {
		     PD5, PD7
		 };

static char * relay_desc[RELAY_COUNT] = 
                 {
		     "not connected",
		     "24VDC / 120VAC",
		 };

static unsigned int reset_delay = 300;

#define IS_EOL(c) (c == '\r' || c == '\n')

void parse_cmd();
void help();
void serror();
void rerror(unsigned int i)
unsigned int uint_arg();

int main()
{
    int i;

    usart_init(1);

    DDRD = 0x00;
    DDRD |= _BV(PIN_LED);

    for(i = 0; i < RELAY_COUNT; i++)
	DDRD |= _BV(relay_pin[i]);
   
    _delay_ms(10);

    puts("\n\n==== REBOOTER v1 ====\n");


    /* show off */
/*    int i;
    for(i = 1; i <= 5; i++)
    {
	PORTD |= _BV(PIN_LED);
	_delay_ms(50);
	PORTD &= ~_BV(PIN_LED);
	_delay_ms(150);
    }

    PORTD |= _BV(PIN_RL);
    _delay_ms(200);
    PORTD &= ~_BV(PIN_RL);
    _delay_ms(200);
*/
 

    while(1)
    {
	fputs(">: ", stdout);
	parse_cmd();
    }


    return 0;
}


void parse_cmd()
{
    unsigned int i;
    char cmd;
    char arg;

    cmd = getchar();
    arg = getchar();

    switch(cmd)
    {
    case '?':
    case 'h':
	if(IS_EOL(arg))
	{
	    help();
	    return;
	}
	break;
    case 'l':
	if(IS_EOL(arg))
	{
	    puts("ID\tPIN\tSTATE\tDESCR");
	    for(i = 0; i < RELAY_COUNT; i++)
		printf("%d\t%d\t%d\t%s\n", i, relay_pin[i], 0, relay_desc[i]);
	    return;
	}
	break;
    case 'd':
	if(IS_EOL(arg))
	    printf("delay=%u\n", reset_delay);
	else
	    reset_delay = uint_arg();
	return;
    case 'p':
	if(!IS_EOL(arg))
	{
	    i = uint_arg();
	    if(i < RELAY_COUNT)   
		PORTD |= _BV((unsigned char)i);
	    else
		rerror(i);
	    return;
	}
	break;
    case 'r':
	if(!IS_EOL(arg))
	{
	    i = uint_arg();
	    if(i < RELAY_COUNT)   
		PORTD &= ~_BV((unsigned char)i);
	    else
		rerror(i);
	    return;
	}
	break;
    case 't':
	if(!IS_EOL(arg))
	{
	    i = uint_arg();
	    if(i < RELAY_COUNT)
	    {   
		PORTD |= _BV((unsigned char)i);
		_delay_ms(reset_delay);
		PORTD &= ~_BV((unsigned char)i);
	    }
	    else
		rerror(i);
	    return;
	}
	break;
    }

    serror();
}


void help()
{
    puts("h or ? help\n"
	 "l      lists available relays\n"
	 "p i    pushes relay i\n"
	 "r i    releases relay i\n"
	 "t i    make a reset with relay i\n"
	 "d      show reset delay\n"
	 "d t    set reset delay to t ms\n"
	);
}

void serror()
{
    puts("bad command, type 'h' for help");
}

void rerror(unsigned int i)
{
    printf("unknown relay `%u'\n", i);
}

unsigned int uint_arg()
{
    return 0;
}
