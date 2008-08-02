/***************************************************************************
 *   This file is part of the 'utils' projects                             *
 *                                                                         *
 *   'utils' projects                                                      *
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

#ifndef IOMIN_H
#define IOMIN_H

#include <lcutil/string.h>

#define MIO_CFG_PUTCHAR(c) putchar(c);

/**
 * Minimal IO
 */

#ifndef MIO_CFG_PUTCHAR
# error "MIO_CFG_PUTCHAR undefined!"
#endif

#ifndef MIO_CFG_LN_BREAK
# define MIO_CFG_LN_BREAK "\r\n"
#endif


#define mio_putc(c) MIO_CFG_PUTCHAR(c)

void mio_puts(const char * str);

/** Minimal version of printf()
 *    Support the following format:
 *       %d: print the integer (decimal).
 *       %h: print the integer (hexadecimal).
 *       %o: print the integer (octal).
 *       %b: print the integer (binary).
 *       %c: print the character.
 *       %s: print the null terminated string.
 *       %n: print a line break.
 *       %%: print %.
 */
void mio_printf(const char * format, ...);


#if !defined(__DOXYGEN__)
static inline void mio_printi(int __i, int __base) __attribute__((always_inline));
#endif

void mio_printi(int i, int base)
{
    char buff[16];
    itoa(i, buff, base);
    mio_puts(buff);
}

#endif


