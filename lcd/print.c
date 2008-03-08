

#define  F_CPU 3686400
#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "lcd.h"


int main()
{
    lcd_init(LCD_DISP_ON);
    lcd_clrscr();
    lcd_puts("%MSG%");
    return 0;
}
