/* 
 *  Author: Nicolas GUILLAUME <ng@ngsoft-fr.com>
 */

#include <avr/pgmspace.h>

#include <util/delay.h>
#include <serial/serial.h>

#include <stdlib.h>

/** Declaration des relais
 */

#define RELAY_COUNT 5

static unsigned char relay_pin[RELAY_COUNT] = 
                 {
		     PD3, PD4, PD5, PD6, PD7
		 };

static char * relay_desc[RELAY_COUNT] = 
                 {
		     "not connected",
		     "24VDC / 120VAC",
		     "GREEN LED",
		     "ORANGE LED",
		     "RED LED",
		 };

static unsigned int reset_delay = 300;

#define IS_EOL(c) (c == '\r' || c == '\n')

void parse_cmd();
void help();
void version();
void rerror(int i);
char * mfgets(char *str, int size, FILE *stream);


int main()
{
    int i;

    usart_init(1);

    DDRD = 0x00;

    for(i = 0; i < RELAY_COUNT; i++)
	DDRD |= _BV(relay_pin[i]);
   
    _delay_ms(10);

    puts("\n\n==== REBOOTER v1 ====\n");
 

    while(1)
    {
	fputs(">: ", stdout);
	parse_cmd();
    }


    return 0;
}


void parse_cmd()
{
    enum {LS = 16};
    unsigned int i;
    char * sok = NULL;
    int arg = -1;
    char ok = 0;
    char line[LS];

    if(!mfgets(line, LS, stdin))
	return;

    if(!line[0] || IS_EOL(line[0]))
	return;

    if(line[1] == ' ')
    {
	arg = strtol(line + 2, &sok, 10);	
	if(!sok || (sok && IS_EOL(*sok)))
	    ok = 1;
    }

    switch(line[0])
    {
    case '?':
    case 'h':
	help();
	return;
    case 'v':
	version();
	return;
    case 'l':
	puts("ID\tPIN\tSTATE\tDESCR");
	for(i = 0; i < RELAY_COUNT; i++)
	    printf("%d\t%d\t%d\t%s\n", i, relay_pin[i], (bit_is_set(PIND, relay_pin[i]) ? 1 : 0), relay_desc[i]);
	return;
    case 'd':
	if(ok)
	{
	    if(arg < 0)
		rerror(arg);
	    else
		reset_delay = arg;
	}
	else
	    printf("delay=%u\n", reset_delay);
	return;
    case 'p':
	if(ok)
	{
	    if(arg >= 0 && arg < RELAY_COUNT)   
		PORTD |= _BV((unsigned char)relay_pin[arg]);
	    else
		rerror(arg);
	    return;
	}
	break;
    case 'r':
	if(ok)
	{
	    if(arg >= 0 && arg < RELAY_COUNT)
		PORTD &= ~_BV((unsigned char)relay_pin[arg]);
	    else
		rerror(arg);
	    return;
	}
	break;
    case 't':
	if(ok)
	{
	    if(arg >= 0 && arg < RELAY_COUNT)
	    {   
		PORTD |= _BV((unsigned char)relay_pin[arg]);
		_delay_ms(reset_delay);
		PORTD &= ~_BV((unsigned char)relay_pin[arg]);
	    }
	    else
		rerror(arg);
	    return;
	}
	break;
    }

    puts("bad command, type 'h' for help");
}


void help()
{
    puts("h or ? help\n"
	 "v      version\n"
	 "l      lists available relays\n"
	 "p i    pushes relay i\n"
	 "r i    releases relay i\n"
	 "t i    make a reset with relay i\n"
	 "d      show reset delay\n"
	 "d t    set reset delay to t ms\n"
	 //"w i x  set a watchdog on i every  x ms\n"
	 //"w i 0  disable the watchdog on i\n"
	 //"n      reset watchdog timer\n"
	);
}

void version()
{
    puts("Copyright (c) Nicolas GUILLAUME 2007 - 2009 <nicolas@guillaume-fr.net>");
}


void rerror(int i)
{
    printf("invalid argument `%d'\n", i);
}

char * mfgets(char *str, int size, FILE *stream)
{
        char *cp;
        int c;

        if ((stream->flags & __SRD) == 0 || size <= 0)
                return NULL;

        size--;
        for (c = 0, cp = str; !IS_EOL(c) && size > 0; size--, cp++)
	{
                if ((c = getc(stream)) == EOF)
		{
                        stream->flags |= __SERR;
                        return NULL;
                }
                *cp = (char)c;
        }
        *cp = '\0';

        return str;
}
