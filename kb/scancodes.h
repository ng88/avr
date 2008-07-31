/* 
 *  Author: Nicolas GUILLAUME <ng@ngosft-fr.com>
 */  

#ifndef SCANCODES_H
#define SCANCODES_H

#define KEY_UP             0xF0
#define KEY_LEFT_SHIFT     0x12
#define KEY_RIGHT_SHIFT    0x59
#define KEY_F1             0x05
#define KEY_F2             0x06

#if !defined(KB_KEYMAP_QWERTY) && !defined(KB_KEYMAP_AZERTY)
# define KB_KEYMAP_QWERTY
# warning "no KB_KEYMAP defined, using KB_KEYMAP_QWERTY by default"
#endif


#ifdef KB_KEYMAP_QWERTY
# include "scancodes_qwerty.h"
#endif

#ifdef KB_KEYMAP_AZERTY
# include "scancodes_azerty.h"
#endif


#endif


