/* Keyboard communication routines
 * Contributors:
 *   scienceprog.com
 *   Nicolas GUILLAUME <ng@ngosft-fr.com>
 */


#include "kb.h"
#include "scancodes.h"

#define BUFF_SIZE 64

enum
{
    FALLING_EDGE = 0,
    RISING_EDGE = 1
};

enum
{
    MODE_ASCII = 0,
    MODE_SCANCODE = 1,
    MODE_ESC = 2,
    MODE_LSC = 3
};

unsigned char edge, bitcount;   // 0 = neg.  1 = pos.

unsigned char kb_buffer[BUFF_SIZE];
unsigned char *inpt, *outpt;
unsigned char buffcnt;


void kb_init(void)
{
    inpt = kb_buffer;           // Initialize buffer
    outpt = kb_buffer;
    buffcnt = 0;

    MCUCR = 2;                  // INT0 interrupt on falling edge
    edge = FALLING_EDGE;
    bitcount = 11;
}

ISR(INT0_vect)
{
    PORTD |= (1 << PD7);
    int a=2048;while(a--);
    PORTD &= ~(1 << PD7);
//    uart_putc('l');
    static unsigned char data;  // Holds the received scan code

    if(!edge)                   // Routine entered at falling edge
    {
        if(bitcount < 11 && bitcount > 2)       // Bit 3 to 10 is data. Parity bit,
        {                       // start and stop bits are ignored.
            data = (data >> 1);
            if(PIND & 8)
                data = data | 0x80;     // Store a '1'
        }

        MCUCR = 3;              // Set interrupt on rising edge
        edge = RISING_EDGE;

    }
    else
    {                           // Routine entered at rising edge

        MCUCR = 2;              // Set interrupt on falling edge
        edge = FALLING_EDGE;

        if(--bitcount == 0)     // All bits received
        {
            kb_decode(data);
            bitcount = 11;
        }
    }
}


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
}

void kb_decode(unsigned char sc)
{
    static unsigned char is_up=0, shift = 0, mode = 0;
    unsigned char i;

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
