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

#ifndef ASSERT_DEBUG_H
#define ASSERT_DEBUG_H

#include <stdlib.h>
#include <stdio.h>

/** check that cond is true, str is displayed if it fails */
#define c_assert2(cond, str) __assert((cond), __LINE__, __FILE__, ___FUNCTION, (str), #cond)

/** check that cond is true, "assertion failed" is displayed if it failed */
#define c_assert(cond) c_assert2((cond), "assertion failed")


/** warm by showing str if cond is not true */
#define c_warning2(cond, str) __warning((cond), __LINE__, __FILE__, ___FUNCTION, (str), #cond)

/** warm by showing "warning" if cond is not true */
#define c_warning(cond) c_warning2((cond), "warning")



#ifndef DISABLE_DEBUG_PRINT

#define dbg_printf(args ...) \
          do {printf("debug> line %d: in %s::%s(): ", __LINE__, __FILE__, ___FUNCTION); printf(args);} while(0)

#else

#define dbg_printf(format, args ...)

#endif


#ifndef DISABLE_ASSERT


#define __assert(cond, line, file, fn, str, cond_str) \
          do { if(!cond) { printf("assertion error on `" cond_str "' in "  file "::%s() at line %d: %s%n", fn, line, str); abort(); } } while(0)
#define __warning(cond, line, file, fn, str, cond_str) \
          do { if(!cond) { printf("warning on `" cond_str "' in " file "::%s() at line %d: %s%n", fn, line, str) ; } } while(0)

#else

#define __assert(cond, line, file, fn, str, cond_str)
#define __warning(cond, line, file, fn, str, cond_str)

#endif

#define ___FUNCTION __FUNCTION__



#endif


