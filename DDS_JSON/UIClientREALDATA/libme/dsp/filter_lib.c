#include "filter_lib.h"
#include "alokasi.h"

void siapkan_filter(int s_rate, int f_start, int f_stop, int tipe_window)
{
    printf("%s():__\r\n", __FUNCTION__);
    int i;

    //windowLength = DEF_PJG_KERNEL;
    windowLength = LEN_KERNEL_HP;

    doubledd d_start = (doubledd) f_start * 1.0;
    doubledd d_stop = (doubledd) f_stop * 1.0;
    doubledd d_rate = (doubledd) s_rate * 1.0;


    hpf_hamming = create2TransSinc( windowLength, d_start, d_stop, d_rate, BAND_PASS);

    //doubledd *hpf = create1TransSinc(windowLength, transFreq, sampFreq, HIGH_PASS);
	//doubledd *hpf = create1TransSinc(windowLength, transFreq, sampFreq, LOW_PASS);
    //hpf_hamming = createWindow2(hpf, NULL, windowLength, HAMMING);


	flag_akhir = INVALID;

#if 0
	for (i=0; i<windowLength; i++)
	{
		printf("%03d, %.20lf\n", i, (doubledd) hpf_hamming[i] );
    }
#endif
	printf("%s(): ...L %d, s_rate %d, start %d, stop %d, OK SIAP\n", \
		__FUNCTION__, windowLength, s_rate, f_start, f_stop);
}

/* input side konvolusi, lihat buku DSP Guide hal 114 */
void konvolusi2( doubledd *in, doubledd *out, doubledd *kernel, int kernel_size, int in_size, doubledd *akhiran)
{
	int outsize;
	int i, y;
	int tes = 1;

	outsize = (kernel_size + in_size) - 1;

	// zero output 
	memset( out, 0, sizeof(doubledd) * outsize);

    printf("in %.10f, k %.10f", in[tes], kernel[tes] );
	
	for (i=0; i<in_size; i++)
	{
		for (y=0; y<kernel_size; y++)
		{
			out[ i + y ] = out[ i + y ] + (in[i] * kernel[y]);
		}
	}

	//printf(", out %.10f", out[tes]);

	if (flag_akhir == VALID)
	{
		/* bagian input (depan) ditambah dengan akhiran sebelumnya */
		for (i=0; i<kernel_size; i++)
			out[i] = out[ i ] + akhiran[ i ];
	}	

	//printf(", out2 %.10f", out[tes]);
	
	int awal = in_size;
	
	// simpan bagian akhirnya
	for (i=0; i<kernel_size ; i++)
	{
		akhiran[i] = out[ awal + i ];
	} 

	//printf(", akh %.10f\n", akhiran[tes]);
	
	flag_akhir = VALID;
}

/* konvolusi output side algoritma, lihat buku DSP GUide hal 121 */
static void konvolusi_out( doubledd *in, doubledd *out, doubledd *kernel, int kernel_size, int in_size)
{
	int outsize;
	int i, y;

	outsize = (kernel_size + in_size) - 1;

	for (i=0; i<outsize; i++)
	{
		out[i] = 0;
		for (y = 0; y<kernel_size+1; y++)
		{
			if ((i - y) < 0) continue;
			//if ((i - y) > in_size) continue;
			
			out[i] = out[i] + (kernel [ y ] * in[ i - y ]);
		}
	}
}

void proses_konvolusi22(doubledd *in, doubledd *out, int size, doubledd *akhir)
{
	int i;
    konvolusi2( in, out, hpf_hamming, windowLength, size, akhir);

    //printf("%s(): %d\n", __FUNCTION__, size);

	#if 0
	// shifting 
	for (i=0; i<size; i++)
	{
		out[i] = temp_out[ i + windowLength/2 ];
	}
	#endif
}

#if 0
void konvolusi( float *in, float *out, float *kernel, int kernel_size, int in_size)
{
    int i;
    int y;

    for (i=0; i<size; i++)
    {
        for (y = 0; y < (M+1); y++ )
        {
            out[ i + y ] = out[ i + y ] + (in[ i ] * kernel[ y ]);
        }
    }
}
#endif

