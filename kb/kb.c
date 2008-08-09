/* Keyboard communication routines
 *  Author:  Nicolas GUILLAUME <ng@ngsoft-fr.com>
 */


#include "kb.h"
#include "scancodes.h"
#include <lcutil/delay.h>
#include <lcutil/cbuffer.h>


static cbuffer_t buff;

void kb_init(void)
{ 
    cb_init(&buff);
    MCUCR = ISC0_FALLING_EDGE;
}

ISR(INT0_vect)
{

    static unsigned char data = 0; /* holds the received scancode */
    static unsigned char bitcount = 11;
 
    /** 11 bits:
     *  Start (0)
     *  0..7 data byte  (Least significant bit first)
     *  Parity (odd)
     *  Stop (1)
     */
	
    if(bitcount > 2 && bitcount < 11)
    {             /* start and stop bits are ignored. */
	data = (data >> 1);
	if(bit_is_set(PIN_KB, DATAPIN))
	    data = data | 0x80; // store a 1
    }

    if(--bitcount == 0)  /* all bits received */
    {
	bitcount = 11;
	//kb_decode(data);
	cb_write(&buff, data);
	//printf("SCANCODE=%X %x\n", data, KEY_UP);
	data = 0;
    }
}

int kb_getchar()
{
}

/*
void kb_decode_old(unsigned char sc)
{
    static unsigned char is_up = 0, shift = 0, mode = 0;
    unsigned char i;

    if(!is_up)                  // Last data received was the up-key identifier
    {
        switch (sc)
        {
        case KEY_UP:
            is_up = 1;
            break;

        case KEY_LEFT_SHIFT:
        case KEY_RIGHT_SHIFT:
            shift = 1;
            break;
	    
        case KEY_F1:
            if(mode == MODE_ASCII)
                mode = MODE_SCANCODE;       // Enter scan code mode
            if(mode == MODE_ESC)
                mode = MODE_LSC;       // Leave scan code mode
            break;

        default:
            if(mode == MODE_ASCII || mode == MODE_LSC)  // If ASCII mode
            {
                if(!shift)      // If shift not pressed,
                {               // do a table look-up
                    for(i = 0; unshifted[i][0] != sc && unshifted[i][0]; i++);
                    if(unshifted[i][0] == sc)
                    {
                        kb_put_buff(unshifted[i][1]);
                    }
                }
                else
                {               // If shift pressed
                    for(i = 0; shifted[i][0] != sc && shifted[i][0]; i++);
                    if(shifted[i][0] == sc)
                    {
                        kb_put_buff(shifted[i][1]);
                    }
                }
            }
            else
            {                   // Scan code mode
                //print_hexbyte(sc);            // Print scan code
                kb_put_buff(' ');
                kb_put_buff(' ');
            }
            break;
        }
    }
    else
    {
        is_up = 0;              // Two 0xF0 in a row not allowed
        switch (sc)
        {
        case KEY_LEFT_SHIFT:
        case KEY_RIGHT_SHIFT:
            shift = 0;
            break;

        case KEY_F1:
            if(mode == MODE_SCANCODE)
                mode = MODE_ESC;
            if(mode == MODE_LSC)
                mode = MODE_ASCII;
            break;
        case KEY_F2:
            //clr();
            break;
        }
    }
}*/
/*
void kb_decode(unsigned char sc)
{
    static unsigned char is_up=0, shift = 0, mode = 0;
    unsigned char i;
//OxE0  first byte of extended
    printf("DECODE is_up=%d, shift=%d, mode=%d, sc=%d\n", is_up, shift, mode, sc);

    if (!is_up)                // Last data received was the up-key identifier
    {
        switch (sc)
        {
          case 0xF0 :        // The up-key identifier
            is_up = 1;
            break;

          case 0x12 :        // Left SHIFT
            shift = 1;
            break;

          case 0x59 :        // Right SHIFT
            shift = 1;
            break;

          case 0x05 :        // F1
            if(mode == 0)
                mode = 1;    // Enter scan code mode
            if(mode == 2)
                mode = 3;    // Leave scan code mode
            break;

          default:
            if(mode == 0 || mode == 3)        // If ASCII mode
            {
                if(!shift)                    // If shift not pressed,
                {                            // do a table look-up
                    for(i = 0; unshifted[i][0]!=sc && unshifted[i][0]; i++);
                    if (unshifted[i][0] == sc) {
                        kb_put_buff(unshifted[i][1]);
                    }
                } else {                    // If shift pressed
                    for(i = 0; shifted[i][0]!=sc && shifted[i][0]; i++);
                    if (shifted[i][0] == sc) {
                        kb_put_buff(shifted[i][1]);
                    }
                }
            } else{                            // Scan code mode
                //print_hexbyte(sc);            // Print scan code
                kb_put_buff(' ');
                kb_put_buff(' ');
            }
            break;
        }
    } else {
        is_up = 0;                            // Two 0xF0 in a row not allowed
        switch (sc)
        {
          case 0x12 :                        // Left SHIFT
            shift = 0;
            break;
            
          case 0x59 :                        // Right SHIFT
            shift = 0;
            break;

          case 0x05 :                        // F1
            if(mode == 1)
                mode = 2;
            if(mode == 3)
                mode = 0;
            break;
          case 0x06 :                        // F2
	      //clr();
            break;
        } 
    }    
} 

void kb_put_buff(unsigned char c)
{
    printf("char=%c %d\n", c, c);
    if(buffcnt < BUFF_SIZE)     // If buffer not full
    {
        *inpt = c;              // Put character into buffer
        inpt++;                 // Increment pointer

        buffcnt++;

        if(inpt >= kb_buffer + BUFF_SIZE)       // Pointer wrapping
            inpt = kb_buffer;
    }
}

int kb_getchar()
{
    int byte;
    while(buffcnt == 0);        // Wait for data

    byte = *outpt;              // Get byte
    outpt++;                    // Increment pointer

    if(outpt >= kb_buffer + BUFF_SIZE)  // Pointer wrapping
        outpt = kb_buffer;

    buffcnt--;                  // Decrement buffer count

    return byte;
}
*/
