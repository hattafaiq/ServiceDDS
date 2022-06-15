
/*
 testing beberapa filter dan plot
 18 des 06, furkan jadid
 daun biru engineering

 buat filter akan menaruh filter kernel di awal_filt_kernel
 untuk sementara filter adalah blackman

 saat akan dipakai, filter_kernel akan dicopy menjadi fraksional ke fast_buf

 ADC sementara masih mode pooling

 24 mar 09, furkan jadid
 porting ke GCC & FreeRTOS

    3 Des 2012
    dipakai untuk qt_simul

 */

#include <float.h>
#include <math.h>
#include <stdio.h> 
#include <stdlib.h>

#include "buat_filter.h"

void fft_float (
    unsigned  NumSamples,
    int       InverseTransform,
    float    *RealIn,
    float    *ImagIn,
    float    *RealOut,
    float    *ImagOut );

#define BESAR_FILTER	(1024)			/* 9 Mei 2011, filter hanya 512 */

float filter_kernel[BESAR_FILTER];
float filter_kernel2[BESAR_FILTER];

void buat_bandpass(int M, float fc, float fc_H, unsigned short kind)
{
    /*	lihat buku DSP Guide bab 16 hal 294
  fc adalah cut off, antara 0 sampai 0.5
  M panjang filter

  20 desember 2006, supaya kompatible dengan 5P, kind :
  1. hanning
  2. rectangular
  3. blackman
  4. hamming

  fc adalah low pass cut off
  fcH adalah high pass cut off

  fc harus > fcH
  */

    int i;
    double sum;
    int Mper2;

    //printf("%s(): jum %d, fc %f, fc_H %f, kind %d\r\n", __FUNCTION__, M, fc, fc_H, kind);

    Mper2 = M/2;

    for (i=0; i<(M+1); i++)
    {
        filter_kernel[i] = 0.00;
        filter_kernel2[i] = 0.00;
    }
    //* buat filter kernel LOW PASS
    if (kind == 1)		//hanning
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel[i] = (float) 2*M_PI*fc;
            }
            else
            {
                filter_kernel[i] = (float)sin(2*M_PI*fc*(i-Mper2))/(i-Mper2);
            }
            filter_kernel[i]=filter_kernel[i]*(0.5-0.5*cos(2 * M_PI * i /M));
        }
    }
    else if (kind == 2)		//rectangular
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel[i] = (float) 2*M_PI*fc;
            }
            else
            {
                filter_kernel[i] = (float)sin(2*M_PI*fc*(i-Mper2))/(i-Mper2);
            }
            filter_kernel[i]=filter_kernel[i]*(0.5-0.5*cos(2 * M_PI * i /M));
        }
    }
    else if (kind == 3)		//blackman
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel[i] = (float) 2*M_PI*fc;
            }
            else
            {
                filter_kernel[i] = (float)sin(2*M_PI*fc*(i-Mper2))/(i-Mper2);
            }
            filter_kernel[i]=filter_kernel[i]*(0.42-0.5*cos(2 * M_PI * i /M) + 0.08 * cos (4 * M_PI * i /M));
        }
    }
    else if (kind == 4)	//hamming
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel[i] = (float) 2*M_PI*fc;
            }
            else
            {
                filter_kernel[i] = (float)sin(2*M_PI*fc*(i-Mper2))/(i-Mper2);
            }
            filter_kernel[i]=filter_kernel[i]*(0.54-0.46*cos(2 * M_PI * i /M));
        }
    }

    sum = 0;
    // normalisasi kernel
    for (i=0; i<M+1; i++)
    {
        sum = sum + filter_kernel[i];
    }

    for (i=0; i<M+1; i++)
    {
        filter_kernel[i]=filter_kernel[i]/sum;
    }

    /* hitung low-pass filter yang kedua sebalum diubah menjadi high pass */

    if (kind == 1)		//hanning
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel2[i] = (float) 2*M_PI*fc_H;
            }
            else
            {
                filter_kernel2[i] = (float)sin(2*M_PI*fc_H*(i-Mper2))/(i-Mper2);
            }
            filter_kernel2[i]=filter_kernel2[i]*(0.5-0.5*cos(2 * M_PI * i /M));
        }
    }
    else if (kind == 2)		//rectangular
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel2[i] = (float) 2*M_PI*fc_H;
            }
            else
            {
                filter_kernel2[i] = (float)sin(2*M_PI*fc_H*(i-Mper2))/(i-Mper2);
            }
            filter_kernel[i]=filter_kernel[i]*(0.5-0.5*cos(2 * M_PI * i /M));
        }
    }
    else if (kind == 3)		//blackman
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel2[i] = (float) 2*M_PI*fc_H;
            }
            else
            {
                filter_kernel2[i] = (float)sin(2*M_PI*fc_H*(i-Mper2))/(i-Mper2);
            }
            filter_kernel2[i]=filter_kernel2[i]*(0.42-0.5*cos(2 * M_PI * i /M) + 0.08 * cos (4 * M_PI * i /M));
        }
    }
    else if (kind == 4)	//hamming
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel2[i] = (float) 2*M_PI*fc_H;
            }
            else
            {
                filter_kernel2[i] = (float)sin(2*M_PI*fc_H*(i-Mper2))/(i-Mper2);
            }
            filter_kernel2[i]=filter_kernel2[i]*(0.54-0.46*cos(2 * M_PI * i /M));
        }
    }

    sum = 0;
    // normalisasi kernel
    for (i=0; i<M+1; i++)
    {
        sum = sum + filter_kernel2[i];
    }

    for (i=0; i<M+1; i++)
    {
        filter_kernel2[i]=filter_kernel2[i]/sum;
    }
    //selesai menyiapkan high pass


    /* mengubah kernel yang kedua menjadi high pass sebagaimana pada gambar 14.5
      dan program 16.2 halaman 295 */
    for (i=0; i<M+1; i++)
    {
        filter_kernel2[i] = -1 * filter_kernel2[i];
    }
    filter_kernel2[Mper2] = filter_kernel2[Mper2] + 1;

    /* untuk mendapatkan band reject, tambahkan filter 1 dan filter 2*/
    for (i=0; i<M+1; i++)
    {
        //H_kernel[i] = filt_kernel1[i] + filt_kernel2[i];
        filter_kernel[i] = filter_kernel[i] + filter_kernel2[i];
    }

    /* untuk mendapatkan band pass, maka diubah */
    for (i=0; i<M+1; i++)
    {
        filter_kernel[i] = -1 * filter_kernel[i];
    }
    filter_kernel[Mper2] = filter_kernel[Mper2] + 1;

    /* konvolusi
   for (i=M ; i<(jum+M); i++)
   {
      out[i] = 0;
      for (k=0; k<M+1; k++)
      {
         out[i] = out[i] + ini[i-k]*H_kernel[k];
      }
   }*/

}

