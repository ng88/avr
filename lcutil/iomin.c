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
#include <lcutil/iomin.h>

void mio_puts(const char * s)
{
    while(*s)
	mio_putc(*s++);
}

void mio_printf(const char * s, ...)
{
    enum { NORMAL, WAIT_PC } state = NORMAL;
    va_list ap;
    va_start(ap, s);

    while(*s)
    {
	if(state == NORMAL)
	{
	    if(*s == '%')
		state = WAIT_PC;
	    else
		mio_putc(*s);
	}
	else
	{
	    switch(*s)
	    {
	    case 'n': mio_puts(MIO_CFG_LN_BREAK); break;
	    case 'p': mio_puts("0x");
	    case 'h': mio_printi(va_arg(ap, int), 16); break;
	    case 'd': mio_printi(va_arg(ap, int), 10); break;
	    case 'o': mio_printi(va_arg(ap, int), 8); break;
	    case 'b': mio_printi(va_arg(ap, int), 2); break;
	    case 's': mio_puts(va_arg(ap, char*)); break;
	    case 'c': mio_putc(va_arg(ap, int)); break;
	    default: mio_putc(*s); break;
	    }
	    state = NORMAL;
	}
	s++;
    }
    va_end(ap);
}








