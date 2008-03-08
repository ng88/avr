
#define  F_CPU 3686400
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
 
ISR(INT0_vect) 				//Vecteur d'interruption de INT0
{
    PORTB |= _BV(PB0);
    _delay_ms(70);
    PORTB &= ~_BV(PB0);
}
 
int main (void)
{
 
 
	DDRD &=~_BV(2); 		//INT0 en entr�e 
	PORTD |= _BV(2); 		//Active la r�sistance de tirage sur l'entr�e INT0
 
	DDRB = 0xFF;
 
	GICR |= _BV(INT0);		//Interruption sur INT0
 
	MCUCR |= _BV(ISC01);		//Interruption sur front  descendant donc dans le registre MCUCR ISC01 = 1 ISC00 =0
					//Vu que MCUCR � comme valeur par defaut 0 on a juste � mettre ISC01 � 1 Cf : datasheet
 
 	sei();
 
	while(1);
 
 
	return 1;
}

