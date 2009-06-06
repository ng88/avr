
#include <avr/pgmspace.h>
#include <pinpad/pinpad.h>
#include <util/delay.h>

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
    unsigned char i, j, k;
    is_active = 1;
    while(is_active)
    {
	for(i = PP_COL_START; i < PP_COL_START + PP_COL_COUNT; i++)
	{
	    _delay_ms(1);
	    PP_PORT_COL &= ~_BV(i);	   
	    _delay_ms(1);

	    for(j = PP_ROW_START; j < PP_ROW_START + PP_ROW_COUNT; j++)
		if(!bit_is_set(PP_PIN_ROW, j))
		{
		    (*cbkeychanged)(j * (PP_ROW_COUNT - 1) + i + 1);
		    /* debouncing, wait for key up or time up */
		    k = 0;
		    while(k < PP_REPET_DELAY && !bit_is_set(PP_PIN_ROW, j))
		    {
			  _delay_ms(10);
                          #if PP_REPET_ENABLED
			   k += 10;
			  #endif
		    }
		}

	    PP_PORT_COL |= _BV(i);
	}
    }
}


void pinpad_stop_active_loop()
{
    is_active = 0;
}




char pinpad_keycode2char(unsigned char keycode)
{
#if PP_ROW_COUNT <= 3 && PP_COL_COUNT <= 3
    return '0' + keycode;
#elif  PP_ROW_COUNT == 4 && PP_COL_COUNT == 3
    if(keycode < 10)
	return '0' + keycode;
    else if(keycode == 10)
	return '*';
    else if(keycode == 11)
	return '0';
    else
	return '#';
#else
# warning "keyboard not supported, pinpad_keycode2char() will not work."
    return keycode;
#endif
}

