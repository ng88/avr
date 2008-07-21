
#include "delay.h"

#define _DMS_LIMIT (262.14 / F_CPU)

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


