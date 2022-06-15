#ifndef WINDOWKAN_H
#define WINDOWKAN_H

#ifdef __cplusplus
extern "C" {
#endif

void windowkan(float *in, float *out, float *koef, int len);
void windowkand(double *in, double *out, double *koef, int len);
enum filterType {LOW_PASS, HIGH_PASS, BAND_PASS, BAND_STOP};
double *create1TransSinc(int windowLength, double transFreq, double sampFreq, enum filterType type);

#ifdef __cplusplus
}
#endif

#endif // WINDOWKAN_H
