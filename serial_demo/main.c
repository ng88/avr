/* 
 *  Author: Nicolas GUILLAUME <ng@ngosft-fr.com>
 */

#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <serial/serial.h>
#include <lcutil/delay.h>


int main()
{
	uart_init(1);
	putc('\n', stdout);
	puts("Hello World!");
	return 0;
}


