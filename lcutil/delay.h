/***************************************************************************
 *   This file is part of the 'avrutils' projects                             *
 *                                                                         *
 *   'avrutils' projects                                                      *
 *                                                                         *
 *   Copyright (C) 2006, 2008 by GUILLAUME Nicolas                         *
 *   ng@ngsoft-fr.com                                                      *
 *                                                                         *
 *   http://svn.ngsoft-fr.com/trac/utils/                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; version 2 of the License only.          *
 *   See the COPYING file.                                                 *
 ***************************************************************************/

#ifndef NG_DELAY_H
#define NG_DELAY_H

#include <util/delay.h>

#define _DMS_LIMIT (262.14 / (double)F_CPU)


#if !defined(__DOXYGEN__)
static inline void delay_ms(unsigned short __ms) __attribute__((always_inline));
#endif

/*
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



void delay_ms(double ms)
{
    register int k = (ms / _DMS_LIMIT) + 1;
    register int i;

    for(i = 0; i < k; ++i)
	_delay_ms(_DMS_LIMIT);
}
*/


void delay_ms(unsigned short ms)
{
    unsigned short outer1, outer2;
    outer1 = 200;
    while(outer1)
    {
	outer2 = 1000;
	while(outer2)
	{
	    while(ms) ms--;
	    outer2--;
	}
	outer1--;
    }
}

#endif
