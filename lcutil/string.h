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

#ifndef LCSTRING_H
#define LCSTRING_H


#if !defined(__DOXYGEN__)
static inline void strreverse(char * __begin, char * __end) __attribute__((always_inline));
#endif


void strreverse(char * begin, char * end)
{	
    char aux;
    while(end>begin)
	aux = *end, *end-- = *begin, *begin++ = aux;
}


void itoa(int value, char * str, int base);

#endif


