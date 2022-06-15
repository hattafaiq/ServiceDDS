// FIR filters by Windowing
// A.Greensted - Feb 2010
// http://www.labbookpages.co.uk

/*
    27 Des 2010
    Asam-Asam

    double diganti ke float

    18 Des 2012
    Dicopy dari Lib Haliza ke Bone/Server_simul

    10 Mei 2013
    untuk Haliza v10
*/
#ifdef __cplusplus
extern "C" {
#endif


#include <stdio.h>
#include <math.h>
#include <malloc.h>
//#include <fftw3.h>
#include <complex.h>

#include "window_filter.h"



// Prototypes
doubledd *create1TransSinc(int windowLength, doubledd transFreq, doubledd sampFreq, enum filterType type);
doubledd *create2TransSinc(int windowLength, doubledd trans1Freq, doubledd trans2Freq, doubledd sampFreq, enum filterType type);

doubledd *createWindow2(doubledd *in, doubledd *out, int windowLength, enum windowType type);

void calculateKaiserParams(doubledd ripple, doubledd transWidth, doubledd sampFreq, int *windowLength, doubledd *beta);
doubledd *createKaiserWindow(doubledd *in, doubledd *out, int windowLength, doubledd beta);
doubledd modZeroBessel(doubledd x);

int outputFFT(char *filename, doubledd *window, int windowLength, doubledd sampFreq);


doubledd * buat_filter_FFT(doubledd *window, int windowLength, doubledd sampFreq);

doubledd *hpf_hamming;
static int flag_akhir;

#define INVALID	0
#define VALID	1

int windowLength;


#ifdef __cplusplus
}
#endif
