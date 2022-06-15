#include "signalprocessing.h"


static int buffer_siap = 0;
static int len_highpass = 0;

#define LEN_BUFFER_PROSES   (1024 * 1024)

signalProcessing::signalProcessing()
{

}

void signalProcessing::proses_ftt(double *data_y, double *win_hanning, double *win_rect, double *win_black, double *win_hamm,
                                  double *hasil_windowing, int spektrum_points, double *fft_re_out, double *fft_im_out,
                                  double *fft_magt, int index){
}

void signalProcessing::gen_window_coef(t_setting *set, double *win_coef, int spektrum_points){
    switch (set->spek.window){
    case 0:
        gen_hanning(win_coef, spektrum_points);
        break;
    case 1:
        gen_rectangular(win_coef, spektrum_points);
        break;
    case 2:
        gen_blackman(win_coef, spektrum_points);
        break;
    default:
        gen_hamming(win_coef, spektrum_points);
        break;
    }
}

/* ------------------------------------------ GEN_WINDOW ----------------------------------------- */
void signalProcessing::gen_hanning(double *out, int M){
    int i;

    /* kompensasi hanning = 8/3 = 1.63 */
    for (i=0; i<= M; i++)
    {
        //out[i] = (1.63) * (0.50 - (0.50 * cos ( 2 * M_PI * i / M ))); //ini juga ga usah dikasih nilai kompensasi dlu ki
        out[i] = (0.50 - (0.50 * cos ( 2 * M_PI * i / M )));
    }
}

void signalProcessing::gen_rectangular(double *out, int M){
    int i;

    for (i=0; i<= M; i++)
    {
        out[i] = 1.00;
    }
}

void signalProcessing::gen_blackman(double *out, int M){
    int i;

    for (i=0; i<= M; i++)
    {
        out[i] = 0.42 - (0.5 * cos ( 2 * M_PI * i / M )) + (0.08 * cos (4 * M_PI * i / M));
    }
}

void signalProcessing::gen_hamming(double *out, int M){
    int i;

    for (i=0; i<= M; i++)
    {
        out[i] = 0.54 - (0.46 * cos ( 2 * M_PI * i / M ));
    }
}



/* ----------------------------------------- FILTER DIGITAL --------------------------------------*/
/* -------------- HIGH_PASS_FILTER -------------- */
void signalProcessing::gen_simple_hpf(double *data, double *filtered, float fcut_off, int numSamples, int fmax){
    double RC    = (double) (1.00 / ((double) fcut_off * 2.00 * 3.14));
    double dt    = (double) (1.00 / (double) fmax);
    double alpha = (double) (RC / (RC + dt));

    filtered[0] = data[0];

    for (int i = 1; i < numSamples; i++){
        filtered[i] = (double) alpha * ((double) filtered[i-1] + (double) data[i] - (double) data[i-1]);
    }

}

void signalProcessing::gen_buterworth_hpf(double *data, double *filtered, float f_cut_off, int numSamples, int fmax, int orde){
    double s;
    double a =  (double) tan(M_PI * ((double) f_cut_off / (double) fmax));
    double a2 = a * a;
    double x;

    double *A = (double *) malloc (orde * sizeof(double));
    memset((double *) A, 0, orde * sizeof(double));

    double *d1 = (double *) malloc (orde * sizeof(double));
    memset((double *) d1, 0, orde * sizeof(double));

    double *d2 = (double *) malloc (orde * sizeof(double));
    memset((double *) d2, 0, orde * sizeof(double));

    double *w0 = (double *) malloc (orde * sizeof(double));
    memset((double *) w0, 0, orde * sizeof(double));

    double *w1 = (double *) malloc (orde * sizeof(double));
    memset((double *) w1, 0, orde * sizeof(double));

    double *w2 = (double *) malloc (orde * sizeof(double));
    memset((double *) w2, 0, orde * sizeof(double));

}

void signalProcessing::init_digital_filter(struct t_setting *setting, double* &filter_out)
{
    qDebug("%s() ==. wave enabel filter = %d",__FUNCTION__, setting->wave.en_filter);
    float f_start = (setting->wave.en_filter) ? setting->wave.f_cutoff : 1.0;
    qDebug()<< "waveform f start = "<<f_start;
//    filter_xx = new double[L_KERNEL * sizeof(double)]; //fungsi create1TransSinc menghasilkan return berupa pointer yg dialokasikan memory secara dynamic, karena filter_xx sbg wadah return fungsi create1TransSinc maka tidak perlu dialokasikan memori dulu
    filter_xx = this->create1TransSinc(L_KERNEL,f_start,setting->fmax * 2.56, HIGH_PASS);

    for (int i=0;i<L_KERNEL;i++)
        filter_out[i] = filter_xx[i];

    delete [] filter_xx;
}




void signalProcessing::gen_highpass(double *in, double *out, int len){
    qDebug("%s: len %d !", __PRETTY_FUNCTION__, len);

    /*
     * urutan proses :
     * - High_pass, pada 0.2 sampling rate, filter kernel dibuat diawal (filter_hp)
     * - Mutlakkan
     * - lowpass pada 0.04
     */

    int i, y;
    int len_baru = len + len_highpass;

    if (len_baru > LEN_BUFFER_PROSES){
        qDebug("Panjang buffer proses kurang !");
        return;
    }


    qDebug("Panjangin");
    qDebug() << "panjang baru : " << len_baru;
    /* memperpanjang sinyal dulu, ditambahkan dari ujung kirinya */
    for (i=len; i<len_baru; i++){
        in[ i ] = in[ i - len ];
    }

    memset( temp_proses, 0, (len + len_highpass) * sizeof (double));

    qDebug("mau mulai Filter");
    /*==== PROSES HIGHPASS ====*/
    for (i=0; i<len_baru; i++){
        for (y=0; y<len_highpass; y++){
            temp_proses[ i + y ] = temp_proses[ i + y ] + ( in[i] * filter_hp[y]);
        }
    }

    qDebug("balikik ke panjang awal");
    /* INI AKAN MENYEBABKAN FASA BERGESER ???
       SEKALIGUS PROSES MUTLAKKAN */
    for (i=0; i<len; i++){
        out[i] = fabs( temp_proses[i+len_highpass] );
    }
}


/* ----------------------------------------- ENTAH APA INI ---------------------------------------*/
double* signalProcessing::create1TransSinc(int windowLength, double transFreq, double sampFreq, enum filtertype type)
{
    int n;

    // Allocate memory for the window
//    double *window = (double *) malloc(windowLength * sizeof(double));
    double* window = new double[windowLength * sizeof(double)];
    if (window == NULL) {
        //fprintf(stderr, "create1TransSinc: Could not allocate memory for window\n");
        return NULL;
    }

    if (type != LOW_PASS && type != HIGH_PASS) {
        //fprintf(stderr, "create1TransSinc: Bad filter type, should be either LOW_PASS of HIGH_PASS\n");
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
        //fprintf(stderr, "create1TransSinc: For high pass filter, window length must be odd\n");
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

    return (double *) window;
}

