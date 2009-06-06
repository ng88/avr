#ifndef _PINPAD_H_86767
#define _PINPAD_H_86767

/** This file must define:
 *  PP_PIN_ROW port used for rows
 *  PP_DDR_ROW
 *  PP_PORT_COL port used for cols
 *  PP_DDR_COL
 *  PP_ROW_START number of the first pin used on PP_PORT_ROW
 *  PP_COL_START number of the first pin used on PP_PIN_COL
 */
#include "pindefs.h"

#ifndef PP_ROW_COUNT
# define PP_ROW_COUNT 4
#endif

#ifndef PP_COL_COUNT
# define PP_COL_COUNT 3
#endif

/** key repetition enabled by default */
#ifndef PP_REPET_ENABLED
# define PP_REPET_ENABLED 1
#endif

/** minimum delay for repetition */
#ifndef PP_REPET_DELAY
# define PP_REPET_DELAY 100
#endif


typedef void (*fn_key_changed_t)(unsigned char keycode);


void pinpad_init();

void pinpad_start_active_loop(fn_key_changed_t cbkeychanged);

void pinpad_stop_active_loop();

char pinpad_keycode2char(unsigned char keycode);

#endif
