#ifndef SIGNALPROCESSING_H
#define SIGNALPROCESSING_H

#include <QDebug>

#include "datasetup.h"

#include "libme/fft/fourier.h"
#include "libme/windowing/buat_filter.h"
#include "libme/windowing/windowkan.h"
//#include "file_setting.h"

#include "math.h"

#define HIGHPASS_VM     6200        // 6 kHz
#define LOWPASS_VM      1500        // 1200
#define LOWPASS_P       1500        // 3.5 kHz
#define L_KERNEL        371 /* disamakan dengan haliza_13 */

class signalProcessing
{
public:
    signalProcessing();

    enum filtertype {LOW_PASS, HIGH_PASS, BAND_PASS};

    void proses_ftt(double *data_y, double *win_hanning, double *win_rect, double *win_black, double *win_hamm,
                    double *hasil_windowing, int spektrum_points, double *fft_re_out, double *fft_im_out,
                    double *fft_magt, int index);

    void gen_window_coef(struct t_setting *set, double *win_coef, int spektrum_points);
    void gen_hanning(double *out, int M);
    void gen_rectangular(double *out, int M);
    void gen_blackman(double *out, int M);
    void gen_hamming(double *out, int M);


    void gen_simple_hpf(double *data, double *filtered, float fcut_off, int numSamples, int fmax);
    void gen_buterworth_hpf(double *data, double *filtered, float f_cut_off, int numSamples, int fmax, int orde);

    void init_digital_filter(struct t_setting *setting, double * &filter_out);
    void gen_highpass(double *in, double *out, int len);
    double* create1TransSinc(int windowLength, double transFreq, double sampFreq, enum filtertype type);

private:
    double *filter_hp;
    double *filter_lp;
    double *temp_proses;
    double *filter_xx;



};

#endif // SIGNALPROCESSING_H