#if 0
int main(void)
{
	int windowLength = 201;
	doubledd sampFreq = 44100;

	// Low and high pass filters
	doubledd transFreq = 10000;

	doubledd *lpf = create1TransSinc(windowLength, transFreq, sampFreq, LOW_PASS);
	doubledd *lpf_hamming = createWindow(lpf, NULL, windowLength, HAMMING);
	doubledd *lpf_blackman = createWindow(lpf, NULL, windowLength, BLACKMAN);

	doubledd *hpf = create1TransSinc(windowLength, transFreq, sampFreq, HIGH_PASS);
	doubledd *hpf_hamming = createWindow(hpf, NULL, windowLength, HAMMING);

	outputFFT("lpf-hamming.dat", lpf_hamming, windowLength, sampFreq);
	outputFFT("lpf-blackman.dat", lpf_blackman, windowLength, sampFreq);
	outputFFT("hpf-hamming.dat", hpf_hamming, windowLength, sampFreq);

	// Band pass and band stop filters
	doubledd trans1Freq = 5000;
	doubledd trans2Freq = 17050;

	doubledd *bpf = create2TransSinc(windowLength, trans1Freq, trans2Freq, sampFreq, BAND_PASS);
	doubledd *bpf_hamming = createWindow(bpf, NULL, windowLength, HAMMING);

	doubledd *bsf = create2TransSinc(windowLength, trans1Freq, trans2Freq, sampFreq, BAND_STOP);
	doubledd *bsf_hamming = createWindow(bsf, NULL, windowLength, HAMMING);

	outputFFT("bpf-hamming.dat", bpf_hamming, windowLength, sampFreq);
	outputFFT("bsf-hamming.dat", bsf_hamming, windowLength, sampFreq);

	// Kaiser Window
	int kaiserWindowLength;
	doubledd beta;

	calculateKaiserParams(0.001, 800, sampFreq, &kaiserWindowLength, &beta);

	lpf = create1TransSinc(kaiserWindowLength, transFreq, sampFreq, LOW_PASS);
	doubledd *lpf_kaiser = createKaiserWindow(lpf, NULL, kaiserWindowLength, beta);

	outputFFT("lpf-kaiser.dat", lpf_kaiser, kaiserWindowLength, sampFreq);

	return 0;
}
#endif

// Create sinc function for filter with 1 transition - Low and High pass filters
doubledd *create1TransSinc(int windowLength, doubledd transFreq, doubledd sampFreq, enum filterType type)
{
	int n;

    printf("%s(): 1st %f, rate %f\r\n", __FUNCTION__, transFreq, sampFreq);

	// Allocate memory for the window
	doubledd *window = (doubledd *) malloc(windowLength * sizeof(doubledd));
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
	doubledd ft = transFreq / sampFreq;

	doubledd m_2 = 0.5 * (windowLength-1);
	int halfLength = windowLength / 2;

	// Set centre tap, if present
	// This avoids a divide by zero
	if (2*halfLength != windowLength) {
		doubledd val = 2.0 * ft;

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
		doubledd val = sin(2.0 * M_PI * ft * (n-m_2)) / (M_PI * (n-m_2));

		window[n] = val;
		window[windowLength-n-1] = val;
	}

	return window;
}

// Create two sinc functions for filter with 2 transitions - Band pass and band stop filters
doubledd *create2TransSinc(int windowLength, doubledd trans1Freq, doubledd trans2Freq, doubledd sampFreq, enum filterType type)
{
	int n;

	printf("%s(): 1st %f, 2nd %f, rate %f\r\n", __FUNCTION__, trans1Freq, trans2Freq, sampFreq);
	
	// Allocate memory for the window
	doubledd *window = (doubledd *) malloc(windowLength * sizeof(doubledd));
	//doubledd *window = &filter_kernel[0];
	if (window == NULL) {
		//fprintf(stderr, "create2TransSinc: Could not allocate memory for window\n");
		printf("create2TransSinc: Could not allocate memory for window\n");
		return NULL;
	}

	if (type != BAND_PASS && type != BAND_STOP) {
		//fprintf(stderr, 
		printf("create2TransSinc: Bad filter type, should be either BAND_PASS or BAND_STOP\n");
		return NULL;
	}

	// Calculate the normalised transistion frequencies.
	doubledd ft1 = trans1Freq / sampFreq;
	doubledd ft2 = trans2Freq / sampFreq;

	doubledd m_2 = 0.5 * (windowLength-1);
	int halfLength = windowLength / 2;

	// Set centre tap, if present
	// This avoids a divide by zero
	if (2*halfLength != windowLength) {
		doubledd val = 2.0 * (ft2 - ft1);

		// If we want a band stop filter, subtract sinc functions from a dirac pulse
		if (type == BAND_STOP) val = 1.0 - val;

		window[halfLength] = val;
	}
	else {
		//fprintf(stderr, 
		printf("create2TransSinc: For band pass and band stop filters, window length must be odd\n");
		return NULL;
	}

	// Swap transition points if Band Stop
	if (type == BAND_STOP) {
		doubledd tmp = ft1;
		ft1 = ft2; ft2 = tmp;
	}

	// Calculate taps
	// Due to symmetry, only need to calculate half the window
	for (n=0 ; n<halfLength ; n++) {
		doubledd val1 = sin(2.0 * M_PI * ft1 * (n-m_2)) / (M_PI * (n-m_2));
		doubledd val2 = sin(2.0 * M_PI * ft2 * (n-m_2)) / (M_PI * (n-m_2));

		window[n] = val2 - val1;
		window[windowLength-n-1] = val2 - val1;
	}

	return window;
}

