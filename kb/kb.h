// Keyboard communication routines

#ifndef __KB_INCLUDED
#define __KB_INCLUDED

#include <avr/interrupt.h>
//#include "io8515.h"
#include "pindefs.h"

#define ISC00 0
#define ISC01 1

void init_kb(void);

ISR(INT0_vect);

void decode(unsigned char sc);

void put_kbbuff(unsigned char c);

int getchar(void);


#endif

