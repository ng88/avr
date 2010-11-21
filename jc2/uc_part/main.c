#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <lcutil/iocompat.h>


#include <serial/serial.h>

#include "local_pin_config.h"
#include "protocol.h"

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

#define MT_MAX_SPEED 255
#define MT_MIN_SPEED 60

#define PROGRAM_MAX_SIZE 64

typedef struct
{
    uint8_t  speed;
    uint16_t len;
} program_instr_t;

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


volatile uint8_t       motor_speed = 0;
volatile uint16_t      motor_len = 0;
volatile motor_mode_t  motor_mode  = MD_OFF;

volatile program_instr_t program[PROGRAM_MAX_SIZE];
volatile uint8_t         program_idx = 0;
volatile uint8_t         program_size = 0;

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

inline void program_exec_instr()
{
    if(program_idx < PROGRAM_MAX_SIZE)
    {
	set_motor_speed(program[program_idx].speed);
	set_motor_run_len(program[program_idx].len);
	program_idx++;
    }
}


/** PWM timer */
ISR(TIMER1_OVF_vect)
{
    if(motor_mode == MD_TSPEED)
    {
	if(motor_len == 0)
	    motor_speed = 0;
	else
	    motor_len--;
    }
    else if(motor_mode == MD_PROGRAM)
    {
	if(motor_len == 0)
	    program_exec_instr();
	else
	    motor_len--;
    }


    OCR = motor_speed;
}

void process_incoming_command()
{
    switch(usart_getbyte())
    {
    case CMD_SET_SPEED:
    {
	uint8_t new_speed = usart_getbyte();
	if(new_speed < MT_MIN_SPEED || new_speed > MT_MAX_SPEED)
	    new_speed = 0;
	cli();
	set_motor_mode(MD_SPEED);
	set_motor_speed(new_speed);
	sei();
	break;
    }
    case CMD_SET_TSPEED:
    {
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
    }
    case CMD_GET_SPEED_LIM:
	usart_putbyte(CMD_GET_SPEED_LIM_ANS);
	usart_putbyte(MT_MIN_SPEED);
	usart_putbyte(MT_MAX_SPEED);
	break;

    case CMD_SET_LED:
	set_led(usart_getbyte());
	break;

    case CMD_PROGRAM_CLEAR:
	if(motor_mode != MD_PROGRAM)
	    program_size = 0;
	break;

    case CMD_PROGRAM_ADD_TSPEED:
	if(motor_mode != MD_PROGRAM)
	{
	    uint8_t new_speed = usart_getbyte();
	    uint16_t new_len  = usart_getword();

	    if(new_speed < MT_MIN_SPEED || new_speed > MT_MAX_SPEED)
		new_speed = 0;

	    if(program_size < PROGRAM_MAX_SIZE - 1)
	    {
		program[program_size].speed = new_speed;
		program[program_size].len = new_len;
		program_size++;
	    }
	}
	break;

    case CMD_PROGRAM_START:
	if(motor_mode != MD_PROGRAM && program_size > 0)
	{
	    cli();
	    program_idx = 0;
	    set_motor_mode(MD_PROGRAM);
	    program_exec_instr();
	    sei();
	}
	break;

    case CMD_PROGRAM_STOP:
	cli();
	set_motor_mode(MD_SPEED);
	set_motor_speed(0);
	sei();
	break;
    }
}

#if 0
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
#endif

int main()
{

    usart_init(0);

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

    /* Enable timer 1 overflow interrupt. */
    TIMSK = _BV (TOIE1);
    sei();


    while(1)
    {

	process_incoming_command();

    }

    return 0;

}