// Create a set of window weights
// in - If not null, each value will be multiplied with the window weight
// out - The output weight values, if NULL and new array will be allocated
// windowLength - the number of weights
// windowType - The window type
doubledd *createWindow2(doubledd *in, doubledd *out, int windowLength, enum windowType type)
{
	// If output buffer has not been allocated, allocate memory now
	if (out == NULL) {
		out = (doubledd *) malloc(windowLength * sizeof(doubledd));
		if (out == NULL) {
			fprintf(stderr, "Could not allocate memory for window\n");
			return NULL;
		}
	}

	int n;
	int m = windowLength - 1;
	int halfLength = windowLength / 2;

	// Calculate taps
	// Due to symmetry, only need to calculate half the window
	switch (type)
	{
		case RECTANGULAR:
			for (n=0 ; n<windowLength ; n++) {
				out[n] = 1.0;
			}
			break;

		case BARTLETT:
			for (n=0 ; n<=halfLength ; n++) {
				doubledd tmp = (doubledd) n - (doubledd)m / 2;
				doubledd val = 1.0 - (2.0 * fabs(tmp))/m;
				out[n] = val;
				out[windowLength-n-1] = val;
			}

			break;

		case HANNING:
			for (n=0 ; n<=halfLength ; n++) {
				doubledd val = 0.5 - 0.5 * cos(2.0 * M_PI * n / m);
				out[n] = val;
				out[windowLength-n-1] = val;
			}

			break;

		case HAMMING:
			for (n=0 ; n<=halfLength ; n++) {
				doubledd val = 0.54 - 0.46 * cos(2.0 * M_PI * n / m);
				out[n] = val;
				out[windowLength-n-1] = val;
			}
			break;

		case BLACKMAN:
			for (n=0 ; n<=halfLength ; n++) {
				doubledd val = 0.42 - 0.5 * cos(2.0 * M_PI * n / m) + 0.08 * cos(4.0 * M_PI * n / m);
				out[n] = val;
				out[windowLength-n-1] = val;
			}
			break;
	}

	// If input has been given, multiply with out
	if (in != NULL) {
		for (n=0 ; n<windowLength ; n++) {
			out[n] *= in[n];
		}
	}

	return out;
}
#if 0
// Transition Width (transWidth) is given in Hz
// Sampling Frequency (sampFreq) is given in Hz
// Window Length (windowLength) will be set
void calculateKaiserParams(doubledd ripple, doubledd transWidth, doubledd sampFreq, int *windowLength, doubledd *beta)
{
	// Calculate delta w
	doubledd dw = 2 * M_PI * transWidth / sampFreq;

	// Calculate ripple dB
	doubledd a = -20.0 * log10(ripple);

	// Calculate filter order
	int m;
	if (a>21) m = ceil((a-7.95) / (2.285*dw));
	else m = ceil(5.79/dw);

	*windowLength = m + 1;

	if (a<=21) *beta = 0.0;
	else if (a<=50) *beta = 0.5842 * pow(a-21, 0.4) + 0.07886 * (a-21);
	else *beta = 0.1102 * (a-8.7);
}

doubledd *createKaiserWindow(doubledd *in, doubledd *out, int windowLength, doubledd beta)
{
	doubledd m_2 = (doubledd)(windowLength-1) / 2.0;
	doubledd denom = modZeroBessel(beta);					// Denominator of Kaiser function

	// If output buffer has not been allocated, allocate memory now
	if (out == NULL) {
		out = (doubledd *) malloc(windowLength * sizeof(doubledd));
		if (out == NULL) {
			fprintf(stderr, "Could not allocate memory for window\n");
			return NULL;
		}
	}

	int n;
	for (n=0 ; n<windowLength ; n++)
	{
		doubledd val = ((n) - m_2) / m_2;
		val = 1 - (val * val);
		out[n] = modZeroBessel(beta * sqrt(val)) / denom;
	}

	// If input has been given, multiply with out
	if (in != NULL) {
		for (n=0 ; n<windowLength ; n++) {
			out[n] *= in[n];
		}
	}

	return out;
}

doubledd modZeroBessel(doubledd x)
{
	int i;

	doubledd x_2 = x/2;
	doubledd num = 1;
	doubledd fact = 1;
	doubledd result = 1;

	for (i=1 ; i<20 ; i++) {
		num *= x_2 * x_2;
		fact *= i;
		result += num / (fact * fact);
//		printf("%f %f %f\n", num, fact, result);
	}

	return result;
}
#endif

