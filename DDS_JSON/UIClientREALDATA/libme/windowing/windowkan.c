/*

 windowkan

 melakukan konvolusi (perkalian) antara sinyal
 dengan koefisien window filter

 furkan jadid
 4 Des 2012
 daun biru engineering

*/

#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include "windowkan.h"

void windowkan(float *in, float *out, float *koef, int len)
{
    int i;

    for (i=0; i<=len; i++)
    {
        out[i] = in[i] * koef[i];
    }
}

void windowkand(double *in, double *out, double *koef, int len)
{
    int i;

    for (i=0; i<=len; i++)
    {
        out[i] = in[i] * koef[i];
    }
}

// Create sinc function for filter with 1 transition - Low and High pass filters
double *create1TransSinc(int windowLength, double transFreq, double sampFreq, enum filterType type)
{
    int n;

    // Allocate memory for the window
    double *window = (double *) malloc(windowLength * sizeof(double));
    if (window == NULL) {
        fprintf(stderr, "create1TransSinc: Could not allocate memory for window\n");
        return NULL;
    }

    if (type != LOW_PASS && type != HIGH_PASS) {
        fprintf(stderr, "create1TransSinc: Bad filter type, should be either LOW_PASS of HIGH_PASS\n");
        return NULL;
    }

    // Calculate the normalised transistion frequency. As transFreq should be
    // less than or equal to sampFreq / 2, ft should be less than 0.5
    double ft = transFreq / sampFreq;

    double m_2 = 0.5 * (windowLength-1);
    int halfLength = windowLength / 2;

    // Set centre tap, if present
    // This avoids a divide by zero
    if (2*halfLength != windowLength) {
        double val = 2.0 * ft;

        // If we want a high pass filter, subtract sinc function from a dirac pulse
        if (type == HIGH_PASS) val = 1.0 - val;

        window[halfLength] = val;
    }
    else if (type == HIGH_PASS) {
        fprintf(stderr, "create1TransSinc: For high pass filter, window length must be odd\n");
        return NULL;
    }

    // This has the effect of inverting all weight values
    if (type == HIGH_PASS) ft = -ft;

    // Calculate taps
    // Due to symmetry, only need to calculate half the window
    for (n=0 ; n<halfLength ; n++) {
        double val = sin(2.0 * M_PI * ft * (n-m_2)) / (M_PI * (n-m_2));

        window[n] = val;
        window[windowLength-n-1] = val;
    }

    return window;
}


