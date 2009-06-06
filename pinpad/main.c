/* 
 *  Author: Nicolas GUILLAUME <ng@ngsoft-fr.com>
 */

#include <avr/pgmspace.h>

#include <util/delay.h>
#include <pinpad/pinpad.h>

#include <serial/serial.h>

void key_pressed(unsigned char keycode)
{
    printf(" %d => %c\n", keycode, pinpad_keycode2char(keycode));
}

int main()
{

    PP_DDR_ROW = 0x00;
    PP_DDR_COL = 0x00;

    usart_init(1);
    _delay_ms(10);
    puts("\n\nUART INIT OK");

    pinpad_init();
    puts("PINPAD INIT OK");

    pinpad_start_active_loop(&key_pressed);

    while(1);

    return 0;
}