#if 0
/* ini untuk mengetahui respon filter saja */
int outputFFT(char *filename, doubledd *window, int windowLength, doubledd sampFreq)
{	
	int i;
	FILE *fp;
	doubledd *in;
	fftw_complex *out;
	fftw_plan plan;
	int result = 0;

	// If the window length is short, zero padding will be used
	int fftSize = (windowLength < 2048) ? 2048 : windowLength;

	// Calculate size of result data
	int resultSize = (fftSize / 2) + 1;

	// Allocate memory to hold input and output data
	in = (doubledd *) fftwf_malloc(fftSize * sizeof(doubledd));
	out = (fftw_complex *) fftwf_malloc(resultSize * sizeof(fftw_complex));
	if (in == NULL || out == NULL) {
		result = 1;
		fprintf(stderr, "outputFFT: Could not allocate input/output data\n");
		goto finalise;
	}

	// Create the plan and check for success
	plan = fftwf_plan_dft_r2c_1d(fftSize, in, out, FFTW_MEASURE); 
	if (plan == NULL) {
		result = 1;
		fprintf(stderr, "outputFFT: Could not create plan\n");
		goto finalise;
	}

	// Copy window and add zero padding (if required)
	for (i=0 ; i<windowLength ; i++) in[i] = window[i];
	for ( ; i<fftSize ; i++) in[i] = 0;
	
	// Perform fft
	fftwf_execute(plan);

	// Open file for writing
	fp = fopen(filename, "w");
	if (fp == NULL) {
		result = 1;
		fprintf(stderr, "outputFFT: Could open output file for writing\n");
		goto finalise;
	}

	// Output result
	for (i=0 ; i<resultSize ; i++)
	{
		doubledd freq = sampFreq * i / fftSize;
		doubledd mag = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
		doubledd magdB = 20 * log10(mag);
		doubledd phase = atan2(out[i][1], out[i][0]);
		fprintf(fp, "%02d %f %f %f %f\n", i, freq, mag, magdB, phase);
	}

	// Perform any cleaning up
	finalise:
	if (plan != NULL) fftwf_destroy_plan(plan);
	if (in != NULL) fftwf_free(in);
	if (out != NULL) fftwf_free(out);
	if (fp != NULL) fclose(fp);

	return result;
}
#endif

#if 0
doubledd * buat_filter_FFT(doubledd *window, int windowLength, doubledd sampFreq)
{	
	int i;
	fftw_complex *out;
	fftw_plan plan;
	doubledd *in;
	doubledd *out_kernel;
	int result = 0;

	// If the window length is short, zero padding will be used
	int fftSize = (windowLength < 2048) ? 2048 : windowLength;

	// Calculate size of result data
	int resultSize = (fftSize / 2) + 1;

	printf("%s(): fft_size %d, result %d\n", __FUNCTION__, fftSize, resultSize);

	#if 1
	// Allocate memory to hold input and output data
	in = (doubledd *) fftwf_malloc(fftSize * sizeof(doubledd));
	out = (fftw_complex *) fftwf_malloc(resultSize * sizeof(fftw_complex));
	out_kernel = (doubledd *) fftwf_malloc(resultSize * sizeof(doubledd));

	if (in == NULL || out == NULL || out_kernel) 
	{
		result = 1;
		fprintf(stderr, "outputFFT: Could not allocate input/output data\n");
		goto finalise;
	}
	#endif
	

	// Create the plan and check for success
	plan = fftwf_plan_dft_r2c_1d(fftSize, in, out, FFTW_MEASURE); 
	if (plan == NULL) {
		result = 1;
		fprintf(stderr, "outputFFT: Could not create plan\n");
		goto finalise;
	}

	// Copy window and add zero padding (if required)
	for (i=0 ; i<windowLength ; i++) 
		in[i] = window[i];

	for ( ; i<fftSize ; i++) in[i] = 0;
	
	// Perform fft
	fftwf_execute(plan);

	// Output result
	for (i=0 ; i<resultSize ; i++)
	{
		doubledd freq = sampFreq * i / fftSize;
		doubledd mag = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
		//doubledd magdB = 20 * log10(mag);
		//doubledd phase = atan2(out[i][1], out[i][0]);
		//fprintf(fp, "%02d %f %f %f %f\n", i, freq, mag, magdB, phase);

		out_kernel[i] = mag;
	}

	// Perform any cleaning up
	finalise:
	if (plan != NULL) fftwf_destroy_plan(plan);
	if (in != NULL) fftwf_free(in);
	if (out != NULL) fftwf_free(out);
	//if (fp != NULL) fclose(fp);

	return out_kernel;
	//return result;
}
#endif