/* generate low pass filter */
void buat_filter(int M, float fc, unsigned short kind)
{
    /*
  lihat buku DSP Guide bab 16 hal 294
  fc adalah cut off, antara 0 sampai 0.5
  M panjang filter

  20 desember 2006, supaya kompatible dengan 5P, kind :
  1. hanning
  2. rectangular
  3. blackman
  4. hamming

  fc diperoleh dari frekuensi_diinginkan/sampling_rate_sekarang

  filter kernel harus ganjil
  misalnya 5, karena harus center di 3 (tengah)
  kernel 0 dan 5 akan sama nilainya

 */

    int i;
    double sum;
    int Mper2;

    //printf("%s(): jum %d, fc %f, kind %d\r\n", __FUNCTION__, M, fc, kind);

    Mper2 = M/2;

    for (i=0; i<(M+1); i++)
        filter_kernel[i] = 0.00;

    //* buat filter kernel
    if (kind == 1)		//hanning
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel[i] = (float) 2*M_PI*fc;
            }
            else
            {
                filter_kernel[i] = (float)sin(2*M_PI*fc*(i-Mper2))/(i-Mper2);
            }
            filter_kernel[i]=filter_kernel[i]*(0.5-0.5*cos(2 * M_PI * i /M));
        }
    }
    else if (kind == 2)		//rectangular
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel[i] = (float) 2*M_PI*fc;
            }
            else
            {
                filter_kernel[i] = (float)sin(2*M_PI*fc*(i-Mper2))/(i-Mper2);
            }
            filter_kernel[i]=filter_kernel[i]*(0.5-0.5*cos(2 * M_PI * i /M));
        }
    }
    else if (kind == 3) //blackman
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel[i] = (float) 2*M_PI*fc;
            }
            else
            {
                filter_kernel[i] = (float)sin(2*M_PI*fc*(i-Mper2))/(i-Mper2);
            }
            filter_kernel[i]=filter_kernel[i]*(0.42-0.5*cos(2 * M_PI * i /M) + 0.08 * cos (4 * M_PI * i /M));
        }
    }
    else if (kind == 4)	//hamming
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel[i] = (float) 2*M_PI*fc;
            }
            else
            {
                filter_kernel[i] = (float)sin(2*M_PI*fc*(i-Mper2))/(i-Mper2);
            }
            filter_kernel[i]=filter_kernel[i]*(0.54-0.46*cos(2 * M_PI * i /M));
        }
    }

    sum = 0;
    // normalisasi kernel
    for (i=0; i<M+1; i++)
    {
        sum = sum + filter_kernel[i];
    }

    for (i=0; i<M+1; i++)
    {
        filter_kernel[i]=filter_kernel[i]/sum;
    }
}

