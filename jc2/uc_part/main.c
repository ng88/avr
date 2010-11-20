#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <lcutil/iocompat.h>

#include "local_pin_config.h"

#define ISC0_FALLING_EDGE 2
#define ISC0_RISING_EDGE 3

/**
 *
 *
 *  @author: Nicolas GUILLAUME <nicolas@guillaume-fr.net> 2008 - 2009
 *
 *
 *  Configuration par défaut (cf local_pin_config.h) :
 *
 *
 */

#define LB_LED_DELAY 150

#define MT_MAX_SPEED 127
#define MT_MIN_SPEED 60

typedef enum
{
    CMD_SET_SPEED = 10,
    CMD_SET_TSPEED = 11,
    CMD_SET_LED = 20,
} cmd_type_t;

typedef enum
{
    MD_OFF = 0,
    /** speed is set synchronously */
    MD_SPEED = 1,
    /** speed & len are set synchronously */
    MD_TSPEED = 2,
    /** program execution mode */
    MD_PROGRAM = 3,
} motor_mode_t;


/** Command:
 *  1 byte header (cmd_type_t) | payload
 *
 *  Motor commands:
 *    Set speed:
 *      CMD_SET_SPEED   (uint8) 
 *      speed_value     (uint8)
 *        between MT_MIN_SPEED & MT_MAX_SPEED
 *
 *    Set speed during a given time:
 *      CMD_SET_TSPEED
 *      speed_value     (uint8)
 *        between MT_MIN_SPEED & MT_MAX_SPEED or 0
 *      length        (uint16)
 *        in PWM timer tick
 *
 *  LED commands:
 *    Set led:
 *      CMD_SET_LED     (uint8) 
 *      status          (uint8)
 *        0 -> LED OFF, other value -> LED ON
 *
 *
 *
 *  CMD_SET_TSPEED | speed_value (uint8) | length (uint16)
 */

volatile uint8_t       motor_speed = 0;
volatile uint16_t      motor_len = 0;
volatile motor_mode_t  motor_mode  = MD_OFF;

#define set_motor_mode(x) motor_mode = (x)
#define set_motor_speed(x) motor_speed = (x)
#define set_motor_run_len(x) motor_len = (x)

void set_led(char v)
{
    if(v)
	LB_PORT |= _BV(LB_PIN);
    else
	LB_PORT &= ~_BV(LB_PIN);
}

/** PWM timer */
ISR(TIMER1_OVF_vect)
{
    
    OCR = motor_speed;
}

void process_incoming_command()
{
    switch(usart_getbyte())
    {
    case CMD_SET_SPEED:
	uint8_t new_speed = usart_getbyte();
	if(new_speed < MT_MIN_SPEED || new_speed > MT_MAX_SPEED)
	    new_speed = 0;
	cli();
	set_motor_mode(MD_SPEED);
	set_motor_speed(new_speed);
	sei();
	break;

    case CMD_SET_TSPEED:
	uint8_t new_speed = usart_getbyte();
	uint16_t new_len  = usart_getword();

	if(new_speed < MT_MIN_SPEED || new_speed > MT_MAX_SPEED)
	    new_speed = 0;

	cli();
	set_motor_mode(MD_TSPEED);
	set_motor_speed(new_speed);
	set_motor_run_len(new_len);
	sei();
	break;

    case CMD_SET_LED:
	set_led(usart_getbyte());
	break;

    }
}

void change_speed()
{
    
    static enum
    {
	UP, 
	DOWN
    } direction = UP;

    if(direction == UP)
    {
	if(motor_speed == MT_MAX_SPEED)
	{
	    motor_speed--;
	    direction = DOWN;
	}
	else
	    motor_speed++;
    }
    else
    {
	if(motor_speed == MT_MIN_SPEED)
	{
	    motor_speed++;
	    direction = UP;
	}
	else
	    motor_speed--;

    }

}


int main()
{

    /* Timer 1: Fast PWM, 8-bit  p98 */
    TCCR1A = _BV(WGM10) | _BV(WGM12) | _BV(COM1A1);//TIMER1_PWM_INIT;

    /*
     * Start timer 1.
     *
     * NB: TCCR1A and TCCR1B could actually be the same register, so
     * take care to not clobber it.
     */
    TCCR1B |= _BV(CS10);//TIMER1_CLOCKSOURCE;
    /*
     * Run any device-dependent timer 1 setup hook if present.
     */
    /* Set PWM value to 0. */
    OCR = 0;

    /* motor & del as output */
    LB_DDR |= _BV(LB_PIN);
    MT_DDR |= _BV(MT_PIN);


    motor_speed = MT_MIN_SPEED;

    /* Enable timer 1 overflow interrupt. */
    TIMSK = _BV (TOIE1);
    sei();


/*
    enum { N = 15 };
    uint8_t s[N] = { 128, 61, 100, 80, 110, 0, 120, 0, 0, 120, 110, 100, 0, 0, 0 };
    uint8_t i = 0;

    while(1)
    {
	LB_PORT |= _BV(LB_PIN);
	_delay_ms(LB_LED_DELAY);

	//change_speed();

	LB_PORT &= ~_BV(LB_PIN);
	_delay_ms(LB_LED_DELAY << 1);

	//change_speed();

	motor_speed = s[i];

	i++;
	if(i == N)
	    i = 0;
    }
*/

    while(1)
    {
    }

    return 0;

}

