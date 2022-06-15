/*
 * 11 Mei 2013
 * Furkan Jadid
 * Daun Biru Engineering
 *
 * IIR idenya banyak diambil dari Haliza
 *
 */

#include <math.h>
#include "window_filter.h"


#define E_NATURAL	2.718281828


void hitung_koef_IIR_velocity(unsigned int srate, doubledd *p_a0, doubledd *p_b1)
{
    doubledd pangkat;
    doubledd xf;
    doubledd a0;
    doubledd b1;

    //pangkat = (float) ( 0.50 / (float) (srate * 1.0) );
    //pangkat = (float) ( 0.317 / (float) (srate * 1.0) );		// masih kurang separo
    pangkat = (doubledd) ( 0.158 / (float) (srate * 1.0) );

    /* disini menghitung koefisien filter recursive */
    pangkat = (doubledd) (2.0 * M_PI * pangkat);

    xf = (doubledd) pow( E_NATURAL, pangkat);
    xf = 1.00 / xf;

    a0 = (doubledd) (1 - xf);
    b1 = (doubledd) xf;

    printf("%s(): a0 = %.10f, b1 = %.10f\r\n", __FUNCTION__, a0, b1);

    *p_a0 = a0;
    *p_b1 = b1;

    return;
}