void buat_highpass(int M, float fc, unsigned short kind)
{
    int i;
    int Mper2;

    Mper2 = M/2;

    /* langsung pakai saja yang low pass */
    buat_filter(M, fc, kind);

    /* mengubah kernel menjadi high pass sebagaimana pada gambar 14.5
      dan program 16.2 halaman 295 */
    for (i=0; i<M+1; i++)
    {
        filter_kernel[i] = -1 * filter_kernel[i];
    }

    filter_kernel[Mper2] = filter_kernel[Mper2] + 1;
}

/* 
 30 agt 2009

 */
#if 0
void konvolusi( float *in, float *out, float *kernel, int M, int size)
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

/* mean adalah nilai tengah, atau DC component */
float meanf_ku(float *masuk, int jum)
{
    int i;
    double sum = 0.0;

    for (i=0; i<jum; i++)
    {
        sum = sum + masuk[i];
    }

    sum = sum / jum;
    return (float) sum;
}

/* ukur porsi AC saja */
float rmsf_ku22(float *masuk, int jum)
{
    int i;
    float temp=0.0;
    float mean;

    mean = meanf_ku(masuk, jum);

    for (i=0; i<jum; i++)
    {
        //temp = temp + (masuk[i] * masuk[i]);
        temp = temp + ((masuk[i] - mean) * (masuk[i] - mean));
    }
    temp = (float) (temp/jum);

    temp = sqrtf(temp);
    return temp;
}

/* dengan running statistik */
float rmsf2_ku(float *masuk, int jum)
{
    int i;

    for (i=0; i<jum; i++)
    {

    }
}

float maksf_ku(float *masuk, int jum)
{
    int i;
    float maks = 0;

    for (i=0; i<jum; i++)
    {
        if (masuk [i] > maks) maks = masuk [i];
    }

    return maks;
}

float minf_ku(float *masuk, int jum)
{
    int i;
    float min = 1000000.00;

    for (i=0; i<jum; i++)
    {
        if (masuk [i] < min) min = masuk [i];
    }

    return min;
}


/* 	9 Sept 2009
 * 	buat window sebelum dipakai untuk fft */
void buat_hanning(float *out, int M)
{
    int i;

    for (i=0; i<= M; i++)
    {
        out[i] = 0.50 - (0.50 * cos ( 2 * M_PI * i / M ));
    }
}

void buat_hamming(float *out, int M)
{
    int i;

    for (i=0; i<= M; i++)
    {
        out[i] = 0.54 - (0.46 * cos ( 2 * M_PI * i / M ));
    }
}

void buat_blackman(float *out, int M)
{
    int i;
    //0.42 - 0.5 cos (2B i / M ) + 0.08 cos (4B i / M )
    for (i=0; i<= M; i++)
    {
        out[i] = 0.42 - (0.5 * cos ( 2 * M_PI * i / M )) + (0.08 * cos (4 * M_PI * i / M));
    }
}

void buat_rectangular(float *out, int M)
{
    int i;

    for (i=0; i<= M; i++)
    {
        out[i] = 1.00;
    }
}

/* type data double */
void buat_hanningd(double *out, int M)
{
    int i;
    /* 1.63 --> nilai kompensasi Hanning */

    for (i=0; i<= M; i++)
    {
        out[i] = (1.63) * (0.50 - (0.50 * cos ( 2 * M_PI * i / M )));
    }
}

void buat_hammingd(double *out, int M)
{
    int i;

    for (i=0; i<= M; i++)
    {
        out[i] = 0.54 - (0.46 * cos ( 2 * M_PI * i / M ));
    }
}

