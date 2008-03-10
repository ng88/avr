

#define  F_CPU 3686400
#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "lcd.h"




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
