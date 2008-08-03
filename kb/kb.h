/* Keyboard communication routines
 * Contributors:
 *   scienceprog.com
 *   Nicolas GUILLAUME <ng@ngosft-fr.com>
 */


#ifndef KB_H
#define KB_H


#include <avr/interrupt.h>
#include "pindefs.h"

#define ISC0_FALLING_EDGE 2
#define ISC0_RISING_EDGE 3

void kb_init(void);

ISR(INT0_vect);

void kb_decode(unsigned char sc);

void kb_put_buff(unsigned char c);

int kb_getchar();


#endif