void buat_blackmand(double *out, int M)
{
    int i;
    //0.42 - 0.5 cos (2B i / M ) + 0.08 cos (4B i / M )
    for (i=0; i<= M; i++)
    {
        out[i] = 0.42 - (0.5 * cos ( 2 * M_PI * i / M )) + (0.08 * cos (4 * M_PI * i / M));
    }
}

void buat_rectangulard(double *out, int M)
{
    int i;

    for (i=0; i<= M; i++)
    {
        out[i] = 1.00;
    }
}

/* 
 * buat low pass filter dengan karakteristik 
 * untuk mendapatkan velocity 6 dB / Octave roll off
 * 
 * Lihat Bab 17
 * 
 * secara mudah dijelaskan :
 * 		buat respon yang dikehendaki
 * 		inverse fft
 * 	
 */
#if 0
void buat_velocity(float *out, int M)
{
    int i;
    int index;
    int p_desain;

    float *real_in;
    float *image_in;
    float *real_out;
    float *image_out;
    float sum;

    /*
  * panjang filter rencana misalnya 3 * M
  * 		2 x untuk iFFT
  * 		4 x untuk float
  * 		3 x untuk panjang desain 3 x M
  */
    p_desain = 2 * 4 * M;

    real_in = (float *) malloc(p_desain * 4);
    image_in = (float *) malloc(p_desain * 4);
    real_out = (float *) malloc(p_desain * 4);
    image_out = (float *) malloc(p_desain * 4);

    for (i=0; i<= p_desain; i++)
    {
        real_in[i] = 0.00;
        image_in[i] = 0.00;
    }

    /* diisi dengan respon filter dikehendaki */
    for (i=1; i<= (p_desain/2); i++)
    {
        //real_in[i] = (float) (2.00 * M_PI * 512) / (2.00 * M_PI * i);
        real_in[i] = (float) 1.0 / (2 * M_PI * i);
        image_in[i] = 0.00;
    }
    real_in[0] = 1.0;
    image_in[0] = 0.00;

    /* inverse FFT, sebanyak 2 x desain filter */
    fft_float( p_desain, 1, real_in, image_in, real_out, image_out);

    /* rotate */
    for (i=0; i< p_desain ; i++)
    {
        index = i + (M / 2);
        if (index > p_desain ) index = index - (p_desain + 1);

        /* variable image_in dipinjam */
        image_in[index] = real_out[i];
    }

    sum = 0;
    /* window signal */
    for (i=0; i<= M ; i++)
    {
        out[i] = image_in[i] * (0.54 - 0.46 * cos(2 * M_PI * i / M));
        sum = sum + out[i];
    }

    /* normalisasi kernel */
    for (i=0; i<= M ; i++)
    {
        out[i] = out[i] / sum;
    }

}
#endif

#if 0
/*
	testing beberapa filter dan plot
	18 des 06, furkan jadid
	daun biru engineering
	
	buat filter akan menaruh filter kernel di awal_filt_kernel
	untuk sementara filter adalah blackman
	
	saat akan dipakai, filter_kernel akan dicopy menjadi fraksional ke fast_buf
	
	ADC sementara masih mode pooling
	
	24 mar 09, furkan jadid
	porting ke GCC & FreeRTOS

    3 Des 2012
    dipakai untuk qt_simul

    float diganti dengan double
	
	*/

#include <float.h>
#include <math.h>
#include <stdio.h> 
#include <stdlib.h>

#include "buat_filter.h"

//typedef double dfloat;

void fft_dfloat (
    unsigned  NumSamples,
    int       InverseTransform,
    dfloat    *RealIn,
    dfloat    *ImagIn,
    dfloat    *RealOut,
    dfloat    *ImagOut );

#define BESAR_FILTER	(1024)			/* 9 Mei 2011, filter hanya 512 */

//dfloat filter_kernel[BESAR_FILTER];
//dfloat filter_kernel2[BESAR_FILTER];

//dfloat *filter_kernel;
//dfloat *filter_kernel2;

void init_kernel(int M)
{
    int i;

    filter_kernel = (dfloat *) malloc( (M + 5) * sizeof(dfloat));
    filter_kernel2 = (dfloat *) malloc( (M + 5) * sizeof(dfloat));

    for (i=0; i<M+5; i++)
    {
        filter_kernel[i] = 0.00;
        filter_kernel2[i] = 0.00;
    }
}

