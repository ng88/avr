/* 
 *  Author: Nicolas GUILLAUME <ng@ngsoft-fr.com>
 */

#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <serial/serial.h>
#include <lcutil/delay.h>


int main()
{
    _delay_ms(100);
    usart_init(1);
    putc('\n', stdout);
    puts("Test starts!\n");
    char c;    
    while( (c = getchar() ))
    {
	putchar(c);
    }
    puts("Test ends.\n");
    while(1);
    return 0;
}


