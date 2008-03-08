#define  F_CPU 3686400
#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "lcd.h"

unsigned char ball;

void mydelay(unsigned char v)
{
	unsigned char j;
	unsigned int i;
	for (j=0;j<v;j++) for (i=0;i<2000;i++) asm volatile ("nop"::);
}



void process()
{
    static unsigned char count = 0;

    ball = bit_is_set(PINC, PC4) ? '*' : '+';

    count++;

    switch(count)
    {
    case 3:
	PORTC |= _BV(PC0);
	_delay_ms(70);
	PORTC &= ~_BV(PC0);
	break;
    case 12:
	count = 0;
    case 6:
	PORTC |= _BV(PC1);
	_delay_ms(70);
	PORTC &= ~_BV(PC1);
	break;
    case 9:
	PORTC |= _BV(PC2);
	_delay_ms(70);
	PORTC &= ~_BV(PC2);
	break;
    default:
	_delay_ms(70);
    }

    mydelay(70);
}



int main(void)
{
    register unsigned char i;

    ball = '*';

    DDRC|= _BV(PC0);
    DDRC|= _BV(PC1);
    DDRC|= _BV(PC2);

    DDRC&= ~_BV(PC4);
    PORTC|= _BV(PC4);

    DDRC&= ~_BV(PC5);
    PORTC|= _BV(PC5);

    lcd_init(LCD_DISP_ON);


	lcd_clrscr();
	lcd_puts("Processing...\n[");
	lcd_putc(ball);
	lcd_gotoxy(15, 1);
	lcd_putc(']');

	while(bit_is_set(PINC, PC5))
	{

	
	    for(i = 2; i <= 14; i++)
	    {
		lcd_gotoxy(i - 1, 1);
		lcd_putc(' ');
		lcd_putc(ball);

		process();
	    }

	    for(i = 13; i >= 1; i--)
	    {
		lcd_gotoxy(i, 1);
		lcd_putc(ball);
		lcd_putc(' ');
		
		process();
	    }
	    
	    
	}
	
	lcd_clrscr();
	lcd_puts("Terminated.");


    return 0;

}