void buat_bandpass(int M, dfloat fc, dfloat fc_H, unsigned short kind, dfloat *out)
{
	/*	lihat buku DSP Guide bab 16 hal 294
		fc adalah cut off, antara 0 sampai 0.5
		M panjang filter
	
		20 desember 2006, supaya kompatible dengan 5P, kind :		
		1. hanning
		2. rectangular
		3. blackman
		4. hamming
		
		fc adalah low pass cut off
		fcH adalah high pass cut off
		
		fc harus > fcH
		*/
	
	int i;
	double sum;
	int Mper2;

    init_kernel( M );

    printf("%s(): jum %d, fc %f, fc_H %f, kind %d\r\n", __FUNCTION__, M, fc, fc_H, kind);
	
	Mper2 = M/2;	
	
	for (i=0; i<(M+1); i++)
	{
		filter_kernel[i] = 0.00;
		filter_kernel2[i] = 0.00;
	}
	//* buat filter kernel LOW PASS
	if (kind == 1)		//hanning
	{	
		for (i=0; i<M+1; i++)
		{
			if ((i-Mper2) == 0)
			{
                filter_kernel[i] = (dfloat) 2*M_PI*fc;
			}
			else
			{
                filter_kernel[i] = (dfloat)sin(2*M_PI*fc*(i-Mper2))/(i-Mper2);
			}
			filter_kernel[i]=filter_kernel[i]*(0.5-0.5*cos(2 * M_PI * i /M));
		} 
	}
	else if (kind == 2)		//rectangular
	{	
		for (i=0; i<M+1; i++)
		{
			if ((i-Mper2) == 0)
			{
                filter_kernel[i] = (dfloat) 2*M_PI*fc;
			}
			else
			{
                filter_kernel[i] = (dfloat)sin(2*M_PI*fc*(i-Mper2))/(i-Mper2);
			}
			filter_kernel[i]=filter_kernel[i]*(0.5-0.5*cos(2 * M_PI * i /M));
		} 
	}
	else if (kind == 3)		//blackman
	{	
		for (i=0; i<M+1; i++)
		{
			if ((i-Mper2) == 0)
			{
                filter_kernel[i] = (dfloat) 2*M_PI*fc;
			}
			else
			{
                filter_kernel[i] = (dfloat)sin(2*M_PI*fc*(i-Mper2))/(i-Mper2);
			}
			filter_kernel[i]=filter_kernel[i]*(0.42-0.5*cos(2 * M_PI * i /M) + 0.08 * cos (4 * M_PI * i /M));
		} 
	}
	else if (kind == 4)	//hamming
	{	
		for (i=0; i<M+1; i++)
		{
			if ((i-Mper2) == 0)
			{
                filter_kernel[i] = (dfloat) 2*M_PI*fc;
			}
			else
			{
                filter_kernel[i] = (dfloat)sin(2*M_PI*fc*(i-Mper2))/(i-Mper2);
			}
			filter_kernel[i]=filter_kernel[i]*(0.54-0.46*cos(2 * M_PI * i /M));
		} 
	}
	
	sum = 0;
	// normalisasi kernel 
	for (i=0; i<M+1; i++)
	{
      sum = sum + filter_kernel[i];
	}

	for (i=0; i<M+1; i++)
	{
		filter_kernel[i]=filter_kernel[i]/sum;
	}	
   
	/* hitung low-pass filter yang kedua sebalum diubah menjadi high pass */
   
	if (kind == 1)		//hanning
	{	
		for (i=0; i<M+1; i++)
		{	
			if ((i-Mper2) == 0)
			{
                filter_kernel2[i] = (dfloat) 2*M_PI*fc_H;
			}
			else
			{
                filter_kernel2[i] = (dfloat)sin(2*M_PI*fc_H*(i-Mper2))/(i-Mper2);
			}
			filter_kernel2[i]=filter_kernel2[i]*(0.5-0.5*cos(2 * M_PI * i /M));
		} 
	}
	else if (kind == 2)		//rectangular
	{	
		for (i=0; i<M+1; i++)
		{
			if ((i-Mper2) == 0)
			{
                filter_kernel2[i] = (dfloat) 2*M_PI*fc_H;
			}
			else
			{
                filter_kernel2[i] = (dfloat)sin(2*M_PI*fc_H*(i-Mper2))/(i-Mper2);
			}
			filter_kernel[i]=filter_kernel[i]*(0.5-0.5*cos(2 * M_PI * i /M));
		} 
	}
	else if (kind == 3)		//blackman
	{	
		for (i=0; i<M+1; i++)
		{
			if ((i-Mper2) == 0)
			{
                filter_kernel2[i] = (dfloat) 2*M_PI*fc_H;
			}
			else
			{
                filter_kernel2[i] = (dfloat)sin(2*M_PI*fc_H*(i-Mper2))/(i-Mper2);
			}
			filter_kernel2[i]=filter_kernel2[i]*(0.42-0.5*cos(2 * M_PI * i /M) + 0.08 * cos (4 * M_PI * i /M));
		} 
	}
	else if (kind == 4)	//hamming
	{	
		for (i=0; i<M+1; i++)
		{
			if ((i-Mper2) == 0)
			{
                filter_kernel2[i] = (dfloat) 2*M_PI*fc_H;
			}
			else
			{
                filter_kernel2[i] = (dfloat)sin(2*M_PI*fc_H*(i-Mper2))/(i-Mper2);
			}
			filter_kernel2[i]=filter_kernel2[i]*(0.54-0.46*cos(2 * M_PI * i /M));
		} 
	}
	
	sum = 0;
	// normalisasi kernel 
	for (i=0; i<M+1; i++)
	{
      sum = sum + filter_kernel2[i];
	}

	for (i=0; i<M+1; i++)
	{
      filter_kernel2[i]=filter_kernel2[i]/sum;
	}
	//selesai menyiapkan high pass
   
   
   /* mengubah kernel yang kedua menjadi high pass sebagaimana pada gambar 14.5
      dan program 16.2 halaman 295 */
   for (i=0; i<M+1; i++)
   {
      filter_kernel2[i] = -1 * filter_kernel2[i];
   }
   filter_kernel2[Mper2] = filter_kernel2[Mper2] + 1;

   /* untuk mendapatkan band reject, tambahkan filter 1 dan filter 2*/
   for (i=0; i<M+1; i++)
   {
      //H_kernel[i] = filt_kernel1[i] + filt_kernel2[i];
      filter_kernel[i] = filter_kernel[i] + filter_kernel2[i];
   }

   /* untuk mendapatkan band pass, maka diubah */
   for (i=0; i<M+1; i++)
   {
      filter_kernel[i] = -1 * filter_kernel[i];
   }
   filter_kernel[Mper2] = filter_kernel[Mper2] + 1;

   for (i=0; i<M+1; i++)
   {
        out[i] = filter_kernel[i];
   }
   /* konvolusi 
   for (i=M ; i<(jum+M); i++)
   {
      out[i] = 0;
      for (k=0; k<M+1; k++)
      {
         out[i] = out[i] + ini[i-k]*H_kernel[k];
      }
   }*/
   
}

