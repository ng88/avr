/* 
 *  Author: Nicolas GUILLAUME <ng@ngsoft-fr.com>
 */

#include <avr/pgmspace.h>

#include <lcutil/delay.h>
#include <serial/serial.h>

#define FOSC F_CPU
#define BAUD 38400
#define MYUBRR FOSC/(F_CPU/1000/1000)/BAUD-1
int main()
{
    DDRD = 0x00;
    DDRD |= _BV(PD4) | _BV(PD5);
  DDRB = 0xEF; //PB4 = MISO
  DDRC = 0xFF; //All outputs
  DDRD = 0xFE; //PORTD (RX on PD0)

    usart_init(1);
  UCSRB = (1<<RXEN)|(1<<TXEN);
  UCSRC = (1<<URSEL)|(3<<UCSZ0);

    printf("salut\n");

    while(1)
    {
    
	/*
	  PORTD |= (1 << PD4) | (1 << PD5);

	delay_ms(1000);
	PORTD &= ~(1 << PD4) & ~(1 << PD5);

	delay_ms(3000);
	*/
	putchar(getchar());
    }


    return 0;
}


