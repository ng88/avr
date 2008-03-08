
#define  F_CPU 3686400
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


SIGNAL(SIG_OVERFLOW0)
{
   
   static volatile unsigned char count = 0;

   count ++;

   if(count >= 10)
   {
 
       count = 0;

       if(bit_is_set(PORTB, PB0))
	   PORTB &= ~_BV(PB0);	   
       else
	   PORTB|= _BV(PB0);

   }

}
 
int main (void)
{
 
    DDRB = 0xFF;
    
    // Reset timer
    TCNT0 = 0;                         
    // Set prescaler 1/1024
    TCCR0 |= 0x05;                     
    // Enable overflow interrupt
    TIMSK |= 1<<TOIE0;
    

    sei();

    while(1)
    {


    }
    
    return 0;
}

