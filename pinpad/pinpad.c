
#include <avr/pgmspace.h>
#include <pinpad/pinpad.h>
#include <util/delay.h>

#include <stdio.h>

static volatile char is_active;

void pinpad_init()
{
    unsigned char i;

    is_active = 0;

    for(i = PP_COL_START; i < PP_COL_START + PP_COL_COUNT; i++)
    {
	PP_DDR_COL |= _BV(i);
	PP_PORT_COL |= _BV(i);
    }

    for(i = PP_ROW_START; i < PP_ROW_START + PP_ROW_COUNT; i++)
    {
	PP_DDR_ROW &= ~_BV(i);
	PP_PORT_ROW |= _BV(i);
    }
}


void pinpad_start_active_loop(fn_key_changed_t cbkeychanged)
{
    unsigned char i, j, c;
    is_active = 1;
    while(is_active)
    {
	c = 0;
	for(i = PP_COL_START; i < PP_COL_START + PP_COL_COUNT; i++)
	{
	    _delay_ms(PP_POLLING_INT);
	    PP_PORT_COL &= ~_BV(i);	   
	    _delay_ms(PP_POLLING_INT);

	    for(j = PP_ROW_START; j < PP_ROW_START + PP_ROW_COUNT; j++)
		if(!bit_is_set(PP_PIN_ROW, j))
		{
		    c = 1;
		    printf("(%d,%d)\n", i, j);
		}

	    PP_PORT_COL |= _BV(i);
	}

#if PP_DEBOUNCING_DELAY > 0
	if(c)
	    _delay_ms(PP_DEBOUNCING_DELAY);
#endif
    }
}


void pinpad_stop_active_loop()
{
    is_active = 0;
}

