#ifndef WINDOW_FILTER_H
#define WINDOW_FILTER_H

//#define USE_HP

#ifdef __cplusplus
extern "C" {
#endif

#define faktor_hanning		0.5
#define faktor_hamming		0.54

void skala_window(double *out, int M, double faktor);

int buat_bandpass(double *out, int M, double fc_L, double fc_H, unsigned short kind);

double calc_rms(double *in, int n);
double digital_rms(double *in, int n);


/* ada di filter_lib.c */
//#define DEF_PJG_KERNEL      101

enum filterType {LOW_PASS, HIGH_PASS, BAND_PASS, BAND_STOP};
enum windowType {RECTANGULAR, BARTLETT, HANNING, HAMMING, BLACKMAN};

#ifdef __i386__
typedef double doubledd;
#else
typedef float doubledd;
#endif


void siapkan_filter(int s_rate, int f_start, int f_stop, int tipe_window);
void proses_konvolusi(doubledd *in, doubledd *out, int size, doubledd *akhir);
doubledd *create1TransSinc(int windowLength, doubledd transFreq, doubledd sampFreq, enum filterType type);
void konvolusi( doubledd *in, doubledd *out, doubledd *kernel, int kernel_size, int in_size, doubledd *akhiran);


/* akhir dari fungsi di filter_lib.c */

/* ada di filter_iir.c */
void hitung_koef_IIR_velocity(unsigned int srate, doubledd *p_a0, doubledd *p_b1);

#ifdef __cplusplus
}
#endif

#endif // WINDOW_FILTER_H
