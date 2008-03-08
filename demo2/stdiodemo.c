/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <joerg@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.        Joerg Wunsch
 * ----------------------------------------------------------------------------
 *
 * Stdio demo
 *
 * $Id: stdiodemo.c,v 1.1.2.1 2005/12/28 22:35:08 joerg_wunsch Exp $
 */

#include "defines.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/pgmspace.h>

#include <util/delay.h>

#include "lcd.h"
#include "uart.h"

/*
 * Do all the startup-time peripheral initializations.
 */
static void
ioinit(void)
{
  lcd_init();
}

FILE lcd_str = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);

static void
delay_1s(void)
{
  uint8_t i;

  for (i = 0; i < 100; i++)
    _delay_ms(10);
}

int
main(void)
{

  ioinit();
  lcd_putchar('s');
  lcd_putchar('a');
  lcd_putchar('l');
  lcd_putchar('u');
  lcd_putchar('t');
  lcd_putchar('\n');

	while(1) _delay_ms(10);

  return 0;
}
