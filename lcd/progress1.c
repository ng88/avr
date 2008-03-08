/*************************************************************************
Title:    testing output to a HD44780 based LCD display.
Author:   Peter Fleury  <pfleury@gmx.ch>  http://jump.to/fleury
Date:     December 2002
Software: AVR-GCC 3.3
Hardware: HD44780 compatible LCD text display
          ATS90S8515/ATmega if memory-mapped LCD interface is used
          any AVR with 7 free I/O pins if 4-bit IO port mode is used
**************************************************************************/
// modified to test extensions 
// by Martin Thomas, 3/2003

#define  F_CPU 3686400
#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "lcd.h"


/*
** constant definitions
*/


/*
** function prototypes
*/ 


void mydelay(unsigned char v)
{
	unsigned char j;
	unsigned int i;
	for (j=0;j<v;j++) for (i=0;i<2000;i++) asm volatile ("nop"::);
}






int main(void)
{
    register unsigned char i;
    lcd_init(LCD_DISP_ON);


    while(1)
    {
	lcd_clrscr();
	lcd_puts("-- Welcome! --");
	mydelay(200);
	mydelay(200);

	lcd_clrscr();
	lcd_puts("Processing...\n[");

	lcd_gotoxy(15, 1);
	lcd_putc(']');

	for(i = 1; i <= 14; ++i)
	{
	    lcd_gotoxy(i, 1);
	    lcd_putc('=');

	    if(i < 14)
		lcd_putc('>');

	    mydelay(100 + rand() % 100);
	}

	lcd_clrscr();
	lcd_puts("-- Launched ---");
	mydelay(200);
	mydelay(200);

    }

    return 0;

}
