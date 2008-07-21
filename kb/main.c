#define  F_CPU 3686400
#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include <lcd/lcd.h>
#include <util/delay.h>

static inline void show_key(char k)
{
    lcd_clrscr();
    lcd_puts("Key pressed:\n");
    lcd_putc(k);
}



int main(void)
{
 
    DDRC|= _BV(PC0);
    DDRC|= _BV(PC1);
    DDRC|= _BV(PC2);

    DDRC&= ~_BV(PC4);
    PORTC|= _BV(PC4);

    DDRC&= ~_BV(PC5);
    PORTC|= _BV(PC5);

    lcd_init(LCD_DISP_ON);

    int i;
    while(1)
    {
	for(i = 0; i < 256; ++i)
	{
	    show_key(i);
	    delay_ms(500);
	}
    }

    return 0;

}
