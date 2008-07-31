/* Keyboard communication routines
 * Contributors:
 *   scienceprog.com
 *   Nicolas GUILLAUME <ng@ngosft-fr.com>
 */


#ifndef KB_H
#define KB_H


#include <avr/interrupt.h>
#include "pindefs.h"

#define ISC00 0
#define ISC01 1

void init_kb(void);

ISR(INT0_vect);

void decode(unsigned char sc);

void put_kbbuff(unsigned char c);

int getchar(void);


#endif
