#ifndef NG_DELAY_H
#define NG_DELAY_H

#include <util/delay.h>

#define _DMS_LIMIT (262.14 / (double)F_CPU)


#if !defined(__DOXYGEN__)
static inline void delay_ms(double __ms) __attribute__((always_inline));
#endif


/** Wait ms milliseconds.
 */
void delay_ms(double ms)
{
    double tw;
    do
    {
	tw = (ms > _DMS_LIMIT) ? _DMS_LIMIT : ms;

	_delay_ms(tw);
	ms -= tw;
    }
    while(ms > 0.00);
}


/** Wait ms milliseconds.
 */
void delay_ms2(double ms)
{
    register int k = (ms / _DMS_LIMIT) + 1;
    register int i;

    for(i = 0; i < k; ++i)
	_delay_ms(_DMS_LIMIT);
}




#endif
