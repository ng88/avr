#ifndef BUZZER_H
#define BUZZER_H

/** @author Nicolas GUILLAUME <nicolas@guillaume-fr.net>
 */

#define N_DO_3 262
#define N_DOD_3 277
#define N_RE_3 294
#define N_RED_3 311
#define N_MI_3 330
#define N_FA_3 349
#define N_FAD_3 370
#define N_SOL_3 392
#define N_SOLD_3 415
#define N_LA_3 440
#define N_LAD_3 466
#define N_SI_3 494
#define N_PAUSE 0

#define N_BLANCHE 4
#define N_NOIRE   2
#define N_RONDE   8
#define N_CROCHE  1


/** Emit a beep at freq during len_ms ms
 */
void bz_beep(double freq, double len_ms);

/** Play music stored in part
 */
void bz_play(unsigned short int ** part, int size, double  tempo);

#endif
