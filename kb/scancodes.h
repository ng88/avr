/* 
 *  Author: Nicolas GUILLAUME <ng@ngosft-fr.com>
 */  

#ifndef SCANCODES_H
#define SCANCODES_H

enum
{
    KEY_UP           = 0xF0,
    KEY_LEFT_SHIFT   = 0x12,
    KEY_RIGHT_SHIFT  = 0x59,
    KEY_F1           = 0x05,
    KEY_F2           = 0x06,
};

enum
{
    KM_KEY = 0,
    KM_NORMAL = 1,
    KM_SHIFTED = 2,
    KM_ALTGRED = 3,

    KM_COUNT
};

#if !defined(KB_KEYMAP_QWERTY) && !defined(KB_KEYMAP_AZERTY)
# define KB_KEYMAP_AZERTY
# warning "no KB_KEYMAP defined, using KB_KEYMAP_AZERTY by default"
#endif


#ifdef KB_KEYMAP_QWERTY
# include "scancodes_qwerty.h"
#endif

#ifdef KB_KEYMAP_AZERTY
# include "scancodes_azerty.h"
#endif

#if !defined(__DOXYGEN__)
static inline unsigned char scancode_to_ascii(unsigned char __c, unsigned char __m) __attribute__((always_inline));
static inline unsigned char scancode_ex_to_ascii(unsigned char __c, unsigned char __m) __attribute__((always_inline));
#endif

/** Normal scancode to ascii */
unsigned char scancode_to_ascii(unsigned char code, unsigned char modifier)
{
    unsigned char i = 0;
    register unsigned char c;
    while( (c = kb_keymap[i][KM_KEY]) )
    {
	if(c == code)
	    return kb_keymap[i][modifier];

	i++;
    }
    return '?';
}

/** Extended scancode to ascii */
unsigned char scancode_ex_to_ascii(unsigned char code, unsigned char modifier)
{
    unsigned char i = 0;
    register unsigned char c;
    while( (c = kb_keymap_ex[i][KM_KEY]) )
    {
	if(c == code)
	    return kb_keymap_ex[i][modifier];

	i++;
    }
    return '?';
}


#endif


