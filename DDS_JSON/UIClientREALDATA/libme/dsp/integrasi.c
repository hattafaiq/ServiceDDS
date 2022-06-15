/*
	integrasi
	furkan jadid

	17 Sept 2012, dicopy dari 
	util_spektrum.c (Haliza)

	diedit untuk disesuiakan dengan 
	CPU dengan Floating Point Unit (FPU)

*/
#include <math.h>
#include "integrasi.h"

/* 	proses integrasi, data input (cin) tidak
	berubah */

//float integral_kuno( fract32 *cin, float *out, int jum)
float integrasi( float *cin, float *out, int jum)
{
	int i;
	float temp;
	float maks;
	float min;
	float mean;

	maks = 0;
	min = 1;
	temp = 0;

	// dicari mean nya, dulu biar pengaruh DC level tidak besar
	for (i=0; i<jum; i++)
	{
		//temp += out[i] = (float) (fr32_to_float( cin[ i ] ));
		temp += cin[ i ];
	}

	mean = (float) (temp/jum);


	// sinyal asli dihilangkan dulu DC nya
	for (i=0; i<jum; i++)
	{
		out[i] = cin[i] - mean;	
	}

	// diintegralkan dan cari maks dan min
	for (i=1; i<jum; i++)
	{
		out[i] = out[i] + out[i-1];
		
		if (out[i] > maks) maks = out[i];
		if (out[i] < min) min = out[i];
    }

	if (fabs(min) > maks) maks = fabs(min);

	/* return berisi maksimum untuk kepentingan lainnya */
	return (float) maks;
}
#if 0
#define E_NATURAL	2.718281828

static double a0;
static double a1;
static double b1;


static double in_lama;
static double out_lama;

void hitung_koef_IIR_highpass(unsigned int srate, int f_start)
{
    double pangkat;
    double xf;

    //pangkat = (float) ( 0.50 / (float) (srate * 1.0) );
    //pangkat = (float) ( 0.317 / (float) (srate * 1.0) );		// masih kurang separo
    pangkat = (double) ( 0.158 / (double) (srate * 1.0) );

    double ff_start = (double) f_start * 1.0;

    pangkat = (double) ( ff_start / (double) (srate * 1.0) );

    printf("start %f, rate %d\n", ff_start, srate);

    /* disini menghitung koefisien filter recursive */
    pangkat = (double) (2.0 * M_PI * pangkat);

    xf = (double) pow( E_NATURAL, pangkat);
    xf = 1.00 / xf;

    // low pass
    a0 = (double) (1 - xf);
    b1 = (double) xf;

    // high pass
    a0 = (double) ((1 + xf)/2.00);
    a1 = (double) -1 * a0;
    b1 = xf;

    //a0 = 0.93;
    //a1 = -0.93;
    //b1 = 0.86;

    printf("%s(): a0 = %.10f, a1= %f, b1 = %.10f, %.20f\r\n", \
           __FUNCTION__, a0, a1, b1, pangkat);

    in_lama = 0;
    out_lama = 0;

    return;
}


void iir_highpass(double *in, double *out, int len)
{
    int i;
    out[0] = (a0 * in[0]) + (a1 * in_lama) + (b1 * out_lama);

    for (i=1;i<len; i++)
         out[i] = (a0 * in[i]) + (a1 * in[i-1]) + (b1 * out[i-1]);
        //a_lama = (a0 * in[i] + (b1 * a_lama);

    in_lama = in[len-1];
    out_lama = out[len-1];
}

#endif
