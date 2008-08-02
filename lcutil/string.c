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


#include <stdarg.h>
#include <stdlib.h>
#include <lcutil/string.h>

	
void itoa(int value, char * str, int base)
{
    static char num[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    char* wstr = str;
    int sign;
    div_t res;
	
    if (base<2 || base>35)
    {
	*wstr = '\0';
	return;
    }
	
    if((sign = value) < 0)
	value = -value;

    do
    {
	res = div(value, base);
	*wstr++ = num[res.rem];
	
    }
    while( (value = res.quot) );
	
    if(sign<0)
	*wstr++ = '-';
    
    *wstr = '\0';
    strreverse(str, wstr - 1);
}





