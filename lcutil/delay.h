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

#define _DMS_LIMIT (262.14 / ((double)F_CPU / 1000000.00))


#if !defined(__DOXYGEN__)
static inline void delay_ms(unsigned short __ms) __attribute__((always_inline));
#endif


void delay_ms(unsigned short ms)
{
    double v = (double)ms / _DMS_LIMIT;
    unsigned short i, k = (unsigned short)v;

    for(i = 0; i < k; ++i)
	_delay_ms(_DMS_LIMIT);

    _delay_ms(v - (double)k);
}



#endif
