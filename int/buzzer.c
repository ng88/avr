
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
0 	0 	0 	Timer d�sactiv�
0 	0 	1 	Fr�quence syst�me
0 	1 	0 	Fr�quence syst�me/8
0 	1 	1 	Fr�quence syst�me/64
1 	0 	0 	Fr�quence syst�me/256
1 	0 	1 	Fr�quence syst�me/1024
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

