/* Keyboard communication routines
 * Contributors:
 *   scienceprog.com
 *   Nicolas GUILLAUME <ng@ngsoft-fr.com>
 */


#ifndef KB_H
#define KB_H


#include <avr/interrupt.h>
#include "pindefs.h"

#define ISC0_FALLING_EDGE 2
#define ISC0_RISING_EDGE 3

enum
{
    CMD_SET_LED_STATUS = 0xed,
    CMD_RESET = 0xff,
    CMD_ECHO = 0xee,
    CMD_SET_SC_SET = 0xf0,
    CMD_SET_REPEAT_RATE = 0xf3,
    CMD_KEYBOARD_ENABLE = 0xf4,
    CMD_KEYBOARD_DISABLE = 0xf5,
    CMD_RESEND = 0xfe,
};

void kb_init(void);

ISR(INT0_vect);

/** Retrieve the next ASCII typed char */
char kb_getchar();

/** Retrieve the next scancode or EOB */
int kb_getscancode();


int kb_decode_next_char();

#endif
