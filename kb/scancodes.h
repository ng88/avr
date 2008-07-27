/* 
 *  Author: Nicolas GUILLAUME <ng@ngosft-fr.com>
 */  

#ifndef SCANCODES_H
#define SCANCODES_H

#ifndef KB_KEYMAP_QWERTY
# ifndef KB_KEYMAP_AZERTY
#  define KB_KEYMAP_QWERTY
# endif
#endif


#ifdef KB_KEYMAP_QWERTY
# include "scancodes_qwerty.h"
#endif

#ifdef KB_KEYMAP_AZERTY
# include "scancodes_azerty.h"
#endif


#endif