/* generate low pass filter */
void buat_filter(int M, dfloat fc, unsigned short kind, dfloat *out)
{
	/*	
		lihat buku DSP Guide bab 16 hal 294
		fc adalah cut off, antara 0 sampai 0.5
		M panjang filter
	
		20 desember 2006, supaya kompatible dengan 5P, kind :		
		1. hanning
		2. rectangular
		3. blackman
		4. hamming
		
		fc diperoleh dari frekuensi_diinginkan/sampling_rate_sekarang
		
		filter kernel harus ganjil
		misalnya 5, karena harus center di 3 (tengah)
		kernel 0 dan 5 akan sama nilainya
		
	*/
	
	int i;
	double sum;
	int Mper2;

    init_kernel( M );
    //printf("%s(): jum %d, fc %f, kind %d\r\n", __FUNCTION__, M, fc, kind);
	
	Mper2 = M/2;
	
	for (i=0; i<(M+1); i++)
		filter_kernel[i] = 0.00;
	
	//* buat filter kernel 
	if (kind == 1)		//hanning
	{	
		for (i=0; i<M+1; i++)
		{
			if ((i-Mper2) == 0)
			{
                filter_kernel[i] = (dfloat) 2*M_PI*fc;
			}
			else
			{
                filter_kernel[i] = (dfloat)sin(2*M_PI*fc*(i-Mper2))/(i-Mper2);
			}
			filter_kernel[i]=filter_kernel[i]*(0.5-0.5*cos(2 * M_PI * i /M));
		} 
	}
	else if (kind == 2)		//rectangular
	{	
		for (i=0; i<M+1; i++)
		{
			if ((i-Mper2) == 0)
			{
                filter_kernel[i] = (dfloat) 2*M_PI*fc;
			}
			else
			{
                filter_kernel[i] = (dfloat)sin(2*M_PI*fc*(i-Mper2))/(i-Mper2);
			}
			filter_kernel[i]=filter_kernel[i]*(0.5-0.5*cos(2 * M_PI * i /M));
		} 
	}
	else if (kind == 3)		//blackman
	{	
		for (i=0; i<M+1; i++)
		{
			if ((i-Mper2) == 0)
			{
                filter_kernel[i] = (dfloat) 2*M_PI*fc;
			}
			else
			{
                filter_kernel[i] = (dfloat)sin(2*M_PI*fc*(i-Mper2))/(i-Mper2);
			}
			filter_kernel[i]=filter_kernel[i]*(0.42-0.5*cos(2 * M_PI * i /M) + 0.08 * cos (4 * M_PI * i /M));
		} 
	}
	else if (kind == 4)	//hamming
	{	
		for (i=0; i<M+1; i++)
		{
			if ((i-Mper2) == 0)
			{
                filter_kernel[i] = (dfloat) 2*M_PI*fc;
			}
			else
			{
                filter_kernel[i] = (dfloat)sin(2*M_PI*fc*(i-Mper2))/(i-Mper2);
			}
			filter_kernel[i]=filter_kernel[i]*(0.54-0.46*cos(2 * M_PI * i /M));
		} 
	}
	
	sum = 0;
	// normalisasi kernel 
	for (i=0; i<M+1; i++)
	{
		sum = sum + filter_kernel[i];
	}

	for (i=0; i<M+1; i++)
	{	
      filter_kernel[i]=filter_kernel[i]/sum;
    }

    for (i=0; i<M+1; i++)
    {
        out[i]= filter_kernel[i];
    }
}

