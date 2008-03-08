
#define  F_CPU 3686400
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"


SIGNAL(SIG_OVERFLOW0)
{
   
   static volatile unsigned char count = 0;
   static volatile unsigned short tot = 0;

   count ++;

   if(count >= 50)
   {
       tot++;
       count = 0;

       char buffer[5];
       lcd_gotoxy(0, 0);
       itoa(tot, buffer, 10);
       lcd_puts(buffer);

      if(bit_is_set(PORTC, PC0))
	   PORTC &= ~_BV(PC0);
      else
	   PORTC|= _BV(PC0);

   }

}
 
int main (void)
{
 
    DDRC = 0xFF;
    
    // Reset timer
    TCNT0 = 0;                         
/*
0 	0 	0 	Timer désactivé
0 	0 	1 	Fréquence système
0 	1 	0 	Fréquence système/8
0 	1 	1 	Fréquence système/64
1 	0 	0 	Fréquence système/256
1 	0 	1 	Fréquence système/1024
*/
    TCCR0 |= 0x03;                     
    // Enable overflow interrupt
    TIMSK |= 1<<TOIE0;
    
    lcd_init(LCD_DISP_ON);
    lcd_clrscr();

    sei();

    while(1)
    {


    }
    
    return 0;
}

