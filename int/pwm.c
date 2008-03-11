
#define  F_CPU 3686400
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
 


int main()
{
    srand(0);

/* set OC2 for PWM output*/

    DDRB = (1<<PINB3);
    
/*set timer counter initial value*/

    TCNT2=0x00;

/*Set timer output compare register*/

    OCR2=0x80;

/*start timer:

without presscaler

Non inverted mode in OC2 pin;

phase corect PWM*/

    TCCR2 = (1<<FOC2)|(1<<COM21)|(1<<COM20)|(1<<WGM20)|(1<<CS00);
    
    for (;;);
}


 