void buat_highpass(int M, dfloat fc, unsigned short kind, dfloat *out)
{
	int i;
	int Mper2;
	
	Mper2 = M/2;
	

	/* langsung pakai saja yang low pass */
    buat_filter(M, fc, kind, out);
	
	/* mengubah kernel menjadi high pass sebagaimana pada gambar 14.5
      dan program 16.2 halaman 295 */
	for (i=0; i<M+1; i++)
	{
		filter_kernel[i] = -1 * filter_kernel[i];
	}
	
	filter_kernel[Mper2] = filter_kernel[Mper2] + 1;

    for (i=0; i<M+1; i++)
    {
        out[i]= filter_kernel[i];
    }
}

/* 
	30 agt 2009
	
	*/
#if 1
static dfloat *run_data;

void reset_konvolusi(int M)
{
    int i;
    run_data = (dfloat *) malloc ( M * 2 * sizeof (dfloat));

    for (i=0; i<M+1; i++)
        run_data[i] = 0;
}


void konvolusi( dfloat *in, dfloat *out, dfloat *kernel, int M, int size)
{
	int i;
    int y;

    /* konvolusi output side */
    for (i=0; i<size+M; i++)
    {
        out[i] = 0;
        for (y=0; y<M; y++)
        {
            if (i>y)
            out[i] = out[i] + (kernel[y] * in[i-y]);
        }
    }
    /*
	for (i=0; i<size; i++)
	{
		for (y = 0; y < (M+1); y++ )
		{
			out[ i + y ] = out[ i + y ] + (in[ i ] * kernel[ y ]);
		}
	}

    // tambah dengan masa sebelumnya
    for (i=0; i<M/2; i++)
    {
        out[i] += run_data[i];
    }
    // simpan untuk masa datang
    for (i=0; i<M/2; i++)
    {
        run_data[i] = out[size+M/2+i];
    }*/
}
#endif

/* mean adalah nilai tengah, atau DC component */
dfloat meanf_ku(dfloat *masuk, int jum)
{
	int i;
	double sum = 0.0;
	
	for (i=0; i<jum; i++)
	{
		sum = sum + masuk[i];
	}
	
	sum = sum / jum;
    return (dfloat) sum;
}

/* ukur porsi AC saja */
dfloat rmsf_ku22(dfloat *masuk, int jum)
{
	int i;
    dfloat temp=0.0;
    dfloat mean;
	
	mean = meanf_ku(masuk, jum);
	
	for (i=0; i<jum; i++)
	{
			//temp = temp + (masuk[i] * masuk[i]);
			temp = temp + ((masuk[i] - mean) * (masuk[i] - mean));
	}
    temp = (dfloat) (temp/jum);
	
	temp = sqrtf(temp);
	return temp;
}

