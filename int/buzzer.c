
#define  F_CPU 3686400
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

SIGNAL(SIG_OVERFLOW0)
{
   
 

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
    TCCR0 |= 0x01;                     
    // Enable overflow interrupt
    TIMSK |= 1<<TOIE0;
    

    sei();

    while(1)
    {


    }
    
    return 0;
}