/* dengan running statistik */
dfloat rmsf2_ku(dfloat *masuk, int jum)
{
	int i;
	
	for (i=0; i<jum; i++)
	{
	
	
	}
}


dfloat maksf_ku(dfloat *masuk, int jum)
{
	int i;
    dfloat maks = 0;
		
	for (i=0; i<jum; i++)
	{
		if (masuk [i] > maks) maks = masuk [i];
	}

	return maks;
}

dfloat minf_ku(dfloat *masuk, int jum)
{
	int i;
    dfloat min = 1000000.00;
		
	for (i=0; i<jum; i++)
	{
		if (masuk [i] < min) min = masuk [i];
	}

	return min;
}


/* 	9 Sept 2009
 * 	buat window sebelum dipakai untuk fft */
void buat_hanning(dfloat *out, int M)
{
	int i;
	
	for (i=0; i<= M; i++)
	{
        out[i] = (dfloat) (0.5 - (0.5 * cos ( 2 * M_PI * i / M )));
	}
}

void buat_hamming(dfloat *out, int M)
{
	int i;
	
	for (i=0; i<= M; i++)
	{
		out[i] = 0.54 - (0.46 * cos ( 2 * M_PI * i / M ));
	}
}

void buat_blackman(dfloat *out, int M)
{
	int i;
	//0.42 - 0.5 cos (2B i / M ) + 0.08 cos (4B i / M )
	for (i=0; i<= M; i++)
	{
		out[i] = 0.42 - (0.5 * cos ( 2 * M_PI * i / M )) + (0.08 * cos (4 * M_PI * i / M));
	}
}

void buat_rectangular(dfloat *out, int M)
{
	int i;
	
	for (i=0; i<= M; i++)
	{
		out[i] = 1.00;
	}
}

/* 
 * buat low pass filter dengan karakteristik 
 * untuk mendapatkan velocity 6 dB / Octave roll off
 * 
 * Lihat Bab 17
 * 
 * secara mudah dijelaskan :
 * 		buat respon yang dikehendaki
 * 		inverse fft
 * 	
 */
#if 0
void buat_velocity(dfloat *out, int M)
{
	int i;
	int index;
	int p_desain;
	
    dfloat *real_in;
    dfloat *image_in;
    dfloat *real_out;
    dfloat *image_out;
    dfloat sum;
	
	/* 
	 * panjang filter rencana misalnya 3 * M 
	 * 		2 x untuk iFFT
     * 		4 x untuk dfloat
	 * 		3 x untuk panjang desain 3 x M
	 */
	p_desain = 2 * 4 * M;
	
    real_in = (dfloat *) malloc(p_desain * 4);
    image_in = (dfloat *) malloc(p_desain * 4);
    real_out = (dfloat *) malloc(p_desain * 4);
    image_out = (dfloat *) malloc(p_desain * 4);
	
	for (i=0; i<= p_desain; i++)
	{
		real_in[i] = 0.00;
		image_in[i] = 0.00;
	}
	
	/* diisi dengan respon filter dikehendaki */
	for (i=1; i<= (p_desain/2); i++)
	{
        //real_in[i] = (dfloat) (2.00 * M_PI * 512) / (2.00 * M_PI * i);
        real_in[i] = (dfloat) 1.0 / (2 * M_PI * i);
		image_in[i] = 0.00;
	}
	real_in[0] = 1.0;
	image_in[0] = 0.00;
	
	/* inverse FFT, sebanyak 2 x desain filter */
    fft_dfloat( p_desain, 1, real_in, image_in, real_out, image_out);
	
	/* rotate */
	for (i=0; i< p_desain ; i++)
	{
		index = i + (M / 2);
		if (index > p_desain ) index = index - (p_desain + 1);
		
		/* variable image_in dipinjam */
		image_in[index] = real_out[i];
	}
	
	sum = 0;
	/* window signal */	
	for (i=0; i<= M ; i++)
	{
		out[i] = image_in[i] * (0.54 - 0.46 * cos(2 * M_PI * i / M));
		sum = sum + out[i];
	}
	
	/* normalisasi kernel */
	for (i=0; i<= M ; i++)
	{
		out[i] = out[i] / sum;
	}
	
}
#endif


>>>>>>> temp_furkan

#endif
